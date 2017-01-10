#include "vdlthree.h"

VDLTHREE::VDLTHREE()
{
}
std::complex<int>* VDLTHREE::InitTrainingSeqMDownlink()
{
    std::complex<int>* S = new std::complex<int>[19];
    S[0].real(32767);
    S[0].imag(0);
    S[1].real(32767);
    S[1].imag(0);
    S[2].real(32767);
    S[2].imag(0);
    S[3].real(32767);
    S[3].imag(0);
    S[4].real(-23169);
    S[4].imag(23169);
    S[5].real(0);
    S[5].imag(32767);
    S[6].real(23169);
    S[6].imag(23169);
    S[7].real(0);
    S[7].imag(-32767);
    S[8].real(0);
    S[8].imag(32767);
    S[9].real(0);
    S[9].imag(32767);
    S[10].real(32767);
    S[10].imag(0);
    S[11].real(23169);
    S[11].imag(23169);
    S[12].real(-23169);
    S[12].imag(-23169);
    S[13].real(-23169);
    S[13].imag(23169);
    S[14].real(0);
    S[14].imag(-32767);
    S[15].real(-23169);
    S[15].imag(23169);
    S[16].real(-23169);
    S[16].imag(-23169);
    S[17].real(0);
    S[17].imag(-32767);
    S[18].real(32767);
    S[18].imag(0);
    return S;
}
std::complex<int>* VDLTHREE::InitTrainingSeqRequest()
{
    std::complex<int>* S = new std::complex<int>[19];
    S[0].real(32767);
    S[0].imag(0);
    S[1].real(32767);
    S[1].imag(0);
    S[2].real(32767);
    S[2].imag(0);
    S[3].real(32767);
    S[3].imag(0);
    S[4].real(23169);
    S[4].imag(-23169);
    S[5].real(0);
    S[5].imag(32767);
    S[6].real(-23169);
    S[6].imag(-23169);
    S[7].real(0);
    S[7].imag(-32767);
    S[8].real(0);
    S[8].imag(-32767);
    S[9].real(0);
    S[9].imag(32767);
    S[10].real(-32767);
    S[10].imag(0);
    S[11].real(23169);
    S[11].imag(23169);
    S[12].real(23169);
    S[12].imag(23169);
    S[13].real(-23169);
    S[13].imag(23169);
    S[14].real(0);
    S[14].imag(32767);
    S[15].real(-23169);
    S[15].imag(23169);
    S[16].real(23169);
    S[16].imag(23169);
    S[17].real(0);
    S[17].imag(-32767);
    S[18].real(-32767);
    S[18].imag(0);
    return S;
}
std::complex<int>* VDLTHREE::InitTrainingSeqUpLinkBurst()
{
    std::complex<int>* S = new std::complex<int>[19];
    S[0].real(32767);
    S[0].imag(0);
    S[1].real(32767);
    S[1].imag(0);
    S[2].real(32767);
    S[2].imag(0);
    S[3].real(32767);
    S[3].imag(0);
    S[4].real(-23169);
    S[4].imag(23169);
    S[5].real(23169);
    S[5].imag(23169);
    S[6].real(0);
    S[6].imag(-32767);
    S[7].real(0);
    S[7].imag(-32767);
    S[8].real(23169);
    S[8].imag(-23169);
    S[9].real(0);
    S[9].imag(-32767);
    S[10].real(-23169);
    S[10].imag(23169);
    S[11].real(-32767);
    S[11].imag(0);
    S[12].real(0);
    S[12].imag(-32767);
    S[13].real(-32767);
    S[13].imag(0);
    S[14].real(32767);
    S[14].imag(0);
    S[15].real(23169);
    S[15].imag(-23169);
    S[16].real(-23169);
    S[16].imag(23169);
    S[17].real(-23169);
    S[17].imag(-23169);
    S[18].real(32767);
    S[18].imag(0);

    return S;
}
std::complex<int>* VDLTHREE::InitTrainingSeqResponse()
{
    std::complex<int>* S = new std::complex<int>[19];
    S[0].real(32767);
    S[0].imag(0);
    S[1].real(32767);
    S[1].imag(0);
    S[2].real(32767);
    S[2].imag(0);
    S[3].real(32767);
    S[3].imag(0);
    S[4].real(23169);
    S[4].imag(-23169);
    S[5].real(23169);
    S[5].imag(23169);
    S[6].real(0);
    S[6].imag(32767);
    S[7].real(0);
    S[7].imag(-32767);
    S[8].real(-23169);
    S[8].imag(23169);
    S[9].real(0);
    S[9].imag(-32767);
    S[10].real(23169);
    S[10].imag(-23169);
    S[11].real(-32767);
    S[11].imag(0);
    S[12].real(0);
    S[12].imag(32767);
    S[13].real(-32767);
    S[13].imag(0);
    S[14].real(-32767);
    S[14].imag(0);
    S[15].real(23169);
    S[15].imag(-23169);
    S[16].real(23169);
    S[16].imag(-23169);
    S[17].real(-23169);
    S[17].imag(-23169);
    S[18].real(-32767);
    S[18].imag(0);

    return S;
}

