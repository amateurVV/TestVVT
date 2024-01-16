#pragma once
#include "type.h"

#define MAX_BIT8 0xFF
#define MAX_BIT16 0xFFFF
#define MAX_BIT32 0xFFFFFFFF
#define MAX_BIT64 0xFFFFFFFFFFFFFFFF

#define SYM_BIT64 0x8000000000000000
#define SYM_BIT32 0x80000000
#define SYM_BIT16 0x8000
#define SYM_BIT8 0x80

enum BitSize
{
	Bit8 = 1,
	Bit16 = 2,
	Bit32 = 4,
	Bit48 = 6,
	Bit64 = 8,
	Bit80 = 10,
	Bit128 = 16,
};


#pragma pack(push, 1)

typedef struct _OpcodeMap
{
	uint8 code;
	uint8 InstType;
	uint8 InstAttr;
	uint8 OpType;
	uint8 OpName;
	uint8 ArgType;
	union
	{
		struct
		{
			uint8 hi;
			uint8 lo;
		} s;
		uint16 attr;
	} Arg[4];
	void *Extend;
} OpcodeMap, *POpcodeMap;

typedef struct
{
	uint8 str[0x30];
	uint8 len;
} StrCtx;


typedef struct
{
	struct
	{
		union
		{
			struct
			{
				uint8 B : 1;
				uint8 X : 1;
				uint8 R : 1;
				uint8 W : 1;
				uint8 Flag : 4;
			} ctx;
			uint8 value;
		} Rex;
		union
		{
			struct
			{
				uint8 RM : 3;
				uint8 Reg : 3;
				uint8 Mod : 2;
			} ctx;
			uint8 value;
		} ModRM;
		union
		{
			struct
			{
				uint8 Base : 3;
				uint8 Index : 3;
				uint8 Scale : 2;
			} ctx;
			uint8 value;
		} SIB;
		struct
		{
			uint8 Opcode[4];
			uint8 count;
			uint8 type;
		} Op;
		struct
		{
			uint8 Pre[8];
			uint8 count;
			uint8 type;
		} Pre;
		union
		{
			int8 disp8;
			int16 disp16;
			int32 disp32;
			int64 disp64;
		} Disp[2];
		union
		{
			uint8 imm8;
			uint16 imm16;
			uint32 imm32;
			uint64 imm64;
		} Imme[2];
		uint16 Selector;
	} DisHex;

	struct
	{
		union
		{
			uint8 u8;
			uint16 u16;
			uint32 u32;
			uint64 u64;
		} Rip;
		union
		{
			uint8 u8;
			uint16 u16;
			uint32 u32;
			uint64 u64;
		} DestAddr;
		union
		{
			uint8 u8;
			uint16 u16;
			uint32 u32;
			uint64 u64;
		} CodeRip;

		uint8 instrLen;
		uint8 isAddr;
		uint8 mode;
		uint8 Dsize;
		uint8 Asize;
		OpcodeMap *pMap;
	} Ex;

	struct
	{
		StrCtx sAddr;
		StrCtx sHex;
		StrCtx sAsm;
	} DisAsm;

	struct
	{
		struct
		{
			uint8 preType;
			uint8 preSeg;
			uint8 preName;
			uint8 opType;
			uint8 opName;
			uint8 oplen;
			uint8 dispSize;
			uint8 immeSize;
			uint8 addrSize;
			uint8 argc;
		} ctx;
		struct
		{
			uint8 use_ptr : 1;
			uint8 use_seg : 1;
			uint8 use_bra : 1;
			uint8 use_regBase : 1;
			uint8 use_regIndex : 1;
			uint8 use_disp : 1;
			uint8 use_imme : 1;
			uint8 use_addr : 1;
			uint8 use_mul : 1;

			uint8 ptrType;
			uint8 regBase;
			uint8 regIndex;
			uint8 dispSize;
			uint8 immeSize;
			uint8 regSize;
			uint8 mulSize;
		} Arg[4];
		struct
		{
			uint8 pre : 1;
			uint8 seg : 1;
			uint8 rex : 1;
			uint8 modrm : 1;
			uint8 sib : 1;
			uint8 disp : 1;
			uint8 imme : 1;
			uint8 Sel : 1;
			uint8 ExModRM : 1;
		} Flags;
	} DisType;

} DisInstr;

#pragma pack(pop)

uint64 Decode(DisInstr *Instr, uint64 ExecRip, uint64 CodeRip, uint8 Mode);
uint64 InstrToHex(DisInstr *Instr);
uint64 InstrToAsm(DisInstr *Instr);