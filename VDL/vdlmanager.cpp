#include "vdlmanager.h"

VDLManager::VDLManager()
{
    m_Demodulator = new Demod;
    m_Demodulator->init();
    m_Decoder = new Decoder;

}

VDLManager::~VDLManager()
{
    delete m_Decoder;
    delete m_Demodulator;
    connect(this,SIGNAL(resultReady(Output)),this,SLOT(handleResult(Output)));
}

void VDLManager::ProcessData(QByteArray signal, bool spectreInverse)
{

    QDataStream ds(signal);
    ///порядок байт`
    ///LittleEndian - первый байт младший
    ///BigEndian - первый байт старший
    ds.setByteOrder(QDataStream::LittleEndian);


    ///считывание до конца файла или FIFO
    while(!ds.atEnd())
    {
        //СЧИТЫВАНИЕ ДАННЫХ
        if(!spectreInverse)
            for(int i = 0; i<FRAME_SIZE; i++)
            {
                ds>>signalI[i];//реальная часть сигнала
                ds>>signalQ[i];//мнимая часть сигнала//ПОМЕНЯТЬ ОБРАТНО!!!!
            }
        else
            for(int i = 0; i<FRAME_SIZE; i++)
            {
                ds>>signalQ[i];//реальная часть сигнала
                ds>>signalI[i];//мнимая часть сигнала//ПОМЕНЯТЬ ОБРАТНО!!!!
            }

    QVector<QBitArray> data_vector;
    //ДЕМОДУЛЯЦИЯ
    data_vector = m_Demodulator->Difdem(signalI,signalQ);
    //ДЕКОДИРОВАНИЕ
    Output m_Output = m_Decoder->Decode(data_vector);
    //ВЫВОД
    //m_Output.OutFileVDL2("ggwp.txt");
    //сигнал о завершении
    QString out;
    for(uint i = 0; i < m_Output.messages.size(); i++ )
    {
        out.append(m_Output.dstAdress.at(i));
        out.append(m_Output.srcAdress.at(i));
        out.append(m_Output.messages.at(i));
    }
    m_Output.packsDetected += data_vector.size();


    emit resultReady(m_Output);
    }
}
QVector<Output> VDLManager::ProcessDataFile(QByteArray signal, bool spectreInverse, bool runtimeOut)
{

    QDataStream ds(signal);
    ///порядок байт`
    ///LittleEndian - первый байт младший
    ///BigEndian - первый байт старший
    ds.setByteOrder(QDataStream::LittleEndian);
    QVector<Output> Resoult;
    Output m_Output;

    ///считывание до конца файла или FIFO
    while(!ds.atEnd())
    {
        //СЧИТЫВАНИЕ ДАННЫХ
        if(!spectreInverse)
            for(int i = 0; i<FRAME_SIZE; i++)
            {
                ds>>signalI[i];//реальная часть сигнала
                ds>>signalQ[i];//мнимая часть сигнала//ПОМЕНЯТЬ ОБРАТНО!!!!
            }
        else
            for(int i = 0; i<FRAME_SIZE; i++)
            {
                ds>>signalQ[i];//реальная часть сигнала
                ds>>signalI[i];//мнимая часть сигнала//ПОМЕНЯТЬ ОБРАТНО!!!!
            }

        QVector<QBitArray> data_vector;
        //ДЕМОДУЛЯЦИЯ


        data_vector = m_Demodulator->Difdem(signalI,signalQ);
        //ДЕКОДИРОВАНИЕ
        m_Output = m_Decoder->Decode(data_vector);
        //ВЫВОД
        Resoult.push_back(m_Output);
        if(runtimeOut)
        {
            m_Output.OutConsoleVDL2();
        }
        //сигнал о завершении
        QString out;
        for(uint i = 0; i < m_Output.messages.size(); i++ )
        {
            out.append(m_Output.dstAdress.at(i));
            out.append(m_Output.srcAdress.at(i));
            out.append(m_Output.messages.at(i));
        }
        m_Output.packsDetected += data_vector.size();
    }
    return Resoult;
}

void VDLManager::handleResult(Output out)
{
    out.OutConsoleVDL2();
}
