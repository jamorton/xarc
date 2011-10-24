#ifndef __ABC_DATA_H__
#define __ABC_DATA_H__

#include <stdint.h>

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

typedef struct _AbcFile {
	uint16_t major;
	uint16_t minor;
	
} AbcFile;

typedef struct _AbcConstantPool {
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
	char ** strings;
	
} AbcConstantPool;

#endif
