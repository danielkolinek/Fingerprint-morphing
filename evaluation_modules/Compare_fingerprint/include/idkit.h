#ifndef INNOVATRICS_IDKIT_H
#define INNOVATRICS_IDKIT_H

#ifdef __cplusplus
# define IDKIT_BOOL bool
#else
# define IDKIT_BOOL char
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#ifdef IDKIT_API_STATIC
#   define IDKIT_API
#else
#   define IDKIT_API __declspec( dllimport )
#endif
#else
#define IDKIT_API
#endif

#define CRYPT_KEY_LENGTH 32
#define MAX_CRITICAL_POINTS_COUNT 16
#define IPLUGIN_DESCRIPTION_MAX_LEN 256


// === Types definition === //

typedef enum
{
    UNKNOWN_FINGER = 0,
    RIGHT_THUMB = 1,
    RIGHT_INDEX = 2,
    RIGHT_MIDDLE = 3,
    RIGHT_RING = 4,
    RIGHT_LITTLE = 5,
    LEFT_THUMB = 6,
    LEFT_INDEX = 7,
    LEFT_MIDDLE = 8,
    LEFT_RING = 9,
    LEFT_LITTLE = 10,
    UNKNOWN_PALM = 20,
    RIGHT_FULL_PALM = 21,
    LEFT_FULL_PALM = 23,
    UNKNOWN_PRINT = 40
} IENGINE_FINGER_POSITION;

typedef enum
{
    IENGINE_FORMAT_BMP = 0,
	IENGINE_FORMAT_PNG = 1,
	IENGINE_FORMAT_JPG = 2,
	IENGINE_FORMAT_GIF = 3,
	IENGINE_FORMAT_TIF = 4,
	IENGINE_FORMAT_WSQ = 5,
	IENGINE_FORMAT_JPEG2K=6
} IENGINE_IMAGE_FORMAT;

typedef enum
{
    FORMAT_ICS = 1,
    FORMAT_ANSI = 2,
	FORMAT_ISO = 3,
    FORMAT_ANSI_PLUS = 4,
    FORMAT_ISO_PLUS = 5
} IENGINE_TEMPLATE_FORMAT;

typedef enum
{
    CFG_BEST_CANDIDATES_COUNT = 0,
    CFG_SIMILARITY_THRESHOLD = 1,
    CFG_SCANNER_TYPE = 2,
    CFG_RESOLUTION_DPI = 3,
    CFG_MAX_ROTATION = 4,
    CFG_STORE_IMAGES = 5,
    CFG_IDENTIFICATION_SPEED = 6,
	CFG_NETWORK_COMPRESSION = 7,
    CFG_LOG_LEVEL = 8,
    CFG_MAX_TEMPLATE_SIZE = 10,
	CFG_JPEG2K_COMPRESSION_RATIO = 11,
	CFG_WSQ_BITRATE = 12,
	CFG_DB_IMAGE_FORMAT = 13,
	CFG_LOAD_IMAGES = 14,
	CFG_MAX_ODBC_LOADING_THREADS = 15,
    //  not supported CFG_ICS_TEMPLATE_VERSION = 16,
	CFG_EXTRACT_CRITICAL_POINTS = 17,
	CFG_EXTRACTOR_ALGORITHM = 18,
	CFG_MAX_IENGINE_THREAD_COUNT = 25
} IENGINE_CONFIG;

typedef enum
{
    MODE_GENERAL = 0,
    MODE_ROLLED = 6
} IENGINE_SCANNER_TYPE;

typedef enum
{
	EXTRACTOR_SPEED_NORMAL = 0,
	EXTRACTOR_SPEED_FAST = 2,
	EXTRACTOR_SPEED_FASTEST = 4,
    EXTRACTOR_SPEED_AFIS = 8
} IENGINE_EXTRACTOR_ALGORITHM;

typedef void *IENGINE_USER;
typedef void *IENGINE_COLLECTION;
typedef void *IENGINE_CONNECTION;

typedef struct
{
    unsigned char angle;
    unsigned short x;
    unsigned short y;
    unsigned char type;
    unsigned char quality;
} IENGINE_MINUTIAE, *IENGINE_MINUTIAE_PTR;

