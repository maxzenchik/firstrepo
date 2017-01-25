#include "vdl.h"

VDL::VDL()
{
}
VDL::ProcessData(QByteArray DataSource)
{
    QDataStream ds(DataSource,QIODevice::ReadOnly);
    ds.setByteOrder(QDataStream::LittleEndian);

        for(int i = 0; i<FRAME_SIZE; i++)
        {
            ds>>signalI[i];//реальная часть сигнала
            ds>>signalQ[i];//мнимая часть сигнала
        }
}

VDL::VDL(QString aFileName)
{
    Filename = aFileName;
    QFile data(Filename);
    data.open(QIODevice::ReadOnly);
    QDataStream ds(&data);
    ///порядок байт`
    ///LittleEndian - первый байт младший
    ///BigEndian - первый байт старший
    ds.setByteOrder(QDataStream::LittleEndian);
    while(!ds.atEnd())
    {
        //СЧИТЫВАНИЕ ДАННЫХ
        for(int i = 0; i<FRAME_SIZE; i++)
        {
            ds>>signalI[i];//реальная часть сигнала
            ds>>signalQ[i];//мнимая часть сигнала
        }
    }
}
