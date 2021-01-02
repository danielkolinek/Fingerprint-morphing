#ifndef CBEFF_RECORD_H_INCLUDED
#define CBEFF_RECORD_H_INCLUDED

#include <Core/NExpandableObject.h>
#include <Biometrics/Standards/BdifTypes.h>
#include <Biometrics/Standards/CbeffBiometricOrganizations.h>
#include <Biometrics/Standards/CbeffBdbFormatIdentifiers.h>
#include <Biometrics/Standards/CbeffPatronFormatIdentifiers.h>
#include <Biometrics/Standards/CbeffProductIdentifiers.h>
#include <Biometrics/Standards/CbeffDeviceIdentifiers.h>
#include <Biometrics/NTemplate.h>
#include <Biometrics/Standards/FMRecord.h>
#include <Biometrics/Standards/FIRecord.h>
#include <Biometrics/Standards/FCRecord.h>
#include <Biometrics/Standards/IIRecord.h>
#include <Biometrics/Standards/ANTemplate.h>
#include <Biometrics/Standards/ANRecord.h>
#include <SmartCards/BerTag.h>
#include <SmartCards/NSmartCardsBiometry.h>
#include <SmartCards/ConstructedBerTlv.h>
#include <SmartCards/PrimitiveBerTlv.h>
#include <SmartCards/NSmartCardsDataElements.h>
#include <Biometrics/Standards/FMCRecord.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(CbeffRecord, NExpandableObject)

typedef enum CbeffIntegrityOptions_
{
	cbeffioMAC = 0,
	cbeffioSigned = 1
} CbeffIntegrityOptions;

N_DECLARE_TYPE(CbeffIntegrityOptions)

// Defines the type of biometric technology
typedef enum CbeffBiometricType_
{
	// ANSI/INCITS 398:2008, ISO/IEC 19785-1:2006, ISO/IEC 19785-1:2006/Amd.1:2010, ISO/IEC 19785-3:2007, ISO/IEC 19785-3:2007/Amd.1:2010  biometric types
	cbeffbtNoInformationGiven         = 0x00000000,
	cbeffbtMultipleBiometricTypesUsed = 0x00000001,
	cbeffbtFace                       = 0x00000002,
	cbeffbtVoice                      = 0x00000004,
	cbeffbtFinger                     = 0x00000008,
	cbeffbtIris                       = 0x00000010,
	cbeffbtRetina                     = 0x00000020,
	cbeffbtHandGeometry               = 0x00000040,
	cbeffbtSignatureSign              = 0x00000080,
	cbeffbtKeystrokeDynamics          = 0x00000100,
	cbeffbtLipMovement                = 0x00000200,
	cbeffbtThermalFaceImage           = 0x00000400, // ISO/IEC and ANSI/INCITS TLV-encoded patron formats specific
	cbeffbtThermalHandImage           = 0x00000800, // ISO/IEC and ANSI/INCITS TLV-encoded patron formats specific
	cbeffbtGait                       = 0x00001000,
	cbeffbtVein                       = 0x00002000,
	cbeffbtDNA                        = 0x00004000,
	cbeffbtEar                        = 0x00008000,
	cbeffbtFoot                       = 0x00010000,
	cbeffbtScent                      = 0x00020000,
	cbeffbtFingerGeometry             = 0x01000000, // ISO/IEC and ANSI/INCITS TLV-encoded patron formats specific
	cbeffbtPalmPrint                  = 0x02000000, // ISO/IEC and ANSI/INCITS TLV-encoded patron formats specific
	// ANSI/INCITS 398:2008 biometric types
	cbeffbtOther                      = 0x40000000,
	cbeffbtPassword                   = 0x80000000
} CbeffBiometricType;

N_DECLARE_TYPE(CbeffBiometricType)

