#include "bitoperations.h"

BitOperations::BitOperations()
{
}
unsigned char BitOperations::Invert(unsigned char x)
{
    int base = 256;
    unsigned char rtv = 0;
    while (x!=0)
    {
        rtv += (x & 1)*(base >>= 1);
        x >>= 1;
    }
    return rtv;
}
///
/// \brief BitOperations::BitsToInt
/// \param bits
/// \return массив бит в целое число
/// invert = true    - инвертировать биты (первый бит в массиве - самый МЛАДШИЙ в числе)
/// invert = false   - прямой порядок бит (первый бит в массиве - самый СТАРШИЙ в числе)
///
int BitOperations::BitsToInt(QBitArray bits, bool invert)
{
    int rtv = 0;
    int i;
    if(invert)
    {
        i = 0;
        while(i!=bits.size()-1)
        {
            rtv^=bits[i];
            i++;
            rtv = rtv<<1;
        }
        rtv^=bits[bits.size()-1];
    }
    else
    {
        i = bits.size()-1;
        while(i!=0)
        {
            rtv^=bits[i];
            i--;
            rtv = rtv<<1;
        }
        rtv^=bits[0];
    }
    return rtv;
}

QBitArray BitOperations::ByteToBits(unsigned char N, bool invert)
{
    QBitArray rtv(8);
    int i = 0;
    if(invert)
    {
        while(i < 8)
        {
            rtv.setBit(i,(N>>i)&1);
            i++;
        }
    }
    else
    {
        while(i < 8)
        {
            rtv.setBit(7-i,(N>>i)&1);
            i++;
        }
    }
    return rtv;
}

unsigned char BitOperations::BitsToByte(QBitArray bits, bool invert)
{
    unsigned char rtv = 0;
    int i;
    if(invert)
    {
        i = 0;
        while(i!=7)
        {
            rtv^=bits[i];
            i++;
            rtv = rtv<<1;
        }
        rtv^=bits[bits.size()-1];
    }
    else
    {
        i = bits.size()-1;
        while(i!=0)
        {
            rtv^=bits[i];
            i--;
            rtv = rtv<<1;
        }
        rtv^=bits[0];
    }
    return rtv;
}

std::vector<unsigned char> BitOperations::BitsToBytes(QBitArray dataBits,bool invert)
{
    QBitArray buffer(8);
    std::vector<unsigned char> dataBytes;
    int a = dataBits.size();
    int b = a%8;
    if(b != 0)
    {
        dataBits.resize(dataBits.size()-b);
    }
    for(int i = 0; i<dataBits.size()-1;i+=8)
    {
        for(int j =0; j<8;j++)
        {
            buffer[j] = dataBits[i+j];
        }
        dataBytes.insert(dataBytes.end(),BitsToByte(buffer,invert));
    }

    return dataBytes;
}