typedef struct
{
	unsigned char angle;
	unsigned short x;
	unsigned short y;
	unsigned char type;
} IENGINE_CRITICAL_POINT, *IENGINE_CRITICAL_POINT_PTR;

typedef enum {
    IENGINE_HARDWARE_ID_METHOD_AUTO = 0,
    IENGINE_HARDWARE_ID_METHOD_DISKID = 1,
    IENGINE_HARDWARE_ID_METHOD_MAC = 2,
    IENGINE_HARDWARE_ID_METHOD_SERIALNO = 3,
    IENGINE_HARDWARE_ID_METHOD_IMEI = 4,
    IENGINE_HARDWARE_ID_METHOD_SMBIOS = 5,
    IENGINE_HARDWARE_ID_METHOD_AMAZON = 6,
    IENGINE_HARDWARE_ID_METHOD_APPID = 7,
    IENGINE_HARDWARE_ID_METHOD_PHY = 8,
    IENGINE_HARDWARE_ID_METHOD_MAC_ADDR = 9
} IENGINE_HARDWARE_ID_METHOD;

// === Initialization and Termination functions ===//

IDKIT_API int IEngine_InitModule( );
IDKIT_API int IEngine_InitWithLicense( const unsigned char *license, int length );
IDKIT_API int IEngine_InitWithChallenge(unsigned char *challenge, unsigned int * challenge_size, const unsigned char *hmac_signature, unsigned int hmac_size);
IDKIT_API int IEngine_TerminateModule( );
IDKIT_API int IEngine_CheckLicense( );

// === Connections === //

IDKIT_API IENGINE_CONNECTION IEngine_InitConnection();
IDKIT_API int IEngine_SelectConnection(const IENGINE_CONNECTION connection);
IDKIT_API int IEngine_CloseConnection(IENGINE_CONNECTION connection);

#ifndef IDKIT_LIGHT_SDK
IDKIT_API int IEngine_Connect( const char * databaseFile);
IDKIT_API int IEngine_InitClient( const char * connectionString );
#endif

// === Configuration Functions === //

IDKIT_API int IEngine_SetParameter( IENGINE_CONFIG parameter, int value );
IDKIT_API int IEngine_GetParameter( IENGINE_CONFIG parameter, int *value );
IDKIT_API int IEngine_SetCryptKey(const unsigned char cryptKey[CRYPT_KEY_LENGTH]);


// === Product Version Information === //

IDKIT_API const char * IEngine_GetProductString();


// === Database Management Related Functions === //

#ifndef IDKIT_LIGHT_SDK
IDKIT_API int IEngine_ClearDatabase();

IDKIT_API int IEngine_RegisterUser(const IENGINE_USER user, int * userID );
IDKIT_API int IEngine_RegisterUserAs(const IENGINE_USER user, int userID );
IDKIT_API int IEngine_UpdateUser( const IENGINE_USER user, int userID );
IDKIT_API int IEngine_RemoveUser( int userID );

IDKIT_API int IEngine_GetUserIfExists( IENGINE_USER user , int userID, int * userExists );
IDKIT_API int IEngine_GetUser( IENGINE_USER user, int userID );
IDKIT_API int IEngine_UserExists( int userID , int * userExists );
IDKIT_API int IEngine_GetUserCount(int *userCount);
IDKIT_API int IEngine_GetMemoryUsage(int * memoryUsage);
IDKIT_API int IEngine_GetUserLimit(int *userLimit);
IDKIT_API int IEngine_GetAllUserIDs(IENGINE_COLLECTION collection);
IDKIT_API int IEngine_GetUserIDsByQuery(IENGINE_COLLECTION collection, const char * query);
#endif

// === User Related Functions === //

IDKIT_API IENGINE_USER IEngine_InitUser();
IDKIT_API int IEngine_CopyUser( const IENGINE_USER srcUser, IENGINE_USER dstUser, IDKIT_BOOL withImages);
IDKIT_API int IEngine_ClearUser( IENGINE_USER user);
IDKIT_API int IEngine_FreeUser( IENGINE_USER user);

