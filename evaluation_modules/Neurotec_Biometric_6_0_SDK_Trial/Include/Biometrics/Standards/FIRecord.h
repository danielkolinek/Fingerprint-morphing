#ifndef FI_RECORD_H_INCLUDED
#define FI_RECORD_H_INCLUDED

#include <Biometrics/Standards/BdifTypes.h>
#include <Images/NImage.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(FIRecord, NObject)

#ifdef N_CPP
}
#endif

typedef enum FirImageCompressionAlgorithm_
{
	firicaNotBitPacked = 0,
	firicaBitPacked = 1,
	firicaWsq = 2,
	firicaJpeg = 3,
	firicaJpeg2000 = 4,
	firicaPng = 5,
	firicaJpeg2000Lossless = 6
} FirImageCompressionAlgorithm;

N_DECLARE_TYPE(FirImageCompressionAlgorithm)

#include <Biometrics/Standards/FirFingerView.h>

#ifdef N_CPP
extern "C"
{
#endif

#define FIR_VERSION_ANSI_1_0 0x0100
#define FIR_VERSION_ANSI_2_5 0x0205
#define FIR_VERSION_ISO_1_0  0x0100
#define FIR_VERSION_ISO_2_0  0x0200

#define FIR_VERSION_ANSI_CURRENT FIR_VERSION_ANSI_2_5
#define FIR_VERSION_ISO_CURRENT  FIR_VERSION_ISO_2_0

#define FIR_MAX_FINGER_VIEW_COUNT_PER_FINGER_1_0 N_BYTE_MAX
#define FIR_MAX_FINGER_VIEW_COUNT_PER_FINGER_2_0 16
#define FIR_MAX_FINGER_VIEW_COUNT_PER_FINGER_2_5 16

#define FIR_MAX_FINGER_COUNT_1_0 N_BYTE_MAX
#define FIR_MAX_FINGER_COUNT_2_0 42
#define FIR_MAX_FINGER_COUNT_2_5 42

#define FIR_MAX_FINGER_VIEW_COUNT_PER_FINGER  16
#define FIR_MAX_FINGER_COUNT                  N_BYTE_MAX
#define FIR_MAX_FINGER_VIEW_COUNT             (FIR_MAX_FINGER_COUNT_1_0 * FIR_MAX_FINGER_VIEW_COUNT_PER_FINGER_1_0)

#define FIR_MAX_FINGER_VIEW_COUNT_1_0 (FIR_MAX_FINGER_COUNT_1_0 * FIR_MAX_FINGER_VIEW_COUNT_PER_FINGER_1_0)
#define FIR_MAX_FINGER_VIEW_COUNT_2_0 (FIR_MAX_FINGER_COUNT_2_0 * FIR_MAX_FINGER_VIEW_COUNT_PER_FINGER_2_0)
#define FIR_MAX_FINGER_VIEW_COUNT_2_5 N_BYTE_MAX

#define FIR_PROCESS_FIRST_FINGER_ONLY                  0x00000100
#define FIR_PROCESS_FIRST_FINGER_VIEW_PER_FINGER_ONLY  0x00001000
#define FIR_PROCESS_FIRST_FINGER_VIEW_ONLY (FIR_PROCESS_FIRST_FINGER_ONLY | FIR_PROCESS_FIRST_FINGER_VIEW_PER_FINGER_ONLY)

NResult N_API FIRecordCreateEx(BdifStandard standard, NVersion_ version, NUInt flags, HFIRecord * phRecord);
NResult N_API FIRecordCreateFromMemoryN(HNBuffer hBuffer, NUInt flags, BdifStandard standard, NSizeType * pSize, HFIRecord * phRecord);
NResult N_API FIRecordCreateFromMemory(const void * pBuffer, NSizeType bufferSize, NUInt flags, BdifStandard standard, NSizeType * pSize, HFIRecord * phRecord);
NResult N_API FIRecordCreateFromFIRecordEx(HFIRecord hSrcRecord, NUInt flags, BdifStandard standard, NVersion_ version, HFIRecord * phRecord);

NResult N_API FIRecordCreateFromNImageEx(HNImage hImage,
	NUShort imageAcquisitionLevel, BdifScaleUnits scaleUnits, NUShort horzScanResolution, NUShort vertScanResolution,
	NByte pixelDepth, FirImageCompressionAlgorithm imageCompressionAlgorithm,
	BdifFPPosition fingerPosition, NUInt flags, BdifStandard standard, NVersion_ version, HFIRecord * phRecord);

NResult N_API FIRecordAddFingerView(HFIRecord hRecord, HFirFingerView hFingerView, NInt * pIndex);
NResult N_API FIRecordGetFingerViewCount(HFIRecord hRecord, NInt * pValue);
NResult N_API FIRecordGetFingerView(HFIRecord hRecord, NInt index, HFirFingerView * phValue);
NResult N_API FIRecordGetFingerViewCapacity(HFIRecord hRecord, NInt * pValue);
NResult N_API FIRecordSetFingerViewCapacity(HFIRecord hRecord, NInt value);
NResult N_API FIRecordRemoveFingerViewAt(HFIRecord hRecord, NInt index);
NResult N_API FIRecordClearFingerViews(HFIRecord hRecord);

NResult N_API FIRecordGetVersion(HFIRecord hRecord, NVersion_ * pValue);
NResult N_API FIRecordGetStandard(HFIRecord hRecord, BdifStandard * pValue);
NResult N_API FIRecordGetCertificationFlag(HFIRecord hRecord, NBool * pValue);
NResult N_API FIRecordSetCertificationFlag(HFIRecord hRecord, NBool value);
NResult N_API FIRecordGetCbeffProductId(HFIRecord hRecord, NUInt * pValue);
NResult N_API FIRecordSetCbeffProductId(HFIRecord hRecord, NUInt value);
NResult N_API FIRecordGetCaptureDeviceId(HFIRecord hRecord, NUShort * pValue);
NResult N_API FIRecordSetCaptureDeviceId(HFIRecord hRecord, NUShort value);
NResult N_API FIRecordGetImageAcquisitionLevel(HFIRecord hRecord, NUShort * pValue);
NResult N_API FIRecordSetImageAcquisitionLevel(HFIRecord hRecord, NUShort value);
NResult N_API FIRecordGetScaleUnits(HFIRecord hRecord, BdifScaleUnits * pValue);
NResult N_API FIRecordSetScaleUnits(HFIRecord hRecord, BdifScaleUnits value);
NResult N_API FIRecordGetHorzScanResolution(HFIRecord hRecord, NUShort * pValue);
NResult N_API FIRecordSetHorzScanResolution(HFIRecord hRecord, NUShort value);
NResult N_API FIRecordGetVertScanResolution(HFIRecord hRecord, NUShort * pValue);
NResult N_API FIRecordSetVertScanResolution(HFIRecord hRecord, NUShort value);
NResult N_API FIRecordGetHorzImageResolution(HFIRecord hRecord, NUShort * pValue);
NResult N_API FIRecordSetHorzImageResolution(HFIRecord hRecord, NUShort value);
NResult N_API FIRecordGetVertImageResolution(HFIRecord hRecord, NUShort * pValue);
NResult N_API FIRecordSetVertImageResolution(HFIRecord hRecord, NUShort value);
NResult N_API FIRecordGetPixelDepth(HFIRecord hRecord, NByte * pValue);
NResult N_API FIRecordSetPixelDepth(HFIRecord hRecord, NByte value);
NResult N_API FIRecordGetImageCompressionAlgorithm(HFIRecord hRecord, FirImageCompressionAlgorithm * pValue);
NResult N_API FIRecordSetImageCompressionAlgorithm(HFIRecord hRecord, FirImageCompressionAlgorithm value);

#ifdef N_MSVC
	#pragma deprecated("FIR_MAX_FINGER_VIEW_COUNT")
	#pragma deprecated("FIR_MAX_FINGER_VIEW_COUNT_PER_FINGER")
	#pragma deprecated("FIR_MAX_FINGER_COUNT")
#endif

#ifdef N_CPP
}
#endif

#endif // !FI_RECORD_H_INCLUDED
