#include <Biometrics/Standards/FmrFingerView.hpp>

#ifndef FM_RECORD_HPP_INCLUDED
#define FM_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/BdifTypes.hpp>
#include <Biometrics/NTemplate.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Biometrics/Standards/FMRecord.h>
}}}

N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, FmrCaptureEquipmentCompliance)

namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Core/NNoDeprecate.h>

#undef FMR_VERSION_ANSI_2_0
#undef FMR_VERSION_ANSI_3_5
#undef FMR_VERSION_ISO_2_0
#undef FMR_VERSION_ISO_3_0

#undef FMR_VERSION_ANSI_CURRENT
#undef FMR_VERSION_ISO_CURRENT

#undef FMR_MAX_FINGER_VIEW_COUNT_PER_FINGER

#undef FMR_MAX_FINGER_COUNT
#undef FMR_MAX_FINGER_VIEW_COUNT

#undef FMR_MAX_FINGER_COUNT_3_0
#undef FMR_MAX_FINGER_VIEW_COUNT_3_0

#undef FMR_MAX_FINGER_COUNT_3_5
#undef FMR_MAX_FINGER_VIEW_COUNT_3_5

#undef FMR_PROCESS_FIRST_FINGER_ONLY
#undef FMR_PROCESS_FIRST_FINGER_VIEW_PER_FINGER_ONLY
#undef FMR_PROCESS_FIRST_FINGER_VIEW_ONLY

const NVersion FMR_VERSION_ANSI_2_0(0x0200);
const NVersion FMR_VERSION_ANSI_3_5(0x0305);
const NVersion FMR_VERSION_ISO_2_0(0x0200);
const NVersion FMR_VERSION_ISO_3_0(0x0300);

const NVersion FMR_VERSION_ANSI_CURRENT(FMR_VERSION_ANSI_3_5);
const NVersion FMR_VERSION_ISO_CURRENT(FMR_VERSION_ISO_3_0);

const NInt FMR_MAX_FINGER_VIEW_COUNT_PER_FINGER = 16;

const NInt FMR_MAX_FINGER_COUNT = 11;
const NInt FMR_MAX_FINGER_VIEW_COUNT = FMR_MAX_FINGER_COUNT * FMR_MAX_FINGER_VIEW_COUNT_PER_FINGER;

const NInt FMR_MAX_FINGER_COUNT_3_0 = 25;
const NInt FMR_MAX_FINGER_VIEW_COUNT_3_0 = (FMR_MAX_FINGER_COUNT_3_0 * FMR_MAX_FINGER_VIEW_COUNT_PER_FINGER);

const NInt FMR_MAX_FINGER_COUNT_3_5 = 25;
const NInt FMR_MAX_FINGER_VIEW_COUNT_3_5 = (FMR_MAX_FINGER_COUNT_3_0 * FMR_MAX_FINGER_VIEW_COUNT_PER_FINGER);

const NUInt FMR_PROCESS_FIRST_FINGER_ONLY = 0x00000100;
const NUInt FMR_PROCESS_FIRST_FINGER_VIEW_PER_FINGER_ONLY = 0x00001000;
const NUInt FMR_PROCESS_FIRST_FINGER_VIEW_ONLY = (FMR_PROCESS_FIRST_FINGER_ONLY | FMR_PROCESS_FIRST_FINGER_VIEW_PER_FINGER_ONLY);

class FMRecord : public NObject
{
	N_DECLARE_OBJECT_CLASS(FMRecord, NObject)

public:
	class FingerViewCollection : public ::Neurotec::Collections::NCollectionBase<FmrFingerView, FMRecord,
		FMRecordGetFingerViewCount, FMRecordGetFingerView>
	{
		FingerViewCollection(const FMRecord & owner)
		{
			SetOwner(owner);
		}

		friend class FMRecord;
	public:
		NInt GetCapacity() const
		{
			NInt value;
			NCheck(FMRecordGetFingerViewCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(FMRecordSetFingerViewCapacity(this->GetOwnerHandle(), value));
		}

		NInt Add(const FmrFingerView & value)
		{
			NInt index;
			NCheck(FMRecordAddFingerView(this->GetOwnerHandle(), value.GetHandle(), &index));
			return index;
		}
		
		void RemoveAt(NInt index)
		{
			NCheck(FMRecordRemoveFingerViewAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(FMRecordClearFingerViews(this->GetOwnerHandle()));
		}
	};

private:
	static HFMRecord Create(BdifStandard standard, NVersion version, NUInt flags)
	{
		HFMRecord handle;
		NCheck(FMRecordCreateEx(standard, version.GetValue(), flags, &handle));
		return handle;
	}

	static HFMRecord Create(const ::Neurotec::IO::NBuffer & buffer, BdifStandard standard, NUInt flags, NSizeType * pSize)
	{
		HFMRecord handle;
		NCheck(FMRecordCreateFromMemoryN(buffer.GetHandle(), flags, standard, pSize, &handle));
		return handle;
	}

	static HFMRecord Create(const void * pBuffer, NSizeType bufferSize, BdifStandard standard, NUInt flags, NSizeType * pSize)
	{
		HFMRecord handle;
		NCheck(FMRecordCreateFromMemory(pBuffer, bufferSize, flags, standard, pSize, &handle));
		return handle;
	}

	static HFMRecord Create(const FMRecord & srcRecord, BdifStandard standard, NVersion version, NUInt flags)
	{
		HFMRecord handle;
		NCheck(FMRecordCreateFromFMRecordEx(srcRecord.GetHandle(), flags, standard, version.GetValue(), &handle));
		return handle;
	}

	static HFMRecord Create(const NFRecord & nfRecord, BdifStandard standard, NVersion version, NUInt flags)
	{
		HFMRecord handle;
		NCheck(FMRecordCreateFromNFRecordEx(nfRecord.GetHandle(), flags, standard, version.GetValue(), &handle));
		return handle;
	}

	static HFMRecord Create(const NFTemplate & nfTemplate, BdifStandard standard, NVersion version, NUInt flags)
	{
		HFMRecord handle;
		NCheck(FMRecordCreateFromNFTemplateEx(nfTemplate.GetHandle(), flags, standard, version.GetValue(), &handle));
		return handle;
	}

public:
	static NType FmrCaptureEquipmentComplianceNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(FmrCaptureEquipmentCompliance), true);
	}

