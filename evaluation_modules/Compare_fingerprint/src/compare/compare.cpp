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

class Params
{
	//-i1 6 -i2 7 -geni 9
	//-f1 ../../img/01_li.bmp -f2 ../../img/01_ri.bmp -gen ../../img/unknown.bmp
	//-f1 C:\Users\danie\Documents\VUT\Otisky\db\fit_db_classes\whorl\a\1100_2_2_P3.bmp -f2 C:\Users\danie\Documents\VUT\Otisky\db\fit_db_classes\whorl\b\1135_2_3_P1.bmp -gen C:\Users\danie\Documents\VUT\Otisky\db\fit_db_classes\whorl\res_mask\1100_2_2_P3-1135_2_3_P1.tif
	//fingerprits can be compared like images (fingerprint1), or compare fingerprints in db (index1 ..)
	//-folder C:\Users\danie\Documents\VUT\Otisky\db\fit_db_classes\arch -suf .bmp
public:
	bool photos = false;					// compare by photos
	bool valid = true;						// are params valid?
	bool save = false;						// save result to db?
	const char* db_string = "";				// database for fingerprints (default is iengine.db) 
	const char* fingerprint1 = "";			// source image for fingerprint 1
	const char* fingerprint2 = "";			// source image for fingerprint 1
	int index1 = -1;						// index to db for fingerprint 1 
	int index2 = -1;						// index to db for fingerprint 2
	const char* generateFingerprint = "";	// source image for generated fingerprint 1
	int generateFingerprintIndex = -1;		// source image for generated fingerprint 2 
	string testFolder = "";					// source folder for testing
	string suf = "";						// suffix of fingerprint images in folder

	Params(int argc, char** argv)
	{
		//load params
		save = false;
		for (int i = 1; i < argc; i++) {
			if (string(argv[i]) == "-db") {
				i++;
				db_string = argv[i];
			}
			else if (string(argv[i]) == "-s") {
				save = true;
			}
			else if (string(argv[i]) == "-f1") {
				i++;
				fingerprint1 = argv[i];
			}
			else if (string(argv[i]) == "-f2") {
				i++;
				fingerprint2 = argv[i];
			}
			else if (string(argv[i]) == "-i1") {
				i++;
				index1 = stoi(argv[i]);
			}
			else if (string(argv[i]) == "-i2") {
				i++;
				index2 = stoi(argv[i]);
			}
			else if (string(argv[i]) == "-gen") {
				i++;
				generateFingerprint = argv[i];
			}
			else if (string(argv[i]) == "-geni") {
				i++;
				generateFingerprintIndex = stoi(argv[i]);
			}
			else if (string(argv[i]) == "-folder") {
				i++;
				testFolder = argv[i];
			}
			else if (string(argv[i]) == "-suf") {
				i++;
				suf = argv[i];
			}
			else {
				valid = false;
			}
		}
		//check if fingerprints are set
		if ((fingerprint1 == "" || fingerprint2 == "" || generateFingerprint == "") && testFolder == "") {
			if (index1 == -1 || index2 == -1 || (generateFingerprintIndex == -1 && generateFingerprint == "")){
				valid = false;
			}
		}
		else {
			photos = true;
		}

		//if do not save, then db string is "iengine.db"
		if (db_string=="") {
			db_string = "iengine.db";
		}
	}
};

void help() {
	cout << "./compare.exe -db _ -s -f1 _ -f2 _ -i1 _ -i2 _ -gen _ -geni _\n\n\
	-db databaseString		: optional, default is iengine.db\n\
	-s						: for saving result to db\n\
	-fN fingerN.bmp			: source image for fingerprint\n\
	-iN fingerprintIndexN	: index for fingerprint\n\
	-gen genFinger.bmp		: source image for generated fingerprint\n\
	-geni genIndex			: index for generated fingerprint\n\
	-folder path/to/folder	: path to folder with inputs to be tested (inputs of morphing not results!!)\n\
	-suf sufix				: sufix of images in folder\n\n\
Use source images or indexes. No combinations of -iN and fN are allowed. Exception is for generated fingerprint, where it can be used with -iN as index or image." << endl;
}

int registerFingerprint(const char* fingerprint) {
	//Initializing user structure
	IENGINE_USER user = IEngine_InitUser();
	if (user == NULL) {
		cout << "InitUser memory error." << endl;
		exit(1);
	}
	//Add user's fingerprint
	int ret = IEngine_AddFingerprintFromFile(user, UNKNOWN_FINGER, fingerprint);
	CHECK_ERROR("IEngine_AddFingerprintFromFile", ret);

	//Register user
	int userID;
	ret = IEngine_RegisterUser(user, &userID);
	CHECK_ERROR("IEngine_RegisterUser", ret);

	//We need to reset user structure (clear all previously associated fingerprints)
	ret = IEngine_ClearUser(user);
	CHECK_ERROR("IEngine_ClearUser", ret);


	return userID;
}

