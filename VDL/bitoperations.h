#ifndef BITOPERATIONS_H
#define BITOPERATIONS_H
#include <QBitArray>
#include <QString>

class BitOperations
{
public:
    BitOperations();
    static unsigned char Invert(unsigned char x);
    static int BitsToInt(QBitArray bits, bool invert);
    static QBitArray ByteToBits(unsigned char byte, bool invert);
    static unsigned char BitsToByte(QBitArray bits, bool invert);
    static std::vector<unsigned char> BitsToBytes(QBitArray bits,bool invert);
    QString BitsToString(QBitArray bits);
};

#endif // BITOPERATIONS_H