IDKIT_API int IEngine_AddFingerprint( IENGINE_USER user, IENGINE_FINGER_POSITION fingerPosition, const unsigned char * fingerprintImage, int imgSize);
IDKIT_API int IEngine_AddFingerprintRAW( IENGINE_USER user, IENGINE_FINGER_POSITION position, const unsigned char * rawImage, int width, int height);
IDKIT_API int IEngine_GetIntermediateImages(const unsigned char* rawImage, int width, int height, unsigned char* skeleton, unsigned char* filtered, unsigned char* binarized, int* bWidth, int* bHeight, unsigned char* bMask);
IDKIT_API int IEngine_AddFingerprintFromFile( IENGINE_USER user, IENGINE_FINGER_POSITION fingerPosition, const char * filename);
IDKIT_API int IEngine_AddFingerprintFromUser( IENGINE_USER user, IENGINE_USER fromUser, int fromIndex, IDKIT_BOOL withImage );
IDKIT_API int IEngine_SetCustomData( IENGINE_USER user, const unsigned char *data, int length );
IDKIT_API int IEngine_SetFingerprint( IENGINE_USER user, int fingerprintIndex, IENGINE_FINGER_POSITION fingerPosition, const unsigned char * fingerprintImage, int imgSize);
IDKIT_API int IEngine_SetFingerprintRAW( IENGINE_USER user, int fingerprintIndex, IENGINE_FINGER_POSITION fingerPosition, const unsigned char * rawImage, int width, int height );
IDKIT_API int IEngine_SetFingerprintFromFile( IENGINE_USER user, int fingerprintIndex, IENGINE_FINGER_POSITION fingerPosition, const char * filename);
IDKIT_API int IEngine_SetFingerprintFromUser( IENGINE_USER user, int index, const IENGINE_USER fromUser, int fromIndex, IDKIT_BOOL withImage );
IDKIT_API int IEngine_SetFingerPosition( IENGINE_USER user, int fingerprintIndex, IENGINE_FINGER_POSITION fingerPosition);
IDKIT_API int IEngine_RemoveFingerprint( IENGINE_USER user, int fingerprintIndex);
IDKIT_API int IEngine_AttachFingerprintImage(IENGINE_USER user, int fingerprintIndex, const unsigned char * fingerprintImage);

IDKIT_API int IEngine_GetCustomData( const IENGINE_USER user, unsigned char *data, int *length );
IDKIT_API int IEngine_FingerprintImageExists( const IENGINE_USER user, int index, int * exists );
IDKIT_API int IEngine_GetFingerprintImage( const IENGINE_USER user, int fingerprintIndex, IENGINE_IMAGE_FORMAT format, unsigned char * fingerprintImage, int * length );
IDKIT_API int IEngine_SaveFingerprintImage( const IENGINE_USER user, int fingerprintIndex, IENGINE_IMAGE_FORMAT format, const char *filename);
IDKIT_API int IEngine_GetFingerPosition( const IENGINE_USER user, int fingerprintIndex, IENGINE_FINGER_POSITION *fingerPosition);
IDKIT_API int IEngine_GetFingerprintCount( const IENGINE_USER user, int *fingerprintCount);

IDKIT_API int IEngine_GetFingerprintQuality(const IENGINE_USER user,int fingerprintIndex, int *quality);
IDKIT_API int IEngine_GetFingerprintPresence(const unsigned char * fingerprintImage, int imgSize, int *presence);
IDKIT_API int IEngine_GetFingerprintPresenceRAW( const unsigned char * rawImage, int width, int height, int *presence );
IDKIT_API int IEngine_GetFingerprintClass(const unsigned char* fingerprintImage, int length, int *fingerprintClass);
IDKIT_API int IEngine_SaveMinutiaeImage( const IENGINE_USER user, int fingerprintIndex, IENGINE_IMAGE_FORMAT format, const char *filename);
IDKIT_API int IEngine_GetMinutiaeImage( const IENGINE_USER user, int fingerprintIndex, IENGINE_IMAGE_FORMAT format,unsigned char * minutiaeImage, int * length );
IDKIT_API int IEngine_GetMinutiaePoints( const IENGINE_USER user, int fingerprintIndex, int *minutiaeCount, IENGINE_MINUTIAE* minutiae);
IDKIT_API int IEngine_GetDeltasAndCores( const IENGINE_USER user, int fingerprintIndex, int * criticalPointsCount, IENGINE_CRITICAL_POINT criticalPoints[MAX_CRITICAL_POINTS_COUNT] );