int matchFingerprints(int userID, const char* generateFingerprint, Params params) {
	int ret;
	/*****
		Create user for generated fingerprint
		or
		load one from db
	*****/
	IENGINE_USER user = IEngine_InitUser();
	if (params.generateFingerprintIndex == -1) {
		ret = IEngine_AddFingerprintFromFile(user, UNKNOWN_FINGER, generateFingerprint);
		
		CHECK_ERROR("IEngine_AddFingerprintFromFile", ret);
	}
	else {
		ret = IEngine_GetUser(user, params.generateFingerprintIndex);
		CHECK_ERROR("IEngine_GetUser(", ret);
	}

	/*****
		Compare generated fingerprint (fingerprint from
		second argument) with just registred fingerprint
	*****/

	//Match unknown fingerprint with previously registered users
	int bestIndex = -1, score = -1;
	ret = IEngine_MatchFingerprint(user, 0, userID, &bestIndex, &score);
	CHECK_ERROR("IEngine_MatchFingerprint", ret);
	

	/*****
		Remove just created users from db (if not params.save)
		and release resources
	*****/

	//remove users from database
	if (!params.save && params.photos) {
		ret = IEngine_RemoveUser(userID);
		CHECK_ERROR("IEngine_GetUserCount", ret);
	}

	//Release resources
	if (user) {
		ret = IEngine_FreeUser(user);
		CHECK_ERROR("IEngine_FreeUser", ret);
	}
	return score;
}

bool has_suffix(const string& str, const string& suffix)
{
	return str.size() >= suffix.size() &&
		str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

//returns paths to input images
tuple <string, string> getFileNames(path filepath, path inpath, string suf) {
	string morph_filename = filepath.filename().string();
	size_t dashpos = morph_filename.rfind("-");
	size_t point = morph_filename.rfind(".");
	string first_file = inpath.string() + "\\" + morph_filename.substr(0, dashpos) + suf;
	string second_file = inpath.string() + "\\" + morph_filename.substr(dashpos+1, point- dashpos - 1) + suf;
	return { first_file , second_file };
}


int main(int argc, char** argv)
{	
	int ret;
	
	//load params and check them
	Params params(argc, argv);
	if (!params.valid) {
		help();
		exit(1);
	}

	//Module initialization
	ret = IEngine_InitModule();
	CHECK_ERROR("IEngine_InitModule", ret);

	//Opens iengine.db flat file database.
	//If iengine.db does not exist, an empty database is created from scratch
	ret = IEngine_Connect(params.db_string);
	CHECK_ERROR("IEngine_Connect", ret);

	//Set trashold for comparison to 0
	ret = IEngine_SetParameter(CFG_SIMILARITY_THRESHOLD, 0);
	CHECK_ERROR("IEngine_SetParameter", ret);

	//if perform tests
	if (params.testFolder != "") {
		//paths to folders with fingerprints
		string folder_a = params.testFolder + "\\a\\";
		string folder_b = params.testFolder + "\\b\\";
		string folder_res = params.testFolder + "\\res_mask\\";
		//morph results that will be written in csv
		const int morph_len = 1010;
		int morph_results[morph_len] = {};
		//info printing
		int info_iterator = 0;
		string info_string = "Fingerprint no. ";
		cout << info_string + to_string(info_iterator);
		string max_image = "";
		int max_score = 0;
		//Go through folder and compare input images with morphed
		for (recursive_directory_iterator next(folder_res), end; next != end; ++next) {
			string filename_res = next->path().filename().string();
			string filepath = next->path().string();


			int dashpos = filename_res.find("-");
			int pointpos = filename_res.find(".");
			string filename_a = folder_a + filename_res.substr(0, dashpos) + params.suf;
			string filename_b = folder_b + filename_res.substr(dashpos+1, pointpos-(dashpos + 1)) + params.suf;

			//controll bash argument for input sufix
			if (params.suf != "" && has_suffix(filename_res, ".tif")) {
				//first fingerprint
				int userID = registerFingerprint(filename_a.c_str());
				int score1 = matchFingerprints(userID, filepath.c_str(), params);

				//second fingerprint
				userID = registerFingerprint(filename_b.c_str());
				int score2 = matchFingerprints(userID, filepath.c_str(), params);
				int score = score1 > score2 ? score2 : score1;

				if (score > max_score) {
					max_image = filename_res;
				}


				morph_results[score] += 1;
				//print how much done (only for info)
				cout << string((info_string + to_string(info_iterator)).length(), '\b');
				info_iterator++;
				cout << info_string + to_string(info_iterator);
			}
		}
		//write results to csv file
		ofstream fout;
		fout.open("results.csv", ios::out | ios::app);
		for (int i = 0; i < morph_len; i++) {
			fout << i << "," << morph_results[i] << "\n";
		}
		//cout << max_image << endl;
		//end comparing
		return 0;
	}
	else {

		/*****
			Create user with one fingerpritn (picture from first argument)
			and save him to db
			or
			Get existing users
		*****/
		int userID1 = (params.photos) ? registerFingerprint(params.fingerprint1) : params.index1;
		int userID2 = (params.photos) ? registerFingerprint(params.fingerprint2) : params.index2;

		int score = matchFingerprints(userID1, params.generateFingerprint, params);
		cout << "Similarity score for fingerprint is " << score << endl;
		score = matchFingerprints(userID2, params.generateFingerprint, params);
		cout << "Similarity score for fingerprint is " << score << endl;


		//save gen user if params.save
		if (params.save) {
			int genID = registerFingerprint(params.generateFingerprint);
			cout << "Id of saved fingerprint 1 is: " << userID1 << endl;
			cout << "Id of saved fingerprint 2 is: " << userID2 << endl;
			cout << "Id of saved gen fingerprint is: " << genID << endl;
		}

	}

	ret = IEngine_TerminateModule();
	CHECK_ERROR("IEngine_TerminateModule", ret);

	return 0;
}