int VDLTHREE::FromBitsToInt(QBitArray bits)
{
    int rtv;
    rtv = 0;
    for(int i = bits.size()-1; i >=0; i--)
    {
        if (bits.at(i))
        {
            rtv+= qPow(2,bits.size()-1-i);
        }
    }
    return rtv;
}
int weight(int vector)
{
    int i, aux;
    aux = 0;
    for (i=0; i<12; i++)
        if ( (vector>>i)&1 )
            aux++;
    return(aux);
}
QBitArray VDLTHREE::GoleyEncode(QBitArray data)
{
    QBitArray rtv(24);
    int iRtv = 0;
    int x[12] = {0xD71800,0x7C9400,0xE95200,0x63B100,0xE6C080,0xB36040,0x99B020,0x5BC010,0x2DE008,0x16F004,0xDC6002,0xAE3001};
    for(int i = 0; i < 24; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            iRtv ^= data[j]&(x[j]>>(23-i));

        }
        iRtv = iRtv<<1;
    }
    iRtv = iRtv>>1;
    for(int i = 0; i < 24; i++)
    {
        rtv.setBit(23-i,(iRtv>>i&1));
    }
    return rtv;
}

QBitArray VDLTHREE::GoleyDecode(QBitArray encoded_data)
{
    QBitArray rtv(12);
    QBitArray ba1(12);
    for(int i = 0; i < 12; i++)
    {
        if(encoded_data.at(i))
            ba1.setBit(i,true);
    }
    QBitArray ba2(12);
    for(int i = 12; i < 24; i++)
    {
        if(encoded_data.at(i))
            ba2.setBit(i-12,true);
    }
    //матрица с единицами в главной диагонали
    int x[12] = { 0x800,0x400,0x200,0x100,0x080,0x040,0x020,0x010,0x008,0x004,0x002,0x001 };
    //образующая или проверочная матрица
    int y[12] = { 0xD71,0x7C9,0xE95,0x63B,0xE6C,0xB36,0x99B,0x5BC,0x2DE,0x16F,0xDC6,0xAE3 };
    // z это транспонированная y
    int z[12] = { 0xAE3,0xF92,0x7C9,0xC76,0x63B,0xC8F,0x9D5,0xB78,0x5BC,0x2DE,0x16F,0xF25 };

    int c[2];          //кодовое слово (12 бит инфы + 12 бит проверки) (ЭТО ВАЖНО!)
    int r[2];          //кодовое слово (для симулятора)
    int e[2];          //ошибки (для симулятора)
    int c_hat[2];      //исправленное кодовое слово
    int s;             //синдром
    int q;             //измененный синдром

    int i,j;
    int aux, found;
    int weight(int vector);

    e[0] = 0;//0xFFF;
    e[1] = 0;//0xFFF;

    c[1] = BitOperations::BitsToInt(ba1,true);
    c[0] = BitOperations::BitsToInt(ba2,true);
    /*c[0] ^= 0x020;
    c[1] ^= 0x801;*/
    r[0] = c[0];
    r[1] = c[1];
    /******* STEP 1: Compute the syndrome of the received vector ********/
    s = 0;
    for (j=0; j<12; j++)
    {
        aux = 0;
        for (i=0; i<12; i++)
            aux = aux ^ ( (x[j]&r[0])>>i &0x01 ); /* identity part */
        for (i=0; i<12; i++)
            aux = aux ^ ( (y[j]&r[1])>>i &0x01 ); /* parity part */
        s = (s<<1)^aux;
    }

    /******* STEP 2 */
    if (weight(s)<=3)
    {
        e[0] = s;
        e[1] = 0;

    }
    else
    {
        /******* STEP 3 */
        i = 0;
        found = 0;
        do {
            if (weight(s^z[i]) <=2)
            {
                e[0] = s^z[i];
                e[1] = x[i];
                found = 1;

            }
            i++;
        } while ( (i<12) && (!found) );

        if (( i==12 ) && (!found))
        {
            /******* STEP 4 */
            q = 0;
            for (j=0; j<12; j++)
            {
                aux = 0;
                for (i=0; i<12; i++)
                    aux = aux ^ ( (z[j]&s)>>i & 0x01 );
                q = (q<<1) ^ aux;
            }
            /******* STEP 5 */
            if (weight(q) <=3)
            {
                e[0] = 0;
                e[1] = q;

            }
            else
            {
                /******* STEP 6 */
                i = 0;
                found = 0;
                do {
                    if (weight(q^y[i]) <=2)
                    {
                        e[0] = x[i];
                        e[1] = q^y[i];
                        found = 1;

                    }
                    i++;
                } while ( (i<12) && (!found) );

                if ((i==12) && (!found))
                {

                    /******* STEP 7 */
                    //incorrectable error pattern ggwp :(
                    /* You can raise a flag here, or output the vector as is */

                }
            }
        }
    }
    c_hat[0] = r[0]^e[0];
    c_hat[1] = r[1]^e[1];
    for(i = 0; i < 12; i++)
    {
        if(c_hat[0]&x[i])
        {
            rtv.setBit(i,true);
        }
    }
    return rtv;
}

