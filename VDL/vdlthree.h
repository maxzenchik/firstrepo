#ifndef VDLTHREE_H
#define VDLTHREE_H
#include <QBitArray>
#include <stdio.h>
#include <math.h>
#include "ezpwd/rs"
#include <qmath.h>
#include <boost/crc.hpp>
#include <bitoperations.h>
#include <stdio.h>
#include <complex>
#include <cstdlib>

class VDLTHREE
{
public:
    VDLTHREE();
    static std::complex<int>* InitTrainingSeqMDownlink();
    static std::complex<int>* InitTrainingSeqRequest();
    static std::complex<int>* InitTrainingSeqUpLinkBurst();
    static std::complex<int>* InitTrainingSeqResponse();

    int weight(int vector);
    static int FromBitsToInt(QBitArray bits);
    static QBitArray GoleyEncode(QBitArray data);

    /// \brief VDLTHREE::GoleyDecode
    /// \param encoded_data - битовый массив содержащий кодовое слово (24 бит)
    /// \return битовый массив содержащий информационное слово без ошибок (12 бит)
    /// деокдер расширенного кода ГОЛЕЯ (24,12,8)
    static QBitArray GoleyDecode(QBitArray encoded_data);
    static std::vector<unsigned char> RSDecodeBlocks(std::vector<unsigned char> data);
    static bool IsCorrectFCS(std::vector<unsigned char> block);
    static unsigned int GetFCS(std::vector<unsigned char> block);
};

#endif // VDLTHREE_H
