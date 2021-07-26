#include <TutorialUtils.hpp>

#ifdef N_MAC_OSX_FRAMEWORKS
	#include <NCore/NCore.hpp>
	#include <NBiometricClient/NBiometricClient.hpp>
	#include <NBiometrics/NBiometrics.hpp>
	#include <NMedia/NMedia.hpp>
	#include <NLicensing/NLicensing.hpp>
#else
	#include <NCore.hpp>
	#include <NBiometricClient.hpp>
	#include <NBiometrics.hpp>
	#include <NMedia.hpp>
	#include <NLicensing.hpp>
#endif

using namespace std;
using namespace Neurotec;
using namespace Neurotec::Licensing;
using namespace Neurotec::Biometrics;
using namespace Neurotec::Biometrics::Client;

const NChar title[] = N_T("VerifyFinger");
const NChar description[] = N_T("Demonstrates fingerprint verification.");
const NChar version[] = N_T("12.1.0.0");
const NChar copyright[] = N_T("Copyright (C) 2016-2021 Neurotechnology");

int usage()
{
	cout << "usage:" << endl;
	cout << "\t" << title << " [reference image] [candidate image] " << endl;
	return 1;
}

static NSubject CreateSubject(const NStringWrapper& fileName, const NStringWrapper& subjectId)
{
	NSubject subject;
	subject.SetId(subjectId);
	NFinger finger;
	finger.SetFileName(fileName);
	subject.GetFingers().Add(finger);
	return subject;
}

int main(int argc, NChar **argv)
{

	if (argc < 3)
	{
		OnExit();
		return usage();
	}

	//=========================================================================
	// CHOOSE LICENCES !!!
	//=========================================================================
	// ONE of the below listed "licenses" lines is required for unlocking this sample's functionality. Choose licenses that you currently have on your device.
	// If you are using a TRIAL version - choose any of them.
	// G:\fit_db_classes\combined\res_center\1100_2_1_L1-1100_3_1_P4.tif

	const NChar * licenses = { N_T("FingerMatcher,FingerExtractor") };
	//const NChar * licenses = { N_T("FingerMatcher,FingerClient") };
	//const NChar * licenses = { N_T("FingerFastMatcher,FingerFastExtractor") };

	//=========================================================================

	//=========================================================================
	// TRIAL MODE
	//=========================================================================
	// Below code line determines whether TRIAL is enabled or not. To use purchased licenses, don't use below code line.
	// GetTrialModeFlag() method takes value from "Bin/Licenses/TrialFlag.txt" file. So to easily change mode for all our examples, modify that file.
	// Also you can just set TRUE to "TrialMode" property in code.

	NLicenseManager::SetTrialMode(GetTrialModeFlag());

	//=========================================================================

	try
	{
		// Obtain licenses
		if (!NLicense::Obtain(N_T("/local"), N_T("5000"), licenses))
		{
			NThrowException(NString::Format(N_T("Could not obtain licenses: {S}"), licenses)); 
		}

		NSubject referenceSubject = CreateSubject(argv[1], argv[1]);
		NSubject candidateSubject = CreateSubject(argv[2], argv[2]);
		NBiometricClient biometricClient;
		biometricClient.SetMatchingThreshold(0);
		biometricClient.SetFingersMatchingSpeed(nmsLow);
		NBiometricStatus status = biometricClient.Verify(referenceSubject, candidateSubject);
		if (status == nbsOk || status == nbsMatchNotFound)
		{
			cout << "Image score " << referenceSubject.GetMatchingResults().Get(0).GetScore() << ", verification ";
			OnExit();
			return referenceSubject.GetMatchingResults().Get(0).GetScore();
		}
		else
		{
			cout << "Verification failed. Status: " << NEnum::ToString(NBiometricTypes::NBiometricStatusNativeTypeOf(), status) << endl;
			return -1;
		}
	}
	catch (NError& ex)
	{
		return LastError(ex);
	}

	OnExit();
	return 0;
}