bool VDLTHREE::IsCorrectFCS(std::vector<unsigned char> block)
{
    if(block.size()>=3)
    {
        boost::crc_optimal<24,0x864CFB,0xB704CE,0xFFFFFF,true,false> CCITT;
        unsigned char crc1;
        unsigned char crc2;
        unsigned char crc3;
        //crc1 = block[block.size()-2];
        //crc2 = block[block.size()-1];
        crc1= BitOperations::Invert(block[block.size()-3]);
        crc2= BitOperations::Invert(block[block.size()-2]);
        crc3= BitOperations::Invert(block[block.size()-1]);

        unsigned char* crc_data;
        int data_len = block.size()-2;
        crc_data = new unsigned char[data_len];
        for(int i = 0; i < data_len; i++)
        {
            crc_data[i] = block[i];
        }

        CCITT.process_bytes(crc_data,data_len);
        //сумма полученная в сообщении
        //unsigned short FCS_recieved = (short)((block[block.size()-1]<<8)|block[block.size()-2]);
        unsigned int FCS_recieved = (int)((crc1<<16)|((crc2<<8)|crc3));
        //сумма расчитанная CRC кодом
        unsigned int FCS_calculated = CCITT.checksum();

        if(FCS_recieved == FCS_calculated)
            return true;
        else
            return false;
    }
    else
        return false;
}
unsigned int VDLTHREE::GetFCS(std::vector<unsigned char> block)
{

    boost::crc_optimal<24,0x864CFB,0xB704CE,0xFFFFFF,true,false> CCITT;
    unsigned char* crc_data;
    int data_len = block.size();
    crc_data = new unsigned char[data_len];
    for(int i = 6; i < data_len; i++)
    {
        crc_data[i] = block[i];
    }
    CCITT.process_bytes(crc_data,data_len-6);



    return CCITT.checksum();

}
std::vector<unsigned char> VDLTHREE::RSDecodeBlocks(std::vector<unsigned char> data)
{
    int correct;
    std::vector<unsigned char> parity;
    for(int i = 62; i< 72; i++)
    {
        parity.push_back(data[i]);
    }
    ezpwd::reed_solomon<unsigned char,8,10,120,1,ezpwd::gfpoly<8,391>,int, int> rs;
    std::vector<int> position;
    std::vector<int> erasures;
    correct = rs.decode(data,erasures,&position);
    correct++;
    return data;
}

