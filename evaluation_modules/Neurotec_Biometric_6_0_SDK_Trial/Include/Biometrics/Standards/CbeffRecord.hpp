#ifndef CBEFF_RECORD_HPP_INCLUDED
#define CBEFF_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/BdifTypes.hpp>
#include <Biometrics/Standards/CbeffBiometricOrganizations.hpp>
#include <Biometrics/Standards/CbeffBdbFormatIdentifiers.hpp>
#include <Biometrics/Standards/CbeffPatronFormatIdentifiers.hpp>
#include <Biometrics/Standards/CbeffProductIdentifiers.hpp>
#include <Biometrics/Standards/CbeffDeviceIdentifiers.hpp>
#include <Biometrics/NTemplate.hpp>
#include <Biometrics/Standards/FMRecord.hpp>
#include <Biometrics/Standards/FIRecord.hpp>
#include <Biometrics/Standards/FCRecord.hpp>
#include <Biometrics/Standards/IIRecord.hpp>
#include <Biometrics/Standards/ANTemplate.hpp>
#include <Biometrics/Standards/ANRecord.hpp>
#include <SmartCards/BerTag.hpp>
#include <SmartCards/BerTlv.hpp>
#include <SmartCards/PrimitiveBerTlv.hpp>
#include <SmartCards/ConstructedBerTlv.hpp>
#include <SmartCards/NSmartCardsBiometry.hpp>
#include <SmartCards/NSmartCardsDataElements.hpp>
#include <Core/NExpandableObject.hpp>
#include <Biometrics/Standards/FMCRecord.hpp>

namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Core/NNoDeprecate.h>

using ::Neurotec::SmartCards::HBerTlv;
#include <Biometrics/Standards/CbeffRecord.h>

class CbeffTimeInterval : public CbeffTimeInterval_
{
	N_DECLARE_STRUCT_CLASS(CbeffTimeInterval)

public:
	CbeffTimeInterval(NDateTime from, NDateTime to)
	{
		this->from = from;
		this->to = to;
	}
};
}}}

N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, CbeffIntegrityOptions)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, CbeffBiometricType)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, CbeffBiometricSubType)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, CbeffPurpose)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, CbeffProcessedLevel)
N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, CbeffTimeInterval)

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef CBEFF_PATRON_FORMAT_INCITS_TC_M1_BIOMETRICS_A
#undef CBEFF_PATRON_FORMAT_INCITS_TC_M1_BIOMETRICS_B
#undef CBEFF_PATRON_FORMAT_NIST_D
#undef CBEFF_PATRON_FORMAT_ISO_IEC_JTC_1_SC_37_BIOMETRICS_SIMPLE_BYTE_ORIENTED
#undef CBEFF_PATRON_FORMAT_ISO_IEC_JTC_1_SC_37_BIOMETRICS_PRESENCE_BYTE_ORIENTED
#undef CBEFF_PATRON_FORMAT_ISO_IEC_JTC_1_SC_37_BIOMETRICS_TLV_ENCODED
#undef CBEFF_PATRON_FORMAT_ISO_IEC_JTC_1_SC_37_BIOMETRICS_COMPLEX
#undef CBEFF_PATRON_FORMAT_ISO_IEC_JTC_1_SC_37_BIOMETRICS_WITH_ADD_ELEM

#undef CBEFF_PDDE_ISO_IEC_JTC_1_SC_37_BIOMETRICS_TLV_ENCODED_ALGORITHM_REFERENCE
#undef CBEFF_PDDE_ISO_IEC_JTC_1_SC_37_BIOMETRICS_TLV_ENCODED_REFERENCE_DATA_QUALIFIER
#undef CBEFF_PDDE_ISO_IEC_JTC_1_SC_37_BIOMETRICS_TLV_ENCODED_BIOMETRIC_ALGORITHM_PARAMETERS
#undef CBEFF_ADDE_ISO_IEC_JTC_1_SC_37_BIOMETRICS_TLV_ENCODED_CONFIGURATION_DATA

#undef CBEFF_FLAG_SKIP_DEFAULT_VALUES

