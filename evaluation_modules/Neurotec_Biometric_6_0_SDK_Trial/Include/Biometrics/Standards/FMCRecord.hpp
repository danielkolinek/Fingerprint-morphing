#ifndef FMC_RECORD_HPP_INCLUDED
#define FMC_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/BdifTypes.hpp>
#include <SmartCards/BerTag.hpp>
#include <Biometrics/NFRecord.hpp>

namespace Neurotec { namespace Biometrics { namespace Standards
{
using ::Neurotec::SmartCards::HBerTlv;
#include <Biometrics/Standards/FMCRecord.h>
}}}

N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, FmcrMinutiaFormat)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, FmcrMinutiaOrder)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, FmcrFeatureHandling)

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef FMCR_VERSION_ISO_2_0
#undef FMCR_VERSION_ISO_3_0
#undef FMCR_VERSION_ISO_CURRENT

#undef FMCR_SKIP_FOUR_NEIGHBORS_RIDGE_COUNTS
#undef FMCR_SKIP_EIGHT_NEIGHBORS_RIDGE_COUNTS
#undef FMCR_SKIP_CORES
#undef FMCR_SKIP_DELTAS
#undef FMCR_SKIP_IMPRESSION_TYPE
#undef FMCR_SKIP_VENDOR_DATA
#undef FMCR_SKIP_RIDGE_COUNTS
#undef FMCR_SKIP_SINGULAR_POINTS
#undef FMCR_SKIP_STANDARD_EXTENDED_DATA
#undef FMCR_SKIP_ALL_EXTENDED_DATA

#undef FMCR_USE_BIOMETRIC_DATA_TEMPLATE
#undef FMCR_USE_STANDARD_BIOMETRIC_DATA_OBJECTS

#undef FMCR_DEFAULT_MIN_ENROLL_MC
#undef FMCR_DEFAULT_MIN_VERIFY_MC
#undef FMCR_DEFAULT_MAX_ENROLL_MC
#undef FMCR_DEFAULT_MAX_VERIFY_MC

#undef FMCR_BDT_TAG_FINGER_MINUTIAE_DATA
#undef FMCR_BDT_TAG_RIDGE_COUNT_DATA
#undef FMCR_BDT_TAG_CORE_POINT_DATA
#undef FMCR_BDT_TAG_DELTA_POINT_DATA
#undef FMCR_BDT_TAG_CELL_QUALITY_DATA
#undef FMCR_BDT_TAG_IMPRESSION_TYPE

const NVersion FMCR_VERSION_ISO_2_0(0x0200);
const NVersion FMCR_VERSION_ISO_3_0(0x0300);
const NVersion FMCR_VERSION_ISO_CURRENT(FMCR_VERSION_ISO_3_0);

const NInt FMCR_SKIP_FOUR_NEIGHBORS_RIDGE_COUNTS = 0x00000100;
const NInt FMCR_SKIP_EIGHT_NEIGHBORS_RIDGE_COUNTS = 0x00000200;
const NInt FMCR_SKIP_CORES = 0x00000400;
const NInt FMCR_SKIP_DELTAS = 0x00000800;
const NInt FMCR_SKIP_IMPRESSION_TYPE = 0x00001000;
const NInt FMCR_SKIP_VENDOR_DATA = 0x00002000;

const NInt FMCR_SKIP_RIDGE_COUNTS = FMCR_SKIP_FOUR_NEIGHBORS_RIDGE_COUNTS | FMCR_SKIP_EIGHT_NEIGHBORS_RIDGE_COUNTS;
const NInt FMCR_SKIP_SINGULAR_POINTS = FMCR_SKIP_CORES | FMCR_SKIP_DELTAS;
const NInt FMCR_SKIP_STANDARD_EXTENDED_DATA = FMCR_SKIP_RIDGE_COUNTS | FMCR_SKIP_SINGULAR_POINTS | FMCR_SKIP_IMPRESSION_TYPE;
const NInt FMCR_SKIP_ALL_EXTENDED_DATA = FMCR_SKIP_STANDARD_EXTENDED_DATA | FMCR_SKIP_VENDOR_DATA;

