#ifndef CBEFF_QUALITY_ALGORITHM_IDENTIFIERS_H_INCLUDED
#define CBEFF_QUALITY_ALGORITHM_IDENTIFIERS_H_INCLUDED

#include <Core/NTypes.h>

#ifdef N_CPP
extern "C"
{
#endif

#define CBEFF_QAI_INTECH_QM 0x001A

#define CBEFF_QAI_NIST_NFIQ 0x377D

#define CBEFF_QAI_VENDOR_UNKNOWN_PRODUCT_UNKNOWN 0x0001

#define CBEFF_QAI_NEUROTECHNOLOGY_FRQ_1 0x0100

N_DECLARE_STATIC_OBJECT_TYPE(CbeffQualityAlgorithmIdentifiers)

#ifdef N_CPP
}
#endif

#endif // !CBEFF_QUALITY_ALGORITHM_IDENTIFIERS_H_INCLUDED