#undef CBEFF_PF_TLV_FLAG_USE_FOR_ON_CARD_MATCHING
#undef CBEFF_PF_TLV_FLAG_ALLOW_NON_BER_TLV_BDB_DATA
#undef CBEFF_PF_TLV_FLAG_USE_CONFIGURATION_DATA

const NUInt CBEFF_PATRON_FORMAT_INCITS_TC_M1_BIOMETRICS_A                             = 0x001B0001;
const NUInt CBEFF_PATRON_FORMAT_INCITS_TC_M1_BIOMETRICS_B                             = 0x001B0002;
const NUInt CBEFF_PATRON_FORMAT_NIST_D                                                = 0x000F0001;
const NUInt CBEFF_PATRON_FORMAT_ISO_IEC_JTC_1_SC_37_BIOMETRICS_SIMPLE_BYTE_ORIENTED   = 0x01010002;
const NUInt CBEFF_PATRON_FORMAT_ISO_IEC_JTC_1_SC_37_BIOMETRICS_PRESENCE_BYTE_ORIENTED = 0x01010003;
const NUInt CBEFF_PATRON_FORMAT_ISO_IEC_JTC_1_SC_37_BIOMETRICS_TLV_ENCODED            = 0x01010005;
const NUInt CBEFF_PATRON_FORMAT_ISO_IEC_JTC_1_SC_37_BIOMETRICS_COMPLEX                = 0x01010006;
const NUInt CBEFF_PATRON_FORMAT_ISO_IEC_JTC_1_SC_37_BIOMETRICS_WITH_ADD_ELEM          = 0x0101000A;

const NChar CBEFF_PDDE_ISO_IEC_JTC_1_SC_37_BIOMETRICS_TLV_ENCODED_ALGORITHM_REFERENCE[]            = N_T("AlgorithmReference");
const NChar CBEFF_PDDE_ISO_IEC_JTC_1_SC_37_BIOMETRICS_TLV_ENCODED_REFERENCE_DATA_QUALIFIER[]       = N_T("ReferenceDataQualifier");
const NChar CBEFF_PDDE_ISO_IEC_JTC_1_SC_37_BIOMETRICS_TLV_ENCODED_BIOMETRIC_ALGORITHM_PARAMETERS[] = N_T("BiometricAlgorithmParameters");
const NChar CBEFF_ADDE_ISO_IEC_JTC_1_SC_37_BIOMETRICS_TLV_ENCODED_CONFIGURATION_DATA[]             = N_T("ConfigurationData");

const NUInt CBEFF_FLAG_SKIP_DEFAULT_VALUES = 0x00100000;

const NUInt CBEFF_PF_TLV_FLAG_USE_FOR_ON_CARD_MATCHING    = 0x00010000;
const NUInt CBEFF_PF_TLV_FLAG_ALLOW_NON_BER_TLV_BDB_DATA  = 0x00020000;
const NUInt CBEFF_PF_TLV_FLAG_USE_CONFIGURATION_DATA      = 0x00040000;

class CbeffRecord : public NExpandableObject
{
	N_DECLARE_OBJECT_CLASS(CbeffRecord, NExpandableObject)

public:
	class RecordCollection;

private:
	static HCbeffRecord Create(NUInt patronFormat)
	{
		HCbeffRecord handle;
		NCheck(CbeffRecordCreate(patronFormat, &handle));
		return handle;
	}

	static HCbeffRecord Create(const IO::NStream & stream, NUInt patronFormat, NUInt flags)
	{
		HCbeffRecord handle;
		NCheck(CbeffRecordCreateFromStreamEx(stream.GetHandle(), patronFormat, flags, &handle));
		return handle;
	}

	static HCbeffRecord Create(const IO::NBuffer & buffer, NUInt patronFormat, NUInt flags, NSizeType * pSize)
	{
		HCbeffRecord handle;
		NCheck(CbeffRecordCreateFromMemoryNEx(buffer.GetHandle(), patronFormat, flags, pSize, &handle));
		return handle;
	}

