#ifndef AN_TYPE_7_RECORD_HPP_INCLUDED
#define AN_TYPE_7_RECORD_HPP_INCLUDED

#include <Biometrics/Standards/ANBinaryRecord.hpp>
namespace Neurotec { namespace Biometrics { namespace Standards
{
#include <Biometrics/Standards/ANType7Record.h>
}}}

namespace Neurotec { namespace Biometrics { namespace Standards
{

#undef AN_TYPE_7_RECORD_FIELD_LEN
#undef AN_TYPE_7_RECORD_FIELD_IDC
#undef AN_TYPE_7_RECORD_FIELD_UDF

const NInt AN_TYPE_7_RECORD_FIELD_LEN = AN_RECORD_FIELD_LEN;
const NInt AN_TYPE_7_RECORD_FIELD_IDC = AN_RECORD_FIELD_IDC;
const NInt AN_TYPE_7_RECORD_FIELD_UDF = AN_RECORD_FIELD_DATA;

class ANType7Record : public ANBinaryRecord
{
	N_DECLARE_OBJECT_CLASS(ANType7Record, ANBinaryRecord)

private:
	static HANType7Record Create(NVersion version, NInt idc, NUInt flags)
	{
		HANType7Record handle;
		NCheck(ANType7RecordCreate(version.GetValue(), idc, flags, &handle));
		return handle;
	}

public:
	explicit ANType7Record(NVersion version, NInt idc, NUInt flags = 0)
		: ANBinaryRecord(Create(version, idc, flags), true)
	{
	}
};

}}}

#endif // !AN_TYPE_7_RECORD_HPP_INCLUDED
