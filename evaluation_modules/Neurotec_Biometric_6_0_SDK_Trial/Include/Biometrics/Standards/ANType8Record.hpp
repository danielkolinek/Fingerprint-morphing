#ifndef AN_TYPE_8_RECORD_HPP_INCLUDED
#define AN_TYPE_8_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANImageBinaryRecord.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Biometrics/Standards/ANType8Record.h>
}}}

N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSignatureType)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANSignatureRepresentationType)

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef AN_TYPE_8_RECORD_FIELD_LEN
#undef AN_TYPE_8_RECORD_FIELD_IDC

#undef AN_TYPE_8_RECORD_FIELD_SIG
#undef AN_TYPE_8_RECORD_FIELD_SRT

#undef AN_TYPE_8_RECORD_FIELD_ISR
#undef AN_TYPE_8_RECORD_FIELD_HLL
#undef AN_TYPE_8_RECORD_FIELD_VLL
#undef AN_TYPE_8_RECORD_FIELD_DATA

const NInt AN_TYPE_8_RECORD_FIELD_LEN = AN_RECORD_FIELD_LEN;
const NInt AN_TYPE_8_RECORD_FIELD_IDC = AN_RECORD_FIELD_IDC;

const NInt AN_TYPE_8_RECORD_FIELD_SIG = 3;
const NInt AN_TYPE_8_RECORD_FIELD_SRT = 4;

const NInt AN_TYPE_8_RECORD_FIELD_ISR = AN_IMAGE_BINARY_RECORD_FIELD_ISR;
const NInt AN_TYPE_8_RECORD_FIELD_HLL = AN_IMAGE_BINARY_RECORD_FIELD_HLL;
const NInt AN_TYPE_8_RECORD_FIELD_VLL = AN_IMAGE_BINARY_RECORD_FIELD_VLL;
const NInt AN_TYPE_8_RECORD_FIELD_DATA = AN_RECORD_FIELD_DATA;

class ANPenVector : public ANPenVector_
{
	N_DECLARE_STRUCT_CLASS(ANPenVector)

public:
	ANPenVector(NUShort x, NUShort y, NByte pressure)
	{
		X = x;
		Y = y;
		Pressure = pressure;
	}
};

}}}

N_DEFINE_STRUCT_TYPE_TRAITS(Neurotec::Biometrics::Standards, ANPenVector)

namespace Neurotec { namespace Biometrics { namespace Standards
{

#include <Core/NNoDeprecate.h>
class ANType8Record : public ANImageBinaryRecord
{
	N_DECLARE_OBJECT_CLASS(ANType8Record, ANImageBinaryRecord)

public:
	class PenVectorCollection : public ::Neurotec::Collections::NCollectionBase<ANPenVector, ANType8Record,
		ANType8RecordGetPenVectorCount, ANType8RecordGetPenVector>
	{
		PenVectorCollection(const ANType8Record & owner)
		{
			SetOwner(owner);
		}

		friend class ANType8Record;
	public:
		N_DEPRECATED("use NArrayWrapper<ANPenVector> GetAll() instead")
		NInt GetAll(ANPenVector * arValues, NInt valuesLength) const
		{
			return NCheck(ANType8RecordGetPenVectorsEx(this->GetOwnerHandle(), arValues, valuesLength));
		}

		NArrayWrapper<ANPenVector> GetAll() const
		{
			ANPenVector::NativeType * arValues = NULL;
			NInt valueCount = 0;
			NCheck(ANType8RecordGetPenVectors(this->GetOwnerHandle(), &arValues, &valueCount));
			return NArrayWrapper<ANPenVector>(arValues, valueCount);
		}

		void Set(NInt index, const ANPenVector & value)
		{
			NCheck(ANType8RecordSetPenVector(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const ANPenVector & value)
		{
			NInt index;
			NCheck(ANType8RecordAddPenVectorEx(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const ANPenVector & value)
		{
			NCheck(ANType8RecordInsertPenVector(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(ANType8RecordRemovePenVectorAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(ANType8RecordClearPenVectors(this->GetOwnerHandle()));
		}
	};

private:
	static HANType8Record Create(NVersion version, NInt idc, NUInt flags)
	{
		HANType8Record handle;
		NCheck(ANType8RecordCreate(version.GetValue(), idc, flags, &handle));
		return handle;
	}

	static HANType8Record Create(NVersion version, NInt idc, ANSignatureType st, const ANPenVector * arPenVectors, NInt penVectorCount, NUInt flags)
	{
		HANType8Record handle;
		NCheck(ANType8RecordCreateFromVectors(version.GetValue(), idc, st, arPenVectors, penVectorCount, flags, &handle));
		return handle;
	}

	static HANType8Record Create(NVersion version, NInt idc, ANSignatureType st, ANSignatureRepresentationType srt, NBool isr,
		const ::Neurotec::Images::NImage & image, NUInt flags)
	{
		HANType8Record handle;
		NCheck(ANType8RecordCreateFromNImage(version.GetValue(), idc, st, srt, isr, image.GetHandle(), flags, &handle));
		return handle;
	}
public:
	explicit ANType8Record(NVersion version, NInt idc, NUInt flags = 0)
		: ANImageBinaryRecord(Create(version, idc, flags), true)
	{
	}

	ANType8Record(NVersion version, NInt idc, ANSignatureType st, ANSignatureRepresentationType srt, NBool isr, const ::Neurotec::Images::NImage & image, NUInt flags = 0)
		: ANImageBinaryRecord(Create(version, idc, st, srt, isr, image, flags), true)
	{
	}

	ANType8Record(NVersion version, NInt idc, ANSignatureType st, const ANPenVector * arPenVectors, NInt penVectorCount, NUInt flags = 0)
		: ANImageBinaryRecord(Create(version, idc, st, arPenVectors, penVectorCount, flags), true)
	{
	}

	static NType ANSignatureTypeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANSignatureType), true);
	}

	static NType ANSignatureRepresentationTypeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(ANSignatureRepresentationType), true);
	}

	ANSignatureType GetSignatureType() const
	{
		ANSignatureType value;
		NCheck(ANType8RecordGetSignatureType(GetHandle(), &value));
		return value;
	}


	void SetSignatureType(ANSignatureType value)
	{
		NCheck(ANType8RecordSetSignatureType(GetHandle(), value));
	}

	ANSignatureRepresentationType GetSignatureRepresentationType() const
	{
		ANSignatureRepresentationType value;
		NCheck(ANType8RecordGetSignatureRepresentationType(GetHandle(), &value));
		return value;
	}

	void SetSignatureRepresentationType(ANSignatureRepresentationType value)
	{
		NCheck(ANType8RecordSetSignatureRepresentationType(GetHandle(), value));
	}

	PenVectorCollection GetPenVectors()
	{
		return PenVectorCollection(*this);
	}

	const PenVectorCollection GetPenVectors() const
	{
		return PenVectorCollection(*this);
	}
};
#include <Core/NReDeprecate.h>

}}}

#endif // !AN_TYPE_8_RECORD_HPP_INCLUDED