const NInt FMCR_USE_BIOMETRIC_DATA_TEMPLATE = 0x02000000;
const NInt FMCR_USE_STANDARD_BIOMETRIC_DATA_OBJECTS = 0x04000000;

const NInt FMCR_DEFAULT_MIN_ENROLL_MC = 16;
const NInt FMCR_DEFAULT_MIN_VERIFY_MC = 12;
const NInt FMCR_DEFAULT_MAX_ENROLL_MC = 60;
const NInt FMCR_DEFAULT_MAX_VERIFY_MC = 60;

const ::Neurotec::SmartCards::BerTag FMCR_BDT_TAG_FINGER_MINUTIAE_DATA(0x90);
const ::Neurotec::SmartCards::BerTag FMCR_BDT_TAG_RIDGE_COUNT_DATA(0x91);
const ::Neurotec::SmartCards::BerTag FMCR_BDT_TAG_CORE_POINT_DATA(0x92);
const ::Neurotec::SmartCards::BerTag FMCR_BDT_TAG_DELTA_POINT_DATA(0x93);
const ::Neurotec::SmartCards::BerTag FMCR_BDT_TAG_CELL_QUALITY_DATA(0x94);
const ::Neurotec::SmartCards::BerTag FMCR_BDT_TAG_IMPRESSION_TYPE(0x95);

