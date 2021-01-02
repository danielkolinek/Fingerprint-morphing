#ifndef NL_ATTRIBUTES_HPP_INCLUDED
#define NL_ATTRIBUTES_HPP_INCLUDED

#include <Biometrics/NBiometricAttributes.hpp>
#include <Biometrics/NLTemplate.hpp>
#include <Geometry/NGeometry.hpp>
#include <Images/NImage.hpp>
namespace Neurotec { namespace Biometrics
{
using ::Neurotec::Geometry::NRect_;
using ::Neurotec::Images::HNImage;
#include <Biometrics/NLAttributes.h>
}}

namespace Neurotec { namespace Biometrics
{

class NFace;

class NLAttributes : public NBiometricAttributes
{
	N_DECLARE_OBJECT_CLASS(NLAttributes, NBiometricAttributes)

public:
	class FeaturePointCollection : public ::Neurotec::Collections::NCollectionWithAllOutBase<NLFeaturePoint, NLAttributes,
		NLAttributesGetFeaturePointCount, NLAttributesGetFeaturePoint, NLAttributesGetFeaturePoints>
	{
		FeaturePointCollection(const NLAttributes & owner)
		{
			SetOwner(owner);
		}

		friend class NLAttributes;
	public:
		NInt GetCapacity() const
		{
			NInt value;
			NCheck(NLAttributesGetFeaturePointCapacity(this->GetOwnerHandle(), &value));
			return value;
		}

		void SetCapacity(NInt value)
		{
			NCheck(NLAttributesSetFeaturePointCapacity(this->GetOwnerHandle(), value));
		}

		void Set(NInt index, const NLFeaturePoint & value)
		{
			NCheck(NLAttributesSetFeaturePoint(this->GetOwnerHandle(), index, &value));
		}

		NInt Add(const NLFeaturePoint & value)
		{
			NInt index;
			NCheck(NLAttributesAddFeaturePoint(this->GetOwnerHandle(), &value, &index));
			return index;
		}

		void Insert(NInt index, const NLFeaturePoint & value)
		{
			NCheck(NLAttributesInsertFeaturePoint(this->GetOwnerHandle(), index, &value));
		}

		void RemoveAt(NInt index)
		{
			NCheck(NLAttributesRemoveFeaturePointAt(this->GetOwnerHandle(), index));
		}

		void Clear()
		{
			NCheck(NLAttributesClearFeaturePoints(this->GetOwnerHandle()));
		}
	};

private:
	static HNLAttributes Create()
	{
		HNLAttributes handle;
		NCheck(NLAttributesCreate(&handle));
		return handle;
	}

public:
	NLAttributes()
		: NBiometricAttributes(Create(), true)
	{
		Reset();
	}

	NFace GetOwner() const;

	::Neurotec::Geometry::NRect GetBoundingRect() const
	{
		::Neurotec::Geometry::NRect value;
		NCheck(NLAttributesGetBoundingRect(GetHandle(), &value));
		return value;
	}

	void SetBoundingRect(const ::Neurotec::Geometry::NRect & value)
	{
		NCheck(NLAttributesSetBoundingRect(GetHandle(), &value));
	}

	NFloat GetYaw() const
	{
		NFloat value;
		NCheck(NLAttributesGetYaw(GetHandle(), &value));
		return value;
	}

	void SetYaw(NFloat value)
	{
		NCheck(NLAttributesSetYaw(GetHandle(), value));
	}

	NFloat GetPitch() const
	{
		NFloat value;
		NCheck(NLAttributesGetPitch(GetHandle(), &value));
		return value;
	}

	void SetPitch(NFloat value)
	{
		NCheck(NLAttributesSetPitch(GetHandle(), value));
	}

	NFloat GetRoll() const
	{
		NFloat value;
		NCheck(NLAttributesGetRoll(GetHandle(), &value));
		return value;
	}

	void SetRoll(NFloat value)
	{
		NCheck(NLAttributesSetRoll(GetHandle(), value));
	}

	NLExpression GetExpression() const
	{
		NLExpression value;
		NCheck(NLAttributesGetExpression(GetHandle(), &value));
		return value;
	}

	void SetExpression(NLExpression value)
	{
		NCheck(NLAttributesSetExpression(GetHandle(), value));
	}

	NLProperties GetProperties() const
	{
		NLProperties value;
		NCheck(NLAttributesGetProperties(GetHandle(), &value));
		return value;
	}

	void SetProperties(NLProperties value)
	{
		NCheck(NLAttributesSetProperties(GetHandle(), value));
	}

	NByte GetSharpness() const
	{
		NByte value;
		NCheck(NLAttributesGetSharpness(GetHandle(), &value));
		return value;
	}

