#include <Biometrics/NFrictionRidge.hpp>

#ifndef N_FINGER_HPP_INCLUDED
#define N_FINGER_HPP_INCLUDED

namespace Neurotec { namespace Biometrics
{
#include <Biometrics/NFinger.h>
}}

namespace Neurotec { namespace Biometrics
{

class NFinger : public NFrictionRidge
{
	N_DECLARE_OBJECT_CLASS(NFinger, NFrictionRidge)

private:
	static HNFinger Create()
	{
		HNFinger handle;
		NCheck(NFingerCreate(&handle));
		return handle;
	}

public:
	NFinger()
		: NFrictionRidge(Create(), true)
	{
	}

	bool GetWrongHandWarning() const
	{
		NBool value;
		NCheck(NFingerGetWrongHandWarning(GetHandle(), &value));
		return value != NFalse;
	}

	void SetWrongHandWarning(bool value)
	{
		NCheck(NFingerSetWrongHandWarning(GetHandle(), value ? NTrue : NFalse));
	}
};

}}

#endif // !N_FINGER_HPP_INCLUDED
