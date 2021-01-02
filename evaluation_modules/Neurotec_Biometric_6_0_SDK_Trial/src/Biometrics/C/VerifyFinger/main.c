#include <Utils.h>

#include <NCore.h>
#include <NBiometricClient.h>
#include <NBiometrics.h>
#include <NMedia.h>
#include <NLicensing.h>


NResult CreateSubject(HNSubject hSubject, const NChar * fileName)
{
	HNFinger hFinger = NULL;
	NResult result = N_OK;

	// create finger for the subject
	result = NFingerCreate(&hFinger);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NFingerCreate() failed (result = %d)!"), result);
		goto FINALLY;
	}

	// read and set the image for the finger
	result = NBiometricSetFileName(hFinger, fileName);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NBiometricSetFileNameN() failed (result = %d)!"), result);
		goto FINALLY;
	}

	// set the finger for the subject
	result = NSubjectAddFinger(hSubject, hFinger, NULL);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NSubjectAddFinger() failed (result = %d)!"), result);
		goto FINALLY;
	}
	result = N_OK;
FINALLY:
	{
		NResult result2 = NObjectSet(NULL, &hFinger);
		if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
	}

	return result;
}

void destroy_everything(HNSubject hProbeSubject, HNSubject hGallerySubject, HNBiometricClient hBiometricClient, HNMatchingResult hMatchingResults, HNString hBiometricStatus, NResult result, const NChar* components)
{
	NResult result2;

	result2 = NObjectSet(NULL, &hProbeSubject);
	if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
	result2 = NObjectSet(NULL, &hGallerySubject);
	if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
	result2 = NObjectSet(NULL, &hBiometricClient);
	if (NFailed(result2)) PrintErrorMsg(N_T("NObjectSet() failed (result = %d)!"), result2);
	result2 = NObjectSet(NULL, &hMatchingResults);
	if (NFailed(result2)) PrintErrorMsg(N_T("NObjectUnrefArray() failed (result = %d)!"), result2);
	result2 = NStringSet(NULL, &hBiometricStatus);
	if (NFailed(result2)) PrintErrorMsg(N_T("NStringSet() failed (result = %d)!"), result);
	result2 = NLicenseReleaseComponents(components);
	if (NFailed(result2)) PrintErrorMsg(N_T("NLicenseReleaseComponents() failed, result = %d\n"), result2);
}

//F:\DK\VUT\MIT\otisky\Fingerprint-morphing\src\scripts\res\101_1.tif F:\DK\VUT\MIT\otisky\Fingerprint-morphing\src\scripts\res\101_3.tif

void help() {
	PrintErrorMsg(N_T("./VerifyFinger path/to/folder sufix\n\n\
	path/to/folder	: path to folder with inputs to be tested (inputs of morphing not results!!)\n\
	sufix		: sufix of images in folder\n\n"), 1);
}

