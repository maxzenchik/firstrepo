#include "demod.h"

using namespace std;

Demod::Demod()
{
    //уникальное слово VDL-2
    UniqueWordVDL2 = VDLTWO::InitUniqWord();

    //уникальное слово VDL-3, стандартная последовательность
    UniqueWordVDL3_S1 = VDLTHREE::InitTrainingSeqMDownlink();//уникальное слово VDL-3, стандартная последовательность

    //training sequence VDLmod3 идентификатор входящего сетевого запроса
    UniqueWordVDL3_S1c = VDLTHREE::InitTrainingSeqRequest();

    //training sequence VDLmod3 M  Uplink burst
    UniqueWordVDL3_S2 = VDLTHREE::InitTrainingSeqResponse();

    //training sequence VDLmod3 идентификатор ответа на запрос
    UniqueWordVDL3_S2c = VDLTHREE::InitTrainingSeqResponse();
}

void Demod::init()
{
    this->simbol_sizeOfData = 0;
    this->maxThreshold = 0;
    this->kmax = 0;
    this->energeS = 0;
    this->packetWriteEnable = false;

    for (int i = 0; i < Ntap_M; ++i)//обнуление массива
    {
        this->M[i] = 0;
    };
    for (int i = 0; i <Ntap_e; ++i)//обнуление массива
    {
        this->Energe[i] = 0;
    };

    direct = undefined;
    paket = noise;
    system_config = VDL_2;
}
inline std::complex<int> Demod::GetCorrFunc(std::complex<int> UniqueWord[])
{
    std::complex<int> sumK = 0;
    complex <int> RegistrCorr[L_uniqueWord];//регистр кореллятора
    for (int i = 0; i < L_uniqueWord; i++)
    {
        RegistrCorr[i]= UniqueWord[(L_uniqueWord-1)-i] * M[i*sampl_inSimbol+L_Z];
        int real =  RegistrCorr[i].real() >> 4;
        RegistrCorr[i].real(real);
        int imag =  RegistrCorr[i].imag() >> 4;
        RegistrCorr[i].imag(imag);

        sumK +=   RegistrCorr[i];
    }
    return sumK;
}
QVector<QBitArray> Demod::Difdem(qint16 *signalI,  qint16 *signalQ)
{


    int sampl_inKadr = 349760;//если это константа то должна быть const static   //32768;//16384;//65504;//349472;//131008;//65504;//65504;//32752;//16376;//m*2047;311144;
    QBitArray  iDsizeBits(12);
    QBitArray  sistemConfigBits(12);//битовое поле  системной конфигурации VDL3
    QBitArray  data;// 1 пакет
    QVector <QBitArray> ArrayData;//набор пакетов в битах, захваченных данным кадром

    static int Mmr[Ntap_T];//массив для блока выделения тактовой частоты
    static int Mmi[Ntap_T];//массив для блока выделения тактовой частоты

    qint64 energeI = 0;//характеризует энергию выбранных отсчетов
    qint64 energeQ = 0;//характеризует энергию выбранных отсчетов квадратурной составляющей

    int minim; //что означает эта переменная?



    static bool enableHeader = false;//для индикации о том что в данный момент ведется обработка заголовка пакета
    static int sizeOfData = 0; // значение размера пакета, в битах

    int overthresh = 0; // значение превышения уровня обнаружителя относительно порогового

    static qint64 kadrsampl = 0;//колличество обработанных кадров * колличество отсчетов  в кадре
    qint64 totalsampl = 0;//колличество обработанных отсчетов, начиная от запуска программы
    QVector <qint64> set_totalsampl;//набор номеров отсчетов соответствовавших времени обработки каждого пакета
    QVector <burst> set_paket;//набор VDL режимов работры


    const int HEADERSIZE = 25;//длина заголовка пакета VDL2
    int THRESHOLD = 10000000;//начальное значение порога для обнаружителя

    qint8 sampl; //текущее значение символа, в октальной нотации,




    QVector <int> set_sizeOfData ;//набор размеров  пакетов ... А выше sizeOfData это что?
    QVector <int> set_simbol_sizeOfData;//набор размеров  пакетов в символах ...
    QVector <QVector<qint8> > simboldata; //набор пакетов в символах, захваченных данным кадром
    // simboldata.clear();

    complex <int> iq;//значение символа  на выходе  дифдекодера
    complex <double> iqD;//значение символа  на выходе  дифдекодера типа double

    //для уникального слова S vdl-2



    complex <int> sumK_2;//значение сумматора кореллятора
    double sIQ2 = 0; //значение функции корелляции VDL-2
    static double sIQ2_ = 0; //предыдущее значение функции корелляции VDL-2
    static double sIQ2__ = 0; //значение функции корелляции VDL-2 двумя отсчетами ранее

    //для уникального слова S1 vdl-3 M-Dowmlink


    complex <int> sumK_S1; //значение сумматора кореллятора S1
    double sIQ3_1 = 0; //значение функции корелляции VDL-3 по синхропоследовательности S1
    static double sIQ3_1_ = 0;
    static double sIQ3_1__ = 0;//значение функции корелляции двумя отсчетами ранее



    complex <int> sumK_S1c;//значение сумматора кореллятора S1*
    double sIQ3_1c = 0;//значение функции корелляции VDL-3 по синхропоследовательности S1*
    static double sIQ3_1c_ = 0;//предыдущее  значение
    static double sIQ3_1c__ = 0;//значение функции корелляции  двумя отсчетами ранее



    complex <int> sumK_S2;
    double sIQ3_2 = 0;//значение функции корелляции VDL-3 по синхропоследовательности S2
    static double sIQ3_2_ = 0;//предыдущее значение функции корелляции
    static double sIQ3_2__ = 0;//значение функции корелляции  двумя отсчетами ранее



    complex <int> sumK_S2c;
    double sIQ3_2c = 0;//значение функции корелляции VDL-3 по синхропоследовательности S2*
    static double sIQ3_2c_ = 0;//предыдущее значение функции корелляции
    static double sIQ3_2c__ = 0;//значение функции корелляции двумя отсчетами ранее

    int korf = 0; //результирующее значение кореллятора
    static int korf_ = 0;//предыдущее результирующее значение кореллятора


    //основной цикл обработки входных отсчетов//

    for(int i = 0;i<sampl_inKadr;i++)
    {
        //перемещаем отсчеты по входному регистру
        for ( int k = (Ntap_M-1);k>0;k--) // лучше тогда написать вместо 269 M.size();
        {
            M[k] = M[k-1];
        };

        M[0].imag(signalQ[i]);
        M[0].real(signalI[i]);

        //Кореллятор VDL-2
        sumK_2 = GetCorrFunc(UniqueWordVDL2);
        sIQ2__ = sIQ2_;
        sIQ2_ = sIQ2;
        sIQ2  = ((int)(pow((sumK_2.real() >> 16),2))+(int)(pow((sumK_2.imag() >> 16),2))) >> 1;//значение корелляционной ф VDL-2

        //Кореллятор VDL-3 стандартный пакет
        sumK_S1  = GetCorrFunc(UniqueWordVDL3_S1);
        sIQ3_1__ = sIQ3_1_;
        sIQ3_1_ = sIQ3_1;
        sIQ3_1  = ((int)(pow((sumK_S1.real() >> 16),2))+(int)(pow((sumK_S1.imag() >> 16),2))) >> 1;

        //Кореллятор VDL-3 входящий сетев запрос
        sumK_S1c  = GetCorrFunc(UniqueWordVDL3_S1c);
        sIQ3_1c__ = sIQ3_1c_;
        sIQ3_1c_ = sIQ3_1c;
        sIQ3_1c  = ((int)(pow((sumK_S1c.real() >> 16),2))+(int)(pow((sumK_S1c.imag() >> 16),2))) >> 1;

        //Кореллятор VDL-3 звук/данные
        sumK_S2  = GetCorrFunc(UniqueWordVDL3_S2);
        sIQ3_2__ = sIQ3_2_;
        sIQ3_2_ = sIQ3_2;
        sIQ3_2  = ((int)(pow((sumK_S2.real() >> 16),2))+(int)(pow((sumK_S2.imag() >> 16),2))) >> 1;

        //Кореллятор VDL-3 исходящий сетев запрос
        sumK_S2c  = GetCorrFunc(UniqueWordVDL3_S2c);
        sIQ3_2c__ = sIQ3_2c_;
        sIQ3_2c_ = sIQ3_2c;
        sIQ3_2c  = ((int)(pow((sumK_S2c.real() >> 16),2))+(int)(pow((sumK_S2c.imag() >> 16),2))) >> 1;


        korf_ = korf;
        korf = max(sIQ2,max(sIQ3_1,max(sIQ3_1c,max(sIQ3_2,sIQ3_2c))));//определяем максимальное значение
        overthresh = korf-THRESHOLD;




        if ((overthresh>0)&&(korf_>maxThreshold))//превышен  порог обнаружения
        {
            maxThreshold = korf_;

            simbol.clear();
            if ((korf_ == sIQ2_)&&(sIQ2<sIQ2_))
            {
                paket = mod2; simbol_sizeOfData = 0;
                sizeOfData = 0;
                enableHeader = true;
                packetWriteEnable = true;//разрешаем запись пакета ... флаг чего? packetWriteEnable или как то так

                simbol.push_back(0);//символ zero

                if (sIQ2  >= sIQ2__) {//определим оптимальный отсчет
                    kmax = i-1;}
                if (sIQ2<sIQ2__) {//определим оптимальный отсчет
                    kmax = i-2;  }




                for ( int k = 0;k<L_uniqueWord;k++)//вычисляем ожидаемый уровень сигнала
                {     energeS+=   abs(M[k*sampl_inSimbol+L_Z+1]);};
            };

            if ((korf_  ==  sIQ3_1_)&&(sIQ3_1 < sIQ3_1_))
            {
                paket = standart;
                simbol_sizeOfData = 16;
                sizeOfData = 48;
                enableHeader = false; //понятно что за флаг
                packetWriteEnable = true;//непонятно что за флаг




                for (int k = 0;k < L_uniqueWord; k++)//вычисляем ожидаемый уровень сигнала
                {
                    energeS+=   abs(M[k*sampl_inSimbol+L_Z+1]);
                };
                if (sIQ3_1  >= sIQ3_1__)
                {
                    kmax = i-1;//определим оптимальный отсчет
                }
                if (sIQ3_1<sIQ3_1__)
                {
                    kmax = i-2;//определим оптимальный отсчет
                }
            };
            if ((korf_ == sIQ3_1c_)&&(sIQ3_1c<sIQ3_1c_))
            {
                paket = net_request;
                simbol_sizeOfData = 16;
                sizeOfData = 48;
                enableHeader = false;
                packetWriteEnable = true;//разрешаем запись пакета






                for ( int k = 0;k<L_uniqueWord;k++)//вычисляем ожидаемый уровень сигнала
                {
                    energeS+=   abs(M[k*sampl_inSimbol+L_Z+1]);
                };
                if (sIQ3_1c  >= sIQ3_1c__)
                {
                    kmax = i-1;//определим оптимальный отсчет
                }
                if (sIQ3_1c<sIQ3_1c__)
                {
                    kmax = i-2;//определим оптимальный отсчет
                }
            };
            if ((korf_ == sIQ3_2_)&&(sIQ3_2<sIQ3_2_))
            {
                paket = voice;
                simbol_sizeOfData = 200;
                sizeOfData = 600;
                enableHeader = false;
                packetWriteEnable = true;//разрешаем запись пакета


                for ( int k = 0;k<L_uniqueWord;k++)//вычисляем ожидаемый уровень сигнала
                {
                    energeS+=   abs(M[k*sampl_inSimbol+L_Z+1]);
                };
                if (sIQ3_2  >= sIQ3_2__)
                {
                    kmax = i-1;//определим оптимальный отсчет
                }
                if (sIQ3_2<sIQ3_2__)
                {
                    kmax = i-2;//определим оптимальный отсчет
                }
            };
            if ((korf_ == sIQ3_2c_)&&(sIQ3_2c<sIQ3_2c_))
            {
                paket = id_air;
                simbol_sizeOfData = 0;
                sizeOfData = 0;
                enableHeader = true;
                packetWriteEnable = true;//разрешаем запись пакета



                for ( int k = 0;k<L_uniqueWord;k++)//вычисляем ожидаемый уровень сигнала
                {
                    energeS+=   abs(M[k*sampl_inSimbol+L_Z+1]);
                };
                if (sIQ3_2c  >= sIQ3_2c__)
                {
                    kmax = i-1;//определим оптимальный отсчет
                }
                if (sIQ3_2c<sIQ3_2c__)
                {
                    kmax = i-2;//определим оптимальный отсчет
                }
            }
        };



        //Блок выделения тактовой частоты  сигнала//

        int Raznost = (M[0].real()-M[sampl_inSimbol].real());
        int  multiply = M[sampl_inSimbol>>1].real()*Raznost;


        for ( int k = (Ntap_T-1);k>0;k--)
        {
            Mmr[k] = Mmr[k-1];
        };
        Mmr[0] = multiply;

        for (int k = 0;k<(Ntap_T>>3);k++)
        {
            energeI +=   abs(Mmr[k*sampl_inSimbol]);
        } ;
        energeI = (energeI>>5); //целочисленное деление. Результатом такого деления будет целое число (Если делимое не кратно 32 то остаток теряется) Это может быть важно
        //////////////
        ///
        ///
        ///
        ///
        int RaznostQ = (M[0].imag()-M[sampl_inSimbol].imag());
        int  multiplyQ = M[sampl_inSimbol>>1].imag()*RaznostQ;

        for ( int k = (Ntap_T-1);k>0;k--)
        {
            Mmi[k] = Mmi[k-1];
        };
        Mmi[0] = multiplyQ;

        for (int k = 0;k<(Ntap_T>>3);k++)
        {
            energeQ +=   abs(Mmi[k*sampl_inSimbol]);
        };
        energeQ = (energeQ>>5);

        for (int e = (Ntap_e-1);e>0;e--)
        {
            Energe[e] = Energe[e-1];

        }
        Energe[0] = (energeI+energeQ)>>1;

        //конец блока выделения тактовой частоты


        switch (packetWriteEnable) {
        case true:


            int k = 0;


            k = (i-kmax)>>3;

            if(i == kmax+2)//сюда заходим  1 раз при обнаружении
            {
                minim = Energe[0];  int j = 0;//индекс минимального эл-та массива

                for (int n = 0;n<Ntap_e;n++)
                {
                    if(Energe[n]<minim)
                    {
                        minim = Energe[n];
                        j = n;
                    }
                }; // Kmax = Kmax-(jj-2);
                if (Energe[j-1] <= Energe[j+1])
                {
                    //  Kmax = i-jj-m+m*simbol.size();//для VDL-2
                };
                if (Energe[j-1]>Energe[j+1])
                {
                    // Kmax = i-jj-1-m+m*simbol.size();//для VDL-2
                };
            };
            if(sampl_inSimbol*k == i-kmax)//размер кадра должен быть кратен m
            {


                /*Демодулятор*/

                //////////////////демодулятор

                iq = M[L_Z]*conj(M[L_Z+sampl_inSimbol]);

                iqD.real(iq.real());
                iqD.imag(iq.imag());


                double faza = arg(iqD);//фаза на выходе диффдекодера

                if(faza <= -2.74889||faza>2.74889){sampl = 6;}
                if(faza>-2.74889&&faza <= -1.963){sampl = 7;}
                if(faza>-1.963&&faza <= -1.1781){sampl = 5;}
                if(faza>-1.1781&&faza <= -0.3927){sampl = 4;}
                if(faza>-0.3927&&faza <= 0.3927){sampl = 0;}
                if(faza>0.3927&&faza <= 1.17809){sampl = 1;}
                if(faza>1.17809&&faza <= 1.963){sampl = 3;}
                if(faza>1.963&&faza <= 2.74889){sampl = 2;}
                ////////////////
                /* конец демодулятора*/
                simbol.push_back(sampl);//добавляем в кадр очередной символ



                //если пакет VDL-2//

                if (paket!= noise)
                {
                    int energeT = 0;
                    for ( int k = 0;k<L_uniqueWord;k++)//определим текущую энергетику
                    { energeT+=   abs(M[k*sampl_inSimbol+L_Z]);};
                    if (energeT <= (energeS>>5)) // длина пакета оказалась меньше ожидаемой
                    {
                        enableHeader = false;     //отменяем обработку пакета
                        simbol.clear(); //очистили вектор simbol
                        simbol_sizeOfData = 1;
                        sizeOfData = 0;
                        maxThreshold = THRESHOLD;//снизили уровень порога
                        packetWriteEnable = false;
                        kmax = 0;
                        energeS = 0;
                        energeT = 0;//cout<<"mismatching of burst size "<<endl;
                    }
                }



                // если последний символ в кадре то заходим сюда //
                if ((simbol.size() == simbol_sizeOfData)&&(enableHeader == false))
                {


                    simboldata.push_back(simbol);//1 пакет данных сохранили
                    set_simbol_sizeOfData.push_back(simbol.size());//сохр число символов  в пакете
                    set_sizeOfData.push_back(3*simbol.size());// сохр число бит в пакете
                    set_paket.push_back(paket);
                    paket = noise;
                    totalsampl = kadrsampl+i;set_totalsampl.push_back(totalsampl);


                    ////////////////для отладки

                };
                //Определяем размер пакета
                switch (paket)
                {
                case noise:
                    break;
                case mod2:
                    if(simbol.size() == 9)
                    {

                        QBitArray  bits(27);
                        int block_codbit;

                        for (int index = 0;index<9;index++)
                        {

                            block_codbit = simbol[index];
                            bitset <1> oct1(simbol[index]);
                            if(oct1.operator  == (true)){bits.setBit(3*index+2,true);};
                            if(oct1.operator  == (false)){bits.setBit(3*index+2,false);};
                            block_codbit>>= 1;
                            bitset <1> oct2(block_codbit);
                            if(oct2.operator  == (true)){bits.setBit(3*index+1,true);};
                            if(oct2.operator  == (false)){bits.setBit(3*index+1,false);};

                            block_codbit>>= 1;
                            bitset <1> oct3(block_codbit);
                            if(oct3.operator  == (true)){bits.setBit(3*index,true);};
                            if(oct3.operator  == (false)){bits.setBit(3*index,false);};

                        }bits.resize(HEADERSIZE);
                        int bitTotal = HEADERSIZE+ VDLTWO::GetTransmissionLength(VDLTWO::DecodeHeader(VDLTWO::Scramble(bits)));
                        int simbolTotal = bitTotal/3;
                        int diff = bitTotal-(simbolTotal*3);
                        if (diff == 0){sizeOfData = bitTotal;}
                        else  sizeOfData = bitTotal+(3-diff);

                        simbol_sizeOfData = sizeOfData/3;
                        //   cout<<"dlina paketa =  "<<simbol_sizeOfData<<" simbolov"<<endl;

                        enableHeader = false;
                    }
                    ;
                    break;
                case standart: //S1 для определения messag ID
                    if (simbol.size() == 8) {
                        QBitArray  bits(24);

                        int block_codbit;
                        for (int index = 0;index<8;index++)
                        {

                            block_codbit = simbol[index];
                            bitset <1> oct1(simbol[index]);
                            if(oct1.operator  == (true)){bits.setBit(3*index+2,true);};
                            if(oct1.operator  == (false)){bits.setBit(3*index+2,false);};
                            block_codbit>>= 1;
                            bitset <1> oct2(block_codbit);
                            if(oct2.operator  == (true)){bits.setBit(3*index+1,true);};
                            if(oct2.operator  == (false)){bits.setBit(3*index+1,false);};

                            block_codbit>>= 1;
                            bitset <1> oct3(block_codbit);
                            if(oct3.operator  == (true)){bits.setBit(3*index,true);};
                            if(oct3.operator  == (false)){bits.setBit(3*index,false);};

                        } VDLTHREE G;
                        iDsizeBits =  G.GoleyDecode(bits);
                    }
                    break;
                case id_air://S2*  все конфигурации.Вычисление размера пакета.



                    if (simbol.size() == 8) {//для определения размера пакета
                        QBitArray  bits(24);////для определения messag ID и направления передачи информации

                        int block_codbit;
                        for (int index = 0;index<8;index++)
                        {

                            block_codbit = simbol[index];
                            bitset <1> oct1(simbol[index]);
                            if(oct1.operator  == (true)){bits.setBit(3*index+2,true);};
                            if(oct1.operator  == (false)){bits.setBit(3*index+2,false);};
                            block_codbit>>= 1;
                            bitset <1> oct2(block_codbit);
                            if(oct2.operator  == (true)){bits.setBit(3*index+1,true);};
                            if(oct2.operator  == (false)){bits.setBit(3*index+1,false);};

                            block_codbit>>= 1;
                            bitset <1> oct3(block_codbit);
                            if(oct3.operator  == (true)){bits.setBit(3*index,true);};
                            if(oct3.operator  == (false)){bits.setBit(3*index,false);};

                        } VDLTHREE G;
                        iDsizeBits =  G.GoleyDecode(bits);
                        //////////////////////////////////////////////////////
                        if (iDsizeBits[0] == false) {
                            direct = up_link;
                        };
                        if (iDsizeBits[0] == true) {
                            direct = down_link;
                        };
                        if (direct == down_link) {//S2* down-link
                            simbol_sizeOfData = 16;sizeOfData = 48;enableHeader = false;};

                        if ((iDsizeBits[0] == false)&&(iDsizeBits[1] == true)&&(iDsizeBits[2] == false)&&
                                (iDsizeBits[3] == true))//3T up-link H-пакет
                        {   simbol_sizeOfData = 40;sizeOfData = 120;enableHeader = false;}

                    };

                    if (simbol.size() == 16) {//для определения системной конфигурации
                        QBitArray  bits(24);

                        int block_codbit;
                        for (int index = 0;index<8;index++)
                        {

                            block_codbit = simbol[index+8];
                            bitset <1> oct1(block_codbit);
                            if(oct1.operator  == (true)){bits.setBit(3*index+2,true);};
                            if(oct1.operator  == (false)){bits.setBit(3*index+2,false);};
                            block_codbit>>= 1;
                            bitset <1> oct2(block_codbit);
                            if(oct2.operator  == (true)){bits.setBit(3*index+1,true);};
                            if(oct2.operator  == (false)){bits.setBit(3*index+1,false);};

                            block_codbit>>= 1;
                            bitset <1> oct3(block_codbit);
                            if(oct3.operator  == (true)){bits.setBit(3*index,true);};
                            if(oct3.operator  == (false)){bits.setBit(3*index,false);};

                        } VDLTHREE G;
                        sistemConfigBits =  G.GoleyDecode(bits);
                        switch (direct)
                        {
                        case up_link:
                            if ((sistemConfigBits[0] == false)&&(sistemConfigBits[1] == true)&&(sistemConfigBits[2] == false)&&(sistemConfigBits[3] == false)) {
                                system_config = Demand_assigned_voice_and_data;
                            }else system_config = Non_3T;
                            break;
                        case down_link:
                            break;
                        case undefined:
                            break;

                        };
                        //окончание условия switch direct  //
                        if ((direct == up_link)&&(system_config == Non_3T)) {// not-3T up-link
                            simbol_sizeOfData = 32;sizeOfData = 96;enableHeader = false;};
                        if ((direct == up_link)&&(system_config == Demand_assigned_voice_and_data)) {//3T up-link
                            simbol_sizeOfData = 128;sizeOfData = 384;enableHeader = false;};

                    };

                    break;
                case voice:
                    break;
                case net_request:
                    break;

                }//укончание условий определения размеров пакетов

            };//окончание условия совпадения текущего  отсчета с  оптимальным



            ///*Задержка сброса порога обнаружителя/
            if ((simbol.size() == simbol_sizeOfData+38)&&(enableHeader == false))
            {int energeT = 0;  simbol_sizeOfData = 0;
                for ( int k = 0;k<L_uniqueWord;k++)
                { energeT+=   abs(M[k*sampl_inSimbol+L_Z]);};//текущая энергетика сигнала
                if (energeT  >= (energeS>>2))//длина пакета  оказалась больше ожидаемой
                {    simboldata.removeLast();//удаляем ложный  пакет
                    set_simbol_sizeOfData.removeLast();
                    set_sizeOfData.removeLast();
                    set_paket.removeLast();
                    set_totalsampl.removeLast();


                    //  cout<<"mismatching of burst size "<<endl;
                };
                simbol.clear(); //очистили вектор simbol

                maxThreshold = THRESHOLD;//снизили уровень порога
                kmax = 0;
                energeS = 0;packetWriteEnable = false;
            };
            break;
        }//окончилось условие flag = true




    }//окончание цикла обработки входных отсчетов ############################################

    kadrsampl = kadrsampl+sampl_inKadr;



    /* Упаковка принятых пакетор в QVector*/

    ArrayData.clear();
    for (int n_PACK = 0;n_PACK<simboldata.size();n_PACK++)//кол-во пакетов  в кадре
    {
        /* набираем первые  40 елементов битового массива data. время регистрации пакета*/
        data.resize(L_preambulaTime);
       // data.fill(false);

        qint64 block_codbit;

        for (int t = 0;t<L_preambulaTime;t++)
        {

            block_codbit =  set_totalsampl[n_PACK]>>t;
            bitset <1> b(block_codbit);
            if(b.operator  == (false)){ data.setBit((L_preambulaTime-1)-t,false);};
            if(b.operator  == (true))  {data.setBit((L_preambulaTime-1)-t,true);};
        }
        /*набираем следующие 5 элементов массива data. добавляем  тип пакета*/
        data.resize(L_preambula);
        switch (set_paket[n_PACK]) {
        case noise:
            break;
        case mod2: //cсинхрослово S
            for (int p = L_preambulaTime; p <(L_preambula-1); ++p) {
                data.setBit(p,false); }
            data.setBit((L_preambula-1),true);
            break;
        case standart: //Синхропоследовательность S1
            //down-link, Reservation Request Message
            if ((iDsizeBits[0] == true)&&(iDsizeBits[1] == false)&&(iDsizeBits[2] == false)&&(iDsizeBits[3] == false))
            {    for (int p = L_preambulaTime; p < 44; ++p)
                {     data.setBit(p,false); }
                data.setBit(44,true); data.setBit(45,false);   data.setBit(46,true);   data.setBit(47,false);
            }     // down-link, Acknowledgement Message
            if ((iDsizeBits[0] == true)&&(iDsizeBits[1] == false)&&(iDsizeBits[2] == false)&&(iDsizeBits[3] == true))
            {    for (int p = L_preambulaTime; p < 44; ++p)
                {     data.setBit(p,false); }
                data.setBit(44,true); data.setBit(45,false);   data.setBit(46,true);   data.setBit(47,true);
            }   // down-link, Leaving Net Message
            if ((iDsizeBits[0] == true)&&(iDsizeBits[1] == false)&&(iDsizeBits[2] == true)&&(iDsizeBits[3] == false))
            {    for (int p = L_preambulaTime; p < 44; ++p)
                {     data.setBit(p,false); }
                data.setBit(44,true); data.setBit(45,true);   data.setBit(46,false);   data.setBit(47,false);
            }
            break;
        case net_request: //Синхропоследовательность S1*
            //  down-link, Net Entry Request Message
            for (int p = L_preambulaTime; p < 44; ++p)
            {     data.setBit(p,false); }
            data.setBit(44,true); data.setBit(45,false);   data.setBit(46,false);   data.setBit(47,true);

            break;
        case voice:  //синхрослово S2
            // V/D-пакет
            data.setBit(40,false); data.setBit(41,false); data.setBit(42,false);   data.setBit(43,true);
            data.setBit(44,false); data.setBit(45,false);   data.setBit(46,false);   data.setBit(47,true);

            break;
        case id_air://Синхропоследовательность S2*
            //up-link Normal Messag
            if ((iDsizeBits[0] == false)&&(iDsizeBits[1] == false)&&(iDsizeBits[2] == false)&&(iDsizeBits[3] == false)&&(system_config == Non_3T))
            {    for (int p = L_preambulaTime; p < 46; ++p) {
                    data.setBit(p,false); }
                data.setBit(46,true);  data.setBit(47,false);
            }
            // up-link  Net Entry Response Message (no previous link)
            if ((iDsizeBits[0] == false)&&(iDsizeBits[1] == false)&&(iDsizeBits[2] == false)&&(iDsizeBits[3] == true)&&(system_config == Non_3T))
            {     for (int p = L_preambulaTime; p < 46; ++p) {
                    data.setBit(p,false); }
                data.setBit(46,true);   data.setBit(47,true);
            }
            //up-link, Net Entry Response Message, (previous link preserved)
            if ((iDsizeBits[0] == false)&&(iDsizeBits[1] == false)&&(iDsizeBits[2] == true)&&(iDsizeBits[3] == false)&&(system_config == Non_3T))
            {    for (int p = L_preambulaTime; p < 45; ++p)
                {      data.setBit(p,false); }
                data.setBit(45,true);   data.setBit(46,false);   data.setBit(47,false);
            }
            // up-link, Next Net Command Message
            if ((iDsizeBits[0] == false)&&(iDsizeBits[1] == false)&&(iDsizeBits[2] == true)&&(iDsizeBits[3] == true)&&(system_config == Non_3T))
            {    for (int p = L_preambulaTime; p < 45; ++p)
                {      data.setBit(p,false);}
                data.setBit(45,true);   data.setBit(46,false);   data.setBit(47,true);
            }
            //  up-link, Recovery Message
            if ((iDsizeBits[0] == false)&&(iDsizeBits[1] == true)&&(iDsizeBits[2] == false)&&(iDsizeBits[3] == false)&&(system_config == Non_3T))
            {    for (int p = L_preambulaTime; p < 45; ++p)
                {     data.setBit(p,false); }
                data.setBit(45,true);   data.setBit(46,true);   data.setBit(47,false);
            }
            //  up-link, 3T  Configurations
            if (system_config == Demand_assigned_voice_and_data)
            {    for (int p = L_preambulaTime; p < 45; ++p)
                {     data.setBit(p,false); }
                data.setBit(45,true);   data.setBit(46,true);   data.setBit(47,true);
            }
            //  Handoff Check Message,
            if ((iDsizeBits[0] == false)&&(iDsizeBits[1] == true)&&(iDsizeBits[2] == false)&&(iDsizeBits[3] == true)&&(system_config == Demand_assigned_voice_and_data))
            {    for (int p = L_preambulaTime; p < 44; ++p)
                {     data.setBit(p,false); }
                data.setBit(44,true); data.setBit(45,false);   data.setBit(46,false);   data.setBit(47,false);
            } // down-link, 4-slot configuration Poll Response, normal range
            if ((iDsizeBits[0] == true)&&(iDsizeBits[1] == false)&&(iDsizeBits[2] == false)&&(iDsizeBits[3] == false))
            {    for (int p = L_preambulaTime; p < 44; ++p)
                {     data.setBit(p,false); }
                data.setBit(44,true); data.setBit(45,true);   data.setBit(46,false);   data.setBit(47,true);
            }  // down-link, 3-slot configuration Poll Response, long range
            if ((iDsizeBits[0] == true)&&(iDsizeBits[1] == false)&&(iDsizeBits[2] == true)&&(iDsizeBits[3] == false))
            {    for (int p = L_preambulaTime; p < 44; ++p)
                {     data.setBit(p,false); }
                data.setBit(44,true); data.setBit(45,true);   data.setBit(46,true);   data.setBit(47,false);
            }  //down-link, 3T configuration Poll Response
            if ((iDsizeBits[0] == true)&&(iDsizeBits[1] == true)&&(iDsizeBits[2] == false)&&(iDsizeBits[3] == false))
            {   data.setBit(40,false); data.setBit(41,false); data.setBit(42,false);   data.setBit(43,false);
                data.setBit(44,true); data.setBit(45,true);   data.setBit(46,true);   data.setBit(47,true);
            }  // down-link, Next Net ACK
            if ((iDsizeBits[0] == true)&&(iDsizeBits[1] == true)&&(iDsizeBits[2] == true)&&(iDsizeBits[3] == true))
            {   data.setBit(40,false); data.setBit(41,false); data.setBit(42,false);   data.setBit(43,true);
                data.setBit(44,false); data.setBit(45,false);   data.setBit(46,false);   data.setBit(47,false);
            }
            break;
        }

        // окончание условия switch (Spaket[n_PACK])


        /*добавляем сам пакет*/
        qint8 sampl_ = 0;
        data.resize(L_preambula+set_sizeOfData[n_PACK]);
        for (int index = 0;index<(set_simbol_sizeOfData[n_PACK]);index++)
        {
            sampl_ = simboldata[n_PACK][index];

            bitset <3> oct(sampl_);

            for ( int l = 0;l<3;l++)
            { data[L_preambula+((index)*3+l)] = oct.operator [](2-l);

            }
        }

        ArrayData.push_back(data);

    }


    return  ArrayData;
}