// === User Related Functions : Extended Use === //

IDKIT_API int IEngine_ExportUserTemplate(const IENGINE_USER user, IENGINE_TEMPLATE_FORMAT format, unsigned char *templateData, int *length);
IDKIT_API int IEngine_ImportUserTemplate(IENGINE_USER user, IENGINE_TEMPLATE_FORMAT format, const unsigned char *templateData);
IDKIT_API int IEngine_ExportCompactTemplate(const IENGINE_USER userRecord,int fingerprintIndex,int maxTemplateSize,unsigned char *compactTemplate,int *templateSize);
IDKIT_API int IEngine_ImportCompactTemplate( IENGINE_USER user, const unsigned char * compactTemplate, IENGINE_FINGER_POSITION fingerPosition );
IDKIT_API int IEngine_SerializeUser( const IENGINE_USER user, IDKIT_BOOL serializeImages, unsigned char * buffer, int * length );
IDKIT_API int IEngine_DeserializeUser( IENGINE_USER user, const unsigned char * buffer );


// === User Related Functions : Tags === //

IDKIT_API int IEngine_SetStringTag(IENGINE_USER user, const char * name, const char * value);
IDKIT_API int IEngine_GetStringTag(const IENGINE_USER user, const char * name, char * value, int * length);
IDKIT_API int IEngine_SetIntTag(IENGINE_USER user, const char * name, int value);
IDKIT_API int IEngine_GetIntTag(const IENGINE_USER user, const char * name, int * value);
IDKIT_API int IEngine_ClearTag(IENGINE_USER user, const char * name);
IDKIT_API int IEngine_HasTag(const IENGINE_USER user, const char * name, int * present);
IDKIT_API int IEngine_GetTagCount(const IENGINE_USER user, int * count);
IDKIT_API int IEngine_GetTagName(const IENGINE_USER user, int offset, char * name, int * length);

// === User Collection Functions === //
#ifndef IDKIT_LIGHT_SDK
IDKIT_API IENGINE_COLLECTION IEngine_InitCollection();
IDKIT_API int IEngine_FreeCollection(IENGINE_COLLECTION collection);
IDKIT_API int IEngine_GetCollectionSize(const IENGINE_COLLECTION collection, int * count);
IDKIT_API int IEngine_GetCollectionIDs(const IENGINE_COLLECTION collection, int * ids, int count);
#endif

// === Conversion Functions === //

IDKIT_API int IEngine_ConvertBmp2RawImage(const unsigned char *bmpImage, int bmpSize,unsigned char * rawImage, int *width, int *height);
IDKIT_API int IEngine_ConvertRawImage2Bmp(const unsigned char *rawImage, int width, int height, unsigned char * bmpImage, int *length);
IDKIT_API int IEngine_ConvertImage(const unsigned char *inImage, int inLength, IENGINE_IMAGE_FORMAT format, unsigned char *outImage, int *outLength);
IDKIT_API int IEngine_RescaleImage(const unsigned char *inImage, int inWidth, int inHeight, int dpi, unsigned char *outImage, int *outWidth, int *outHeight);

// === Identification Functions === //

#ifndef IDKIT_LIGHT_SDK
IDKIT_API int IEngine_FindUser(const IENGINE_USER user, int * userID, int * score );
IDKIT_API int IEngine_FindFingerprint(const IENGINE_USER user, int fingerprintIndex, int * userID, int *bestIndex, int * score );
IDKIT_API int IEngine_FindUserInSelection(const IENGINE_USER user,int selectionCount, const int *selectedUserIDs,int *userID,int *score);
IDKIT_API int IEngine_FindFingerprintInSelection(const IENGINE_USER user, int index, int selectionCount, const int *selectedUserIDs,int * userID, int *bestIndex, int *score);
IDKIT_API int IEngine_FindUserInMemory(const IENGINE_USER user, int recordCount, const unsigned char **recordsInMemory, int *userID, int *score);
IDKIT_API int IEngine_FindFingerprintInMemory(const IENGINE_USER user, int index, int recordCount, const unsigned char **recordsInMemory, int *userID, int *bestIndex, int *score);
IDKIT_API int IEngine_FindUserByQuery(const IENGINE_USER user, const char * query, int * uids, int * scores);
IDKIT_API int IEngine_FindFingerprintByQuery(const IENGINE_USER user, int index, const char * query, int * uids, int * bestIndices, int * scores);
#endif

