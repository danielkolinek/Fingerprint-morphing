#ifndef IIR_IRIS_IMAGE_HPP_INCLUDED
#define IIR_IRIS_IMAGE_HPP_INCLUDED

#include <Core/NDateTime.hpp>
#include <Images/NImage.hpp>
#include <Biometrics/Standards/BdifTypes.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
using ::Neurotec::Images::HNImage;
#include <Biometrics/Standards/IirIrisImage.h>
}}}

N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, IirCaptureDeviceTechnology)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, IirImageKind)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, IirPreviousCompression)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, IirImageFormat)

namespace Neurotec { namespace Biometrics { namespace Standards
{
#undef IIR_MAX_IRIS_IMAGE_COUNT

#undef IIRII_MAX_QUALITY_BLOCK_COUNT
#undef IIRII_COORDINATE_UNDEFINED
#undef IIRII_CAPTURE_DEVICE_VENDOR_UNDEFINED
#undef IIRII_CAPTURE_DEVICE_TYPE_UNDEFINED
#undef IIRII_RANGE_UNASSIGNED
#undef IIRII_RANGE_FAILED
#undef IIRII_RANGE_OVERFLOW

#include <Core/NNoDeprecate.h>
const N_DEPRECATED("deprecated, use BDIF_MAX_QUALITY_BLOCK_COUNT instead.") NInt IIRII_MAX_QUALITY_BLOCK_COUNT = 255;
#include <Core/NReDeprecate.h>

const NInt IIRII_COORDINATE_UNDEFINED = 0;
const NInt IIRII_CAPTURE_DEVICE_VENDOR_UNDEFINED = 0;
const NInt IIRII_CAPTURE_DEVICE_TYPE_UNDEFINED = 0;
const NInt IIRII_RANGE_UNASSIGNED = 0;
const NInt IIRII_RANGE_FAILED = 1;
const NInt IIRII_RANGE_OVERFLOW = 0xFFFE;

class IIRecord;

class IirIrisImage : public NObject
{
	N_DECLARE_OBJECT_CLASS(IirIrisImage, NObject)

public:
	class QualityBlockCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<BdifQualityBlock, IirIrisImage,
		IirIrisImageGetQualityBlockCount, IirIrisImageGetQualityBlock, IirIrisImageGetQualityBlocks>
	{
		QualityBlockCollection(const IirIrisImage & owner)
		{
			SetOwner(owner);
		}

		friend class IirIrisImage;
	public:
		NInt GetCapacity() const
		{
			NInt value;
			NCheck(IirIrisImageGetQualityBlockCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(IirIrisImageSetQualityBlockCapacity(this->GetOwnerHandle(), value));
		}
	
		void Set(NInt index, const BdifQualityBlock & value)
		{
			NCheck(IirIrisImageSetQualityBlock(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const BdifQualityBlock & value)
		{
			NInt index;
			NCheck(IirIrisImageAddQualityBlock(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const BdifQualityBlock & value)
		{
			NCheck(IirIrisImageInsertQualityBlock(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(IirIrisImageRemoveQualityBlockAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(IirIrisImageClearQualityBlocks(this->GetOwnerHandle()));
		}
	};

private:
	static HIirIrisImage Create(BdifStandard standard, NVersion version)
	{
		HIirIrisImage handle;
		NCheck(IirIrisImageCreateEx(standard, version.GetValue(), &handle));
		return handle;
	}

public:
	static NType IirCaptureDeviceTechnologyNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(IirCaptureDeviceTechnology), true);
	}

	static NType IirImageKindNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(IirImageKind), true);
	}

	static NType IirPreviousCompressionNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(IirPreviousCompression), true);
	}

	static NType IirImageFormatNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(IirImageFormat), true);
	}

	IirIrisImage(BdifStandard standard, NVersion version)
		: NObject(Create(standard, version), true)
	{
	}

	::Neurotec::Images::NImage ToNImage(NUInt flags = 0) const
	{
		HNImage hImage;
		NCheck(IirIrisImageToNImage(GetHandle(), flags, &hImage));
		return FromHandle< ::Neurotec::Images::NImage>(hImage);
	}

	void SetImage(const ::Neurotec::Images::NImage & image, NUInt flags = 0)
	{
		NCheck(IirIrisImageSetImage(GetHandle(), flags, image.GetHandle()));
	}

	BdifStandard GetStandard() const
	{
		BdifStandard value;
		NCheck(IirIrisImageGetStandard(GetHandle(), &value));
		return value;
	}

	NVersion GetVersion() const
	{
		NVersion_ value;
		NCheck(IirIrisImageGetVersion(GetHandle(), &value));
		return NVersion(value);
	}

