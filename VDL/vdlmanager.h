#ifndef VDLMANAGER_H
#define VDLMANAGER_H
#include <QByteArray>
#include <output.h>
#include <vdlthree.h>
#include <vdltwo.h>
#include <decoder.h>
#include <demod.h>

class VDLManager : public QObject
{
    Q_OBJECT
public:
    static const int FRAME_SIZE = 349760;
    VDLManager();
    ~VDLManager();
    Demod *m_Demodulator;
    Decoder *m_Decoder;

    //qint16* signalI;
    //qint16* signalQ;
    ///
    /// \brief ProcessDataFile демодуляция декодирование и вывод сообщений VDL (через возвращаемое значение)
    /// \param signal массив выборок
    /// \param spectreInverse инверсия спектра
    /// \param realTimeOut true = вывод в консоль сообщений сразу после обнаружения и декодирования. false = вывод нужно осуществлять после завершения функции
    /// \return - вектор, содержащий все найденые сообщения
    ///
    QVector<Output> ProcessDataFile(QFile *signal, bool spectreInverse, bool runtimeOut);
signals:
    void resultReady(Output);
public slots:
    ///
    /// \brief ProcessData демодуляция и вывод сообщений VDL (используется механизм сигналов и слотов)
    /// \param signal
    /// \param spectreInverse
    ///
    void ProcessData(QByteArray signal, bool spectreInverse);
    void handleResult(Output out);




};

#endif // VDLMANAGER_H
