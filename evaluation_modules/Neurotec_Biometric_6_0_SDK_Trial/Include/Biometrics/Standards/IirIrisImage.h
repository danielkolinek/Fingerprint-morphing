#ifndef IIR_IRIS_IMAGE_H_INCLUDED
#define IIR_IRIS_IMAGE_H_INCLUDED

#include <Core/NDateTime.h>
#include <Images/NImage.h>
#include <Biometrics/Standards/BdifTypes.h>

#ifdef N_CPP
extern "C"
{
#endif

typedef enum IirImageFormat_
{
	iirifMonoRaw = 2,
	iirifRgbRaw = 4,
	iirifMonoJpeg = 6,
	iirifRgbJpeg = 8,
	iirifMonoJpegLS = 10,
	iirifRgbJpegLS = 12,
	iirifMonoJpeg2000 = 14,
	iirifRgbJpeg2000 = 16,
	iirifMonoPng = 18
} IirImageFormat;

N_DECLARE_TYPE(IirImageFormat)

N_DECLARE_OBJECT_TYPE(IirIrisImage, NObject)

#ifdef N_CPP
}
#endif

#include <Biometrics/Standards/IIRecord.h>

#ifdef N_CPP
extern "C"
{
#endif

#define IIRII_MAX_QUALITY_BLOCK_COUNT 255
#define IIRII_COORDINATE_UNDEFINED 0
#define IIRII_CAPTURE_DEVICE_VENDOR_UNDEFINED 0
#define IIRII_CAPTURE_DEVICE_TYPE_UNDEFINED 0
#define IIRII_RANGE_UNASSIGNED 0
#define IIRII_RANGE_FAILED 1
#define IIRII_RANGE_OVERFLOW 0xFFFE

typedef enum IirCaptureDeviceTechnology_
{
	iircdtUndefined = 0,
	iircdtCmosCcd = 1
} IirCaptureDeviceTechnology;

N_DECLARE_TYPE(IirCaptureDeviceTechnology)

typedef enum IirImageKind_
{
	iirikUncropped = 1,
	iirikVga = 2,
	iirikCropped = 3,
	iirikCroppedAndMasked = 7
} IirImageKind;

N_DECLARE_TYPE(IirImageKind)

typedef enum IirPreviousCompression_
{
	iirpcUndefined = 0,
	iirpcLosslessOrNone = 1,
	iirpcLossy = 2
} IirPreviousCompression;

N_DECLARE_TYPE(IirPreviousCompression)

NResult N_API IirIrisImageSetImage(HIirIrisImage hIrisImage, NUInt flags, HNImage hImage);
NResult N_API IirIrisImageToNImage(HIirIrisImage hIrisImage, NUInt flags, HNImage * phImage);
NResult N_API IirIrisImageCreateEx(BdifStandard standard, NVersion_ version, HIirIrisImage * phIrisImage);
NResult N_API IirIrisImageGetStandard(HIirIrisImage hIrisImage, BdifStandard * pValue);
NResult N_API IirIrisImageGetVersion(HIirIrisImage hIrisImage, NVersion_ * pValue);
NResult N_API IirIrisImageGetCaptureDateAndTimeEx(HIirIrisImage hIrisImage, struct BdifCaptureDateTime_ * pValue);
NResult N_API IirIrisImageSetCaptureDateAndTimeEx(HIirIrisImage hIrisImage, struct BdifCaptureDateTime_ value);
NResult N_API IirIrisImageGetCaptureDeviceTechnology(HIirIrisImage hIrisImage, IirCaptureDeviceTechnology * pValue);
NResult N_API IirIrisImageSetCaptureDeviceTechnology(HIirIrisImage hIrisImage, IirCaptureDeviceTechnology value);
NResult N_API IirIrisImageGetCaptureDeviceVendorId(HIirIrisImage hIrisImage, NUShort * pValue);
NResult N_API IirIrisImageSetCaptureDeviceVendorId(HIirIrisImage hIrisImage, NUShort value);
NResult N_API IirIrisImageGetCaptureDeviceTypeId(HIirIrisImage hIrisImage, NUShort * pValue);
NResult N_API IirIrisImageSetCaptureDeviceTypeId(HIirIrisImage hIrisImage, NUShort value);
NResult N_API IirIrisImageGetPosition(HIirIrisImage hIrisImage, BdifEyePosition * pValue);
NResult N_API IirIrisImageSetPosition(HIirIrisImage hIrisImage, BdifEyePosition value);
NResult N_API IirIrisImageGetImageNumber(HIirIrisImage hIrisImage, NInt * pValue);
NResult N_API IirIrisImageGetQuality(HIirIrisImage hIrisImage, NByte * pValue);
NResult N_API IirIrisImageSetQuality(HIirIrisImage hIrisImage, NByte value);
NResult N_API IirIrisImageGetImageType(HIirIrisImage hIrisImage, IirImageKind * pValue);
NResult N_API IirIrisImageSetImageType(HIirIrisImage hIrisImage, IirImageKind value);
NResult N_API IirIrisImageGetImageFormat(HIirIrisImage hIrisImage, IirImageFormat * pValue);
NResult N_API IirIrisImageSetImageFormat(HIirIrisImage hIrisImage, IirImageFormat value);
NResult N_API IirIrisImageGetIrisHorzOrientation(HIirIrisImage hIrisImage, BdifIrisOrientation * pValue);
NResult N_API IirIrisImageSetIrisHorzOrientation(HIirIrisImage hIrisImage, BdifIrisOrientation value);
NResult N_API IirIrisImageGetIrisVertOrientation(HIirIrisImage hIrisImage, BdifIrisOrientation * pValue);
NResult N_API IirIrisImageSetIrisVertOrientation(HIirIrisImage hIrisImage, BdifIrisOrientation value);
NResult N_API IirIrisImageGetPreviousCompression(HIirIrisImage hIrisImage, IirPreviousCompression * pValue);
NResult N_API IirIrisImageSetPreviousCompression(HIirIrisImage hIrisImage, IirPreviousCompression value);
NResult N_API IirIrisImageGetImageWidth(HIirIrisImage hIrisImage, NUShort * pValue);
NResult N_API IirIrisImageSetImageWidth(HIirIrisImage hIrisImage, NUShort value);
NResult N_API IirIrisImageGetImageHeight(HIirIrisImage hIrisImage, NUShort * pValue);
NResult N_API IirIrisImageSetImageHeight(HIirIrisImage hIrisImage, NUShort value);
NResult N_API IirIrisImageGetIntensityDepth(HIirIrisImage hIrisImage, NByte * pValue);
NResult N_API IirIrisImageSetIntensityDepth(HIirIrisImage hIrisImage, NByte value);
NResult N_API IirIrisImageGetRange(HIirIrisImage hIrisImage, NUShort * pValue);
NResult N_API IirIrisImageSetRange(HIirIrisImage hIrisImage, NUShort value);
NResult N_API IirIrisImageGetRotationAngleEx(HIirIrisImage hIrisImage, NUShort * pValue);
NResult N_API IirIrisImageSetRotationAngleEx(HIirIrisImage hIrisImage, NUShort value);
NResult N_API IirIrisImageGetRotationAngleUncertainty(HIirIrisImage hIrisImage, NUShort * pValue);
NResult N_API IirIrisImageSetRotationAngleUncertainty(HIirIrisImage hIrisImage, NUShort value);
NResult N_API IirIrisImageGetIrisCenterSmallestX(HIirIrisImage hIrisImage, NUShort * pValue);
NResult N_API IirIrisImageSetIrisCenterSmallestX(HIirIrisImage hIrisImage, NUShort value);
NResult N_API IirIrisImageGetIrisCenterLargestX(HIirIrisImage hIrisImage, NUShort * pValue);
NResult N_API IirIrisImageSetIrisCenterLargestX(HIirIrisImage hIrisImage, NUShort value);
NResult N_API IirIrisImageGetIrisCenterSmallestY(HIirIrisImage hIrisImage, NUShort * pValue);
NResult N_API IirIrisImageSetIrisCenterSmallestY(HIirIrisImage hIrisImage, NUShort value);
NResult N_API IirIrisImageGetIrisCenterLargestY(HIirIrisImage hIrisImage, NUShort * pValue);
NResult N_API IirIrisImageSetIrisCenterLargestY(HIirIrisImage hIrisImage, NUShort value);
NResult N_API IirIrisImageGetIrisDiameterSmallest(HIirIrisImage hIrisImage, NUShort * pValue);
NResult N_API IirIrisImageSetIrisDiameterSmallest(HIirIrisImage hIrisImage, NUShort value);
NResult N_API IirIrisImageGetIrisDiameterLargest(HIirIrisImage hIrisImage, NUShort * pValue);
NResult N_API IirIrisImageSetIrisDiameterLargest(HIirIrisImage hIrisImage, NUShort value);
NResult N_API IirIrisImageGetImageDataN(HIirIrisImage hIrisImage, HNBuffer * phValue);
NResult N_API IirIrisImageSetImageDataN(HIirIrisImage hIrisImage, HNBuffer hValue);

NResult N_API IirIrisImageGetQualityBlockCount(HIirIrisImage hIrisImage, NInt * pValue);
NResult N_API IirIrisImageGetQualityBlock(HIirIrisImage hIrisImage, NInt index, struct BdifQualityBlock_ * pValue);
NResult N_API IirIrisImageSetQualityBlock(HIirIrisImage hIrisImage, NInt index, const struct BdifQualityBlock_ * pValue);
NResult N_API IirIrisImageGetQualityBlocks(HIirIrisImage hIrisImage, struct BdifQualityBlock_ * * parValues, NInt * pValueCount);
NResult N_API IirIrisImageGetQualityBlockCapacity(HIirIrisImage hIrisImage, NInt * pValue);
NResult N_API IirIrisImageSetQualityBlockCapacity(HIirIrisImage hIrisImage, NInt value);
NResult N_API IirIrisImageAddQualityBlock(HIirIrisImage hIrisImage, const struct BdifQualityBlock_ * pValue, NInt * pIndex);
NResult N_API IirIrisImageInsertQualityBlock(HIirIrisImage hIrisImage, NInt index, const struct BdifQualityBlock_ * pValue);
NResult N_API IirIrisImageRemoveQualityBlockAt(HIirIrisImage hIrisImage, NInt index);
NResult N_API IirIrisImageClearQualityBlocks(HIirIrisImage hIrisImage);

#ifdef N_MSVC
	#pragma deprecated("IIRII_MAX_QUALITY_BLOCK_COUNT")
#endif

#ifdef N_CPP
}
#endif

#endif // !IIR_IRIS_IMAGE_H_INCLUDED