// More specifically defines the type of biometric data
typedef enum CbeffBiometricSubType_
{
	// ANSI/INCITS 398:2008, ISO/IEC 19785-1:2006, ISO/IEC 19785-1:2006/Amd.1:2010 biometric subtypes
	cbeffbstNoInformationGiven = 0x00,
	cbeffbstLeft               = 0x01,
	cbeffbstRight              = 0x02,

	// ANSI/INCITS 398:2008 biometric subtypes
	cbeffbstThumb          = 0x04,
	cbeffbstPointerFinger  = 0x08,
	cbeffbstMiddleFinger   = 0x10,
	cbeffbstRingFinger     = 0x20,
	cbeffbstLittleFinger   = 0x40,
	cbeffbstVeinMask       = 0x80,
	cbeffbstVeinPalm       = 0x04,
	cbeffbstVeinBackOfHand = 0x08,
	cbeffbstVeinWrist      = 0x10,

	// ISO/IEC 19785-1:2006, ISO/IEC 19785-1:2006/Amd.1:2010 biometric subtypes
	cbeffbstLeftThumb          = cbeffbstLeft | cbeffbstThumb,
	cbeffbstLeftPointerFinger  = cbeffbstLeft | cbeffbstPointerFinger,
	cbeffbstLeftMiddleFinger   = cbeffbstLeft | cbeffbstMiddleFinger,
	cbeffbstLeftRingFinger     = cbeffbstLeft | cbeffbstRingFinger,
	cbeffbstLeftLittleFinger   = cbeffbstLeft | cbeffbstLittleFinger,
	cbeffbstRightThumb         = cbeffbstRight | cbeffbstThumb,
	cbeffbstRightPointerFinger = cbeffbstRight | cbeffbstPointerFinger,
	cbeffbstRightMiddleFinger  = cbeffbstRight | cbeffbstMiddleFinger,
	cbeffbstRightRingFinger    = cbeffbstRight | cbeffbstRingFinger,
	cbeffbstRightLittleFinger  = cbeffbstRight | cbeffbstLittleFinger,
	cbeffbstLeftPalm           = cbeffbstLeft | cbeffbstVeinMask | cbeffbstVeinPalm,
	cbeffbstLeftBackOfHand     = cbeffbstLeft | cbeffbstVeinMask | cbeffbstVeinBackOfHand,
	cbeffbstLeftWrist          = cbeffbstLeft | cbeffbstVeinMask | cbeffbstVeinWrist,
	cbeffbstRightPalm          = cbeffbstRight | cbeffbstVeinMask | cbeffbstVeinPalm,
	cbeffbstRightBackOfHand    = cbeffbstRight | cbeffbstVeinMask | cbeffbstVeinBackOfHand,
	cbeffbstRightWrist         = cbeffbstRight | cbeffbstVeinMask | cbeffbstVeinWrist,
} CbeffBiometricSubType;

N_DECLARE_TYPE(CbeffBiometricSubType)

// Specifies the intended use of the data
typedef enum CbeffPurpose_
{
	cbeffpNoInformationGiven          = 0x00,
	cbeffpVerify                      = 0x01,
	cbeffpIdentify                    = 0x02,
	cbeffpEnroll                      = 0x03,
	cbeffpEnrollForVerificationOnly   = 0x04,
	cbeffpEnrollForIdentificationOnly = 0x05,
	cbeffpAudit                       = 0x06
} CbeffPurpose;

N_DECLARE_TYPE(CbeffPurpose)

// ISO/IEC 19785-1:2006 CBEFF BDB processed level, ANSI/INCITS 398:2008 CBEFF Biometric Data Type
typedef enum CbeffProcessedLevel_
{
	cbeffplNoInformationGiven = 0x00,
	cbeffplRaw = 0x01,
	cbeffplIntermediate = 0x02,
	cbeffplProcessed = 0x04,
	cbeffplScore = 0x08,
	cbeffplDecision = 0x09,
	cbeffplBiographic = 0x0A
} CbeffProcessedLevel;

N_DECLARE_TYPE(CbeffProcessedLevel)

struct CbeffTimeInterval_
{
	NDateTime from;
	NDateTime to;
};
#ifndef CBEFF_RECORD_HPP_INCLUDED
typedef struct CbeffTimeInterval_ CbeffTimeInterval;
#endif

N_DECLARE_TYPE(CbeffTimeInterval)

