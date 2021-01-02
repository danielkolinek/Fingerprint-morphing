#ifndef AN_TYPE_2_RECORD_HPP_INCLUDED
#define AN_TYPE_2_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANAsciiRecord.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Biometrics/Standards/ANType2Record.h>
}}}

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef AN_TYPE_2_RECORD_FIELD_LEN
#undef AN_TYPE_2_RECORD_FIELD_IDC

#undef AN_TYPE_2_RECORD_FIELD_UDF_FROM
#undef AN_TYPE_2_RECORD_FIELD_UDF_TO
#undef AN_TYPE_2_RECORD_FIELD_UDF_TO_V4

const NInt AN_TYPE_2_RECORD_FIELD_LEN = AN_RECORD_FIELD_LEN;
const NInt AN_TYPE_2_RECORD_FIELD_IDC = AN_RECORD_FIELD_IDC;

const NInt AN_TYPE_2_RECORD_FIELD_UDF_FROM = (AN_TYPE_2_RECORD_FIELD_IDC + 1);
const NInt AN_TYPE_2_RECORD_FIELD_UDF_TO = AN_RECORD_MAX_FIELD_NUMBER;
const NInt AN_TYPE_2_RECORD_FIELD_UDF_TO_V4 = AN_ASCII_RECORD_MAX_FIELD_NUMBER;

class ANType2Record : public ANAsciiRecord
{
	N_DECLARE_OBJECT_CLASS(ANType2Record, ANAsciiRecord)

private:
	static HANType2Record Create(NVersion version, NInt idc, NUInt flags)
	{
		HANType2Record handle;
		NCheck(ANType2RecordCreate(version.GetValue(), idc, flags, &handle));
		return handle;
	}

public:
	explicit ANType2Record(NVersion version, NInt idc, NUInt flags = 0)
		: ANAsciiRecord(Create(version, idc, flags), true)
	{
	}
};

}}}

#endif // !AN_TYPE_2_RECORD_HPP_INCLUDED
