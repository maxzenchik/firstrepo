

#include "demod.h"

using namespace std;



void Demod::init()
{

    this->simbol_sizeOfData=0;
    this->energeS=0;
    this->flag=false;
    for (int mm = 0; mm < N_tapM; ++mm)//обнуление массива
    {
        this->MI[mm]=0; this->MQ[mm]=0;///////////
    };
    kmax=0;
    maxThreshold=0;
    direct = undefined;
    paket = noise;
    system_config = VDL_2;
    schetchik_ZpolifF=0;
    schetchik_i=0;
    m_index=0;
    Z_index=0;
    opt_1=false;
    nFIR=0;
    out_polifaznik_= 0;
    en=false;
    n_Z=0;
}

complex<qint32> Demod::plfFir(int MI[], int MQ[],qint16 p_index, qint8 nFIR) {

    qint16 FIRCoef[Ntap] = {
        1,1,2,2,2,2,2,2,2,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,4,4,4,4,4,4,3,3,3,3,2,2,2,1,1,1,0,0,0,0,0,0,-1,-1,-2,-2,-3,-3,-4,-4,-5,-5,-6,-6,-7,-7,-7,-8,-8,-9,-9,-10,-10,-11,-11,-12,-12,-13,-13,-13,-14,-14,-15,-15,-15,-16,-16,-16,-16,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-16,-16,-16,-15,-15,-15,-14,-14,-13,-12,-12,-11,-11,-10,-9,-8,-8,-7,-6,-5,-4,-3,-2,-1,0,0,1,2,3,4,6,7,8,9,10,12,13,14,15,16,18,19,20,21,22,24,25,26,27,28,29,30,31,32,33,34,35,36,36,37,38,38,39,39,40,40,41,41,41,41,41,41,41,41,41,41,40,40,39,39,38,37,37,36,35,34,33,31,30,29,27,26,24,23,21,19,17,15,13,11,9,7,5,3,1,-1,-3,-5,-8,-10,-13,-15,-18,-20,-23,-25,-28,-30,-33,-35,-38,-40,-43,-45,-48,-50,-52,-54,-57,-59,-61,-63,-65,-67,-69,-70,-72,-73,-75,-76,-77,-79,-80,-80,-81,-82,-82,-83,-83,-83,-83,-83,-83,-82,-82,-81,-80,-79,-78,-77,-76,-74,-72,-70,-68,-66,-64,-62,-59,-56,-54,-51,-47,-44,-41,-37,-34,-30,-26,-22,-18,-14,-10,-6,-2,2,6,11,15,20,24,29,34,38,43,48,53,57,62,67,71,76,80,84,89,93,97,101,105,109,113,116,120,123,126,129,132,135,137,140,142,143,145,147,148,149,150,150,151,151,151,150,150,149,148,146,145,143,140,138,135,132,129,126,122,118,114,110,105,100,95,90,84,78,72,66,60,53,47,40,33,26,18,11,3,-3,-11,-19,-27,-35,-43,-51,-59,-67,-75,-83,-91,-99,-107,-115,-123,-130,-138,-145,-153,-160,-167,-173,-180,-186,-193,-199,-204,-210,-215,-220,-224,-229,-233,-236,-240,-243,-245,-248,-250,-251,-252,-253,-253,-253,-253,-252,-251,-249,-247,-245,-242,-238,-235,-230,-226,-221,-215,-209,-203,-196,-189,-182,-174,-166,-157,-148,-139,-130,-120,-109,-99,-88,-77,-66,-54,-42,-30,-18,-6,6,18,31,44,57,70,83,96,109,122,135,148,161,174,187,199,211,223,235,247,258,270,280,291,301,311,320,329,338,346,354,361,368,374,379,385,389,393,397,399,402,403,404,405,404,404,402,400,397,393,389,384,379,373,366,358,350,341,332,322,311,300,288,275,262,249,234,220,204,189,173,156,139,121,103,85,67,48,29,9,-9,-29,-49,-69,-90,-110,-130,-151,-171,-191,-211,-232,-252,-271,-291,-310,-329,-348,-366,-384,-402,-419,-435,-452,-467,-482,-497,-510,-523,-536,-547,-558,-569,-578,-587,-594,-601,-607,-612,-616,-620,-622,-623,-624,-623,-621,-619,-615,-611,-605,-598,-591,-582,-572,-562,-550,-537,-524,-509,-493,-477,-459,-441,-422,-402,-381,-359,-336,-313,-289,-264,-238,-212,-186,-158,-130,-102,-73,-44,-14,14,45,75,106,137,167,198,229,260,291,322,352,383,413,442,471,500,529,556,583,610,636,661,685,709,731,753,774,793,812,830,846,861,876,888,900,910,919,927,933,938,941,943,944,943,940,936,931,924,915,905,893,880,865,849,831,812,791,769,746,721,694,666,637,607,575,542,508,473,436,399,360,321,280,239,197,154,111,67,22,-22,-68,-114,-160,-207,-253,-300,-347,-394,-440,-487,-533,-579,-624,-669,-713,-757,-800,-842,-883,-923,-962,-1000,-1037,-1073,-1107,-1140,-1172,-1202,-1231,-1257,-1283,-1306,-1328,-1347,-1365,-1381,-1395,-1407,-1417,-1424,-1430,-1433,-1434,-1433,-1429,-1424,-1416,-1405,-1392,-1377,-1360,-1340,-1318,-1294,-1268,-1239,-1207,-1174,-1138,-1101,-1061,-1018,-974,-928,-880,-830,-778,-724,-669,-612,-553,-492,-431,-368,-303,-237,-171,-103,-34,34,105,176,247,319,391,464,536,609,681,754,826,897,968,1038,1107,1176,1243,1310,1375,1438,1500,1561,1620,1676,1731,1784,1835,1884,1930,1973,2014,2053,2088,2121,2151,2178,2202,2222,2240,2254,2264,2272,2276,2276,2272,2266,2255,2241,2223,2201,2176,2146,2113,2077,2036,1992,1944,1892,1837,1778,1716,1650,1580,1507,1431,1351,1268,1182,1093,1001,906,808,708,605,500,392,282,171,57,-57,-174,-293,-413,-534,-655,-778,-901,-1025,-1149,-1273,-1397,-1521,-1644,-1766,-1888,-2009,-2128,-2246,-2362,-2477,-2589,-2699,-2807,-2912,-3014,-3114,-3209,-3302,-3391,-3476,-3557,-3634,-3706,-3774,-3837,-3896,-3949,-3997,-4039,-4076,-4107,-4132,-4151,-4164,-4171,-4171,-4165,-4152,-4132,-4105,-4071,-4031,-3983,-3927,-3865,-3795,-3717,-3632,-3540,-3440,-3332,-3217,-3094,-2964,-2826,-2680,-2527,-2366,-2198,-2023,-1840,-1649,-1452,-1247,-1036,-817,-592,-360,-121,123,374,632,895,1165,1440,1720,2006,2297,2592,2893,3197,3506,3819,4136,4456,4780,5107,5436,5768,6102,6439,6776,7116,7456,7798,8140,8482,8824,9166,9508,9849,10188,10526,10863,11197,11529,11858,12185,12508,12828,13144,13456,13764,14067,14365,14658,14946,15228,15504,15774,16037,16294,16544,16786,17022,17249,17469,17681,17884,18080,18266,18444,18613,18773,18923,19064,19196,19318,19430,19533,19625,19708,19780,19842,19894,19935,19966,19987,19998,19998,19987,19966,19935,19894,19842,19780,19708,19625,19533,19430,19318,19196,19064,18923,18773,18613,18444,18266,18080,17884,17681,17469,17249,17022,16786,16544,16294,16037,15774,15504,15228,14946,14658,14365,14067,13764,13456,13144,12828,12508,12185,11858,11529,11197,10863,10526,10188,9849,9508,9166,8824,8482,8140,7798,7456,7116,6776,6439,6102,5768,5436,5107,4780,4456,4136,3819,3506,3197,2893,2592,2297,2006,1720,1440,1165,895,632,374,123,-121,-360,-592,-817,-1036,-1247,-1452,-1649,-1840,-2023,-2198,-2366,-2527,-2680,-2826,-2964,-3094,-3217,-3332,-3440,-3540,-3632,-3717,-3795,-3865,-3927,-3983,-4031,-4071,-4105,-4132,-4152,-4165,-4171,-4171,-4164,-4151,-4132,-4107,-4076,-4039,-3997,-3949,-3896,-3837,-3774,-3706,-3634,-3557,-3476,-3391,-3302,-3209,-3114,-3014,-2912,-2807,-2699,-2589,-2477,-2362,-2246,-2128,-2009,-1888,-1766,-1644,-1521,-1397,-1273,-1149,-1025,-901,-778,-655,-534,-413,-293,-174,-57,57,171,282,392,500,605,708,808,906,1001,1093,1182,1268,1351,1431,1507,1580,1650,1716,1778,1837,1892,1944,1992,2036,2077,2113,2146,2176,2201,2223,2241,2255,2266,2272,2276,2276,2272,2264,2254,2240,2222,2202,2178,2151,2121,2088,2053,2014,1973,1930,1884,1835,1784,1731,1676,1620,1561,1500,1438,1375,1310,1243,1176,1107,1038,968,897,826,754,681,609,536,464,391,319,247,176,105,34,-34,-103,-171,-237,-303,-368,-431,-492,-553,-612,-669,-724,-778,-830,-880,-928,-974,-1018,-1061,-1101,-1138,-1174,-1207,-1239,-1268,-1294,-1318,-1340,-1360,-1377,-1392,-1405,-1416,-1424,-1429,-1433,-1434,-1433,-1430,-1424,-1417,-1407,-1395,-1381,-1365,-1347,-1328,-1306,-1283,-1257,-1231,-1202,-1172,-1140,-1107,-1073,-1037,-1000,-962,-923,-883,-842,-800,-757,-713,-669,-624,-579,-533,-487,-440,-394,-347,-300,-253,-207,-160,-114,-68,-22,22,67,111,154,197,239,280,321,360,399,436,473,508,542,575,607,637,666,694,721,746,769,791,812,831,849,865,880,893,905,915,924,931,936,940,943,944,943,941,938,933,927,919,910,900,888,876,861,846,830,812,793,774,753,731,709,685,661,636,610,583,556,529,500,471,442,413,383,352,322,291,260,229,198,167,137,106,75,45,14,-14,-44,-73,-102,-130,-158,-186,-212,-238,-264,-289,-313,-336,-359,-381,-402,-422,-441,-459,-477,-493,-509,-524,-537,-550,-562,-572,-582,-591,-598,-605,-611,-615,-619,-621,-623,-624,-623,-622,-620,-616,-612,-607,-601,-594,-587,-578,-569,-558,-547,-536,-523,-510,-497,-482,-467,-452,-435,-419,-402,-384,-366,-348,-329,-310,-291,-271,-252,-232,-211,-191,-171,-151,-130,-110,-90,-69,-49,-29,-9,9,29,48,67,85,103,121,139,156,173,189,204,220,234,249,262,275,288,300,311,322,332,341,350,358,366,373,379,384,389,393,397,400,402,404,404,405,404,403,402,399,397,393,389,385,379,374,368,361,354,346,338,329,320,311,301,291,280,270,258,247,235,223,211,199,187,174,161,148,135,122,109,96,83,70,57,44,31,18,6,-6,-18,-30,-42,-54,-66,-77,-88,-99,-109,-120,-130,-139,-148,-157,-166,-174,-182,-189,-196,-203,-209,-215,-221,-226,-230,-235,-238,-242,-245,-247,-249,-251,-252,-253,-253,-253,-253,-252,-251,-250,-248,-245,-243,-240,-236,-233,-229,-224,-220,-215,-210,-204,-199,-193,-186,-180,-173,-167,-160,-153,-145,-138,-130,-123,-115,-107,-99,-91,-83,-75,-67,-59,-51,-43,-35,-27,-19,-11,-3,3,11,18,26,33,40,47,53,60,66,72,78,84,90,95,100,105,110,114,118,122,126,129,132,135,138,140,143,145,146,148,149,150,150,151,151,151,150,150,149,148,147,145,143,142,140,137,135,132,129,126,123,120,116,113,109,105,101,97,93,89,84,80,76,71,67,62,57,53,48,43,38,34,29,24,20,15,11,6,2,-2,-6,-10,-14,-18,-22,-26,-30,-34,-37,-41,-44,-47,-51,-54,-56,-59,-62,-64,-66,-68,-70,-72,-74,-76,-77,-78,-79,-80,-81,-82,-82,-83,-83,-83,-83,-83,-83,-82,-82,-81,-80,-80,-79,-77,-76,-75,-73,-72,-70,-69,-67,-65,-63,-61,-59,-57,-54,-52,-50,-48,-45,-43,-40,-38,-35,-33,-30,-28,-25,-23,-20,-18,-15,-13,-10,-8,-5,-3,-1,1,3,5,7,9,11,13,15,17,19,21,23,24,26,27,29,30,31,33,34,35,36,37,37,38,39,39,40,40,41,41,41,41,41,41,41,41,41,41,40,40,39,39,38,38,37,36,36,35,34,33,32,31,30,29,28,27,26,25,24,22,21,20,19,18,16,15,14,13,12,10,9,8,7,6,4,3,2,1,0,0,-1,-2,-3,-4,-5,-6,-7,-8,-8,-9,-10,-11,-11,-12,-12,-13,-14,-14,-15,-15,-15,-16,-16,-16,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-17,-16,-16,-16,-16,-15,-15,-15,-14,-14,-13,-13,-13,-12,-12,-11,-11,-10,-10,-9,-9,-8,-8,-7,-7,-7,-6,-6,-5,-5,-4,-4,-3,-3,-2,-2,-1,-1,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,3,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,2,2,2,2,2,2,2,1,1
    };
    qint32 sum_xhI=0;
    qint32 sum_xhQ=0;
    complex <qint32> sum_xh (0,0);//выход полифазного фильтра
    for(int  k=0; k<NtapT; k++)
    {
        int ln=p_index-k;  if (ln < 0) {ln=N_tapM+ln;}

        //перемножаем 1 выборку на множитель каждого КИХ фильтра и
        //суммируем все результаты перемножений по каждому КИХ фильтру
        sum_xhI +=(MI[ln]*FIRCoef[k*KoefI+nFIR])>>1;

        sum_xhQ +=(MQ[ln]*FIRCoef[k*KoefI+nFIR])>>1;
    }
    sum_xh.real(sum_xhI);
    sum_xh.imag(sum_xhQ);
    sum_xh=(sum_xh/DCgain);

    return sum_xh;
}
/////////////////////////////////////////////////////////////////////////////////