#define CBEFF_PATRON_FORMAT_INCITS_TC_M1_BIOMETRICS_A                              NMakeDWord(CBEFF_PFI_INCITS_TC_M1_BIOMETRICS_A, CBEFF_BO_INCITS_TC_M1_BIOMETRICS)
#define CBEFF_PATRON_FORMAT_INCITS_TC_M1_BIOMETRICS_B                              NMakeDWord(CBEFF_PFI_INCITS_TC_M1_BIOMETRICS_B, CBEFF_BO_INCITS_TC_M1_BIOMETRICS)
#define CBEFF_PATRON_FORMAT_NIST_D                                                 NMakeDWord(CBEFF_PFI_NIST_D, CBEFF_BO_NIST)
#define CBEFF_PATRON_FORMAT_ISO_IEC_JTC_1_SC_37_BIOMETRICS_SIMPLE_BYTE_ORIENTED    NMakeDWord(CBEFF_PFI_ISO_IEC_JTC_1_SC_37_BIOMETRICS_SIMPLE_BYTE_ORIENTED, CBEFF_BO_ISO_IEC_JTC_1_SC_37_BIOMETRICS)
#define CBEFF_PATRON_FORMAT_ISO_IEC_JTC_1_SC_37_BIOMETRICS_PRESENCE_BYTE_ORIENTED  NMakeDWord(CBEFF_PFI_ISO_IEC_JTC_1_SC_37_BIOMETRICS_PRESENCE_BYTE_ORIENTED, CBEFF_BO_ISO_IEC_JTC_1_SC_37_BIOMETRICS)
#define CBEFF_PATRON_FORMAT_ISO_IEC_JTC_1_SC_37_BIOMETRICS_TLV_ENCODED             NMakeDWord(CBEFF_PFI_ISO_IEC_JTC_1_SC_37_BIOMETRICS_TLV_ENCODED, CBEFF_BO_ISO_IEC_JTC_1_SC_37_BIOMETRICS)
#define CBEFF_PATRON_FORMAT_ISO_IEC_JTC_1_SC_37_BIOMETRICS_COMPLEX                 NMakeDWord(CBEFF_PFI_ISO_IEC_JTC_1_SC_37_BIOMETRICS_COMPLEX, CBEFF_BO_ISO_IEC_JTC_1_SC_37_BIOMETRICS)
#define CBEFF_PATRON_FORMAT_ISO_IEC_JTC_1_SC_37_BIOMETRICS_WITH_ADD_ELEM           NMakeDWord(CBEFF_PFI_ISO_IEC_JTC_1_SC_37_BIOMETRICS_COMPLEX_WITH_ADD_ELEM, CBEFF_BO_ISO_IEC_JTC_1_SC_37_BIOMETRICS)

// Patron-defined (not CBEFF-defined) data elements
#define CBEFF_PDDE_ISO_IEC_JTC_1_SC_37_BIOMETRICS_TLV_ENCODED_ALGORITHM_REFERENCE            N_T("AlgorithmReference")
#define CBEFF_PDDE_ISO_IEC_JTC_1_SC_37_BIOMETRICS_TLV_ENCODED_REFERENCE_DATA_QUALIFIER       N_T("ReferenceDataQualifier")
#define CBEFF_PDDE_ISO_IEC_JTC_1_SC_37_BIOMETRICS_TLV_ENCODED_BIOMETRIC_ALGORITHM_PARAMETERS N_T("BiometricAlgorithmParameters")
// Additionally defined data elements for on-card matching only (introduced for TLV-encoded format by ISO/IEC JTC 1/SC17 in ISO/IEC 24787:2010)
#define CBEFF_ADDE_ISO_IEC_JTC_1_SC_37_BIOMETRICS_TLV_ENCODED_CONFIGURATION_DATA             N_T("ConfigurationData")

#define CBEFF_PDDE_NIST_D_FASCN            N_T("Fascn")

#define CBEFF_FLAG_SKIP_DEFAULT_VALUES              0x00100000

#define CBEFF_PF_TLV_FLAG_USE_FOR_ON_CARD_MATCHING      0x00010000
#define CBEFF_PF_TLV_FLAG_ALLOW_NON_BER_TLV_BDB_DATA    0x00020000
#define CBEFF_PF_TLV_FLAG_USE_CONFIGURATION_DATA        0x00040000

NResult N_API CbeffRecordCreate(NUInt patronFormat, HCbeffRecord * phRecord);
NResult N_API CbeffRecordIsSupportedCbeffFormat(NUInt patronFormat, NBool * pValue);

