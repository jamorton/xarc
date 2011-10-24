
#include "abc.h"

const AbcOpcode Opcode_Info[] = {

#define ABC_OP(ops, throws, stack, _, name) { ops, throws, stackChange, #name },
#define ABC_UNUSED_OP ABC_OP

	#include "opcodes.tbl"

#undef ABC_OP
#undef ABC_UNUSED_OP

};


