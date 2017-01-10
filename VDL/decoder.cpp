#include "decoder.h"

Decoder::Decoder()
{
}
unsigned char Decoder::GetVersion(QBitArray bits)
{
    unsigned char rtv = 0;
    for(int i = 40; i <48; i++)
    {
        rtv = rtv<<1;
        if (bits.at(i))
            rtv^=1;
    }
    return rtv;
}

Output Decoder::Decode(QVector<QBitArray> data_vector)
{
    try
    {
        Output m_Out;
        unsigned char version;
        foreach (QBitArray bits, data_vector)
        {
            quint64 time = VDLTWO::GetTime(bits);
            m_Out.times.push_back(time);
            version = GetVersion(bits);
            switch(version)
            {
            case VDL2:
            {
                if(bits.size()<VDL2_MIN_PACKET_SIZE)
                {break;}
                m_Out.types.push_back(1);
                //получение бит для скремблинга (отбрасывание бит которые не скремблятся
                bits = VDLTWO::GetScrambledBits(bits);
                //получение 25 бит заголовка
                QBitArray header(25);
                for(int i = 0; i < header.size(); i++)
                {
                    if(bits.at(i))
                    {
                        header.setBit(i,true);
                    }
                }
                //скремблинг заголовка
                header = VDLTWO::Scramble(header);
                //декодирование заголовка
                header = VDLTWO::DecodeHeader(header);
                //int tr_len = VDLTWO::GetTransmissionLength(header);
                //дескремблинг
                bits = VDLTWO::Scramble(bits);
                //удаление 25 бит заголовка
                for(int i =0; i< bits.size()-25;i++)
                {
                    bits[i] = bits[i+25];
                }
                bits.resize(bits.size()-25);
                std::vector<unsigned char> data_bytes;
                //получение байт для дальнейшего перемежения

                data_bytes = BitOperations::BitsToBytes(bits,false);

                //интерливинг (перемежение)
                data_bytes = VDLTWO::Interleave(data_bytes);

                //получение блоков данный для Рида Соломона

                blocks = VDLTWO::GetBlocks(data_bytes);

                //Декодирование РидомСоломоном
                blocks = VDLTWO::RSDecodeBlocks(blocks);

                //объединение полученных блоков в единый массив данных
                data_bytes = VDLTWO::MergeBlocks(blocks);

                //перевод в биты для того чтобы вырезать служебные биты
                bits.resize(data_bytes.size()*8);
                bits = VDLTWO::FromBytes(data_bytes);

                QVector<QBitArray> bitBlocks;
                blocks.clear();
                //std::vector<std::vector<unsigned char> > frames;
                bitBlocks = VDLTWO::GetDataFrames(bits);
                //вырезать лишние биты
                foreach (QBitArray bitBlock, bitBlocks)
                {
                    bitBlock = VDLTWO::BitStuffingBack(bitBlock);
                    blocks.push_back(BitOperations::BitsToBytes(bitBlock,false));
                }

                for(uint i = 0; i < blocks.size(); i++)
                {
                    paket++;

                    QString msgBuffer;
                    msgBuffer.clear();
                    if(VDLTWO::IsCorrectFCS(blocks[i]))
                    {
                        //получение сообщения, адреса отправления и назначения для каждого фрейма
                        if(blocks[i].size()>2)
                        {
                            for(unsigned int j = 9; j< blocks[i].size()-2;j++)
                            {
                                msgBuffer.append(blocks[i][j]);
                            }
                            m_Out.messages.push_back(msgBuffer);
                            m_Out.lengths.push_back(msgBuffer.size()+6);
                            msgBuffer.clear();
                            m_Out.srcAdress.push_back(VDLTWO::GetSourceAdress(blocks[i]));
                            m_Out.dstAdress.push_back(VDLTWO::GetDestAdress(blocks[i]));
                        }
                        //вывод в файл или на экран

                    }
                }
                blocks.clear();
                //return m_Out;
            }
            case VDL3_S1:
            {
                break;

                //end of case VDL 3
            }
            case VDL3_S2:
            {
                if(bits.size()<96)
                {
                    break;
                }
                bits = VDLTWO::GetScrambledBits(bits);
                bits = VDLTWO::Scramble(bits);
                QBitArray header(24);

                for(int i = 0; i < 24; i++)
                {
                    header[i]= bits[i];
                }
                header = VDLTHREE::GoleyDecode(header);
                for(int i = 24; i< bits.size(); i++)
                {
                    bits[i-24] = bits[i];
                }
                bits.resize(576);
                std::vector<unsigned char> data_bytes;

                data_bytes = BitOperations::BitsToBytes(bits,true);

                data_bytes = VDLTHREE::RSDecodeBlocks(data_bytes);
                data_bytes.resize(data_bytes.size()-10);
                uint adress = 0;
                for(int i = 2; i >= 0; i--)
                {
                    for(int j = 0; j < 8; j++)
                    {
                        adress^=(data_bytes[i]>>j)&1;
                        adress = adress<<1;
                    }
                }
                adress = adress>>1;
                data_bytes.erase(data_bytes.begin(),data_bytes.begin()+6);
                unsigned int FCS = VDLTHREE::GetFCS(data_bytes);
                adress = adress^FCS;
                unsigned char LC_adress_type;
                LC_adress_type ^= data_bytes[3];
                unsigned char message_len = data_bytes[5];
                unsigned char type = 3;
                QString message;
                for(uint i = 0; i<data_bytes.size(); i++)
                {
                    message.append(data_bytes[i]);
                }
                int bytesWriten = 0;
                m_Out.outBytes.insert(0, message);//сообщение
                m_Out.outBytes.insert(0, adress);//адрес
                m_Out.outBytes.insert(0, adress>>8);//адрес
                m_Out.outBytes.insert(0, adress>>16);//адрес

                m_Out.outBytes.insert(bytesWriten,message_len);//длинна

                m_Out.outBytes.insert(bytesWriten,type);//тип

                m_Out.outBytes.insert(bytesWriten,time);//время
                m_Out.outBytes.insert(bytesWriten,time>>8);//время
                m_Out.outBytes.insert(bytesWriten,time>>16);//время
                m_Out.outBytes.insert(bytesWriten,time>>24);//время
                m_Out.outBytes.insert(bytesWriten,time>>32);//время


                break;

            }
            };//end of switch



        }///ВЫВОД
        return m_Out;
    }
    catch(QException e)
    {
        stdout<<e;
    }
}
