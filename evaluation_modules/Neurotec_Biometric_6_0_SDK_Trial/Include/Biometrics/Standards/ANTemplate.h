#ifndef AN_TEMPLATE_H_INCLUDED
#define AN_TEMPLATE_H_INCLUDED

#include <Biometrics/Standards/ANType1Record.h>
#include <Biometrics/Standards/ANType2Record.h>
#include <Biometrics/Standards/ANType3Record.h>
#include <Biometrics/Standards/ANType4Record.h>
#include <Biometrics/Standards/ANType5Record.h>
#include <Biometrics/Standards/ANType6Record.h>
#include <Biometrics/Standards/ANType7Record.h>
#include <Biometrics/Standards/ANType8Record.h>
#include <Biometrics/Standards/ANType9Record.h>
#include <Biometrics/Standards/ANType10Record.h>
#include <Biometrics/Standards/ANType13Record.h>
#include <Biometrics/Standards/ANType14Record.h>
#include <Biometrics/Standards/ANType15Record.h>
#include <Biometrics/Standards/ANType16Record.h>
#include <Biometrics/Standards/ANType17Record.h>
#include <Biometrics/Standards/ANType99Record.h>
#include <Images/NImage.h>
#include <Biometrics/NTemplate.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(ANTemplate, NObject)

#define AN_TEMPLATE_VERSION_2_0 0x0200
#define AN_TEMPLATE_VERSION_2_1 0x0201
#define AN_TEMPLATE_VERSION_3_0 0x0300
#define AN_TEMPLATE_VERSION_4_0 0x0400

#define AN_TEMPLATE_VERSION_CURRENT AN_TEMPLATE_VERSION_4_0


NResult N_API ANTemplateGetVersionsEx(NVersion_ * arValue, NInt valueLength);
NResult N_API ANTemplateIsVersionSupported(NVersion_ version, NBool * pValue);

NResult N_API ANTemplateGetVersionNameN(NVersion_ version, HNString * phValue);

#define ANT_USE_NIST_MINUTIA_NEIGHBORS        0x00010000
#define ANT_LEAVE_INVALID_RECORDS_UNVALIDATED 0x00020000
#define ANT_USE_TWO_DIGIT_IDC                 0x00040000
#define ANT_USE_TWO_DIGIT_FIELD_NUMBER        0x00080000
#define ANT_USE_TWO_DIGIT_FIELD_NUMBER_TYPE_1 0x00100000

N_DEPRECATED("function is deprecated, use ANTemplateCreateEx instead")
NResult N_API ANTemplateCreateWithMinimalValidation(NUInt flags, HANTemplate * phTemplate);
NResult N_API ANTemplateCreateEx(NVersion_ version, ANValidationLevel validationLevel, NUInt flags, HANTemplate * phTemplate);

N_DEPRECATED("function is deprecated, use ANTemplateCreateWithTransactionInformationN instead")
NResult N_API ANTemplateCreateN(HNString hTot, HNString hDai, HNString hOri, HNString hTcn, NUInt flags, HANTemplate * phTemplate);
#ifndef N_NO_ANSI_FUNC
N_DEPRECATED("function is deprecated, use ANTemplateCreateWithTransactionInformationA instead")
NResult N_API ANTemplateCreateA(const NAChar * szTot, const NAChar * szDai, const NAChar * szOri, const NAChar * szTcn, NUInt flags, HANTemplate * phTemplate);
#endif
#ifndef N_NO_UNICODE
N_DEPRECATED("function is deprecated, use ANTemplateCreateWithTransactionInformationW instead")
NResult N_API ANTemplateCreateW(const NWChar * szTot, const NWChar * szDai, const NWChar * szOri, const NWChar * szTcn, NUInt flags, HANTemplate * phTemplate);
#endif
#ifdef N_DOCUMENTATION
N_DEPRECATED("function is deprecated, use ANTemplateCreateWithTransactionInformation instead")
NResult N_API ANTemplateCreate(const NChar * szTot, const NChar * szDai, const NChar * szOri, const NChar * szTcn, NUInt flags, HANTemplate * phTemplate);
#endif
#define ANTemplateCreate N_FUNC_AW(ANTemplateCreate)

