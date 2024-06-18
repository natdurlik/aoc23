(* ::Package:: *)

(* ::Input:: *)
(*points:={{1,2},{2,4},{3,6},{4,9},{5,13},{6,16},{7,22},{8,30},{9,41},{10,50},{11,63},{12,74},{13,89},{14,99},{15,115},{16,129},{17,145},{18,165},{19,192},{20,216},{21,234},{22,261},{23,294},{24,326},{25,353},{26,395},{27,427},{28,460},{29,491},{30,537},{31,574},{32,605},{33,644},{34,689},{35,740},{36,784},{37,846},{38,894},{39,944},{40,989},{41,1053},{42,1107},{43,1146},{44,1196},{45,1256},{46,1324},{47,1383},{48,1464},{49,1528},{50,1594},{51,1653},{52,1735},{53,1805},{54,1853},{55,1914},{56,1988},{57,2072},{58,2145},{59,2244},{60,2324},{61,2406},{62,2479},{63,2579},{64,2665},{65,2722},{66,2794},{67,2882},{68,2982},{69,3069},{70,3186},{71,3282},{72,3380},{73,3467},{74,3585},{75,3687},{76,3753},{77,3836},{78,3938},{79,4054},{80,4155},{81,4290},{82,4402},{83,4516},{84,4617},{85,4753},{86,4871},{87,4946},{88,5040},{89,5156},{90,5288},{91,5403},{92,5556},{93,5684},{94,5814},{95,5929},{96,6083},{97,6217},{98,6301},{99,6406},{100,6536},{101,6684},{102,6813},{103,6984},{104,7128},{105,7274},{106,7403},{107,7575},{108,7725},{109,7818},{110,7934},{111,8078},{112,8242},{113,8385},{114,8574},{115,8734},{116,8896},{117,9039},{118,9229},{119,9395},{120,9497},{121,9624},{122,9782},{123,9962},{124,10119},{125,10326},{126,10502},{127,10680},{128,10837},{129,11045},{130,11227},{131,11338},{132,11476},{133,11648},{134,11844},{135,12015},{136,12240},{137,12432},{138,12626},{139,12797},{140,13023},{141,13221},{142,13341},{143,13490},{144,13676},{145,13888},{146,14073},{147,14316},{148,14524},{149,14734},{150,14919},{151,15163},{152,15377},{153,15506},{154,15666},{155,15866},{156,16094},{157,16293},{158,16554},{159,16778},{160,17004},{161,17203},{162,17465},{163,17695},{164,17833},{165,18004},{166,18218},{167,18462},{168,18675},{169,18954},{170,19194},{171,19436},{172,19649},{173,19929},{174,20175},{175,20322},{176,20504},{177,20732},{178,20992},{179,21219},{180,21516},{181,21772},{182,22030},{183,22257},{184,22555},{185,22817},{186,22973},{187,23166},{188,23408},{189,23684},{190,23925},{191,24240},{192,24512},{193,24786},{194,25027},{195,25343},{196,25621},{197,25786},{198,25990},{199,26246},{200,26538},{201,26793},{202,27126},{203,27414},{204,27704},{205,27959},{206,28293},{207,28587},{208,28761},{209,28976},{210,29246},{211,29554},{212,29823},{213,30174},{214,30478},{215,30784},{216,31053},{217,31405},{218,31715},{219,31898},{220,32124},{221,32408},{222,32732},{223,33015},{224,33384},{225,33704},{226,34026},{227,34309},{228,34679},{229,35005},{230,35197},{231,35434},{232,35732},{233,36072},{234,36369},{235,36756},{236,37092},{237,37430},{238,37727},{239,38115},{240,38457},{241,38658},{242,38906},{243,39218},{244,39574},{245,39885},{246,40290},{247,40642},{248,40996},{249,41307},{250,41713},{251,42071},{252,42281},{253,42540},{254,42866},{255,43238},{256,43563},{257,43986},{258,44354},{259,44724},{260,45049},{261,45473},{262,45847},{263,46066},{264,46336},{265,46676},{266,47064},{267,47403},{268,47844},{269,48228},{270,48614},{271,48953},{272,49395},{273,49785},{274,50013},{275,50294},{276,50648},{277,51052},{278,51405},{279,51864},{280,52264},{281,52666},{282,53019},{283,53479},{284,53885},{285,54122},{286,54414},{287,54782},{288,55202},{289,55569},{290,56046},{291,56462},{292,56880},{293,57247},{294,57725},{295,58147},{296,58393},{297,58696},{298,59078},{299,59514},{300,59895},{301,60390},{302,60822},{303,61256},{304,61637},{305,62133},{306,62571},{307,62826},{308,63140},{309,63536},{310,63988},{311,64383},{312,64896},{313,65344},{314,65794},{315,66189},{316,66703},{317,67157},{318,67421},{319,67746},{320,68156},{321,68624},{322,69033},{323,69564},{324,70028},{325,70494},{326,70903},{327,71435},{328,71905},{329,72178},{330,72514},{331,72938},{332,73422},{333,73845},{334,74394},{335,74874},{336,75356},{337,75779},{338,76329},{339,76815},{340,77097},{341,77444},{342,77882},{343,78382},{344,78819},{345,79386},{346,79882},{347,80380},{348,80817},{349,81385},{350,81887},{351,82178},{352,82536},{353,82988},{354,83504},{355,83955},{356,84540},{357,85052},{358,85566},{359,86017},{360,86603},{361,87121},{362,87421},{363,87790},{364,88256},{365,88788},{366,89253},{367,89856},{368,90384},{369,90914},{370,91379},{371,91983},{372,92517},{373,92826},{374,93206},{375,93686},{376,94234},{377,94713},{378,95334},{379,95878},{380,96424},{381,96903},{382,97525},{383,98075},{384,98393},{385,98784},{386,99278},{387,99842},{388,100335},{389,100974},{390,101534},{391,102096},{392,102589},{393,103229},{394,103795},{395,104122},{396,104524},{397,105032},{398,105612},{399,106119},{400,106776},{401,107352},{402,107930},{403,108437},{404,109095},{405,109677},{406,110013},{407,110426},{408,110948},{409,111544},{410,112065},{411,112740},{412,113332},{413,113926},{414,114447},{415,115123},{416,115721},{417,116066},{418,116490},{419,117026},{420,117638},{421,118173},{422,118866},{423,119474},{424,120084},{425,120619},{426,121313},{427,121927},{428,122281},{429,122716},{430,123266},{431,123894},{432,124443},{433,125154},{434,125778},{435,126404},{436,126953},{437,127665},{438,128295},{439,128658},{440,129104},{441,129668},{442,130312},{443,130875},{444,131604},{445,132244},{446,132886},{447,133449},{448,134179},{449,134825},{450,135197},{451,135654},{452,136232},{453,136892},{454,137469},{455,138216},{456,138872},{457,139530},{458,140107},{459,140855},{460,141517},{461,141898},{462,142366},{463,142958},{464,143634},{465,144225},{466,144990},{467,145662},{468,146336},{469,146927},{470,147693},{471,148371},{472,148761},{473,149240},{474,149846},{475,150538},{476,151143},{477,151926},{478,152614},{479,153304},{480,153909},{481,154693},{482,155387},{483,155786},{484,156276},{485,156896},{486,157604},{487,158223},{488,159024},{489,159728},{490,160434},{491,161053},{492,161855},{493,162565},{494,162973},{495,163474},{496,164108},{497,164832},{498,165465},{499,166284},{500,167004},{501,167726},{502,168359},{503,169179},{504,169905},{505,170322},{506,170834},{507,171482},{508,172222},{509,172869},{510,173706},{511,174442},{512,175180},{513,175827},{514,176665},{515,177407},{516,177833},{517,178356},{518,179018},{519,179774},{520,180435},{521,181290},{522,182042},{523,182796},{524,183457},{525,184313},{526,185071},{527,185506},{528,186040},{529,186716},{530,187488},{531,188163},{532,189036},{533,189804},{534,190574},{535,191249},{536,192123},{537,192897},{538,193341},{539,193886},{540,194576},{541,195364},{542,196053},{543,196944},{544,197728},{545,198514},{546,199203},{547,200095},{548,200885},{549,201338},{550,201894},{551,202598},{552,203402},{553,204105},{554,205014},{555,205814},{556,206616},{557,207319},{558,208229},{559,209035},{560,209497},{561,210064},{562,210782},{563,211602},{564,212319},{565,213246},{566,214062},{567,214880},{568,215597},{569,216525},{570,217347},{571,217818},{572,218396},{573,219128},{574,219964},{575,220695},{576,221640},{577,222472},{578,223306},{579,224037},{580,224983},{581,225821},{582,226301},{583,226890},{584,227636},{585,228488},{586,229233},{587,230196},{588,231044},{589,231894},{590,232639},{591,233603},{592,234457},{593,234946},{594,235546},{595,236306},{596,237174},{597,237933},{598,238914},{599,239778},{600,240644},{601,241403},{602,242385},{603,243255},{604,243753},{605,244364},{606,245138},{607,246022},{608,246795},{609,247794},{610,248674},{611,249556},{612,250329},{613,251329},{614,252215},{615,252722},{616,253344},{617,254132},{618,255032},{619,255819},{620,256836},{621,257732},{622,258630},{623,259417},{624,260435},{625,261337},{626,261853},{627,262486},{628,263288},{629,264204},{630,265005},{631,266040},{632,266952},{633,267866},{634,268667},{635,269703},{636,270621},{637,271146},{638,271790},{639,272606},{640,273538},{641,274353},{642,275406},{643,276334},{644,277264},{645,278079},{646,279133},{647,280067},{648,280601},{649,281256},{650,282086},{651,283034},{652,283863},{653,284934},{654,285878},{655,286824},{656,287653},{657,288725},{658,289675},{659,290218},{660,290884},{661,291728},{662,292692},{663,293535},{664,294624},{665,295584},{666,296546},{667,297389},{668,298479},{669,299445},{670,299997},{671,300674},{672,301532},{673,302512},{674,303369},{675,304476},{676,305452},{677,306430},{678,307287},{679,308395},{680,309377},{681,309938},{682,310626},{683,311498},{684,312494},{685,313365},{686,314490},{687,315482},{688,316476},{689,317347},{690,318473},{691,319471},{692,320041},{693,320740},{694,321626},{695,322638},{696,323523},{697,324666},{698,325674},{699,326684},{700,327569}}*)


(* ::Input:: *)
(*ListPlot[points]*)


(* ::Input:: *)
(*quadratic:=Interpolation[points]*)


(* ::Input:: *)
(*Plot[quadratic[x],{x,2,10000}]*)


(* ::Input:: *)
(*f[x_]:=3759+14925x+14812x^2*)


(* ::Input:: *)
(*f[202300]*)