QVector<QBitArray> Demod::Difdem(qint16 signalI[],  qint16 signalQ[], double ResiverTakt)
{
    double  w=0;//текащая фаза демодулированного отсчета

    int Sampl_inSimbol=8;//число отсчетов на символ
    int Sampl_inKadr=349760;
    // ResiverTakt= 83932.85372;//входной параметр тактовая частота приемника
    int derror=MAXerror*(Sampl_inSimbol*KoefI*(F0-ResiverTakt))/F0;//ошибка соответствующая тактовой частоте приемника

    QBitArray  iDsizeBits(12);
    QBitArray  sistemConfigBits(12);//битовое поле  системной конфигурации VDL3
    QBitArray  data;// битовый массив одного пакета
    QVector <QBitArray> ArrayData;//массив пакетов, захваченных данным кадром

    static bool enableHeader=false;//для индикации о том что в данный момент ведется обработка заголовка пакета
    static int sizeOfData=0;// значение размера пакета, в битах

    static int overthresh=0;// значение превышения уровня обнаружителя относительно порогового

    static qint64 kadrsampl=0;//колличество обработанных кадров * колличество отсчетов  в кадре
    qint64 totalsampl=0;//колличество обработанных отсчетов, начиная от запуска программы
    QVector <qint64> set_totalsampl;//набор номеров отсчетов соответствовавших времени обработки каждого пакета
    QVector <burst> set_paket;//набор VDL режимов работры

    const int HeaderSize2=25;//длина заголовка пакета VDL2
    int Threshold=100000;//начальное значение порога для обнаружителя

    qint8 sampl;//текущее значение символа, в октальной нотации,

    QVector <int> set_sizeOfData ;//набор размеров  пакетов
    QVector <int> set_simbol_sizeOfData;//набор размеров  пакетов в символах
    QVector <QVector<qint8>> simboldata;//набор пакетов в символах, захваченных данным кадром

    complex <int> iq;//значение символа  на выходе  дифдекодера
    complex <double> iqD;//значение символа  на выходе  дифдекодера типа double

    int k_temp;
    int Rreal;
    int Rimag;
    //для уникального слова S vdl-2//
    int SumK_2r;//значение сумматора кореллятора по реальной составляющей
    int SumK_2i;//значение сумматора кореллятора по квадратурной составляющей

    int SIQ2=0; //значение функции корелляции VDL-2
    static int SIQ2_=0; //предыдущее значение функции корелляции VDL-2
    static int SIQ2__=0; //значение функции корелляции VDL-2 двумя отсчетами ранее

    //для уникального слова S1 vdl-3 //
    int SumK_S1r;//значение сумматора кореллятора по реальной составляющей
    int SumK_S1i;//значение сумматора кореллятора по квадратурной составляющей
    int SIQ3_1=0; //значение функции корелляции VDL-3
    static int SIQ3_1_=0;//предыдущее значение функции корелляции VDL-3
    static int SIQ3_1__=0;//значение функции корелляции VDL-3 двумя отсчетами ранее

    //для уникального слова S1* vdl-3 //
    int SumK_S1cr;//значение сумматора кореллятора по реальной составляющей
    int SumK_S1ci;//значение сумматора кореллятора по квадратурной составляющей
    int SIQ3_1c=0;//значение функции корелляции VDL-3
    static int SIQ3_1c_=0;//предыдущее значение функции корелляции VDL-3
    static int SIQ3_1c__=0;//значение функции корелляции VDL-3 двумя отсчетами ранее

    //для уникального слова S2 vdl-3  //
    int SumK_S2r;//значение сумматора кореллятора по реальной составляющей
    int SumK_S2i;//значение сумматора кореллятора по квадратурной составляющей
    int SIQ3_2=0;//значение функции корелляции VDL-3
    static int SIQ3_2_=0;//предыдущее значение функции корелляции VDL-3
    static int SIQ3_2__=0;//значение функции корелляции VDL-3 двумя отсчетами ранее

    //для уникального слова S2* vdl-3 //
    int SumK_S2cr;//значение сумматора кореллятора по реальной составляющей
    int SumK_S2ci;//значение сумматора кореллятора по квадратурной составляющей
    int SIQ3_2c=0;//значение функции корелляции VDL-3
    static int SIQ3_2c_=0;//предыдущее значение функции корелляции VDL-3
    static int SIQ3_2c__=0;//значение функции корелляции VDL-3 двумя отсчетами ранее

    int Korf=0; //результирующее значение кореллятора
    static int Korf_=0;//предыдущее результирующее значение кореллятора


    int UniqueWordVDL2real[137]={};
    int UniqueWordVDL2imag[137]={};
    //_______RAMP______________________________1 символ
    UniqueWordVDL2real[0]=32767;UniqueWordVDL2imag[0]=0;

    // ___________1__________                                 ____________2___________
    UniqueWordVDL2real[8]=32767;UniqueWordVDL2imag[8]=0;         UniqueWordVDL2real[16]=-23169;UniqueWordVDL2imag[16]=-23169;
    //_______________3____________                              ________________4____________
    UniqueWordVDL2real[24]=-23169;UniqueWordVDL2imag[24]=23169;  UniqueWordVDL2real[32]=23169;UniqueWordVDL2imag[32]=-23169;
    //  _______________5_____________                             _______________6____________
    UniqueWordVDL2real[40]=23169; UniqueWordVDL2imag[40]=-23169; UniqueWordVDL2real[48]=0;UniqueWordVDL2imag[48]=-32767;
    //_______________7___________                                _________________8__________
    UniqueWordVDL2real[56]=32767;UniqueWordVDL2imag[56]=0;       UniqueWordVDL2real[64]=-32767;UniqueWordVDL2imag[64]=0;
    //_________________9______________                           ______________10______________
    UniqueWordVDL2real[72]=-23169;UniqueWordVDL2imag[72]=23169;  UniqueWordVDL2real[80]=-32767;UniqueWordVDL2imag[80]=0;
    // _____________11______________                             ___________________12_______________
    UniqueWordVDL2real[88]=0;UniqueWordVDL2imag[88]=32767;       UniqueWordVDL2real[96]=-23169;UniqueWordVDL2imag[96]=-23169;
    //    _____________13_________                                _________________14______________
    UniqueWordVDL2real[104]=23169;UniqueWordVDL2imag[104]=-23169;UniqueWordVDL2real[112]=0;UniqueWordVDL2imag[112]=32767;
    //_________________15_______________                           _________________16__________
    UniqueWordVDL2real[120]=-23169;UniqueWordVDL2imag[120]=23169;UniqueWordVDL2real[128]=32767;UniqueWordVDL2imag[128]=0;
    //_________________17________________
    UniqueWordVDL2real[136]=32767;UniqueWordVDL2imag[136]=0;

    int UniqueWordVDL3_1real[137]={};
    int UniqueWordVDL3_1imag[137]={};
    //____________________________________RAMP_______________________2 символа
    UniqueWordVDL3_1real[0]=32767;UniqueWordVDL3_1imag[0]=0; UniqueWordVDL3_1real[8]=32767;UniqueWordVDL3_1imag[8]=0;

    UniqueWordVDL3_1real[16]=32767;UniqueWordVDL3_1imag[16]=0; UniqueWordVDL3_1real[24]=-23169;UniqueWordVDL3_1imag[24]=23169;
    //_______________3____________      ________________4____________
    UniqueWordVDL3_1real[32]=0;UniqueWordVDL3_1imag[32]=32767; UniqueWordVDL3_1real[40]=23169;UniqueWordVDL3_1imag[40]=23169;
    // _______________5_____________     _______________6____________
    UniqueWordVDL3_1real[48]=0;UniqueWordVDL3_1imag[48]=-32767;UniqueWordVDL3_1real[56]=0;UniqueWordVDL3_1imag[56]=32767;
    //  _______________7___________    _________________8____________
    UniqueWordVDL3_1real[64]=0;UniqueWordVDL3_1imag[64]=32767; UniqueWordVDL3_1real[72]=32767;UniqueWordVDL3_1imag[72]=0;
    //_________________9______________       ______________10______________
    UniqueWordVDL3_1real[80]=23169;UniqueWordVDL3_1imag[80]=23169; UniqueWordVDL3_1real[88]=-23169;UniqueWordVDL3_1imag[88]=-23169;
    //_____________11_______________         ___________________12_______________
    UniqueWordVDL3_1real[96]=-23169;UniqueWordVDL3_1imag[96]=23169;UniqueWordVDL3_1real[104]=0;UniqueWordVDL3_1imag[104]=-32767;
    //    ______________13___________            _________________14______________
    UniqueWordVDL3_1real[112]=-23169;UniqueWordVDL3_1imag[112]=23169; UniqueWordVDL3_1real[120]=-23169;UniqueWordVDL3_1imag[120]=-23169;
    //_________________15_______________      _________________16____________
    UniqueWordVDL3_1real[128]=0;UniqueWordVDL3_1imag[128]=-32767; UniqueWordVDL3_1real[136]=32767;UniqueWordVDL3_1imag[136]=0;

    int UniqueWordVDL3_1creal[137]={};
    int UniqueWordVDL3_1cimag[137]={};
    //____________________________________RAMP_________________________________________________2 символа
    UniqueWordVDL3_1creal[0]=(32767);  UniqueWordVDL3_1cimag[0]=(0);       UniqueWordVDL3_1creal[8]=(32767);   UniqueWordVDL3_1cimag[8]=(0);

    UniqueWordVDL3_1creal[16]=(32767); UniqueWordVDL3_1cimag[16]=(0);       UniqueWordVDL3_1creal[24]=(23169); UniqueWordVDL3_1cimag[24]=(-23169);
    //   _______________3____________                                      ________________4____________
    UniqueWordVDL3_1creal[32]=(0);     UniqueWordVDL3_1cimag[32]=(32767);   UniqueWordVDL3_1creal[40]=(-23169);UniqueWordVDL3_1cimag[40]=(-23169);
    //   _______________5_____________
    UniqueWordVDL3_1creal[48]=(0);     UniqueWordVDL3_1cimag[48]=(-32767);  UniqueWordVDL3_1creal[56]=(0);     UniqueWordVDL3_1cimag[56]=(-32767);
    //   _______________7_____________                                     _________________8____________
    UniqueWordVDL3_1creal[64]=(0);     UniqueWordVDL3_1cimag[64]=(32767);   UniqueWordVDL3_1creal[72]=(-32767);UniqueWordVDL3_1cimag[72]=(0);
    //_________________9______________                                        ________________10______________
    UniqueWordVDL3_1creal[80]=(23169); UniqueWordVDL3_1cimag[80]=(23169);   UniqueWordVDL3_1creal[88]=(23169); UniqueWordVDL3_1cimag[88]=(23169);
    //    _____________11_______________                                      _________________12_______________
    UniqueWordVDL3_1creal[96]=(-23169);UniqueWordVDL3_1cimag[96]=(23169);   UniqueWordVDL3_1creal[104]=(0);    UniqueWordVDL3_1cimag[104]=(32767);
    // ________________13___________                                         _________________14______________
    UniqueWordVDL3_1creal[112]=(-23169);UniqueWordVDL3_1cimag[112]=(23169); UniqueWordVDL3_1creal[120]=(23169);UniqueWordVDL3_1cimag[120]=(23169);
    //_________________15_______________                                      _________________16____________
    UniqueWordVDL3_1creal[128]=(0);    UniqueWordVDL3_1cimag[128]=(-32767); UniqueWordVDL3_1creal[136]=(-32767);UniqueWordVDL3_1cimag[136]=(0);


    int UniqueWordVDL3_2real[137]={};
    int UniqueWordVDL3_2imag[137]={};
    //____________________________________RAMP_________________________________________________2 символа
    UniqueWordVDL3_2real[0]=(32767);   UniqueWordVDL3_2imag[0]=(0);      UniqueWordVDL3_2real[8]=(32767);   UniqueWordVDL3_2imag[8]=(0);

    UniqueWordVDL3_2real[16]=(32767);  UniqueWordVDL3_2imag[16]=(0);     UniqueWordVDL3_2real[24]=(-23169); UniqueWordVDL3_2imag[24]=(23169);
    //_______________3____________                                         ________________4____________
    UniqueWordVDL3_2real[32]=(23169);  UniqueWordVDL3_2imag[32]=(23169); UniqueWordVDL3_2real[40]=(0);      UniqueWordVDL3_2imag[40]=(-32767);
    // _______________5_____________                                       _______________6____________
    UniqueWordVDL3_2real[48]=(0);      UniqueWordVDL3_2imag[48]=(-32767);UniqueWordVDL3_2real[56]=(23169);  UniqueWordVDL3_2imag[56]=(-23169);
    //  _______________7_____________                                         _________________8____________
    UniqueWordVDL3_2real[64]=(0);      UniqueWordVDL3_2imag[64]=(-32767);UniqueWordVDL3_2real[72]=(-23169);  UniqueWordVDL3_2imag[72]=(23169);
    //_________________9______________                                         ______________10______________
    UniqueWordVDL3_2real[80]=(-32767); UniqueWordVDL3_2imag[80]=(0);     UniqueWordVDL3_2real[88]=(0);       UniqueWordVDL3_2imag[88]=(-32767);
    //_____________11_______________                                           ___________________12_______________
    UniqueWordVDL3_2real[96]=(-32767); UniqueWordVDL3_2imag[96]=(0);     UniqueWordVDL3_2real[104]=(32767);  UniqueWordVDL3_2imag[104]=(0);
    //    ______________13___________                                          _________________14______________
    UniqueWordVDL3_2real[112]=(23169); UniqueWordVDL3_2imag[112]=(-23169);UniqueWordVDL3_2real[120]=(-23169);UniqueWordVDL3_2imag[120]=(23169);
    //_________________15_______________                                        _________________16____________
    UniqueWordVDL3_2real[128]=(-23169);UniqueWordVDL3_2imag[128]=(-23169);UniqueWordVDL3_2real[136]=(32767); UniqueWordVDL3_2imag[136]=(0);


    int UniqueWordVDL3_2creal[137]={};
    int UniqueWordVDL3_2cimag[137]={};
    //____________________________________RAMP_________________________________________________2 символа
    UniqueWordVDL3_2creal[0]=(32767);   UniqueWordVDL3_2cimag[0]=(0);     UniqueWordVDL3_2creal[8]=(32767);   UniqueWordVDL3_2cimag[8]=(0);

    UniqueWordVDL3_2creal[16]=(32767);  UniqueWordVDL3_2cimag[16]=(0);    UniqueWordVDL3_2creal[24]=(23169);  UniqueWordVDL3_2cimag[24]=(-23169);
    //   _______________3____________                                       ________________4____________
    UniqueWordVDL3_2creal[32]=(23169);  UniqueWordVDL3_2cimag[32]=(23169); UniqueWordVDL3_2creal[40]=(0);     UniqueWordVDL3_2cimag[40]=(32767);
    //   _______________5_____________
    UniqueWordVDL3_2creal[48]=(0);      UniqueWordVDL3_2cimag[48]=(-32767);UniqueWordVDL3_2creal[56]=(-23169);UniqueWordVDL3_2cimag[56]=(23169);
    //   _______________7_____________                                       _________________8____________
    UniqueWordVDL3_2creal[64]=(0);      UniqueWordVDL3_2cimag[64]=(-32767);UniqueWordVDL3_2creal[72]=(23169); UniqueWordVDL3_2cimag[72]=(-23169);
    //_________________9______________                                        ________________10______________
    UniqueWordVDL3_2creal[80]=(-32767); UniqueWordVDL3_2cimag[80]=(0);     UniqueWordVDL3_2creal[88]=(0);     UniqueWordVDL3_2cimag[88]=(32767);
    //    _____________11_______________                                     _________________12_______________
    UniqueWordVDL3_2creal[96]=(-32767); UniqueWordVDL3_2cimag[96]=(0);     UniqueWordVDL3_2creal[104]=(-32767);UniqueWordVDL3_2cimag[104]=(0);
    // ________________13___________                                        _________________14______________
    UniqueWordVDL3_2creal[112]=(23169); UniqueWordVDL3_2cimag[112]=(-23169);UniqueWordVDL3_2creal[120]=(23169);UniqueWordVDL3_2cimag[120]=(-23169);
    //_________________15_______________                                     _________________16____________
    UniqueWordVDL3_2creal[128]=(-23169);UniqueWordVDL3_2cimag[128]=(-23169);UniqueWordVDL3_2creal[136]=(-32767);UniqueWordVDL3_2cimag[136]=(0);

    double accError=0;

    // начало циклаобработки входного отсчета //
    for(int i=0;i<Sampl_inKadr;i++)
    {
        MI[Z_index]=signalI[i]; MQ[Z_index]=signalQ[i];

        SumK_2r=0;
        SumK_2i=0;

        SumK_S1r=0;
        SumK_S1i=0;

        SumK_S1cr=0;
        SumK_S1ci=0;

        SumK_S2r=0;
        SumK_S2i=0;

        SumK_S2cr=0;
        SumK_S2ci=0;
        for ( int k=0;k<137;k=k+Sampl_inSimbol)
        {
            int m_ind=Z_index-k; if (m_ind < 0) {m_ind=N_tapM+m_ind;};
            //РАССЧЕТ Корреляционной функции для
            // VDL-2

            k_temp=  UniqueWordVDL2real[136-k]*(MI[m_ind]+MQ[m_ind]);
            Rreal=(k_temp-MQ[m_ind]*(UniqueWordVDL2real[136-k]+UniqueWordVDL2imag[136-k]));
            Rimag=(k_temp+MI[m_ind]*(UniqueWordVDL2imag[136-k]-UniqueWordVDL2real[136-k]));

            SumK_2r +=(Rreal>>4);
            SumK_2i +=(Rimag>>4);

            //РАССЧЕТ Корреляционной функции
            //для VDL-3 стандартный пакет

            k_temp=  UniqueWordVDL3_1real[136-k]*(MI[m_ind]+MQ[m_ind]);
            Rreal=(k_temp-MQ[m_ind]*(UniqueWordVDL3_1real[136-k]+UniqueWordVDL3_1imag[136-k]));
            Rimag=(k_temp+MI[m_ind]*(UniqueWordVDL3_1imag[136-k]-UniqueWordVDL3_1real[136-k]));

            SumK_S1r +=(Rreal>>4);
            SumK_S1i +=(Rimag>>4);

            //РАССЧЕТ Корреляционной функции для
            // VDL-3 входящий сетев запрос

            k_temp=  UniqueWordVDL3_1creal[136-k]*(MI[m_ind]+MQ[m_ind]);
            Rreal=(k_temp-MQ[m_ind]*(UniqueWordVDL3_1creal[136-k]+UniqueWordVDL3_1cimag[136-k]));
            Rimag=(k_temp+MI[m_ind]*(UniqueWordVDL3_1cimag[136-k]-UniqueWordVDL3_1creal[136-k]));

            SumK_S1cr += (Rreal>>4);
            SumK_S1ci += (Rimag>>4);

            //РАССЧЕТ Корреляционной функции для
            // VDL-3 V/D

            k_temp=  UniqueWordVDL3_2real[136-k]*(MI[m_ind]+MQ[m_ind]);
            Rreal=(k_temp-MQ[m_ind]*(UniqueWordVDL3_2real[136-k]+UniqueWordVDL3_2imag[136-k]));
            Rimag=(k_temp+MI[m_ind]*(UniqueWordVDL3_2imag[136-k]-UniqueWordVDL3_2real[136-k]));

            SumK_S2r += (Rreal>>4);
            SumK_S2i += (Rimag>>4);

            //РАССЧЕТ Корреляционной функции для
            //VDL-3 исходящий сетев запрос

            k_temp=  UniqueWordVDL3_2creal[136-k]*(MI[m_ind]+MQ[m_ind]);
            Rreal=(k_temp-MQ[m_ind]*(UniqueWordVDL3_2creal[136-k]+UniqueWordVDL3_2cimag[136-k]));
            Rimag=(k_temp+MI[m_ind]*(UniqueWordVDL3_2cimag[136-k]-UniqueWordVDL3_2creal[136-k]));

            SumK_S2cr +=(Rreal>>4);
            SumK_S2ci +=(Rimag>>4);
        }

        SumK_2r >>= 16;
        SumK_2i >>= 16;
        int I=SumK_2r*SumK_2r;
        int Q=SumK_2i*SumK_2i;

        SIQ2__=SIQ2_;
        SIQ2_=SIQ2;
        SIQ2 =(I+Q);//значение корелляционной функции VDL-2

        SumK_S1r >>= 16;
        SumK_S1i >>= 16;
        int I3_1=SumK_S1r*SumK_S1r;
        int Q3_1=SumK_S1i*SumK_S1i;
        SIQ3_1__=SIQ3_1_;
        SIQ3_1_=SIQ3_1;
        SIQ3_1 =(I3_1+Q3_1);//значение корелляционной функции VDL3_M

        SumK_S1cr >>= 16;
        SumK_S1ci >>= 16;
        int I3_1c=SumK_S1cr*SumK_S1cr;
        int Q3_1c=SumK_S1ci*SumK_S1ci;
        SIQ3_1c__=SIQ3_1c_;
        SIQ3_1c_=SIQ3_1c;
        SIQ3_1c =(I3_1c+Q3_1c);//значение корелляционной функции VDL3_M

        SumK_S2r >>= 16;
        SumK_S2i >>= 16;
        int I3_2=SumK_S2r*SumK_S2r;
        int Q3_2=SumK_S2i*SumK_S2i;
        SIQ3_2__=SIQ3_2_;
        SIQ3_2_=SIQ3_2;
        SIQ3_2 =(I3_2+Q3_2) ;//значение корелляционной функции VDL3_M

        SumK_S2cr >>= 16;
        SumK_S2ci >>= 16;
        int I3_2c=SumK_S2cr*SumK_S2cr;
        int Q3_2c=SumK_S2ci*SumK_S2ci;
        SIQ3_2c__=SIQ3_2c_;
        SIQ3_2c_=SIQ3_2c;
        SIQ3_2c =(I3_2c+Q3_2c);//значение корелляционной функции VDL3

        Korf_=Korf;
        Korf=max(SIQ2,max(SIQ3_1,max(SIQ3_1c,max(SIQ3_2,SIQ3_2c))));//определяем максимальное значение

        overthresh=Korf-Threshold;

        if (nFIR==-1)
        {nFIR=15;schetchik_i=schetchik_i+1;}

        if ((overthresh>0)&&(Korf_>maxThreshold)&&(Korf_>Korf))//превышен  порог обнаружения
        {   maxThreshold=Korf_; simbol.clear();
            flag=true; n_Z=0;nFIR=0;  schetchik_ZpolifF=0;schetchik_i=0;
            opt_1=false;  m_index=0;
            accError=0; kmax=i-1;energeS=0;
            for ( int k=0;k<L_uniqueWord;k++)//вычисляем ожидаемый уровень сигнала
            {  int s_m=-k*Sampl_inSimbol+1+Z_index; if (s_m < 0) {s_m=s_m+N_tapM;};
                energeS+= abs(MI[s_m])+abs(MQ[s_m]);
            };

            if ((Korf_==SIQ2_)&&(SIQ2<SIQ2_))
            {   paket=mod2; simbol_sizeOfData=0;sizeOfData=0; enableHeader=true;//разрешаем запись пакета

                simbol.push_back(0);//символ zero

                double parabola =((double)(SIQ2-SIQ2__)/(double)(2*(SIQ2-2*SIQ2_+SIQ2__)))*KoefI;//начальное количество задержек полифазного фильтра
                qint8 begin_n =parabola; double drob=parabola-begin_n;
                if (drob>=0.5 ) { begin_n=begin_n+1; }; //
                if (drob<=-0.5) { begin_n=begin_n-1; }; //
                qint8 begin_nFIR;// начальный номер КИХ фильтра для полифазной фильтрации
                begin_nFIR=15-begin_n ;
                if (begin_nFIR<0) {begin_nFIR=16+begin_nFIR; n_Z=1; }
                if (begin_nFIR>15)
                {begin_nFIR=begin_nFIR-16; n_Z=-1;}

                nFIR=begin_nFIR;

            };
            if ((Korf_==SIQ3_1_)&&(SIQ3_1<SIQ3_1_))
            { paket=standart;simbol_sizeOfData=16;sizeOfData=48; enableHeader=false;  //разрешаем запись пакета

                double parabola =((double)(SIQ3_1-SIQ3_1__)/(double)(2*(SIQ3_1-2*SIQ3_1_+SIQ3_1__)))*KoefI;//начальное количество задержек полифазного фильтра
                qint8 begin_n =parabola; double drob=parabola-begin_n;
                if (drob>=0.5 ) { begin_n=begin_n+1; }; //
                if (drob<=-0.5) { begin_n=begin_n-1; }; //
                qint8 begin_nFIR;// начальный номер КИХ фильтра для полифазной фильтрации
                begin_nFIR=15-begin_n ;
                if (begin_nFIR<0) {begin_nFIR=16+begin_nFIR; n_Z=1; }
                if (begin_nFIR>15)
                {begin_nFIR=begin_nFIR-16; n_Z=-1;}

                nFIR=begin_nFIR;

            };
            if ((Korf_==SIQ3_1c_)&&(SIQ3_1c<SIQ3_1c_))
            {  paket=net_request;simbol_sizeOfData=16;sizeOfData=48; enableHeader=false;    //разрешаем запись пакета

                double parabola =((double)(SIQ3_1c-SIQ3_1c__)/(double)(2*(SIQ3_1c-2*SIQ3_1c_+SIQ3_1c__)))*KoefI;//начальное количество задержек полифазного фильтра
                qint8 begin_n =parabola; double drob=parabola-begin_n;
                if (drob>=0.5 ) { begin_n=begin_n+1; }; //
                if (drob<=-0.5) { begin_n=begin_n-1; }; //
                qint8 begin_nFIR;// начальный номер КИХ фильтра для полифазной фильтрации
                begin_nFIR=15-begin_n ;
                if (begin_nFIR<0) {begin_nFIR=16+begin_nFIR; n_Z=1; }
                if (begin_nFIR>15)
                {begin_nFIR=begin_nFIR-16; n_Z=-1;}

                nFIR=begin_nFIR; //


            };
            if ((Korf_==SIQ3_2_)&&(SIQ3_2<SIQ3_2_))
            {  paket=voice;simbol_sizeOfData=200;sizeOfData=600; enableHeader=false;   //разрешаем запись пакета


                double parabola =((double)(SIQ3_2-SIQ3_2__)/(double)(2*(SIQ3_2-2*SIQ3_2_+SIQ3_2__)))*KoefI;//начальное количество задержек полифазного фильтра
                qint8 begin_n =parabola; double drob=parabola-begin_n;
                if (drob>=0.5 ) { begin_n=begin_n+1; }; //
                if (drob<=-0.5) { begin_n=begin_n-1; }; //
                qint8 begin_nFIR;// начальный номер КИХ фильтра для полифазной фильтрации
                begin_nFIR=15-begin_n ;
                if (begin_nFIR<0) {begin_nFIR=16+begin_nFIR; n_Z=1; }
                if (begin_nFIR>15)
                {begin_nFIR=begin_nFIR-16; n_Z=-1;}

                nFIR=begin_nFIR; //

            };
            if ((Korf_==SIQ3_2c_)&&(SIQ3_2c<SIQ3_2c_))
            {  paket=id_air; simbol_sizeOfData=0;sizeOfData=0;  enableHeader=true; //разрешаем запись пакета
                double parabola =((double)(SIQ3_2c-SIQ3_2c__)/(double)(2*(SIQ3_2c-2*SIQ3_2c_+SIQ3_2c__)))*KoefI;//начальное количество задержек полифазного фильтра
                qint8 begin_n =parabola; double drob=parabola-begin_n;
                if (drob>=0.5 ) { begin_n=begin_n+1; }; //
                if (drob<=-0.5) { begin_n=begin_n-1; }; //
                qint8 begin_nFIR;// начальный номер КИХ фильтра для полифазной фильтрации
                begin_nFIR=15-begin_n ;
                if (begin_nFIR<0) {begin_nFIR=16+begin_nFIR; n_Z=1; }
                if (begin_nFIR>15)
                {begin_nFIR=begin_nFIR-16; n_Z=-1;}

                nFIR=begin_nFIR; //

            }
        };

        ////Демодулятор

        complex <int> out_polifaznik=0;

        if ((opt_1==true))
        {//условие пропуска входных отсчетов
            m_index=m_index+1   ; opt_1=false;
        }
        else
        {  if(en==true)
            {
                qint16 p_index=Z_index-m_index;
                if (   p_index<0) {p_index=N_tapM+p_index;};

                out_polifaznik=plfFir(MI,MQ,p_index,nFIR);
            }
        }
        switch (flag) {
        case true:

            schetchik_ZpolifF=schetchik_ZpolifF+1;

            int k=0;

            int ke=0;

            int iz=i-63;
            ke=(iz+1+n_Z-kmax)>>3; //для определения номера предыдушего  оптимальному отсчету
            k=(iz+n_Z-kmax)>>3;    //для определения номера оптимального отсчета
            //условие выбора отсчета предыдущего оптимальному//
            if((Sampl_inSimbol*ke==iz+1-kmax+n_Z)&&(schetchik_ZpolifF>=62)) //if(...+n_Z)
            {  en=true;//разрешаем работу полифазного фильтра
                if (accError>MAXerror )
                { nFIR=nFIR-1;
                    accError=accError-MAXerror;}

            }
            //окончание условия выбора отсчета предыдущего оптимальному//

            //условия выбора оптимального отсчета//
            if((Sampl_inSimbol*k==iz-kmax+n_Z)&&(schetchik_ZpolifF>=71))//if(...+n_Z)
            {
                accError=accError+derror;
                if ((nFIR==0)&&(accError>MAXerror))
                {opt_1=true;}
                en=false;//запрещаем  работу полифазного фильтра
                ////Демодулятор

                iq=out_polifaznik*conj(out_polifaznik_);

                iqD.real(iq.real());
                iqD.imag(iq.imag());

                w=arg(iqD);

                if(w<=-2.74889||w>2.74889){sampl=6;};
                if(w>-2.74889&&w<=-1.963){sampl=7;};
                if(w>-1.963&&w<=-1.1781){sampl=5;};
                if(w>-1.1781&&w<=-0.3927){sampl=4;};
                if(w>-0.3927&&w<=0.3927){sampl=0;};
                if(w>0.3927&&w<=1.17809){sampl=1;};
                if(w>1.17809&&w<=1.963){sampl=3;};
                if(w>1.963&&w<=2.74889){sampl=2;};
                ////////////////конец

                simbol.push_back(sampl);
                //  Условие несовпадения несовпадения лины пакета //
                if (paket!=noise)
                { int energeT=0;
                    for ( int kk=0;kk<L_uniqueWord;kk++)//определим текущую энергетику
                    {
                        int e_index=Z_index-m_index-(NtapT>>1)-kk*Sampl_inSimbol;
                        if (  e_index < 0) {e_index=e_index+N_tapM;};
                        energeT+= abs(MI[e_index])+abs(MQ[e_index]);
                    };
                    if (energeT<=(energeS>>1)) // длина пакета оказалась меньше ожидаемой
                    {
                        enableHeader=false;     //отменяем обработку пакета
                        simbol.clear(); //очистили вектор simbol
                        simbol_sizeOfData=1;sizeOfData=0;
                        maxThreshold=Threshold;//снизили уровень порога
                        flag = false;kmax=0;//пакета на входе нет
                        energeS=0;energeT=0;
                    }
                }
                //Определяем размер пакета
                switch (paket) {

                case mod2:
                    if(simbol.size()==9)
                    {
                        QBitArray  bits(27);
                        int block_codbit;

                        for (int index=0;index<9;index++)
                        {

                            block_codbit=simbol[index];
                            bitset <1> oct1(simbol[index]);
                            if(oct1.operator ==(true)){bits.setBit(3*index+2,true);};
                            if(oct1.operator ==(false)){bits.setBit(3*index+2,false);};
                            block_codbit>>=1;
                            bitset <1> oct2(block_codbit);
                            if(oct2.operator ==(true)){bits.setBit(3*index+1,true);};
                            if(oct2.operator ==(false)){bits.setBit(3*index+1,false);};

                            block_codbit>>=1;
                            bitset <1> oct3(block_codbit);
                            if(oct3.operator ==(true)){bits.setBit(3*index,true);};
                            if(oct3.operator ==(false)){bits.setBit(3*index,false);};

                        }bits.resize(HeaderSize2);
                        int bitTotal=HeaderSize2+ VDLTWO::GetTransmissionLength(VDLTWO::DecodeHeader(VDLTWO::Scramble(bits)));
                        if (bitTotal>131071) {

                            enableHeader=false;     //длина  пакета более максимально допустимой, отменяем обработку пакета
                            simbol.clear(); //очистили вектор simbol
                            simbol_sizeOfData=1;sizeOfData=0;
                            maxThreshold=Threshold;//снизили уровень порога
                            flag = false;kmax=0;//пакета на входе нет
                            energeS=0;
                        }
                        int simbolTotal=bitTotal/3;
                        int diff=bitTotal-(simbolTotal*3);
                        if (diff==0){sizeOfData=bitTotal;}
                        else  sizeOfData=bitTotal+(3-diff);

                        simbol_sizeOfData=sizeOfData/3;
                        enableHeader=false;
                        ///        cout<<"size "<<simbol_sizeOfData<<" simbolov" <<endl;
                    }
                    ;
                    break;
                case standart: //для определения messag ID
                    if (simbol.size()==8) {
                        QBitArray  bits(24);

                        int block_codbit;
                        for (int index=0;index<8;index++)
                        {
                            block_codbit=simbol[index];
                            bitset <1> oct1(simbol[index]);
                            if(oct1.operator ==(true)){bits.setBit(3*index+2,true);};
                            if(oct1.operator ==(false)){bits.setBit(3*index+2,false);};
                            block_codbit>>=1;
                            bitset <1> oct2(block_codbit);
                            if(oct2.operator ==(true)){bits.setBit(3*index+1,true);};
                            if(oct2.operator ==(false)){bits.setBit(3*index+1,false);};

                            block_codbit>>=1;
                            bitset <1> oct3(block_codbit);
                            if(oct3.operator ==(true)){bits.setBit(3*index,true);};
                            if(oct3.operator ==(false)){bits.setBit(3*index,false);};

                        } VDLTHREE G;
                        iDsizeBits= G.GoleyDecode(bits);
                    }
                    break;
                case id_air://  все конфигурации.Вычисление размера пакета.

                    if (simbol.size()==8) {//для определения размера пакета
                        QBitArray  bits(24);////для определения messag ID и направления передачи информации

                        int block_codbit;
                        for (int index=0;index<8;index++)
                        {

                            block_codbit=simbol[index];
                            bitset <1> oct1(simbol[index]);
                            if(oct1.operator ==(true)){bits.setBit(3*index+2,true);};
                            if(oct1.operator ==(false)){bits.setBit(3*index+2,false);};
                            block_codbit>>=1;
                            bitset <1> oct2(block_codbit);
                            if(oct2.operator ==(true)){bits.setBit(3*index+1,true);};
                            if(oct2.operator ==(false)){bits.setBit(3*index+1,false);};

                            block_codbit>>=1;
                            bitset <1> oct3(block_codbit);
                            if(oct3.operator ==(true)){bits.setBit(3*index,true);};
                            if(oct3.operator ==(false)){bits.setBit(3*index,false);};

                        } VDLTHREE G;
                        iDsizeBits= G.GoleyDecode(bits);
                        //////////////////////////////////////////////////////
                        if (iDsizeBits[0]==false) {
                            direct=up_link;
                        };
                        if (iDsizeBits[0]==true) {
                            direct=down_link;
                        };
                        if (direct==down_link) {// воздух-земля, подтверждение запроса
                            simbol_sizeOfData=16;sizeOfData=48;enableHeader=false;};

                        if ((iDsizeBits[0]==false)&&(iDsizeBits[1]==true)&&(iDsizeBits[2]==false)&&
                                (iDsizeBits[3]==true))//конфигурация-3T, земля-воздух, H-пакет
                        {   simbol_sizeOfData=40;sizeOfData=120;enableHeader=false;}

                    };

                    if (simbol.size()==16) {//для определения системной конфигурации
                        QBitArray  bits(24);

                        int block_codbit;
                        for (int index=0;index<8;index++)
                        {

                            block_codbit=simbol[index+8];
                            bitset <1> oct1(block_codbit);
                            if(oct1.operator ==(true)){bits.setBit(3*index+2,true);};
                            if(oct1.operator ==(false)){bits.setBit(3*index+2,false);};
                            block_codbit>>=1;
                            bitset <1> oct2(block_codbit);
                            if(oct2.operator ==(true)){bits.setBit(3*index+1,true);};
                            if(oct2.operator ==(false)){bits.setBit(3*index+1,false);};

                            block_codbit>>=1;
                            bitset <1> oct3(block_codbit);
                            if(oct3.operator ==(true)){bits.setBit(3*index,true);};
                            if(oct3.operator ==(false)){bits.setBit(3*index,false);};

                        } VDLTHREE G;
                        sistemConfigBits= G.GoleyDecode(bits);
                        switch (direct)
                        {
                        case up_link:
                            if ((sistemConfigBits[0]==false)&&(sistemConfigBits[1]==true)&&(sistemConfigBits[2]==false)&&(sistemConfigBits[3]==false)) {
                                system_config=Demand_assigned_voice_and_data;
                            }else system_config=Non_3T;
                            break;
                        case down_link:
                            break;
                        case undefined:
                            break;
                        };

                        if ((direct==up_link)&&(system_config==Non_3T)) {// конфигурация не-3T , земля-воздух
                            simbol_sizeOfData=32;sizeOfData=96;enableHeader=false;};
                        if ((direct==up_link)&&(system_config==Demand_assigned_voice_and_data)) {// конфигурация-3T , земля-воздух
                            simbol_sizeOfData=128;sizeOfData=384;enableHeader=false;};

                    };

                    break;
                case noise:
                    break;
                case net_request:
                    break;
                case voice:
                    break;
                }


                // если последний символ в кадре то заходим сюда //
                if ((simbol.size()==simbol_sizeOfData)&&(enableHeader==false))
                {
                    simboldata.push_back(simbol);//1 пакет данных сохранили
                    set_simbol_sizeOfData.push_back(simbol.size());//сохр число символов  в пакете
                    set_sizeOfData.push_back(3*simbol.size());// сохр число бит в пакете
                    set_paket.push_back(paket);
                    paket=noise;
                    totalsampl=kadrsampl+i;set_totalsampl.push_back(totalsampl);
                };

                ///*Задержка сброса порога обнаружителя/
                if ((simbol.size()==simbol_sizeOfData+11)&&(enableHeader==false))
                {int energeT=0;  simbol_sizeOfData=0;
                    for ( int kk=0;kk<L_uniqueWord;kk++)
                    {
                        int e_index=Z_index-m_index-kk*Sampl_inSimbol;
                        if (   e_index < 0) {e_index=e_index+N_tapM;};
                        energeT+= abs(MI[e_index])+abs(MQ[e_index]);
                    };//текущая энергетика сигнала
                    if (energeT>=(energeS>>1))//длина пакета  оказалась больше ожидаемой
                    {    simboldata.removeLast();//удаляем ложный  пакет
                        set_simbol_sizeOfData.removeLast();
                        set_sizeOfData.removeLast();
                        set_paket.removeLast();
                        set_totalsampl.removeLast();
                        energeS=0;

                        cout<<"mismatching of burst size (more)"<<endl;
                    };
                    simbol.clear(); //очистили вектор simbol
                    nFIR=0;//возвраили начальные условия задержек полифазного фильтра
                    maxThreshold=Threshold;//снизили уровень порога
                    kmax=0;//пакета на входе нет
                    energeS=0;schetchik_ZpolifF=0; flag = false;
                };


            };
            //окончание условия выбора оптимального отсчета//

            //условия выбора оптимального отсчета, соответствующего иаксимуму коррелляционной функции//
            if((Sampl_inSimbol*k==iz-kmax+n_Z)&&(schetchik_ZpolifF>=62))
            {
                if ( schetchik_ZpolifF<71) {   accError=accError+derror;};///////////////
                out_polifaznik_=out_polifaznik;

            }

            break;
        }//окончилось условие flag = true


        Z_index=Z_index+1;
        if (Z_index==N_tapM) { Z_index=0;};//индекс эл-т вхадного буфера
    }//окончание цикла обработки входных отсчетов ############################################

    kadrsampl=kadrsampl+Sampl_inKadr;

    ////// Упаковка принятых пакетор в QVector//////

    ArrayData.clear();

    for (int n_PACK=0;n_PACK<simboldata.size();n_PACK++)//кол-во пакетов  в кадре
    {
        //набираем первые  40 елементов битового массива data. время регистрации пакета//
        data.resize(40);
        data.fill(false);

        qint64 block_codbit;

        for (int tot=0;tot<40;tot++)
        {

            block_codbit= set_totalsampl[n_PACK]>>(tot);
            bitset <1> b(block_codbit);
            if(b.operator ==(false)){ data.setBit(39-tot,false);};
            if(b.operator ==(true))  {data.setBit(39-tot,true);};
        }
        //добавляем  тип пакета//
        data.resize(48);
        switch (set_paket[n_PACK]) {
        case mod2: //синхропоследовательность S
            for (int p = 40; p < 47; ++p) {
                data.setBit(p,false);        }
            data.setBit(47,true);
            break;
        case standart: //Синхропоследовательность S1
            //воздух-земля, запрос на бронирование
            if ((iDsizeBits[0]==true)&&(iDsizeBits[1]==false)&&(iDsizeBits[2]==false)&&(iDsizeBits[3]==false))
            {    for (int p = 40; p < 44; ++p)
                {     data.setBit(p,false); }
                data.setBit(44,true); data.setBit(45,false);   data.setBit(46,true);   data.setBit(47,false);
            }     // воздух-земля, подтверждение запроса
            if ((iDsizeBits[0]==true)&&(iDsizeBits[1]==false)&&(iDsizeBits[2]==false)&&(iDsizeBits[3]==true))
            {    for (int p = 40; p < 44; ++p)
                {     data.setBit(p,false); }
                data.setBit(44,true); data.setBit(45,false);   data.setBit(46,true);   data.setBit(47,true);
            }   // воздух-земля, сообщение выхода из сети
            if ((iDsizeBits[0]==true)&&(iDsizeBits[1]==false)&&(iDsizeBits[2]==true)&&(iDsizeBits[3]==false))
            {    for (int p = 40; p < 44; ++p)
                {     data.setBit(p,false); }
                data.setBit(44,true); data.setBit(45,true);   data.setBit(46,false);   data.setBit(47,false);
            }
            break;
        case net_request: //Синхропоследовательность S1*
            //   воздух-земля, сетевой запрос
            for (int p = 40; p < 44; ++p)
            {     data.setBit(p,false); }
            data.setBit(44,true); data.setBit(45,false);   data.setBit(46,false);   data.setBit(47,true);
            break;
        case voice:  //синхрослово S2
            // пакет данных или звука
            data.setBit(40,false); data.setBit(41,false); data.setBit(42,false);   data.setBit(43,true);
            data.setBit(44,false); data.setBit(45,false);   data.setBit(46,false);   data.setBit(47,true);
            break;
        case id_air://Синхропоследовательность S2*
            //земля-воздух Normal Messag
            if ((iDsizeBits[0]==false)&&(iDsizeBits[1]==false)&&(iDsizeBits[2]==false)&&(iDsizeBits[3]==false)&&(system_config==Non_3T))
            {    for (int p = 40; p < 46; ++p) {
                    data.setBit(p,false); }
                data.setBit(46,true);  data.setBit(47,false);
            }
            // земля-воздух, подтверждение сетевого запроса, (no previous link)
            if ((iDsizeBits[0]==false)&&(iDsizeBits[1]==false)&&(iDsizeBits[2]==false)&&(iDsizeBits[3]==true)&&(system_config==Non_3T))
            {     for (int p = 40; p < 46; ++p) {
                    data.setBit(p,false); }
                data.setBit(46,true);   data.setBit(47,true);
            }
            //земля-воздух, подтверждение сетевого запроса, (previous link preserved)
            if ((iDsizeBits[0]==false)&&(iDsizeBits[1]==false)&&(iDsizeBits[2]==true)&&(iDsizeBits[3]==false)&&(system_config==Non_3T))
            {    for (int p = 40; p < 45; ++p)
                {      data.setBit(p,false); }
                data.setBit(45,true);   data.setBit(46,false);   data.setBit(47,false);
            }
            // земля-воздух, сообщение  перехода в следующую сеть
            if ((iDsizeBits[0]==false)&&(iDsizeBits[1]==false)&&(iDsizeBits[2]==true)&&(iDsizeBits[3]==true)&&(system_config==Non_3T))
            {    for (int p = 40; p < 45; ++p)
                {      data.setBit(p,false);}
                data.setBit(45,true);   data.setBit(46,false);   data.setBit(47,true);
            }
            //  земля-воздух, сообщение возврата
            if ((iDsizeBits[0]==false)&&(iDsizeBits[1]==true)&&(iDsizeBits[2]==false)&&(iDsizeBits[3]==false)&&(system_config==Non_3T))
            {    for (int p = 40; p < 45; ++p)
                {     data.setBit(p,false); }
                data.setBit(45,true);   data.setBit(46,true);   data.setBit(47,false);
            }
            //  земля-воздух, 3T конфигурация
            if (system_config==Demand_assigned_voice_and_data)
            {    for (int p = 40; p < 45; ++p)
                {     data.setBit(p,false); }
                data.setBit(45,true);   data.setBit(46,true);   data.setBit(47,true);
            }
            //  сообщение проверки ,Н-пакет
            if ((iDsizeBits[0]==false)&&(iDsizeBits[1]==true)&&(iDsizeBits[2]==false)&&(iDsizeBits[3]==true)&&(system_config==Demand_assigned_voice_and_data))
            {    for (int p = 40; p < 44; ++p)
                {     data.setBit(p,false); }
                data.setBit(44,true); data.setBit(45,false);   data.setBit(46,false);   data.setBit(47,false);
            } // воздух-земля,  подтверждение запроса в 4-х слотовой конфигурации, нормальный режим
            if ((iDsizeBits[0]==true)&&(iDsizeBits[1]==false)&&(iDsizeBits[2]==false)&&(iDsizeBits[3]==false))
            {    for (int p = 40; p < 44; ++p)
                {     data.setBit(p,false); }
                data.setBit(44,true); data.setBit(45,true);   data.setBit(46,false);   data.setBit(47,true);
            }  // воздух-земля,  подтверждение запроса в 3-х слотовой конфигурации, удлиненный режим
            if ((iDsizeBits[0]==true)&&(iDsizeBits[1]==false)&&(iDsizeBits[2]==true)&&(iDsizeBits[3]==false))
            {    for (int p = 40; p < 44; ++p)
                {     data.setBit(p,false); }
                data.setBit(44,true); data.setBit(45,true);   data.setBit(46,true);   data.setBit(47,false);
            }  //воздух-земля,  подтверждение запроса в 3Т-конфигурации
            if ((iDsizeBits[0]==true)&&(iDsizeBits[1]==true)&&(iDsizeBits[2]==false)&&(iDsizeBits[3]==false))
            {   data.setBit(40,false); data.setBit(41,false); data.setBit(42,false);   data.setBit(43,false);
                data.setBit(44,true); data.setBit(45,true);   data.setBit(46,true);   data.setBit(47,true);
            }  // воздух-земля, подтверждение перехода  в следующую сеть
            if ((iDsizeBits[0]==true)&&(iDsizeBits[1]==true)&&(iDsizeBits[2]==true)&&(iDsizeBits[3]==true))
            {   data.setBit(40,false); data.setBit(41,false); data.setBit(42,false);   data.setBit(43,true);
                data.setBit(44,false); data.setBit(45,false);   data.setBit(46,false);   data.setBit(47,false);
            }
            break;
        case noise:
            break;
        }
        //добавляем сам пакет//
        data.resize(48+set_sizeOfData[n_PACK]);
        qint8 sampl_=0;
        for (int ind=0;ind<(set_simbol_sizeOfData[n_PACK]);ind++)
        {
            sampl_=simboldata[n_PACK][ind];

            bitset <3> oct(sampl_);

            for ( int i3=0;i3<3;i3++)
            { data[48+((ind)*3+i3)]=oct.operator [](2-i3);

            }
        }

        ArrayData.push_back(data);

    }

    return  ArrayData;
}


