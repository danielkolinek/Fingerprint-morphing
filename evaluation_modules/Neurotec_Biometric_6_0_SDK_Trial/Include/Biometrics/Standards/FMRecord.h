#ifndef FM_RECORD_H_INCLUDED
#define FM_RECORD_H_INCLUDED

#include <Biometrics/Standards/BdifTypes.h>
#include <Biometrics/NTemplate.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(FMRecord, NObject)

#ifdef N_CPP
}
#endif

#include <Biometrics/Standards/FmrFingerView.h>

#ifdef N_CPP
extern "C"
{
#endif

typedef enum FmrCaptureEquipmentCompliance_
{
	fmrcecNone = 0,
	fmrcecFbi = 0x80,
	fmrcecIso = 0x01
} FmrCaptureEquipmentCompliance;

N_DECLARE_TYPE(FmrCaptureEquipmentCompliance)

#define FMR_VERSION_ANSI_2_0 0x0200
#define FMR_VERSION_ANSI_3_5 0x0305
#define FMR_VERSION_ISO_2_0  0x0200
#define FMR_VERSION_ISO_3_0  0x0300

#define FMR_VERSION_ANSI_CURRENT FMR_VERSION_ANSI_3_5
#define FMR_VERSION_ISO_CURRENT  FMR_VERSION_ISO_3_0

#define FMR_MAX_FINGER_VIEW_COUNT_PER_FINGER 16

#define FMR_MAX_FINGER_COUNT 11
#define FMR_MAX_FINGER_VIEW_COUNT (FMR_MAX_FINGER_COUNT * FMR_MAX_FINGER_VIEW_COUNT_PER_FINGER)

#define FMR_MAX_FINGER_COUNT_3_0 25
#define FMR_MAX_FINGER_VIEW_COUNT_3_0 (FMR_MAX_FINGER_COUNT_3_0 * FMR_MAX_FINGER_VIEW_COUNT_PER_FINGER)

#define FMR_MAX_FINGER_COUNT_3_5 25
#define FMR_MAX_FINGER_VIEW_COUNT_3_5 (FMR_MAX_FINGER_COUNT_3_5 * FMR_MAX_FINGER_VIEW_COUNT_PER_FINGER)

#define FMR_PROCESS_FIRST_FINGER_ONLY                 0x00000100
#define FMR_PROCESS_FIRST_FINGER_VIEW_PER_FINGER_ONLY 0x00001000
#define FMR_PROCESS_FIRST_FINGER_VIEW_ONLY           (FMR_PROCESS_FIRST_FINGER_ONLY | FMR_PROCESS_FIRST_FINGER_VIEW_PER_FINGER_ONLY)

NResult N_API FMRecordCreateEx(BdifStandard standard, NVersion_ version, NUInt flags, HFMRecord * phRecord);
NResult N_API FMRecordCreateFromMemoryN(HNBuffer hBuffer, NUInt flags, BdifStandard standard, NSizeType * pSize, HFMRecord * phRecord);
NResult N_API FMRecordCreateFromMemory(const void * pBuffer, NSizeType bufferSize, NUInt flags, BdifStandard standard, NSizeType * pSize, HFMRecord * phRecord);
NResult N_API FMRecordCreateFromFMRecordEx(HFMRecord hSrcRecord, NUInt flags, BdifStandard standard, NVersion_ version, HFMRecord * phRecord);
NResult N_API FMRecordCreateFromNFRecordEx(HNFRecord hNFRecord, NUInt flags, BdifStandard standard, NVersion_ version, HFMRecord * phRecord);
NResult N_API FMRecordCreateFromNFTemplateEx(HNFTemplate hNFTemplate, NUInt flags, BdifStandard standard, NVersion_ version, HFMRecord * phRecord);

NResult N_API FMRecordToNFTemplate(HFMRecord hRecord, NUInt flags, HNFTemplate * phNFTemplate);
NResult N_API FMRecordToNTemplate(HFMRecord hRecord, NUInt flags, HNTemplate * phNTemplate);

NResult N_API FMRecordGetStandard(HFMRecord hRecord, BdifStandard * pValue);
NResult N_API FMRecordGetVersion(HFMRecord hRecord, NVersion_ * pValue);
NResult N_API FMRecordGetCbeffProductId(HFMRecord hRecord, NUInt * pValue);
NResult N_API FMRecordSetCbeffProductId(HFMRecord hRecord, NUInt value);
NResult N_API FMRecordGetCertificationFlag(HFMRecord hRecord, NBool * pValue);
NResult N_API FMRecordSetCertificationFlag(HFMRecord hRecord, NBool value);

NResult N_API FMRecordAddFingerView(HFMRecord hRecord, HFmrFingerView hFingerView, NInt * pIndex);
NResult N_API FMRecordGetFingerViewCount(HFMRecord hRecord, NInt * pValue);
NResult N_API FMRecordGetFingerView(HFMRecord hRecord, NInt index, HFmrFingerView * phValue);
NResult N_API FMRecordGetFingerViews(HFMRecord hRecord, HFmrFingerView * * parValues, NInt * pValueCount);
NResult N_API FMRecordGetFingerViewCapacity(HFMRecord hRecord, NInt * pValue);
NResult N_API FMRecordSetFingerViewCapacity(HFMRecord hRecord, NInt value);
NResult N_API FMRecordRemoveFingerViewAt(HFMRecord hRecord, NInt index);
NResult N_API FMRecordClearFingerViews(HFMRecord hRecord);

NResult N_API FMRecordGetCaptureEquipmentCompliance(HFMRecord hRecord, FmrCaptureEquipmentCompliance * pValue);
NResult N_API FMRecordSetCaptureEquipmentCompliance(HFMRecord hRecord, FmrCaptureEquipmentCompliance value);
NResult N_API FMRecordGetCaptureEquipmentId(HFMRecord hRecord, NUShort * pValue);
NResult N_API FMRecordSetCaptureEquipmentId(HFMRecord hRecord, NUShort value);
NResult N_API FMRecordGetSizeX(HFMRecord hRecord, NUShort * pValue);
NResult N_API FMRecordSetSizeX(HFMRecord hRecord, NUShort value);
NResult N_API FMRecordGetSizeY(HFMRecord hRecord, NUShort * pValue);
NResult N_API FMRecordSetSizeY(HFMRecord hRecord, NUShort value);
NResult N_API FMRecordGetResolutionX(HFMRecord hRecord, NUShort * pValue);
NResult N_API FMRecordSetResolutionX(HFMRecord hRecord, NUShort value);
NResult N_API FMRecordGetResolutionY(HFMRecord hRecord, NUShort * pValue);
NResult N_API FMRecordSetResolutionY(HFMRecord hRecord, NUShort value);

#ifdef N_CPP
}
#endif

#endif // !FM_RECORD_H_INCLUDED
