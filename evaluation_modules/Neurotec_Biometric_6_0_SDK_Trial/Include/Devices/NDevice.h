#ifndef N_DEVICE_H_INCLUDED
#define N_DEVICE_H_INCLUDED

#include <Core/NObject.h>
#include <Plugins/NPlugin.h>

#ifdef N_CPP
extern "C"
{
#endif

typedef enum NDeviceType_
{
	ndtNone = 0,
	ndtCamera = 0x01,
	ndtBiometricDevice = 0x02,
	ndtFScanner = 0x04,
	ndtFingerScanner = 0x08,
	ndtPalmScanner = 0x10,
	ndtIrisScanner = 0x20,
	ndtCaptureDevice = 0x40,
	ndtMicrophone = 0x80,
	ndtAny = 0x80000000
} NDeviceType;

N_DECLARE_TYPE(NDeviceType)

N_DECLARE_OBJECT_TYPE(NDevice, NObject)

NResult N_API NDeviceGetChildCount(HNDevice hDevice, NInt * pValue);
NResult N_API NDeviceGetChild(HNDevice hDevice, NInt index, HNDevice * phValue);
NResult N_API NDeviceGetChildren(HNDevice hDevice, HNDevice * * parhValues, NInt * pValueCount);

NResult N_API NDeviceGetPlugin(HNDevice hDevice, HNPlugin * phValue);
NResult N_API NDeviceGetDeviceType(HNDevice hDevice, NDeviceType * pValue);
NResult N_API NDeviceIsAvailable(HNDevice hDevice, NBool * pValue);
NResult N_API NDeviceIsPrivate(HNDevice hDevice, NBool * pValue);
NResult N_API NDeviceIsDisconnectable(HNDevice hDevice, NBool * pValue);
NResult N_API NDeviceGetParent(HNDevice hDevice, HNDevice * phValue);

NResult N_API NDeviceGetIdN(HNDevice hDevice, HNString * phValue);
NResult N_API NDeviceGetDisplayNameN(HNDevice hDevice, HNString * phValue);
NResult N_API NDeviceGetMakeN(HNDevice hDevice, HNString * phValue);
NResult N_API NDeviceGetModelN(HNDevice hDevice, HNString * phValue);
NResult N_API NDeviceGetSerialNumberN(HNDevice hDevice, HNString * phValue);

#ifdef N_CPP
}
#endif

#endif // !N_DEVICE_H_INCLUDED
