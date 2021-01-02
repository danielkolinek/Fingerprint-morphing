#include <Devices/NCaptureDevice.hpp>

#ifndef N_MICROPHONE_HPP_INCLUDED
#define N_MICROPHONE_HPP_INCLUDED

#include <Sound/NSoundBuffer.hpp>
namespace Neurotec { namespace Devices
{
using ::Neurotec::Sound::HNSoundBuffer;
#include <Devices/NMicrophone.h>
}}

namespace Neurotec { namespace Devices
{
class NMicrophone : public NCaptureDevice
{
	N_DECLARE_OBJECT_CLASS(NMicrophone, NCaptureDevice)

public:
	::Neurotec::Sound::NSoundBuffer GetSoundSample(NTimeSpan * pTimeStamp = NULL, NTimeSpan * pDuration = NULL)
	{
		HNSoundBuffer hSoundBuffer = NULL;
		NTimeSpan_ ts = 0, d = 0;
		NCheck(NMicrophoneGetSoundSampleEx(GetHandle(), pTimeStamp ? &ts : NULL, pDuration ? &d : NULL, &hSoundBuffer));
		if (pTimeStamp) *pTimeStamp = NTimeSpan(ts);
		if (pDuration) *pDuration = NTimeSpan(d);
		return FromHandle< ::Neurotec::Sound::NSoundBuffer>(hSoundBuffer);
	}
};

}}

#endif // !N_MICROPHONE_HPP_INCLUDED
