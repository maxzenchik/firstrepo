#include "output.h"

Output::Output()
{
    packsDetected = 0;
}
void Output::OutConsoleVDL2()
{
    try
    {
        QTextStream Qcout(stdout);

        for(unsigned int j = 0; j < messages.size();j++)
        {
            Qcout << "Destination adress (HEX) : ";
            Qcout << QString::number(dstAdress[j],16)<<"\r\n";
            Qcout << "Source adress (HEX) : ";
            Qcout << QString::number(srcAdress[j],16)<<"\r\n";
            Qcout << "Data (characters): \r\n";
            Qcout << messages[j].toUtf8() << "\r\n";
        }
    }
    catch(QException e)
    {

    }
}

void Output::OutFileVDL2(QString outFileName)
{
    try
    {
        if(outFileName != NULL)
        {
            QFile outFile(outFileName);
            outFile.open(QIODevice::Append);
            for(int i = 0; i <messages.size(); i++)
            {
                //адрес source
                outFile.write(format_src_str.toUtf8());
                outFile.write(QString::number(srcAdress.at(i),16).toUtf8().toUpper());
                outFile.write(format_div_str.toUtf8());
                //адрес dst
                outFile.write(format_dst_str.toUtf8());
                outFile.write(QString::number(dstAdress.at(i),16).toUtf8().toUpper());
                outFile.write(format_div_str.toUtf8());
                //время
                /*outFile.write(format_time_str.toUtf8());
                outFile.write(QString::number(times.at(i),16).toUtf8());
                outFile.write(format_div_str.toUtf8());*/
                //тип
                /*outFile.write(format_type_str.toUtf8());
                outFile.write(QString::number(types.at(i),16).toUtf8());
                outFile.write(format_div_str.toUtf8());*/
                //сообщение
                outFile.write(format_msg_str.toUtf8());
                outFile.write(messages.at(i).toUtf8());
                outFile.write(format_div_str.toUtf8());
                outFile.write(format_div_str.toUtf8());

            }

        }
    }
    catch(QException e)
    {

    }

}
void Output::OutFileVDL3(QString outFileName)
{
    try
    {
        if(outFileName != NULL)
        {
            QFile outFile(outFileName);
            outFile.open(QIODevice::WriteOnly);

            outFile.write(outBytes);
        }
    }
    catch(QException e)
    {

    }
}
