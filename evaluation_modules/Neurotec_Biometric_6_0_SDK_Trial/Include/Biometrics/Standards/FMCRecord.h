#ifndef FMC_RECORD_H_INCLUDED
#define FMC_RECORD_H_INCLUDED

#include <Biometrics/NFRecord.h>
#include <Biometrics/Standards/FmrFingerView.h>
#include <SmartCards/BerTag.h>
#include <SmartCards/BerTlv.h>
#include <Biometrics/Standards/BdifTypes.h>
#include <SmartCards/ConstructedBerTlv.h>
#include <SmartCards/PrimitiveBerTlv.h>
#include <SmartCards/NSmartCardsDataElements.h>
#include <SmartCards/NSmartCardsBiometry.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(FMCRecord, NObject)

#define FMCR_DEFAULT_MIN_ENROLL_MC 16
#define FMCR_DEFAULT_MIN_VERIFY_MC 12
#define FMCR_DEFAULT_MAX_ENROLL_MC 60
#define FMCR_DEFAULT_MAX_VERIFY_MC 60

typedef enum FmcrMinutiaOrder_
{
	fmcrmoNone = 0,
	fmcrmoAscending = 0x01,
	fmcrmoDescending = 0x02,
	fmcrmoCartesianXY = 0x04,
	fmcrmoCartesianYX = 0x08,
	fmcrmoAngle = 0x0C,
	fmcrmoPolar = 0x10,
	fmcrmoXOrYCoordinateExtension = 0x20
} FmcrMinutiaOrder;

N_DECLARE_TYPE(FmcrMinutiaOrder)

typedef enum FmcrFeatureHandling_
{
	fmcrfhNone = 0,
	fmcrfhRidgeCounts = 0x01,
	fmcrfhCorePoints = 0x02,
	fmcrfhDeltaPoints = 0x04,
	fmcrfhCellQuality = 0x08,
} FmcrFeatureHandling;

N_DECLARE_TYPE(FmcrFeatureHandling)

#define FMCR_BDT_TAG_FINGER_MINUTIAE_DATA 0x90
#define FMCR_BDT_TAG_RIDGE_COUNT_DATA     0x91
#define FMCR_BDT_TAG_CORE_POINT_DATA      0x92
#define FMCR_BDT_TAG_DELTA_POINT_DATA     0x93
#define FMCR_BDT_TAG_CELL_QUALITY_DATA    0x94
#define FMCR_BDT_TAG_IMPRESSION_TYPE      0x95

typedef enum FmcrMinutiaFormat_
{
	fmcrmfCompactSize = 0,
	fmcrmfNormalSize = 1
} FmcrMinutiaFormat;

N_DECLARE_TYPE(FmcrMinutiaFormat)

#define FMCR_VERSION_ISO_2_0  0x0200
#define FMCR_VERSION_ISO_3_0  0x0300

#define FMCR_VERSION_ISO_CURRENT FMCR_VERSION_ISO_3_0

#define FMCR_SKIP_FOUR_NEIGHBORS_RIDGE_COUNTS  0x00000100
#define FMCR_SKIP_EIGHT_NEIGHBORS_RIDGE_COUNTS 0x00000200
#define FMCR_SKIP_CORES                        0x00000400
#define FMCR_SKIP_DELTAS                       0x00000800
#define FMCR_SKIP_IMPRESSION_TYPE              0x00001000
#define FMCR_SKIP_VENDOR_DATA                  0x00002000
#define FMCR_SKIP_RIDGE_COUNTS                 FMCR_SKIP_FOUR_NEIGHBORS_RIDGE_COUNTS | FMCR_SKIP_EIGHT_NEIGHBORS_RIDGE_COUNTS
#define FMCR_SKIP_SINGULAR_POINTS              FMCR_SKIP_CORES | FMCR_SKIP_DELTAS
#define FMCR_SKIP_STANDARD_EXTENDED_DATA       FMCR_SKIP_RIDGE_COUNTS | FMCR_SKIP_SINGULAR_POINTS | FMCR_SKIP_IMPRESSION_TYPE
#define FMCR_SKIP_ALL_EXTENDED_DATA            FMCR_SKIP_STANDARD_EXTENDED_DATA | FMCR_SKIP_VENDOR_DATA

