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
        stdout<<e;
    }
}

void Output::OutFileVDL2(QString outFileName)
{
    try
    {
        if(outFileName != NULL)
        {
            QFile outFile(outFileName);
            outFile.open(QIODevice::WriteOnly);
            for(int i = messages.size()-1; i >= 0; i--)
            {
                outBytes.insert(bytesWriten,messages[i]);//сообщение

                outBytes.insert(bytesWriten,srcAdress[i]);//адрес отправителя
                outBytes.insert(bytesWriten,srcAdress[i]>>8);//адрес отправителя
                outBytes.insert(bytesWriten,srcAdress[i]>>16);//адрес отправителя

                outBytes.insert(bytesWriten,dstAdress[i]);//адрес назначения
                outBytes.insert(bytesWriten,dstAdress[i]>>8);//адрес назначения
                outBytes.insert(bytesWriten,dstAdress[i]>>16);//адрес назначения

                outBytes.insert(bytesWriten,lengths[0]);//длинна
                outBytes.insert(bytesWriten,lengths[0]>>8);//длинна

                outBytes.insert(bytesWriten,types[0]);//тип

                outBytes.insert(bytesWriten,times[0]);//время
                outBytes.insert(bytesWriten,times[0]>>8);//время
                outBytes.insert(bytesWriten,times[0]>>16);//время
                outBytes.insert(bytesWriten,times[0]>>24);//время
                outBytes.insert(bytesWriten,times[0]>>32);//время
            }
            outFile.write(outBytes);
        }
    }
    catch(QException e)
    {
        stdout<<e;
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
        stdout<<e;
    }
}
