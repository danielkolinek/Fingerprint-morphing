#ifndef N_SMART_CARDS_BIOMETRY_H_INCLUDED
#define N_SMART_CARDS_BIOMETRY_H_INCLUDED

#include <SmartCards/BerTag.h>

#ifdef N_CPP
extern "C"
{
#endif

typedef enum SCardBiometricType_
{
	scbtNone = 0x00,
	scbtMultipleBiometrics = 0x01,
	scbtFacialFeatures = 0x02,
	scbtVoice = 0x04,
	scbtFingerprint = 0x08,
	scbtIris = 0x10,
	scbtRetina = 0x20,
	scbtHandGeometry = 0x40,
	scbtSignatureDynamics = 0x80,
	scbtKeystrokeDynamics = 0x0100,
	scbtLipMovement = 0x0200,
	scbtThermalFaceImage = 0x0400,
	scbtThermalHandImage = 0x0800,
	scbtGait = 0x1000,
	scbtBodyOdor = 0x2000,
	scbtDna = 0x4000,
	scbtEarShape = 0x8000,
	scbtFingerGeometry = 0x010000,
	scbtPalmPrint = 0x020000,
	scbtVeinPattern = 0x040000,
	scbtFootPrint = 0x080000
} SCardBiometricType;

N_DECLARE_TYPE(SCardBiometricType)

typedef enum SCardBiometricSubtype_
{
	scbsNone = 0x00,
	scbsRight = 0x01,
	scbsLeft = 0x02,
	scbsThumb = 0x04,
	scbsPointerFinger = 0x08,
	scbsMiddleFinger = 0x0C,
	scbsRingFinger = 0x10,
	scbsLittleFinger = 0x14
} SCardBiometricSubtype;

N_DECLARE_TYPE(SCardBiometricSubtype)

typedef enum SCardChallengeQualifier_
{
	sccqUnspecified = 0,
	sccqUtf8Coding = 1
} SCardChallengeQualifier;

N_DECLARE_TYPE(SCardChallengeQualifier)

typedef enum SCardAuthenticationType_
{
	scatComparisonOnCard = 0,
	scatWorkCharingComparisonOnCard = 1,
	scatSystemOnCard = 2
} SCardAuthenticationType;

N_DECLARE_TYPE(SCardAuthenticationType)

typedef enum SCardFmrGrade_
{
	scfmrgNoIndicationGiven = 0,
	scfmrgFmrGrade1 = 1,
	scfmrgFmrGrade2 = 2,
	scfmrgFmrGrade3 = 3,
	scfmrgFmrGrade4 = 4,
	scfmrgFmrGrade5 = 5,
	scfmrgFmrGrade6 = 6
} SCardFmrGrade;

N_DECLARE_TYPE(SCardFmrGrade)

// SCARD_TAG_BIOMETRIC_INFORMATION_TEMPLATE (CBEFF TLV-encoded BIR)

#define SCARD_BIT_TAG_ALGORITHM_REFERENCE                   0x80
#define SCARD_BIT_TAG_REFERENCE_DATA_QUALIFIER              0x83
#define SCARD_BIT_TAG_STANDARD_DATA_OBJECTS                 0xA0
#define SCARD_BIT_TAG_TAG_ALLOCATION_AUTHORITY_DATA_OBJECTS 0xA1
#define SCARD_BIT_TAG_BIOMETRIC_HEADER_TEMPLATE             SCARD_BIT_TAG_TAG_ALLOCATION_AUTHORITY_DATA_OBJECTS
#define SCARD_BIT_TAG_CONFIGURATION_DATA                    0xB1

// SCARD_BIT_TAG_BIOMETRIC_HEADER_TEMPLATE (CBEFF TLV-encoded BIR's SBH block)

// ISO/IEC 19785-3:2007, CBEFF TLV-encoded patron format (for smart cards and other tokens) tag values
#define SCARD_BIT_BHT_TAG_PATRON_HEADER_VERSION                   0x80
#define SCARD_BIT_BHT_TAG_BIT_INDEX                               0x90
#define SCARD_BIT_BHT_TAG_BDT_BIOMETRIC_TYPE                      0x81
#define SCARD_BIT_BHT_TAG_BDT_BIOMETRIC_SUBTYPE                   0x82
#define SCARD_BIT_BHT_TAG_BDT_CREATION_DATE                       0x83
#define SCARD_BIT_BHT_TAG_BIT_CREATOR                             0x84
#define SCARD_BIT_BHT_TAG_BDT_VALIDITY_PERIOD                     0x85
#define SCARD_BIT_BHT_TAG_BDT_PRODUCT_IDENTIFIER                  0x86
#define SCARD_BIT_BHT_TAG_BDT_FORMAT_OWNER                        0x87
#define SCARD_BIT_BHT_TAG_BDT_FORMAT_TYPE                         0x88
#define SCARD_BIT_BHT_TAG_BIOMETRIC_ALGORITHM_PARAMETERS_DATA     0x91
#define SCARD_BIT_BHT_TAG_BIOMETRIC_ALGORITHM_PARAMETERS_TEMPLATE 0xB1

#define SCARD_BIT_BHT_TAG_INDEX                                   0x90 // deprecated, use SCARD_BIT_BHT_TAG_BIT_INDEX instead
#define SCARD_BIT_BHT_TAG_BIOMETRIC_TYPE                          0x81 // deprecated, use SCARD_BIT_BHT_TAG_BDT_BIOMETRIC_TYPE instead
#define SCARD_BIT_BHT_TAG_BIOMETRIC_SUBTYPE                       0x82 // deprecated, use SCARD_BIT_BHT_TAG_BDT_BIOMETRIC_SUBTYPE instead
#define SCARD_BIT_BHT_TAG_CREATION_DATE                           0x83 // deprecated, use SCARD_BIT_BHT_TAG_BDT_CREATION_DATE instead
#define SCARD_BIT_BHT_TAG_CREATOR                                 0x84 // deprecated, use SCARD_BIT_BHT_TAG_BIT_CREATOR instead
#define SCARD_BIT_BHT_TAG_VALIDITY_PERIOD                         0x85 // deprecated, use SCARD_BIT_BHT_TAG_BDT_VALIDITY_PERIOD instead
#define SCARD_BIT_BHT_TAG_PRODUCT_IDENTIFIER                      0x86 // deprecated, use SCARD_BIT_BHT_TAG_BDT_PRODUCT_IDENTIFIER instead
#define SCARD_BIT_BHT_TAG_FORMAT_OWNER                            0x87 // deprecated, use SCARD_BIT_BHT_TAG_BDT_FORMAT_OWNER instead
#define SCARD_BIT_BHT_TAG_FORMAT_TYPE                             0x88 // deprecated, use SCARD_BIT_BHT_TAG_BDT_FORMAT_TYPE instead

// ISO/IEC 19785-3:2007, CBEFF TLV-encoded patron format (for smart cards and other tokens) RFU tag values
#define SCARD_BIT_BHT_TAG_BDT_CHALLENGE_RESPONSE                  0x93
#define SCARD_BIT_BHT_TAG_BDT_INDEX                               0x94
#define SCARD_BIT_BHT_TAG_BDT_PROCESSED_LEVEL                     0x95
#define SCARD_BIT_BHT_TAG_BDT_PURPOSE                             0x96
#define SCARD_BIT_BHT_TAG_BDT_QUALITY                             0x97
#define SCARD_BIT_BHT_TAG_BIT_CREATION_DATE                       0x98
#define SCARD_BIT_BHT_TAG_BIT_PATRON_FORMAT_OWNER                 0x99
#define SCARD_BIT_BHT_TAG_BIT_PATRON_FORMAT_TYPE                  0x9A
#define SCARD_BIT_BHT_TAG_BIT_VALIDITY_PERIOD                     0x9B
#define SCARD_BIT_BHT_TAG_CBEFF_VERSION                           0x9C

#define SCARD_BIT_BHT_TAG_STANDARD_BHT                            0xA1
#define SCARD_BIT_BHT_TAG_PROPRIETARY_BHT                         0xA2

// SCARD_TAG_BIOMETRIC_DATA_TEMPLATE (CBEFF TLV-encoded BIR's BDB block)

#define SCARD_BDT_TAG_CHALLENGE_DATA                     0x80
#define SCARD_BDT_TAG_CHALLENGE_TEMPLATE                 0xA0
#define SCARD_BDT_TAG_STANDARD_BIOMETRIC_DATA            0x81
#define SCARD_BDT_TAG_STANDARD_BIOMETRIC_DATA_OBJECTS    0xA1
#define SCARD_BDT_TAG_PROPRIETARY_BIOMETRIC_DATA         0x82
#define SCARD_BDT_TAG_PROPRIETARY_BIOMETRIC_DATA_OBJECTS 0xA2

// SCARD_BDT_TAG_CHALLENGE_TEMPLATE

#define SCARD_BDT_CT_TAG_CHALLENGE_QUALIFIER 0x90
#define SCARD_BDT_CT_TAG_CHALLENGE           0x80

// SCARD_BIT_TAG_CONFIGURATION_DATA (ISO/IEC 24787:2010)

#define SCARD_BIT_CD_TAG_MAXIMUM_VERIFICATION_DATA_SIZE           0x80
#define SCARD_BIT_CD_TAG_MAXIMUM_REFERENCE_DATA_SIZE              0x81
#define SCARD_BIT_CD_TAG_NUMBER_OF_BIOMETRIC_TEMPLATES            0x82
#define SCARD_BIT_CD_TAG_REENROLLMENT_POSSIBILITY                 0x83
#define SCARD_BIT_CD_TAG_MINIMUM_VERIFICATION_DATA_QUALITY        0x85
#define SCARD_BIT_CD_TAG_INITIAL_RETRY_COUNTER                    0x86
#define SCARD_BIT_CD_TAG_INTERNAL_QUALITY_RESTRICTIONS            0x87
#define SCARD_BIT_CD_TAG_PROPIETARY_DATA                          0x8F
#define SCARD_BIT_CD_TAG_AUTHENTICATION_TYPE_AND_FMR_GRADE        0x90
#define SCARD_BIT_CD_TAG_ALGORITHM_IDENTIFIER                     0xA4


// SCARD_BIT_BHT_TAG_BIOMETRIC_ALGORITHM_PARAMETERS_TEMPLATE (ISO/IEC 24787:2010)

#define SCARD_BIT_BHT_BAPT_TAG_FEATURE_COUNT_OR_LENGTH              0x81
#define SCARD_BIT_BHT_BAPT_TAG_FEATURE_ORDER                        0x82
#define SCARD_BIT_BHT_BAPT_TAG_EXTENDED_FEATURE_HANDLING_INDICATOR  0x83
#define SCARD_BIT_BHT_BAPT_TAG_ALIGNMENT                            0x84
#define SCARD_BIT_BHT_BAPT_TAG_MINIMUM_VERIFICATION_DATA_QUALITY    0x85
#define SCARD_BIT_BHT_BAPT_TAG_AUTHENTICATION_TYPE_AND_FMR_GRADE    0x90
#define SCARD_BIT_BHT_BAPT_TAG_MAXIMUM_RESPONSE_TIME                0x91


NBool N_API NSmartCardBiometryAuthenticationTypeIsValid(SCardAuthenticationType authType);
NBool N_API NSmartCardBiometryFmrGradeIsValid(SCardFmrGrade fmrGrade);
NBool N_API NSmartCardBiometryAuthenticationTypeAndFmrGradeByteIsValid(NByte authTypeAndFmrGradeByte);

NResult N_API NSmartCardBiometryMakeAuthenticationTypeAndFmrGradeByte(SCardAuthenticationType authType, SCardFmrGrade fmrGrade, NByte * pValue);
NResult N_API NSmartCardBiometryGetAuthenticationType(NByte authTypeAndFmrGradeByte, SCardAuthenticationType * pValue);
NResult N_API NSmartCardBiometryGetFmrGrade(NByte authTypeAndFmrGradeByte, SCardFmrGrade * pValue);

N_DECLARE_STATIC_OBJECT_TYPE(NSmartCardsBiometry)

#ifdef N_MSVC
	#pragma deprecated("SCARD_BIT_BHT_TAG_INDEX")
	#pragma deprecated("SCARD_BIT_BHT_TAG_BIOMETRIC_TYPE")
	#pragma deprecated("SCARD_BIT_BHT_TAG_BIOMETRIC_SUBTYPE")
	#pragma deprecated("SCARD_BIT_BHT_TAG_CREATION_DATE")
	#pragma deprecated("SCARD_BIT_BHT_TAG_CREATOR")
	#pragma deprecated("SCARD_BIT_BHT_TAG_VALIDITY_PERIOD")
	#pragma deprecated("SCARD_BIT_BHT_TAG_PRODUCT_IDENTIFIER")
	#pragma deprecated("SCARD_BIT_BHT_TAG_FORMAT_OWNER")
	#pragma deprecated("SCARD_BIT_BHT_TAG_FORMAT_TYPE")
#endif

#ifdef N_CPP
}
#endif

#endif // !N_SMART_CARDS_BIOMETRY_H_INCLUDED
