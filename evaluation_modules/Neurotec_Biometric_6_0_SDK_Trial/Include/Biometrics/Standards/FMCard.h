#ifndef FM_CARD_H_INCLUDED
#define FM_CARD_H_INCLUDED

#include <Biometrics/NFRecord.h>
#include <SmartCards/BerTag.h>
#include <Biometrics/Standards/FMCRecord.h>

#ifdef N_CPP
extern "C"
{
#endif

#define FMC_DEFAULT_MIN_ENROLL_MC 16 // use FMCR_DEFAULT_MIN_ENROLL_MC instead
#define FMC_DEFAULT_MIN_VERIFY_MC 12 // use FMCR_DEFAULT_MIN_VERIFY_MC instead
#define FMC_DEFAULT_MAX_ENROLL_MC 60 // use FMCR_DEFAULT_MAX_ENROLL_MC instead
#define FMC_DEFAULT_MAX_VERIFY_MC 60 // use FMCR_DEFAULT_MAX_VERIFY_MC instead

typedef enum FmcMinutiaOrder_
{
	fmcmoNone = 0,
	fmcmoAscending = 0x01,
	fmcmoDescending = 0x02,
	fmcmoCartesianXY = 0x04,
	fmcmoCartesianYX = 0x08,
	fmcmoAngle = 0x0C,
	fmcmoPolar = 0x10,
	fmcmoXOrYCoordinateExtension = 0x20
} FmcMinutiaOrder;

N_DECLARE_TYPE(FmcMinutiaOrder)

typedef enum FmcFeatureHandling_
{
	fmcfhNone = 0,
	fmcfhRidgeCounts = 0x01,
	fmcfhCorePoints = 0x02,
	fmcfhDeltaPoints = 0x04,
	fmcfhCellQuality = 0x08,
} FmcFeatureHandling;

N_DECLARE_TYPE(FmcFeatureHandling)

#define FMC_BDT_TAG_FINGER_MINUTIAE_DATA 0x90 // use FMCR_BDT_TAG_FINGER_MINUTIAE_DATA instead
#define FMC_BDT_TAG_RIDGE_COUNT_DATA     0x91 // use FMCR_BDT_TAG_RIDGE_COUNT_DATA instead
#define FMC_BDT_TAG_CORE_POINT_DATA      0x92 // use FMCR_BDT_TAG_CORE_POINT_DATA instead
#define FMC_BDT_TAG_DELTA_POINT_DATA     0x93 // use FMCR_BDT_TAG_DELTA_POINT_DATA instead
#define FMC_BDT_TAG_CELL_QUALITY_DATA    0x94 // use FMCR_BDT_TAG_CELL_QUALITY_DATA instead
#define FMC_BDT_TAG_IMPRESSION_TYPE      0x95 // use FMCR_BDT_TAG_IMPRESSION_TYPE instead

// (ISO/IEC 19794-2, generalized for 19794-x series in ISO/IEC 24787:2010)
#define FMC_BIT_BHT_BAPT_TAG_NUMBER_OF_MINUTIAE         0x81 // use SCARD_BIT_BHT_BAPT_TAG_FEATURE_COUNT_OR_LENGTH instead
#define FMC_BIT_BHT_BAPT_TAG_MINUTIAE_ORDER             0x82 // use SCARD_BIT_BHT_BAPT_TAG_FEATURE_ORDER instead
#define FMC_BIT_BHT_BAPT_TAG_FEATURE_HANDLING_INDICATOR 0x83 // use SCARD_BIT_BHT_BAPT_TAG_EXTENDED_FEATURE_HANDLING_INDICATOR insetad

N_DECLARE_STATIC_OBJECT_TYPE(FMCard)

N_DEPRECATED("function is deprecated, use FMCRecordCreateFromNFRecord, NObjectSaveToMemoryN instead")
NResult N_API FMCardWriteNormalSizeMinutiaeN(HNFRecord hNFRecord, FmcMinutiaOrder order, HNBuffer hBuffer, NUInt flags, NSizeType * pSize);
N_DEPRECATED("function is deprecated, use FMCRecordCreateFromNFRecord, NObjectSaveToMemoryN instead")
NResult N_API FMCardWriteNormalSizeMinutiae(HNFRecord hNFRecord, FmcMinutiaOrder order, void * pBuffer, NSizeType bufferSize, NUInt flags, NSizeType * pSize);
N_DEPRECATED("function is deprecated, use FMCRecordCreateFromNFRecord, NObjectSaveToMemoryN instead")
NResult N_API FMCardWriteNormalSizeMinutiaeToMemoryN(HNFRecord hNFRecord, FmcMinutiaOrder order, NUInt flags, HNBuffer * phBuffer);
N_DEPRECATED("function is deprecated, use FMCRecordCreateFromNFRecord, NObjectSaveToMemoryN instead")
NResult N_API FMCardWriteCompactSizeMinutiaeN(HNFRecord hNFRecord, FmcMinutiaOrder order, HNBuffer hBuffer, NUInt flags, NSizeType * pSize);
N_DEPRECATED("function is deprecated, use FMCRecordCreateFromNFRecord, NObjectSaveToMemoryN instead")
NResult N_API FMCardWriteCompactSizeMinutiae(HNFRecord hNFRecord, FmcMinutiaOrder order, void * pBuffer, NSizeType bufferSize, NUInt flags, NSizeType * pSize);
N_DEPRECATED("function is deprecated, use FMCRecordCreateFromNFRecord, NObjectSaveToMemoryN instead")
NResult N_API FMCardWriteCompactSizeMinutiaeToMemoryN(HNFRecord hNFRecord, FmcMinutiaOrder order, NUInt flags, HNBuffer * phBuffer);
N_DEPRECATED("function is deprecated, use FMCRecordCreateFromMemoryN, FMCRecordToNFRecord instead")
NResult N_API FMCardReadNormalSizeMinutiaeN(HNBuffer hBuffer, FmcMinutiaOrder order, NUInt flags, NSizeType * pSize, HNFRecord * phNFRecord);
N_DEPRECATED("function is deprecated, use FMCRecordCreateFromMemoryN, FMCRecordToNFRecord instead")
NResult N_API FMCardReadNormalSizeMinutiaeEx(const void * pBuffer, NSizeType bufferSize, FmcMinutiaOrder order, NUInt flags, NSizeType * pSize, HNFRecord * phNFRecord);
N_DEPRECATED("function is deprecated, use FMCRecordCreateFromMemoryN, FMCRecordToNFRecord instead")
NResult N_API FMCardReadCompactSizeMinutiaeN(HNBuffer hBuffer, FmcMinutiaOrder order, NUInt flags, NSizeType * pSize, HNFRecord * phNFRecord);
N_DEPRECATED("function is deprecated, use FMCRecordCreateFromMemoryN, FMCRecordToNFRecord instead")
NResult N_API FMCardReadCompactSizeMinutiaeEx(const void * pBuffer, NSizeType bufferSize, FmcMinutiaOrder order, NUInt flags, NSizeType * pSize, HNFRecord * phNFRecord);

#ifdef N_MSVC
	#pragma deprecated("FmcMinutiaOrder")
	#pragma deprecated("FmcFeatureHandling")
	#pragma deprecated("FMC_BDT_TAG_FINGER_MINUTIAE_DATA")
	#pragma deprecated("FMC_BDT_TAG_RIDGE_COUNT_DATA")
	#pragma deprecated("FMC_BDT_TAG_CORE_POINT_DATA")
	#pragma deprecated("FMC_BDT_TAG_DELTA_POINT_DATA")
	#pragma deprecated("FMC_BDT_TAG_CELL_QUALITY_DATA")
	#pragma deprecated("FMC_BDT_TAG_IMPRESSION_TYPE")
	#pragma deprecated("FMC_BIT_BHT_BAPT_TAG_NUMBER_OF_MINUTIAE")
	#pragma deprecated("FMC_BIT_BHT_BAPT_TAG_MINUTIAE_ORDER")
	#pragma deprecated("FMC_BIT_BHT_BAPT_TAG_FEATURE_HANDLING_INDICATOR")
	#pragma deprecated("FMC_DEFAULT_MIN_ENROLL_MC")
	#pragma deprecated("FMC_DEFAULT_MIN_VERIFY_MC")
	#pragma deprecated("FMC_DEFAULT_MAX_ENROLL_MC")
	#pragma deprecated("FMC_DEFAULT_MAX_VERIFY_MC")
#endif

#ifdef N_CPP
}
#endif

#endif // !FM_CARD_H_INCLUDED