// === Database Verification Functions (userID) === //

#ifndef IDKIT_LIGHT_SDK
IDKIT_API int IEngine_MatchUser(const IENGINE_USER user, int userID, int * score );
IDKIT_API int IEngine_MatchUserEx(const IENGINE_USER user, int userID, int * score, int * matchingFingersCount );
IDKIT_API int IEngine_MatchFingerprint(const IENGINE_USER user, int fingerprintIndex, int userID,int *bestIndex,int * score );
#endif


// === Plain Verification Functions === //

IDKIT_API int IEngine_MatchUsers(const IENGINE_USER probeUser, const IENGINE_USER galleryUser, int * score );
IDKIT_API int IEngine_MatchUsersEx(const IENGINE_USER probeUser, const IENGINE_USER galleryUser, int * score , int * matchingFingersCount );
IDKIT_API int IEngine_MatchFingerprints(const IENGINE_USER probeUser, int fingerprintIndex, const IENGINE_USER galleryUser, int fingerprintIndex2, int * score );
IDKIT_API int IEngine_MatchFingerprints_transformation(const IENGINE_USER probeUser, int index, const IENGINE_USER galleryUser, int index2, int * score, int * dx, int * dy, unsigned char *dAngle);
IDKIT_API int IEngine_MatchFingerprintsEx(const IENGINE_USER probeUser, int fingerprintIndex, const IENGINE_USER galleryUser, int fingerprintIndex2, int * score, int * dx, int * dy, unsigned char * dAngle, int * associationCount, unsigned short * assocProbeMinutiae, unsigned short * assocGalleryMinutiae, unsigned char * assocQuality);

// === Error Handling === //

IDKIT_API const char * IEngine_GetErrorMsg( int errcode );
IDKIT_API int IEngine_SetLogFile( const char * filename );

// == NEW == //

IDKIT_API int IEngine_GetHardwareId( char * hwId, int *length);
IDKIT_API int IEngine_GetHardwareIdByMethod( IENGINE_HARDWARE_ID_METHOD method, char *hwid, int *length );
IDKIT_API int IEngine_GetLicenseInformation( char *hwId, int *hwId_length, char *clientId, int *clientId_length, int *userLimit, int *clientLimit, int *expYear, int *expMonth, int *expDay, char *licFileLocation );
IDKIT_API int IEngine_GetLicenseValue(const char *key, char *value, int *valueLength);
IDKIT_API int IEngine_ReloadConfig();

IDKIT_API const char * IEngine_GetServiceState(int *err);

// == Unsupported enums for internal purposes == //

typedef enum {
    /*
    This parameter is read-only
    */
    CFG_IDENTIFICATION_MINUTIAE_FEATURE_MAP_SIZE = 5000,
    /*
    This parameter is write-only
    */
    CFG_IDENTIFICATION_MINUTIAE_FEATURE_MAP_BUFFER = 5001
} IENGINE_INTERNAL_CONFIG;

typedef enum {
	ACCESS_MODE_READ_ONLY = 0,
	ACCESS_MODE_READ_WRITE,
	ACCESS_MODE_UNKNOWN,
    ACCESS_MODE_FULL
} IENGINE_ACCESS_MODE;

// == Unsupported functions for internal purposes == //