	BdifCaptureDateTime GetCaptureDateAndTimeEx() const
	{
		BdifCaptureDateTime_ value;
		NCheck(IirIrisImageGetCaptureDateAndTimeEx(GetHandle(), &value));
		return BdifCaptureDateTime(value);
	}

	void SetCaptureDateAndTimeEx(const BdifCaptureDateTime & value)
	{
		NCheck(IirIrisImageSetCaptureDateAndTimeEx(GetHandle(), value));
	}

	IirCaptureDeviceTechnology GetCaptureDeviceTechnology() const
	{
		IirCaptureDeviceTechnology value;
		NCheck(IirIrisImageGetCaptureDeviceTechnology(GetHandle(), &value));
		return value;
	}

	void SetCaptureDeviceTechnology(IirCaptureDeviceTechnology value)
	{
		NCheck(IirIrisImageSetCaptureDeviceTechnology(GetHandle(), value));
	}

	NUShort GetCaptureDeviceVendorId() const
	{
		NUShort value;
		NCheck(IirIrisImageGetCaptureDeviceVendorId(GetHandle(), &value));
		return value;
	}

	void SetCaptureDeviceVendorId(NUShort value)
	{
		NCheck(IirIrisImageSetCaptureDeviceVendorId(GetHandle(), value));
	}

	NUShort GetCaptureDeviceTypeId() const
	{
		NUShort value;
		NCheck(IirIrisImageGetCaptureDeviceTypeId(GetHandle(), &value));
		return value;
	}

	void SetCaptureDeviceTypeId(NUShort value)
	{
		NCheck(IirIrisImageSetCaptureDeviceTypeId(GetHandle(), value));
	}

	BdifEyePosition GetPosition() const
	{
		BdifEyePosition value;
		NCheck(IirIrisImageGetPosition(GetHandle(), &value));
		return value;
	}

	void SetPosition(BdifEyePosition value)
	{
		NCheck(IirIrisImageSetPosition(GetHandle(), value));
	}

	NInt GetImageNumber() const
	{
		NInt value;
		NCheck(IirIrisImageGetImageNumber(GetHandle(), &value));
		return value;
	}

	NByte GetQuality() const
	{
		NByte value;
		NCheck(IirIrisImageGetQuality(GetHandle(), &value));
		return value;
	}

	void SetQuality(NByte value)
	{
		NCheck(IirIrisImageSetQuality(GetHandle(), value));
	}

	IirImageKind GetImageType() const
	{
		IirImageKind value;
		NCheck(IirIrisImageGetImageType(GetHandle(), &value));
		return value;
	}

	void SetImageType(IirImageKind value)
	{
		NCheck(IirIrisImageSetImageType(GetHandle(), value));
	}

	IirImageFormat GetImageFormat() const
	{
		IirImageFormat value;
		NCheck(IirIrisImageGetImageFormat(GetHandle(), &value));
		return value;
	}

	void SetImageFormat(IirImageFormat value)
	{
		NCheck(IirIrisImageSetImageFormat(GetHandle(), value));
	}

	BdifIrisOrientation GetIrisHorzOrientation() const
	{
		BdifIrisOrientation value;
		NCheck(IirIrisImageGetIrisHorzOrientation(GetHandle(), &value));
		return value;
	}

	void SetIrisHorzOrientation(BdifIrisOrientation value)
	{
		NCheck(IirIrisImageSetIrisHorzOrientation(GetHandle(), value));
	}

	BdifIrisOrientation GetIrisVertOrientation() const
	{
		BdifIrisOrientation value;
		NCheck(IirIrisImageGetIrisVertOrientation(GetHandle(), &value));
		return value;
	}

	void SetIrisVertOrientation(BdifIrisOrientation value)
	{
		NCheck(IirIrisImageSetIrisVertOrientation(GetHandle(), value));
	}

	IirPreviousCompression GetPreviousCompression() const
	{
		IirPreviousCompression value;
		NCheck(IirIrisImageGetPreviousCompression(GetHandle(), &value));
		return value;
	}

	void SetPreviousCompression(IirPreviousCompression value)
	{
		NCheck(IirIrisImageSetPreviousCompression(GetHandle(), value));
	}

	NUShort GetImageWidth() const
	{
		NUShort value;
		NCheck(IirIrisImageGetImageWidth(GetHandle(), &value));
		return value;
	}

	void SetImageWidth(NUShort value)
	{
		NCheck(IirIrisImageSetImageWidth(GetHandle(), value));
	}

