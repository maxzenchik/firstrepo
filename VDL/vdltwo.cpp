
#include "vdltwo.h"


VDLTWO::VDLTWO()
{
}

std::complex<int>* VDLTWO::InitUniqWord()
{
    std::complex<int>* S = new std::complex<int>[19];
    //уникальное слово VDL-2
    //4 нуля+ cопряженная послед-ть к уник слову+ ноль

    S[0].real(32767);
    S[0].imag(0);
    S[1].real(32767);
    S[1].imag(0);
    S[2].real(32767);
    S[2].imag(0);
    S[3].real(-23169);
    S[3].imag(-23169);
    S[4].real(-23169);
    S[4].imag(23169);
    S[5].real(23169);
    S[5].imag(-23169);
    S[6].real(23169);
    S[6].imag(-23169);
    S[7].real(0);
    S[7].imag(-32767);
    S[8].real(32767);
    S[8].imag(0);
    S[9].real(-32767);
    S[9].imag(0);
    S[10].real(-23169);
    S[10].imag(23169);
    S[11].real(-32767);
    S[11].imag(0);
    S[12].real(0);
    S[12].imag(32767);
    S[13].real(-23169);
    S[13].imag(-23169);
    S[14].real(23169);
    S[14].imag(-23169);
    S[15].real(0);
    S[15].imag(32767);
    S[16].real(-23169);
    S[16].imag(23169);
    S[17].real(32767);
    S[17].imag(0);
    S[18].real(32767);
    S[18].imag(0);
    return S;
}
std::complex<int>* VDLTWO::InitTrSequence()
{
    std::complex<int>* S = new std::complex<int>[19];//уникальное слово VDL-2
    S[0].real(32767);
    S[0].imag(0);
    S[1].real(-23098);
    S[1].imag(-23240);
    S[2].real(-23311);
    S[2].imag(23026);
    S[3].real(23381);
    S[3].imag(-22955);
    S[4].real(23452);
    S[4].imag(-22883);
    S[5].real(503);
    S[5].imag(-32763);
    S[6].real(32761);
    S[6].imag(603);
    S[7].real(-32760);
    S[7].imag(-704);
    S[8].real(-23731);
    S[8].imag(22593);
    S[9].real(-32755);
    S[9].imag(-905);
    S[10].real(-1005);
    S[10].imag(32752);
    S[11].real(-22374);
    S[11].imag(-23938);
    S[12].real(24006);
    S[12].imag(-22305);
    S[13].real(-1307);
    S[13].imag(32741);
    S[14].real(-24143);
    S[14].imag(22153);
    S[15].real(32732);
    S[15].imag(1507);
    return S;
}
//###############################################################################################################
QBitArray VDLTWO::DecodeHeader(QBitArray bits)
{
    //проверочная матрица
    bool correcting_matrix[5][25] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,0,0,0,0},
        {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,0,1,0,0,0},
        {1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,0,0,1,0,0},
        {1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1,0,0,0,1,0},
        {0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1,0,0,0,0,1}
    };
    //массив синдромов (транспонированная проверочная матрица без блока проверки)
    bool sindroms[20][5] = {
        {0,0,1,1,0},
        {0,0,1,1,1},
        {0,1,0,0,1},
        {0,1,0,1,0},
        {0,1,0,1,1},
        {0,1,1,0,0},
        {0,1,1,1,0},
        {0,1,1,1,1},
        {1,0,0,0,1},
        {1,0,0,1,1},
        {1,0,1,0,1},
        {1,0,1,1,0},
        {1,1,0,0,0},
        {1,1,0,0,1},
        {1,1,0,1,0},
        {1,1,0,1,1},
        {1,1,1,0,0},
        {1,1,1,0,1},
        {1,1,1,1,0},
        {1,1,1,1,1}
    };
    bool syndrom[5];                //синдром полученный в результате декодирования (без ошибок будет 0 0 0 0 0)
    bool tmp;
    bool tmp_arr[25];
    try
    {
        for(int j = 0; j<5; j++)        //проход по столбцам проверочной матрицы
        {
            tmp = 0;
            for(int i = 0; i < 25; i++) //проход по строкам
            {
                tmp_arr[i] = bits[i]&correcting_matrix[j][i];       //побитовое "И" исходной последовательности и строки матрицы

            }
            for(int i = 0; i<25; i++)
            {
                tmp = tmp ^ tmp_arr[i];                             //XOR полученных бит в результате побитового "И"
            }
            syndrom[j] = tmp;

        }
        bool fail;                                          //индикатор ошибки
        for(int i =0; i < 20;i++)                           //проход по каждому синдрому
        {
            fail = true;                                    //индикатор ошибки устанавливается. предположение что ошибка есть
            for(int j = 0; j < 5; j++)
            {
                if(syndrom[j]!=sindroms[i][j])
                {
                    fail = false;                               //если один из элементов синдрома не совпадает то ошибки нет в i-ом бите
                }                                           //индикатор сбрасывается
            }
            if(fail)
            {                                                //если индикатор не сбросился - ощибка в i-м бите
                bits[i] = bits[i]^1;                         //XOR с единицей исправляет ее
            }
        }
        return bits;
    }
    catch(QException e)
    {
        stdout<<e;
    }
}
//###############################################################################################################
int VDLTWO::GetTransmissionLength(QBitArray bits)
{
    //записать 25 бит заголовка FEC начиная с 49-го бита
    //декодировать заголовок
    try
    {
        QBitArray Tr_length(17);
        //записать с 4-го по 20-й бит (первые 3 бита зарезервированны 000)
        for(int i = 3; i< 20; i++)
        {
            Tr_length[i-3] = bits[i];
        }
        int tr_ln = BitOperations::BitsToInt(Tr_length,false);

        if(tr_ln%8 !=0)
        {
            tr_ln+= 8-tr_ln%8;
        }
        int last_block_len = (tr_ln%1992)/8;
        int last_rs_len;
        {
            if(last_block_len < 3)
            {
                last_rs_len = 0;
            }
        }
        {
            if(last_block_len >= 3 && last_block_len < 31)
            {
                last_rs_len = 2;
            }
        }
        {
            if(last_block_len >= 31 && last_block_len < 68)
            {
                last_rs_len = 4;
            }
        }
        {
            if(last_block_len >= 68)
            {
                last_rs_len = 6;
            }
        }
        int RS = (tr_ln/1992)*6 + last_rs_len;

        return tr_ln + RS*8;
    }
    catch(QException e)
    {
        stdout<<e;
    }
}
//###############################################################################################################
QBitArray VDLTWO::GetData(QBitArray bits)
{

    QBitArray data(4032);
    for(int i = 73; i < 4105; i++ )
    {
        data[i-73] = bits[i];
    }
    return data;
}
//###############################################################################################################
QBitArray VDLTWO::GetRSFEC(QBitArray bits)
{
    QBitArray RSFEC(112);
    
    for(int i = 4105; i< 4217; i++)
    {
        RSFEC[i-4105] = bits[i];
    }
    return RSFEC;
}
//###############################################################################################################
quint64 VDLTWO::GetTime(QBitArray databits)
{
    try
    {
        quint64 rtv = 0;
        for(int i = 0; i <40; i++)
        {
            rtv = rtv<<1;
            if (databits.at(i))
                rtv^=1;
        }
        return rtv;
    }
    catch(QException e)
    {
        stdout<<e;
    }
}
//###############################################################################################################
QBitArray VDLTWO::GetScrambledBits(QBitArray databits)
{
    try
    {
        QBitArray scrambled_bits(databits.size()-48);

        for(int i = 48; i < databits.size(); i++)
        {
            scrambled_bits[i-48] = databits[i];
        }
        return scrambled_bits;
    }
    catch(QException e)
    {
        stdout<<e;
    }
}
//###############################################################################################################
QBitArray VDLTWO::Scramble(QBitArray bits)
{
    try
    {
        bool scram_bit;                                     //бит, который XORится с входным битом
        int shift_reg = 26969;                              //изначальное состояние регистра сдвига
        bool shift_reg_array[15];                           //регистр сдвига
        //////////////////////////////////////////////
        //инициализация начального состояния регистра сдвига
        for(int j =0; j<15; j++)
        {
            shift_reg_array[14-j]= shift_reg%2;
            shift_reg = shift_reg>>1;
        }
        ///////////////////////////////////////////////
        //SCRAMBLING BEGIN
        for(int i = 0; i < bits.size(); i++)                //проход по всему входному потоку
        {
            //полученние бита для скремблинга
            scram_bit = shift_reg_array[0]^shift_reg_array[14];            //1й и последний элемент регистра XOR
            bits[i] = bits[i]^scram_bit;
            //XOR данных и скрембл бита
            //сдвиг регистра
            for(int j = 15; j>0; j--)
            {
                shift_reg_array[j] = shift_reg_array[j-1];
            }
            shift_reg_array[0] = scram_bit;                 //нулевым элементом становится бит скремблинга
        }
        //SCRAMBLING END
        /////////////////////////////////////////////////
        return bits;
    }
}
//###############################################################################################################
std::vector<unsigned char> VDLTWO::Interleave(std::vector<unsigned char> data_bytes)
{
    try
    {
        int tr_len = data_bytes.size()*8;
        unsigned char block_count = data_bytes.size()/255 +1;
        std::vector<std::vector<unsigned char>> blocks;
        for(int i =0; i < block_count; i++)
        {
            std::vector<unsigned char> buff;
            blocks.push_back(buff);
        }
        int buff_count = tr_len/1992 +1;
        int lastbuff_len = data_bytes.size() - (255*(buff_count-1)); //количество виртуальных октетет в последнем блоке
        int lastblock_len = 0;
        int last_RS_len;
        int virtual_octet_count;
        //вычисление длинны последнего блока
        if(lastbuff_len <3)                             //если длинна меньше 3 то RS байт нет
        {
            lastblock_len = lastbuff_len;
            last_RS_len =0;
        }
        if(lastbuff_len >=3 && lastbuff_len<33)         //если от 3 до 32 то 2 RS байта
        {
            lastblock_len = lastbuff_len-2;
            last_RS_len = 2;
        }
        if(lastbuff_len >= 33 && lastbuff_len < 72)     //если от 33 до 71 то 4 RS байта
        {
            lastblock_len = lastbuff_len-4;
            last_RS_len = 4;
        }
        if(lastbuff_len >= 72)                          //если от 71, то 6 RS байт
        {
            lastblock_len = lastbuff_len-6;
            last_RS_len = 6;
        }
        virtual_octet_count = 249 - lastblock_len;
        //заполнение первых РЕАЛЬНЫХ октет в блоках (кол-во блоков buff_count)
        for(int i = 0; i < lastblock_len*buff_count; i++)
        {
            for(unsigned int j = 0; j<blocks.size(); j++)
            {
                blocks[j].push_back(data_bytes[i++]);
            }
            i--;
        }
        //последний буффер заполнен, остались остальные
        //
        //ДО количества виртуальных октет умноженное на количество буфферов -1

        for(int i = lastblock_len*buff_count; i< virtual_octet_count*(buff_count-1) + lastblock_len*buff_count;  i++)
        {
            for(unsigned int j = 0; j<blocks.size()-1; j++)
            {
                blocks[j].push_back(data_bytes[i++]);
            }
            i--;

        }
        //RS октеты (количество = количество буфферов*количество РС октет) О БОЖЕ! ПОНЯТЬ БЫ ЭТО ЧЕРЕЗ МЕСЯЦ
        for(
            int i = virtual_octet_count*(buff_count-1) + lastblock_len*buff_count;                          //от
            i < virtual_octet_count*(buff_count-1) + lastblock_len*buff_count + last_RS_len*buff_count;     //до
            i++
            )
        {
            for(unsigned int j = 0; j<blocks.size(); j++)
            {
                blocks[j].push_back(data_bytes[i++]);
            }
            i--;

        }
        for(
            unsigned int i = virtual_octet_count*(buff_count-1) + lastblock_len*buff_count + last_RS_len*buff_count;  //от
            i< data_bytes.size();                                                                            //до конца
            i++
            )
        {
            for(unsigned int j = 0; j<blocks.size()-1; j++)
            {
                blocks[j].push_back(data_bytes[i++]);
            }
            i--;

        }
        //пихаем в итоговый поток буффера по очереди
        std::vector<unsigned char> rtv;
        for(unsigned int i = 0; i < blocks.size(); i++)
        {
            for(unsigned int j = 0; j < blocks[i].size();j++)
            {
                rtv.push_back(blocks[i][j]);
            }
        }

        return rtv;
    }
    catch(QException e)
    {
        stdout<<e;
    }
}
//###############################################################################################################
std::vector<std::vector <unsigned char> > VDLTWO::GetBlocks(std::vector<unsigned char> data_bytes)
{
    try
    {
        int block_count = 0;
        std::vector<std::vector<unsigned char>> rtv;
        std::vector<unsigned char> buffer;
        if(data_bytes.size()%255 !=0){
            block_count = data_bytes.size()/255 +1;
        }
        else
        {
            block_count = data_bytes.size()/255;
        }
        //проход по входному массиву, заполнение блоков
        for(int k = 0; k < block_count-1; k++)
        {
            for(int i = 0; i< 255; i++)
            {
                buffer.push_back(data_bytes[i+255*k]);
            }
            rtv.push_back(buffer);
            buffer.clear();
        }
        int last_block_len = data_bytes.size() - (block_count-1)*255;
        for(int i = 0; i< last_block_len; i++)
        {
            buffer.push_back(data_bytes[i+255*(block_count-1)]);
        }

        std::vector<unsigned char> rs_buffer;

        if(last_block_len <3)                             //если длинна меньше 3 то RS байт нет
        {
            for(int i = last_block_len; i < 255; i++)
            {
                buffer.push_back(0);
            }
        }
        if(last_block_len >=3 && last_block_len<33)         //если от 3 до 32 то 2 RS байта
        {
            for(int i = last_block_len; i < 255; i++)
            {
                buffer.push_back(0);
            }
            buffer.at(249) = buffer.at(last_block_len - 2);
            buffer.at(last_block_len - 2) = 0;
            buffer.at(250) = buffer.at(last_block_len - 1);
            buffer.at(last_block_len - 1) = 0;
        }
        if(last_block_len >= 33 && last_block_len < 72)     //если от 33 до 71 то 4 RS байта
        {
            for(int i = last_block_len; i < 255; i++)
            {
                buffer.push_back(0);
            }

            buffer.at(249) = buffer.at(last_block_len - 4);
            buffer.at(last_block_len - 4) = 0;
            buffer.at(250) = buffer.at(last_block_len - 3);
            buffer.at(last_block_len - 3) = 0;
            buffer.at(251) = buffer.at(last_block_len - 2);
            buffer.at(last_block_len - 2) = 0;
            buffer.at(252) = buffer.at(last_block_len - 1);
            buffer.at(last_block_len - 1) = 0;
        }
        if(last_block_len >= 72)                          //если от 71, то 6 RS байт
        {
            for(int i = last_block_len; i < 255; i++)
            {
                buffer.push_back(0);
            }

            buffer.at(249) = buffer.at(last_block_len - 6);
            buffer.at(last_block_len - 6) = 0;
            buffer.at(250) = buffer.at(last_block_len - 5);
            buffer.at(last_block_len - 5) = 0;
            buffer.at(251) = buffer.at(last_block_len - 4);
            buffer.at(last_block_len - 4) = 0;
            buffer.at(252) = buffer.at(last_block_len - 3);
            buffer.at(last_block_len - 3) = 0;
            buffer.at(253) = buffer.at(last_block_len - 2);
            buffer.at(last_block_len - 2) = 0;
            buffer.at(254) = buffer.at(last_block_len - 1);
            buffer.at(last_block_len - 1) = 0;
        }

        rtv.push_back(buffer);
        buffer.clear();

        return rtv;
    }
    catch(QException e)
    {
        stdout<<e;
    }
}
//###############################################################################################################
std::vector<unsigned char> VDLTWO::MergeBlocks(std::vector<std::vector<unsigned char> > blocks)
{
    try
    {
        std::vector<unsigned char> rtv;
        for (unsigned int i = 0; i < blocks.size(); i++)
        {
            blocks.at(i).resize(249);
        }
        unsigned char count = 0;
        for(unsigned int i = 0; i < blocks.size(); i++)
        {
            for(unsigned int j = 0; j < 249; j++)
                rtv.push_back(blocks[i][j]);
        }
        for(unsigned int i = 0; i < rtv.size(); i++)
        {
            if (rtv[i] == 0)
                count++;
        }
        rtv.resize(rtv.size()-count);
        ///

        return rtv;
    }
    catch(QException e)
    {
        stdout<<e;
    }
}
//###############################################################################################################
QBitArray VDLTWO::FromBytes(std::vector<unsigned char> data_bytes)
{
    try
    {
        QBitArray rtv(data_bytes.size()*8);
        for(uint i = 0; i < data_bytes.size(); i++)
        {
            for(int j = 0; j < 8; j++)
            {
                rtv.setBit(i*8+j,(data_bytes[i]>>j)&1);
            }
        }
        return rtv;
    } catch(QException e)
    {
        stdout<<e;
    }
}
//###############################################################################################################
QBitArray VDLTWO::FromBytesRMB(std::vector<unsigned char> data_bytes)
{
    try
    {
        QBitArray rtv(data_bytes.size()*8);
        QBitArray buffer(8);

        for(unsigned int i = 0; i<data_bytes.size(); i++)    //проход по каждому байту
        {
            buffer = BitOperations::ByteToBits(data_bytes[i],false);
            for(int j = 0; j<buffer.size(); j++)//проход по биту
            {
                if(buffer[j])
                {
                    rtv.setBit(i*8+j);
                }
            }

        }
        return rtv;
    } catch(QException e)
    {
        stdout<<e;
    }
}
//###############################################################################################################
QBitArray VDLTWO::BitStuffingBack(QBitArray stuffed_data)
{
    try
    {
        short sequense_of_ones = 0;
        short stuffed_bits = 0;
        QBitArray Unstuffed_data(stuffed_data.size());
        for(int i =0; i < stuffed_data.size(); i++)
        {
            if(sequense_of_ones == 5 && stuffed_data[i]!=1)
            {
                stuffed_bits++;
            }
            else
            {
                Unstuffed_data.setBit(i-stuffed_bits,stuffed_data[i]);
            }
            if(stuffed_data.at(i)==1)
            {
                sequense_of_ones++;
            }
            else
            {
                sequense_of_ones =0;
            }
        }
        Unstuffed_data.resize(Unstuffed_data.size()-stuffed_bits);
        return Unstuffed_data;
    } catch(QException e)
    {
        stdout<<e;
    }
}
//###############################################################################################################
QVector<QBitArray> VDLTWO::GetDataFrames(QBitArray data)
{
    try
    {
        QVector<QBitArray> rtv;
        QVector<bool> buffer;
        int i =0;
        int j =0;
        unsigned char flag = 0;
        for(i = 0; i < data.size(); i++)
        {
            flag = flag<<1;
            if(data.at(i))
            {
                flag = flag^1;
            }
            //flag^data.at(i);

            buffer.push_back(data[i]);
            if(flag == 126||i == data.size())
            {
                QBitArray block(buffer.size());
                for(j =0; j< buffer.size();++j)
                {
                    block.setBit(j,buffer[j]);
                }
                block.resize(block.size()-8);
                if(block.size()>0)
                {
                    rtv.append(block);
                }
                buffer.clear();
            }
        }

        return rtv;
    }
    catch(QException e)
    {
        stdout<<e;
    }
}
//###############################################################################################################
int VDLTWO::GetSourceAdress(std::vector<unsigned char> data)
{
    try
    {
        QString dst_adress;
        std::vector<unsigned char> buffer;
        QBitArray dst_bits(32);
        QBitArray dst_adress_24bit(24);
        QBitArray adress_type(3);
        // bool air_ground = true;
        for(int i = 7; i>= 4; i--)
        {
            buffer.push_back(data[i]);
        }
        dst_bits = FromBytesRMB(buffer);

        for(int i = 0; i < dst_bits.size(); i++)
        {
            if(i < 7)
            {
                dst_adress_24bit[i] = dst_bits[i];
            }
            if(i>7&&i<15)
            {
                dst_adress_24bit[i-1] = dst_bits[i];
            }
            if(i > 15 && i < 23)
            {
                dst_adress_24bit[i-2] = dst_bits[i];
            }
            if(i > 23 && i < 27)
            {
                dst_adress_24bit[i-3] = dst_bits[i];
            }
            if(i > 26 && i < 30)
            {
                adress_type[i-27] = dst_bits[i];
            }
            /*if(i==30)
        {
            air_ground = dst_bits[i];
        }*/
        }

        int A = BitOperations::BitsToInt(dst_adress_24bit,false);
        dst_adress.append(QString::number(A,16).toUpper());

        /*dst_adress.append("   ");
    for(int i = 0; i < 3; i++)
    {
        if(adress_type[i]== true)
        {dst_adress.append("1");}
        else
        {dst_adress.append("0");}
    }
    dst_adress.append("   ");
    if(air_ground == false)
    {dst_adress.append("Command frame");}
    else
    {dst_adress.append("Response frame");}*/
        return A;
    }
    catch(QException e)
    {
        stdout<<e;
    }
}
//###############################################################################################################
int VDLTWO::GetDestAdress(std::vector<unsigned char> data)
{
    try
    {
        QString dst_adress;
        std::vector<unsigned char> buffer;
        QBitArray dst_bits(32);
        QBitArray dst_adress_24bit(24);
        QBitArray adress_type(3);
        //bool air_ground = true;
        for(int i = 3; i>= 0; i--)
        {
            buffer.push_back(data[i]);
        }
        dst_bits = FromBytesRMB(buffer);
        for(int i = 0; i < dst_bits.size(); i++)
        {
            if(i < 7)
            {
                dst_adress_24bit[i] = dst_bits[i];
            }
            if(i>7&&i<15)
            {
                dst_adress_24bit[i-1] = dst_bits[i];
            }
            if(i > 15 && i < 23)
            {
                dst_adress_24bit[i-2] = dst_bits[i];
            }
            if(i > 23 && i < 27)
            {
                dst_adress_24bit[i-3] = dst_bits[i];
            }
            if(i > 26 && i < 30)
            {
                adress_type[i-27] = dst_bits[i];
            }
            /*if(i==30)
        {
            air_ground = dst_bits[i];
        }*/
        }
        int A = BitOperations::BitsToInt(dst_adress_24bit,false);

        dst_adress.append(QString::number(A,16).toUpper());


        return A;
    }
    catch(QException e)
    {
        stdout<<e;
    }
}
//###############################################################################################################
std::vector<std::vector<unsigned char> > VDLTWO::RSDecodeBlocks(std::vector<std::vector<unsigned char> > blocks)
{
    try
    {
        std::vector<int> correct;
        ezpwd::reed_solomon<unsigned char,8,6,120,1,ezpwd::gfpoly<8,391>,int, int> rs;
        std::vector<int> position;
        std::vector<int> erasures;
        for(unsigned int i = 0; i < blocks.size(); i++)
        {
            for(unsigned int j = 249; j < 255; j++)
            {
                if(blocks[i][j]==0)
                    erasures.push_back(j);
            }
            correct.push_back(rs.decode(blocks[i],erasures,&position));
            erasures.clear();
        }
        return blocks;
    } catch(QException e)
    {
        stdout<<e;
    }
}
//###############################################################################################################
bool VDLTWO::IsCorrectFCS(std::vector<unsigned char> block)
{
    try
    {
        if(block.size()>=2)
        {
            boost::crc_optimal<16,0x1021,0xFFFF,0xFFFF,true,false> CCITT;

            unsigned char crc1= BitOperations::Invert(block[block.size()-2]);
            unsigned char crc2= BitOperations::Invert(block[block.size()-1]);

            unsigned char* crc_data;
            int data_len = block.size()-2;
            crc_data = new unsigned char[data_len];
            for(int i = 0; i < data_len; i++)
            {
                crc_data[i] = block[i];
            }
            CCITT.process_bytes(crc_data,data_len);

            unsigned short FCS_recieved = (short)((crc1<<8)|crc2);

            unsigned short FCS_calculated = CCITT.checksum();

            if(FCS_recieved == FCS_calculated)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    catch(QException e)
    {
        stdout<<e;
    }
}
