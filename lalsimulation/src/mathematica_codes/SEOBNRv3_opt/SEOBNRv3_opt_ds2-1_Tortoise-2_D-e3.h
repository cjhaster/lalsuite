REAL8 tmp1=x->data[0]*x->data[0];
REAL8 tmp2=x->data[1]*x->data[1];
REAL8 tmp3=x->data[2]*x->data[2];
REAL8 tmp4=tmp1+tmp2+tmp3;
REAL8 tmp9=s1Vec->data[1]+s2Vec->data[1];
REAL8 tmp7=s1Vec->data[0]+s2Vec->data[0];
REAL8 tmp8=tmp7*tmp7;
REAL8 tmp10=tmp9*tmp9;
REAL8 tmp11=s1Vec->data[2]+s2Vec->data[2];
REAL8 tmp12=tmp11*tmp11;
REAL8 tmp13=tmp10+tmp12+tmp8;
REAL8 tmp15=1./sqrt(tmp13);
REAL8 tmp16=tmp15*tmp9;
REAL8 tmp17=0.1+tmp16;
REAL8 tmp20=tmp15*tmp7;
REAL8 tmp21=0.1+tmp20;
REAL8 tmp18=1/tmp13;
REAL8 tmp19=tmp12*tmp18;
REAL8 tmp22=tmp21*tmp21;
REAL8 tmp23=tmp17*tmp17;
REAL8 tmp24=tmp19+tmp22+tmp23;
REAL8 tmp25=1./sqrt(tmp24);
REAL8 tmp26=1./sqrt(tmp4);
REAL8 tmp5=(1.0/(tmp4*tmp4));
REAL8 tmp53=1/tmp4;
REAL8 tmp56=coeffs->KK*eta;
REAL8 tmp57=-1.+tmp56;
REAL8 tmp45=pow(tmp4,-2.5);
REAL8 tmp72=tmp13*tmp13;
REAL8 tmp51=(1.0/sqrt(tmp4*tmp4*tmp4));
REAL8 tmp58=(1.0/(tmp57*tmp57));
REAL8 tmp59=1.*tmp58;
REAL8 tmp60=1.*tmp13*tmp53;
REAL8 tmp61=1/tmp57;
REAL8 tmp62=2.*tmp26*tmp61;
REAL8 tmp63=tmp59+tmp60+tmp62;
REAL8 tmp98=(1.0/sqrt(tmp13*tmp13*tmp13));
REAL8 tmp96=(1.0/(tmp13*tmp13));
REAL8 tmp97=-2.*tmp12*tmp9*tmp96;
REAL8 tmp99=-2.*tmp21*tmp7*tmp9*tmp98;
REAL8 tmp100=-(tmp10*tmp98);
REAL8 tmp101=tmp100+tmp15;
REAL8 tmp102=2.*tmp101*tmp17;
REAL8 tmp103=tmp102+tmp97+tmp99;
REAL8 tmp104=(1.0/sqrt(tmp24*tmp24*tmp24));
REAL8 tmp64=1.*tmp21*tmp25*tmp26*x->data[0];
REAL8 tmp65=1.*tmp17*tmp25*tmp26*x->data[1];
REAL8 tmp66=1.*tmp11*tmp15*tmp25*tmp26*x->data[2];
REAL8 tmp67=tmp64+tmp65+tmp66;
REAL8 tmp86=-1.+m1PlusEtaKK;
REAL8 tmp71=c1k5*tmp13;
REAL8 tmp73=c2k5*tmp72;
REAL8 tmp74=c0k5+tmp71+tmp73;
REAL8 tmp75=1.*tmp45*tmp74;
REAL8 tmp76=c1k4*tmp13;
REAL8 tmp77=c2k4*tmp72;
REAL8 tmp78=c0k4+tmp76+tmp77;
REAL8 tmp79=1.*tmp5*tmp78;
REAL8 tmp80=c1k3*tmp13;
REAL8 tmp81=c0k3+tmp80;
REAL8 tmp82=1.*tmp51*tmp81;
REAL8 tmp83=c1k2*tmp13;
REAL8 tmp84=c0k2+tmp83;
REAL8 tmp85=1.*tmp53*tmp84;
REAL8 tmp87=coeffs->KK*tmp86;
REAL8 tmp88=coeffs->KK+tmp87;
REAL8 tmp89=-2.*m1PlusEtaKK*tmp26*tmp88;
REAL8 tmp90=1.*tmp26;
REAL8 tmp91=log(tmp90);
REAL8 tmp92=1.*coeffs->k5l*tmp45*tmp91;
REAL8 tmp93=1.+tmp75+tmp79+tmp82+tmp85+tmp89+tmp92;
REAL8 tmp68=tmp67*tmp67;
REAL8 tmp69=-tmp68;
REAL8 tmp70=1.+tmp69;
REAL8 tmp112=coeffs->KK*eta*tmp86;
REAL8 tmp113=log(tmp93);
REAL8 tmp114=eta*tmp113;
REAL8 tmp115=1.+tmp112+tmp114;
REAL8 tmp40=tmp1+tmp10+tmp12+tmp2+tmp3+tmp8;
REAL8 tmp14=sqrt(tmp13);
REAL8 tmp120=tmp40*tmp40;
REAL8 tmp121=-(tmp115*tmp13*tmp4*tmp63*tmp70);
REAL8 tmp122=tmp120+tmp121;
REAL8 tmp27=-(tmp17*tmp25*tmp26*x->data[0]);
REAL8 tmp28=1.*tmp21*tmp25*tmp26*x->data[1];
REAL8 tmp29=tmp27+tmp28;
REAL8 tmp30=p->data[2]*tmp29;
REAL8 tmp31=1.*tmp11*tmp15*tmp25*tmp26*x->data[0];
REAL8 tmp32=-(tmp21*tmp25*tmp26*x->data[2]);
REAL8 tmp33=tmp31+tmp32;
REAL8 tmp34=p->data[1]*tmp33;
REAL8 tmp35=-(tmp11*tmp15*tmp25*tmp26*x->data[1]);
REAL8 tmp36=1.*tmp17*tmp25*tmp26*x->data[2];
REAL8 tmp37=tmp35+tmp36;
REAL8 tmp38=p->data[0]*tmp37;
REAL8 tmp39=tmp30+tmp34+tmp38;
REAL8 tmp144=1/tmp122;
REAL8 tmp148=tmp13*tmp68;
REAL8 tmp149=tmp1+tmp148+tmp2+tmp3;
REAL8 tmp150=1/tmp149;
REAL8 tmp125=0.5*tmp103*tmp104*tmp17*tmp26*x->data[0];
REAL8 tmp126=-(tmp101*tmp25*tmp26*x->data[0]);
REAL8 tmp127=-0.5*tmp103*tmp104*tmp21*tmp26*x->data[1];
REAL8 tmp128=-(tmp25*tmp26*tmp7*tmp9*tmp98*x->data[1]);
REAL8 tmp129=tmp125+tmp126+tmp127+tmp128;
REAL8 tmp131=-0.5*tmp103*tmp104*tmp11*tmp15*tmp26*x->data[0];
REAL8 tmp132=-(tmp11*tmp25*tmp26*tmp9*tmp98*x->data[0]);
REAL8 tmp133=0.5*tmp103*tmp104*tmp21*tmp26*x->data[2];
REAL8 tmp134=1.*tmp25*tmp26*tmp7*tmp9*tmp98*x->data[2];
REAL8 tmp135=tmp131+tmp132+tmp133+tmp134;
REAL8 tmp137=0.5*tmp103*tmp104*tmp11*tmp15*tmp26*x->data[1];
REAL8 tmp138=1.*tmp11*tmp25*tmp26*tmp9*tmp98*x->data[1];
REAL8 tmp139=-0.5*tmp103*tmp104*tmp17*tmp26*x->data[2];
REAL8 tmp140=1.*tmp101*tmp25*tmp26*x->data[2];
REAL8 tmp141=tmp137+tmp138+tmp139+tmp140;
REAL8 tmp154=1/tmp70;
REAL8 tmp105=-0.5*tmp103*tmp104*tmp21*tmp26*x->data[0];
REAL8 tmp106=-(tmp25*tmp26*tmp7*tmp9*tmp98*x->data[0]);
REAL8 tmp107=-0.5*tmp103*tmp104*tmp17*tmp26*x->data[1];
REAL8 tmp108=1.*tmp101*tmp25*tmp26*x->data[1];
REAL8 tmp109=-0.5*tmp103*tmp104*tmp11*tmp15*tmp26*x->data[2];
REAL8 tmp110=-(tmp11*tmp25*tmp26*tmp9*tmp98*x->data[2]);
REAL8 tmp111=tmp105+tmp106+tmp107+tmp108+tmp109+tmp110;
REAL8 tmp168=tmp26*tmp29*x->data[1];
REAL8 tmp169=-(tmp26*tmp33*x->data[2]);
REAL8 tmp170=tmp168+tmp169;
REAL8 tmp171=p->data[0]*tmp170;
REAL8 tmp172=tmp26*tmp33*x->data[0];
REAL8 tmp173=-(tmp26*tmp37*x->data[1]);
REAL8 tmp174=tmp172+tmp173;
REAL8 tmp175=p->data[2]*tmp174;
REAL8 tmp176=-(tmp26*tmp29*x->data[0]);
REAL8 tmp177=tmp26*tmp37*x->data[2];
REAL8 tmp178=tmp176+tmp177;
REAL8 tmp179=p->data[1]*tmp178;
REAL8 tmp180=tmp171+tmp175+tmp179;
REAL8 tmp186=tmp180*tmp180;
REAL8 tmp42=2.*c1k5*tmp9;
REAL8 tmp43=4.*c2k5*tmp13*tmp9;
REAL8 tmp44=tmp42+tmp43;
REAL8 tmp46=1.*tmp44*tmp45;
REAL8 tmp47=2.*c1k4*tmp9;
REAL8 tmp48=4.*c2k4*tmp13*tmp9;
REAL8 tmp49=tmp47+tmp48;
REAL8 tmp50=1.*tmp49*tmp5;
REAL8 tmp52=2.*c1k3*tmp51*tmp9;
REAL8 tmp54=2.*c1k2*tmp53*tmp9;
REAL8 tmp55=tmp46+tmp50+tmp52+tmp54;
REAL8 tmp94=1/tmp93;
REAL8 tmp190=p->data[0]*tmp26*x->data[0];
REAL8 tmp191=p->data[1]*tmp26*x->data[1];
REAL8 tmp192=p->data[2]*tmp26*x->data[2];
REAL8 tmp193=tmp190+tmp191+tmp192;
REAL8 tmp194=tmp193*tmp193;
REAL8 tmp182=2.*tmp111*tmp13*tmp67;
REAL8 tmp183=2.*tmp68*tmp9;
REAL8 tmp184=tmp182+tmp183;
REAL8 tmp185=(1.0/(tmp149*tmp149));
REAL8 tmp195=-3.*eta;
REAL8 tmp196=26.+tmp195;
REAL8 tmp197=2.*eta*tmp196*tmp51;
REAL8 tmp198=6.*eta*tmp53;
REAL8 tmp199=1.+tmp197+tmp198;
REAL8 tmp200=log(tmp199);
REAL8 tmp201=1.+tmp200;
REAL8 tmp205=4.+tmp195;
REAL8 tmp208=1./(tmp40*tmp40*tmp40*tmp40);
REAL8 tmp210=(tmp193*tmp193*tmp193*tmp193);
REAL8 tmp211=tmp201*tmp201;
REAL8 tmp207=(tmp4*tmp4*tmp4);
REAL8 tmp209=(tmp63*tmp63*tmp63*tmp63);
REAL8 tmp216=(tmp115*tmp115*tmp115*tmp115);
REAL8 tmp41=4.*tmp40*tmp9;
REAL8 tmp95=-(eta*tmp13*tmp4*tmp55*tmp63*tmp70*tmp94);
REAL8 tmp116=2.*tmp111*tmp115*tmp13*tmp4*tmp63*tmp67;
REAL8 tmp117=-2.*tmp115*tmp13*tmp70*tmp9;
REAL8 tmp118=-2.*tmp115*tmp4*tmp63*tmp70*tmp9;
REAL8 tmp119=tmp116+tmp117+tmp118+tmp41+tmp95;
REAL8 tmp123=(1.0/(tmp122*tmp122));
REAL8 tmp130=p->data[2]*tmp129;
REAL8 tmp136=p->data[1]*tmp135;
REAL8 tmp142=p->data[0]*tmp141;
REAL8 tmp143=tmp130+tmp136+tmp142;
REAL8 tmp220=tmp39*tmp39;
REAL8 tmp188=(1.0/(tmp70*tmp70));
REAL8 tmp147=1/tmp63;
REAL8 tmp151=1/tmp115;
REAL8 tmp152=tmp122*tmp147*tmp150*tmp151*tmp53;
REAL8 tmp226=tmp150*tmp154*tmp186*tmp4;
REAL8 tmp227=tmp115*tmp150*tmp194*tmp201*tmp4*tmp63;
REAL8 tmp228=2.*eta*tmp205*tmp207*tmp208*tmp209*tmp210*tmp211*tmp216;
REAL8 tmp229=tmp144*tmp149*tmp154*tmp220*tmp4;
REAL8 tmp230=1.+tmp226+tmp227+tmp228+tmp229;
REAL8 tmp244=sqrt(tmp4*tmp4*tmp4);
REAL8 tmp246=1/mass1;
REAL8 tmp247=mass2*s1Vec->data[0]*tmp246;
REAL8 tmp248=1/mass2;
REAL8 tmp249=mass1*s2Vec->data[0]*tmp248;
REAL8 tmp250=tmp247+tmp249;
REAL8 tmp243=sqrt(tmp4);
REAL8 tmp155=tmp129*tmp26*x->data[1];
REAL8 tmp156=-(tmp135*tmp26*x->data[2]);
REAL8 tmp157=tmp155+tmp156;
REAL8 tmp158=p->data[0]*tmp157;
REAL8 tmp159=tmp135*tmp26*x->data[0];
REAL8 tmp160=-(tmp141*tmp26*x->data[1]);
REAL8 tmp161=tmp159+tmp160;
REAL8 tmp162=p->data[2]*tmp161;
REAL8 tmp163=-(tmp129*tmp26*x->data[0]);
REAL8 tmp164=tmp141*tmp26*x->data[2];
REAL8 tmp165=tmp163+tmp164;
REAL8 tmp166=p->data[1]*tmp165;
REAL8 tmp167=tmp158+tmp162+tmp166;
REAL8 tmp181=2.*tmp150*tmp154*tmp167*tmp180*tmp4;
REAL8 tmp187=-(tmp154*tmp184*tmp185*tmp186*tmp4);
REAL8 tmp189=2.*tmp111*tmp150*tmp186*tmp188*tmp4*tmp67;
REAL8 tmp202=eta*tmp150*tmp194*tmp201*tmp4*tmp55*tmp63*tmp94;
REAL8 tmp203=-(tmp115*tmp184*tmp185*tmp194*tmp201*tmp4*tmp63);
REAL8 tmp204=2.*tmp115*tmp150*tmp194*tmp201*tmp9;
REAL8 tmp221=-(tmp119*tmp123*tmp149*tmp154*tmp220*tmp4);
REAL8 tmp222=2.*tmp143*tmp144*tmp149*tmp154*tmp39*tmp4;
REAL8 tmp223=tmp144*tmp154*tmp184*tmp220*tmp4;
REAL8 tmp224=2.*tmp111*tmp144*tmp149*tmp188*tmp220*tmp4*tmp67;
REAL8 tmp256=tmp181+tmp187+tmp189+tmp202+tmp203+tmp204+tmp221+tmp222+tmp223+tmp224;
REAL8 tmp206=eta*eta;
REAL8 tmp262=tmp63*tmp63;
REAL8 tmp214=tmp4*tmp4;
REAL8 tmp265=tmp115*tmp115;
REAL8 tmp272=-16.*eta;
REAL8 tmp273=21.*tmp206;
REAL8 tmp274=tmp272+tmp273;
REAL8 tmp278=0.+tmp226+tmp227+tmp229;
REAL8 tmp280=-47.*eta;
REAL8 tmp281=54.*tmp206;
REAL8 tmp282=tmp243*tmp274*tmp278;
REAL8 tmp283=tmp280+tmp281+tmp282;
REAL8 tmp261=(eta*eta*eta);
REAL8 tmp264=1./(tmp149*tmp149*tmp149);
REAL8 tmp296=-6.*eta;
REAL8 tmp297=39.*tmp206;
REAL8 tmp298=tmp296+tmp297;
REAL8 tmp301=16.*eta;
REAL8 tmp302=147.*tmp206;
REAL8 tmp303=tmp243*tmp278*tmp298;
REAL8 tmp304=tmp301+tmp302+tmp303;
REAL8 tmp313=mass2*s1Vec->data[2]*tmp246;
REAL8 tmp314=mass1*s2Vec->data[2]*tmp248;
REAL8 tmp315=tmp313+tmp314;
REAL8 tmp263=-720.*tmp115*tmp185*tmp207*tmp210*tmp211*tmp261*tmp262*tmp55*tmp94;
REAL8 tmp266=720.*tmp184*tmp206*tmp207*tmp210*tmp211*tmp262*tmp264*tmp265;
REAL8 tmp267=-1440.*tmp185*tmp206*tmp210*tmp211*tmp214*tmp265*tmp63*tmp9;
REAL8 tmp268=103.*eta;
REAL8 tmp269=-60.*tmp206;
REAL8 tmp270=tmp268+tmp269;
REAL8 tmp271=2.*tmp243*tmp256*tmp270;
REAL8 tmp275=6.*tmp115*tmp150*tmp194*tmp201*tmp214*tmp256*tmp274*tmp63;
REAL8 tmp276=3.*eta;
REAL8 tmp277=23.+tmp276;
REAL8 tmp279=2.*eta*tmp256*tmp277*tmp278*tmp4;
REAL8 tmp284=6.*eta*tmp150*tmp194*tmp201*tmp244*tmp283*tmp55*tmp63*tmp94;
REAL8 tmp285=-6.*tmp115*tmp184*tmp185*tmp194*tmp201*tmp244*tmp283*tmp63;
REAL8 tmp286=12.*tmp115*tmp150*tmp194*tmp201*tmp243*tmp283*tmp9;
REAL8 tmp287=tmp263+tmp266+tmp267+tmp271+tmp275+tmp279+tmp284+tmp285+tmp286;
REAL8 tmp289=1620.*tmp115*tmp185*tmp207*tmp210*tmp211*tmp261*tmp262*tmp55*tmp94;
REAL8 tmp290=-1620.*tmp184*tmp206*tmp207*tmp210*tmp211*tmp262*tmp264*tmp265;
REAL8 tmp291=3240.*tmp185*tmp206*tmp210*tmp211*tmp214*tmp265*tmp63*tmp9;
REAL8 tmp292=-109.*eta;
REAL8 tmp293=51.*tmp206;
REAL8 tmp294=tmp292+tmp293;
REAL8 tmp295=4.*tmp243*tmp256*tmp294;
REAL8 tmp299=-6.*tmp115*tmp150*tmp194*tmp201*tmp214*tmp256*tmp298*tmp63;
REAL8 tmp300=-90.*eta*tmp256*tmp278*tmp4;
REAL8 tmp305=-6.*eta*tmp150*tmp194*tmp201*tmp244*tmp304*tmp55*tmp63*tmp94;
REAL8 tmp306=6.*tmp115*tmp184*tmp185*tmp194*tmp201*tmp244*tmp304*tmp63;
REAL8 tmp307=-12.*tmp115*tmp150*tmp194*tmp201*tmp243*tmp304*tmp9;
REAL8 tmp308=tmp289+tmp290+tmp291+tmp295+tmp299+tmp300+tmp305+tmp306+tmp307;
REAL8 tmp333=mass2*s1Vec->data[1]*tmp246;
REAL8 tmp334=mass1*s2Vec->data[1]*tmp248;
REAL8 tmp335=tmp333+tmp334;
REAL8 tmp355=tmp278*tmp278;
REAL8 tmp350=27.*eta;
REAL8 tmp351=-353.+tmp350;
REAL8 tmp352=2.*eta*tmp351;
REAL8 tmp353=-360.*tmp185*tmp206*tmp207*tmp210*tmp211*tmp262*tmp265;
REAL8 tmp354=2.*tmp243*tmp270*tmp278;
REAL8 tmp356=eta*tmp277*tmp355*tmp4;
REAL8 tmp357=6.*tmp115*tmp150*tmp194*tmp201*tmp244*tmp283*tmp63;
REAL8 tmp358=tmp352+tmp353+tmp354+tmp356+tmp357;
REAL8 tmp361=8.+tmp276;
REAL8 tmp362=-112.*eta*tmp361;
REAL8 tmp363=810.*tmp185*tmp206*tmp207*tmp210*tmp211*tmp262*tmp265;
REAL8 tmp364=4.*tmp243*tmp278*tmp294;
REAL8 tmp365=-45.*eta*tmp355*tmp4;
REAL8 tmp366=-6.*tmp115*tmp150*tmp194*tmp201*tmp244*tmp304*tmp63;
REAL8 tmp367=tmp362+tmp363+tmp364+tmp365+tmp366;
REAL8 tmp371=coeffs->d1v2*eta*tmp51*tmp7;
REAL8 tmp372=-8.*tmp7;
REAL8 tmp373=14.*tmp250;
REAL8 tmp374=-36.*tmp115*tmp150*tmp194*tmp201*tmp244*tmp63*tmp7;
REAL8 tmp375=-30.*tmp115*tmp150*tmp194*tmp201*tmp244*tmp250*tmp63;
REAL8 tmp376=3.*tmp243*tmp278*tmp7;
REAL8 tmp377=4.*tmp243*tmp250*tmp278;
REAL8 tmp378=tmp372+tmp373+tmp374+tmp375+tmp376+tmp377;
REAL8 tmp379=0.08333333333333333*eta*tmp26*tmp378;
REAL8 tmp380=-0.013888888888888888*tmp250*tmp358*tmp53;
REAL8 tmp381=0.006944444444444444*tmp367*tmp53*tmp7;
REAL8 tmp382=tmp247+tmp249+tmp371+tmp379+tmp380+tmp381;
REAL8 tmp385=coeffs->d1v2*eta*tmp51*tmp9;
REAL8 tmp386=-8.*tmp9;
REAL8 tmp387=14.*tmp335;
REAL8 tmp388=-36.*tmp115*tmp150*tmp194*tmp201*tmp244*tmp63*tmp9;
REAL8 tmp389=-30.*tmp115*tmp150*tmp194*tmp201*tmp244*tmp335*tmp63;
REAL8 tmp390=3.*tmp243*tmp278*tmp9;
REAL8 tmp391=4.*tmp243*tmp278*tmp335;
REAL8 tmp392=tmp386+tmp387+tmp388+tmp389+tmp390+tmp391;
REAL8 tmp393=0.08333333333333333*eta*tmp26*tmp392;
REAL8 tmp394=-0.013888888888888888*tmp335*tmp358*tmp53;
REAL8 tmp395=0.006944444444444444*tmp367*tmp53*tmp9;
REAL8 tmp396=tmp333+tmp334+tmp385+tmp393+tmp394+tmp395;
REAL8 tmp399=coeffs->d1v2*eta*tmp11*tmp51;
REAL8 tmp400=-8.*tmp11;
REAL8 tmp401=14.*tmp315;
REAL8 tmp402=-36.*tmp11*tmp115*tmp150*tmp194*tmp201*tmp244*tmp63;
REAL8 tmp403=-30.*tmp115*tmp150*tmp194*tmp201*tmp244*tmp315*tmp63;
REAL8 tmp404=3.*tmp11*tmp243*tmp278;
REAL8 tmp405=4.*tmp243*tmp278*tmp315;
REAL8 tmp406=tmp400+tmp401+tmp402+tmp403+tmp404+tmp405;
REAL8 tmp407=0.08333333333333333*eta*tmp26*tmp406;
REAL8 tmp408=-0.013888888888888888*tmp315*tmp358*tmp53;
REAL8 tmp409=0.006944444444444444*tmp11*tmp367*tmp53;
REAL8 tmp410=tmp313+tmp314+tmp399+tmp407+tmp408+tmp409;
REAL8 tmp415=sqrt(tmp149);
REAL8 tmp245=-36.*eta*tmp150*tmp194*tmp201*tmp244*tmp55*tmp63*tmp7*tmp94;
REAL8 tmp251=-30.*eta*tmp150*tmp194*tmp201*tmp244*tmp250*tmp55*tmp63*tmp94;
REAL8 tmp252=36.*tmp115*tmp184*tmp185*tmp194*tmp201*tmp244*tmp63*tmp7;
REAL8 tmp253=30.*tmp115*tmp184*tmp185*tmp194*tmp201*tmp244*tmp250*tmp63;
REAL8 tmp254=-72.*tmp115*tmp150*tmp194*tmp201*tmp243*tmp7*tmp9;
REAL8 tmp255=-60.*tmp115*tmp150*tmp194*tmp201*tmp243*tmp250*tmp9;
REAL8 tmp257=3.*tmp243*tmp256*tmp7;
REAL8 tmp258=4.*tmp243*tmp250*tmp256;
REAL8 tmp259=tmp245+tmp251+tmp252+tmp253+tmp254+tmp255+tmp257+tmp258;
REAL8 tmp260=0.08333333333333333*eta*tmp259*tmp26;
REAL8 tmp288=-0.013888888888888888*tmp250*tmp287*tmp53;
REAL8 tmp309=0.006944444444444444*tmp308*tmp53*tmp7;
REAL8 tmp310=tmp260+tmp288+tmp309;
REAL8 tmp311=1.*tmp21*tmp25*tmp310;
REAL8 tmp312=-36.*eta*tmp11*tmp150*tmp194*tmp201*tmp244*tmp55*tmp63*tmp94;
REAL8 tmp316=-30.*eta*tmp150*tmp194*tmp201*tmp244*tmp315*tmp55*tmp63*tmp94;
REAL8 tmp317=36.*tmp11*tmp115*tmp184*tmp185*tmp194*tmp201*tmp244*tmp63;
REAL8 tmp318=30.*tmp115*tmp184*tmp185*tmp194*tmp201*tmp244*tmp315*tmp63;
REAL8 tmp319=-72.*tmp11*tmp115*tmp150*tmp194*tmp201*tmp243*tmp9;
REAL8 tmp320=-60.*tmp115*tmp150*tmp194*tmp201*tmp243*tmp315*tmp9;
REAL8 tmp321=3.*tmp11*tmp243*tmp256;
REAL8 tmp322=4.*tmp243*tmp256*tmp315;
REAL8 tmp323=tmp312+tmp316+tmp317+tmp318+tmp319+tmp320+tmp321+tmp322;
REAL8 tmp324=0.08333333333333333*eta*tmp26*tmp323;
REAL8 tmp325=-0.013888888888888888*tmp287*tmp315*tmp53;
REAL8 tmp326=0.006944444444444444*tmp11*tmp308*tmp53;
REAL8 tmp327=tmp324+tmp325+tmp326;
REAL8 tmp328=1.*tmp11*tmp15*tmp25*tmp327;
REAL8 tmp329=mass1*tmp248;
REAL8 tmp330=coeffs->d1v2*eta*tmp51;
REAL8 tmp331=14.*mass1*tmp248;
REAL8 tmp332=-36.*eta*tmp150*tmp194*tmp201*tmp244*tmp55*tmp63*tmp9*tmp94;
REAL8 tmp336=-30.*eta*tmp150*tmp194*tmp201*tmp244*tmp335*tmp55*tmp63*tmp94;
REAL8 tmp337=36.*tmp115*tmp184*tmp185*tmp194*tmp201*tmp244*tmp63*tmp9;
REAL8 tmp338=30.*tmp115*tmp184*tmp185*tmp194*tmp201*tmp244*tmp335*tmp63;
REAL8 tmp339=-72.*tmp10*tmp115*tmp150*tmp194*tmp201*tmp243;
REAL8 tmp340=-60.*tmp115*tmp150*tmp194*tmp201*tmp243*tmp335*tmp9;
REAL8 tmp341=-36.*tmp115*tmp150*tmp194*tmp201*tmp244*tmp63;
REAL8 tmp342=-30.*mass1*tmp115*tmp150*tmp194*tmp201*tmp244*tmp248*tmp63;
REAL8 tmp343=3.*tmp243*tmp256*tmp9;
REAL8 tmp344=4.*tmp243*tmp256*tmp335;
REAL8 tmp345=3.*tmp243*tmp278;
REAL8 tmp346=4.*mass1*tmp243*tmp248*tmp278;
REAL8 tmp347=-8.+tmp331+tmp332+tmp336+tmp337+tmp338+tmp339+tmp340+tmp341+tmp342+tmp343+tmp344+tmp345+tmp346;
REAL8 tmp348=0.08333333333333333*eta*tmp26*tmp347;
REAL8 tmp349=-0.013888888888888888*tmp287*tmp335*tmp53;
REAL8 tmp359=-0.013888888888888888*mass1*tmp248*tmp358*tmp53;
REAL8 tmp360=0.006944444444444444*tmp308*tmp53*tmp9;
REAL8 tmp368=0.006944444444444444*tmp367*tmp53;
REAL8 tmp369=tmp329+tmp330+tmp348+tmp349+tmp359+tmp360+tmp368;
REAL8 tmp370=1.*tmp17*tmp25*tmp369;
REAL8 tmp383=-0.5*tmp103*tmp104*tmp21*tmp382;
REAL8 tmp384=-(tmp25*tmp382*tmp7*tmp9*tmp98);
REAL8 tmp397=-0.5*tmp103*tmp104*tmp17*tmp396;
REAL8 tmp398=1.*tmp101*tmp25*tmp396;
REAL8 tmp411=-0.5*tmp103*tmp104*tmp11*tmp15*tmp410;
REAL8 tmp412=-(tmp11*tmp25*tmp410*tmp9*tmp98);
REAL8 tmp413=tmp311+tmp328+tmp370+tmp383+tmp384+tmp397+tmp398+tmp411+tmp412;
REAL8 tmp426=1.*tmp21*tmp25*tmp382;
REAL8 tmp427=1.*tmp17*tmp25*tmp396;
REAL8 tmp428=1.*tmp11*tmp15*tmp25*tmp410;
REAL8 tmp429=tmp426+tmp427+tmp428;
REAL8 tmp416=tmp115*tmp4*tmp63;
REAL8 tmp417=sqrt(tmp416);
REAL8 tmp418=-tmp417;
REAL8 tmp419=tmp115*tmp144*tmp149*tmp4*tmp63;
REAL8 tmp420=sqrt(tmp419);
REAL8 tmp421=tmp415*tmp420;
REAL8 tmp422=tmp418+tmp421;
REAL8 tmp423=1.+tmp226+tmp227+tmp229;
REAL8 tmp424=1./sqrt(tmp423);
REAL8 tmp436=1./sqrt(tmp149);
REAL8 tmp439=1./sqrt(tmp416);
REAL8 tmp445=1./sqrt(tmp419);
REAL8 tmp471=sqrt(tmp423);
REAL8 tmp461=tmp26*tmp382*x->data[0];
REAL8 tmp462=tmp26*tmp396*x->data[1];
REAL8 tmp463=tmp26*tmp410*x->data[2];
REAL8 tmp464=tmp461+tmp462+tmp463;
REAL8 tmp468=sqrt(tmp13*tmp13*tmp13);
REAL8 tmp469=(1.0/sqrt(tmp149*tmp149*tmp149));
REAL8 tmp432=(1.0/sqrt(tmp423*tmp423*tmp423));
REAL8 tmp472=1.+tmp471;
REAL8 tmp474=tmp149*tmp149;
REAL8 tmp475=-(tmp115*tmp144*tmp214*tmp220*tmp474*tmp63);
REAL8 tmp476=tmp186*tmp4;
REAL8 tmp477=1.+tmp226+tmp227+tmp229+tmp471;
REAL8 tmp478=-(tmp149*tmp477*tmp70);
REAL8 tmp479=tmp476+tmp478;
REAL8 tmp480=tmp115*tmp4*tmp479*tmp63;
REAL8 tmp481=tmp475+tmp480;
REAL8 tmp482=tmp464*tmp481;
REAL8 tmp483=tmp115*tmp201*tmp4*tmp63;
REAL8 tmp484=sqrt(tmp483);
REAL8 tmp485=tmp37*tmp382;
REAL8 tmp486=tmp33*tmp396;
REAL8 tmp487=tmp29*tmp410;
REAL8 tmp488=tmp485+tmp486+tmp487;
REAL8 tmp489=-(tmp243*tmp39*tmp415*tmp420*tmp488);
REAL8 tmp490=tmp170*tmp382;
REAL8 tmp491=tmp178*tmp396;
REAL8 tmp492=tmp174*tmp410;
REAL8 tmp493=tmp490+tmp491+tmp492;
REAL8 tmp494=tmp180*tmp243*tmp417*tmp493;
REAL8 tmp495=tmp489+tmp494;
REAL8 tmp496=-(tmp193*tmp417*tmp484*tmp495);
REAL8 tmp497=tmp482+tmp496;
REAL8 tmp499=1/tmp472;
REAL8 tmp440=eta*tmp4*tmp55*tmp63*tmp94;
REAL8 tmp441=2.*tmp115*tmp9;
REAL8 tmp442=tmp440+tmp441;
REAL8 tmp446=-(tmp115*tmp119*tmp123*tmp149*tmp4*tmp63);
REAL8 tmp447=eta*tmp144*tmp149*tmp4*tmp55*tmp63*tmp94;
REAL8 tmp448=tmp115*tmp144*tmp184*tmp4*tmp63;
REAL8 tmp449=2.*tmp115*tmp144*tmp149*tmp9;
REAL8 tmp450=tmp446+tmp447+tmp448+tmp449;
REAL8 tmp457=tmp26*tmp310*x->data[0];
REAL8 tmp458=tmp26*tmp327*x->data[2];
REAL8 tmp459=tmp26*tmp369*x->data[1];
REAL8 tmp460=tmp457+tmp458+tmp459;
REAL8 tmp564=coeffs->k5l*tmp91;
REAL8 tmp565=c0k5+tmp564+tmp71+tmp73;
REAL8 tmp537=tmp310*tmp37;
REAL8 tmp538=tmp29*tmp327;
REAL8 tmp539=tmp33*tmp369;
REAL8 tmp540=tmp141*tmp382;
REAL8 tmp541=tmp135*tmp396;
REAL8 tmp542=tmp129*tmp410;
REAL8 tmp543=tmp537+tmp538+tmp539+tmp540+tmp541+tmp542;
REAL8 tmp548=tmp170*tmp310;
REAL8 tmp549=tmp174*tmp327;
REAL8 tmp550=tmp178*tmp369;
REAL8 tmp551=tmp157*tmp382;
REAL8 tmp552=tmp165*tmp396;
REAL8 tmp553=tmp161*tmp410;
REAL8 tmp554=tmp548+tmp549+tmp550+tmp551+tmp552+tmp553;
REAL8 tmp532=1./sqrt(tmp483);
REAL8 tmp533=eta*tmp201*tmp4*tmp55*tmp63*tmp94;
REAL8 tmp534=2.*tmp115*tmp201*tmp9;
REAL8 tmp535=tmp533+tmp534;
REAL8 tmp520=0.5*tmp256*tmp424;
REAL8 tmp521=tmp181+tmp187+tmp189+tmp202+tmp203+tmp204+tmp221+tmp222+tmp223+tmp224+tmp520;
REAL8 tmp615=tmp180*tmp193*tmp243*tmp464*tmp484;
REAL8 tmp616=-(tmp115*tmp194*tmp201*tmp4*tmp493*tmp63);
REAL8 tmp617=tmp149*tmp477*tmp493;
REAL8 tmp618=tmp615+tmp616+tmp617;
REAL8 tmp470=1/tmp423;
REAL8 tmp562=2.*tmp122*tmp14;
REAL8 tmp563=4.*tmp243*tmp40;
REAL8 tmp566=1.*tmp45*tmp565;
REAL8 tmp567=1.+tmp566+tmp79+tmp82+tmp85+tmp89;
REAL8 tmp568=1/tmp567;
REAL8 tmp569=-2.*m1PlusEtaKK*tmp88;
REAL8 tmp570=2.*tmp84;
REAL8 tmp571=3.*tmp81;
REAL8 tmp572=4.*tmp78;
REAL8 tmp573=5.*tmp26*tmp565;
REAL8 tmp574=tmp572+tmp573;
REAL8 tmp575=1.*tmp26*tmp574;
REAL8 tmp576=tmp571+tmp575;
REAL8 tmp577=1.*tmp26*tmp576;
REAL8 tmp578=tmp570+tmp577;
REAL8 tmp579=1.*tmp26*tmp578;
REAL8 tmp580=tmp569+tmp579;
REAL8 tmp581=-(eta*tmp568*tmp580*tmp63);
REAL8 tmp582=2.*tmp115*tmp243*tmp63;
REAL8 tmp583=1.*tmp61;
REAL8 tmp584=1.*tmp13*tmp26;
REAL8 tmp585=tmp583+tmp584;
REAL8 tmp586=-2.*tmp115*tmp585;
REAL8 tmp587=tmp581+tmp582+tmp586;
REAL8 tmp588=-(tmp13*tmp587*tmp70);
REAL8 tmp589=tmp563+tmp588;
REAL8 tmp590=-2.*tmp14*tmp243*tmp589;
REAL8 tmp591=tmp562+tmp590;
REAL8 tmp473=(1.0/(tmp472*tmp472));
REAL8 tmp624=-(tmp180*tmp39*tmp4*tmp415*tmp417*tmp420*tmp488);
REAL8 tmp625=tmp115*tmp144*tmp214*tmp220*tmp474*tmp493*tmp63;
REAL8 tmp626=tmp115*tmp4*tmp618*tmp63*tmp70;
REAL8 tmp627=tmp624+tmp625+tmp626;
REAL8 tmp501=1./(tmp122*tmp122*tmp122);
REAL8 tmp504=pow(tmp149,-2.5);
REAL8 tmp509=(1.0/sqrt(tmp416*tmp416*tmp416));
REAL8 tmp511=(1.0/sqrt(tmp419*tmp419*tmp419));
REAL8 tmp675=tmp150*tmp243;
REAL8 tmp676=-tmp532;
REAL8 tmp677=tmp675+tmp676;
REAL8 tmp664=-(tmp115*tmp4*tmp63);
REAL8 tmp665=tmp1+tmp10+tmp12+tmp2+tmp3+tmp664+tmp8;
REAL8 tmp685=-4.*tmp115*tmp244*tmp63;
REAL8 tmp686=tmp40*tmp587;
REAL8 tmp687=tmp685+tmp686;
REAL8 tmp688=0.5*tmp144*tmp147*tmp151*tmp40*tmp53*tmp687;
REAL8 tmp689=tmp675+tmp688;
REAL8 tmp666=2.*tmp471;
REAL8 tmp667=1.+tmp666;
REAL8 tmp236=(1.0/(tmp115*tmp115));
REAL8 tmp668=-(tmp13*tmp144*tmp243*tmp39*tmp40*tmp417*tmp420*tmp436*tmp464*tmp665*tmp667*tmp67*tmp70);
REAL8 tmp669=tmp201*tmp214*tmp262*tmp265;
REAL8 tmp670=1./sqrt(tmp669);
REAL8 tmp671=-2.*tmp115*tmp4*tmp63;
REAL8 tmp672=tmp484*tmp587;
REAL8 tmp673=tmp671+tmp672;
REAL8 tmp674=-0.5*tmp243*tmp39*tmp415*tmp420*tmp472*tmp493*tmp670*tmp673;
REAL8 tmp678=tmp180*tmp243*tmp417*tmp488*tmp677;
REAL8 tmp679=-(tmp13*tmp150*tmp193*tmp67*tmp70);
REAL8 tmp680=tmp180*tmp243*tmp677;
REAL8 tmp681=-(tmp13*tmp150*tmp67);
REAL8 tmp682=tmp13*tmp144*tmp150*tmp40*tmp665*tmp67;
REAL8 tmp683=tmp681+tmp682;
REAL8 tmp684=tmp193*tmp683*tmp70;
REAL8 tmp690=-(tmp180*tmp243*tmp689);
REAL8 tmp691=tmp680+tmp684+tmp690;
REAL8 tmp692=tmp471*tmp691;
REAL8 tmp693=tmp679+tmp692;
REAL8 tmp694=tmp417*tmp488*tmp693;
REAL8 tmp695=tmp243*tmp39*tmp415*tmp420*tmp493*tmp667*tmp689;
REAL8 tmp696=tmp678+tmp694+tmp695;
REAL8 tmp697=tmp417*tmp696;
REAL8 tmp698=tmp674+tmp697;
REAL8 tmp699=tmp484*tmp698;
REAL8 tmp700=tmp668+tmp699;
REAL8 tmp702=1/tmp477;
REAL8 tmp239=(1.0/(tmp63*tmp63));
REAL8 tmp632=2.*eta*tmp243*tmp55*tmp63*tmp94;
REAL8 tmp633=-2.*eta*tmp55*tmp585*tmp94;
REAL8 tmp634=4.*c1k2*tmp9;
REAL8 tmp635=6.*c1k3*tmp9;
REAL8 tmp636=4.*tmp49;
REAL8 tmp637=5.*tmp26*tmp44;
REAL8 tmp638=tmp636+tmp637;
REAL8 tmp639=1.*tmp26*tmp638;
REAL8 tmp640=tmp635+tmp639;
REAL8 tmp641=1.*tmp26*tmp640;
REAL8 tmp642=tmp634+tmp641;
REAL8 tmp643=-(eta*tmp26*tmp568*tmp63*tmp642);
REAL8 tmp644=(1.0/(tmp567*tmp567));
REAL8 tmp645=eta*tmp55*tmp580*tmp63*tmp644;
REAL8 tmp646=-2.*eta*tmp53*tmp568*tmp580*tmp9;
REAL8 tmp647=0.+tmp632+tmp633+tmp643+tmp645+tmp646;
REAL8 tmp711=2.*tmp9;
REAL8 tmp712=-(eta*tmp4*tmp55*tmp63*tmp94);
REAL8 tmp713=-2.*tmp115*tmp9;
REAL8 tmp714=tmp711+tmp712+tmp713;
REAL8 tmp746=-(tmp184*tmp185*tmp243);
REAL8 tmp747=(1.0/sqrt(tmp483*tmp483*tmp483));
REAL8 tmp748=0.5*tmp535*tmp747;
REAL8 tmp749=tmp746+tmp748;
REAL8 tmp769=-4.*eta*tmp244*tmp55*tmp63*tmp94;
REAL8 tmp770=tmp40*tmp647;
REAL8 tmp771=-8.*tmp115*tmp243*tmp9;
REAL8 tmp772=2.*tmp587*tmp9;
REAL8 tmp773=tmp769+tmp770+tmp771+tmp772;
REAL8 tmp774=0.5*tmp144*tmp147*tmp151*tmp40*tmp53*tmp773;
REAL8 tmp775=-0.5*tmp119*tmp123*tmp147*tmp151*tmp40*tmp53*tmp687;
REAL8 tmp776=-0.5*eta*tmp144*tmp147*tmp236*tmp40*tmp53*tmp55*tmp687*tmp94;
REAL8 tmp777=-(tmp144*tmp151*tmp239*tmp40*tmp5*tmp687*tmp9);
REAL8 tmp778=1.*tmp144*tmp147*tmp151*tmp53*tmp687*tmp9;
REAL8 tmp779=tmp746+tmp774+tmp775+tmp776+tmp777+tmp778;
REAL8 tmp153=1./sqrt(tmp152);
REAL8 tmp234=sqrt(tmp230);
REAL8 ds000010=(1.*eta*(2.*tmp14*tmp143*tmp144*tmp4-2.*tmp119*tmp123*tmp14*tmp39*tmp4+2.*tmp14*tmp144*tmp243*tmp413+tmp144*tmp154*tmp243*tmp39*tmp413*tmp415*tmp422*tmp424-2.*tmp119*tmp123*tmp14*tmp243*tmp429+tmp143*tmp144*tmp154*tmp243*tmp415*tmp422*tmp424*tmp429-tmp119*tmp123*tmp154*tmp243*tmp39*tmp415*tmp422*tmp424*tmp429-0.5*tmp144*tmp154*tmp243*tmp256*tmp39*tmp415*tmp422*tmp429*tmp432+0.5*tmp144*tmp154*tmp184*tmp243*tmp39*tmp422*tmp424*tmp429*tmp436+tmp144*tmp154*tmp243*tmp39*tmp415*tmp424*tmp429*(0.5*tmp184*tmp420*tmp436-0.5*tmp439*tmp442+0.5*tmp415*tmp445*tmp450)+2.*coeffs->dheffSSv2*eta*s2Vec->data[1]*tmp5-0.5*(2.*tmp310*tmp382+2.*tmp369*tmp396+2.*tmp327*tmp410-6.*tmp460*tmp464)*tmp51-0.25*tmp123*tmp154*tmp256*tmp439*tmp445*tmp469*tmp470*tmp473*tmp484*tmp591*tmp627-0.25*tmp123*tmp154*tmp256*tmp432*tmp439*tmp445*tmp469*tmp484*tmp499*tmp591*tmp627-tmp119*tmp154*tmp424*tmp439*tmp445*tmp469*tmp484*tmp499*tmp501*tmp591*tmp627-0.75*tmp123*tmp154*tmp184*tmp424*tmp439*tmp445*tmp484*tmp499*tmp504*tmp591*tmp627-0.25*tmp123*tmp154*tmp424*tmp442*tmp445*tmp469*tmp484*tmp499*tmp509*tmp591*tmp627-0.25*tmp123*tmp154*tmp424*tmp439*tmp450*tmp469*tmp484*tmp499*tmp511*tmp591*tmp627+0.25*tmp123*tmp154*tmp424*tmp439*tmp445*tmp469*tmp499*tmp532*tmp535*tmp591*tmp627-2.*tmp111*tmp115*tmp123*tmp244*tmp424*tmp439*tmp445*tmp468*tmp469*tmp497*tmp499*tmp63+2.*tmp111*tmp144*tmp188*tmp243*tmp39*tmp415*tmp422*tmp424*tmp429*tmp67+1.*tmp111*tmp123*tmp188*tmp424*tmp439*tmp445*tmp469*tmp484*tmp499*tmp591*tmp627*tmp67+1.*tmp115*tmp123*tmp244*tmp256*tmp439*tmp445*tmp468*tmp469*tmp470*tmp473*tmp497*tmp63*tmp67+1.*tmp115*tmp123*tmp244*tmp256*tmp432*tmp439*tmp445*tmp468*tmp469*tmp497*tmp499*tmp63*tmp67+4.*tmp115*tmp119*tmp244*tmp424*tmp439*tmp445*tmp468*tmp469*tmp497*tmp499*tmp501*tmp63*tmp67+3.*tmp115*tmp123*tmp184*tmp244*tmp424*tmp439*tmp445*tmp468*tmp497*tmp499*tmp504*tmp63*tmp67+1.*tmp115*tmp123*tmp244*tmp424*tmp442*tmp445*tmp468*tmp469*tmp497*tmp499*tmp509*tmp63*tmp67+1.*tmp115*tmp123*tmp244*tmp424*tmp439*tmp450*tmp468*tmp469*tmp497*tmp499*tmp511*tmp63*tmp67-tmp147*tmp151*tmp154*tmp184*tmp185*tmp420*tmp53*tmp700*tmp702+0.5*tmp147*tmp150*tmp151*tmp154*tmp445*tmp450*tmp53*tmp700*tmp702+2.*tmp111*tmp147*tmp150*tmp151*tmp188*tmp420*tmp53*tmp67*tmp700*tmp702+2.*tmp144*tmp15*tmp39*tmp4*tmp9+2.*tmp144*tmp15*tmp243*tmp429*tmp9-4.*tmp115*tmp123*tmp243*tmp424*tmp439*tmp445*tmp468*tmp469*tmp497*tmp499*tmp67*tmp9-6.*tmp115*tmp123*tmp14*tmp244*tmp424*tmp439*tmp445*tmp469*tmp497*tmp499*tmp63*tmp67*tmp9-2.*tmp150*tmp151*tmp154*tmp239*tmp420*tmp5*tmp700*tmp702*tmp9+0.5*tmp123*tmp154*tmp424*tmp439*tmp445*tmp469*tmp484*tmp499*tmp627*(2.*tmp119*tmp14+2.*tmp122*tmp15*tmp9-2.*tmp15*tmp243*tmp589*tmp9-2.*tmp14*tmp243*(2.*tmp111*tmp13*tmp587*tmp67-tmp13*tmp647*tmp70+8.*tmp243*tmp9-2.*tmp587*tmp70*tmp9))-2.*eta*tmp123*tmp244*tmp424*tmp439*tmp445*tmp468*tmp469*tmp497*tmp499*tmp55*tmp63*tmp67*tmp94-eta*tmp147*tmp150*tmp154*tmp236*tmp420*tmp53*tmp55*tmp700*tmp702*tmp94-2.*tmp115*tmp123*tmp244*tmp424*tmp439*tmp445*tmp468*tmp469*tmp499*tmp63*tmp67*(tmp460*tmp481-0.5*tmp193*tmp439*tmp442*tmp484*tmp495-0.5*tmp193*tmp417*tmp495*tmp532*tmp535-tmp193*tmp417*tmp484*(-(tmp143*tmp243*tmp415*tmp420*tmp488)-0.5*tmp184*tmp243*tmp39*tmp420*tmp436*tmp488-0.5*tmp243*tmp39*tmp415*tmp445*tmp450*tmp488+tmp167*tmp243*tmp417*tmp493+0.5*tmp180*tmp243*tmp439*tmp442*tmp493-tmp243*tmp39*tmp415*tmp420*tmp543+tmp180*tmp243*tmp417*tmp554)+tmp464*(-2.*tmp115*tmp144*tmp149*tmp184*tmp214*tmp220*tmp63+tmp115*tmp119*tmp123*tmp214*tmp220*tmp474*tmp63-2.*tmp115*tmp143*tmp144*tmp214*tmp39*tmp474*tmp63+tmp115*tmp4*tmp63*(2.*tmp167*tmp180*tmp4+2.*tmp111*tmp149*tmp477*tmp67-tmp184*tmp477*tmp70-tmp149*tmp521*tmp70)-2.*tmp115*tmp144*tmp220*tmp4*tmp474*tmp9+2.*tmp115*tmp479*tmp9-eta*tmp144*tmp214*tmp220*tmp474*tmp55*tmp63*tmp94+eta*tmp4*tmp479*tmp55*tmp63*tmp94))+0.5*tmp123*tmp154*tmp424*tmp439*tmp445*tmp469*tmp484*tmp499*tmp591*(-(tmp143*tmp180*tmp4*tmp415*tmp417*tmp420*tmp488)-tmp167*tmp39*tmp4*tmp415*tmp417*tmp420*tmp488-0.5*tmp180*tmp184*tmp39*tmp4*tmp417*tmp420*tmp436*tmp488-0.5*tmp180*tmp39*tmp4*tmp415*tmp420*tmp439*tmp442*tmp488-0.5*tmp180*tmp39*tmp4*tmp415*tmp417*tmp445*tmp450*tmp488-tmp180*tmp39*tmp4*tmp415*tmp417*tmp420*tmp543+2.*tmp115*tmp144*tmp149*tmp184*tmp214*tmp220*tmp493*tmp63-tmp115*tmp119*tmp123*tmp214*tmp220*tmp474*tmp493*tmp63+2.*tmp115*tmp143*tmp144*tmp214*tmp39*tmp474*tmp493*tmp63+tmp115*tmp144*tmp214*tmp220*tmp474*tmp554*tmp63-2.*tmp111*tmp115*tmp4*tmp618*tmp63*tmp67+2.*tmp115*tmp144*tmp220*tmp4*tmp474*tmp493*tmp9+2.*tmp115*tmp618*tmp70*tmp9+eta*tmp144*tmp214*tmp220*tmp474*tmp493*tmp55*tmp63*tmp94+eta*tmp4*tmp55*tmp618*tmp63*tmp70*tmp94+tmp115*tmp4*tmp63*tmp70*(tmp180*tmp193*tmp243*tmp460*tmp484+tmp167*tmp193*tmp243*tmp464*tmp484+tmp184*tmp477*tmp493+tmp149*tmp493*tmp521+0.5*tmp180*tmp193*tmp243*tmp464*tmp532*tmp535+tmp149*tmp477*tmp554-tmp115*tmp194*tmp201*tmp4*tmp554*tmp63-2.*tmp115*tmp194*tmp201*tmp493*tmp9-eta*tmp194*tmp201*tmp4*tmp493*tmp55*tmp63*tmp94))-0.5*tmp234*(tmp119*tmp147*tmp150*tmp151*tmp53-tmp122*tmp147*tmp151*tmp184*tmp185*tmp53-2.*tmp122*tmp150*tmp151*tmp239*tmp5*tmp9-eta*tmp122*tmp147*tmp150*tmp236*tmp53*tmp55*tmp94)*(1.0/sqrt(tmp152*tmp152*tmp152))-tmp147*tmp150*tmp151*tmp154*tmp420*tmp521*tmp53*tmp700*(1.0/(tmp477*tmp477))+tmp147*tmp150*tmp151*tmp154*tmp420*tmp53*tmp702*(2.*tmp111*tmp13*tmp144*tmp243*tmp39*tmp40*tmp417*tmp420*tmp436*tmp464*tmp665*tmp667*tmp68+0.5*tmp532*tmp535*tmp698-tmp111*tmp13*tmp144*tmp243*tmp39*tmp40*tmp417*tmp420*tmp436*tmp464*tmp665*tmp667*tmp70-tmp13*tmp144*tmp243*tmp256*tmp39*tmp40*tmp417*tmp420*tmp424*tmp436*tmp464*tmp665*tmp67*tmp70-tmp13*tmp144*tmp243*tmp39*tmp40*tmp417*tmp420*tmp436*tmp460*tmp665*tmp667*tmp67*tmp70-tmp13*tmp143*tmp144*tmp243*tmp40*tmp417*tmp420*tmp436*tmp464*tmp665*tmp667*tmp67*tmp70+tmp119*tmp123*tmp13*tmp243*tmp39*tmp40*tmp417*tmp420*tmp436*tmp464*tmp665*tmp667*tmp67*tmp70-0.5*tmp13*tmp144*tmp243*tmp39*tmp40*tmp420*tmp436*tmp439*tmp442*tmp464*tmp665*tmp667*tmp67*tmp70-0.5*tmp13*tmp144*tmp243*tmp39*tmp40*tmp417*tmp436*tmp445*tmp450*tmp464*tmp665*tmp667*tmp67*tmp70+0.5*tmp13*tmp144*tmp184*tmp243*tmp39*tmp40*tmp417*tmp420*tmp464*tmp469*tmp665*tmp667*tmp67*tmp70-tmp13*tmp144*tmp243*tmp39*tmp40*tmp417*tmp420*tmp436*tmp464*tmp667*tmp67*tmp70*tmp714-2.*tmp13*tmp144*tmp243*tmp39*tmp417*tmp420*tmp436*tmp464*tmp665*tmp667*tmp67*tmp70*tmp9-2.*tmp144*tmp243*tmp39*tmp40*tmp417*tmp420*tmp436*tmp464*tmp665*tmp667*tmp67*tmp70*tmp9+tmp484*(-0.25*tmp243*tmp256*tmp39*tmp415*tmp420*tmp424*tmp493*tmp670*tmp673-0.5*tmp143*tmp243*tmp415*tmp420*tmp472*tmp493*tmp670*tmp673-0.25*tmp184*tmp243*tmp39*tmp420*tmp436*tmp472*tmp493*tmp670*tmp673-0.25*tmp243*tmp39*tmp415*tmp445*tmp450*tmp472*tmp493*tmp670*tmp673-0.5*tmp243*tmp39*tmp415*tmp420*tmp472*tmp554*tmp670*tmp673+0.5*tmp439*tmp442*tmp696+tmp417*(tmp167*tmp243*tmp417*tmp488*tmp677+0.5*tmp180*tmp243*tmp439*tmp442*tmp488*tmp677+tmp180*tmp243*tmp417*tmp543*tmp677+1.*tmp243*tmp256*tmp39*tmp415*tmp420*tmp424*tmp493*tmp689+tmp143*tmp243*tmp415*tmp420*tmp493*tmp667*tmp689+0.5*tmp184*tmp243*tmp39*tmp420*tmp436*tmp493*tmp667*tmp689+0.5*tmp243*tmp39*tmp415*tmp445*tmp450*tmp493*tmp667*tmp689+tmp243*tmp39*tmp415*tmp420*tmp554*tmp667*tmp689+0.5*tmp439*tmp442*tmp488*tmp693+tmp417*tmp543*tmp693+tmp180*tmp243*tmp417*tmp488*tmp749+tmp243*tmp39*tmp415*tmp420*tmp493*tmp667*tmp779+tmp417*tmp488*(2.*tmp111*tmp13*tmp150*tmp193*tmp68+0.5*tmp256*tmp424*tmp691-tmp111*tmp13*tmp150*tmp193*tmp70+tmp13*tmp184*tmp185*tmp193*tmp67*tmp70-2.*tmp150*tmp193*tmp67*tmp70*tmp9+tmp471*(tmp167*tmp243*tmp677-2.*tmp111*tmp193*tmp67*tmp683-tmp167*tmp243*tmp689+tmp180*tmp243*tmp749-tmp180*tmp243*tmp779+tmp193*tmp70*(-(tmp111*tmp13*tmp150)+tmp111*tmp13*tmp144*tmp150*tmp40*tmp665+tmp13*tmp184*tmp185*tmp67-tmp119*tmp123*tmp13*tmp150*tmp40*tmp665*tmp67-tmp13*tmp144*tmp184*tmp185*tmp40*tmp665*tmp67+tmp13*tmp144*tmp150*tmp40*tmp67*tmp714-2.*tmp150*tmp67*tmp9+2.*tmp13*tmp144*tmp150*tmp665*tmp67*tmp9+2.*tmp144*tmp150*tmp40*tmp665*tmp67*tmp9))))-0.5*tmp243*tmp39*tmp415*tmp420*tmp472*tmp493*tmp670*(0.5*tmp532*tmp535*tmp587+tmp484*tmp647-4.*tmp115*tmp9-2.*eta*tmp4*tmp55*tmp63*tmp94)+0.25*tmp243*tmp39*tmp415*tmp420*tmp472*tmp493*tmp673*(4.*tmp201*tmp265*tmp4*tmp63*tmp9+2.*eta*tmp115*tmp201*tmp214*tmp262*tmp55*tmp94)*(1.0/sqrt(tmp669*tmp669*tmp669))))+(0.5*tmp153*(tmp181+tmp187+tmp189+tmp202+tmp203+tmp204+tmp221+tmp222+tmp223+tmp224+8.*tmp205*tmp206*tmp207*tmp208*tmp209*tmp210*tmp211*tmp55*tmp94*(tmp115*tmp115*tmp115)-16.*eta*tmp205*tmp207*tmp209*tmp210*tmp211*tmp216*tmp9*pow(tmp40,-5.)+16.*eta*tmp205*tmp208*tmp210*tmp211*tmp214*tmp216*tmp9*(tmp63*tmp63*tmp63)))/sqrt(tmp230)))/sqrt(1.+2.*eta*(-1.+tmp153*tmp234+2.*tmp14*tmp144*tmp39*tmp4+2.*tmp14*tmp144*tmp243*tmp429+tmp144*tmp154*tmp243*tmp39*tmp415*tmp422*tmp424*tmp429+0.5*tmp123*tmp154*tmp424*tmp439*tmp445*tmp469*tmp484*tmp499*tmp591*tmp627-2.*tmp115*tmp123*tmp244*tmp424*tmp439*tmp445*tmp468*tmp469*tmp497*tmp499*tmp63*tmp67+tmp147*tmp150*tmp151*tmp154*tmp420*tmp53*tmp700*tmp702+coeffs->dheffSSv2*eta*tmp5*(s1Vec->data[0]*s1Vec->data[0]+s1Vec->data[1]*s1Vec->data[1]+s1Vec->data[2]*s1Vec->data[2]+s2Vec->data[0]*s2Vec->data[0]+s2Vec->data[1]*s2Vec->data[1]+s2Vec->data[2]*s2Vec->data[2])-0.5*tmp51*(tmp382*tmp382+tmp396*tmp396+tmp410*tmp410-3.*(tmp464*tmp464))));