#define FMCR_USE_BIOMETRIC_DATA_TEMPLATE         0x02000000
#define FMCR_USE_STANDARD_BIOMETRIC_DATA_OBJECTS 0x04000000

NResult N_API FMCRecordCreate(BdifStandard standard, NVersion_ version, FmcrMinutiaFormat minutiaFormat, NUInt flags, HFMCRecord * phRecord);
NResult N_API FMCRecordCreateFromMemoryN(HNBuffer hBuffer, BdifStandard standard, NVersion_ version, FmcrMinutiaFormat minutiaFormat, NUInt flags, NSizeType * pSize, HFMCRecord * phRecord);
NResult N_API FMCRecordCreateFromMemory(const void * pBuffer, NSizeType bufferSize, BdifStandard standard, NVersion_ version, FmcrMinutiaFormat minutiaFormat, NUInt flags, NSizeType * pSize, HFMCRecord * phRecord);
NResult N_API FMCRecordCreateFromFMCRecord(HFMCRecord hSrcRecord, BdifStandard standard, NVersion_ version, FmcrMinutiaFormat minutiaFormat, NUInt flags, HFMCRecord * phRecord);

NResult N_API FMCRecordCreateFromNFRecord(HNFRecord hNFRecord, BdifStandard standard, NVersion_ version, FmcrMinutiaFormat minutiaFormat, FmcrMinutiaOrder order, NUInt flags, HFMCRecord * phRecord);
NResult N_API FMCRecordToNFRecord(HFMCRecord hRecord, NUInt flags, HNFRecord * phNFRecord);
NResult N_API FMCRecordToBerTlv(HFMCRecord hRecord, NUInt flags, HBerTlv * phBerTlv);

NResult N_API FMCRecordSortMinutiae(HFMCRecord hRecord, FmcrMinutiaOrder order);

NResult N_API FMCRecordGetVersion(HFMCRecord hRecord, NVersion_ * pValue);
NResult N_API FMCRecordGetStandard(HFMCRecord hRecord, BdifStandard * pValue);
NResult N_API FMCRecordGetMinutiaFormat(HFMCRecord hRecord, FmcrMinutiaFormat * pValue);
NResult N_API FMCRecordGetImpressionType(HFMCRecord hRecord, BdifFPImpressionType * pValue);
NResult N_API FMCRecordSetImpressionType(HFMCRecord hRecord, BdifFPImpressionType value);

NResult N_API FMCRecordGetMinutiaCount(HFMCRecord hRecord, NInt * pValue);
NResult N_API FMCRecordGetMinutia(HFMCRecord hRecord, NInt index, struct FmrMinutia_ * pValue);
NResult N_API FMCRecordSetMinutia(HFMCRecord hRecord, NInt index, const struct FmrMinutia_ * pValue);
NResult N_API FMCRecordGetMinutiae(HFMCRecord hRecord, struct FmrMinutia_ * * parValues, NInt * pValueCount);
NResult N_API FMCRecordGetMinutiaCapacity(HFMCRecord hRecord, NInt * pValue);
NResult N_API FMCRecordSetMinutiaCapacity(HFMCRecord hRecord, NInt value);
NResult N_API FMCRecordAddMinutia(HFMCRecord hRecord, const struct FmrMinutia_ * pValue, NInt * pIndex);
NResult N_API FMCRecordInsertMinutia(HFMCRecord hRecord, NInt index, const struct FmrMinutia_ * pValue);
NResult N_API FMCRecordRemoveMinutiaAt(HFMCRecord hRecord, NInt index);
NResult N_API FMCRecordClearMinutiae(HFMCRecord HFMCRecord);

