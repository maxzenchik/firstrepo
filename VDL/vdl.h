#ifndef VDL_H
#define VDL_H
#include <QCoreApplication>
#include <QString>
#include <QFile>
#include <QtDebug>
#include <vdltwo.h>
#include <vdlthree.h>
#include <QDataStream>
#include <vector>

#include <assert.h>
#include <cstdlib>
class VDL
{
public:
    VDL();


    const int FRAME_SIZE = 349760;
    static const QString IN_FILE_FLAG = "-z";
    static const QString OUT_FILE_FLAG = "-v";
    static const QString HELP_FLAG = "-h";
    QString Filename;

    qint16 signalI[FRAME_SIZE];
    qint16 signalQ[FRAME_SIZE];

    void ReadSingnal(QByteArray ba);
    void ProcessData(QByteArray ba);
};

#endif // VDL_H
