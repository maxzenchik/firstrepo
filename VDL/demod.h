#ifndef DEMOD_H
#define DEMOD_H

#include <QtCore/QCoreApplication>
#include <bitset>
#include "vdlthree.h"
#include "vdltwo.h"

#define Ntap_M 270 //длина  регистра для входного сигнала
#define Ntap_T 256 //длина  регистра для блока выделения тактовой частоты
#define Ntap_e 5

#define L_uniqueWord 19 //длина уникального слова
#define L_preambulaTime 40 //Длина преамбулы времени
#define L_preambulaVDL 8   //Длина преамбулы режима VDL
#define L_preambula 48
#define L_Z 120  //длина линии задержки входного сигнала
using namespace std;
class Demod:public QObject
{ Q_OBJECT
//функции для декодирования заголовка пакета VDL-2. Вызываются в указанном порядке

int sampl_inSimbol = 8; //колличество входных отсчетов на символ
bool packetWriteEnable;//для идентификации VDL пакета
int simbol_sizeOfData;//размер пакета  в символах
int maxThreshold;//текущий порог для обнаружитенля
int kmax;// номер отсчета максимума кореляционной функции
int energeS;//енергетика сигнала VDL-2
QVector <qint8> simbol;//набор демодулированных символов



//перечисление возможных вариантов  уникального слова
enum burst {noise,//нет пакета
            mod2,//пакет режима VDL-Mod2
            standart,//пакет M-DownLink
            net_request,//пакет использующийся для идентификации сетевого запроса при M-DownLink
            voice,//пакет звук/данные пользоваетля
            id_air//пакет для идентификации ID судна при M-DownLink ( poll responses
           };
burst paket;

//перечисление возможных конфигураций систем
enum System_configurations {
            VDL_2,//режим VDL-2
            Non_3T,//конфигурация не-3Т
            Dedicated_voice_circuit_ABCD,//выделенный канал(слот) звука для каждой группы полъзователей,поддерж 4 гр, слоты: A B C D
            Dedicated_voice_circuit_wshared_data_circuit_ABC,//выделенный канал(слот) звука для каждой группы полъзователей,поддерж 3 гр,слоты: A B C и общий канал данных, слот D
            Dedicated_voice_circuit_wdedicated_data_circuit,//выделенные каналы(слот) звука для кажд группы пользователей, слоты: A B и выделенные каналы данных для кажд группы пользов, слоты: C D, поддерж 2 гр
            Demand_assigned_voice_and_data,//предоставление по требованию звука и данных, по всем слотам, поддерж 1 гр пользоват. 3-T конфигурация
            //длинная серия
            Dedicated_voice_circuit_ABC,//выделенный канал(слот) звука для каждой группы полъзователей A B C, поддерж 3гр
            Dedicated_voice_circuit_with_ABCstation_diversity,//выделенный канал звука по трем различным станциям(слотам), слоты:  A B C, поддерж 1гр
            Dedicated_voice_circuit_with_ACstation_diversity,//выделенный канал звука по двум различным станциям(слотам), слоты:  A C, поддерж 1гр
            Dedicated_voice_circuit_wshared_data_circuit_AB//выделенный канал(слот) звука для каждой группы полъзователей,поддерж 2 гр,слоты: A B  и общий канал данных, слот С

                          };
 System_configurations system_config;

 //перечисление возможных направлений пакета
enum link {undefined,
           up_link,
           down_link
          };
link  direct;


complex <int> M[Ntap_M];//массив кореллятора

qint64 Energe[Ntap_e];

public:
 void init();

std::complex<int> GetCorrFunc(std::complex<int> UniqueWordVDL2[]);
//Функция Демодулятор.Принимает массивы  signalI и signalQ. Возвращает демодулированные VDL пакеты.
//Один элемент QVector соответствует одному  VDL пакету
QVector <QBitArray> Difdem(qint16 signalI[], qint16 signalQ[]);


};
#endif // DEMOD_H
