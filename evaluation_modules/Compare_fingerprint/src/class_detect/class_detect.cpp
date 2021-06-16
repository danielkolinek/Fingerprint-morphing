/*******************************************************************************
*
*   Project         :   Match three fingerprints
*   Filename        :   main.cpp
*   Description     :   This console app uses Innovatrics software to compare 
						one gingerprint with two fingerprints. 
*
*   Author			:   Daniel Kolinek (xkolin05)
*   Platform        :   Linux/Windows
*   Language        :   C++
*
******************************************************************************/

#include <iostream>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>


#include <sstream>
#include <filesystem>
#include <fstream>

#include <tuple>


using namespace std;
using namespace std::filesystem;

#include "../../lib/idkit.h"

using namespace std;

// Error Checking Macros
#define CHECK_ERROR( msg, err ) {                                                                           \
    if ( (err) != IENGINE_E_NOERROR ) {                                                                     \
        cout << (msg) << ": Error code " << (err) << " - " << IEngine_GetErrorMsg(err) << endl;   \
        exit(err);                                                                                          \
    }                                                                                                       \
}


void help() {
	cout << "./class_detect.exe image_name width height\n\n\
	imagename				: image of fingerprint\n\
	width					: width of fingerprint image\n\
	height					: height of fingerprint image\n\
Detects class of fingerprint from input" << endl;
}

int main(int argc, char** argv)
{	
	int ret;
	
	//get image path from argument
	if (argc < 4) {
		help();
		return 42;
	}
	const char* fingerprint = argv[1];
	const int width = stoi(argv[2]);
	const int height = stoi(argv[3]);

	//Module initialization
	ret = IEngine_InitModule();
	CHECK_ERROR("IEngine_InitModule", ret);

	/*****regster user to db*****/
	//Initializing user structure
	const IENGINE_USER user = IEngine_InitUser();
	if (user == NULL) {
		cout << "InitUser memory error." << endl;
		exit(1);
	}
	//Add user's fingerprint
	ret = IEngine_AddFingerprintFromFile(user, UNKNOWN_FINGER, fingerprint);
	CHECK_ERROR("IEngine_AddFingerprintFromFile", ret);


	unsigned char fingerprintImage[260 * 300];
	int length =  width * height * sizeof(char);
	memset(fingerprintImage, 0, 260 * 300 * sizeof(char));
	
	//get user fingerprint
	ret = IEngine_GetFingerprintImage(user, UNKNOWN_FINGER, IENGINE_FORMAT_WSQ, fingerprintImage, &length);
	CHECK_ERROR("IEngine_GetFingerprintImage", ret);

	//get class of fingerprint
	int f_class = 0;
	ret = IEngine_GetFingerprintClass(fingerprintImage,  length, &f_class);
	
	cout << f_class << endl;

	ret = IEngine_TerminateModule();
	CHECK_ERROR("IEngine_TerminateModule", ret);

	return f_class;
}
