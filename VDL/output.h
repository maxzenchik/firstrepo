#ifndef OUTPUT_H
#define OUTPUT_H
#include <QFile>
#include <QTextStream>
///
/// \brief The Output class
///класс для хранения и вывода обработанной информации VDL2 и VDL3.
class Output
{

public:
    Output();
    QByteArray outBytes;
    int bytesWriten;
    int packsDetected;
    std::vector<int> srcAdress;
    std::vector<int> dstAdress;
    std::vector<QString> messages;
    std::vector<unsigned int> lengths;
    std::vector<quint64> times;
    std::vector<unsigned char> types;
    uint adressVDL3;

    void OutConsoleVDL2();
    void OutFileVDL2(QString outFileName);
    void OutFileVDL3(QString outFileName);
};

#endif // OUTPUT_H