	explicit FMRecord(BdifStandard standard, NVersion version, NUInt flags = 0)
		: NObject(Create(standard, version, flags), true)
	{
	}

	FMRecord(const ::Neurotec::IO::NBuffer & buffer, BdifStandard standard, NUInt flags = 0, NSizeType * pSize = NULL)
		: NObject(Create(buffer, standard, flags, pSize), true)
	{
	}

	FMRecord(const void * pBuffer, NSizeType bufferSize, BdifStandard standard, NUInt flags = 0, NSizeType * pSize = NULL)
		: NObject(Create(pBuffer, bufferSize, standard, flags, pSize), true)
	{
	}

	FMRecord(const FMRecord & srcRecord, BdifStandard standard, NVersion version, NUInt flags = 0)
		: NObject(Create(srcRecord, standard, version, flags), true)
	{
	}

	FMRecord(const NFRecord & nfRecord, BdifStandard standard, NVersion version, NUInt flags = 0)
		: NObject(Create(nfRecord, standard, version, flags), true)
	{
	}

	FMRecord(const NFTemplate & nfTemplate, BdifStandard standard, NVersion version, NUInt flags = 0)
		: NObject(Create(nfTemplate, standard, version, flags), true)
	{
	}

	NFTemplate ToNFTemplate(NUInt flags = 0) const
	{
		HNFTemplate hNFTemplate;
		NCheck(FMRecordToNFTemplate(GetHandle(), flags, &hNFTemplate));
		return FromHandle<NFTemplate>(hNFTemplate);
	}

	NTemplate ToNTemplate(NUInt flags = 0) const
	{
		HNTemplate hNTemplate;
		NCheck(FMRecordToNTemplate(GetHandle(), flags, &hNTemplate));
		return FromHandle<NTemplate>(hNTemplate);
	}

	BdifStandard GetStandard() const
	{
		BdifStandard value;
		NCheck(FMRecordGetStandard(GetHandle(), &value));
		return value;
	}

	NVersion GetVersion() const
	{
		NVersion_ value;
		NCheck(FMRecordGetVersion(GetHandle(), &value));
		return NVersion(value);
	}

	bool GetCertificationFlag() const
	{
		NBool value;
		NCheck(FMRecordGetCertificationFlag(GetHandle(), &value));
		return value != 0;
	}

	void SetCertificationFlag(bool value)
	{
		NCheck(FMRecordSetCertificationFlag(GetHandle(), value ? NTrue : NFalse));
	}

	NUInt GetCbeffProductId() const
	{
		NUInt value;
		NCheck(FMRecordGetCbeffProductId(GetHandle(), &value));
		return value;
	}

	void SetCbeffProductId(NUInt value)
	{
		NCheck(FMRecordSetCbeffProductId(GetHandle(), value));
	}

	FmrCaptureEquipmentCompliance GetCaptureEquipmentCompliance() const
	{
		FmrCaptureEquipmentCompliance value;
		NCheck(FMRecordGetCaptureEquipmentCompliance(GetHandle(), &value));
		return value;
	}

	void SetCaptureEquipmentCompliance(FmrCaptureEquipmentCompliance value)
	{
		NCheck(FMRecordSetCaptureEquipmentCompliance(GetHandle(), value));
	}

	NUShort GetCaptureEquipmentId() const
	{
		NUShort value;
		NCheck(FMRecordGetCaptureEquipmentId(GetHandle(), &value));
		return value;
	}

	void SetCaptureEquipmentId(NUShort value)
	{
		NCheck(FMRecordSetCaptureEquipmentId(GetHandle(), value));
	}

	NUShort GetSizeX() const
	{
		NUShort value;
		NCheck(FMRecordGetSizeX(GetHandle(), &value));
		return value;
	}

	void SetSizeX(NUShort value)
	{
		NCheck(FMRecordSetSizeX(GetHandle(), value));
	}

	NUShort GetSizeY() const
	{
		NUShort value;
		NCheck(FMRecordGetSizeY(GetHandle(), &value));
		return value;
	}

	void SetSizeY(NUShort value)
	{
		NCheck(FMRecordSetSizeY(GetHandle(), value));
	}

	NUShort GetResolutionX() const
	{
		NUShort value;
		NCheck(FMRecordGetResolutionX(GetHandle(), &value));
		return value;
	}

	void SetResolutionX(NUShort value)
	{
		NCheck(FMRecordSetResolutionX(GetHandle(), value));
	}

	NUShort GetResolutionY() const
	{
		NUShort value;
		NCheck(FMRecordGetResolutionY(GetHandle(), &value));
		return value;
	}

	void SetResolutionY(NUShort value)
	{
		NCheck(FMRecordSetResolutionY(GetHandle(), value));
	}

	FingerViewCollection GetFingerViews()
	{
		return FingerViewCollection(*this);
	}

	const FingerViewCollection GetFingerViews() const
	{
		return FingerViewCollection(*this);
	}
};

#include <Core/NReDeprecate.h>
}}}

#endif // !FM_RECORD_HPP_INCLUDED
