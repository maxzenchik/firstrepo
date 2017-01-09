
#include <decoder.h>
#include <output.h>
#include <vdlmanager.h>
#include <QTime>

const quint64 VDL2 = 0;
const quint64 VDL3_S1 = 1;
const quint64 VDL3_S1_2 = 2;
const quint64 VDL3_S2 = 3;
const quint64 VDL3_S2_2 = 4;



int main(int argc, char *argv[])
{

    QCoreApplication a(argc, argv);

    static const QString IN_FILE_FLAG = "-z";
    static const QString OUT_FILE_FLAG = "-v";
    static const QString HELP_FLAG = "-h";


    std::vector<QString> params;
    for(int i = 0; i < argc; i++)
    {
        params.push_back(argv[i]);
    }

    QString inFileName;
    QString outFileName;
    QString help = "Command format: \r\n-z <IN_file_name> -v <OUT_file_name> \r\nIf OUT file name is empty - output to console \r\n";
    //УСТАНОВКА ПАРАМЕТРОВ
    for(int i = 0; i < argc; i++)
    {
        if(params[i] == IN_FILE_FLAG)
        {
            inFileName = params[++i];
        }
        if(params[i] == OUT_FILE_FLAG)
        {
            outFileName = params[++i];
        }
        if(params[i] == HELP_FLAG)
        {
            QTextStream Qcout(stdout);
            Qcout << help;
        }
    }


    ///НАЧАЛО
    ///Открыть файл (канал) и считать данные



    if(inFileName!=NULL)
    {
        QFile data(inFileName);
        data.open(QIODevice::ReadOnly);
        QByteArray signal = data.readAll();
        VDLManager m_VDL;
        QTime t = QTime::currentTime();
        QTextStream Qcout(stdout);
        Qcout << "Processing Data...";

        int start_time = t.currentTime().second();
        QVector<Output> Out = m_VDL.ProcessDataFile(signal,false, true);
        int end_time = t.currentTime().second();
        //emit m_VDL->ProcessData(signal,false);
        data.close();//закрытие файла (канала)*/
        if(start_time > end_time)
        {
            end_time += 60;
        }
        Qcout<<"done \r\n";
        Qcout<<QString::number(end_time - start_time,10);



    }
    return a.exec();
}


