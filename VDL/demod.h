#ifndef DEMOD_H
#define DEMOD_H
#include "qmath.h"
#include "vdlthree.h"
//#include "lpf.h"
#include <iostream>
#include <fstream>
#include <cstdlib>// нужна что бы взять модуль от комплексного
#include <math.h>
#include <complex>
#include <bitset>
#include <array>
#include <vector>
#include <QtCore/QCoreApplication>
#include <QBitArray>
#include <QByteArray>
#include <QDataStream>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QFile>

#define N_tapM 512

using namespace std;
class Demod : public QObject
{
Q_OBJECT

    //функции для декодирования заголовка пакета VDL-2. Вызываются в указанном порядке//
static QBitArray Scramble(QBitArray bits);//1й
static QBitArray DecodeHeader(QBitArray bits);//2й
static int GetTransmissionLength(QBitArray bits);//3й

int FromBitsToInt(QBitArray bits);
complex<qint32> plfFir (qint32 MI[], qint32 MQ[], qint16 p_index, qint8 nFIR);//полифазный фильтр

bool flag;//для идентификации VDL пакета
int simbol_sizeOfData;//размер пакета  в символах
int kmax;//номер отсчета,при котором был обнаружен пакет
int energeS;//величина енергетики сигнала
int maxThreshold; //уровень пика  корелляционной функции

QVector <qint8> simbol;//набор демодулированных символов

int schetchik_ZpolifF; // счетчик задержки ролифазного фильтра
bool en;// используется для включения  полифазного фильтра
int nFIR;//номер КИХ фильтра полифазного фильтра
qint16 n_Z;//поправка для выбора номера выборки в символе
qint16 schetchik_i;//счетчик переходов на соседнюю выборку после окончания наболров КИХ полифазного фильтра
complex <int> out_polifaznik_;//предыдущее значение выхода полифазного фильтра


qint16 Z_index;//текущий номер элемента  входного кольуевого буфера
qint16 m_index;// номер элемента  входного кольцевого буфера соответствующий полифазному фильтру
bool opt_1;//выбор номера входной выборки  совпадает по времени  с оптимальным отсчетом
   //индикатор уникального слова//
enum burst {noise,//нет пакета
            mod2,//пакет режима VDL-Mod2
            standart,//пакет M-DownLink
            net_request,//пакет использующийся для идентификации сетевого запроса при M-DownLink
            voice,//пакет звук/данные пользоваетля
            id_air//пакет для идентификации ID судна при M-DownLink ( poll responses
           };
burst paket;

    //перечисление возможных конфигураций систем//
enum System_configurations {
            VDL_2,//режим VDL-2
            Non_3T,//конфигурация не-3Т
            Dedicated_voice_circuit_ABCD,//выделенный канал(слот) звука для каждой группы полъзователей,поддерж 4 гр, слоты: A B C D
            Dedicated_voice_circuit_wshared_data_circuit_ABC,//выделенный канал(слот) звука для каждой группы полъзователей,поддерж 3 гр,слоты: A B C и общий канал данных, слот D
            Dedicated_voice_circuit_wdedicated_data_circuit,//выделенные каналы(слот) звука для кажд группы пользователей, слоты: A B и выделенные каналы данных для кажд группы пользов, слоты: C D, поддерж 2 гр
            Demand_assigned_voice_and_data,//предоставление по требованию звука и данных, по всем слотам, поддерж 1 гр пользоват. 3-T конфигурация

            Dedicated_voice_circuit_ABC,//выделенный канал(слот) звука для каждой группы полъзователей A B C, поддерж 3гр
            Dedicated_voice_circuit_with_ABCstation_diversity,//выделенный канал звука по трем различным станциям(слотам), слоты:  A B C, поддерж 1гр
            Dedicated_voice_circuit_with_ACstation_diversity,//выделенный канал звука по двум различным станциям(слотам), слоты:  A C, поддерж 1гр
            Dedicated_voice_circuit_wshared_data_circuit_AB//выделенный канал(слот) звука для каждой группы полъзователей,поддерж 2 гр,слоты: A B  и общий канал данных, слот С

                          };
 System_configurations system_config;

 //перечисление возможных направлений пакета//
enum link {undefined,
           up_link,
           down_link
          };
link  direct;

int MI[N_tapM];
int MQ[N_tapM];


public:

  void init();//данную функцию необходимо вызвать при запуске программы

        //Функция Демодулятор.Принимает массивы  signalI и signalQ, размерами 349760.
        //Возвращает демодулированные VDL пакеты в битах.
        //Один элемент QVector соответствует одному  VDL пакету
  QVector <QBitArray> Difdem(qint16 signalI[], qint16 signalQ[], double ResiverTakt);



};
#endif // DEMOD_H
