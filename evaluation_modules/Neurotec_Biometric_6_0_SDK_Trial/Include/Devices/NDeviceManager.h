#ifndef N_DEVICE_MANAGER_H_INCLUDED
#define N_DEVICE_MANAGER_H_INCLUDED

#include <Devices/NDevice.h>
#include <Collections/NCollection.h>
#include <Plugins/NPluginManager.h>
#include <ComponentModel/NParameterDescriptor.h>
#include <Core/NPropertyBag.h>
#include <Biometrics/NBiometricEngine.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(NDeviceManager, NObject)

NResult N_API NDeviceManagerGetPluginManager(HNPluginManager * phValue);

NResult N_API NDeviceManagerIsConnectToDeviceSupported(HNPlugin hPlugin, NBool * pValue);
NResult N_API NDeviceManagerGetConnectToDeviceParameters(HNPlugin hPlugin, HNParameterDescriptor * * parhParameters, NInt * pParameterCount);

NResult N_API NDeviceManagerCreateEx(HNDeviceManager * phDeviceManager);

NResult N_API NDeviceManagerGetDeviceCount(HNDeviceManager hDeviceManager, NInt * pValue);
NResult N_API NDeviceManagerGetDevice(HNDeviceManager hDeviceManager, NInt index, HNDevice * phValue);
NResult N_API NDeviceManagerGetDevices(HNDeviceManager hDeviceManager, HNDevice * * parhValues, NInt * pValueCount);

NResult N_API NDeviceManagerGetDeviceByIdN(HNDeviceManager hDeviceManager, HNString hId, HNDevice * phValue);
#ifndef N_NO_ANSI_FUNC
NResult N_API NDeviceManagerGetDeviceByIdA(HNDeviceManager hDeviceManager, const NAChar * szId, HNDevice * phValue);
#endif
#ifndef N_NO_UNICODE
NResult N_API NDeviceManagerGetDeviceByIdW(HNDeviceManager hDeviceManager, const NWChar * szId, HNDevice * phValue);
#endif
#ifdef N_DOCUMENTATION
NResult N_API NDeviceManagerGetDeviceById(HNDeviceManager hDeviceManager, const NChar * szId, HNDevice * phValue);
#endif
#define NDeviceManagerGetDeviceById N_FUNC_AW(NDeviceManagerGetDeviceById)

NResult N_API NDeviceManagerInitialize(HNDeviceManager hDeviceManager);
NResult N_API NDeviceManagerConnectToDevice(HNDeviceManager hDeviceManager, HNPlugin hPlugin, HNPropertyBag hParameters, HNDevice * phDevice);

NResult N_API NDeviceManagerConnectToDeviceWithStringN(HNDeviceManager hDeviceManager, HNString hPlugin, HNString hParameters, HNDevice * phDevice);
#ifndef N_NO_ANSI_FUNC
NResult N_API NDeviceManagerConnectToDeviceWithStringA(HNDeviceManager hDeviceManager, const NAChar * szPlugin, const NAChar * szParameters, HNDevice * phDevice);
#endif
#ifndef N_NO_UNICODE
NResult N_API NDeviceManagerConnectToDeviceWithStringW(HNDeviceManager hDeviceManager, const NWChar * szPlugin, const NWChar * szParameters, HNDevice * phDevice);
#endif
#ifdef N_DOCUMENTATION
NResult N_API NDeviceManagerConnectToDeviceWithString(HNDeviceManager hDeviceManager, const NChar * szPlugin, const NChar * szParameters, HNDevice * phDevice);
#endif
#define NDeviceManagerConnectToDeviceWithString N_FUNC_AW(NDeviceManagerConnectToDeviceWithString)

NResult N_API NDeviceManagerDisconnectFromDevice(HNDeviceManager hDeviceManager, HNDevice hDevice);

NResult N_API NDeviceManagerIsInitialized(HNDeviceManager hDeviceManager, NBool * pValue);
NResult N_API NDeviceManagerGetDeviceTypes(HNDeviceManager hDeviceManager, NDeviceType * pValue);
NResult N_API NDeviceManagerSetDeviceTypes(HNDeviceManager hDeviceManager, NDeviceType value);
NResult N_API NDeviceManagerGetAutoPlug(HNDeviceManager hDeviceManager, NBool * pValue);
NResult N_API NDeviceManagerSetAutoPlug(HNDeviceManager hDeviceManager, NBool value);
NResult N_API NDeviceManagerGetBiometricEngine(HNDeviceManager hDeviceManager, HNBiometricEngine * phValue);
NResult N_API NDeviceManagerSetBiometricEngine(HNDeviceManager hDeviceManager, HNBiometricEngine hValue);

NResult N_API NDeviceManagerAddDevicesCollectionChanged(HNDeviceManager hDeviceManager, HNCallback hCallback);
NResult N_API NDeviceManagerAddDevicesCollectionChangedCallback(HNDeviceManager hDeviceManager, N_COLLECTION_CHANGED_CALLBACK_ARG(HNDevice, pCallback), void * pParam);
NResult N_API NDeviceManagerRemoveDevicesCollectionChanged(HNDeviceManager hDeviceManager, HNCallback hCallback);
NResult N_API NDeviceManagerRemoveDevicesCollectionChangedCallback(HNDeviceManager hDeviceManager, N_COLLECTION_CHANGED_CALLBACK_ARG(HNDevice, pCallback), void * pParam);

#ifdef N_CPP
}
#endif

#endif // !N_DEVICE_MANAGER_H_INCLUDED