	static HCbeffRecord Create(const void * pBuffer, NSizeType bufferSize, NUInt patronFormat, NUInt flags, NSizeType * pSize)
	{
		HCbeffRecord handle;
		NCheck(CbeffRecordCreateFromMemoryEx(pBuffer, bufferSize, patronFormat, flags, pSize, &handle));
		return handle;
	}

	static HCbeffRecord Create(NUInt bdbFormat, const IO::NBuffer & bdbBuffer, NUInt patronFormat)
	{
		HCbeffRecord handle;
		NCheck(CbeffRecordCreateFromDataN(bdbFormat, bdbBuffer.GetHandle(), patronFormat, &handle));
		return handle;
	}

	static HCbeffRecord Create(NUInt bdbFormat, const void * pBdbBuffer, NSizeType bdbBufferSize, NUInt patronFormat)
	{
		HCbeffRecord handle;
		NCheck(CbeffRecordCreateFromData(bdbFormat, pBdbBuffer, bdbBufferSize, patronFormat, &handle));
		return handle;
	}

	static HCbeffRecord Create(const IIRecord & record, NUInt patronFormat, NUInt flags)
	{
		HCbeffRecord handle;
		NCheck(CbeffRecordCreateFromIIRecordEx(record.GetHandle(), patronFormat, flags, &handle));
		return handle;
	}

	static HCbeffRecord Create(const FCRecord & record, NUInt patronFormat, NUInt flags)
	{
		HCbeffRecord handle;
		NCheck(CbeffRecordCreateFromFCRecordEx(record.GetHandle(), patronFormat, flags, &handle));
		return handle;
	}

	static HCbeffRecord Create(const FIRecord & record, NUInt patronFormat, NUInt flags)
	{
		HCbeffRecord handle;
		NCheck(CbeffRecordCreateFromFIRecordEx(record.GetHandle(), patronFormat, flags, &handle));
		return handle;
	}

	static HCbeffRecord Create(const FMRecord & record, NUInt patronFormat, NUInt flags)
	{
		HCbeffRecord handle;
		NCheck(CbeffRecordCreateFromFMRecordEx(record.GetHandle(), patronFormat, flags, &handle));
		return handle;
	}

	static HCbeffRecord Create(const FMCRecord & record, NUInt patronFormat, NUInt flags)
	{
		HCbeffRecord handle;
		NCheck(CbeffRecordCreateFromFMCRecord(record.GetHandle(), patronFormat, flags, &handle));
		return handle;
	}

	static HCbeffRecord Create(const ANTemplate & anTemplate, NUInt patronFormat, NUInt flags)
	{
		HCbeffRecord handle;
		NCheck(CbeffRecordCreateFromANTemplateEx(anTemplate.GetHandle(), patronFormat, flags, &handle));
		return handle;
	}