N_DEPRECATED("function is deprecated, use CbeffRecordCreateFromStreamEx instead")
NResult N_API CbeffRecordCreateFromStream(HNStream hStream, NUInt patronFormat, HCbeffRecord * phRecord);
NResult N_API CbeffRecordCreateFromStreamEx(HNStream hStream, NUInt patronFormat, NUInt flags, HCbeffRecord * phRecord);
N_DEPRECATED("function is deprecated, use CbeffRecordCreateFromMemoryNEx instead")
NResult N_API CbeffRecordCreateFromMemoryN(HNBuffer hBuffer, NUInt patronFormat, NSizeType * pSize, HCbeffRecord * phRecord);
NResult N_API CbeffRecordCreateFromMemoryNEx(HNBuffer hBuffer, NUInt patronFormat, NUInt flags, NSizeType * pSize, HCbeffRecord * phRecord);
N_DEPRECATED("function is deprecated, use CbeffRecordCreateFromMemoryEx instead")
NResult N_API CbeffRecordCreateFromMemory(const void * pBuffer, NSizeType bufferSize, NUInt patronFormat, NSizeType * pSize, HCbeffRecord * phRecord);
NResult N_API CbeffRecordCreateFromMemoryEx(const void * pBuffer, NSizeType bufferSize, NUInt patronFormat, NUInt flags, NSizeType * pSize, HCbeffRecord * phRecord);

NResult N_API CbeffRecordCreateFromDataN(NUInt bdbFormat, HNBuffer hBdbBuffer, NUInt patronFormat, HCbeffRecord * phRecord);
NResult N_API CbeffRecordCreateFromDataNEx(NUInt bdbFormat, HNBuffer hBdbBuffer, NUInt patronFormat, NUInt flags, HCbeffRecord * phRecord);
NResult N_API CbeffRecordCreateFromData(NUInt bdbFormat, const void * pBdbBuffer, NSizeType bdbBufferSize, NUInt patronFormat, HCbeffRecord * phRecord);
NResult N_API CbeffRecordCreateFromDataEx(NUInt bdbFormat, const void * pBdbBuffer, NSizeType bdbBufferSize, NUInt patronFormat, NUInt flags, HCbeffRecord * phRecord);
N_DEPRECATED("function is deprecated, use CbeffRecordCreateFromIIRecordEx instead")
NResult N_API CbeffRecordCreateFromIIRecord(HIIRecord hIIRecord, NUInt patronFormat, HCbeffRecord * phRecord);
NResult N_API CbeffRecordCreateFromIIRecordEx(HIIRecord hIIRecord, NUInt patronFormat, NUInt flags, HCbeffRecord * phRecord);
N_DEPRECATED("function is deprecated, use CbeffRecordCreateFromFCRecordEx instead")
NResult N_API CbeffRecordCreateFromFCRecord(HFCRecord hFCRecord, NUInt patronFormat, HCbeffRecord * phRecord);
NResult N_API CbeffRecordCreateFromFCRecordEx(HFCRecord hFCRecord, NUInt patronFormat, NUInt flags, HCbeffRecord * phRecord);
N_DEPRECATED("function is deprecated, use CbeffRecordCreateFromFIRecordEx instead")
NResult N_API CbeffRecordCreateFromFIRecord(HFIRecord hFIRecord, NUInt patronFormat, HCbeffRecord * phRecord);
NResult N_API CbeffRecordCreateFromFIRecordEx(HFIRecord hFIRecord, NUInt patronFormat, NUInt flags, HCbeffRecord * phRecord);
N_DEPRECATED("function is deprecated, use CbeffRecordCreateFromFMRecordEx instead")
NResult N_API CbeffRecordCreateFromFMRecord(HFMRecord hFMRecord, NUInt patronFormat, HCbeffRecord * phRecord);
NResult N_API CbeffRecordCreateFromFMRecordEx(HFMRecord hFMRecord, NUInt patronFormat, NUInt flags, HCbeffRecord * phRecord);
NResult N_API CbeffRecordCreateFromFMCRecord(HFMCRecord hFMCRecord, NUInt patronFormat, NUInt flags, HCbeffRecord * phRecord);
N_DEPRECATED("function is deprecated, use CbeffRecordCreateFromANTemplateEx instead")
NResult N_API CbeffRecordCreateFromANTemplate(HANTemplate hANTemplate, NUInt patronFormat, HCbeffRecord * phRecord);
NResult N_API CbeffRecordCreateFromANTemplateEx(HANTemplate hANTemplate, NUInt patronFormat, NUInt flags, HCbeffRecord * phRecord);
NResult N_API CbeffRecordCreateFromANRecord(HANRecord hANRecord, NUInt patronFormat, HCbeffRecord * phRecord);

