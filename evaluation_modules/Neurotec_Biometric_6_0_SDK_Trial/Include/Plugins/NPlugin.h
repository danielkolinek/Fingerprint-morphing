#ifndef N_PLUGIN_H_INCLUDED
#define N_PLUGIN_H_INCLUDED

#include <Core/NObject.h>
#include <Core/NTimeSpan.h>
#include <Plugins/NPluginModule.h>

#ifdef N_CPP
extern "C"
{
#endif

typedef enum NPluginState_
{
	npsNone = 0,
	npsLoadError = 1,
	npsNotRecognized = 2,
	npsInvalidModule = 3,
	npsInterfaceTypeMismatch = 4,
	npsInterfaceVersionMismatch = 5,
	npsInvalidInterface = 6,
	npsUnplugged = 64,
	npsUnused = 65,
	npsDisabled = 66,
	npsDuplicate = 67,
	npsIncompatibleWithOtherPlugins = 68,
	npsPluggingError = 69,
	npsPlugged = 128
} NPluginState;

N_DECLARE_TYPE(NPluginState)

N_DECLARE_OBJECT_TYPE(NPlugin, NObject)

NResult N_API NPluginPlug(HNPlugin hPlugin);
NResult N_API NPluginUnplug(HNPlugin hPlugin);
NResult N_API NPluginEnable(HNPlugin hPlugin);
NResult N_API NPluginDisable(HNPlugin hPlugin);

NResult N_API NPluginGetFileNameN(HNPlugin hPlugin, HNString * phValue);

NResult N_API NPluginGetState(HNPlugin hPlugin, NPluginState * pValue);
NResult N_API NPluginGetError(HNPlugin hPlugin, HNError * phValue);
NResult N_API NPluginGetLoadTime(HNPlugin hPlugin, NTimeSpan_ * pValue);
NResult N_API NPluginGetModule(HNPlugin hPlugin, HNPluginModule * phValue);
NResult N_API NPluginGetSelectedInterfaceVersion(HNPlugin hPlugin, NVersion_ * pValue);
NResult N_API NPluginGetPlugTime(HNPlugin hPlugin, NTimeSpan_ * pValue);

#ifdef N_CPP
}
#endif

#endif // !N_PLUGIN_H_INCLUDED