class FMCRecord : public NObject
{
	N_DECLARE_OBJECT_CLASS(FMCRecord, NObject)

public:
	class MinutiaCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<FmrMinutia, FMCRecord,
		FMCRecordGetMinutiaCount, FMCRecordGetMinutia, FMCRecordGetMinutiae>
	{
		MinutiaCollection(const FMCRecord & owner)
		{
			SetOwner(owner);
		}

		friend class FMCRecord;
	public:
		NInt GetCapacity() const
		{
			NInt value;
			NCheck(FMCRecordGetMinutiaCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(FMCRecordSetMinutiaCapacity(this->GetOwnerHandle(), value));
		}

		void Set(NInt index, const FmrMinutia & value)
		{
			NCheck(FMCRecordSetMinutia(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const FmrMinutia & value)
		{
			NInt index;
			NCheck(FMCRecordAddMinutia(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const FmrMinutia & value)
		{
			NCheck(FMCRecordInsertMinutia(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(FMCRecordRemoveMinutiaAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(FMCRecordClearMinutiae(this->GetOwnerHandle()));
		}
	};

	class MinutiaFourNeighborsCollection : public ::Neurotec::NObjectPartBase<FMCRecord>
	{
		MinutiaFourNeighborsCollection(const FMCRecord & owner)
		{
			SetOwner(owner);
		}

		friend class FMCRecord;
	public:
		NInt GetCount(NInt baseIndex) const
		{
			N_UNREFERENCED_PARAMETER(baseIndex);
			return 4;
		}

		void Get(NInt baseIndex, NInt index, BdifFPMinutiaNeighbor * pValue) const
		{
			NCheck(FMCRecordGetMinutiaFourNeighbor(this->GetOwnerHandle(), baseIndex, index, pValue));
		}

		BdifFPMinutiaNeighbor Get(NInt baseIndex, NInt index) const
		{
			BdifFPMinutiaNeighbor value;
			NCheck(FMCRecordGetMinutiaFourNeighbor(this->GetOwnerHandle(), baseIndex, index, &value));
			return value;
		}

		NArrayWrapper<BdifFPMinutiaNeighbor> GetAll(NInt baseIndex) const
		{
			BdifFPMinutiaNeighbor_ * arValue = NULL;
			NInt nativeCount = 0;
			NCheck(FMCRecordGetMinutiaFourNeighbors(this->GetOwnerHandle(), baseIndex, &arValue, &nativeCount));
			return NArrayWrapper< ::Neurotec::Biometrics::Standards::BdifFPMinutiaNeighbor>(arValue, nativeCount);
		}

		void Set(NInt baseIndex, NInt index, const BdifFPMinutiaNeighbor & value)
		{
			NCheck(FMCRecordSetMinutiaFourNeighbor(this->GetOwnerHandle(), baseIndex, index, &value));
		}
	};

	class MinutiaEightNeighborsCollection : public ::Neurotec::NObjectPartBase<FMCRecord>
	{
		MinutiaEightNeighborsCollection(const FMCRecord & owner)
		{
			SetOwner(owner);
		}

		friend class FMCRecord;
	public:
		NInt GetCount(NInt baseIndex) const
		{
			N_UNREFERENCED_PARAMETER(baseIndex);
			return 8;
		}

		void Get(NInt baseIndex, NInt index, BdifFPMinutiaNeighbor * pValue) const
		{
			NCheck(FMCRecordGetMinutiaEightNeighbor(this->GetOwnerHandle(), baseIndex, index, pValue));
		}

		BdifFPMinutiaNeighbor Get(NInt baseIndex, NInt index) const
		{
			BdifFPMinutiaNeighbor value;
			NCheck(FMCRecordGetMinutiaEightNeighbor(this->GetOwnerHandle(), baseIndex, index, &value));
			return value;
		}

		NArrayWrapper<BdifFPMinutiaNeighbor> GetAll(NInt baseIndex) const
		{
			BdifFPMinutiaNeighbor_ * arValue = NULL;
			NInt nativeCount = 0;
			NCheck(FMCRecordGetMinutiaEightNeighbors(this->GetOwnerHandle(), baseIndex, &arValue, &nativeCount));
			return NArrayWrapper< ::Neurotec::Biometrics::Standards::BdifFPMinutiaNeighbor>(arValue, nativeCount);
		}

		void Set(NInt baseIndex, NInt index, const BdifFPMinutiaNeighbor & value)
		{
			NCheck(FMCRecordSetMinutiaEightNeighbor(this->GetOwnerHandle(), baseIndex, index, &value));
		}
	};

	class CoreCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<FmrCore, FMCRecord,
		FMCRecordGetCoreCount, FMCRecordGetCore, FMCRecordGetCores>
	{
		CoreCollection(const FMCRecord & owner)
		{
			SetOwner(owner);
		}

		friend class FMCRecord;
	public:
		NInt GetCapacity() const
		{
			NInt value;
			NCheck(FMCRecordGetCoreCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(FMCRecordSetCoreCapacity(this->GetOwnerHandle(), value));
		}

		void Set(NInt index, const FmrCore & value)
		{
			NCheck(FMCRecordSetCore(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const FmrCore & value)
		{
			NInt index;
			NCheck(FMCRecordAddCore(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const FmrCore & value)
		{
			NCheck(FMCRecordInsertCore(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(FMCRecordRemoveCoreAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(FMCRecordClearCores(this->GetOwnerHandle()));
		}
	};

	class DeltaCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<FmrDelta, FMCRecord,
		FMCRecordGetDeltaCount, FMCRecordGetDelta, FMCRecordGetDeltas>
	{
		DeltaCollection(const FMCRecord & owner)
		{
			SetOwner(owner);
		}

		friend class FMCRecord;
	public:
		NInt GetCapacity() const
		{
			NInt value;
			NCheck(FMCRecordGetDeltaCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(FMCRecordSetDeltaCapacity(this->GetOwnerHandle(), value));
		}

		void Set(NInt index, const FmrDelta & value)
		{
			NCheck(FMCRecordSetDelta(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const FmrDelta & value)
		{
			NInt index;
			NCheck(FMCRecordAddDelta(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const FmrDelta & value)
		{
			NCheck(FMCRecordInsertDelta(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(FMCRecordRemoveDeltaAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(FMCRecordClearDeltas(this->GetOwnerHandle()));
		}
	};

private:
	static HFMCRecord Create(BdifStandard standard, NVersion version, FmcrMinutiaFormat minutiaFormat, NUInt flags)
	{
		HFMCRecord handle;
		NCheck(FMCRecordCreate(standard, version.GetValue(), minutiaFormat, flags, &handle));
		return handle;
	}

	static HFMCRecord Create(const ::Neurotec::IO::NBuffer & buffer, BdifStandard standard, NVersion version, FmcrMinutiaFormat minutiaFormat, NUInt flags, NSizeType * pSize)
	{
		HFMCRecord handle;
		NCheck(FMCRecordCreateFromMemoryN(buffer.GetHandle(), standard, version.GetValue(), minutiaFormat, flags, pSize, &handle));
		return handle;
	}

	static HFMCRecord Create(const void * pBuffer, NSizeType bufferSize, BdifStandard standard, NVersion version, FmcrMinutiaFormat minutiaFormat, NUInt flags, NSizeType * pSize)
	{
		HFMCRecord handle;
		NCheck(FMCRecordCreateFromMemory(pBuffer, bufferSize, standard, version.GetValue(), minutiaFormat, flags, pSize, &handle));
		return handle;
	}

	static HFMCRecord Create(const FMCRecord & srcRecord, BdifStandard standard, NVersion version, FmcrMinutiaFormat minutiaFormat, NUInt flags)
	{
		HFMCRecord handle;
		NCheck(FMCRecordCreateFromFMCRecord(srcRecord.GetHandle(), standard, version.GetValue(), minutiaFormat, flags, &handle));
		return handle;
	}

	static HFMCRecord Create(const NFRecord & nfRecord, BdifStandard standard, NVersion version, FmcrMinutiaFormat minutiaFormat, FmcrMinutiaOrder order, NUInt flags)
	{
		HFMCRecord handle;
		NCheck(FMCRecordCreateFromNFRecord(nfRecord.GetHandle(), standard, version.GetValue(), minutiaFormat, order, flags, &handle));
		return handle;
	}

public:
	static NType FmcrMinutiaFormatNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(FmcrMinutiaFormat), true);
	}

	explicit FMCRecord(BdifStandard standard, NVersion version, FmcrMinutiaFormat minutiaFormat, NUInt flags = 0)
		: NObject(Create(standard, version, minutiaFormat, flags), true)
	{
	}

	FMCRecord(const ::Neurotec::IO::NBuffer & buffer, BdifStandard standard, NVersion version, FmcrMinutiaFormat minutiaFormat, NUInt flags = 0, NSizeType * pSize = NULL)
		: NObject(Create(buffer, standard, version, minutiaFormat, flags, pSize), true)
	{
	}

	FMCRecord(const void * pBuffer, NSizeType bufferSize, BdifStandard standard, NVersion version, FmcrMinutiaFormat minutiaFormat, NUInt flags = 0, NSizeType * pSize = NULL)
		: NObject(Create(pBuffer, bufferSize, standard, version, minutiaFormat, flags, pSize), true)
	{
	}

	FMCRecord(const FMCRecord & srcRecord, BdifStandard standard, NVersion version, FmcrMinutiaFormat minutiaFormat, NUInt flags = 0)
		: NObject(Create(srcRecord, standard, version, minutiaFormat, flags), true)
	{
	}

	FMCRecord(const NFRecord & nfRecord, BdifStandard standard, NVersion version, FmcrMinutiaFormat minutiaFormat, FmcrMinutiaOrder order, NUInt flags = 0)
		: NObject(Create(nfRecord, standard, version, minutiaFormat, order, flags), true)
	{
	}

	void SortMinutiae(FmcrMinutiaOrder order) const
	{
		NCheck(FMCRecordSortMinutiae(GetHandle(), order));
	}

	NFRecord ToNFRecord(NUInt flags = 0) const
	{
		HNFRecord hNFRecord;
		NCheck(FMCRecordToNFRecord(GetHandle(), flags, &hNFRecord));
		return FromHandle<NFRecord>(hNFRecord);
	}

	SmartCards::BerTlv ToBerTlv(NUInt flags = 0) const
	{
		SmartCards::HBerTlv hBerTlv;
		NCheck(FMCRecordToBerTlv(GetHandle(), flags, &hBerTlv));
		return FromHandle<SmartCards::BerTlv>(hBerTlv);
	}

	BdifStandard GetStandard() const
	{
		BdifStandard value;
		NCheck(FMCRecordGetStandard(GetHandle(), &value));
		return value;
	}

	NVersion GetVersion() const
	{
		NVersion_ value;
		NCheck(FMCRecordGetVersion(GetHandle(), &value));
		return NVersion(value);
	}

	FmcrMinutiaFormat GetMinutiaFormat() const
	{
		FmcrMinutiaFormat value;
		NCheck(FMCRecordGetMinutiaFormat(GetHandle(), &value));
		return value;
	}

	BdifFPImpressionType GetImpressionType() const
	{
		BdifFPImpressionType value;
		NCheck(FMCRecordGetImpressionType(GetHandle(), &value));
		return value;
	}

	void SetImpressionType(BdifFPImpressionType value)
	{
		NCheck(FMCRecordSetImpressionType(GetHandle(), value));
	}

	SmartCards::BerTlv GetVendorData() const
	{
		SmartCards::HBerTlv hValue;
		NCheck(FMCRecordGetVendorData(GetHandle(), &hValue));
		return FromHandle<SmartCards::BerTlv>(hValue);
	}

	void SetVendorData(const SmartCards::BerTlv & value)
	{
		NCheck(FMCRecordSetVendorData(GetHandle(), value.GetHandle()));
	}

	bool ValidateMinutiaeUniqueness() const
	{
		NBool value;
		NCheck(FMCRecordValidateMinutiaeUniqueness(GetHandle(), &value));
		return value != 0;
	}

	bool GetHasFourNeighborRidgeCounts() const
	{
		NBool value;
		NCheck(FMCRecordHasFourNeighborRidgeCounts(GetHandle(), &value));
		return value != 0;
	}

	void SetHasFourNeighborRidgeCounts(bool value)
	{
		NCheck(FMCRecordSetHasFourNeighborRidgeCounts(GetHandle(), value ? NTrue : NFalse));
	}

	bool GetHasEightNeighborRidgeCounts() const
	{
		NBool value;
		NCheck(FMCRecordHasEightNeighborRidgeCounts(GetHandle(), &value));
		return value != 0;
	}

	void SetHasEightNeighborRidgeCounts(bool value)
	{
		NCheck(FMCRecordSetHasEightNeighborRidgeCounts(GetHandle(), value ? NTrue : NFalse));
	}

	MinutiaCollection GetMinutiae()
	{
		return MinutiaCollection(*this);
	}

	const MinutiaCollection GetMinutiae() const
	{
		return MinutiaCollection(*this);
	}

	MinutiaFourNeighborsCollection GetMinutiaeFourNeighbors()
	{
		return MinutiaFourNeighborsCollection(*this);
	}

	const MinutiaFourNeighborsCollection GetMinutiaeFourNeighbors() const
	{
		return MinutiaFourNeighborsCollection(*this);
	}

	MinutiaEightNeighborsCollection GetMinutiaeEightNeighbors()
	{
		return MinutiaEightNeighborsCollection(*this);
	}

	const MinutiaEightNeighborsCollection GetMinutiaeEightNeighbors() const
	{
		return MinutiaEightNeighborsCollection(*this);
	}

	CoreCollection GetCores()
	{
		return CoreCollection(*this);
	}

	const CoreCollection GetCores() const
	{
		return CoreCollection(*this);
	}

	DeltaCollection GetDeltas()
	{
		return DeltaCollection(*this);
	}

	const DeltaCollection GetDeltas() const
	{
		return DeltaCollection(*this);
	}
};

}}}

#endif // !FMC_RECORD_HPP_INCLUDED
