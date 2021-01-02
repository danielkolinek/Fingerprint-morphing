#ifndef FCR_FACE_IMAGE_HPP_INCLUDED
#define FCR_FACE_IMAGE_HPP_INCLUDED

#include <Images/NImage.hpp>
#include <Biometrics/Standards/BdifTypes.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
using ::Neurotec::Images::HNImage;
#include <Biometrics/Standards/FcrFaceImage.h>
}}}

N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, FcrFaceImageType)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, FcrImageDataType)
N_DEFINE_ENUM_TYPE_TRAITS(Neurotec::Biometrics::Standards, FcrImageColorSpace)

namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Core/NNoDeprecate.h>

#undef FCRFI_MAX_FEATURE_POINT_COUNT

#undef FCRFI_SKIP_FEATURE_POINTS

const NInt FCRFI_MAX_FEATURE_POINT_COUNT = N_USHORT_MAX;

const NUInt FCRFI_SKIP_FEATURE_POINTS = 0x00010000;

class FCRecord;

class FcrFaceImage : public NObject
{
	N_DECLARE_OBJECT_CLASS(FcrFaceImage, NObject)

public:
	class FeaturePointCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<BdifFaceFeaturePoint, FcrFaceImage,
		FcrFaceImageGetFeaturePointCount, FcrFaceImageGetFeaturePoint, FcrFaceImageGetFeaturePointsEx2>
	{
		FeaturePointCollection(const FcrFaceImage & owner)
		{
			SetOwner(owner);
		}

		friend class FcrFaceImage;
	public:
		NInt GetCapacity() const
		{
			NInt value;
			NCheck(FcrFaceImageGetFeaturePointCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(FcrFaceImageSetFeaturePointCapacity(this->GetOwnerHandle(), value));
		}

		N_DEPRECATED("use NArrayWrapper<BdifFaceFeaturePoint> GetAll() instead")
		NInt GetAll(BdifFaceFeaturePoint * arValues, NInt valuesLength) const
		{
			NInt count;
			NCheck(count = FcrFaceImageGetFeaturePoints(this->GetOwnerHandle(), arValues, valuesLength));
			return count;
		}

		using ::Neurotec::Collections::NCollectionWithAllOutBase<BdifFaceFeaturePoint, FcrFaceImage,
			FcrFaceImageGetFeaturePointCount, FcrFaceImageGetFeaturePoint, FcrFaceImageGetFeaturePointsEx2>::GetAll;

		void Set(NInt index, const BdifFaceFeaturePoint & value)
		{
			NCheck(FcrFaceImageSetFeaturePoint(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const BdifFaceFeaturePoint & value)
		{
			NInt index;
			NCheck(FcrFaceImageAddFeaturePointEx(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const BdifFaceFeaturePoint & value)
		{
			NCheck(FcrFaceImageInsertFeaturePoint(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(FcrFaceImageRemoveFeaturePointAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(FcrFaceImageClearFeaturePoints(this->GetOwnerHandle()));
		}
	};

	class QualityBlockCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<BdifQualityBlock, FcrFaceImage,
		FcrFaceImageGetQualityBlockCount, FcrFaceImageGetQualityBlock, FcrFaceImageGetQualityBlocks>
	{
		QualityBlockCollection(const FcrFaceImage & owner)
		{
			SetOwner(owner);
		}

		friend class FcrFaceImage;
	public:
		NInt GetCapacity() const
		{
			NInt value;
			NCheck(FcrFaceImageGetQualityBlockCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(FcrFaceImageSetQualityBlockCapacity(this->GetOwnerHandle(), value));
		}
	
		void Set(NInt index, const BdifQualityBlock & value)
		{
			NCheck(FcrFaceImageSetQualityBlock(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const BdifQualityBlock & value)
		{
			NInt index;
			NCheck(FcrFaceImageAddQualityBlock(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const BdifQualityBlock & value)
		{
			NCheck(FcrFaceImageInsertQualityBlock(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(FcrFaceImageRemoveQualityBlockAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(FcrFaceImageClearQualityBlocks(this->GetOwnerHandle()));
		}
	};

private:
	static HFcrFaceImage Create(BdifStandard standard, NVersion version)
	{
		HFcrFaceImage handle;
		NCheck(FcrFaceImageCreate(standard, version.GetValue(), &handle));
		return handle;
	}

public:
	static NType FcrImageDataTypeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(FcrImageDataType), true);
	}

	static NType FcrFaceImageTypeNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(FcrFaceImageType), true);
	}

	static NType FcrImageColorSpaceNativeTypeOf()
	{
		return NObject::GetObject<NType>(N_TYPE_OF(FcrImageColorSpace), true);
	}

	explicit FcrFaceImage(BdifStandard standard, NVersion version)
		: NObject(Create(standard, version), true)
	{
	}

	::Neurotec::Images::NImage ToNImage(NUInt flags = 0) const
	{
		HNImage hImage;
		NCheck(FcrFaceImageToNImage(GetHandle(), flags, &hImage));
		return FromHandle< ::Neurotec::Images::NImage>(hImage);
	}

	void SetImage(const ::Neurotec::Images::NImage & image, NUInt flags = 0)
	{
		NCheck(FcrFaceImageSetImage(GetHandle(), flags, image.GetHandle()));
	}

	BdifStandard GetStandard() const
	{
		BdifStandard value;
		NCheck(FcrFaceImageGetStandard(GetHandle(), &value));
		return value;
	}

	NVersion GetVersion() const
	{
		NVersion_ value;
		NCheck(FcrFaceImageGetVersion(GetHandle(), &value));
		return NVersion(value);
	}

	BdifCaptureDateTime GetCaptureDateAndTime() const
	{
		BdifCaptureDateTime_ value;
		NCheck(FcrFaceImageGetCaptureDateAndTime(GetHandle(), &value));
		return BdifCaptureDateTime(value);
	}

	void SetCaptureDateAndTime(const BdifCaptureDateTime & value)
	{
		NCheck(FcrFaceImageSetCaptureDateAndTime(GetHandle(), value));
	}

	NUShort GetCaptureDeviceVendorId() const
	{
		NUShort value;
		NCheck(FcrFaceImageGetCaptureDeviceVendorId(GetHandle(), &value));
		return value;
	}

	void SetCaptureDeviceVendorId(NUShort value)
	{
		NCheck(FcrFaceImageSetCaptureDeviceVendorId(GetHandle(), value));
	}
	
	BdifGender GetGender() const
	{
		BdifGender value;
		NCheck(FcrFaceImageGetGender(GetHandle(), &value));
		return value;
	}

	void SetGender(BdifGender value)
	{
		NCheck(FcrFaceImageSetGender(GetHandle(), value));
	}

	BdifEyeColor GetEyeColor() const
	{
		BdifEyeColor value;
		NCheck(FcrFaceImageGetEyeColor(GetHandle(), &value));
		return value;
	}

	void SetEyeColor(BdifEyeColor value)
	{
		NCheck(FcrFaceImageSetEyeColor(GetHandle(), value));
	}

	BdifHairColor GetHairColor() const
	{
		BdifHairColor value;
		NCheck(FcrFaceImageGetHairColor(GetHandle(), &value));
		return value;
	}

	void SetHairColor(BdifHairColor value)
	{
		NCheck(FcrFaceImageSetHairColor(GetHandle(), value));
	}

	NByte GetSubjectHeight() const
	{
		NByte value;
		NCheck(FcrFaceImageGetSubjectHeight(GetHandle(), &value));
		return value;
	}

	void SetSubjectHeight(NByte value)
	{
		NCheck(FcrFaceImageSetSubjectHeight(GetHandle(), value));
	}

	BdifFaceProperties GetProperties() const
	{
		BdifFaceProperties value;
		NCheck(FcrFaceImageGetProperties(GetHandle(), &value));
		return value;
	}

	void SetProperties(BdifFaceProperties value)
	{
		NCheck(FcrFaceImageSetProperties(GetHandle(), value));
	}

	BdifFaceExpression GetExpression() const
	{
		BdifFaceExpression value;
		NCheck(FcrFaceImageGetExpression(GetHandle(), &value));
		return value;
	}

	BdifFaceExpressionBitMask GetExpressionBitMask() const
	{
		BdifFaceExpressionBitMask value;
		NCheck(FcrFaceImageGetExpressionBitMask(GetHandle(), &value));
		return value;
	}

	NUShort GetVendorExpression() const
	{
		NUShort value;
		NCheck(FcrFaceImageGetVendorExpression(GetHandle(), &value));
		return value;
	}

	void SetExpression(BdifFaceExpression value, BdifFaceExpressionBitMask valueBitMask, NUShort vendorValue)
	{
		NCheck(FcrFaceImageSetExpressionEx(GetHandle(), value, valueBitMask, vendorValue));
	}

	NByte GetPoseAngleYaw() const
	{
		NByte value;
		NCheck(FcrFaceImageGetPoseAngleYaw(GetHandle(), &value));
		return value;
	}

	void SetPoseAngleYaw(NByte value)
	{
		NCheck(FcrFaceImageSetPoseAngleYaw(GetHandle(), value));
	}

	NByte GetPoseAnglePitch() const
	{
		NByte value;
		NCheck(FcrFaceImageGetPoseAnglePitch(GetHandle(), &value));
		return value;
	}

	void SetPoseAnglePitch(NByte value)
	{
		NCheck(FcrFaceImageSetPoseAnglePitch(GetHandle(), value));
	}

	NByte GetPoseAngleRoll() const
	{
		NByte value;
		NCheck(FcrFaceImageGetPoseAngleRoll(GetHandle(), &value));
		return value;
	}

	void SetPoseAngleRoll(NByte value)
	{
		NCheck(FcrFaceImageSetPoseAngleRoll(GetHandle(), value));
	}

	void GetPoseAngle(NByte * pYaw, NByte * pPitch, NByte * pRoll) const
	{
		NCheck(FcrFaceImageGetPoseAngle(GetHandle(), pYaw, pPitch, pRoll));
	}

	void SetPoseAngle(NByte yaw, NByte pitch, NByte roll)
	{
		NCheck(FcrFaceImageSetPoseAngle(GetHandle(), yaw, pitch, roll));
	}

	NByte GetPoseAngleUncertaintyYaw() const
	{
		NByte value;
		NCheck(FcrFaceImageGetPoseAngleUncertaintyYaw(GetHandle(), &value));
		return value;
	}

	NByte GetPoseAngleUncertaintyPitch() const
	{
		NByte value;
		NCheck(FcrFaceImageGetPoseAngleUncertaintyPitch(GetHandle(), &value));
		return value;
	}

	NByte GetPoseAngleUncertaintyRoll() const
	{
		NByte value;
		NCheck(FcrFaceImageGetPoseAngleUncertaintyRoll(GetHandle(), &value));
		return value;
	}

	void GetPoseAngleUncertainty(NByte * pYaw, NByte * pPitch, NByte * pRoll) const
	{
		NCheck(FcrFaceImageGetPoseAngleUncertainty(GetHandle(), pYaw, pPitch, pRoll));
	}

	void SetPoseAngleUncertainty(NByte yaw, NByte pitch, NByte roll)
	{
		NCheck(FcrFaceImageSetPoseAngleUncertainty(GetHandle(), yaw, pitch, roll));
	}

	FcrFaceImageType GetFaceImageType() const
	{
		FcrFaceImageType value;
		NCheck(FcrFaceImageGetFaceImageType(GetHandle(), &value));
		return value;
	}

	void SetFaceImageType(FcrFaceImageType value)
	{
		NCheck(FcrFaceImageSetFaceImageType(GetHandle(), value));
	}

	FcrImageDataType GetImageDataType() const
	{
		FcrImageDataType value;
		NCheck(FcrFaceImageGetImageDataType(GetHandle(), &value));
		return value;
	}

	void SetImageDataType(FcrImageDataType value)
	{
		NCheck(FcrFaceImageSetImageDataType(GetHandle(), value));
	}

	NUShort GetWidth() const
	{
		NUShort value;
		NCheck(FcrFaceImageGetWidth(GetHandle(), &value));
		return value;
	}

	void SetWidth(NUShort value)
	{
		NCheck(FcrFaceImageSetWidth(GetHandle(), value));
	}

	NUShort GetHeight() const
	{
		NUShort value;
		NCheck(FcrFaceImageGetHeight(GetHandle(), &value));
		return value;
	}

	void SetHeight(NUShort value)
	{
		NCheck(FcrFaceImageSetHeight(GetHandle(), value));
	}

	BdifFaceSpatialSamplingRateLevel GetSpatialSamplingRateLevel() const
	{
		BdifFaceSpatialSamplingRateLevel value;
		NCheck(FcrFaceImageGetSpatialSamplingRateLevel(GetHandle(), &value));
		return value;
	}

	void SetSpatialSamplingRateLevel(BdifFaceSpatialSamplingRateLevel value)
	{
		NCheck(FcrFaceImageSetSpatialSamplingRateLevel(GetHandle(), value));
	}

	BdifFacePostAcquisitionProcessing GetPostAcquisitionProcessing() const
	{
		BdifFacePostAcquisitionProcessing value;
		NCheck(FcrFaceImageGetPostAcquisitionProcessing(GetHandle(), &value));
		return value;
	}

	void SetPostAcquisitionProcessing(BdifFacePostAcquisitionProcessing value)
	{
		NCheck(FcrFaceImageSetPostAcquisitionProcessing(GetHandle(), value));
	}

	NUShort GetCrossReference() const
	{
		NUShort value;
		NCheck(FcrFaceImageGetCrossReference(GetHandle(), &value));
		return value;
	}

	void SetCrossReference(NUShort value)
	{
		NCheck(FcrFaceImageSetCrossReference(GetHandle(), value));
	}

	FcrImageColorSpace GetImageColorSpace() const
	{
		FcrImageColorSpace value;
		NCheck(FcrFaceImageGetImageColorSpace(GetHandle(), &value));
		return value;
	}

	NByte GetVendorImageColorSpace() const
	{
		NByte value;
		NCheck(FcrFaceImageGetVendorImageColorSpace(GetHandle(), &value));
		return value;
	}

	void SetImageColorSpace(FcrImageColorSpace value, NByte vendorValue)
	{
		NCheck(FcrFaceImageSetImageColorSpace(GetHandle(), value, vendorValue));
	}

	BdifImageSourceType GetSourceType() const
	{
		BdifImageSourceType value;
		NCheck(FcrFaceImageGetSourceType(GetHandle(), &value));
		return value;
	}

	NByte GetVendorSourceType() const
	{
		NByte value;
		NCheck(FcrFaceImageGetVendorSourceType(GetHandle(), &value));
		return value;
	}

	void SetSourceType(BdifImageSourceType value, NByte vendorValue)
	{
		NCheck(FcrFaceImageSetSourceType(GetHandle(), value, vendorValue));
	}

	NUShort GetDeviceType() const
	{
		NUShort value;
		NCheck(FcrFaceImageGetDeviceType(GetHandle(), &value));
		return value;
	}

	void SetDeviceType(NUShort value)
	{
		NCheck(FcrFaceImageSetDeviceType(GetHandle(), value));
	}

	NUShort GetQuality() const
	{
		NUShort value;
		NCheck(FcrFaceImageGetQuality(GetHandle(), &value));
		return value;
	}

	void SetQuality(NUShort value)
	{
		NCheck(FcrFaceImageSetQuality(GetHandle(), value));
	}

	::Neurotec::IO::NBuffer GetImageData() const
	{
		return GetObject<HandleType, ::Neurotec::IO::NBuffer>(FcrFaceImageGetImageDataN, true);
	}

	void SetImageData(const ::Neurotec::IO::NBuffer & value)
	{
		SetObject(FcrFaceImageSetImageDataN, value);
	}

	FeaturePointCollection GetFeaturePoints()
	{
		return FeaturePointCollection(*this);
	}

	const FeaturePointCollection GetFeaturePoints() const
	{
		return FeaturePointCollection(*this);
	}

	QualityBlockCollection GetQualityBlocks()
	{
		return QualityBlockCollection(*this);
	}

	const QualityBlockCollection GetQualityBlocks() const
	{
		return QualityBlockCollection(*this);
	}

	FCRecord GetOwner() const;
};
#include <Core/NReDeprecate.h>
}}}

#include <Biometrics/Standards/FCRecord.hpp>

namespace Neurotec { namespace Biometrics { namespace Standards
{

inline FCRecord FcrFaceImage::GetOwner() const
{
	return NObject::GetOwner<FCRecord>();
}

}}}

#endif // !FCR_FACE_IMAGE_HPP_INCLUDED
