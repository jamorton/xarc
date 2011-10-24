#ifndef __ABC_DATA_H__
#define __ABC_DATA_H__

#include <stdint.h>

/*** ABC Constants ***/

enum AbcPoolType {
	POOL_TYPE_unused_0x00        = 0x00,
	POOL_TYPE_Utf8               = 0x01,
	POOL_TYPE_Int                = 0x03,
	POOL_TYPE_UInt               = 0x04,
	POOL_TYPE_PrivateNs          = 0x05, // non-shared namespace
	POOL_TYPE_Double             = 0x06,
	POOL_TYPE_Qname              = 0x07, // o.ns::name, ct ns, ct name
	POOL_TYPE_Namespace          = 0x08,
	POOL_TYPE_Multiname          = 0x09, // o.name, ct nsset, ct name
	POOL_TYPE_False              = 0x0A,
	POOL_TYPE_True               = 0x0B,
	POOL_TYPE_Null               = 0x0C,
	POOL_TYPE_QnameA             = 0x0D, // o.@ns::name, ct ns, ct attr-name
	POOL_TYPE_MultinameA         = 0x0E, // o.@name, ct attr-name
	POOL_TYPE_RTQname            = 0x0F, // o.ns::name, rt ns, ct name
	POOL_TYPE_RTQnameA           = 0x10, // o.@ns::name, rt ns, ct attr-name
	POOL_TYPE_RTQnameL           = 0x11, // o.ns::[name], rt ns, rt name
	POOL_TYPE_RTQnameLA          = 0x12, // o.@ns::[name], rt ns, rt attr-name
	POOL_TYPE_NamespaceSet       = 0x15,
	POOL_TYPE_PackageNamespace   = 0x16,
	POOL_TYPE_PackageInternalNs  = 0x17,
	POOL_TYPE_ProtectedNamespace = 0x18,
	POOL_TYPE_ExplicitNamespace  = 0x19,
	POOL_TYPE_StaticProtectedNs  = 0x1A,
	POOL_TYPE_MultinameL         = 0x1B,
	POOL_TYPE_MultinameLA        = 0x1C,
	POOL_TYPE_TypeName           = 0x1D
};

/*** OPCODE DATA ***/

enum AbcOpcode
{
#define ABC_OP(a, b, c, d, name) OP_##name
#define ABC_UNUSED_OP ABC_OP
#include "opcodes.tbl"
#undef ABC_OP
#undef ABC_UNUSED_OP
};

typedef struct _AbcOpcodeInfo {
	int8_t operands;
	int8_t throws;
	int8_t stackChange;
	const char * name;
} AbcOpcodeInfo;

extern const AbcOpcodeInfo Opcode_Info[];

/*** ABC File data structures ***/

struct _AbcFile {
	uint16_t major;
	uint16_t minor;
	
};

struct _AbcConstantPool {
	uint32_t numInts;
	uint32_t numUints;
	uint32_t numDoubles;
	uint32_t numStrings;
	uint32_t numNamespaces;
	uint32_t numNssets;
	uint32_t numMultinames;
	int32_t * ints;
	uint32_t * uints;
	double * doubles;
	AbcString ** strings;
	
};

struct _AbcString {
	uint32_t size;
	char * data;
};

struct _AbcNamespace {
	AbcPoolType kind;
	AbcString * name;
};

struct _AbcNsset {
	uint32_t count;
	AbcNamespace * namespaces;
};

struct _AbcName {
	AbcPoolType kind;
	void * data;
};

struct _AbcQName {
	AbcNamespace * ns;
	AbcString * name;
};

struct _AbcRTQName {
	AbcString * name;
};

struct _AbcRTQNameL {
	uint8_t unused; // Empty struct may be bad...
};

struct _AbcMultiname {
	AbcString * name;
	AbcNsset * nsset;
};

struct _AbcMultinameL {
	AbcNsset * nsset;
};

typedef struct _AbcFile AbcFile;
typedef struct _AbcConstantPool AbcConstantPool;
typedef struct _AbcString AbcString;
typedef struct _AbcNamespace AbcNamespace;
typedef struct _AbcNsset AbcNsset;
typedef struct _AbcName AbcName;
typedef struct _AbcQName AbcQName;
typedef struct _AbcRTQName AbcRTQName;
typedef struct _AbcRTQNameL AbcRTQNameL;
typedef struct _AbcMultiname AbcMultiname;
typedef struct _AbcMultinameL AbcMultinameL;

#endif
