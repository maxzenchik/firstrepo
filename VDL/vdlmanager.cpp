#include "vdlmanager.h"

VDLManager::VDLManager()
{
    m_Demodulator = new Demod;
    m_Demodulator->init();
    m_Decoder = new Decoder;

}

int VDLManager::getSamplingFrequency() {
    return  samplingFrequency;
}

void VDLManager::setSamplingFrequency(int samplingFrequency) {
    samplingFrequency = samplingFrequency;
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

    qint16 *signalI = new qint16[FRAME_SIZE];
    qint16 *signalQ = new qint16[FRAME_SIZE];
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
        data_vector = m_Demodulator->Difdem(signalI,signalQ, samplingFrequency);
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
        delete [] signalI;
        delete [] signalQ;

        emit resultReady(m_Output);
    }
}
QVector<Output> VDLManager::ProcessDataFile(QFile *signal, bool spectreInverse, bool runtimeOut)
{

    QDataStream ds(signal);
    ///порядок байт`
    ///LittleEndian - первый байт младший
    ///BigEndian - первый байт старший
    ds.setByteOrder(QDataStream::LittleEndian);
    QVector<Output> Resoult;
    Output m_Output;
    qint16 *signalI = new qint16[FRAME_SIZE];
    qint16 *signalQ = new qint16[FRAME_SIZE];
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


        data_vector = m_Demodulator->Difdem(signalI,signalQ, samplingFrequency);
        //ДЕКОДИРОВАНИЕ
        m_Output = m_Decoder->Decode(data_vector);
        //ВЫВОД

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
        Resoult.push_back(m_Output);
    }
    delete [] signalI;
    delete [] signalQ;
    return Resoult;

}

void VDLManager::handleResult(Output out)
{
    out.OutConsoleVDL2();
}