NInt detect(HNBiometricClient hBiometricClient, const NChar* components, const NChar* fingerprint1, const NChar* fingerprint2) {
	HNSubject hProbeSubject = NULL;
	HNSubject hGallerySubject = NULL;
	HNMatchingResult hMatchingResults = NULL;
	HNString hBiometricStatus = NULL;

	NResult result = N_OK;
	NBiometricStatus biometricStatus = nbsNone;
	NInt matchScore = 0;
	const NChar* szBiometricStatus = NULL;

	// create subject for probe image
	result = NSubjectCreate(&hProbeSubject);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NSubjectCreate() failed (result = %d)!"), result);
		destroy_everything(hProbeSubject, hGallerySubject, hBiometricClient, hMatchingResults, hBiometricStatus, result, components);
		exit(1);
	}

	result = CreateSubject(hProbeSubject,fingerprint1);
	if (NFailed(result))
	{
		PrintErrorMsg(N_T("CreateSubject() failed (result = %d)!"), result);
		destroy_everything(hProbeSubject, hGallerySubject, hBiometricClient, hMatchingResults, hBiometricStatus, result, components);
		exit(1);
	}

	// create subject for gallery image
	result = NSubjectCreate(&hGallerySubject);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NSubjectCreate() failed (result = %d)!"), result);
		destroy_everything(hProbeSubject, hGallerySubject, hBiometricClient, hMatchingResults, hBiometricStatus, result, components);
		exit(1);
	}

	result = CreateSubject(hGallerySubject, fingerprint2);
	if (NFailed(result))
	{
		PrintErrorMsg(N_T("CreateSubject() failed (result = %d)!"), result);
		destroy_everything(hProbeSubject, hGallerySubject, hBiometricClient, hMatchingResults, hBiometricStatus, result, components);
		exit(1);
	}

	{
		NInt matchingThreshold = 0;
		NMatchingSpeed matchingSpeed = nmsLow;

		// set matching threshold
		result = NObjectSetPropertyP(hBiometricClient, N_T("Matching.Threshold"), N_TYPE_OF(NInt32), naNone, &matchingThreshold, sizeof(matchingThreshold), 1, NTrue);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
			destroy_everything(hProbeSubject, hGallerySubject, hBiometricClient, hMatchingResults, hBiometricStatus, result, components);
			exit(1);
		}

		// set matching speed
		result = NObjectSetPropertyP(hBiometricClient, N_T("Fingers.MatchingSpeed"), N_TYPE_OF(NMatchingSpeed), naNone, &matchingSpeed, sizeof(matchingSpeed), 1, NTrue);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
			destroy_everything(hProbeSubject, hGallerySubject, hBiometricClient, hMatchingResults, hBiometricStatus, result, components);
			exit(1);
		}
	}

	// verify probe and gallery templates
	result = NBiometricEngineVerifyOffline(hBiometricClient, hProbeSubject, hGallerySubject, &biometricStatus);

	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NBiometricEngineVerifyOffline() failed (result = %d)!"), result);
		destroy_everything(hProbeSubject, hGallerySubject, hBiometricClient, hMatchingResults, hBiometricStatus, result, components);
		exit(1);
	}

	if (biometricStatus != nbsOk)
	{
		// retrieve biometric status
		result = NEnumToStringP(N_TYPE_OF(NBiometricStatus), biometricStatus, NULL, &hBiometricStatus);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NEnumToStringP() failed (result = %d)!"), result);
			destroy_everything(hProbeSubject, hGallerySubject, hBiometricClient, hMatchingResults, hBiometricStatus, result, components);
			exit(1);
		}

		result = NStringGetBuffer(hBiometricStatus, NULL, &szBiometricStatus);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NStringGetBuffer() failed (result = %d)!"), result);
			destroy_everything(hProbeSubject, hGallerySubject, hBiometricClient, hMatchingResults, hBiometricStatus, result, components);
			exit(1);
		}
		/*
		printf(N_T("verification failed!\n"));
		printf(N_T("biometric status: %s\n"), szBiometricStatus);
		*/

		result = N_E_FAILED;
		destroy_everything(hProbeSubject, hGallerySubject, hBiometricClient, hMatchingResults, hBiometricStatus, result, components);
	}
	else
	{
		// retrieve matching results from hProbeSubject
		result = NSubjectGetMatchingResult(hProbeSubject, 0, &hMatchingResults);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NStringGetBuffer() failed (result = %d)!"), result);
			destroy_everything(hProbeSubject, hGallerySubject, hBiometricClient, hMatchingResults, hBiometricStatus, result, components);
			exit(1);
		}

		// retrieve matching score from matching results
		result = NMatchingResultGetScore(hMatchingResults, &matchScore);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NStringGetBuffer() failed (result = %d)!"), result);
			destroy_everything(hProbeSubject, hGallerySubject, hBiometricClient, hMatchingResults, hBiometricStatus, result, components);
			exit(1);
		}

		//printf(N_T("\nimage scored %d, verification.. "), matchScore);
		printf(N_T("%d"), matchScore);
		return matchScore;

		/*
		if (matchScore > 0)
			printf(N_T("succeeded\n"));
		else
			printf(N_T("failed\n"));
		*/
	}

}

int main(int argc, NChar **argv)
{

	if (argc != 3)
	{
		help();
		NCoreOnExitEx(NFalse);
		exit(1);

	}

	HNSubject hProbeSubject = NULL;
	HNSubject hGallerySubject = NULL;
	HNBiometricClient hBiometricClient = NULL;
	HNMatchingResult hMatchingResults = NULL;
	HNString hBiometricStatus = NULL;

	const NChar * components = N_T("Biometrics.FingerExtraction,Biometrics.FingerMatching");
	NBool available = NFalse;
	NResult result = N_OK;
	NBiometricStatus biometricStatus = nbsNone;
	NInt matchScore = 0;
	const NChar * szBiometricStatus = NULL;

	// check the license first
	result = NLicenseObtainComponents(N_T("/local"), N_T("5000"), components, &available);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicenseObtainComponents() failed (result = %d)!"), result);
		destroy_everything(hProbeSubject, hGallerySubject, hBiometricClient, hMatchingResults, hBiometricStatus, result, components);
		exit(1);
	}

	if (!available)
	{
		printf(N_T("Licenses for %s not available\n"), components);
		result = N_E_NOT_ACTIVATED;
		destroy_everything(hProbeSubject, hGallerySubject, hBiometricClient, hMatchingResults, hBiometricStatus, result, components);
		exit(1);
	}

	// create biometric client
	result = NBiometricClientCreate(&hBiometricClient);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NBiometricClientCreate() failed (result = %d)!"), result);
		destroy_everything(hProbeSubject, hGallerySubject, hBiometricClient, hMatchingResults, hBiometricStatus, result, components);
		exit(1);
	}

	return detect(hBiometricClient, components, argv[1], argv[2]);
	

	//PrintErrorMsg(N_T("Result = %d\n"), result);
	//for (int c = 0; c < 10000000000000; c++);
	//return result;
	
}