NResult N_API FMCRecordGetMinutiaFourNeighbor(HFMCRecord hRecord, NInt minutiaIndex, NInt index, struct BdifFPMinutiaNeighbor_ * pValue);
NResult N_API FMCRecordSetMinutiaFourNeighbor(HFMCRecord hRecord, NInt minutiaIndex, NInt index, const struct BdifFPMinutiaNeighbor_ * pValue);
NResult N_API FMCRecordGetMinutiaFourNeighbors(HFMCRecord hRecord, NInt minutiaIndex, struct BdifFPMinutiaNeighbor_ * * parValues, NInt * pValueCount);
NResult N_API FMCRecordHasFourNeighborRidgeCounts(HFMCRecord hRecord, NBool * pValue);
NResult N_API FMCRecordSetHasFourNeighborRidgeCounts(HFMCRecord hRecord, NBool value);

NResult N_API FMCRecordGetMinutiaEightNeighbor(HFMCRecord hRecord, NInt minutiaIndex, NInt index, struct BdifFPMinutiaNeighbor_ * pValue);
NResult N_API FMCRecordSetMinutiaEightNeighbor(HFMCRecord hRecord, NInt minutiaIndex, NInt index, const struct BdifFPMinutiaNeighbor_ * pValue);
NResult N_API FMCRecordGetMinutiaEightNeighbors(HFMCRecord hRecord, NInt minutiaIndex, struct BdifFPMinutiaNeighbor_ * * parValues, NInt * pValueCount);
NResult N_API FMCRecordHasEightNeighborRidgeCounts(HFMCRecord hRecord, NBool * pValue);
NResult N_API FMCRecordSetHasEightNeighborRidgeCounts(HFMCRecord hRecord, NBool value);

NResult N_API FMCRecordGetCoreCount(HFMCRecord hRecord, NInt * pValue);
NResult N_API FMCRecordGetCore(HFMCRecord hRecord, NInt index, struct FmrCore_ * pValue);
NResult N_API FMCRecordSetCore(HFMCRecord hRecord, NInt index, const struct FmrCore_ * pValue);
NResult N_API FMCRecordGetCores(HFMCRecord hRecord, struct FmrCore_ * * parValues, NInt * pValueCount);
NResult N_API FMCRecordGetCoreCapacity(HFMCRecord hRecord, NInt * pValue);
NResult N_API FMCRecordSetCoreCapacity(HFMCRecord hRecord, NInt value);
NResult N_API FMCRecordAddCore(HFMCRecord hRecord, const struct FmrCore_ * pValue, NInt * pIndex);
NResult N_API FMCRecordInsertCore(HFMCRecord hRecord, NInt index, const struct FmrCore_ * pValue);
NResult N_API FMCRecordRemoveCoreAt(HFMCRecord hRecord, NInt index);
NResult N_API FMCRecordClearCores(HFMCRecord HFMCRecord);

NResult N_API FMCRecordGetDeltaCount(HFMCRecord hRecord, NInt * pValue);
NResult N_API FMCRecordGetDelta(HFMCRecord hRecord, NInt index, struct FmrDelta_ * pValue);
NResult N_API FMCRecordSetDelta(HFMCRecord hRecord, NInt index, const struct FmrDelta_ * pValue);
NResult N_API FMCRecordGetDeltas(HFMCRecord hRecord, struct FmrDelta_ * * parValues, NInt * pValueCount);
NResult N_API FMCRecordGetDeltaCapacity(HFMCRecord hRecord, NInt * pValue);
NResult N_API FMCRecordSetDeltaCapacity(HFMCRecord hRecord, NInt value);
NResult N_API FMCRecordAddDelta(HFMCRecord hRecord, const struct FmrDelta_ * pValue, NInt * pIndex);
NResult N_API FMCRecordInsertDelta(HFMCRecord hRecord, NInt index, const struct FmrDelta_ * pValue);
NResult N_API FMCRecordRemoveDeltaAt(HFMCRecord hRecord, NInt index);
NResult N_API FMCRecordClearDeltas(HFMCRecord HFMCRecord);

NResult N_API FMCRecordGetVendorData(HFMCRecord hRecord, HBerTlv * phValue);
NResult N_API FMCRecordSetVendorData(HFMCRecord hRecord, HBerTlv hValue);

NResult N_API FMCRecordValidateMinutiaeUniqueness(HFMCRecord hRecord, NBool * pIsUnique);


#ifdef N_CPP
}
#endif

#endif // !FMC_RECORD_H_INCLUDED
