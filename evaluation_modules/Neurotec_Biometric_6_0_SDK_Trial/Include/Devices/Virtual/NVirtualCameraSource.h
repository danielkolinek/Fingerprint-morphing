#ifndef N_VIRTUAL_CAMERA_SOURCE_H_INCLUDED
#define N_VIRTUAL_CAMERA_SOURCE_H_INCLUDED

#include <Core/NTimeSpan.h>
#include <Images/NImage.h>
#include <Devices/NDeviceManager.h>
#include <Devices/NCamera.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(NVirtualCameraSource, NObject)

NResult N_API NVirtualCameraSourceConnect(HNDeviceManager hDeviceManager, HNVirtualCameraSource * phSource);
NResult N_API NVirtualCameraSourceGetCamera(HNVirtualCameraSource hSource, HNCamera * phValue);
NResult N_API NVirtualCameraSourcePushSample(HNVirtualCameraSource hSource, HNImage hImage, NTimeSpan_ start, NTimeSpan_ duration, NInt * pIndex);
NResult N_API NVirtualCameraSourcePushFileSample(HNVirtualCameraSource hSource, HNString hFileName, NTimeSpan_ start, NTimeSpan_ duration, NInt * pIndex);

#ifdef N_CPP
}
#endif

#endif