	NUShort GetImageHeight() const
	{
		NUShort value;
		NCheck(IirIrisImageGetImageHeight(GetHandle(), &value));
		return value;
	}

	void SetImageHeight(NUShort value)
	{
		NCheck(IirIrisImageSetImageHeight(GetHandle(), value));
	}

	NByte GetIntensityDepth() const
	{
		NByte value;
		NCheck(IirIrisImageGetIntensityDepth(GetHandle(), &value));
		return value;
	}

	void SetIntensityDepth(NByte value)
	{
		NCheck(IirIrisImageSetIntensityDepth(GetHandle(), value));
	}

	NUShort GetRange() const
	{
		NUShort value;
		NCheck(IirIrisImageGetRange(GetHandle(), &value));
		return value;
	}

	void SetRange(NUShort value)
	{
		NCheck(IirIrisImageSetRange(GetHandle(), value));
	}

	NUShort GetRotationAngle() const
	{
		NUShort value;
		NCheck(IirIrisImageGetRotationAngleEx(GetHandle(), &value));
		return value;
	}

	void SetRotationAngle(NUShort value)
	{
		NCheck(IirIrisImageSetRotationAngleEx(GetHandle(), value));
	}

	NUShort GetRotationAngleUncertainty() const
	{
		NUShort value;
		NCheck(IirIrisImageGetRotationAngleUncertainty(GetHandle(), &value));
		return value;
	}

	void SetRotationAngleUncertainty(NUShort value)
	{
		NCheck(IirIrisImageSetRotationAngleUncertainty(GetHandle(), value));
	}

	NUShort GetIrisCenterSmallestX() const
	{
		NUShort value;
		NCheck(IirIrisImageGetIrisCenterSmallestX(GetHandle(), &value));
		return value;
	}

	void SetIrisCenterSmallestX(NUShort value)
	{
		NCheck(IirIrisImageSetIrisCenterSmallestX(GetHandle(), value));
	}

	NUShort GetIrisCenterLargestX() const
	{
		NUShort value;
		NCheck(IirIrisImageGetIrisCenterLargestX(GetHandle(), &value));
		return value;
	}

	void SetIrisCenterLargestX(NUShort value)
	{
		NCheck(IirIrisImageSetIrisCenterLargestX(GetHandle(), value));
	}

	NUShort GetIrisCenterSmallestY() const
	{
		NUShort value;
		NCheck(IirIrisImageGetIrisCenterSmallestY(GetHandle(), &value));
		return value;
	}

	void SetIrisCenterSmallestY(NUShort value)
	{
		NCheck(IirIrisImageSetIrisCenterSmallestY(GetHandle(), value));
	}

	NUShort GetIrisCenterLargestY() const
	{
		NUShort value;
		NCheck(IirIrisImageGetIrisCenterLargestY(GetHandle(), &value));
		return value;
	}

	void SetIrisCenterLargestY(NUShort value)
	{
		NCheck(IirIrisImageSetIrisCenterLargestY(GetHandle(), value));
	}

	NUShort GetIrisDiameterSmallest() const
	{
		NUShort value;
		NCheck(IirIrisImageGetIrisDiameterSmallest(GetHandle(), &value));
		return value;
	}

	void SetIrisDiameterSmallest(NUShort value)
	{
		NCheck(IirIrisImageSetIrisDiameterSmallest(GetHandle(), value));
	}

	NUShort GetIrisDiameterLargest() const
	{
		NUShort value;
		NCheck(IirIrisImageGetIrisDiameterLargest(GetHandle(), &value));
		return value;
	}

	void SetIrisDiameterLargest(NUShort value)
	{
		NCheck(IirIrisImageSetIrisDiameterLargest(GetHandle(), value));
	}

	::Neurotec::IO::NBuffer GetImageData() const
	{
		return GetObject<HandleType, ::Neurotec::IO::NBuffer>(IirIrisImageGetImageDataN, true);
	}

	void SetImageData(const ::Neurotec::IO::NBuffer & value)
	{
		SetObject(IirIrisImageSetImageDataN, value);
	}

	QualityBlockCollection GetQualityBlocks()
	{
		return QualityBlockCollection(*this);
	}

	const QualityBlockCollection GetQualityBlocks() const
	{
		return QualityBlockCollection(*this);
	}

	IIRecord GetOwner() const;
};
}}}

#include <Biometrics/Standards/IIRecord.hpp>

namespace Neurotec { namespace Biometrics { namespace Standards
{

inline IIRecord IirIrisImage::GetOwner() const
{
	return NObject::GetOwner<IIRecord>();
}

}}}

#endif // !IIR_IRIS_IMAGE_HPP_INCLUDED
