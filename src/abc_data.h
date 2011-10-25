#ifndef __ABC_DATA_H__
#define __ABC_DATA_H__

#include <stdint.h>

/*** ABC Constants ***/

typedef enum {
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
} AbcPoolType;

typedef enum {
    TRAIT_Slot          = 0x00,
    TRAIT_Method        = 0x01,
    TRAIT_Getter        = 0x02,
    TRAIT_Setter        = 0x03,
    TRAIT_Class         = 0x04,
    TRAIT_Const         = 0x06,
    TRAIT_COUNT         = TRAIT_Const+1,
    TRAIT_mask          = 15
} AbcTraitKind;

typedef enum
{
    /** need arguments[0..argc] */
    METHOD_NEED_ARGUMENTS         = 0x01,

    /** need activation object */
    METHOD_NEED_ACTIVATION        = 0x02,

    /** need arguments[param_count+1..argc] */
    METHOD_NEED_REST              = 0x04,

    /** has optional parameters */
    METHOD_HAS_OPTIONAL           = 0x08,

    /** allow extra args, but dont capture them */
    METHOD_IGNORE_REST            = 0x10,

    /** method is native */
    METHOD_NATIVE                 = 0x20,

    /** method sets default namespace */
    METHOD_SETS_DXNS              = 0x40,

    /** method has table for parameter names */
    METHOD_HAS_PARAM_NAMES        = 0x80
} AbcMethodFlags;

const uint8_t ATTR_final            = 0x10; // 1=final, 0=virtual
const uint8_t ATTR_override         = 0x20; // 1=override, 0=new
const uint8_t ATTR_metadata         = 0x40; // 1=has metadata, 0=no metadata

/*** OPCODE DATA ***/

typedef enum
{
#define ABC_OP(a, b, c, d, name) OP_##name,
#define ABC_UNUSED_OP ABC_OP
#include "opcodes.tbl"
#undef ABC_OP
#undef ABC_UNUSED_OP
} AbcOpcode;

typedef struct _AbcOpcodeInfo {
	int8_t operands;
	int8_t throws;
	int8_t stackChange;
	const char * name;
} AbcOpcodeInfo;

extern const AbcOpcodeInfo Opcode_Info[];

/*** Struct Objects ***/

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
typedef struct _AbcMethod AbcMethod;
typedef struct _AbcMethodOptions AbcMethodOptions;
typedef struct _AbcMetadata AbcMetadata;
typedef struct _AbcInstance AbcInstance;
typedef struct _AbcClass AbcClass;
typedef struct _AbcTrait AbcTrait;
typedef struct _AbcTraitSlot AbcTraitSlot;
typedef struct _AbcTraitClass AbcTraitClass;
typedef struct _AbcTraitFunction AbcTraitFunction;
typedef struct _AbcTraitMethod AbcTraitMethod;
typedef struct _AbcScript AbcScript;
typedef struct _AbcMethodBody AbcMethodBody;
typedef struct _AbcException AbcException;

/*** ABC STRUCTURES ***/

struct _AbcFile {
	uint16_t major;
	uint16_t minor;
	uint32_t numMethods;
	uint32_t numMetadatas;
	uint32_t numClasses;
	uint32_t numScripts;
	uint32_t numMethodBodies;
	AbcMethod ** methods;
	AbcMetadata ** metadatas;
	AbcInstance ** instances;
	AbcClass ** classes;
	AbcScript ** scripts;
	AbcMethodBody ** methodBodies;
};

// CONSTANT POOL

/*
 * Note: the AVM2 spec uses the word Multiname for two different concepts,
 * the kind contained in the cpool is called a Name here.
 */

struct _AbcConstantPool {
	uint32_t numInts;
	uint32_t numUints;
	uint32_t numDoubles;
	uint32_t numStrings;
	uint32_t numNamespaces;
	uint32_t numNssets;
	uint32_t numNames;
	int32_t * ints;
	uint32_t * uints;
	double * doubles;
	AbcString * strings;
	AbcNamespace * namespaces;
	AbcNsset * nssets;
	AbcName * names;
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

// METHODS

struct  _AbcMethodOptions {
	uint32_t count;
	AbcPoolType * kinds;
	void ** vals;  // a cpool entry, depends on kind
};

struct _AbcMethod {
	AbcName * returnType;
	uint32_t numParams;
	AbcName ** params;
	AbcString * name;
	uint8_t flags;
	// optional in Abc file but no need for that complexity
	AbcMethodOptions options;
	AbcString ** paramNames;
};

// METADATA

struct _AbcMetadata {
	AbcString * name;
	uint32_t count;
	AbcString ** keys;
	AbcString ** vals;
};

// INSTANCES

struct _AbcInstance {
	AbcName * name;
	AbcName * superName;
	uint8_t flags;
	AbcNamespace * protectedNamespace;
	uint32_t numInterfaces;
	AbcName ** interfaces;
	AbcMethod * iinit;
	uint32_t numTraits;
	AbcTrait ** traits;
};

// CLASSES

struct _AbcClass {
	AbcMethod * cinit;
	uint32_t numTraits;
	AbcTrait ** traits;
};

// TRAITS

struct _AbcTrait {
	AbcName * name;
	uint8_t kind;
	uint8_t attr;
	void * trait;
	uint32_t numMetadatas;
	AbcMetadata ** metadatas;
	
};

struct _AbcTraitSlot {
	uint32_t id;
	AbcMultiname * type;
	void * vIndex;
	AbcPoolType vKind;
};

struct _AbcTraitClass {
	uint32_t id;
	AbcClass * class;
};

struct _AbcTraitFunction {
	uint32_t id;
	AbcMethod * function;
};

struct _AbcTraitMethod {
	uint32_t disp;
	AbcMethod * method;
};

// SCRIPTS

struct _AbcScript {
	AbcMethod * init;
	uint32_t numTraits;
	AbcTrait ** traits;
};

// METHOD BODIES

struct _AbcMethodBody {
	AbcMethod * method;
	uint32_t maxStack;
	uint32_t localCount;
	uint32_t initScopeDepth;
	uint32_t maxScopeDepth;
	uint32_t codeLength;
	uint8_t * code;
	uint32_t numExceptions;
	AbcException ** exceptions;
	uint32_t numTraits;
	AbcTrait ** traits;
};

// EXCEPTIONS

struct _AbcException {
	uint32_t from;
	uint32_t to;
	uint32_t target;
	AbcString * type;
	AbcString * name;
};

#endif