	void SetSharpness(NByte value)
	{
		NCheck(NLAttributesSetSharpness(GetHandle(), value));
	}

	NByte GetBackgroundUniformity() const
	{
		NByte value;
		NCheck(NLAttributesGetBackgroundUniformity(GetHandle(), &value));
		return value;
	}

	void SetBackgroundUniformity(NByte value)
	{
		NCheck(NLAttributesSetBackgroundUniformity(GetHandle(), value));
	}

	NByte GetGrayscaleDensity() const
	{
		NByte value;
		NCheck(NLAttributesGetGrayscaleDensity(GetHandle(), &value));
		return value;
	}

	void SetGrayscaleDensity(NByte value)
	{
		NCheck(NLAttributesSetGrayscaleDensity(GetHandle(), value));
	}

	NLFeaturePoint GetRightEyeCenter() const
	{
		NLFeaturePoint value;
		NCheck(NLAttributesGetRightEyeCenter(GetHandle(), &value));
		return value;
	}

	void SetRightEyeCenter(const NLFeaturePoint & value)
	{
		NCheck(NLAttributesSetRightEyeCenter(GetHandle(), &value));
	}

	NLFeaturePoint GetLeftEyeCenter() const
	{
		NLFeaturePoint value;
		NCheck(NLAttributesGetLeftEyeCenter(GetHandle(), &value));
		return value;
	}

	void SetLeftEyeCenter(const NLFeaturePoint & value)
	{
		NCheck(NLAttributesSetLeftEyeCenter(GetHandle(), &value));
	}

	NLFeaturePoint GetNoseTip() const
	{
		NLFeaturePoint value;
		NCheck(NLAttributesGetNoseTip(GetHandle(), &value));
		return value;
	}

	void SetNoseTip(const NLFeaturePoint & value)
	{
		NCheck(NLAttributesSetNoseTip(GetHandle(), &value));
	}

	NLFeaturePoint GetMouthCenter() const
	{
		NLFeaturePoint value;
		NCheck(NLAttributesGetMouthCenter(GetHandle(), &value));
		return value;
	}

	void SetMouthCenter(const NLFeaturePoint & value)
	{
		NCheck(NLAttributesSetMouthCenter(GetHandle(), &value));
	}

	NGender GetGender() const
	{
		NGender value;
		NCheck(NLAttributesGetGender(GetHandle(), &value));
		return value;
	}

	void SetGender(NGender value)
	{
		NCheck(NLAttributesSetGender(GetHandle(), value));
	}

	NByte GetGenderConfidence() const
	{
		NByte value;
		NCheck(NLAttributesGetGenderConfidence(GetHandle(), &value));
		return value;
	}

	void SetGenderConfidence(NByte value)
	{
		NCheck(NLAttributesSetGenderConfidence(GetHandle(), value));
	}

	NByte GetExpressionConfidence() const
	{
		NByte value;
		NCheck(NLAttributesGetExpressionConfidence(GetHandle(), &value));
		return value;
	}

	void SetExpressionConfidence(NByte value)
	{
		NCheck(NLAttributesSetExpressionConfidence(GetHandle(), value));
	}

	NByte GetGlassesConfidence() const
	{
		NByte value;
		NCheck(NLAttributesGetGlassesConfidence(GetHandle(), &value));
		return value;
	}

	void SetGlassesConfidence(NByte value)
	{
		NCheck(NLAttributesSetGlassesConfidence(GetHandle(), value));
	}

	NByte GetDarkGlassesConfidence() const
	{
		NByte value;
		NCheck(NLAttributesGetDarkGlassesConfidence(GetHandle(), &value));
		return value;
	}

	void SetDarkGlassesConfidence(NByte value)
	{
		NCheck(NLAttributesSetDarkGlassesConfidence(GetHandle(), value));
	}

	NByte GetBlinkConfidence() const
	{
		NByte value;
		NCheck(NLAttributesGetBlinkConfidence(GetHandle(), &value));
		return value;
	}

	void SetBlinkConfidence(NByte value)
	{
		NCheck(NLAttributesSetBlinkConfidence(GetHandle(), value));
	}

	NByte GetMouthOpenConfidence() const
	{
		NByte value;
		NCheck(NLAttributesGetMouthOpenConfidence(GetHandle(), &value));
		return value;
	}

	void SetMouthOpenConfidence(NByte value)
	{
		NCheck(NLAttributesSetMouthOpenConfidence(GetHandle(), value));
	}

	NByte GetEmotionNeutralConfidence() const
	{
		NByte value;
		NCheck(NLAttributesGetEmotionNeutralConfidence(GetHandle(), &value));
		return value;
	}