	static HCbeffRecord Create(const ANRecord & record, NUInt patronFormat)
	{
		HCbeffRecord handle;
		NCheck(CbeffRecordCreateFromANRecord(record.GetHandle(), patronFormat, &handle));
		return handle;
	}

public:
	static NType CbeffIntegrityOptionsNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(CbeffIntegrityOptions), true);
	}

	static NType CbeffBiometricTypeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(CbeffBiometricType), true);
	}

	static NType CbeffBiometricSubTypeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(CbeffBiometricSubType), true);
	}

	static NType CbeffPurposeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(CbeffPurpose), true);
	}

	static NType CbeffProcessedLevelNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(CbeffProcessedLevel), true);
	}

	static NType CbeffTimeIntervalNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(CbeffTimeInterval), true);
	}

	explicit CbeffRecord(NUInt patronFormat)
		: NExpandableObject(Create(patronFormat), true)
	{
	}
	CbeffRecord(const IO::NStream & stream, NUInt patronFormat, NUInt flags = 0)
		: NExpandableObject(Create(stream, patronFormat, flags), true)
	{
	}
	CbeffRecord(const IO::NBuffer & buffer, NUInt patronFormat, NUInt flags = 0, NSizeType * pSize = NULL)
		: NExpandableObject(Create(buffer, patronFormat, flags, pSize), true)
	{
	}
	CbeffRecord(const void * pBuffer, NSizeType bufferSize, NUInt patronFormat, NUInt flags = 0, NSizeType * pSize = NULL)
		: NExpandableObject(Create(pBuffer, bufferSize, patronFormat, flags, pSize), true)
	{
	}
	explicit CbeffRecord(NUInt bdbFormat, const IO::NBuffer & bdbBuffer, NUInt patronFormat)
		: NExpandableObject(Create(bdbFormat, bdbBuffer, patronFormat), true)
	{
	}
	CbeffRecord(NUInt bdbFormat, const void * pBuffer, NSizeType bufferSize, NUInt patronFormat)
		: NExpandableObject(Create(bdbFormat, pBuffer, bufferSize, patronFormat), true)
	{
	}

	CbeffRecord(const IIRecord & record, NUInt patronFormat, NUInt flags = 0)
		: NExpandableObject(Create(record, patronFormat, flags), true)
	{
	}

	CbeffRecord(const FCRecord & record, NUInt patronFormat, NUInt flags = 0)
		: NExpandableObject(Create(record, patronFormat, flags), true)
	{
	}

	CbeffRecord(const FIRecord & record, NUInt patronFormat, NUInt flags = 0)
		: NExpandableObject(Create(record, patronFormat, flags), true)
	{
	}

	CbeffRecord(const FMRecord & record, NUInt patronFormat, NUInt flags = 0)
		: NExpandableObject(Create(record, patronFormat, flags), true)
	{
	}

	CbeffRecord(const FMCRecord & record, NUInt patronFormat, NUInt flags = 0)
		: NExpandableObject(Create(record, patronFormat, flags), true)
	{
	}

	CbeffRecord(const ANTemplate & anTemplate, NUInt patronFormat, NUInt flags = 0)
		: NExpandableObject(Create(anTemplate, patronFormat, flags), true)
	{
	}

	CbeffRecord(const ANRecord & record, NUInt patronFormat)
		: NExpandableObject(Create(record, patronFormat), true)
	{
	}

	static bool IsSupportedCbeffFormat(NUInt patronFormat)
	{
		NBool value;
		NCheck(CbeffRecordIsSupportedCbeffFormat(patronFormat, &value));
		return value != NFalse;
	}

	NUInt GetPatronFormat() const
	{
		NUInt value;
		NCheck(CbeffRecordGetPatronFormat(GetHandle(), &value));
		return value;
	}

	bool GetEncryption() const
	{
		NBool value;
		NCheck(CbeffRecordGetEncryption(GetHandle(), &value));
		return value != NFalse;
	}

	void SetEncryption(bool value)
	{
		NCheck(CbeffRecordSetEncryption(GetHandle(), value));
	}

	bool GetIntegrity() const
	{
		NBool value;
		NCheck(CbeffRecordGetIntegrity(GetHandle(), &value));
		return value != NFalse;
	}

	void SetIntegrity(bool value)
	{
		NCheck(CbeffRecordSetIntegrity(GetHandle(), value));
	}

	bool GetIntegrityOptions(CbeffIntegrityOptions * pValue) const
	{
		NBool hasValue;
		NCheck(CbeffRecordGetIntegrityOptions(GetHandle(), pValue, &hasValue));
		return hasValue != NFalse;
	}

	void SetIntegrityOptions(const CbeffIntegrityOptions * pValue)
	{
		NCheck(CbeffRecordSetIntegrityOptions(GetHandle(), pValue));
	}

	NUInt GetBdbFormat() const
	{
		NUInt value;
		NCheck(CbeffRecordGetBdbFormat(GetHandle(), &value));
		return value;
	}

	void SetBdbFormat(NUInt value)
	{
		NCheck(CbeffRecordSetBdbFormat(GetHandle(), value));
	}

	IO::NBuffer GetBdbBuffer() const
	{
		HNBuffer handle;
		NCheck(CbeffRecordGetBdbBuffer(GetHandle(), &handle));
		return FromHandle<IO::NBuffer>(handle);
	}

	void SetBdbBuffer(const IO::NBuffer & buffer)
	{
		NCheck(CbeffRecordSetBdbBuffer(GetHandle(), buffer.GetHandle()));
	}

	CbeffBiometricType GetBiometricType() const
	{
		CbeffBiometricType value;
		NCheck(CbeffRecordGetBiometricType(GetHandle(), &value));
		return value;
	}

	void SetBiometricType(CbeffBiometricType value)
	{
		NCheck(CbeffRecordSetBiometricType(GetHandle(), value));
	}

	CbeffBiometricSubType GetBiometricSubType() const
	{
		CbeffBiometricSubType value;
		NCheck(CbeffRecordGetBiometricSubType(GetHandle(), &value));
		return value;
	}

	void SetBiometricSubType(CbeffBiometricSubType value)
	{
		NCheck(CbeffRecordSetBiometricSubType(GetHandle(), value));
	}

	IO::NBuffer GetChallengeResponse() const
	{
		HNBuffer handle;
		NCheck(CbeffRecordGetChallengeResponse(GetHandle(), &handle));
		return FromHandle<IO::NBuffer>(handle);
	}

	void SetChallengeResponse(const IO::NBuffer & buffer)
	{
		NCheck(CbeffRecordSetChallengeResponse(GetHandle(), buffer.GetHandle()));
	}

	bool GetBdbCreationDate(NDateTime * pValue) const
	{
		NBool hasValue;
		NCheck(CbeffRecordGetBdbCreationDate(GetHandle(), (NDateTime_ *)pValue, &hasValue));
		return hasValue != NFalse;
	}

	void SetBdbCreationDate(const NDateTime * pValue)
	{
		NCheck(CbeffRecordSetBdbCreationDate(GetHandle(), (const NDateTime_ *)pValue));
	}

	IO::NBuffer GetBdbIndex() const
	{
		HNBuffer handle;
		NCheck(CbeffRecordGetBdbIndex(GetHandle(), &handle));
		return FromHandle<IO::NBuffer>(handle);
	}

	void SetBdbIndex(const IO::NBuffer & buffer)
	{
		NCheck(CbeffRecordSetBdbIndex(GetHandle(), buffer.GetHandle()));
	}

	bool GetProduct(NUInt * pValue) const
	{
		NBool hasValue;
		NCheck(CbeffRecordGetProduct(GetHandle(), pValue, &hasValue));
		return hasValue != NFalse;
	}

	void SetProduct(const NUInt * pValue)
	{
		NCheck(CbeffRecordSetProduct(GetHandle(), pValue));
	}

	bool GetCaptureDevice(NUInt * pValue) const
	{
		NBool hasValue;
		NCheck(CbeffRecordGetCaptureDevice(GetHandle(), pValue, &hasValue));
		return hasValue != NFalse;
	}

	void SetCaptureDevice(const NUInt * pValue)
	{
		NCheck(CbeffRecordSetCaptureDevice(GetHandle(), pValue));
	}

	bool GetFeatureExtractionAlgorithm(NUInt * pValue) const
	{
		NBool hasValue;
		NCheck(CbeffRecordGetFeatureExtractionAlgorithm(GetHandle(), pValue, &hasValue));
		return hasValue != NFalse;
	}

	void SetFeatureExtractionAlgorithm(const NUInt * pValue)
	{
		NCheck(CbeffRecordSetFeatureExtractionAlgorithm(GetHandle(), pValue));
	}

	bool GetComparisonAlgorithm(NUInt * pValue) const
	{
		NBool hasValue;
		NCheck(CbeffRecordGetComparisonAlgorithm(GetHandle(), pValue, &hasValue));
		return hasValue != NFalse;
	}

	void SetComparisonAlgorithm(const NUInt * pValue)
	{
		NCheck(CbeffRecordSetComparisonAlgorithm(GetHandle(), pValue));
	}

	bool GetQualityAlgorithm(NUInt * pValue) const
	{
		NBool hasValue;
		NCheck(CbeffRecordGetQualityAlgorithm(GetHandle(), pValue, &hasValue));
		return hasValue != NFalse;
	}

	void SetQualityAlgorithm(const NUInt * pValue)
	{
		NCheck(CbeffRecordSetQualityAlgorithm(GetHandle(), pValue));
	}

	bool GetCompressionAlgorithm(NUInt * pValue) const
	{
		NBool hasValue;
		NCheck(CbeffRecordGetCompressionAlgorithm(GetHandle(), pValue, &hasValue));
		return hasValue != NFalse;
	}

	void SetCompressionAlgorithm(const NUInt * pValue)
	{
		NCheck(CbeffRecordSetCompressionAlgorithm(GetHandle(), pValue));
	}

	CbeffProcessedLevel GetProcessedLevel() const
	{
		CbeffProcessedLevel value;
		NCheck(CbeffRecordGetProcessedLevel(GetHandle(), &value));
		return value;
	}

	void SetProcessedLevel(CbeffProcessedLevel value)
	{
		NCheck(CbeffRecordSetProcessedLevel(GetHandle(), value));
	}

	CbeffPurpose GetPurpose() const
	{
		CbeffPurpose value;
		NCheck(CbeffRecordGetPurpose(GetHandle(), &value));
		return value;
	}

	void SetPurpose(CbeffPurpose value)
	{
		NCheck(CbeffRecordSetPurpose(GetHandle(), value));
	}

	bool GetQuality(NByte * pValue) const
	{
		NBool hasValue;
		NCheck(CbeffRecordGetQuality(GetHandle(), pValue, &hasValue));
		return hasValue != NFalse;
	}

	void SetQuality(const NByte * pValue)
	{
		NCheck(CbeffRecordSetQuality(GetHandle(), pValue));
	}

	bool GetBdbValidityPeriod(CbeffTimeInterval * pValue) const
	{
		NBool hasValue;
		NCheck(CbeffRecordGetBdbValidityPeriod(GetHandle(), (CbeffTimeInterval_ *)pValue, &hasValue));
		return hasValue != NFalse;
	}

	void SetBdbValidityPeriod(const CbeffTimeInterval * pValue)
	{
		NCheck(CbeffRecordSetBdbValidityPeriod(GetHandle(), (const CbeffTimeInterval_ *)pValue));
	}

	bool GetBirCreationDate(NDateTime * pValue) const
	{
		NBool hasValue;
		NCheck(CbeffRecordGetBirCreationDate(GetHandle(), (NDateTime_ *)pValue, &hasValue));
		return hasValue != NFalse;
	}

	void SetBirCreationDate(const NDateTime * pValue)
	{
		NCheck(CbeffRecordSetBirCreationDate(GetHandle(), (const NDateTime_ *)pValue));
	}

	NString GetCreator() const
	{
		HNString hValue;
		NCheck(CbeffRecordGetCreator(GetHandle(), &hValue));
		return NString(hValue, true);
	}

	void SetCreator(const NStringWrapper & value)
	{
		NCheck(CbeffRecordSetCreator(GetHandle(), value.GetHandle()));
	}

	IO::NBuffer GetBirIndex() const
	{
		HNBuffer hValue;
		NCheck(CbeffRecordGetBirIndex(GetHandle(), &hValue));
		return FromHandle<IO::NBuffer>(hValue);
	}

	void SetBirIndex(const IO::NBuffer & value)
	{
		NCheck(CbeffRecordSetBirIndex(GetHandle(), value.GetHandle()));
	}

	IO::NBuffer GetPayload() const
	{
		HNBuffer hValue;
		NCheck(CbeffRecordGetPayload(GetHandle(), &hValue));
		return FromHandle<IO::NBuffer>(hValue);
	}

	void SetPayload(const IO::NBuffer & value)
	{
		NCheck(CbeffRecordSetPayload(GetHandle(), value.GetHandle()));
	}

	bool GetBirValidityPeriod(CbeffTimeInterval * pValue) const
	{
		NBool hasValue = NFalse;
		NCheck(CbeffRecordGetBirValidityPeriod(GetHandle(), (CbeffTimeInterval_ *)pValue, &hasValue));
		return hasValue != NFalse;
	}

	void SetBirValidityPeriod(const CbeffTimeInterval * pValue)
	{
		NCheck(CbeffRecordSetBirValidityPeriod(GetHandle(), (const CbeffTimeInterval_ *)pValue));
	}

	bool GetCbeffVersion(NByte * pValue) const
	{
		NBool hasValue = NTrue;
		NCheck(CbeffRecordGetCbeffVersion(GetHandle(), pValue));
		return hasValue != NFalse;
	}

	bool GetPatronHeaderVersion(NByte * pValue) const
	{
		NBool hasValue = NTrue;
		NCheck(CbeffRecordGetPatronHeaderVersion(GetHandle(), pValue));
		return hasValue != NFalse;
	}

	N_DEPRECATED("method is deprecated, use NPropertyBagTryGet(HNPropertyBag, NChar, HNValue, NBool) instead.")
	IO::NBuffer GetFascnBuffer() const
	{
		HNBuffer hValue;
		NCheck(CbeffRecordGetFascnBuffer(GetHandle(), &hValue));
		return FromHandle<IO::NBuffer>(hValue);
	}

	N_DEPRECATED("method is deprecated, use NPropertyBagSet(HNPropertyBag, NChar, HNValue) instead.")
	void SetFascnBuffer(const IO::NBuffer & value)
	{
		NCheck(CbeffRecordSetFascnBuffer(GetHandle(), value.GetHandle()));
	}

	bool GetSbFormat(NUInt * pValue) const
	{
		NBool hasValue = NFalse;
		NCheck(CbeffRecordGetSbFormat(GetHandle(), pValue, &hasValue));
		return hasValue != NFalse;
	}

	void SetSbFormat(const NUInt * pValue)
	{
		NCheck(CbeffRecordSetSbFormat(GetHandle(), pValue));
	}

	IO::NBuffer GetSbBuffer() const
	{
		HNBuffer hValue;
		NCheck(CbeffRecordGetSbBuffer(GetHandle(), &hValue));
		return FromHandle<IO::NBuffer>(hValue);
	}

	void SetSbBuffer(const IO::NBuffer & value)
	{
		NCheck(CbeffRecordSetSbBuffer(GetHandle(), value.GetHandle()));
	}

	::Neurotec::SmartCards::BerTlv ToBerTlv(NUInt flags = 0) const
	{
		::Neurotec::SmartCards::HBerTlv hValue;
		NCheck(CbeffRecordToBerTlv(GetHandle(), flags, &hValue));
		return FromHandle< ::Neurotec::SmartCards::BerTlv>(hValue);
	}

	RecordCollection GetRecords();
	const RecordCollection GetRecords() const;
};

