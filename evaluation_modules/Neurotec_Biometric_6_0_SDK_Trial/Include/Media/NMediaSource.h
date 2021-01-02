#ifndef N_MEDIA_SOURCE_H_INCLUDED
#define N_MEDIA_SOURCE_H_INCLUDED

#include <Media/NMediaFormat.h>

#ifdef N_CPP
extern "C"
{
#endif

N_DECLARE_OBJECT_TYPE(NMediaSource, NObject)

#define NMS_DO_NOT_USE_DIRECT_SHOW              0x00000001
#define NMS_DO_NOT_USE_WINDOWS_MEDIA_FOUNDATION 0x00000002
#define NMS_DO_NOT_USE_WINDOWS_MEDIA            0x00000004
#define NMS_PREFER_DIRECT_SHOW                  0x00000008
#define NMS_PREFER_WINDOWS_MEDIA_FOUNDATION     0x00000010
#define NMS_ALLOW_DUPLICATE_DEVICES             0x00000020

NResult N_API NMediaSourceEnumDevices(NMediaType mediaType, NUInt flags, HNMediaSource * * parhDevices, NInt * pDeviceCount);

NResult N_API NMediaSourceCreateFromFileN(HNString hFileName, NUInt flags, HNMediaSource * phSource);
#ifndef N_NO_ANSI_FUNC
NResult N_API NMediaSourceCreateFromFileA(const NAChar * szFileName, NUInt flags, HNMediaSource * phSource);
#endif
#ifndef N_NO_UNICODE
NResult N_API NMediaSourceCreateFromFileW(const NWChar * szFileName, NUInt flags, HNMediaSource * phSource);
#endif
#ifdef N_DOCUMENTATION
NResult N_API NMediaSourceCreateFromFile(const NChar * szFileName, NUInt flags, HNMediaSource * phSource);
#endif
#define NMediaSourceCreateFromFile N_FUNC_AW(NMediaSourceCreateFromFile)

NResult N_API NMediaSourceCreateFromUrlN(HNString hUrl, NUInt flags, HNMediaSource * phSource);
#ifndef N_NO_ANSI_FUNC
NResult N_API NMediaSourceCreateFromUrlA(const NAChar * szUrl, NUInt flags, HNMediaSource * phSource);
#endif
#ifndef N_NO_UNICODE
NResult N_API NMediaSourceCreateFromUrlW(const NWChar * szUrl, NUInt flags, HNMediaSource * phSource);
#endif
#ifdef N_DOCUMENTATION
NResult N_API NMediaSourceCreateFromUrl(const NChar * szUrl, NUInt flags, HNMediaSource * phSource);
#endif
#define NMediaSourceCreateFromUrl N_FUNC_AW(NMediaSourceCreateFromUrl)

NResult N_API NMediaSourceGetFormats(HNMediaSource hSource, NMediaType mediaType, HNMediaFormat * * parhFormats, NInt * pFormatCount);
NResult N_API NMediaSourceGetCurrentFormat(HNMediaSource hSource, NMediaType mediaType, HNMediaFormat * phFormat);
NResult N_API NMediaSourceSetCurrentFormat(HNMediaSource hSource, NMediaType mediaType, HNMediaFormat hFormat);

NResult N_API NMediaSourceGetIdN(HNMediaSource hSource, HNString * phValue);
NResult N_API NMediaSourceGetDisplayNameN(HNMediaSource hSource, HNString * phValue);

NResult N_API NMediaSourceGetMediaType(HNMediaSource hSource, NMediaType * pValue);

#ifdef N_CPP
}
#endif

#endif // !N_MEDIA_SOURCE_H_INCLUDED