	void SetEmotionNeutralConfidence(NByte value)
	{
		NCheck(NLAttributesSetEmotionNeutralConfidence(GetHandle(), value));
	}

	NByte GetEmotionAngerConfidence() const
	{
		NByte value;
		NCheck(NLAttributesGetEmotionAngerConfidence(GetHandle(), &value));
		return value;
	}

	void SetEmotionAngerConfidence(NByte value)
	{
		NCheck(NLAttributesSetEmotionAngerConfidence(GetHandle(), value));
	}

	NByte GetEmotionDisgustConfidence() const
	{
		NByte value;
		NCheck(NLAttributesGetEmotionDisgustConfidence(GetHandle(), &value));
		return value;
	}

	void SetEmotionDisgustConfidence(NByte value)
	{
		NCheck(NLAttributesSetEmotionDisgustConfidence(GetHandle(), value));
	}

	NByte GetEmotionFearConfidence() const
	{
		NByte value;
		NCheck(NLAttributesGetEmotionFearConfidence(GetHandle(), &value));
		return value;
	}

	void SetEmotionFearConfidence(NByte value)
	{
		NCheck(NLAttributesSetEmotionFearConfidence(GetHandle(), value));
	}

	NByte GetEmotionHappinessConfidence() const
	{
		NByte value;
		NCheck(NLAttributesGetEmotionHappinessConfidence(GetHandle(), &value));
		return value;
	}

	void SetEmotionHappinessConfidence(NByte value)
	{
		NCheck(NLAttributesSetEmotionHappinessConfidence(GetHandle(), value));
	}

	NByte GetEmotionSadnessConfidence() const
	{
		NByte value;
		NCheck(NLAttributesGetEmotionSadnessConfidence(GetHandle(), &value));
		return value;
	}

	void SetEmotionSadnessConfidence(NByte value)
	{
		NCheck(NLAttributesSetEmotionSadnessConfidence(GetHandle(), value));
	}

	NByte GetEmotionSurpriseConfidence() const
	{
		NByte value;
		NCheck(NLAttributesGetEmotionSurpriseConfidence(GetHandle(), &value));
		return value;
	}

	void SetEmotionSurpriseConfidence(NByte value)
	{
		NCheck(NLAttributesSetEmotionSurpriseConfidence(GetHandle(), value));
	}

	NByte GetAge() const
	{
		NByte value;
		NCheck(NLAttributesGetAge(GetHandle(), &value));
		return value;
	}

	void SetAge(NByte value)
	{
		NCheck(NLAttributesSetAge(GetHandle(), value));
	}

	NInt GetBaseFrameIndex() const
	{
		NInt value;
		NCheck(NLAttributesGetBaseFrameIndex(GetHandle(), &value));
		return value;
	}

	void SetBaseFrameIndex(NInt value)
	{
		NCheck(NLAttributesSetBaseFrameIndex(GetHandle(), value));
	}

	::Neurotec::Images::NImage GetThumbnail() const
	{
		return GetObject<HandleType, ::Neurotec::Images::NImage>(NLAttributesGetThumbnail, true);
	}

	void SetThumbnail(const ::Neurotec::Images::NImage & value)
	{
		SetObject(NLAttributesSetThumbnail, value);
	}

	NLTemplate GetTemplate() const
	{
		return GetObject<HandleType, NLTemplate>(NLAttributesGetTemplate, true);
	}

	void SetTemplate(const NLTemplate & value)
	{
		NCheck(NLAttributesSetTemplate(GetHandle(), value.GetHandle()));
	}

	FeaturePointCollection GetFeaturePoints()
	{
		return FeaturePointCollection(*this);
	}

	const FeaturePointCollection GetFeaturePoints() const
	{
		return FeaturePointCollection(*this);
	}

	NLivenessAction GetLivenessAction() const
	{
		NLivenessAction value;
		NCheck(NLAttributesGetLivenessAction(GetHandle(), &value));
		return value;
	}

	NByte GetLivenessScore() const
	{
		NByte value;
		NCheck(NLAttributesGetLivenessScore(GetHandle(), &value));
		return value;
	}

	NFloat GetLivenessTargetYaw() const
	{
		NFloat value;
		NCheck(NLAttributesGetLivenessTargetYaw(GetHandle(), &value));
		return value;
	}

};

}}

#include <Biometrics/NFace.hpp>

namespace Neurotec { namespace Biometrics
{

inline NFace NLAttributes::GetOwner() const
{
	return NObject::GetOwner<NFace>();
}

}}

#endif // !NL_ATTRIBUTES_HPP_INCLUDED
