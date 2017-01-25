#ifndef OUTPUT_H
#define OUTPUT_H
#include <QFile>
#include <QTextStream>
#include <QException>
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
private:
    QString format_src_str = "Source adress: ";
    QString format_dst_str = "Destination adress: ";
    QString format_msg_str = "Data (characters): \r\n";
    QString format_time_str = "Time: ";
    QString format_type_str = "Type: ";
    QString format_div_str = "\r\n";
};

#endif // OUTPUT_H