IDKIT_API int IEngine_AddMultiScaleFingerprint( IENGINE_USER user, IENGINE_FINGER_POSITION position, const unsigned char * image, int imgSize, int dpi1, int dpi2, int dpi3, int dpi4 );
IDKIT_API int IEngine_AddFingerprintWithMinutiaePoints( IENGINE_USER user, IENGINE_FINGER_POSITION position, const unsigned char * image, int imgSize, unsigned char * imageMask, IENGINE_MINUTIAE * forcedMinutiae, int minutiaeCount );
IDKIT_API int IEngine_SetFingerprintWithMinutiaePoints( IENGINE_USER user, int index, IENGINE_FINGER_POSITION position, const unsigned char * image, int imgSize, unsigned char * imageMask, IENGINE_MINUTIAE * forcedMinutiae, int minutiaeCount );
IDKIT_API int IEngine_AddFingerprintRAWWithMinutiaePoints( IENGINE_USER user, IENGINE_FINGER_POSITION position, const unsigned char * rawImage, int width, int height, unsigned char * imageMask, IENGINE_MINUTIAE * forcedMinutiae, int minutiaeCount );
IDKIT_API int IEngine_SetFingerprintRAWWithMinutiaePoints( IENGINE_USER user, int index, IENGINE_FINGER_POSITION position, const unsigned char * rawImage, int width, int height, unsigned char * imageMask, IENGINE_MINUTIAE * forcedMinutiae, int minutiaeCount );
IDKIT_API int IEngine_SetPtrParameter( IENGINE_CONFIG , void * ptr );
IDKIT_API int IEngine_GetAccessMode(IENGINE_ACCESS_MODE* accessMode);
IDKIT_API int IEngine_ReloadLicense();

// === Error Messages === //

#define IENGINE_E_NOERROR           0
#define IENGINE_E_BADPARAM          1101
#define IENGINE_E_NOFINGERPRINT     1102
#define IENGINE_E_DBOPEN            1111
#define IENGINE_E_DBFAILED          1112
#define IENGINE_E_DBACCESSDENIED    1113
#define IENGINE_E_BLANKIMAGE        1114
#define IENGINE_E_BADIMAGE          1115
#define IENGINE_E_INIT              1116
#define IENGINE_E_FILE              1117
#define IENGINE_E_BADUSER           1118
#define IENGINE_E_BADINDEX          1119
#define IENGINE_E_MEMORY            1120
#define IENGINE_E_NULLPARAM         1121
#define IENGINE_E_OTHER             1122
#define IENGINE_E_NOIMAGE           1123
#define IENGINE_E_INTERNAL          1124
#define IENGINE_E_NONEXISTINGID     1125
#define IENGINE_E_DUPLICATEID       1126
#define IENGINE_E_BADUSERID         1127
#define IENGINE_E_DBFULL            1128
#define IENGINE_E_BADLICENSE        1129
#define IENGINE_E_EXPIREDLICENSE    1130
#define IENGINE_E_MISSINGDLL        1131
#define IENGINE_E_BADFORMAT         1132
#define IENGINE_E_BADVALUE          1133
#define IENGINE_E_INCONSISTENTSIZE  1134 // Deprecated
#define IENGINE_E_BADTEMPLATE       1135
#define IENGINE_E_QUERYSYNTAX       1136
#define IENGINE_E_INCOMPATIBLE_TEMPLATE 1137
#define IENGINE_E_SEARCHINDEX       1138
#define IENGINE_E_BADCRYPTKEY       1140
#define IENGINE_E_SSL               1141
#define IENGINE_E_USERFULL          1142
#define IENGINE_E_DBMISSINGTABLE    1143
#define IENGINE_E_DBBADVERSION      1144
#define IENGINE_E_INTDBFULL         1145
#define IENGINE_E_SMALLIMAGE        1146
#define IENGINE_E_BIGIMAGE          1147
#define IENGINE_E_BADDPI            1148

#define IENGINE_E_NOTIMPLEMENTED    1150
#define IENGINE_E_BADMASK           1151


#define IENGINE_E_NOTEMPLATES       1160
#define IENGINE_E_SOME_TEMLATE_DATA_MISSING     1164

#define IENGINE_E_SRVFAILED         1201
#define IENGINE_E_CONSTR            1202
#define IENGINE_E_CONTYPE           1203
#define IENGINE_E_NOTCONNECTED      1204
#define IENGINE_E_MAXCLIENTS        1205
#define IENGINE_E_NONODE            1206 // Deprecated
#define IENGINE_E_NODEDISCONNECTED  1207 // Deprecated
#define IENGINE_E_TEMPORARY         1208
#define IENGINE_E_PROTOCOL          1209
#define IENGINE_E_PASSWORD          1210
#define IENGINE_E_NOTSUPPORTED      1211
#define IENGINE_E_SOAPFAILED        1212


// === Deprecated Symbols === //


#ifdef __cplusplus
}
#endif

#endif // INNOVATRICS_IDKIT_H
