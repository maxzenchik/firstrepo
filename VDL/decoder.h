#ifndef DECODER_H
#define DECODER_H
#include <QCoreApplication>
#include <vdltwo.h>
#include <vdlthree.h>
#include <QDataStream>
#include <output.h>
class Decoder
{
public:
    Decoder();
    //константы


    //переменные
    int paket = 0;
    std::vector<QString> messages;
    std::vector<int> srcAdress;
    std::vector<int> dstAdress;
    std::vector<std::vector<unsigned char>> blocks;


    //функции
private:
    static const int VDL2_MIN_PACKET_SIZE = 73;
    static const quint64 VDL2 = 1;
    static const quint64 VDL3_S1 = 2;
    static const quint64 VDL3_S1_2 = 3;
    static const quint64 VDL3_S2 = 4;
    static const quint64 VDL3_S2_2 = 5;
    unsigned char GetVersion(QBitArray bits);
public:

    Output Decode(QVector<QBitArray> inData);

};

#endif // DECODER_H
