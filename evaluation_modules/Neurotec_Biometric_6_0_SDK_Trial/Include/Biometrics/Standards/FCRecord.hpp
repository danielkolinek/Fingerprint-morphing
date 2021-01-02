#include <Biometrics/Standards/FcrFaceImage.hpp>

#ifndef FC_RECORD_HPP_INCLUDED
#define FC_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/BdifTypes.hpp>
#include <Images/NImage.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
using ::Neurotec::Images::HNImage;
#include <Biometrics/Standards/FCRecord.h>
}}}

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef FCR_VERSION_ANSI_1_0
#undef FCR_VERSION_ISO_1_0
#undef FCR_VERSION_ISO_3_0
#undef FCR_VERSION_ANSI_CURRENT
#undef FCR_VERSION_ISO_CURRENT

#undef FCR_MAX_FACE_IMAGE_COUNT
#undef FCR_PROCESS_FIRST_FACE_IMAGE_ONLY

const NVersion FCR_VERSION_ANSI_1_0(0x0100);
const NVersion FCR_VERSION_ISO_1_0(0x0100);
const NVersion FCR_VERSION_ISO_3_0(0x0300);

const NVersion FCR_VERSION_ANSI_CURRENT(FCR_VERSION_ANSI_1_0);
const NVersion FCR_VERSION_ISO_CURRENT(FCR_VERSION_ISO_3_0);

const NInt FCR_MAX_FACE_IMAGE_COUNT = N_USHORT_MAX;
const NUInt FCR_PROCESS_FIRST_FACE_IMAGE_ONLY = 0x00000100;

class FCRecord : public NObject
{
	N_DECLARE_OBJECT_CLASS(FCRecord, NObject)

public:
	class FaceImageCollection : public ::Neurotec::Collections::NCollectionBase<FcrFaceImage, FCRecord,
		FCRecordGetFaceImageCount, FCRecordGetFaceImage>
	{
		FaceImageCollection(const FCRecord & owner)
		{
			SetOwner(owner);
		}

		friend class FCRecord;
	public:
		NInt GetCapacity() const
		{
			NInt value;
			NCheck(FCRecordGetFaceImageCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(FCRecordSetFaceImageCapacity(this->GetOwnerHandle(), value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(FCRecordRemoveFaceImageAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(FCRecordClearFaceImages(this->GetOwnerHandle()));
		}

		NInt Add(const FcrFaceImage & value)
		{
			NInt index;
			NCheck(FCRecordAddFaceImageEx(this->GetOwnerHandle(), value.GetHandle(), &index));
			return index;
		}
	};

private:
	static HFCRecord Create(BdifStandard standard, NVersion version, NUInt flags)
	{
		HFCRecord handle;
		NCheck(FCRecordCreateEx(standard, version.GetValue(), flags, &handle));
		return handle;
	}

	static HFCRecord Create(const ::Neurotec::IO::NBuffer & buffer, BdifStandard standard, NUInt flags, NSizeType * pSize)
	{
		HFCRecord handle;
		NCheck(FCRecordCreateFromMemoryN(buffer.GetHandle(), flags, standard, pSize, &handle));
		return handle;
	}

	static HFCRecord Create(const void * pBuffer, NSizeType bufferSize, BdifStandard standard, NUInt flags, NSizeType * pSize)
	{
		HFCRecord handle;
		NCheck(FCRecordCreateFromMemory(pBuffer, bufferSize, flags, standard, pSize, &handle));
		return handle;
	}

	static HFCRecord Create(const FCRecord & srcRecord, BdifStandard standard, NVersion version, NUInt flags)
	{
		HFCRecord handle;
		NCheck(FCRecordCreateFromFCRecordEx(srcRecord.GetHandle(), flags, standard, version.GetValue(), &handle));
		return handle;
	}

	static HFCRecord Create(const ::Neurotec::Images::NImage & image, FcrFaceImageType faceImageType, FcrImageDataType imageDataType, BdifStandard standard, NVersion version, NUInt flags)
	{
		HFCRecord handle;
		NCheck(FCRecordCreateFromNImageEx(image.GetHandle(), faceImageType, imageDataType, flags, standard, version.GetValue(), &handle));
		return handle;
	}

public:
	explicit FCRecord(BdifStandard standard, NVersion version, NUInt flags = 0)
		: NObject(Create(standard, version, flags), true)
	{
	}

	FCRecord(const ::Neurotec::IO::NBuffer & buffer, BdifStandard standard, NUInt flags = 0, NSizeType * pSize = NULL)
		: NObject(Create(buffer, standard, flags, pSize), true)
	{
	}

	FCRecord(const void * pBuffer, NSizeType bufferSize, BdifStandard standard, NUInt flags = 0, NSizeType * pSize = NULL)
		: NObject(Create(pBuffer, bufferSize, standard, flags, pSize), true)
	{
	}

	FCRecord(const FCRecord & srcRecord, BdifStandard standard, NVersion version, NUInt flags = 0)
		: NObject(Create(srcRecord, standard, version, flags), true)
	{
	}

	FCRecord(const ::Neurotec::Images::NImage & image, FcrFaceImageType faceImageType, FcrImageDataType imageDataType, BdifStandard standard, NVersion version, NUInt flags = 0)
		: NObject(Create(image, faceImageType, imageDataType, standard, version, flags), true)
	{
	}

	BdifStandard GetStandard() const
	{
		BdifStandard value;
		NCheck(FCRecordGetStandard(GetHandle(), &value));
		return value;
	}

	NVersion GetVersion() const
	{
		NVersion_ value;
		NCheck(FCRecordGetVersion(GetHandle(), &value));
		return NVersion(value);
	}

	bool GetCertificationFlag() const
	{
		NBool value;
		NCheck(FCRecordGetCertificationFlag(GetHandle(), &value));
		return value != 0;
	}

	BdifFaceTemporalSemantics GetTemporalSemantics() const
	{
		BdifFaceTemporalSemantics value;
		NCheck(FCRecordGetTemporalSemantics(GetHandle(), &value));
		return value;
	}

	NUShort GetTemporalSemanticsInMilliseconds() const
	{
		NUShort value;
		NCheck(FCRecordGetTemporalSemanticsInMilliseconds(GetHandle(), &value));
		return value;
	}

	void SetTemporalSemantics(const BdifFaceTemporalSemantics value,  NUShort valueInMilliseconds)
	{
		NCheck(FCRecordSetTemporalSemantics(GetHandle(), value, valueInMilliseconds));
	}

	FaceImageCollection GetFaceImages()
	{
		return FaceImageCollection(*this);
	}

	const FaceImageCollection GetFaceImages() const
	{
		return FaceImageCollection(*this);
	}
};

}}}

#endif // !FC_RECORD_HPP_INCLUDED