NResult N_API CbeffRecordGetPatronFormat(HCbeffRecord hRecord, NUInt * pValue);
NResult N_API CbeffRecordGetEncryption(HCbeffRecord hRecord, NBool * pValue);
NResult N_API CbeffRecordSetEncryption(HCbeffRecord hRecord, NBool value);
NResult N_API CbeffRecordGetIntegrity(HCbeffRecord hRecord, NBool * pValue);
NResult N_API CbeffRecordSetIntegrity(HCbeffRecord hRecord, NBool value);
NResult N_API CbeffRecordGetIntegrityOptions(HCbeffRecord hRecord, CbeffIntegrityOptions * pValue, NBool * pHasValue);
NResult N_API CbeffRecordSetIntegrityOptions(HCbeffRecord hRecord, const CbeffIntegrityOptions * pValue);
NResult N_API CbeffRecordGetBdbFormat(HCbeffRecord hRecord, NUInt * pValue);
NResult N_API CbeffRecordSetBdbFormat(HCbeffRecord hRecord, NUInt value);
NResult N_API CbeffRecordGetBdbBuffer(HCbeffRecord hRecord, HNBuffer * phValue);
NResult N_API CbeffRecordSetBdbBuffer(HCbeffRecord hRecord, HNBuffer hValue);
NResult N_API CbeffRecordGetBiometricType(HCbeffRecord hRecord, CbeffBiometricType * pValue);
NResult N_API CbeffRecordSetBiometricType(HCbeffRecord hRecord, CbeffBiometricType value);
NResult N_API CbeffRecordGetBiometricSubType(HCbeffRecord hRecord, CbeffBiometricSubType * pValue);
NResult N_API CbeffRecordSetBiometricSubType(HCbeffRecord hRecord, CbeffBiometricSubType value);
NResult N_API CbeffRecordGetChallengeResponse(HCbeffRecord hRecord, HNBuffer * phValue);
NResult N_API CbeffRecordSetChallengeResponse(HCbeffRecord hRecord, HNBuffer hValue);
NResult N_API CbeffRecordGetBdbCreationDate(HCbeffRecord hRecord, NDateTime_ * pValue, NBool * pHasValue);
NResult N_API CbeffRecordSetBdbCreationDate(HCbeffRecord hRecord, const NDateTime_ * pValue);
NResult N_API CbeffRecordGetBdbIndex(HCbeffRecord hRecord, HNBuffer * phValue);
NResult N_API CbeffRecordSetBdbIndex(HCbeffRecord hRecord, HNBuffer hValue);
NResult N_API CbeffRecordGetProduct(HCbeffRecord hRecord, NUInt * pValue, NBool * pHasValue);
NResult N_API CbeffRecordSetProduct(HCbeffRecord hRecord, const NUInt * pValue);
NResult N_API CbeffRecordGetCaptureDevice(HCbeffRecord hRecord, NUInt * pValue, NBool * pHasValue);
NResult N_API CbeffRecordSetCaptureDevice(HCbeffRecord hRecord, const NUInt * pValue);
NResult N_API CbeffRecordGetFeatureExtractionAlgorithm(HCbeffRecord hRecord, NUInt * pValue, NBool * pHasValue);
NResult N_API CbeffRecordSetFeatureExtractionAlgorithm(HCbeffRecord hRecord, const NUInt * pValue);
NResult N_API CbeffRecordGetComparisonAlgorithm(HCbeffRecord hRecord, NUInt * pValue, NBool * pHasValue);
NResult N_API CbeffRecordSetComparisonAlgorithm(HCbeffRecord hRecord, const NUInt * pValue);
NResult N_API CbeffRecordGetQualityAlgorithm(HCbeffRecord hRecord, NUInt * pValue, NBool * pHasValue);
NResult N_API CbeffRecordSetQualityAlgorithm(HCbeffRecord hRecord, const NUInt * pValue);
NResult N_API CbeffRecordGetCompressionAlgorithm(HCbeffRecord hRecord, NUInt * pValue, NBool * pHasValue);
NResult N_API CbeffRecordSetCompressionAlgorithm(HCbeffRecord hRecord, const NUInt * pValue);
NResult N_API CbeffRecordGetProcessedLevel(HCbeffRecord hRecord, CbeffProcessedLevel * pValue);
NResult N_API CbeffRecordSetProcessedLevel(HCbeffRecord hRecord, CbeffProcessedLevel value);
NResult N_API CbeffRecordGetPurpose(HCbeffRecord hRecord, CbeffPurpose * pValue);
NResult N_API CbeffRecordSetPurpose(HCbeffRecord hRecord, CbeffPurpose value);
NResult N_API CbeffRecordGetQuality(HCbeffRecord hRecord, NByte * pValue, NBool * pHasValue);
NResult N_API CbeffRecordSetQuality(HCbeffRecord hRecord, const NByte * pValue);
NResult N_API CbeffRecordGetBdbValidityPeriod(HCbeffRecord hRecord, struct CbeffTimeInterval_ * pValue, NBool * pHasValue);
NResult N_API CbeffRecordSetBdbValidityPeriod(HCbeffRecord hRecord, const struct CbeffTimeInterval_ * pValue);
NResult N_API CbeffRecordGetBirCreationDate(HCbeffRecord hRecord, NDateTime_ * pValue, NBool * pHasValue);
NResult N_API CbeffRecordSetBirCreationDate(HCbeffRecord hRecord, const NDateTime_ * pValue);
NResult N_API CbeffRecordGetCreator(HCbeffRecord hRecord, HNString * phValue);
NResult N_API CbeffRecordSetCreator(HCbeffRecord hRecord, HNString hValue);
NResult N_API CbeffRecordGetBirIndex(HCbeffRecord hRecord, HNBuffer * phValue);
NResult N_API CbeffRecordSetBirIndex(HCbeffRecord hRecord, HNBuffer hValue);
NResult N_API CbeffRecordGetPayload(HCbeffRecord hRecord, HNBuffer * phValue);
NResult N_API CbeffRecordSetPayload(HCbeffRecord hRecord, HNBuffer hValue);
NResult N_API CbeffRecordGetBirValidityPeriod(HCbeffRecord hRecord, struct CbeffTimeInterval_ * pValue, NBool * pHasValue);
NResult N_API CbeffRecordSetBirValidityPeriod(HCbeffRecord hRecord, const struct CbeffTimeInterval_ * pValue);
NResult N_API CbeffRecordGetCbeffVersion(HCbeffRecord hRecord, NByte * pValue);
NResult N_API CbeffRecordGetPatronHeaderVersion(HCbeffRecord hRecord, NByte * pValue);
N_DEPRECATED("function is deprecated, use NPropertyBagTryGet instead")
NResult N_API CbeffRecordGetFascnBuffer(HCbeffRecord hRecord, HNBuffer * phValue);
N_DEPRECATED("function is deprecated, use NPropertyBagSet instead")
NResult N_API CbeffRecordSetFascnBuffer(HCbeffRecord hRecord, HNBuffer hValue);
NResult N_API CbeffRecordGetSbFormat(HCbeffRecord hRecord, NUInt * pValue, NBool * pHasValue);
NResult N_API CbeffRecordSetSbFormat(HCbeffRecord hRecord, const NUInt * pValue);
NResult N_API CbeffRecordGetSbBuffer(HCbeffRecord hRecord, HNBuffer * phValue);
NResult N_API CbeffRecordSetSbBuffer(HCbeffRecord hRecord, HNBuffer hValue);

NResult N_API CbeffRecordGetRecordCount(HCbeffRecord hRecord, NInt * pValue);
NResult N_API CbeffRecordGetRecord(HCbeffRecord hRecord, NInt index, HCbeffRecord * phValue);
NResult N_API CbeffRecordGetRecords(HCbeffRecord hRecord, HCbeffRecord * * parhValues, NInt * pValueCount);
NResult N_API CbeffRecordSetRecord(HCbeffRecord hRecord, NInt index, HCbeffRecord hValue);
NResult N_API CbeffRecordAddRecord(HCbeffRecord hRecord, HCbeffRecord hValue, NInt * pIndex);
NResult N_API CbeffRecordInsertRecord(HCbeffRecord hRecord, NInt index, HCbeffRecord hValue);
NResult N_API CbeffRecordRemoveRecordAt(HCbeffRecord hRecord, NInt index);
NResult N_API CbeffRecordClearRecords(HCbeffRecord hRecord);

NResult N_API CbeffRecordToBerTlv(HCbeffRecord hRecord, NUInt flags, HBerTlv * phValue);

#ifdef N_CPP
}
#endif

#endif // !CBEFF_RECORD_H_INCLUDED
