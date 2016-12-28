# Copyright (C) 2013 Duncan Macleod
# Copyright (C) 2016 Kipp Cannon
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 3 of the License, or (at your
# option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
# Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

"""Modules extending the Cache file functionality from LAL
"""

import os
import re
import tempfile
from six.moves import urllib

from glue import segments

from .. import git_version
from ..lal import CacheImport
from ..lal import LIGOTimeGPS

__author__ = "Duncan Macleod <duncan.macleod@ligo.org>"
__version__ = git_version.id
__date__ = git_version.date

__all__ = ['CacheEntry', 'lalcache_from_gluecache']

def lalcache_from_gluecache(cache):
    """Convert a glue.lal.Cache object to a lal.Cache object.
    Writes cache to temporary file and reads to Cache.

    @param cache
        LAL cache object from GLUE to convert
        type cache glue.lal.Cache

    @returns a lal.Cache object representing the same data
    """
    with tempfile.NamedTemporaryFile(delete=False) as t:
        cache = cache
        for e in cache:
            e.segment = type(e.segment)(int(e.segment[0]), int(e.segment[1]))
        cache.tofile(t)
        frcache = CacheImport(t.name)
    os.remove(t.name)
    return frcache


#
# Representation of a line in a LAL cache file
#


class CacheEntry(object):
    """
    A Python object representing one line in a LAL cache file.

    The LAL cache format is defined elsewhere, and what follows is meant
    only to be informative, not an official specification.  Each line in a
    LAL cache identifies a single file, and the line consists of five
    columns of white-space delimited text.

    The first column, "observatory", generally stores the name of an
    observatory site or one or more instruments (preferably delimited by
    ",", but often there is no delimiter between instrument names in which
    case they should be 2 characters each).

    The second column, "description", stores a short string tag that is
    usually all capitals with "_" separating components, in the style of
    the description part of the LIGO-Virgo frame filename format.

    The third and fourth columns store the start time and duration in GPS
    seconds of the interval spanned by the file identified by the cache
    line.  When the file does not start on an integer second or its
    duration is not an integer number of seconds, the conventions of the
    LIGO-Virgo frame filename format apply.

    The fifth (last) column stores the file's URL.

    The values for these columns are stored in the .observatory,
    .description, .segment and .url attributes of instances of this class,
    respectively.  The .segment attribute stores a glue.segments.segment
    object describing the interval spanned by the file.  Any of these
    attributes except the URL is allowed to be None.

    This module also provides a Cache class, which some codes use to
    represent an entire LAL cache file.  However, for most use cases a
    simple Python list or set of CacheEntry objects is sufficient for
    representing a LAL cache file.

    Example (parse a string):

    >>> c = CacheEntry("H1 S5 815901601 576.5 file://localhost/home/kipp/tmp/1/H1-815901601-576.xml")
    >>> c.scheme
    'file'
    >>> c.host
    'localhost'

    Example (one-liners to read and write a cache file):

    >>> import os
    >>> filename = "874000000-20000.cache"
    >>> # adjustment for doctest in out-of-tree builds
    >>> inname = os.path.join(os.environ.get("LAL_TEST_SRCDIR", "."), filename)
    >>> cache = map(CacheEntry, open(inname))
    >>> f = open(filename + ".new", "w")
    >>> for cacheentry in cache: print >>f, str(cacheentry)

    Example (extract segmentlist dictionary from LAL cache):

    >>> from glue import segments
    >>> seglists = segments.segmentlistdict()
    >>> for cacheentry in cache:
    ...    seglists |= cacheentry.segmentlistdict
    ...

    NOTE:  the CacheEntry type defines a comparison operation and a
    .__hash__() implementation, both of which disregard the URL.  That is,
    if two CacheEntry objects differ only by URL and otherwise have same
    metadata, they are considered to be redundant copies of the same data.
    For example, uniquification with a set() will retain only one redundant
    copy, selected at random.

    >>> x = CacheEntry("H1 S5 815901601 576.5 file://localhost/home/kipp/tmp/1/H1-815901601-576.xml")
    >>> y = CacheEntry("H1 S5 815901601 576.5 gsiftp://data.server.org/bigpileofdata/H1-815901601-576.xml")
    >>> x == y
    True
    >>> len(set((x, y)))
    1

    NOTE:  this is a pure Python object providing an alternative
    representation of the contents of a LAL cache file to the C
    implementation in the LAL library proper.  The two are not
    interchangeable.

    See also:

    glue.segmentsUtils.fromlalcache()
    """
    # How to parse a line in a LAL cache file.  Five white-space
    # delimited columns.
    _regex = re.compile(r"\A\s*(?P<obs>\S+)\s+(?P<dsc>\S+)\s+(?P<strt>\S+)\s+(?P<dur>\S+)\s+(?P<url>\S+)\s*\Z")
    _url_regex = re.compile(r"\A((.*/)*(?P<obs>[^/]+)-(?P<dsc>[^/]+)-(?P<strt>[^/]+)-(?P<dur>[^/\.]+)\.[^/]+)\Z")

    def __init__(self, *args, **kwargs):
        """
        Intialize a CacheEntry object.  The arguments can take two forms:
        a single string argument, which is interpreted and parsed as a line
        from a LAL cache file, or four arguments used to explicitly
        initialize the observatory, description, segment and URL in that
        order.  When parsing a single line of text from a LAL cache, an
        optional key-word argument "coltype" can be provided to set the
        type the start and durations are parsed as.  The default is
        lal.LIGOTimeGPS.

        Example:

        >>> c = CacheEntry("H1", "S5", segments.segment(815901601, 815902177.5), "file://localhost/home/kipp/tmp/1/H1-815901601-576.xml")
        >>> print c.segment
        [815901601 ... 815902177.5)
        >>> print str(c)
        H1 S5 815901601 576.5 file://localhost/home/kipp/tmp/1/H1-815901601-576.xml
        >>> c = CacheEntry("H1 S5 815901601 576.5 file://localhost/home/kipp/tmp/1/H1-815901601-576.xml")
        >>> print c.segment
        [815901601 ... 815902177.5)
        >>> print CacheEntry("H1 S5 815901601 576.5 file://localhost/home/kipp/tmp/1/H1-815901601-576.xml", coltype = float).segment
        [815901601.0 ... 815902177.5)

        See also the .from_T050017() class method for an
        alternative initialization mechanism.
        """
        if len(args) == 1:
            # parse line of text as an entry in a cache file
            match = self._regex.search(args[0])
            try:
                match = match.groupdict()
            except AttributeError:
                raise ValueError("could not convert %s to CacheEntry" % repr(args[0]))
            self.observatory = match["obs"]
            self.description = match["dsc"]
            # FIXME:  remove typecasts when LIGOTimeGPS can be passed a unicode
            start = str(match["strt"])
            duration = str(match["dur"])
            coltype = kwargs.pop("coltype", LIGOTimeGPS)
            if start == "-" and duration == "-":
                # no segment information
                self.segment = None
            else:
                start = coltype(start)
                self.segment = segments.segment(start, start + coltype(duration))
            self.url = match["url"]
            if kwargs:
                raise TypeError("unrecognized keyword arguments: %s" % ", ".join(kwargs))
        elif len(args) == 4:
            # parse arguments as observatory, description,
            # segment, url
            if kwargs:
                raise TypeError("invalid arguments: %s" % ", ".join(kwargs))
            self.observatory, self.description, self.segment, self.url = args
        else:
            raise TypeError("invalid arguments: %s" % args)

        # "-" indicates an empty column
        if self.observatory == "-":
            self.observatory = None
        if self.description == "-":
            self.description = None


    def __str__(self):
        """
        Convert the CacheEntry to a string in the format of a line in a LAL
        cache.  Used to write the CacheEntry to a file.

        Example:

        >>> c = CacheEntry("H1 S5 815901601 576.5 file://localhost/home/kipp/tmp/1/H1-815901601-576.xml")
        >>> str(c)
        'H1 S5 815901601 576.5 file://localhost/home/kipp/tmp/1/H1-815901601-576.xml'
        """
        if self.segment is not None:
            start = str(self.segment[0])
            duration = str(abs(self.segment))
        else:
            start = "-"
            duration = "-"
        return "%s %s %s %s %s" % (self.observatory or "-", self.description or "-", start, duration, self.url)

    def __cmp__(self, other):
        """
        Compare two CacheEntry objects by observatory, then description,
        then segment.  CacheEntry objects that have different URLs but for
        which all other metadata are the same are considered to be
        equivalent.  If two entries differ only by their URL, they are
        considered to be redundant copies of the same data, and by
        comparing them as equal the Python sort operation (which is a
        stable sort) will preserve their relative order.  By preserving the
        order of redundant copies, we allow the preference for the order in
        which redundant copies are to be attempted to be conveyed by their
        order in the list, and preserved.
        """
        if not isinstance(other, CacheEntry):
            raise TypeError("can only compare CacheEntry to CacheEntry")
        return cmp((self.observatory, self.description, self.segment), (other.observatory, other.description, other.segment))

    def __hash__(self):
        """
        CacheEntry objects are hashed by the tuple (observatory,
        description, segment), i.e., the URL is disregarded.
        """
        return hash((self.observatory, self.description, self.segment))

    @property
    def url(self):
        """
        The cache entry's URL.  The URL is constructed from the values of
        the scheme, host, and path attributes.  Assigning a value to the
        URL attribute causes the value to be parsed and the scheme, host
        and path attributes updated.
        """
        return urllib.parse.urlunparse((self.scheme, self.host, self.path, None, None, None))

    @url.setter
    def url(self, url):
        self.scheme, self.host, self.path = urllib.parse.urlparse(url)[:3]

    @property
    def segmentlistdict(self):
        """
        A segmentlistdict object describing the instruments and time
        spanned by this CacheEntry.  A new object is constructed each time
        this attribute is accessed (segments are immutable so there is no
        reason to try to share a reference to the CacheEntry's internal
        segment; modifications of one would not be reflected in the other
        anyway).

        Example:

        >>> c = CacheEntry(u"H1 S5 815901601 576.5 file://localhost/home/kipp/tmp/1/H1-815901601-576.xml")
        >>> c.segmentlistdict
        {u'H1': [segment(LIGOTimeGPS(815901601, 0), LIGOTimeGPS(815902177, 500000000))]}

        The \"observatory\" column of the cache entry, which is frequently
        used to store instrument names, is parsed into instrument names for
        the dictionary keys using the same rules as
        glue.ligolw.lsctables.instrument_set_from_ifos().

        Example:

        >>> c = CacheEntry(u"H1H2, S5 815901601 576.5 file://localhost/home/kipp/tmp/1/H1H2-815901601-576.xml")
        >>> c.segmentlistdict
        {u'H1H2': [segment(LIGOTimeGPS(815901601, 0), LIGOTimeGPS(815902177, 500000000))]}
        """
        # the import has to be done here to break the cyclic
        # dependancy
        from glue.ligolw.lsctables import instrument_set_from_ifos
        instruments = instrument_set_from_ifos(self.observatory) or (None,)
        return segments.segmentlistdict((instrument, segments.segmentlist(self.segment is not None and [self.segment] or [])) for instrument in instruments)

    @classmethod
    def from_T050017(cls, url, coltype = LIGOTimeGPS):
        """
        Parse a URL in the style of T050017-00 into a CacheEntry.  The
        T050017-00 file name format is, essentially,

        observatory-description-start-duration.extension

        Example:

        >>> c = CacheEntry.from_T050017("file://localhost/data/node144/frames/S5/strain-L2/LLO/L-L1_RDS_C03_L2-8365/L-L1_RDS_C03_L2-836562330-83.gwf")
        >>> c.observatory
        'L'
        >>> c.host
        'localhost'
        >>> os.path.basename(c.path)
        'L-L1_RDS_C03_L2-836562330-83.gwf'
        """
        match = cls._url_regex.search(url)
        if not match:
            raise ValueError("could not convert %s to CacheEntry" % repr(url))
        observatory = match.group("obs")
        description = match.group("dsc")
        # FIXME:  remove typecasts when LIGOTimeGPS can be passed a unicode
        start = str(match.group("strt"))
        duration = str(match.group("dur"))
        if start == "-" and duration == "-":
            # no segment information
            segment = None
        else:
            segment = segments.segment(coltype(start), coltype(start) + coltype(duration))
        return cls(observatory, description, segment, url)