NResult N_API ANTemplateCreateWithTransactionInformationN(NVersion_ version, HNString hTot, HNString hDai, HNString hOri, HNString hTcn, NUInt flags, HANTemplate * phTemplate);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANTemplateCreateWithTransactionInformationA(NVersion_ version, const NAChar * szTot, const NAChar * szDai, const NAChar * szOri, const NAChar * szTcn, NUInt flags, HANTemplate * phTemplate);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANTemplateCreateWithTransactionInformationW(NVersion_ version, const NWChar * szTot, const NWChar * szDai, const NWChar * szOri, const NWChar * szTcn, NUInt flags, HANTemplate * phTemplate);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANTemplateCreateWithTransactionInformation(NVersion_ version, const NChar * szTot, const NChar * szDai, const NChar * szOri, const NChar * szTcn, NUInt flags, HANTemplate * phTemplate);
#endif
#define ANTemplateCreateWithTransactionInformation N_FUNC_AW(ANTemplateCreateWithTransactionInformation)

NResult N_API ANTemplateCreateFromFileN(HNString hFileName, ANValidationLevel validationLevel, NUInt flags, HANTemplate * phTemplate);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANTemplateCreateFromFileA(const NAChar * szFileName, ANValidationLevel validationLevel, NUInt flags, HANTemplate * phTemplate);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANTemplateCreateFromFileW(const NWChar * szFileName, ANValidationLevel validationLevel, NUInt flags, HANTemplate * phTemplate);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANTemplateCreateFromFile(const NChar * szFileName, ANValidationLevel validationLevel, NUInt flags, HANTemplate * phTemplate);
#endif
#define ANTemplateCreateFromFile N_FUNC_AW(ANTemplateCreateFromFile)

NResult N_API ANTemplateCreateFromMemoryN(HNBuffer hBuffer, ANValidationLevel validationLevel, NUInt flags, NSizeType * pSize, HANTemplate * phTemplate);
NResult N_API ANTemplateCreateFromMemoryEx(const void * pBuffer, NSizeType bufferSize, ANValidationLevel validationLevel, NUInt flags, NSizeType * pSize, HANTemplate * phTemplate);
NResult N_API ANTemplateCreateFromStream(HNStream hStream, ANValidationLevel validationLevel, NUInt flags, HANTemplate * phTemplate);

NResult N_API ANTemplateCreateFromANTemplate(HANTemplate hSrcTemplate, NVersion_ version, NUInt flags, HANTemplate * phTemplate);

N_DEPRECATED("function is deprecated, use ANTemplateCreateFromNTemplateExN instead")
NResult N_API ANTemplateCreateFromNTemplateN(HNString hTot, HNString hDai, HNString hOri, HNString hTcn,
	NBool type9RecordFmt, HNTemplate hNTemplate, NUInt flags, HANTemplate * phTemplate);
#ifndef N_NO_ANSI_FUNC
N_DEPRECATED("function is deprecated, use ANTemplateCreateFromNTemplateExA instead")
NResult N_API ANTemplateCreateFromNTemplateA(const NAChar * szTot, const NAChar * szDai, const NAChar * szOri, const NAChar * szTcn,
	NBool type9RecordFmt, HNTemplate hNTemplate, NUInt flags, HANTemplate * phTemplate);
#endif
#ifndef N_NO_UNICODE
N_DEPRECATED("function is deprecated, use ANTemplateCreateFromNTemplateExW instead")
NResult N_API ANTemplateCreateFromNTemplateW(const NWChar * szTot, const NWChar * szDai, const NWChar * szOri, const NWChar * szTcn,
	NBool type9RecordFmt, HNTemplate hNTemplate, NUInt flags, HANTemplate * phTemplate);
#endif
#ifdef N_DOCUMENTATION
N_DEPRECATED("function is deprecated, use ANTemplateCreateFromNTemplateEx instead")
NResult N_API ANTemplateCreateFromNTemplate(const NChar * szTot, const NChar * szDai, const NChar * szOri, const NChar * szTcn,
	NBool type9RecordFmt, HNTemplate hNTemplate, NUInt flags, HANTemplate * phTemplate);
#endif
#define ANTemplateCreateFromNTemplate N_FUNC_AW(ANTemplateCreateFromNTemplate)

NResult N_API ANTemplateCreateFromNTemplateExN(NVersion_ version, HNString hTot, HNString hDai, HNString hOri, HNString hTcn,
	NBool type9RecordFmt, HNTemplate hNTemplate, NUInt flags, HANTemplate * phTemplate);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANTemplateCreateFromNTemplateExA(NVersion_ version, const NAChar * szTot, const NAChar * szDai, const NAChar * szOri, const NAChar * szTcn,
	NBool type9RecordFmt, HNTemplate hNTemplate, NUInt flags, HANTemplate * phTemplate);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANTemplateCreateFromNTemplateExW(NVersion_ version, const NWChar * szTot, const NWChar * szDai, const NWChar * szOri, const NWChar * szTcn,
	NBool type9RecordFmt, HNTemplate hNTemplate, NUInt flags, HANTemplate * phTemplate);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANTemplateCreateFromNTemplateEx(NVersion_ version, const NChar * szTot, const NChar * szDai, const NChar * szOri, const NChar * szTcn,
	NBool type9RecordFmt, HNTemplate hNTemplate, NUInt flags, HANTemplate * phTemplate);
