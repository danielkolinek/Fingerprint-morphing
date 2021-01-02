#include <TutorialUtils.h>

#include <NCore.h>
#include <NBiometricClient.h>
#include <NBiometrics.h>
#include <NMedia.h>
#include <NLicensing.h>

#define no_init_all deprecated

const NChar title[] = N_T("VerifyFinger");
const NChar description[] = N_T("Demonstrates fingerprint verification.");
const NChar version[] = N_T("6.0.0.0");
const NChar copyright[] = N_T("Copyright (C) 2008-2016 Neurotechnology");

int usage()
{
	printf(N_T("usage:\n"));
	printf(N_T("\t%s [reference image] [candidate image]\n"), title);
	printf(N_T("\n"));

	return 1;
}

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

int main(int argc, NChar **argv)
{

	if (argc < 3)
	{
		OnExit();
		return usage();
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

	OnStart(title, description, version, copyright, argc, argv);
	// check the license first
	result = NLicenseObtainComponents(N_T("/local"), N_T("5000"), components, &available);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NLicenseObtainComponents() failed (result = %d)!"), result);
		goto FINALLY;
	}

	if (!available)
	{
		printf(N_T("Licenses for %s not available\n"), components);
		result = N_E_NOT_ACTIVATED;
		goto FINALLY;
	}

	// create biometric client
	result = NBiometricClientCreate(&hBiometricClient);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NBiometricClientCreate() failed (result = %d)!"), result);
		goto FINALLY;
	}

	// create subject for probe image
	result = NSubjectCreate(&hProbeSubject);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NSubjectCreate() failed (result = %d)!"), result);
		goto FINALLY;
	}

	result = CreateSubject(hProbeSubject, argv[1]);
	if (NFailed(result))
	{
		PrintErrorMsg(N_T("CreateSubject() failed (result = %d)!"), result);
		goto FINALLY;
	}

	// create subject for gallery image
	result = NSubjectCreate(&hGallerySubject);
	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NSubjectCreate() failed (result = %d)!"), result);
		goto FINALLY;
	}

	result = CreateSubject(hGallerySubject, argv[2]);
	if (NFailed(result))
	{
		PrintErrorMsg(N_T("CreateSubject() failed (result = %d)!"), result);
		goto FINALLY;
	}

	{
		NInt matchingThreshold = 48;
		NMatchingSpeed matchingSpeed = nmsLow;

		// set matching threshold
		result = NObjectSetPropertyP(hBiometricClient, N_T("Matching.Threshold"), N_TYPE_OF(NInt32), naNone, &matchingThreshold, sizeof(matchingThreshold), 1, NTrue);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
			goto FINALLY;
		}

		// set matching speed
		result = NObjectSetPropertyP(hBiometricClient, N_T("Fingers.MatchingSpeed"), N_TYPE_OF(NMatchingSpeed), naNone, &matchingSpeed, sizeof(matchingSpeed), 1, NTrue);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NObjectSetPropertyP() failed (result = %d)!"), result);
			goto FINALLY;
		}
	}

	// verify probe and gallery templates
	result = NBiometricEngineVerifyOffline(hBiometricClient, hProbeSubject, hGallerySubject, &biometricStatus);

	if (NFailed(result))
	{
		result = PrintErrorMsgWithLastError(N_T("NBiometricEngineVerifyOffline() failed (result = %d)!"), result);
		goto FINALLY;
	}

	if (biometricStatus != nbsOk)
	{
		// retrieve biometric status
		result = NEnumToStringP(N_TYPE_OF(NBiometricStatus), biometricStatus, NULL, &hBiometricStatus);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NEnumToStringP() failed (result = %d)!"), result);
			goto FINALLY;
		}

		result = NStringGetBuffer(hBiometricStatus, NULL, &szBiometricStatus);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NStringGetBuffer() failed (result = %d)!"), result);
			goto FINALLY;
		}

		printf(N_T("verification failed!\n"));
		printf(N_T("biometric status: %s\n"), szBiometricStatus);

		result = N_E_FAILED;
		goto FINALLY;
	}
	else
	{
		// retrieve matching results from hProbeSubject
		result = NSubjectGetMatchingResult(hProbeSubject, 0, &hMatchingResults);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NStringGetBuffer() failed (result = %d)!"), result);
			goto FINALLY;
		}

		// retrieve matching score from matching results
		result = NMatchingResultGetScore(hMatchingResults, &matchScore);
		if (NFailed(result))
		{
			result = PrintErrorMsgWithLastError(N_T("NStringGetBuffer() failed (result = %d)!"), result);
			goto FINALLY;
		}

		printf(N_T("\nimage scored %d, verification.. "), matchScore);

		if (matchScore > 0)
			printf(N_T("succeeded\n"));
		else
			printf(N_T("failed\n"));
	}

	result = N_OK;
FINALLY:
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

	OnExit();

	//PrintErrorMsg(N_T("Result = %d\n"), result);
	for (int c = 0; c < 10000000000000; c++);
	//return result;
}
