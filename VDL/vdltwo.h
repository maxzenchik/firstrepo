#ifndef VDLTWO_H
#define VDLTWO_H
#include <cstdlib>
#include "ezpwd/rs"
#include "qmath.h"
#include "QBitArray"
#include "stdio.h"
#include <QString>
#include <QVector>
#include "boost/crc.hpp"
#include <bitoperations.h>
#include <complex>

class VDLTWO
{
public:
    VDLTWO();
    static std::complex<int>* InitUniqWord();
    static std::complex<int>* InitTrSequence();
    static int FromBitsToInt(QBitArray bits);
    ///
    /// \brief ByteToBitsRMB
    /// \param N - байт
    /// \return массив из 8 бит
    /// переводит байт в массив из 8 бит считая старшим ПРАВЫЙ бит
    static QBitArray ByteToBitsRMB(unsigned char N);
    /// \brief ByteToBitsLMB
    /// \param N - байт
    /// \return массив из 8 бит
    /// переводит байт в массив из 8 бит считая старшим ЛЕВЫЙ бит
    static QBitArray ByteToBitsLMB(unsigned char N);
    ///
    /// \brief Int16ToBitsLMB
    /// \param N
    /// \return
    ///
    static QBitArray Int16ToBitsLMB(int N);
    ///
    /// \brief DecodeHeader
    /// \param bits массив из 25 бит - закодированный заголовок
    /// \return массив из 25 бит - декодированный заголовок
    /// декодирование заголовка кодом исправляющим ошибки (25,20)
    static QBitArray DecodeHeader(QBitArray bits);
    ///
    /// \brief GetUniqWord
    /// \param bits массив входных данных
    /// \return массив 48 бит уникальное слово
    /// получает уникально слово (индикатор начала пакета)
    static QBitArray GetUniqWord(QBitArray bits);
    ///
    /// \brief GetTransmissionLength
    /// \param bits 25 бит декодированный заголовок
    /// \return длинна пересылки
    /// получает из заголовка длинну пересылки
    static int GetTransmissionLength(QBitArray bits);
    ///
    /// \brief GetData
    /// \param bits
    /// \return
    ///
    static QBitArray GetData(QBitArray bits);
    ///
    /// \brief GetRSFEC
    /// \param bits
    /// \return
    ///
    static QBitArray GetRSFEC(QBitArray bits);
    ///
    /// \brief GetScrambledBits
    /// \param databits битовый поток данных
    /// \return биты на которые накладывался псевдослучайный шум
    /// получает массив бит для дальнейшего скремблинга
    static QBitArray GetScrambledBits(QBitArray databits);
    ///
    /// \brief GetTime
    /// \param databits - битовый массив данных
    /// \return время обнаружения пакета
    ///
    static quint64 GetTime(QBitArray databits);
    ///
    /// \brief Scramble
    /// \param bits входной массив бит для скремблинга
    /// \return дескремблированные биты
    /// СКРЕМБЛЕР, он же ДЕСКРЕМБЛЕР
    static QBitArray Scramble(QBitArray bits);
    ///
    /// \brief Interleave
    /// \param data_bytes массив байт после дескремблинга
    /// \return массив байт
    /// выполняет обратное перемежение байт
    static std::vector<unsigned char> Interleave(std::vector<unsigned char> data_bytes);
    ///
    /// \brief VDLTWO::GetBlocks
    /// \param data_bytes
    /// \return возвращает двумерный массив состоящий из блоков длинной 255 байт. 249 байт данных и 6 байт проверочных Рида соломона.
    ///последний блок дополняется нулями если это необходимо. Количество данных может быть меньше 249 проверочныз байт меньше 6 но длинна выходного блока всегда будет 255
    ///формат: 1й блок [данные..........249 байт][проверка....6 байт]
    ///        2й блок [данные..........249 байт][проверка....6 байт]
    ///.............................................................
    ///        nй блок [данные...+ нули...249 б.][проверка+нули  6 б]
    static std::vector<std::vector<unsigned char>> GetBlocks(std::vector<unsigned char> data_bytes);
    ///
    /// \brief MergeBlocks
    /// \param blocks
    /// \return
    /// объединяет блоки после декодирования в цельный поток байт
    /// удаляет нулевые байты которые были добавлены в GetBlocks
    /// может удалить значимые байты если они являеются нулевыми
    static std::vector<unsigned char> MergeBlocks(std::vector<std::vector<unsigned char>> blocks);
    ///
    /// \brief FromBytes или FromBytesRMB
    /// \param data_bytes
    /// \return
    /// переводит массив байт в массив бит считая старшим ЛЕВЫЙ или ПРАВЫЙ бит
    static QBitArray FromBytes(std::vector<unsigned char> data_bytes);
    static QBitArray FromBytesRMB(std::vector<unsigned char> data_bytes);
    ///
    /// \brief BitStuffingBack
    /// \param stuffed_data
    /// \return массив бит без "лишних" бит
    /// находит и вырезает служебные биты
    static QBitArray BitStuffingBack(QBitArray stuffed_data);
    ///
    /// \brief GetDataFrames
    /// \param data
    /// \return
    /// извлекает флаги начала/конца фрейма и получает фреймы сообщения
    static QVector<QBitArray> GetDataFrames(QBitArray);
    ///
    /// \brief GetSourceAdress или GetDestAdress
    /// \param data - фрейм
    /// \return адресс
    /// получает адрес назначения или отправления фрейма
    static int GetSourceAdress(std::vector<unsigned char> data);
    static int GetDestAdress(std::vector<unsigned char> data);
    ///
    /// \brief RSDecodeBlocks
    /// \param blocks блоки данных по 255 байт
    /// \return декодированные блоки данных
    /// декодер Рида Соломона
    static std::vector<std::vector<unsigned char>> RSDecodeBlocks(std::vector<std::vector<unsigned char>> blocks);
    ///
    /// \brief CheckCRC
    /// \param block - блок данных ВМЕСТЕ с контрольной суммой (2 последних байта)
    /// \return true - контрольная сумма совпадает. false - контрольная сумма не совпадает
    /// проверка CRC контрольной суммы блока данных
    static bool IsCorrectFCS(std::vector<unsigned char> block);
};

#endif // VDLTWO_H