#endif
#define ANTemplateCreateFromNTemplateEx N_FUNC_AW(ANTemplateCreateFromNTemplateEx)

NResult N_API ANTemplateValidate(HANTemplate hTemplate);

NResult N_API ANTemplateGetRecordCount(HANTemplate hTemplate, NInt * pValue);
NResult N_API ANTemplateGetRecordEx(HANTemplate hTemplate, NInt index, HANRecord * phValue);
NResult N_API ANTemplateGetRecordCapacity(HANTemplate hTemplate, NInt * pValue);
NResult N_API ANTemplateSetRecordCapacity(HANTemplate hTemplate, NInt value);
N_DEPRECATED("function is deprecated, use ANRecordCreate, ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddRecord(HANTemplate hTemplate, HANRecordType hRecordType, NInt idc, NUInt flags, HANRecord * phRecord);
NResult N_API ANTemplateAddRecordEx(HANTemplate hTemplate, HANRecord hRecord, NInt * pIndex);

N_DEPRECATED("function is deprecated, use ANType2RecordCreate, ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType2Record(HANTemplate hTemplate, NInt idc, NUInt flags, HANType2Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType3RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType3RecordN(HANTemplate hTemplate, NInt idc, NBool isr, NUInt isrValue, NUInt ir, NUShort hll, NUShort vll,
	ANImageCompressionAlgorithm ca, NByte vendorCA, HNBuffer hImageData, NUInt flags, HANType3Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType3RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType3Record(HANTemplate hTemplate, NInt idc, NBool isr, NUInt isrValue, NUInt ir, NUShort hll, NUShort vll,
	ANImageCompressionAlgorithm ca, NByte vendorCA, const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType3Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType3RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType3RecordFromNImage(HANTemplate hTemplate, NInt idc, NBool isr, NUInt isrValue, ANImageCompressionAlgorithm ca,
	HNImage hImage, NUInt flags, HANType3Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType3RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType3RecordFromNImageEx(HANTemplate hTemplate, NInt idc, NBool isr, NUInt isrValue, ANImageCompressionAlgorithm ca,
	HNImage hImage, NUInt flags, HANType3Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType4RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType4RecordN(HANTemplate hTemplate, NInt idc, NBool isr, NUInt isrValue, NUInt ir, NUShort hll, NUShort vll,
	ANImageCompressionAlgorithm ca, NByte vendorCA, HNBuffer hImageData, NUInt flags, HANType4Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType4RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType4Record(HANTemplate hTemplate, NInt idc, NBool isr, NUInt isrValue, NUInt ir, NUShort hll, NUShort vll,
	ANImageCompressionAlgorithm ca, NByte vendorCA, const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType4Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType4RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType4RecordFromNImage(HANTemplate hTemplate, NInt idc, NBool isr, NUInt isrValue, ANImageCompressionAlgorithm ca,
	HNImage hImage, NUInt flags, HANType4Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType4RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType4RecordFromNImageEx(HANTemplate hTemplate, NInt idc, NBool isr, NUInt isrValue, ANImageCompressionAlgorithm ca,
	HNImage hImage, NUInt flags, HANType4Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType5RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType5RecordN(HANTemplate hTemplate, NInt idc, NBool isr, NUInt isrValue, NUInt ir, NUShort hll, NUShort vll,
	ANBinaryImageCompressionAlgorithm ca, NByte vendorCA, HNBuffer hImageData, NUInt flags, HANType5Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType5RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType5Record(HANTemplate hTemplate, NInt idc, NBool isr, NUInt isrValue, NUInt ir, NUShort hll, NUShort vll,
	ANBinaryImageCompressionAlgorithm ca, NByte vendorCA, const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType5Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType5RecordCreateFromNImage, ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType5RecordFromNImage(HANTemplate hTemplate, NInt idc, NBool isr, NUInt isrValue, ANBinaryImageCompressionAlgorithm ca,
	HNImage hImage, NUInt flags, HANType5Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType5RecordCreateFromNImage, ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType5RecordFromNImageEx(HANTemplate hTemplate, NInt idc, NBool isr, NUInt isrValue, ANBinaryImageCompressionAlgorithm ca,
	HNImage hImage, NUInt flags, HANType5Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType6RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType6RecordN(HANTemplate hTemplate, NInt idc, NBool isr, NUInt isrValue, NUInt ir, NUShort hll, NUShort vll,
	ANBinaryImageCompressionAlgorithm ca, NByte vendorCA, HNBuffer hImageData, NUInt flags, HANType6Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType6RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType6Record(HANTemplate hTemplate, NInt idc, NBool isr, NUInt isrValue, NUInt ir, NUShort hll, NUShort vll,
	ANBinaryImageCompressionAlgorithm ca, NByte vendorCA, const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType6Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType6RecordCreateFromNImage, ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType6RecordFromNImage(HANTemplate hTemplate, NInt idc, NBool isr, NUInt isrValue, ANBinaryImageCompressionAlgorithm ca,
	HNImage hImage, NUInt flags, HANType6Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType6RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType6RecordFromNImageEx(HANTemplate hTemplate, NInt idc, NBool isr, NUInt isrValue, ANBinaryImageCompressionAlgorithm ca,
	HNImage hImage, NUInt flags, HANType6Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType7RecordCreate, ANRecordSetDataN, ANType1RecordSetNativeScanningResolution, ANType1RecordSetNominalTransmittingResolution and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType7RecordN(HANTemplate hTemplate, NInt idc, NUInt isr, NUInt ir,
	HNBuffer hImageData, NUInt flags, HANType7Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType7RecordCreate, ANRecordSetDataEx, ANType1RecordSetNativeScanningResolution, ANType1RecordSetNominalTransmittingResolution and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType7Record(HANTemplate hTemplate, NInt idc, NUInt isr, NUInt ir,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType7Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType8RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType8RecordN(HANTemplate hTemplate, NInt idc, ANSignatureRepresentationType srt, NBool isr, NUInt isrValue, NUInt ir, NUShort hll, NUShort vll,
	HNBuffer hImageData, NUInt flags, HANType8Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType8RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType8Record(HANTemplate hTemplate, NInt idc, ANSignatureRepresentationType srt, NBool isr, NUInt isrValue, NUInt ir, NUShort hll, NUShort vll,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType8Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType8RecordCreateFromVectors and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType8RecordFromVectors(HANTemplate hTemplate, NInt idc, NUInt isr, NUInt ir,
	const struct ANPenVector_ * arPenVectors, NInt penVectorCount, NUInt flags, HANType8Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType8RecordCreateFromNImage and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType8RecordFromNImage(HANTemplate hTemplate, NInt idc, ANSignatureRepresentationType srt, NBool isr, NUInt isrValue,
	HNImage hImage, NUInt flags, HANType8Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType8RecordCreateFromNImage and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType8RecordFromNImageEx(HANTemplate hTemplate, NInt idc, ANSignatureRepresentationType srt, NBool isr, NUInt isrValue,
	HNImage hImage, NUInt flags, HANType8Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType9RecordCreate, ANType9RecordSetImpressionType, ANType9RecordSetMinutiaeFormat, ANType9RecordSetHasMinutiae, ANType9RecordSetHasMinutiaeRidgeCounts, ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType9Record(HANTemplate hTemplate, NInt idc, BdifFPImpressionType imp, NBool fmt, NBool hasMinutiae, NBool rdg, NBool hasMinutiaeRidgeCountsIndicator,
	NUInt flags, HANType9Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType9RecordCreateFromNFRecord, ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType9RecordFromNFRecord(HANTemplate hTemplate, NInt idc, NBool fmt, HNFRecord hNFRecord,
	NUInt flags, HANType9Record * phRecord);

N_DEPRECATED("function is deprecated, use ANType10RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType10RecordN(HANTemplate hTemplate, NInt idc, ANImageType imt, HNString hSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, ANImageColorSpace csp, HNString hSmt,
	HNBuffer hImageData, NUInt flags, HANType10Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType10RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType10RecordSSN(HANTemplate hTemplate, NInt idc, ANImageType imt, HNString hSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, ANImageColorSpace csp, HNString hSmt,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType10Record * phRecord);
#ifndef N_NO_ANSI_FUNC
N_DEPRECATED("function is deprecated, use ANType10RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType10RecordA(HANTemplate hTemplate, NInt idc, ANImageType imt, const NAChar * szSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, ANImageColorSpace csp, const NAChar * szSmt,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType10Record * phRecord);
#endif
#ifndef N_NO_UNICODE
N_DEPRECATED("function is deprecated, use ANType10RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType10RecordW(HANTemplate hTemplate, NInt idc, ANImageType imt, const NWChar * szSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, ANImageColorSpace csp, const NWChar * szSmt,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType10Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
N_DEPRECATED("function is deprecated, use ANType10RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType10Record(HANTemplate hTemplate, NInt idc, ANImageType imt, const NChar * szSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, ANImageColorSpace csp, const NChar * szSmt,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType10Record * phRecord);
#endif
#define ANTemplateAddType10Record N_FUNC_AW(ANTemplateAddType10Record)

N_DEPRECATED("function is deprecated, use ANType10RecordCreateFromNImageN and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType10RecordFromNImageN(HANTemplate hTemplate, NInt idc, ANImageType imt, HNString hSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga, HNString hSmt,
	HNImage hImage, NUInt flags, HANType10Record * phRecord);
#ifndef N_NO_ANSI_FUNC
N_DEPRECATED("function is deprecated, use ANType10RecordCreateFromNImageA and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType10RecordFromNImageA(HANTemplate hTemplate, NInt idc, ANImageType imt, const NAChar * szSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga, const NAChar * szSmt,
	HNImage hImage, NUInt flags, HANType10Record * phRecord);
#endif
#ifndef N_NO_UNICODE
N_DEPRECATED("function is deprecated, use ANType10RecordCreateFromNImageW and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType10RecordFromNImageW(HANTemplate hTemplate, NInt idc, ANImageType imt, const NWChar * szSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga, const NWChar * szSmt,
	HNImage hImage, NUInt flags, HANType10Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
N_DEPRECATED("function is deprecated, use ANType10RecordCreateFromNImage and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType10RecordFromNImage(HANTemplate hTemplate, NInt idc, ANImageType imt, const NChar * szSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga, const NChar * szSmt,
	HNImage hImage, NUInt flags, HANType10Record * phRecord);
#endif
#define ANTemplateAddType10RecordFromNImage N_FUNC_AW(ANTemplateAddType10RecordFromNImage)

N_DEPRECATED("function is deprecated, use ANType13RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType13RecordN(HANTemplate hTemplate, NInt idc, BdifFPImpressionType imp, HNString hSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx,
	HNBuffer hImageData, NUInt flags, HANType13Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType13RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType13RecordSN(HANTemplate hTemplate, NInt idc, BdifFPImpressionType imp, HNString hSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType13Record * phRecord);
#ifndef N_NO_ANSI_FUNC
N_DEPRECATED("function is deprecated, use ANType13RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType13RecordA(HANTemplate hTemplate, NInt idc, BdifFPImpressionType imp, const NAChar * szSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType13Record * phRecord);
#endif
#ifndef N_NO_UNICODE
N_DEPRECATED("function is deprecated, use ANType13RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType13RecordW(HANTemplate hTemplate, NInt idc, BdifFPImpressionType imp, const NWChar * szSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType13Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
N_DEPRECATED("function is deprecated, use ANType13RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType13Record(HANTemplate hTemplate, NInt idc, BdifFPImpressionType imp, const NChar * szSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType13Record * phRecord);
#endif
#define ANTemplateAddType13Record N_FUNC_AW(ANTemplateAddType13Record)

N_DEPRECATED("function is deprecated, use ANType13RecordCreateFromNImageN and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType13RecordFromNImageN(HANTemplate hTemplate, NInt idc, BdifFPImpressionType imp, HNString hSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType13Record * phRecord);
#ifndef N_NO_ANSI_FUNC
N_DEPRECATED("function is deprecated, use ANType13RecordCreateFromNImageA and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType13RecordFromNImageA(HANTemplate hTemplate, NInt idc, BdifFPImpressionType imp, const NAChar * szSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType13Record * phRecord);
#endif
#ifndef N_NO_UNICODE
N_DEPRECATED("function is deprecated, use ANType13RecordCreateFromNImageW and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType13RecordFromNImageW(HANTemplate hTemplate, NInt idc, BdifFPImpressionType imp, const NWChar * szSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType13Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
N_DEPRECATED("function is deprecated, use ANType13RecordCreateFromNImage and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType13RecordFromNImage(HANTemplate hTemplate, NInt idc, BdifFPImpressionType imp, const NChar * szSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType13Record * phRecord);
#endif
#define ANTemplateAddType13RecordFromNImage N_FUNC_AW(ANTemplateAddType13RecordFromNImage)

N_DEPRECATED("function is deprecated, use ANType14RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType14RecordN(HANTemplate hTemplate, NInt idc, HNString hSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx,
	HNBuffer hImageData, NUInt flags, HANType14Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType14RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType14RecordSN(HANTemplate hTemplate, NInt idc, HNString hSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType14Record * phRecord);
#ifndef N_NO_ANSI_FUNC
N_DEPRECATED("function is deprecated, use ANType14RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType14RecordA(HANTemplate hTemplate, NInt idc, const NAChar * szSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType14Record * phRecord);
#endif
#ifndef N_NO_UNICODE
N_DEPRECATED("function is deprecated, use ANType14RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType14RecordW(HANTemplate hTemplate, NInt idc, const NWChar * szSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType14Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
N_DEPRECATED("function is deprecated, use ANType13RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType14Record(HANTemplate hTemplate, NInt idc, const NChar * szSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType14Record * phRecord);
#endif
#define ANTemplateAddType14Record N_FUNC_AW(ANTemplateAddType14Record)

N_DEPRECATED("function is deprecated, use ANType14RecordCreateFromNImageN and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType14RecordFromNImageN(HANTemplate hTemplate, NInt idc, HNString hSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType14Record * phRecord);
#ifndef N_NO_ANSI_FUNC
N_DEPRECATED("function is deprecated, use ANType14RecordCreateFromNImageA and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType14RecordFromNImageA(HANTemplate hTemplate, NInt idc, const NAChar * szSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType14Record * phRecord);
#endif
#ifndef N_NO_UNICODE
N_DEPRECATED("function is deprecated, use ANType14RecordCreateFromNImageW and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType14RecordFromNImageW(HANTemplate hTemplate, NInt idc, const NWChar * szSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType14Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
N_DEPRECATED("function is deprecated, use ANType14RecordCreateFromNImage and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType14RecordFromNImage(HANTemplate hTemplate, NInt idc, const NChar * szSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType14Record * phRecord);
#endif
#define ANTemplateAddType14RecordFromNImage N_FUNC_AW(ANTemplateAddType14RecordFromNImage)

N_DEPRECATED("function is deprecated, use ANType15RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType15RecordN(HANTemplate hTemplate, NInt idc, HNString hSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx,
	HNBuffer hImageData, NUInt flags, HANType15Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType15RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType15RecordSN(HANTemplate hTemplate, NInt idc, HNString hSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType15Record * phRecord);
#ifndef N_NO_ANSI_FUNC
N_DEPRECATED("function is deprecated, use ANType15RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType15RecordA(HANTemplate hTemplate, NInt idc, const NAChar * szSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType15Record * phRecord);
#endif
#ifndef N_NO_UNICODE
N_DEPRECATED("function is deprecated, use ANType15RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType15RecordW(HANTemplate hTemplate, NInt idc, const NWChar * szSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType15Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
N_DEPRECATED("function is deprecated, use ANType15RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType15Record(HANTemplate hTemplate, NInt idc, const NChar * szSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType15Record * phRecord);
#endif
#define ANTemplateAddType15Record N_FUNC_AW(ANTemplateAddType15Record)

N_DEPRECATED("function is deprecated, use ANType15RecordCreateFromNImageN and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType15RecordFromNImageN(HANTemplate hTemplate, NInt idc, HNString hSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType15Record * phRecord);
#ifndef N_NO_ANSI_FUNC
N_DEPRECATED("function is deprecated, use ANType15RecordCreateFromNImageA and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType15RecordFromNImageA(HANTemplate hTemplate, NInt idc, const NAChar * szSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType15Record * phRecord);
#endif
#ifndef N_NO_UNICODE
N_DEPRECATED("function is deprecated, use ANType15RecordCreateFromNImageW and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType15RecordFromNImageW(HANTemplate hTemplate, NInt idc, const NWChar * szSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType15Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
N_DEPRECATED("function is deprecated, use ANType15RecordCreateFromNImage and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType15RecordFromNImage(HANTemplate hTemplate, NInt idc, const NChar * szSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType15Record * phRecord);
#endif
#define ANTemplateAddType15RecordFromNImage N_FUNC_AW(ANTemplateAddType15RecordFromNImage)

N_DEPRECATED("function is deprecated, use ANType16RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType16RecordN(HANTemplate hTemplate, NInt idc, HNString hUdi, HNString hSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx, ANImageColorSpace csp,
	HNBuffer hImageData, NUInt flags, HANType16Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType16RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType16RecordUSN(HANTemplate hTemplate, NInt idc, HNString hUdi, HNString hSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx, ANImageColorSpace csp,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType16Record * phRecord);
#ifndef N_NO_ANSI_FUNC
N_DEPRECATED("function is deprecated, use ANType16RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType16RecordA(HANTemplate hTemplate, NInt idc, const NAChar * szUdi, const NAChar * szSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx, ANImageColorSpace csp,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType16Record * phRecord);
#endif
#ifndef N_NO_UNICODE
N_DEPRECATED("function is deprecated, use ANType16RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType16RecordW(HANTemplate hTemplate, NInt idc, const NWChar * szUdi, const NWChar * szSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx, ANImageColorSpace csp,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType16Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
N_DEPRECATED("function is deprecated, use ANType16RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType16Record(HANTemplate hTemplate, NInt idc, const NChar * szUdi, const NChar * szSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx, ANImageColorSpace csp,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType16Record * phRecord);
#endif
#define ANTemplateAddType16Record N_FUNC_AW(ANTemplateAddType16Record)

N_DEPRECATED("function is deprecated, use ANType16RecordCreateFromNImageN and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType16RecordFromNImageN(HANTemplate hTemplate, NInt idc, HNString hUdi, HNString hSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType16Record * phRecord);
#ifndef N_NO_ANSI_FUNC
N_DEPRECATED("function is deprecated, use ANType16RecordCreateFromNImageA and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType16RecordFromNImageA(HANTemplate hTemplate, NInt idc, const NAChar * szUdi, const NAChar * szSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType16Record * phRecord);
#endif
#ifndef N_NO_UNICODE
N_DEPRECATED("function is deprecated, use ANType16RecordCreateFromNImageW and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType16RecordFromNImageW(HANTemplate hTemplate, NInt idc, const NWChar * szUdi, const NWChar * szSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType16Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
N_DEPRECATED("function is deprecated, use ANType16RecordCreateFromNImage and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType16RecordFromNImage(HANTemplate hTemplate, NInt idc, const NChar * szUdi, const NChar * szSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType16Record * phRecord);
#endif
#define ANTemplateAddType16RecordFromNImage N_FUNC_AW(ANTemplateAddType16RecordFromNImage)

N_DEPRECATED("function is deprecated, use ANType17RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType17RecordN(HANTemplate hTemplate, NInt idc, HNString hSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx, ANImageColorSpace csp,
	HNBuffer hImageData, NUInt flags, HANType17Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType17RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType17RecordSN(HANTemplate hTemplate, NInt idc, HNString hSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx, ANImageColorSpace csp,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType17Record * phRecord);
#ifndef N_NO_ANSI_FUNC
N_DEPRECATED("function is deprecated, use ANType17RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType17RecordA(HANTemplate hTemplate, NInt idc, const NAChar * szSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx, ANImageColorSpace csp,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType17Record * phRecord);
#endif
#ifndef N_NO_UNICODE
N_DEPRECATED("function is deprecated, use ANType17RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType17RecordW(HANTemplate hTemplate, NInt idc, const NWChar * szSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx, ANImageColorSpace csp,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType17Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
N_DEPRECATED("function is deprecated, use ANType16RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType17Record(HANTemplate hTemplate, NInt idc, const NChar * szSrc,
	NUShort hll, NUShort vll, BdifScaleUnits slc, NUShort hps, NUShort vps, ANImageCompressionAlgorithm cga, NByte bpx, ANImageColorSpace csp,
	const void * pImageData, NSizeType imageDataLength, NUInt flags, HANType17Record * phRecord);
#endif
#define ANTemplateAddType17Record N_FUNC_AW(ANTemplateAddType17Record)

N_DEPRECATED("function is deprecated, use ANType17RecordCreateFromNImageN and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType17RecordFromNImageN(HANTemplate hTemplate, NInt idc, HNString hSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType17Record * phRecord);
#ifndef N_NO_ANSI_FUNC
N_DEPRECATED("function is deprecated, use ANType17RecordCreateFromNImageA and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType17RecordFromNImageA(HANTemplate hTemplate, NInt idc, const NAChar * szSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType17Record * phRecord);
#endif
#ifndef N_NO_UNICODE
N_DEPRECATED("function is deprecated, use ANType17RecordCreateFromNImageW and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType17RecordFromNImageW(HANTemplate hTemplate, NInt idc, const NWChar * szSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType17Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
N_DEPRECATED("function is deprecated, use ANType17RecordCreateFromNImage and ANTemplateAddRecordEx instead")
NResult ANTemplateAddType17RecordFromNImage(HANTemplate hTemplate, NInt idc, const NChar * szSrc,
	BdifScaleUnits slc, ANImageCompressionAlgorithm cga,
	HNImage hImage, NUInt flags, HANType17Record * phRecord);
#endif
#define ANTemplateAddType17RecordFromNImage N_FUNC_AW(ANTemplateAddType17RecordFromNImage)

N_DEPRECATED("function is deprecated, use ANType99RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType99RecordN(HANTemplate hTemplate, NInt idc, HNString hSrc, NVersion_ hdv, ANBiometricType bty, NUShort bfo, NUShort bft,
	HNBuffer hBdb, NUInt flags, HANType99Record * phRecord);
N_DEPRECATED("function is deprecated, use ANType99RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType99RecordSN(HANTemplate hTemplate, NInt idc, HNString hSrc, NVersion_ hdv, ANBiometricType bty, NUShort bfo, NUShort bft,
	const void * pBdb, NSizeType bdbLength, NUInt flags, HANType99Record * phRecord);
#ifndef N_NO_ANSI_FUNC
N_DEPRECATED("function is deprecated, use ANType99RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType99RecordA(HANTemplate hTemplate, NInt idc, const NAChar * szSrc, NVersion_ hdv, ANBiometricType bty, NUShort bfo, NUShort bft,
	const void * pBdb, NSizeType bdbLength, NUInt flags, HANType99Record * phRecord);
#endif
#ifndef N_NO_UNICODE
N_DEPRECATED("function is deprecated, use ANType99RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType99RecordW(HANTemplate hTemplate, NInt idc, const NWChar * szSrc, NVersion_ hdv, ANBiometricType bty, NUShort bfo, NUShort bft,
	const void * pBdb, NSizeType bdbLength, NUInt flags, HANType99Record * phRecord);
#endif
#ifdef N_DOCUMENTATION
N_DEPRECATED("function is deprecated, use ANType99RecordCreate, set attributes and ANTemplateAddRecordEx instead")
NResult N_API ANTemplateAddType99Record(HANTemplate hTemplate, NInt idc, const NChar * szSrc, NVersion hdv, ANBiometricType bty, NUShort bfo, NUShort bft,
	const void * pBdb, NSizeType bdbLength, NUInt flags, HANType99Record * phRecord);
#endif
#define ANTemplateAddType99Record N_FUNC_AW(ANTemplateAddType99Record)

N_DEPRECATED("function is deprecated, use ANTemplateRemoveRecordAt instead")
NResult N_API ANTemplateRemoveRecord(HANTemplate hTemplate, NInt index);
NResult N_API ANTemplateRemoveRecordAt(HANTemplate hTemplate, NInt index);
NResult N_API ANTemplateClearRecords(HANTemplate hTemplate);

NResult N_API ANTemplateSaveToFileN(HANTemplate hTemplate, HNString hFileName, NUInt flags);
#ifndef N_NO_ANSI_FUNC
NResult N_API ANTemplateSaveToFileA(HANTemplate hTemplate, const NAChar * szFileName, NUInt flags);
#endif
#ifndef N_NO_UNICODE
NResult N_API ANTemplateSaveToFileW(HANTemplate hTemplate, const NWChar * szFileName, NUInt flags);
#endif
#ifdef N_DOCUMENTATION
NResult N_API ANTemplateSaveToFile(HANTemplate hTemplate, const NChar * szFileName, NUInt flags);
#endif
#define ANTemplateSaveToFile N_FUNC_AW(ANTemplateSaveToFile)

NResult N_API ANTemplateToNTemplate(HANTemplate hTemplate, NUInt flags, HNTemplate * phNTemplate);

NResult N_API ANTemplateGetValidationLevel(HANTemplate hTemplate, ANValidationLevel * pValue);
NResult N_API ANTemplateGetVersion(HANTemplate hTemplate, NVersion_ * pValue);
NResult N_API ANTemplateSetVersion(HANTemplate hTemplate, NVersion_ value);

#ifdef N_CPP
}
#endif

#endif // !AN_TEMPLATE_H_INCLUDED
