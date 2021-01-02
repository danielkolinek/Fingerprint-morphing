#ifndef N_VIRTUAL_CAMERA_SOURCE_HPP_INCLUDED
#define N_VIRTUAL_CAMERA_SOURCE_HPP_INCLUDED

#include <Core/NTimeSpan.hpp>
#include <Images/NImage.hpp>
#include <Devices/NDeviceManager.hpp>
#include <Devices/NCamera.hpp>
namespace Neurotec { namespace Devices { namespace Virtual {
using Neurotec::Devices::HNDeviceManager;
using Neurotec::Devices::HNCamera;
#include <Devices/Virtual/NVirtualCameraSource.h>
}}}

namespace Neurotec { namespace Devices { namespace Virtual {
class NVirtualCameraSource : public NObject
{
	N_DECLARE_OBJECT_CLASS(NVirtualCameraSource, NObject)
private:
	static HNVirtualCameraSource Create(::Neurotec::Devices::HNDeviceManager hDeviceManager)
	{
		HNVirtualCameraSource handle;
		NCheck(NVirtualCameraSourceConnect(hDeviceManager, &handle));
		return handle;
	}
public:
	static NVirtualCameraSource Connect(const Neurotec::Devices::NDeviceManager & deviceManager)
	{
		return NVirtualCameraSource(Create(deviceManager.GetHandle()), true);
	}

	::Neurotec::Devices::NCamera GetCamera() const
	{
		return GetObject<HandleType, ::Neurotec::Devices::NCamera>(NVirtualCameraSourceGetCamera);
	}

	NInt PushSample(const ::Neurotec::Images::NImage & image, const NTimeSpan & start, const NTimeSpan & duration)
	{
		NInt index;
		NCheck(NVirtualCameraSourcePushSample(GetHandle(), image.GetHandle(), start.GetTicks(), duration.GetTicks(), &index));
		return index;
	}

	NInt PushSample(const ::Neurotec::NStringWrapper & fileName, const NTimeSpan & start, const NTimeSpan & duration)
	{
		NInt index;
		NCheck(NVirtualCameraSourcePushFileSample(GetHandle(), fileName.GetHandle(), start.GetTicks(), duration.GetTicks(), &index));
		return index;
	}
};

}}}

#endif