class CbeffRecord::RecordCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<CbeffRecord, CbeffRecord,
	CbeffRecordGetRecordCount, CbeffRecordGetRecord, CbeffRecordGetRecords>
{
	RecordCollection(const CbeffRecord & owner)
	{
		SetOwner(owner);
	}

	friend class CbeffRecord;

public:
	void Set(NInt index, const CbeffRecord & value)
	{
		NCheck(CbeffRecordSetRecord(this->GetOwnerHandle(), index, value.GetHandle()));
	}

	NInt Add(const CbeffRecord & value)
	{
		NInt index;
		NCheck(CbeffRecordAddRecord(this->GetOwnerHandle(), value.GetHandle(), &index));
		return index;
	}

	void Insert(NInt index, const CbeffRecord & value)
	{
		NCheck(CbeffRecordInsertRecord(this->GetOwnerHandle(), index, value.GetHandle()));
	}

	void RemoveAt(NInt index)
	{
		NCheck(CbeffRecordRemoveRecordAt(this->GetOwnerHandle(), index));
	}

	void Clear()
	{
		NCheck(CbeffRecordClearRecords(this->GetOwnerHandle()));
	}
};

inline CbeffRecord::RecordCollection CbeffRecord::GetRecords()
{
	return CbeffRecord::RecordCollection(*this);
}

inline const CbeffRecord::RecordCollection CbeffRecord::GetRecords() const
{
	return CbeffRecord::RecordCollection(*this);
}

#include <Core/NReDeprecate.h>
}}}

#endif // !CBEFF_RECORD_HPP_INCLUDED
