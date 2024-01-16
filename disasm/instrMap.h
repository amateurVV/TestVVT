#pragma once
#include "type.h"
#include "instrtype.h"

#pragma pack(1)
struct  OpcodeMap;
#pragma pack()


OpcodeMap ReMapGroup1[][8] =
	{
		{
			{0x80, Inst_EModRM, 0, Op_Calc, C_ADD, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0x80, Inst_EModRM, 0, Op_Calc, C_OR, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0x80, Inst_EModRM, 0, Op_Calc, C_ADC, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0x80, Inst_EModRM, 0, Op_Calc, C_SBB, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0x80, Inst_EModRM, 0, Op_Calc, C_AND, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0x80, Inst_EModRM, 0, Op_Calc, C_SUB, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0x80, Inst_EModRM, 0, Op_Calc, C_XOR, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0x80, Inst_EModRM, 0, Op_Calc, C_CMP, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
		},
		{
			{0x81, Inst_EModRM, 0, Op_Calc, C_ADD, Arg_E_ModRM, {{E, v}, {I, z}, {0}, {0}}, 0},
			{0x81, Inst_EModRM, 0, Op_Calc, C_OR, Arg_E_ModRM, {{E, v}, {I, z}, {0}, {0}}, 0},
			{0x81, Inst_EModRM, 0, Op_Calc, C_ADC, Arg_E_ModRM, {{E, v}, {I, z}, {0}, {0}}, 0},
			{0x81, Inst_EModRM, 0, Op_Calc, C_SBB, Arg_E_ModRM, {{E, v}, {I, z}, {0}, {0}}, 0},
			{0x81, Inst_EModRM, 0, Op_Calc, C_AND, Arg_E_ModRM, {{E, v}, {I, z}, {0}, {0}}, 0},
			{0x81, Inst_EModRM, 0, Op_Calc, C_SUB, Arg_E_ModRM, {{E, v}, {I, z}, {0}, {0}}, 0},
			{0x81, Inst_EModRM, 0, Op_Calc, C_XOR, Arg_E_ModRM, {{E, v}, {I, z}, {0}, {0}}, 0},
			{0x81, Inst_EModRM, 0, Op_Calc, C_CMP, Arg_E_ModRM, {{E, v}, {I, z}, {0}, {0}}, 0},
		},
		{
			{0x82, Inst_EModRM, Up_i64, Op_Calc, C_ADD, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0x82, Inst_EModRM, Up_i64, Op_Calc, C_OR, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0x82, Inst_EModRM, Up_i64, Op_Calc, C_ADC, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0x82, Inst_EModRM, Up_i64, Op_Calc, C_SBB, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0x82, Inst_EModRM, Up_i64, Op_Calc, C_AND, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0x82, Inst_EModRM, Up_i64, Op_Calc, C_SUB, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0x82, Inst_EModRM, Up_i64, Op_Calc, C_XOR, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0x82, Inst_EModRM, Up_i64, Op_Calc, C_CMP, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
		},
		{
			{0x83, Inst_EModRM, 0, Op_Calc, C_ADD, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
			{0x83, Inst_EModRM, 0, Op_Calc, C_OR, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
			{0x83, Inst_EModRM, 0, Op_Calc, C_ADC, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
			{0x83, Inst_EModRM, 0, Op_Calc, C_SBB, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
			{0x83, Inst_EModRM, 0, Op_Calc, C_AND, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
			{0x83, Inst_EModRM, 0, Op_Calc, C_SUB, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
			{0x83, Inst_EModRM, 0, Op_Calc, C_XOR, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
			{0x83, Inst_EModRM, 0, Op_Calc, C_CMP, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
		},
};
OpcodeMap ReMapGroup2[][8] =
	{
		{
			{0xC0, Inst_EModRM, 0, Op_Logic, L_ROL, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0xC0, Inst_EModRM, 0, Op_Logic, L_ROR, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0xC0, Inst_EModRM, 0, Op_Logic, L_RCL, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0xC0, Inst_EModRM, 0, Op_Logic, L_RCR, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0xC0, Inst_EModRM, 0, Op_Logic, L_SHL, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0xC0, Inst_EModRM, 0, Op_Logic, L_SHR, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0xC0, Inst_EModRM, 0, Op_Logic, L_SAL, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0xC0, Inst_EModRM, 0, Op_Logic, L_SAR, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
		},
		{
			{0xC1, Inst_EModRM, 0, Op_Logic, L_ROL, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
			{0xC1, Inst_EModRM, 0, Op_Logic, L_ROR, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
			{0xC1, Inst_EModRM, 0, Op_Logic, L_RCL, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
			{0xC1, Inst_EModRM, 0, Op_Logic, L_RCR, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
			{0xC1, Inst_EModRM, 0, Op_Logic, L_SHL, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
			{0xC1, Inst_EModRM, 0, Op_Logic, L_SHR, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
			{0xC1, Inst_EModRM, 0, Op_Logic, L_SAL, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
			{0xC1, Inst_EModRM, 0, Op_Logic, L_SAR, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
		},
		{
			{0xD0, Inst_EModRM, 0, Op_Logic, L_ROL, Arg_E_ModRM, {{E, b}, {I, Imm1}, {0}, {0}}, 0},
			{0xD0, Inst_EModRM, 0, Op_Logic, L_ROR, Arg_E_ModRM, {{E, b}, {I, Imm1}, {0}, {0}}, 0},
			{0xD0, Inst_EModRM, 0, Op_Logic, L_RCL, Arg_E_ModRM, {{E, b}, {I, Imm1}, {0}, {0}}, 0},
			{0xD0, Inst_EModRM, 0, Op_Logic, L_RCR, Arg_E_ModRM, {{E, b}, {I, Imm1}, {0}, {0}}, 0},
			{0xD0, Inst_EModRM, 0, Op_Logic, L_SHL, Arg_E_ModRM, {{E, b}, {I, Imm1}, {0}, {0}}, 0},
			{0xD0, Inst_EModRM, 0, Op_Logic, L_SHR, Arg_E_ModRM, {{E, b}, {I, Imm1}, {0}, {0}}, 0},
			{0xD0, Inst_EModRM, 0, Op_Logic, L_SAL, Arg_E_ModRM, {{E, b}, {I, Imm1}, {0}, {0}}, 0},
			{0xD0, Inst_EModRM, 0, Op_Logic, L_SAR, Arg_E_ModRM, {{E, b}, {I, Imm1}, {0}, {0}}, 0},
		},
		{
			{0xD1, Inst_EModRM, 0, Op_Logic, L_ROL, Arg_E_ModRM, {{E, v}, {I, Imm1}, {0}, {0}}, 0},
			{0xD1, Inst_EModRM, 0, Op_Logic, L_ROR, Arg_E_ModRM, {{E, v}, {I, Imm1}, {0}, {0}}, 0},
			{0xD1, Inst_EModRM, 0, Op_Logic, L_RCL, Arg_E_ModRM, {{E, v}, {I, Imm1}, {0}, {0}}, 0},
			{0xD1, Inst_EModRM, 0, Op_Logic, L_RCR, Arg_E_ModRM, {{E, v}, {I, Imm1}, {0}, {0}}, 0},
			{0xD1, Inst_EModRM, 0, Op_Logic, L_SHL, Arg_E_ModRM, {{E, v}, {I, Imm1}, {0}, {0}}, 0},
			{0xD1, Inst_EModRM, 0, Op_Logic, L_SHR, Arg_E_ModRM, {{E, v}, {I, Imm1}, {0}, {0}}, 0},
			{0xD1, Inst_EModRM, 0, Op_Logic, L_SAL, Arg_E_ModRM, {{E, v}, {I, Imm1}, {0}, {0}}, 0},
			{0xD1, Inst_EModRM, 0, Op_Logic, L_SAR, Arg_E_ModRM, {{E, v}, {I, Imm1}, {0}, {0}}, 0},
		},
		{
			{0xD2, Inst_EModRM, 0, Op_Logic, L_ROL, Arg_E_ModRM, {{E, b}, {R_CL}, {0}, {0}}, 0},
			{0xD2, Inst_EModRM, 0, Op_Logic, L_ROR, Arg_E_ModRM, {{E, b}, {R_CL}, {0}, {0}}, 0},
			{0xD2, Inst_EModRM, 0, Op_Logic, L_RCL, Arg_E_ModRM, {{E, b}, {R_CL}, {0}, {0}}, 0},
			{0xD2, Inst_EModRM, 0, Op_Logic, L_RCR, Arg_E_ModRM, {{E, b}, {R_CL}, {0}, {0}}, 0},
			{0xD2, Inst_EModRM, 0, Op_Logic, L_SHL, Arg_E_ModRM, {{E, b}, {R_CL}, {0}, {0}}, 0},
			{0xD2, Inst_EModRM, 0, Op_Logic, L_SHR, Arg_E_ModRM, {{E, b}, {R_CL}, {0}, {0}}, 0},
			{0xD2, Inst_EModRM, 0, Op_Logic, L_SAL, Arg_E_ModRM, {{E, b}, {R_CL}, {0}, {0}}, 0},
			{0xD2, Inst_EModRM, 0, Op_Logic, L_SAR, Arg_E_ModRM, {{E, b}, {R_CL}, {0}, {0}}, 0},
		},
		{
			{0xD3, Inst_EModRM, 0, Op_Logic, L_ROL, Arg_E_ModRM, {{E, v}, {R_CL}, {0}, {0}}, 0},
			{0xD3, Inst_EModRM, 0, Op_Logic, L_ROR, Arg_E_ModRM, {{E, v}, {R_CL}, {0}, {0}}, 0},
			{0xD3, Inst_EModRM, 0, Op_Logic, L_RCL, Arg_E_ModRM, {{E, v}, {R_CL}, {0}, {0}}, 0},
			{0xD3, Inst_EModRM, 0, Op_Logic, L_RCR, Arg_E_ModRM, {{E, v}, {R_CL}, {0}, {0}}, 0},
			{0xD3, Inst_EModRM, 0, Op_Logic, L_SHL, Arg_E_ModRM, {{E, v}, {R_CL}, {0}, {0}}, 0},
			{0xD3, Inst_EModRM, 0, Op_Logic, L_SHR, Arg_E_ModRM, {{E, v}, {R_CL}, {0}, {0}}, 0},
			{0xD3, Inst_EModRM, 0, Op_Logic, L_SAL, Arg_E_ModRM, {{E, v}, {R_CL}, {0}, {0}}, 0},
			{0xD3, Inst_EModRM, 0, Op_Logic, L_SAR, Arg_E_ModRM, {{E, v}, {R_CL}, {0}, {0}}, 0},
		},
};
OpcodeMap ReMapGroup3[][8] =
	{
		{
			{0xF6, Inst_EModRM, 0, Op_Calc, C_TEST, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0xF6, Inst_UD2, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, 0},
			{0xF6, Inst_EModRM, 0, Op_Calc, C_NOT, Arg_E_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
			{0xF6, Inst_EModRM, 0, Op_Calc, C_NEG, Arg_E_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
			{0xF6, Inst_EModRM, 0, Op_Calc, C_MUL, Arg_E_ModRM, {{E, b}, {R_AL}, {0}, {0}}, 0},
			{0xF6, Inst_EModRM, 0, Op_Calc, C_IMUL, Arg_E_ModRM, {{E, b}, {R_AL}, {0}, {0}}, 0},
			{0xF6, Inst_EModRM, 0, Op_Calc, C_DIV, Arg_E_ModRM, {{E, b}, {R_AL}, {0}, {0}}, 0},
			{0xF6, Inst_EModRM, 0, Op_Calc, C_IDIV, Arg_E_ModRM, {{E, b}, {R_AL}, {0}, {0}}, 0},
		},
		{
			{0xF7, Inst_EModRM, 0, Op_Calc, C_TEST, Arg_E_ModRM, {{E, v}, {I, z}, {0}, {0}}, 0},
			{0xF7, Inst_UD2, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, 0},
			{0xF7, Inst_EModRM, 0, Op_Calc, C_NOT, Arg_E_ModRM, {{E, v}, {0}, {0}, {0}}, 0},
			{0xF7, Inst_EModRM, 0, Op_Calc, C_NEG, Arg_E_ModRM, {{E, v}, {0}, {0}, {0}}, 0},
			{0xF7, Inst_EModRM, 0, Op_Calc, C_MUL, Arg_E_ModRM, {{E, v}, {R_rAX}, {0}, {0}}, 0},
			{0xF7, Inst_EModRM, 0, Op_Calc, C_IMUL, Arg_E_ModRM, {{E, v}, {R_rAX}, {0}, {0}}, 0},
			{0xF7, Inst_EModRM, 0, Op_Calc, C_DIV, Arg_E_ModRM, {{E, v}, {R_rAX}, {0}, {0}}, 0},
			{0xF7, Inst_EModRM, 0, Op_Calc, C_IDIV, Arg_E_ModRM, {{E, v}, {R_rAX}, {0}, {0}}, 0},
		},
};
OpcodeMap ReMapGroup4[][8] =
	{
		{
			{0xFE, Inst_EModRM, 0, Op_Calc, C_INC, Arg_E_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
			{0xFE, Inst_EModRM, 0, Op_Calc, C_DEC, Arg_E_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
			{0},
			{0},
			{0},
			{0},
			{0},
			{0},
		},
};
OpcodeMap ReMapGroup5[][8] =
	{
		{
			{0xFF, Inst_EModRM, 0, Op_Calc, C_INC, Arg_E_ModRM, {{E, v}, {0}, {0}, {0}}, 0},
			{0xFF, Inst_EModRM, 0, Op_Calc, C_DEC, Arg_E_ModRM, {{E, v}, {0}, {0}, {0}}, 0},
			{0xFF, Inst_EModRM, Up_f64, Op_Jcc, J_CALL, Arg_E_ModRM, {{E, v}, {0}, {0}, {0}}, 0},
			{0xFF, Inst_EModRM, 0, Op_Jcc, J_CALL, Arg_E_ModRM, {{E, p}, {0}, {0}, {0}}, 0},
			{0xFF, Inst_EModRM, Up_f64, Op_Jcc, J_JMP, Arg_E_ModRM, {{E, v}, {0}, {0}, {0}}, 0},
			{0xFF, Inst_EModRM, 0, Op_Jcc, J_JMP, Arg_E_ModRM, {{M, p}, {0}, {0}, {0}}, 0},
			{0xFF, Inst_EModRM, Up_d64, Op_Stack, K_PUSH, Arg_E_ModRM, {{E, v}, {0}, {0}, {0}}, 0},
			{0xFF, Inst_UD2},
		},
};
OpcodeMap ReMapGroup6[][8] =
	{
		{
			{0x00, Inst_EModRM, 0, Op_Sys, S_SLDT, Arg_E_ModRM, {{M, w}, {0}, {0}, {0}}, 0},
			{0x00, Inst_EModRM, 0, Op_Sys, S_STR, Arg_E_ModRM, {{M, w}, {0}, {0}, {0}}, 0},
			{0x00, Inst_EModRM, 0, Op_Sys, S_LLDT, Arg_E_ModRM, {{E, w}, {0}, {0}, {0}}, 0},
			{0x00, Inst_EModRM, 0, Op_Sys, S_LTR, Arg_E_ModRM, {{E, w}, {0}, {0}, {0}}, 0},
			{0x00, Inst_EModRM, 0, Op_Sys, S_VERR, Arg_E_ModRM, {{E, w}, {0}, {0}, {0}}, 0},
			{0x00, Inst_EModRM, 0, Op_Sys, S_VERW, Arg_E_ModRM, {{E, w}, {0}, {0}, {0}}, 0},
			{0x00, Inst_UD2},
			{0x00, Inst_UD2},
		},
};
OpcodeMap ReMapGroup7[][8] =
	{
		{
			// mod=mem
			{0x01, Inst_EModRM, 0, Op_Sys, S_SGDT, Arg_E_ModRM, {{M, s}, {0}, {0}, {0}}, 0},
			{0x01, Inst_EModRM, 0, Op_Sys, S_SIDT, Arg_E_ModRM, {{M, s}, {0}, {0}, {0}}, 0},
			{0x01, Inst_EModRM, 0, Op_Sys, S_LGDT, Arg_E_ModRM, {{E, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_EModRM, 0, Op_Sys, S_LIDT, Arg_E_ModRM, {{E, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_EModRM, 0, Op_Sys, S_SMSW, Arg_E_ModRM, {{M, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_LMSW, Arg_E_ModRM, {{E, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_EModRM, 0, Op_Sys, S_INVLPG, Arg_E_ModRM, {{M, b}, {0}, {0}, {0}}, 0},
		},
		{
			// mod=11,rm=000
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_MONITOR, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0x01, Inst_EModRM, 0, Op_Sys, S_XGETBV, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_SMSW, Arg_E_ModRM, {{M, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_LMSW, Arg_E_ModRM, {{E, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_EModRM, Up_o64, Op_Sys, S_SWAPGS, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
		},
		{
			// mod=11,rm=001
			{0x01, Inst_EModRM, 0, Op_Vm, V_VMCALL, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0x01, Inst_EModRM, 0, Op_Sys, S_MWAIT, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0x01, Inst_EModRM, 0, Op_Sys, S_XSETBV, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_SMSW, Arg_E_ModRM, {{M, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_LMSW, Arg_E_ModRM, {{E, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_EModRM, 0, Op_Sys, S_RDTSCP, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
		},
		{
			// mod=11,rm=010
			{0x01, Inst_EModRM, 0, Op_Vm, V_VMLAUNCH, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0x01, Inst_EModRM, 0, Op_Sys, S_CLAC, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_SMSW, Arg_E_ModRM, {{M, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_LMSW, Arg_E_ModRM, {{E, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
		},
		{
			// mod=11,rm=011
			{0x01, Inst_EModRM, 0, Op_Vm, V_VMRESUME, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0x01, Inst_EModRM, 0, Op_Sys, S_STAC, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_SMSW, Arg_E_ModRM, {{M, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_LMSW, Arg_E_ModRM, {{E, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
		},
		{
			// mod=11,rm=100
			{0x01, Inst_EModRM, 0, Op_Vm, V_VMXOFF, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Vm, V_VMFUNC, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_SMSW, Arg_E_ModRM, {{M, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_LMSW, Arg_E_ModRM, {{E, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
		},
		{
			// mod=11,rm=101
			{0x01, Inst_UD2},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_XEND, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_SMSW, Arg_E_ModRM, {{M, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_LMSW, Arg_E_ModRM, {{E, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
		},
		{
			// mod=11,rm=110
			{0x01, Inst_UD2},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_XTEST, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_SMSW, Arg_E_ModRM, {{M, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_LMSW, Arg_E_ModRM, {{E, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
		},
		{
			// mod=11,rm=111
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_ENCLS, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0x01, Inst_EModRM, 0, Op_Sys, S_ENCLU, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_SMSW, Arg_E_ModRM, {{M, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
			{0x01, Inst_EModRM, 0, Op_Sys, S_LMSW, Arg_E_ModRM, {{E, w}, {0}, {0}, {0}}, 0},
			{0x01, Inst_UD2},
		},
};
OpcodeMap ReMapGroup8[][8] =
	{
		{
			{0xBA, Inst_UD2},
			{0xBA, Inst_UD2},
			{0xBA, Inst_UD2},
			{0xBA, Inst_UD2},
			{0xBA, Inst_EModRM, 0, Op_Calc, C_BT, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
			{0xBA, Inst_EModRM, 0, Op_Calc, C_BTS, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
			{0xBA, Inst_EModRM, 0, Op_Calc, C_BTR, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
			{0xBA, Inst_EModRM, 0, Op_Calc, C_BTC, Arg_E_ModRM, {{E, v}, {I, b}, {0}, {0}}, 0},
		},
};
OpcodeMap ReMapGroup9[][8] =
	{
		{
			// modrm:mem-pre-no
			{0xC7, Inst_UD2},
			{0xC7, Inst_EModRM, 0, Op_Data, D_CMPXCHG, Arg_E_ModRM, {{M, q}, {0}, {0}, {0}}, 0},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_EModRM, 0, Op_Vm, V_VMPTRLD, Arg_E_ModRM, {{M, q}, {0}, {0}, {0}}, 0},
			{0xC7, Inst_EModRM, 0, Op_Vm, V_VMPTRST, Arg_E_ModRM, {{M, q}, {0}, {0}, {0}}, 0},
		},
		{
			// modrm:mem-pre-0x66
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_EModRM, 0, Op_Vm, V_VMCLEAR, Arg_E_ModRM, {{M, q}, {0}, {0}, {0}}, 0},
			{0xC7, Inst_UD2},
		},
		{
			// modrm:mem-pre-0xF3
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_EModRM, 0, Op_Vm, V_VMXON, Arg_E_ModRM, {{M, q}, {0}, {0}, {0}}, 0},
			{0xC7, Inst_UD2},
		},
		{
			// modrm:mod=11B,pre-no
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_EModRM, 0, Op_Sys, S_RDRAND, Arg_E_ModRM, {{R, v}, {0}, {0}, {0}}, 0},
			{0xC7, Inst_EModRM, 0, Op_Sys, S_RDSEED, Arg_E_ModRM, {{R, v}, {0}, {0}, {0}}, 0},
		},
		{
			// modrm:mod=11B,pre-0xF3
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_UD2},
			{0xC7, Inst_EModRM, 0, Op_Sys, S_RDPID, Arg_E_ModRM, {{R, v}, {0}, {0}, {0}}, 0},
		},
};
OpcodeMap ReMapGroup10[][8] =
	{
		{
			{0xB9, Inst_UD2},
			{0},
			{0},
			{0},
			{0},
			{0},
			{0},
			{0},
		},
};
OpcodeMap ReMapGroup11[][8] =
	{
		{
			{0xC6, Inst_EModRM, 0, Op_Data, D_MOV, Arg_E_ModRM, {{E, b}, {I, b}, {0}, {0}}, 0},
			{0xC6, Inst_EModRM, 0, Op_Other, O_XABORT, Arg_E_ModRM, {{I, b}, {0}, {0}, {0}}, 0},
			{0},
			{0},
			{0},
			{0},
			{0},
			{0},
		},
		{
			{0xC7, Inst_EModRM, 0, Op_Data, D_MOV, Arg_E_ModRM, {{E, v}, {I, z}, {0}, {0}}, 0},
			{0xC7, Inst_EModRM, 0, Op_Other, O_BEGIN, Arg_E_ModRM, {{J, z}, {0}, {0}, {0}}, 0},
			{0},
			{0},
			{0},
			{0},
			{0},
			{0},
		},
};
OpcodeMap ReMapGroup12[][8] =
	{
		{
			{0x71, Inst_UD2},
			{0x71, Inst_UD2},
			{0x71, Inst_EModRM, 0, Op_SSE, SSE_PSRLW, Arg_E_ModRM, {{N, q}, {I, b}, {0}, {0}}, 0},
			{0x71, Inst_UD2},
			{0x71, Inst_EModRM, 0, Op_SSE, SSE_PSRAW, Arg_E_ModRM, {{N, q}, {I, b}, {0}, {0}}, 0},
			{0x71, Inst_UD2},
			{0x71, Inst_EModRM, 0, Op_SSE, SSE_PSLLW, Arg_E_ModRM, {{N, q}, {I, b}, {0}, {0}}, 0},
			{0x71, Inst_UD2},
		},
		{
			{0x71, Inst_UD2},
			{0x71, Inst_UD2},
			{0x71, Inst_EModRM, 0, Op_SSE, SSE_VPSRLW, Arg_E_ModRM, {{H, x}, {U, x}, {I, b}, {0}}, 0},
			{0x71, Inst_UD2},
			{0x71, Inst_EModRM, 0, Op_SSE, SSE_VPSRAW, Arg_E_ModRM, {{H, x}, {U, x}, {I, b}, {0}}, 0},
			{0x71, Inst_UD2},
			{0x71, Inst_EModRM, 0, Op_SSE, SSE_VPSLLW, Arg_E_ModRM, {{H, x}, {U, x}, {I, b}, {0}}, 0},
			{0x71, Inst_UD2},
		},
};
OpcodeMap ReMapGroup13[][8] =
	{
		{
			{0x72, Inst_UD2},
			{0x72, Inst_UD2},
			{0x72, Inst_EModRM, 0, Op_SSE, SSE_PSRLD, Arg_E_ModRM, {{N, q}, {I, b}, {0}, {0}}, 0},
			{0x72, Inst_UD2},
			{0x72, Inst_EModRM, 0, Op_SSE, SSE_PSRAD, Arg_E_ModRM, {{N, q}, {I, b}, {0}, {0}}, 0},
			{0x72, Inst_UD2},
			{0x72, Inst_EModRM, 0, Op_SSE, SSE_PSLLD, Arg_E_ModRM, {{N, q}, {I, b}, {0}, {0}}, 0},
			{0x72, Inst_UD2},
		},
		{
			{0x72, Inst_UD2},
			{0x72, Inst_UD2},
			{0x72, Inst_EModRM, 0, Op_SSE, SSE_VPSRLD, Arg_E_ModRM, {{H, x}, {U, x}, {I, b}, {0}}, 0},
			{0x72, Inst_UD2},
			{0x72, Inst_EModRM, 0, Op_SSE, SSE_VPSRAD, Arg_E_ModRM, {{H, x}, {U, x}, {I, b}, {0}}, 0},
			{0x72, Inst_UD2},
			{0x72, Inst_EModRM, 0, Op_SSE, SSE_VPSLLD, Arg_E_ModRM, {{H, x}, {U, x}, {I, b}, {0}}, 0},
			{0x72, Inst_UD2},
		},
};
OpcodeMap ReMapGroup14[][8] =
	{
		{
			{0x73, Inst_UD2},
			{0x73, Inst_UD2},
			{0x73, Inst_EModRM, 0, Op_SSE, SSE_PSRLQ, Arg_E_ModRM, {{N, q}, {I, b}, {0}, {0}}, 0},
			{0x73, Inst_UD2},
			{0x73, Inst_UD2},
			{0x73, Inst_UD2},
			{0x73, Inst_EModRM, 0, Op_SSE, SSE_PSLLQ, Arg_E_ModRM, {{N, q}, {I, b}, {0}, {0}}, 0},
			{0x73, Inst_UD2},
		},
		{
			{0x73, Inst_UD2},
			{0x73, Inst_UD2},
			{0x73, Inst_EModRM, 0, Op_SSE, SSE_VPSRLQ, Arg_E_ModRM, {{H, x}, {U, x}, {I, b}, {0}}, 0},
			{0x73, Inst_EModRM, 0, Op_SSE, SSE_VPSRLDQ, Arg_E_ModRM, {{H, x}, {U, x}, {I, b}, {0}}, 0},
			{0x73, Inst_UD2},
			{0x73, Inst_UD2},
			{0x73, Inst_EModRM, 0, Op_SSE, SSE_VPSLLQ, Arg_E_ModRM, {{H, x}, {U, x}, {I, b}, {0}}, 0},
			{0x73, Inst_EModRM, 0, Op_SSE, SSE_VPSLLDQ, Arg_E_ModRM, {{H, x}, {U, x}, {I, b}, {0}}, 0},
		},
};
OpcodeMap ReMapGroup15[][8] =
	{
		{
			// modrm->mod==mem
			{0xAE, Inst_EModRM, 0, Op_Other, O_FXSAVE, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0xAE, Inst_EModRM, 0, Op_Other, O_FXRSTOR, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0xAE, Inst_EModRM, 0, Op_Other, O_LDMXCSR, Arg_Null, {{M, d}, {0}, {0}, {0}}, 0},
			{0xAE, Inst_EModRM, 0, Op_Other, O_STMXCSR, Inst_EModRM, {{M, d}, {0}, {0}, {0}}, 0},
			{0xAE, Inst_EModRM, 0, Op_Other, O_XSAVE, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0xAE, Inst_EModRM, 0, Op_Other, O_XRSTOR, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0xAE, Inst_EModRM, 0, Op_Other, O_XSAVEOPT, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0xAE, Inst_EModRM, 0, Op_Other, O_CLFLUSH, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
		},
		{
			// modrm->mod==11B
			{0xAE, Inst_UD2},
			{0xAE, Inst_UD2},
			{0xAE, Inst_UD2},
			{0xAE, Inst_UD2},
			{0xAE, Inst_UD2},
			{0xAE, Inst_EModRM, 0, Op_Other, O_LFENCE, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0xAE, Inst_EModRM, 0, Op_Other, O_MFENCE, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0xAE, Inst_EModRM, 0, Op_Other, O_SFENCE, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
		},
		{
			// modrm->mod==11B && pre==0xF3
			{0xAE, Inst_EModRM, 0, Op_Sys, S_RDFSBASE, Arg_E_ModRM, {{R, y}, {0}, {0}, {0}}, 0},
			{0xAE, Inst_EModRM, 0, Op_Sys, S_RDGSBASE, Arg_E_ModRM, {{R, y}, {0}, {0}, {0}}, 0},
			{0xAE, Inst_EModRM, 0, Op_Sys, S_WRFSBASE, Arg_E_ModRM, {{R, y}, {0}, {0}, {0}}, 0},
			{0xAE, Inst_EModRM, 0, Op_Sys, S_WRGSBASE, Arg_E_ModRM, {{R, y}, {0}, {0}, {0}}, 0},
			{0xAE, Inst_UD2},
			{0xAE, Inst_UD2},
			{0xAE, Inst_UD2},
			{0xAE, Inst_UD2},
		},
};
OpcodeMap ReMapGroup16[][8] =
	{
		{
			{0xAE, Inst_EModRM, 0, Op_Sys, S_PREFETCH, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0xAE, Inst_EModRM, 0, Op_Sys, S_PREFETCH, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0xAE, Inst_EModRM, 0, Op_Sys, S_PREFETCH, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0xAE, Inst_EModRM, 0, Op_Sys, S_PREFETCH, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
			{0xAE, Inst_UD2},
			{0xAE, Inst_UD2},
			{0xAE, Inst_UD2},
			{0xAE, Inst_UD2},
		},
};
OpcodeMap ReMapGroup1A[][8] =
	{
		{
			{0x8F, Inst_EModRM, Up_d64, 0, K_POP, Arg_E_ModRM, {{E, v}, {0}, {0}, {0}}, 0},
			{0},
			{0},
			{0},
			{0},
			{0},
			{0},
			{0},
		},
};

OpcodeMap ReEscape[] = {
	{0},
};

OpcodeMap ReMapVEX2[]={
	{0},
};
OpcodeMap ReMapVEX1[]={
	{0},
};

OpcodeMap ThreeByte[]={
	{0},
};

OpcodeMap TwoByteReserve[] = {
	{0x10, Inst_UD2, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, 0},
};
OpcodeMap ReMapNOP[] = {
	{0x10, Inst_Gen, 0, Op_Other, O_NOP, 0, {{0}, {0}, {0}, {0}}, 0},
};

OpcodeMap ExPre10[] = {
	{0x10, Inst_Gen, 0, Op_SSE, V_VMOVUPS, Arg_ModRM, {{V, ps}, {W, ps}, {0}, {0}}, 0},
	{0x10, Inst_Gen, 0, Op_SSE, V_VMOVUPD, Arg_ModRM, {{V, pd}, {W, pd}, {0}, {0}}, 0},
	{0x10, Inst_Gen, 0, Op_SSE, V_VMOVSS, Arg_ModRM, {{V, x}, {H, x}, {W, ss}, {0}}, 0},
	{0x10, Inst_Gen, 0, Op_SSE, V_VMOVSD, Arg_ModRM, {{V, x}, {H, x}, {W, sd}, {0}}, 0},
};
OpcodeMap ExPre11[] = {
	{0x11, Inst_Gen, 0, Op_SSE, V_VMOVUPS, Arg_ModRM, {{W, ps}, {V, ps}, {0}, {0}}, 0},
	{0x11, Inst_Gen, 0, Op_SSE, V_VMOVUPD, Arg_ModRM, {{W, pd}, {V, pd}, {0}, {0}}, 0},
	{0x11, Inst_Gen, 0, Op_SSE, V_VMOVSS, Arg_ModRM, {{W, ss}, {H, x}, {V, ss}, {0}}, 0},
	{0x11, Inst_Gen, 0, Op_SSE, V_VMOVSD, Arg_ModRM, {{W, sd}, {H, x}, {V, sd}, {0}}, 0},
};
OpcodeMap ExPre12[] = {
	{0x12, Inst_Gen, 0, Op_SSE, V_VMOVLPS, Arg_ModRM, {{V, q}, {H, q}, {M, q}, {0}}, 0},
	{0x12, Inst_Gen, 0, Op_SSE, V_VMOVLPD, Arg_ModRM, {{V, q}, {H, q}, {M, q}, {0}}, 0},
	{0x12, Inst_Gen, 0, Op_SSE, V_VMOVSLDUP, Arg_ModRM, {{V, x}, {W, x}, {0}, {0}}, 0},
	{0x12, Inst_Gen, 0, Op_SSE, V_VMOVDDUP, Arg_ModRM, {{V, x}, {W, x}, {0}, {0}}, 0},
};
OpcodeMap ExPre13[] = {
	{0x13, Inst_Gen, 0, Op_SSE, V_VMOVLPS, Arg_ModRM, {{M, q}, {V, q}, {0}, {0}}, 0},
	{0x13, Inst_Gen, 0, Op_SSE, V_VMOVLPD, Arg_ModRM, {{M, q}, {V, q}, {0}, {0}}, 0},
	{0x13, Inst_UD2},
	{0x13, Inst_UD2},
};
OpcodeMap ExPre14[] = {
	{0x14, Inst_Gen, 0, Op_SSE, V_VUNPCKLPS, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x14, Inst_Gen, 0, Op_SSE, V_VUNPCKLPD, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x14, Inst_UD2},
	{0x14, Inst_UD2},
};
OpcodeMap ExPre15[] = {
	{0x15, Inst_Gen, 0, Op_SSE, V_VUNPCKHPS, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x15, Inst_Gen, 0, Op_SSE, V_VUNPCKHPD, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x15, Inst_UD2},
	{0x15, Inst_UD2},
};
OpcodeMap ExPre16[] = {
	{0x16, Inst_Gen, Up_v1, Op_SSE, V_VMOVHPS, Arg_ModRM, {{V, dq}, {H, q}, {M, q}, {0}}, 0},
	{0x16, Inst_Gen, Up_v1, Op_SSE, V_VMOVHPD, Arg_ModRM, {{V, dq}, {H, q}, {M, q}, {0}}, 0},
	{0x16, Inst_Gen, 0, Op_SSE, V_VMOVSHDUP, Arg_ModRM, {{V, x}, {W, x}, {0}, {0}}, 0},
	{0x16, Inst_UD2},
};
OpcodeMap ExPre17[] = {
	{0x17, Inst_Gen, Up_v1, Op_SSE, V_VMOVHPS, Arg_ModRM, {{M, q}, {V, q}, {0}, {0}}, 0},
	{0x17, Inst_Gen, Up_v1, Op_SSE, V_VMOVHPD, Arg_ModRM, {{M, q}, {V, q}, {0}, {0}}, 0},
	{0x17, Inst_UD2},
	{0x17, Inst_UD2},
};
OpcodeMap ExPre1A[] = {
	{0x1A, Inst_Gen, 0, Op_Other, O_BNDLDX, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
	{0x1A, Inst_Gen, 0, Op_Other, O_BNDMOV, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
	{0x1A, Inst_Gen, 0, Op_Other, O_BNDCL, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
	{0x1A, Inst_Gen, 0, Op_Other, O_BNDCU, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
};
OpcodeMap ExPre1B[] = {
	{0x1B, Inst_Gen, 0, Op_Other, O_BNDSTX, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
	{0x1B, Inst_Gen, 0, Op_Other, O_BNDMOV, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
	{0x1B, Inst_Gen, 0, Op_Other, O_BNDMK, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
	{0x1B, Inst_Gen, 0, Op_Other, O_BNDCN, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
};

OpcodeMap ExPre28[] = {
	{0x28, Inst_Gen, 0, Op_SSE, V_VMOVAPS, Arg_ModRM, {{V, ps}, {W, ps}, {0}, {0}}, 0},
	{0x28, Inst_Gen, 0, Op_SSE, V_VMOVAPD, Arg_ModRM, {{V, pd}, {W, pd}, {0}, {0}}, 0},
	{0x28, Inst_UD2},
	{0x28, Inst_UD2},
};
OpcodeMap ExPre29[] = {
	{0x29, Inst_Gen, 0, Op_SSE, V_VMOVAPS, Arg_ModRM, {{W, ps}, {V, ps}, {0}, {0}}, 0},
	{0x29, Inst_Gen, 0, Op_SSE, V_VMOVAPD, Arg_ModRM, {{W, pd}, {V, pd}, {0}, {0}}, 0},
	{0x29, Inst_UD2},
	{0x29, Inst_UD2},
};
OpcodeMap ExPre2A[] = {
	{0x2A, Inst_Gen, 0, Op_SSE, V_CVTPI2PS, Arg_Null, {{V, ps}, {Q, pi}, {0}, {0}}, 0},
	{0x2A, Inst_Gen, 0, Op_SSE, V_CVTPI2PD, Arg_Null, {{V, pd}, {Q, pi}, {0}, {0}}, 0},
	{0x2A, Inst_Gen, 0, Op_SSE, V_VCVTSI2SS, Arg_Null, {{V, ss}, {H, ss}, {E, y}, {0}}, 0},
	{0x2A, Inst_Gen, 0, Op_SSE, V_VCVTSI2SD, Arg_Null, {{V, sd}, {H, sd}, {E, y}, {0}}, 0},
};
OpcodeMap ExPre2B[] = {
	{0x29, Inst_Gen, 0, Op_SSE, V_VMOVNTPS, Arg_ModRM, {{M, ps}, {V, ps}, {0}, {0}}, 0},
	{0x29, Inst_Gen, 0, Op_SSE, V_VMOVNTPD, Arg_ModRM, {{M, pd}, {V, pd}, {0}, {0}}, 0},
	{0x29, Inst_UD2},
	{0x29, Inst_UD2},
};
OpcodeMap ExPre2C[] = {
	{0x2C, Inst_Gen, 0, Op_SSE, V_CVTTPS2PI, Arg_Null, {{P, pi}, {W, ps}, {0}, {0}}, 0},
	{0x2C, Inst_Gen, 0, Op_SSE, V_CVTTPD2PI, Arg_Null, {{P, pi}, {W, pd}, {0}, {0}}, 0},
	{0x2C, Inst_Gen, 0, Op_SSE, V_VCVTTSS2SI, Arg_Null, {{G, y}, {W, ss}, {0}, {0}}, 0},
	{0x2C, Inst_Gen, 0, Op_SSE, V_VCVTTSD2SI, Arg_Null, {{G, y}, {W, sd}, {0}, {0}}, 0},
};
OpcodeMap ExPre2D[] = {
	{0x2D, Inst_Gen, 0, Op_SSE, V_CVTPS2PI, Arg_Null, {{P, pi}, {W, ps}, {0}, {0}}, 0},
	{0x2D, Inst_Gen, 0, Op_SSE, V_CVTPD2PI, Arg_Null, {{Q, pi}, {W, pd}, {0}, {0}}, 0},
	{0x2D, Inst_Gen, 0, Op_SSE, V_VCVTSS2SI, Arg_Null, {{G, y}, {W, ss}, {0}, {0}}, 0},
	{0x2D, Inst_Gen, 0, Op_SSE, V_VCVTSD2SI, Arg_Null, {{G, y}, {W, sd}, {0}, {0}}, 0},
};
OpcodeMap ExPre2E[] = {
	{0x2E, Inst_Gen, 0, Op_SSE, V_VUCOMISS, Arg_ModRM, {{V, ss}, {W, ss}, {0}, {0}}, 0},
	{0x2E, Inst_Gen, 0, Op_SSE, V_VUCOMISD, Arg_ModRM, {{V, sd}, {W, sd}, {0}, {0}}, 0},
	{0x2E, Inst_UD2},
	{0x2E, Inst_UD2},
};
OpcodeMap ExPre2F[] = {
	{0x2F, Inst_Gen, 0, Op_SSE, V_VCOMISS, Arg_ModRM, {{V, ss}, {W, ss}, {0}, {0}}, 0},
	{0x2F, Inst_Gen, 0, Op_SSE, V_VCOMISD, Arg_ModRM, {{V, sd}, {W, sd}, {0}, {0}}, 0},
	{0x2F, Inst_UD2},
	{0x2F, Inst_UD2},
};

OpcodeMap ExPre50[] = {
	{0x50, Inst_Gen, 0, Op_SSE, V_VMOVMSKPS, Arg_ModRM, {{G, y}, {U, ps}, {0}, {0}}, 0},
	{0x50, Inst_Gen, 0, Op_SSE, V_VMOVMSKPD, Arg_ModRM, {{G, y}, {U, pd}, {0}, {0}}, 0},
	{0x50, Inst_UD2},
	{0x50, Inst_UD2},
};
OpcodeMap ExPre51[] = {
	{0x51, Inst_Gen, 0, Op_SSE, V_VSQRTPS, Arg_ModRM, {{V, ps}, {W, ps}, {0}, {0}}, 0},
	{0x51, Inst_Gen, 0, Op_SSE, V_VSQRTPD, Arg_ModRM, {{V, pd}, {W, pd}, {0}, {0}}, 0},
	{0x51, Inst_Gen, 0, Op_SSE, V_VSQRTSS, Arg_ModRM, {{V, ss}, {H, ss}, {W, ss}, {0}}, 0},
	{0x51, Inst_Gen, 0, Op_SSE, V_VSQRTSD, Arg_ModRM, {{V, sd}, {H, sd}, {W, sd}, {0}}, 0},
};
OpcodeMap ExPre52[] = {
	{0x52, Inst_Gen, 0, Op_SSE, V_VRSQRTPS, Arg_ModRM, {{V, ps}, {W, ps}, {0}, {0}}, 0},
	{0x52, Inst_UD2},
	{0x52, Inst_Gen, 0, Op_SSE, V_VRSQRTSS, Arg_ModRM, {{V, ss}, {H, ss}, {W, ss}, {0}}, 0},
	{0x52, Inst_UD2},
};
OpcodeMap ExPre53[] = {
	{0x53, Inst_Gen, 0, Op_SSE, V_VRCPPS, Arg_ModRM, {{V, ps}, {W, ps}, {0}, {0}}, 0},
	{0x53, Inst_UD2},
	{0x53, Inst_Gen, 0, Op_SSE, V_VRCPSS, Arg_ModRM, {{V, ss}, {H, ss}, {W, ss}, {0}}, 0},
	{0x53, Inst_UD2},
};
OpcodeMap ExPre54[] = {
	{0x54, Inst_Gen, 0, Op_SSE, V_VANDPS, Arg_ModRM, {{V, ps}, {H, ps}, {W, ps}, {0}}, 0},
	{0x54, Inst_Gen, 0, Op_SSE, V_VANDPD, Arg_ModRM, {{V, pd}, {H, pd}, {W, pd}, {0}}, 0},
	{0x54, Inst_UD2},
	{0x54, Inst_UD2},
};
OpcodeMap ExPre55[] = {
	{0x55, Inst_Gen, 0, Op_SSE, V_VANDNPS, Arg_ModRM, {{V, ps}, {H, ps}, {W, ps}, {0}}, 0},
	{0x55, Inst_Gen, 0, Op_SSE, V_VANDNPD, Arg_ModRM, {{V, pd}, {H, pd}, {W, pd}, {0}}, 0},
	{0x55, Inst_UD2},
	{0x55, Inst_UD2},
};
OpcodeMap ExPre56[] = {
	{0x56, Inst_Gen, 0, Op_SSE, V_VORPS, Arg_ModRM, {{V, ps}, {H, ps}, {W, ps}, {0}}, 0},
	{0x56, Inst_Gen, 0, Op_SSE, V_VORPD, Arg_ModRM, {{V, pd}, {H, pd}, {W, pd}, {0}}, 0},
	{0x56, Inst_UD2},
	{0x56, Inst_UD2},
};
OpcodeMap ExPre57[] = {
	{0x57, Inst_Gen, 0, Op_SSE, V_VXORPS, Arg_ModRM, {{V, ps}, {H, ps}, {W, ps}, {0}}, 0},
	{0x57, Inst_Gen, 0, Op_SSE, V_VXORPD, Arg_ModRM, {{V, pd}, {H, pd}, {W, pd}, {0}}, 0},
	{0x57, Inst_UD2},
	{0x57, Inst_UD2},
};
OpcodeMap ExPre58[] = {
	{0x58, Inst_Gen, 0, Op_SSE, V_VADDPS, Arg_ModRM, {{V, ps}, {H, ps}, {W, ps}, {0}}, 0},
	{0x58, Inst_Gen, 0, Op_SSE, V_VADDPD, Arg_ModRM, {{V, pd}, {H, pd}, {W, pd}, {0}}, 0},
	{0x58, Inst_Gen, 0, Op_SSE, V_VADDSS, Arg_ModRM, {{V, ss}, {H, ss}, {W, ss}, {0}}, 0},
	{0x58, Inst_Gen, 0, Op_SSE, V_VADDSD, Arg_ModRM, {{V, sd}, {H, sd}, {W, sd}, {0}}, 0},
};
OpcodeMap ExPre59[] = {
	{0x59, Inst_Gen, 0, Op_SSE, V_VMULPS, Arg_ModRM, {{V, ps}, {H, ps}, {W, ps}, {0}}, 0},
	{0x59, Inst_Gen, 0, Op_SSE, V_VMULPD, Arg_ModRM, {{V, pd}, {H, pd}, {W, pd}, {0}}, 0},
	{0x59, Inst_Gen, 0, Op_SSE, V_VMULSS, Arg_ModRM, {{V, ss}, {H, ss}, {W, ss}, {0}}, 0},
	{0x59, Inst_Gen, 0, Op_SSE, V_VMULSD, Arg_ModRM, {{V, sd}, {H, sd}, {W, sd}, {0}}, 0},
};
OpcodeMap ExPre5A[] = {
	{0x5A, Inst_Gen, 0, Op_SSE, V_VCVTPS2PD, Arg_ModRM, {{V, pd}, {W, ps}, {0}, {0}}, 0},
	{0x5A, Inst_Gen, 0, Op_SSE, V_VCVTPD2PS, Arg_ModRM, {{V, ps}, {W, pd}, {0}, {0}}, 0},
	{0x5A, Inst_Gen, 0, Op_SSE, V_VCVTSS2SD, Arg_ModRM, {{V, sd}, {H, x}, {W, ss}, {0}}, 0},
	{0x5A, Inst_Gen, 0, Op_SSE, V_VCVTSD2SS, Arg_ModRM, {{V, ss}, {H, x}, {W, sd}, {0}}, 0},
};
OpcodeMap ExPre5B[] = {
	{0x5B, Inst_Gen, 0, Op_SSE, V_VCVTDQ2PS, Arg_ModRM, {{V, ps}, {W, dq}, {0}, {0}}, 0},
	{0x5B, Inst_Gen, 0, Op_SSE, V_VCVTPS2DQ, Arg_ModRM, {{V, dq}, {W, ps}, {0}, {0}}, 0},
	{0x5B, Inst_Gen, 0, Op_SSE, V_VCVTTPS2DQ, Arg_ModRM, {{V, dq}, {W, ps}, {0}, {0}}, 0},
	{0x5B, Inst_UD2},
};
OpcodeMap ExPre5C[] = {
	{0x5C, Inst_Gen, 0, Op_SSE, V_VSUBPS, Arg_ModRM, {{V, ps}, {H, ps}, {W, ps}, {0}}, 0},
	{0x5C, Inst_Gen, 0, Op_SSE, V_VSUBPD, Arg_ModRM, {{V, pd}, {H, pd}, {W, pd}, {0}}, 0},
	{0x5C, Inst_Gen, 0, Op_SSE, V_VSUBSS, Arg_ModRM, {{V, ss}, {H, ss}, {W, ss}, {0}}, 0},
	{0x5C, Inst_Gen, 0, Op_SSE, V_VSUBSD, Arg_ModRM, {{V, sd}, {H, sd}, {W, sd}, {0}}, 0},
};
OpcodeMap ExPre5D[] = {
	{0x5D, Inst_Gen, 0, Op_SSE, V_VMINPS, Arg_ModRM, {{V, ps}, {H, ps}, {W, ps}, {0}}, 0},
	{0x5D, Inst_Gen, 0, Op_SSE, V_VMINPD, Arg_ModRM, {{V, pd}, {H, pd}, {W, pd}, {0}}, 0},
	{0x5D, Inst_Gen, 0, Op_SSE, V_VMINSS, Arg_ModRM, {{V, ss}, {H, ss}, {W, ss}, {0}}, 0},
	{0x5D, Inst_Gen, 0, Op_SSE, V_VMINSD, Arg_ModRM, {{V, sd}, {H, sd}, {W, sd}, {0}}, 0},
};
OpcodeMap ExPre5E[] = {
	{0x5E, Inst_Gen, 0, Op_SSE, V_VDIVPS, Arg_ModRM, {{V, ps}, {H, ps}, {W, ps}, {0}}, 0},
	{0x5E, Inst_Gen, 0, Op_SSE, V_VDIVPD, Arg_ModRM, {{V, pd}, {H, pd}, {W, pd}, {0}}, 0},
	{0x5E, Inst_Gen, 0, Op_SSE, V_VDIVSS, Arg_ModRM, {{V, ss}, {H, ss}, {W, ss}, {0}}, 0},
	{0x5E, Inst_Gen, 0, Op_SSE, V_VDIVSD, Arg_ModRM, {{V, sd}, {H, sd}, {W, sd}, {0}}, 0},
};
OpcodeMap ExPre5F[] = {
	{0x5F, Inst_Gen, 0, Op_SSE, V_VMAXPS, Arg_ModRM, {{V, ps}, {H, ps}, {W, ps}, {0}}, 0},
	{0x5F, Inst_Gen, 0, Op_SSE, V_VMAXPD, Arg_ModRM, {{V, pd}, {H, pd}, {W, pd}, {0}}, 0},
	{0x5F, Inst_Gen, 0, Op_SSE, V_VMAXSS, Arg_ModRM, {{V, ss}, {H, ss}, {W, ss}, {0}}, 0},
	{0x5F, Inst_Gen, 0, Op_SSE, V_VMAXSD, Arg_ModRM, {{V, sd}, {H, sd}, {W, sd}, {0}}, 0},
};

OpcodeMap ExPre60[] = {
	{0x60, Inst_Gen, 0, Op_SSE, V_PUNPCKLBW, Arg_ModRM, {{P, q}, {Q, d}, {0}, {0}}, 0},
	{0x60, Inst_Gen, 0, Op_SSE, V_VPUNPCKLBW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x60, Inst_UD2},
	{0x60, Inst_UD2},
};
OpcodeMap ExPre61[] = {
	{0x61, Inst_Gen, 0, Op_SSE, V_PUNPCKLWD, Arg_ModRM, {{P, q}, {Q, d}, {0}, {0}}, 0},
	{0x61, Inst_Gen, 0, Op_SSE, V_VPUNPCKLWD, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x61, Inst_UD2},
	{0x61, Inst_UD2},
};
OpcodeMap ExPre62[] = {
	{0x62, Inst_Gen, 0, Op_SSE, V_PUNPCKLDQ, Arg_ModRM, {{P, q}, {Q, d}, {0}, {0}}, 0},
	{0x62, Inst_Gen, 0, Op_SSE, V_VPUNPCKLDQ, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x62, Inst_UD2},
	{0x62, Inst_UD2},
};
OpcodeMap ExPre63[] = {
	{0x63, Inst_Gen, 0, Op_SSE, V_PACKSSWB, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0x63, Inst_Gen, 0, Op_SSE, V_VPACKSSWB, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x63, Inst_UD2},
	{0x63, Inst_UD2},
};
OpcodeMap ExPre64[] = {
	{0x64, Inst_Gen, 0, Op_SSE, V_PCMPGTB, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0x64, Inst_Gen, 0, Op_SSE, V_VPCMPGTB, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x64, Inst_UD2},
	{0x64, Inst_UD2},
};
OpcodeMap ExPre65[] = {
	{0x65, Inst_Gen, 0, Op_SSE, V_PCMPGTW, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0x65, Inst_Gen, 0, Op_SSE, V_VPCMPGTW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x65, Inst_UD2},
	{0x65, Inst_UD2},
};
OpcodeMap ExPre66[] = {
	{0x66, Inst_Gen, 0, Op_SSE, V_PCMPGTD, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0x66, Inst_Gen, 0, Op_SSE, V_VPCMPGTD, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x66, Inst_UD2},
	{0x66, Inst_UD2},
};
OpcodeMap ExPre67[] = {
	{0x67, Inst_Gen, 0, Op_SSE, V_PACKUSWB, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0x67, Inst_Gen, 0, Op_SSE, V_VPACKUSWB, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x67, Inst_UD2},
	{0x67, Inst_UD2},
};
OpcodeMap ExPre68[] = {
	{0x68, Inst_Gen, 0, Op_SSE, V_PUNPCKHBW, Arg_ModRM, {{P, q}, {Q, d}, {0}, {0}}, 0},
	{0x68, Inst_Gen, 0, Op_SSE, V_VPUNPCKHBW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x68, Inst_UD2},
	{0x68, Inst_UD2},
};
OpcodeMap ExPre69[] = {
	{0x69, Inst_Gen, 0, Op_SSE, V_PUNPCKHWD, Arg_ModRM, {{P, q}, {Q, d}, {0}, {0}}, 0},
	{0x69, Inst_Gen, 0, Op_SSE, V_VPUNPCKHWD, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x69, Inst_UD2},
	{0x69, Inst_UD2},
};
OpcodeMap ExPre6A[] = {
	{0x6A, Inst_Gen, 0, Op_SSE, V_PUNPCKHDQ, Arg_ModRM, {{P, q}, {Q, d}, {0}, {0}}, 0},
	{0x6A, Inst_Gen, 0, Op_SSE, V_VPUNPCKHDQ, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x6A, Inst_UD2},
	{0x6A, Inst_UD2},
};
OpcodeMap ExPre6B[] = {
	{0x6B, Inst_Gen, 0, Op_SSE, V_PACKSSDW, Arg_ModRM, {{P, q}, {Q, d}, {0}, {0}}, 0},
	{0x6B, Inst_Gen, 0, Op_SSE, V_VPACKSSDW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x6B, Inst_UD2},
	{0x6B, Inst_UD2},
};
OpcodeMap ExPre6C[] = {
	{0x6C, Inst_UD2},
	{0x6C, Inst_Gen, 0, Op_SSE, V_VPUNPCKLQDQ, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x6C, Inst_UD2},
	{0x6C, Inst_UD2},
};
OpcodeMap ExPre6D[] = {
	{0x6D, Inst_UD2},
	{0x6D, Inst_Gen, 0, Op_SSE, V_VPUNPCKHQDQ, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x6D, Inst_UD2},
	{0x6D, Inst_UD2},
};
OpcodeMap ExPre6E[] = {
	{0x6E, Inst_Gen, 0, Op_SSE, V_MOVQ, Arg_ModRM, {{P, d}, {E, y}, {0}, {0}}, 0},
	{0x6E, Inst_Gen, 0, Op_SSE, V_VMOVQ, Arg_ModRM, {{V, y}, {E, y}, {0}, {0}}, 0},
	{0x6E, Inst_UD2},
	{0x6E, Inst_UD2},
};
OpcodeMap ExPre6F[] = {
	{0x6F, Inst_Gen, 0, Op_SSE, V_MOVQ, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0x6F, Inst_Gen, 0, Op_SSE, V_VMOVDQA, Arg_ModRM, {{V, x}, {W, x}, {0}, {0}}, 0},
	{0x6F, Inst_Gen, 0, Op_SSE, V_VMOVDQU, Arg_ModRM, {{V, x}, {W, x}, {0}, {0}}, 0},
	{0x6F, Inst_UD2},
};

OpcodeMap ExPre70[] = {
	{0x70, Inst_Gen, 0, Op_SSE, V_PSHUFW, Arg_ModRM, {{P, q}, {Q, q}, {I, b}, {0}}, 0},
	{0x70, Inst_Gen, 0, Op_SSE, V_VPSHUFD, Arg_ModRM, {{V, x}, {W, x}, {I, b}, {0}}, 0},
	{0x70, Inst_Gen, 0, Op_SSE, V_VPSHUFHW, Arg_ModRM, {{V, x}, {W, x}, {I, b}, {0}}, 0},
	{0x70, Inst_Gen, 0, Op_SSE, V_VPSHUFLW, Arg_ModRM, {{V, x}, {W, x}, {I, b}, {0}}, 0},
};
OpcodeMap ExPre74[] = {
	{0x74, Inst_Gen, 0, Op_SSE, V_PCMPEQB, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0x74, Inst_Gen, 0, Op_SSE, V_VPCMPEQB, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x74, Inst_UD2},
	{0x74, Inst_UD2},
};
OpcodeMap ExPre75[] = {
	{0x75, Inst_Gen, 0, Op_SSE, V_PCMPEQW, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0x75, Inst_Gen, 0, Op_SSE, V_VPCMPEQW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x75, Inst_UD2},
	{0x75, Inst_UD2},
};
OpcodeMap ExPre76[] = {
	{0x76, Inst_Gen, 0, Op_SSE, V_PCMPEQD, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0x76, Inst_Gen, 0, Op_SSE, V_VPCMPEQD, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0x76, Inst_UD2},
	{0x76, Inst_UD2},
};
OpcodeMap ExPre77[] = {
	{0x77, Inst_Gen, 0, Op_SSE, V_EMMS, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
	{0x77, Inst_UD2},
	{0x77, Inst_UD2},
	{0x77, Inst_UD2},
};
OpcodeMap ExPre7C[] = {
	{0x7C, Inst_UD2},
	{0x7C, Inst_Gen, 0, Op_SSE, V_VHADDPD, Arg_ModRM, {{V, pd}, {H, pd}, {W, pd}, {0}}, 0},
	{0x7C, Inst_UD2},
	{0x7C, Inst_Gen, 0, Op_SSE, V_VHADDPS, Arg_ModRM, {{V, ps}, {H, ps}, {W, ps}, {0}}, 0},
};
OpcodeMap ExPre7D[] = {
	{0x7D, Inst_UD2},
	{0x7D, Inst_Gen, 0, Op_SSE, V_VHSUBPD, Arg_ModRM, {{V, pd}, {H, pd}, {W, pd}, {0}}, 0},
	{0x7D, Inst_UD2},
	{0x7D, Inst_Gen, 0, Op_SSE, V_VHSUBPS, Arg_ModRM, {{V, ps}, {H, ps}, {W, ps}, {0}}, 0},
};
OpcodeMap ExPre7E[] = {
	{0x7E, Inst_Gen, 0, Op_SSE, V_MOVQ, Arg_ModRM, {{E, y}, {P, d}, {0}, {0}}, 0},
	{0x7E, Inst_Gen, 0, Op_SSE, V_VMOVQ, Arg_ModRM, {{E, y}, {V, y}, {0}, {0}}, 0},
	{0x7E, Inst_Gen, 0, Op_SSE, V_VMOVQ, Arg_ModRM, {{V, q}, {W, q}, {0}, {0}}, 0},
	{0x7E, Inst_UD2},
};
OpcodeMap ExPre7F[] = {
	{0x7F, Inst_Gen, 0, Op_SSE, V_MOVQ, Arg_ModRM, {{Q, q}, {P, q}, {0}, {0}}, 0},
	{0x7F, Inst_Gen, 0, Op_SSE, V_VMOVDQA, Arg_ModRM, {{W, x}, {V, x}, {0}, {0}}, 0},
	{0x7F, Inst_Gen, 0, Op_SSE, V_VMOVDQU, Arg_ModRM, {{W, x}, {V, x}, {0}, {0}}, 0},
	{0x7F, Inst_UD2},
};

OpcodeMap ExPreB8[] = {
	{0xB8, Inst_Gen, 0, Op_Sys, S_JMPE, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
	{0xB8, Inst_UD2},
	{0xB8, Inst_Gen, 0, Op_Sys, S_POPCNT, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0xB8, Inst_UD2},
};
OpcodeMap ExPreBB[] = {
	{0xBB, Inst_Gen, 0, Op_Calc, C_BTC, Arg_ModRM, {{E, v}, {G, v}, {0}, {0}}, 0},
	{0xBB, Inst_UD2},
	{0xBB, Inst_UD2},
	{0xBB, Inst_UD2},
};
OpcodeMap ExPreBC[] = {
	{0xBC, Inst_Gen, 0, Op_Calc, C_BSF, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0xBC, Inst_UD2},
	{0xBC, Inst_Gen, 0, Op_Calc, C_TZCNT, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0xBC, Inst_UD2},
};
OpcodeMap ExPreBD[] = {
	{0xBD, Inst_Gen, 0, Op_Calc, C_BSR, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0xBD, Inst_UD2},
	{0xBD, Inst_Gen, 0, Op_Calc, C_LZCNT, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0xBD, Inst_UD2},
};

OpcodeMap ExPreC0[] = {
	{0xC0, Inst_Gen, 0, Op_Calc, C_XADD, Arg_ModRM, {{E, b}, {G, b}, {0}, {0}}, 0},
	{0xC0, Inst_UD2},
	{0xC0, Inst_UD2},
	{0xC0, Inst_UD2},
};
OpcodeMap ExPreC1[] = {
	{0xC1, Inst_Gen, 0, Op_Calc, C_XADD, Arg_ModRM, {{E, v}, {G, v}, {0}, {0}}, 0},
	{0xC1, Inst_UD2},
	{0xC1, Inst_UD2},
	{0xC1, Inst_UD2},
};
OpcodeMap ExPreC2[] = {
	{0xC2, Inst_Gen, 0, Op_SSE, V_VCMPPS, Arg_ModRM, {{V, ps}, {H, ps}, {W, ps}, {I, b}}, 0},
	{0xC2, Inst_Gen, 0, Op_SSE, V_VCMPPD, Arg_ModRM, {{V, pd}, {H, pd}, {W, pd}, {I, b}}, 0},
	{0xC2, Inst_Gen, 0, Op_SSE, V_VCMPSS, Arg_ModRM, {{V, ss}, {H, ss}, {W, ss}, {I, b}}, 0},
	{0xC2, Inst_Gen, 0, Op_SSE, V_VCMPSD, Arg_ModRM, {{V, sd}, {H, sd}, {W, sd}, {I, b}}, 0},
};
OpcodeMap ExPreC3[] = {
	{0xC3, Inst_Gen, 0, Op_Data, D_MOVNTI, Arg_ModRM, {{M, y}, {G, y}, {0}, {0}}, 0},
	{0xC3, Inst_UD2},
	{0xC3, Inst_UD2},
	{0xC3, Inst_UD2},
};
OpcodeMap ExPreC4[] = {
	{0xC4, Inst_Gen, 0, Op_SSE, V_PINSRW, Arg_ModRM, {{P, q}, {M, w}, {I, b}, {0}}, 0},
	{0xC4, Inst_Gen, 0, Op_SSE, V_VPINSRW, Arg_ModRM, {{V, dq}, {H, dq}, {M, w}, {I, b}}, 0},
	{0xC4, Inst_UD2},
	{0xC4, Inst_UD2},
};
OpcodeMap ExPreC5[] = {
	{0xC5, Inst_Gen, 0, Op_SSE, V_PEXTRW, Arg_ModRM, {{G, d}, {N, q}, {I, b}, {0}}, 0},
	{0xC5, Inst_Gen, 0, Op_SSE, V_VPEXTRW, Arg_ModRM, {{G, d}, {U, dq}, {I, b}, {0}}, 0},
	{0xC5, Inst_UD2},
	{0xC5, Inst_UD2},
};
OpcodeMap ExPreC6[] = {
	{0xC6, Inst_Gen, 0, Op_SSE, V_VSHUFPS, Arg_ModRM, {{V, ps}, {H, ps}, {W, ps}, {I, b}}, 0},
	{0xC6, Inst_Gen, 0, Op_SSE, V_VSHUFPD, Arg_ModRM, {{V, pd}, {H, pd}, {W, pd}, {I, b}}, 0},
	{0xC6, Inst_UD2},
	{0xC6, Inst_UD2},
};

OpcodeMap ExPreD0[] = {
	{0xD0, Inst_UD2},
	{0xD0, Inst_Gen, 0, Op_SSE, V_VADDSUBPD, Arg_ModRM, {{V, pd}, {H, pd}, {W, pd}, {0}}, 0},
	{0xD0, Inst_UD2},
	{0xD0, Inst_Gen, 0, Op_SSE, V_VADDSUBPS, Arg_ModRM, {{V, ps}, {H, ps}, {W, ps}, {0}}, 0},
};
OpcodeMap ExPreD1[] = {
	{0xD1, Inst_Gen, 0, Op_SSE, V_PSRLW, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xD1, Inst_Gen, 0, Op_SSE, V_VPSRLW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xD1, Inst_UD2},
	{0xD1, Inst_UD2},
};
OpcodeMap ExPreD2[] = {
	{0xD2, Inst_Gen, 0, Op_SSE, V_PSRLD, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xD2, Inst_Gen, 0, Op_SSE, V_VPSRLD, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xD2, Inst_UD2},
	{0xD2, Inst_UD2},
};
OpcodeMap ExPreD3[] = {
	{0xD3, Inst_Gen, 0, Op_SSE, V_PSRLQ, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xD3, Inst_Gen, 0, Op_SSE, V_VPSRLQ, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xD3, Inst_UD2},
	{0xD3, Inst_UD2},
};
OpcodeMap ExPreD4[] = {
	{0xD4, Inst_Gen, 0, Op_SSE, V_PADDQ, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xD4, Inst_Gen, 0, Op_SSE, V_VPADDQ, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xD4, Inst_UD2},
	{0xD4, Inst_UD2},
};
OpcodeMap ExPreD5[] = {
	{0xD5, Inst_Gen, 0, Op_SSE, V_PMULLW, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xD5, Inst_Gen, 0, Op_SSE, V_VPMULLW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xD5, Inst_UD2},
	{0xD5, Inst_UD2},
};
OpcodeMap ExPreD6[] = {
	{0xD6, Inst_UD2},
	{0xD6, Inst_Gen, 0, Op_SSE, V_VMOVQ, Arg_ModRM, {{W, q}, {V, q}, {0}, {0}}, 0},
	{0xD6, Inst_Gen, 0, Op_SSE, V_MOVQ2DQ, Arg_ModRM, {{V, dq}, {N, q}, {0}, {0}}, 0},
	{0xD6, Inst_Gen, 0, Op_SSE, V_MOVDQ2Q, Arg_ModRM, {{P, q}, {U, q}, {0}, {0}}, 0},
};
OpcodeMap ExPreD7[] = {
	{0xD7, Inst_Gen, 0, Op_SSE, V_PMOVMSKB, Arg_ModRM, {{G, d}, {U, x}, {0}, {0}}, 0},
	{0xD7, Inst_Gen, 0, Op_SSE, V_VPMOVMSKB, Arg_ModRM, {{G, d}, {N, q}, {0}, {0}}, 0},
	{0xD7, Inst_UD2},
	{0xD7, Inst_UD2},
};

OpcodeMap ExPreD8[] = {
	{0xD8, Inst_Gen, 0, Op_SSE, V_PSUBUSB, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xD8, Inst_Gen, 0, Op_SSE, V_VPSUBUSB, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xD8, Inst_UD2},
	{0xD8, Inst_UD2},
};
OpcodeMap ExPreD9[] = {
	{0xD9, Inst_Gen, 0, Op_SSE, V_PSUBUSW, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xD9, Inst_Gen, 0, Op_SSE, V_VPSUBUSW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xD9, Inst_UD2},
	{0xD9, Inst_UD2},
};
OpcodeMap ExPreDA[] = {
	{0xDA, Inst_Gen, 0, Op_SSE, V_PMINUB, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xDA, Inst_Gen, 0, Op_SSE, V_VPMINUB, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xDA, Inst_UD2},
	{0xDA, Inst_UD2},
};
OpcodeMap ExPreDB[] = {
	{0xDB, Inst_Gen, 0, Op_SSE, V_PAND, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xDB, Inst_Gen, 0, Op_SSE, V_VPAND, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xDB, Inst_UD2},
	{0xDB, Inst_UD2},
};
OpcodeMap ExPreDC[] = {
	{0xDC, Inst_Gen, 0, Op_SSE, V_PADDUSB, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xDC, Inst_Gen, 0, Op_SSE, V_VPADDUSB, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xDC, Inst_UD2},
	{0xDC, Inst_UD2},
};
OpcodeMap ExPreDD[] = {
	{0xDD, Inst_Gen, 0, Op_SSE, V_PADDUSW, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xDD, Inst_Gen, 0, Op_SSE, V_VPADDUSW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xDD, Inst_UD2},
	{0xDD, Inst_UD2},
};
OpcodeMap ExPreDE[] = {
	{0xDE, Inst_Gen, 0, Op_SSE, V_PMAXUB, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xDE, Inst_Gen, 0, Op_SSE, V_VPMAXUB, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xDE, Inst_UD2},
	{0xDE, Inst_UD2},
};
OpcodeMap ExPreDF[] = {
	{0xDF, Inst_Gen, 0, Op_SSE, V_PANDN, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xDF, Inst_Gen, 0, Op_SSE, V_VPANDN, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xDF, Inst_UD2},
	{0xDF, Inst_UD2},
};

OpcodeMap ExPreE0[] = {
	{0xE0, Inst_Gen, 0, Op_SSE, V_PAVGB, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xE0, Inst_Gen, 0, Op_SSE, V_VPAVGB, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xE0, Inst_UD2},
	{0xE0, Inst_UD2},
};
OpcodeMap ExPreE1[] = {
	{0xE1, Inst_Gen, 0, Op_SSE, V_PSRAW, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xE1, Inst_Gen, 0, Op_SSE, V_VPSRAW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xE1, Inst_UD2},
	{0xE1, Inst_UD2},
};
OpcodeMap ExPreE2[] = {
	{0xE2, Inst_Gen, 0, Op_SSE, V_PSRAD, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xE2, Inst_Gen, 0, Op_SSE, V_VPSRAD, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xE2, Inst_UD2},
	{0xE2, Inst_UD2},
};
OpcodeMap ExPreE3[] = {
	{0xE3, Inst_Gen, 0, Op_SSE, V_PAVGW, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xE3, Inst_Gen, 0, Op_SSE, V_VPAVGW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xE3, Inst_UD2},
	{0xE3, Inst_UD2},
};
OpcodeMap ExPreE4[] = {
	{0xE4, Inst_Gen, 0, Op_SSE, V_PMULHUW, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xE4, Inst_Gen, 0, Op_SSE, V_VPMULHUW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xE4, Inst_UD2},
	{0xE4, Inst_UD2},
};
OpcodeMap ExPreE5[] = {
	{0xE5, Inst_Gen, 0, Op_SSE, V_PMULHW, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xE5, Inst_Gen, 0, Op_SSE, V_VPMULHW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xE5, Inst_UD2},
	{0xE5, Inst_UD2},
};
OpcodeMap ExPreE6[] = {
	{0xE6, Inst_UD2},
	{0xE6, Inst_Gen, 0, Op_SSE, V_VCVTTPD2DQ, Arg_ModRM, {{V, x}, {W, pd}, {0}, {0}}, 0},
	{0xE6, Inst_Gen, 0, Op_SSE, V_VCVTDQ2PD, Arg_ModRM, {{V, x}, {W, pd}, {0}, {0}}, 0},
	{0xE6, Inst_Gen, 0, Op_SSE, V_VCVTPD2DQ, Arg_ModRM, {{V, x}, {W, pd}, {0}, {0}}, 0},
};
OpcodeMap ExPreE7[] = {
	{0xE7, Inst_Gen, 0, Op_SSE, V_MOVNTQ, Arg_ModRM, {{M, q}, {P, q}, {0}, {0}}, 0},
	{0xE7, Inst_Gen, 0, Op_SSE, V_VMOVNTDQ, Arg_ModRM, {{M, x}, {V, x}, {0}, {0}}, 0},
	{0xE7, Inst_UD2},
	{0xE7, Inst_UD2},
};
OpcodeMap ExPreE8[] = {
	{0xE8, Inst_Gen, 0, Op_SSE, V_PSUBSB, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xE8, Inst_Gen, 0, Op_SSE, V_VPSUBSB, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xE8, Inst_UD2},
	{0xE8, Inst_UD2},
};
OpcodeMap ExPreE9[] = {
	{0xE9, Inst_Gen, 0, Op_SSE, V_PSUBSW, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xE9, Inst_Gen, 0, Op_SSE, V_VPSUBSW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xE9, Inst_UD2},
	{0xE9, Inst_UD2},
};
OpcodeMap ExPreEA[] = {
	{0xEA, Inst_Gen, 0, Op_SSE, V_PMINSW, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xEA, Inst_Gen, 0, Op_SSE, V_VPMINSW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xEA, Inst_UD2},
	{0xEA, Inst_UD2},
};
OpcodeMap ExPreEB[] = {
	{0xEB, Inst_Gen, 0, Op_SSE, V_POR, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xEB, Inst_Gen, 0, Op_SSE, V_VPOR, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xEB, Inst_UD2},
	{0xEB, Inst_UD2},
};
OpcodeMap ExPreEC[] = {
	{0xEC, Inst_Gen, 0, Op_SSE, V_PADDSB, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xEC, Inst_Gen, 0, Op_SSE, V_VPADDSB, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xEC, Inst_UD2},
	{0xEC, Inst_UD2},
};
OpcodeMap ExPreED[] = {
	{0xED, Inst_Gen, 0, Op_SSE, V_PADDSW, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xED, Inst_Gen, 0, Op_SSE, V_VPADDSW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xED, Inst_UD2},
	{0xED, Inst_UD2},
};
OpcodeMap ExPreEE[] = {
	{0xEE, Inst_Gen, 0, Op_SSE, V_PMAXSW, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xEE, Inst_Gen, 0, Op_SSE, V_VPMAXSW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xEE, Inst_UD2},
	{0xEE, Inst_UD2},
};
OpcodeMap ExPreEF[] = {
	{0xEF, Inst_Gen, 0, Op_SSE, V_PXOR, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xEF, Inst_Gen, 0, Op_SSE, V_VPXOR, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xEF, Inst_UD2},
	{0xEF, Inst_UD2},
};

OpcodeMap ExPreF0[] = {
	{0xF0, Inst_UD2},
	{0xF0, Inst_UD2},
	{0xF0, Inst_Gen, 0, Op_SSE, V_VLDDQU, Arg_ModRM, {{V, x}, {M, x}, {0}, {0}}, 0},
	{0xF0, Inst_UD2},
};
OpcodeMap ExPreF1[] = {
	{0xF1, Inst_Gen, 0, Op_SSE, V_PSLLW, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xF1, Inst_Gen, 0, Op_SSE, V_VPSLLW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xF1, Inst_UD2},
	{0xF1, Inst_UD2},
};
OpcodeMap ExPreF2[] = {
	{0xF2, Inst_Gen, 0, Op_SSE, V_PSLLD, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xF2, Inst_Gen, 0, Op_SSE, V_VPSLLD, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xF2, Inst_UD2},
	{0xF2, Inst_UD2},
};
OpcodeMap ExPreF3[] = {
	{0xF3, Inst_Gen, 0, Op_SSE, V_PSLLQ, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xF3, Inst_Gen, 0, Op_SSE, V_VPSLLQ, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xF3, Inst_UD2},
	{0xF3, Inst_UD2},
};
OpcodeMap ExPreF4[] = {
	{0xF4, Inst_Gen, 0, Op_SSE, V_PMULUDQ, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xF4, Inst_Gen, 0, Op_SSE, V_VPMULUDQ, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xF4, Inst_UD2},
	{0xF4, Inst_UD2},
};
OpcodeMap ExPreF5[] = {
	{0xF5, Inst_Gen, 0, Op_SSE, V_PMADDWD, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xF5, Inst_Gen, 0, Op_SSE, V_VPMADDWD, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xF5, Inst_UD2},
	{0xF5, Inst_UD2},
};
OpcodeMap ExPreF6[] = {
	{0xF6, Inst_Gen, 0, Op_SSE, V_PSADBW, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xF6, Inst_Gen, 0, Op_SSE, V_VPSADBW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xF6, Inst_UD2},
	{0xF6, Inst_UD2},
};
OpcodeMap ExPreF7[] = {
	{0xF7, Inst_Gen, 0, Op_SSE, V_MASKMOVQ, Arg_ModRM, {{P, q}, {N, q}, {0}, {0}}, 0},
	{0xF7, Inst_Gen, 0, Op_SSE, V_VMASKMOVDQU, Arg_ModRM, {{V, dq}, {U, dq}, {0}, {0}}, 0},
	{0xF7, Inst_UD2},
	{0xF7, Inst_UD2},
};

OpcodeMap ExPreF8[] = {
	{0xF8, Inst_Gen, 0, Op_SSE, V_PSUBB, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xF8, Inst_Gen, 0, Op_SSE, V_VPSUBB, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xF8, Inst_UD2},
	{0xF8, Inst_UD2},
};
OpcodeMap ExPreF9[] = {
	{0xF9, Inst_Gen, 0, Op_SSE, V_PSUBW, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xF9, Inst_Gen, 0, Op_SSE, V_VPSUBW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xF9, Inst_UD2},
	{0xF9, Inst_UD2},
};
OpcodeMap ExPreFA[] = {
	{0xFA, Inst_Gen, 0, Op_SSE, V_PSUBD, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xFA, Inst_Gen, 0, Op_SSE, V_VPSUBD, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xFA, Inst_UD2},
	{0xFA, Inst_UD2},
};
OpcodeMap ExPreFB[] = {
	{0xFB, Inst_Gen, 0, Op_SSE, V_PSUBQ, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xFB, Inst_Gen, 0, Op_SSE, V_VPSUBQ, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xFB, Inst_UD2},
	{0xFB, Inst_UD2},
};
OpcodeMap ExPreFC[] = {
	{0xFC, Inst_Gen, 0, Op_SSE, V_PADDB, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xFC, Inst_Gen, 0, Op_SSE, V_VPADDB, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xFC, Inst_UD2},
	{0xFC, Inst_UD2},
};
OpcodeMap ExPreFD[] = {
	{0xFD, Inst_Gen, 0, Op_SSE, V_PADDW, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xFD, Inst_Gen, 0, Op_SSE, V_VPADDW, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xFD, Inst_UD2},
	{0xFD, Inst_UD2},
};
OpcodeMap ExPreFE[] = {
	{0xFE, Inst_Gen, 0, Op_SSE, V_PADDD, Arg_ModRM, {{P, q}, {Q, q}, {0}, {0}}, 0},
	{0xFE, Inst_Gen, 0, Op_SSE, V_VPADDD, Arg_ModRM, {{V, x}, {H, x}, {W, x}, {0}}, 0},
	{0xFE, Inst_UD2},
	{0xFE, Inst_UD2},
};
/*

 */

OpcodeMap TwoByte[] = {
	{0x00, Inst_Grp, Grp_6, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ReMapGroup6},
	{0x01, Inst_Grp, Grp_7, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ReMapGroup7},
	{0x02, Inst_Gen, 0, Op_Sys, S_LAR, Arg_ModRM, {{G, v}, {E, w}, {0}, {0}}, 0},
	{0x03, Inst_Gen, 0, Op_Sys, S_LSL, Arg_ModRM, {{G, v}, {E, w}, {0}, {0}}, 0},
	{0x04, Inst_UD2},
	{0x05, Inst_O64, Up_o64, Op_Sys, S_SYSCALL, 0, {{0}, {0}, {0}, {0}}, 0},
	{0x06, Inst_Gen, 0, Op_Sys, S_CLTS, 0, {{0}, {0}, {0}, {0}}, 0},
	{0x07, Inst_O64, Up_o64, Op_Sys, S_SYSRET, 0, {{0}, {0}, {0}, {0}}, 0},
	{0x08, Inst_Gen, 0, Op_Sys, S_INVD, 0, {{0}, {0}, {0}, {0}}, 0},
	{0x09, Inst_Gen, 0, Op_Sys, S_WBINVD, 0, {{0}, {0}, {0}, {0}}, 0},
	{0x0A, Inst_UD2},
	{0x0B, Inst_UD2},
	{0x0C, Inst_UD2},
	{0x0D, Inst_Gen, 0, Op_Sys, S_PREFETCHW, Arg_ModRM, {{E, v}, {0}, {0}, {0}}, 0},
	{0x0E, Inst_UD2},
	{0x0F, Inst_UD2},

	{0x10, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre10},
	{0x11, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre11},
	{0x12, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre12},
	{0x13, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre13},
	{0x14, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre14},
	{0x15, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre15},
	{0x16, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre16},
	{0x17, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre17},
	{0x18, Inst_Pre, Grp_16, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ReMapGroup16},
	{0x19, Inst_Gen, 0, Op_Other, O_NOP, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
	{0x1A, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre1A},
	{0x1B, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre1B},
	{0x1C, Inst_Gen, 0, Op_Other, O_NOP, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
	{0x1D, Inst_Gen, 0, Op_Other, O_NOP, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
	{0x1E, Inst_Gen, 0, Op_Other, O_NOP, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
	{0x1F, Inst_Gen, 0, Op_Other, O_NOP, Arg_ModRM, {{E, v}, {0}, {0}, {0}}, 0},

	{0x20, Inst_Gen, 0, Op_Sys, S_MOV, Arg_ModRM, {{R, d}, {C, d}, {0}, {0}}, 0},
	{0x21, Inst_Gen, 0, Op_Sys, S_MOV, Arg_ModRM, {{R, d}, {D, d}, {0}, {0}}, 0},
	{0x22, Inst_Gen, 0, Op_Sys, S_MOV, Arg_ModRM, {{C, d}, {R, d}, {0}, {0}}, 0},
	{0x23, Inst_Gen, 0, Op_Sys, S_MOV, Arg_ModRM, {{D, d}, {R, d}, {0}, {0}}, 0},
	{0x24, Inst_UD2},
	{0x25, Inst_UD2},
	{0x26, Inst_UD2},
	{0x27, Inst_UD2},
	{0x28, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre28},
	{0x29, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre29},
	{0x2A, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre2A},
	{0x2B, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre2B},
	{0x2C, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre2C},
	{0x2D, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre2D},
	{0x2E, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre2E},
	{0x2F, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre2F},

	{0x30, Inst_Gen, 0, Op_Sys, S_WRMSR, 0, {{0}, {0}, {0}, {0}}, 0},
	{0x31, Inst_Gen, 0, Op_Sys, S_RDTSC, 0, {{0}, {0}, {0}, {0}}, 0},
	{0x32, Inst_Gen, 0, Op_Sys, S_RDMSR, 0, {{0}, {0}, {0}, {0}}, 0},
	{0x33, Inst_Gen, 0, Op_Sys, S_RDPMC, 0, {{0}, {0}, {0}, {0}}, 0},
	{0x34, Inst_Gen, 0, Op_Sys, S_SYSENTER, 0, {{0}, {0}, {0}, {0}}, 0},
	{0x35, Inst_Gen, 0, Op_Sys, S_SYSEXIT, 0, {{0}, {0}, {0}, {0}}, 0},
	{0x36, Inst_UD2},
	{0x37, Inst_Gen, 0, Op_Sys, S_GETSEC, 0, {{0}, {0}, {0}, {0}}, 0},
	{0x38, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ThreeByte[0]},
	{0x39, Inst_UD2},
	{0x3A, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ThreeByte[1]},
	{0x3B, Inst_UD2},
	{0x3C, Inst_UD2},
	{0x3D, Inst_UD2},
	{0x3E, Inst_UD2},
	{0x3F, Inst_UD2},

	{0x40, Inst_Gen, 0, Op_Data, D_CMOVO, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0x41, Inst_Gen, 0, Op_Data, D_CMOVNO, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0x42, Inst_Gen, 0, Op_Data, D_CMOVB, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0x43, Inst_Gen, 0, Op_Data, D_CMOVNB, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0x44, Inst_Gen, 0, Op_Data, D_CMOVE, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0x45, Inst_Gen, 0, Op_Data, D_CMOVNE, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0x46, Inst_Gen, 0, Op_Data, D_CMOVNA, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0x47, Inst_Gen, 0, Op_Data, D_CMOVA, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0x48, Inst_Gen, 0, Op_Data, D_CMOVS, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0x49, Inst_Gen, 0, Op_Data, D_CMOVNS, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0x4A, Inst_Gen, 0, Op_Data, D_CMOVP, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0x4B, Inst_Gen, 0, Op_Data, D_CMOVNP, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0x4C, Inst_Gen, 0, Op_Data, D_CMOVL, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0x4D, Inst_Gen, 0, Op_Data, D_CMOVNL, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0x4E, Inst_Gen, 0, Op_Data, D_CMOVNG, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},
	{0x4F, Inst_Gen, 0, Op_Data, D_CMOVG, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},

	{0x50, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre50},
	{0x51, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre51},
	{0x52, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre52},
	{0x53, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre53},
	{0x54, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre54},
	{0x55, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre55},
	{0x56, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre56},
	{0x57, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre57},
	{0x58, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre58},
	{0x59, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre59},
	{0x5A, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre5A},
	{0x5B, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre5B},
	{0x5C, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre5C},
	{0x5D, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre5D},
	{0x5E, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre5E},
	{0x5F, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre5F},

	{0x60, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre60},
	{0x61, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre61},
	{0x62, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre62},
	{0x63, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre63},
	{0x64, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre64},
	{0x65, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre65},
	{0x66, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre66},
	{0x67, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre67},
	{0x68, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre68},
	{0x69, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre69},
	{0x6A, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre6A},
	{0x6B, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre6B},
	{0x6C, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre6C},
	{0x6D, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre6D},
	{0x6E, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre6E},
	{0x6F, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre6F},

	{0x70, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre70},
	{0x71, Inst_Grp, Grp_12, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ReMapGroup12},
	{0x72, Inst_Grp, Grp_13, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ReMapGroup13},
	{0x73, Inst_Grp, Grp_14, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ReMapGroup14},
	{0x74, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre74},
	{0x75, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre75},
	{0x76, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre76},
	{0x77, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre77},
	{0x78, Inst_Gen, 0, Op_Vm, V_VMREAD, Arg_ModRM, {{E, y}, {G, y}, {0}, {0}}, 0},
	{0x79, Inst_Gen, 0, Op_Vm, V_VMWRITE, Arg_ModRM, {{G, y}, {E, y}, {0}, {0}}, 0},
	{0x7A, Inst_UD2},
	{0x7B, Inst_UD2},
	{0x7C, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre7C},
	{0x7D, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre7D},
	{0x7E, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre7E},
	{0x7F, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPre7F},

	{0x80, Inst_Gen, Up_f64, Op_Jcc, J_JO, Arg_NoModRM, {{J, z}, {0}, {0}, {0}}, 0},
	{0x81, Inst_Gen, Up_f64, Op_Jcc, J_JNO, Arg_NoModRM, {{J, z}, {0}, {0}, {0}}, 0},
	{0x82, Inst_Gen, Up_f64, Op_Jcc, J_JC, Arg_NoModRM, {{J, z}, {0}, {0}, {0}}, 0},
	{0x83, Inst_Gen, Up_f64, Op_Jcc, J_JNC, Arg_NoModRM, {{J, z}, {0}, {0}, {0}}, 0},
	{0x84, Inst_Gen, Up_f64, Op_Jcc, J_JE, Arg_NoModRM, {{J, z}, {0}, {0}, {0}}, 0},
	{0x85, Inst_Gen, Up_f64, Op_Jcc, J_JNE, Arg_NoModRM, {{J, z}, {0}, {0}, {0}}, 0},
	{0x86, Inst_Gen, Up_f64, Op_Jcc, J_JNA, Arg_NoModRM, {{J, z}, {0}, {0}, {0}}, 0},
	{0x87, Inst_Gen, Up_f64, Op_Jcc, J_JA, Arg_NoModRM, {{J, z}, {0}, {0}, {0}}, 0},
	{0x88, Inst_Gen, Up_f64, Op_Jcc, J_JS, Arg_NoModRM, {{J, z}, {0}, {0}, {0}}, 0},
	{0x89, Inst_Gen, Up_f64, Op_Jcc, J_JNS, Arg_NoModRM, {{J, z}, {0}, {0}, {0}}, 0},
	{0x8A, Inst_Gen, Up_f64, Op_Jcc, J_JP, Arg_NoModRM, {{J, z}, {0}, {0}, {0}}, 0},
	{0x8B, Inst_Gen, Up_f64, Op_Jcc, J_JNP, Arg_NoModRM, {{J, z}, {0}, {0}, {0}}, 0},
	{0x8C, Inst_Gen, Up_f64, Op_Jcc, J_JL, Arg_NoModRM, {{J, z}, {0}, {0}, {0}}, 0},
	{0x8D, Inst_Gen, Up_f64, Op_Jcc, J_JNL, Arg_NoModRM, {{J, z}, {0}, {0}, {0}}, 0},
	{0x8E, Inst_Gen, Up_f64, Op_Jcc, J_JNG, Arg_NoModRM, {{J, z}, {0}, {0}, {0}}, 0},
	{0x8F, Inst_Gen, Up_f64, Op_Jcc, J_JG, Arg_NoModRM, {{J, z}, {0}, {0}, {0}}, 0},

	{0x90, Inst_Gen, 0, Op_Flags, F_SETO, Arg_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
	{0x91, Inst_Gen, 0, Op_Flags, F_SETNO, Arg_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
	{0x92, Inst_Gen, 0, Op_Flags, F_SETC, Arg_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
	{0x93, Inst_Gen, 0, Op_Flags, F_SETNC, Arg_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
	{0x94, Inst_Gen, 0, Op_Flags, F_SETE, Arg_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
	{0x95, Inst_Gen, 0, Op_Flags, F_SETNE, Arg_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
	{0x96, Inst_Gen, 0, Op_Flags, F_SETNA, Arg_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
	{0x97, Inst_Gen, 0, Op_Flags, F_SETA, Arg_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
	{0x98, Inst_Gen, 0, Op_Flags, F_SETS, Arg_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
	{0x99, Inst_Gen, 0, Op_Flags, F_SETNS, Arg_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
	{0x9A, Inst_Gen, 0, Op_Flags, F_SETP, Arg_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
	{0x9B, Inst_Gen, 0, Op_Flags, F_SETNP, Arg_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
	{0x9C, Inst_Gen, 0, Op_Flags, F_SETL, Arg_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
	{0x9D, Inst_Gen, 0, Op_Flags, F_SETNL, Arg_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
	{0x9E, Inst_Gen, 0, Op_Flags, F_SETNG, Arg_ModRM, {{E, b}, {0}, {0}, {0}}, 0},
	{0x9F, Inst_Gen, 0, Op_Flags, F_SETG, Arg_ModRM, {{E, b}, {0}, {0}, {0}}, 0},

	{0xA0, Inst_Gen, Up_d64, Op_Stack, K_PUSH, Arg_Seg, {{S_FS}, {0}, {0}, {0}}, 0},
	{0xA1, Inst_Gen, Up_d64, Op_Stack, K_POP, Arg_Seg, {{S_FS}, {0}, {0}, {0}}, 0},
	{0xA2, Inst_Gen, 0, Op_Sys, S_CPUID, Arg_Null, {{0}, {0}, {0}, {0}}, 0},
	{0xA3, Inst_Gen, 0, Op_Calc, C_BT, Arg_ModRM, {{E, v}, {G, v}, {0}, {0}}, 0},
	{0xA4, Inst_Gen, 0, Op_Logic, L_SHLD, Arg_ModRM, {{E, v}, {G, v}, {I, b}, {0}}, 0},
	{0xA5, Inst_Gen, 0, Op_Logic, L_SHLD, Arg_ModRM, {{E, v}, {G, v}, {R_CL}, {0}}, 0},
	{0xA6, Inst_UD2},
	{0xA7, Inst_UD2},
	{0xA8, Inst_Gen, Up_d64, Op_Stack, K_PUSH, Arg_Seg, {{S_GS}, {0}, {0}, {0}}, 0},
	{0xA9, Inst_Gen, Up_d64, Op_Stack, K_POP, Arg_Seg, {{S_GS}, {0}, {0}, {0}}, 0},
	{0xAA, Inst_Gen, 0, Op_Sys, S_RSM, Arg_NoModRM, {{0}, {0}, {0}, {0}}, 0},
	{0xA3, Inst_Gen, 0, Op_Calc, C_BTS, Arg_ModRM, {{E, v}, {G, v}, {0}, {0}}, 0},
	{0xA4, Inst_Gen, 0, Op_Logic, L_SHRD, Arg_ModRM, {{E, v}, {G, v}, {I, b}, {0}}, 0},
	{0xA5, Inst_Gen, 0, Op_Logic, L_SHRD, Arg_ModRM, {{E, v}, {G, v}, {R_CL}, {0}}, 0},
	{0xAE, Inst_Grp, Grp_15, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ReMapGroup15},
	{0xAF, Inst_Gen, 0, Op_Calc, C_IMUL, Arg_ModRM, {{G, v}, {E, v}, {0}, {0}}, 0},

	{0xB0, Inst_Gen, 0, Op_Data, D_CMPXCHG, Arg_ModRM, {{E, b}, {G, b}, {0}, {0}}, 0},
	{0xB1, Inst_Gen, 0, Op_Data, D_CMPXCHG, Arg_ModRM, {{E, v}, {G, v}, {0}, {0}}, 0},
	{0xB2, Inst_Gen, 0, Op_Sys, S_LSS, Arg_ModRM, {{G, v}, {M, p}, {0}, {0}}, 0},
	{0xB3, Inst_Gen, 0, Op_Calc, C_BTR, Arg_ModRM, {{E, v}, {G, v}, {0}, {0}}, 0},
	{0xB4, Inst_Gen, 0, Op_Sys, S_LFS, Arg_ModRM, {{G, v}, {M, p}, {0}, {0}}, 0},
	{0xB5, Inst_Gen, 0, Op_Sys, S_LGS, Arg_ModRM, {{G, v}, {M, p}, {0}, {0}}, 0},
	{0xB6, Inst_Gen, 0, Op_Data, D_MOVZX, Arg_ModRM, {{G, v}, {E, b}, {0}, {0}}, 0},
	{0xB7, Inst_Gen, 0, Op_Data, D_MOVZX, Arg_ModRM, {{G, v}, {E, w}, {0}, {0}}, 0},
	{0xB8, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreB8},
	{0xB9, Inst_Grp, Grp_10, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ReMapGroup10},
	{0xBA, Inst_Grp, Grp_8, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ReMapGroup8},
	{0xBB, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreBB},
	{0xBC, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreBC},
	{0xBD, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreBD},
	{0xBE, Inst_Gen, 0, Op_Data, D_MOVSX, Arg_ModRM, {{G, v}, {E, b}, {0}, {0}}, 0},
	{0xBF, Inst_Gen, 0, Op_Data, D_MOVSX, Arg_ModRM, {{G, v}, {E, w}, {0}, {0}}, 0},

	{0xC0, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreC0},
	{0xC1, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreC1},
	{0xC2, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreC2},
	{0xC3, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreC3},
	{0xC4, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreC4},
	{0xC5, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreC5},
	{0xC6, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreC6},
	{0xC7, Inst_Grp, Grp_9, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ReMapGroup9},
	{0xC8, Inst_Gen, 0, Op_Calc, C_BSWAP, Arg_NoModRM, {{Rr_1}, {0}, {0}, {0}}, 0},
	{0xC9, Inst_Gen, 0, Op_Calc, C_BSWAP, Arg_NoModRM, {{Rr_2}, {0}, {0}, {0}}, 0},
	{0xCA, Inst_Gen, 0, Op_Calc, C_BSWAP, Arg_NoModRM, {{Rr_3}, {0}, {0}, {0}}, 0},
	{0xCB, Inst_Gen, 0, Op_Calc, C_BSWAP, Arg_NoModRM, {{Rr_4}, {0}, {0}, {0}}, 0},
	{0xCC, Inst_Gen, 0, Op_Calc, C_BSWAP, Arg_NoModRM, {{Rr_5}, {0}, {0}, {0}}, 0},
	{0xCD, Inst_Gen, 0, Op_Calc, C_BSWAP, Arg_NoModRM, {{Rr_6}, {0}, {0}, {0}}, 0},
	{0xCE, Inst_Gen, 0, Op_Calc, C_BSWAP, Arg_NoModRM, {{Rr_7}, {0}, {0}, {0}}, 0},
	{0xCF, Inst_Gen, 0, Op_Calc, C_BSWAP, Arg_NoModRM, {{Rr_8}, {0}, {0}, {0}}, 0},

	{0xD0, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreD0},
	{0xD1, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreD1},
	{0xD2, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreD2},
	{0xD3, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreD3},
	{0xD4, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreD4},
	{0xD5, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreD5},
	{0xD6, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreD6},
	{0xD7, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreD7},
	{0xD8, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreD8},
	{0xD9, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreD9},
	{0xDA, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreDA},
	{0xDB, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreDB},
	{0xDC, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreDC},
	{0xDD, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreDD},
	{0xDE, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreDE},
	{0xDF, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreDF},

	{0xE0, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreE0},
	{0xE1, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreE1},
	{0xE2, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreE2},
	{0xE3, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreE3},
	{0xE4, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreE4},
	{0xE5, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreE5},
	{0xE6, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreE6},
	{0xE7, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreE7},
	{0xE8, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreE8},
	{0xE9, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreE9},
	{0xEA, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreEA},
	{0xEB, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreEB},
	{0xEC, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreEC},
	{0xED, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreED},
	{0xEE, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreEE},
	{0xEF, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreEF},

	{0xF0, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreF0},
	{0xF1, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreF1},
	{0xF2, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreF2},
	{0xF3, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreF3},
	{0xF4, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreF4},
	{0xF5, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreF5},
	{0xF6, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreF6},
	{0xF7, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreF7},
	{0xF8, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreF8},
	{0xF9, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreF9},
	{0xFA, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreFA},
	{0xFB, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreFB},
	{0xFC, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreFC},
	{0xFD, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreFD},
	{0xFE, Inst_ExPre, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, &ExPreFE},
	{0xFF, Inst_UD2, 0, 0, 0, 0, {{0}, {0}, {0}, {0}}, 0},

};


OpcodeMap ReMap63[]={
{0x63,	Inst_I64,		Up_i64,	Op_Other,	O_ARPL,		Arg_ModRM,		{{E,w},		{G,w},	    {0},	{0}},0},
{0x63,	Inst_O64,		Up_o64,	Op_Data,	D_MOVSXD,	Arg_ModRM,		{{G,v},		{E,v},	    {0},	{0}},0},
};							    
OpcodeMap ReMapC4[]={   
{0xC4,	Inst_I64,		Up_i64,	Op_Sys,		S_LES,		Arg_ModRM,		{{G,z},		{M,p},	    {0},	{0}},0 },
{0xC4,	Inst_Vex2,		Up_o64,	0,			0,			0,				{{0},		{0},	    {0},	{0}},&ReMapVEX2[0]},
};  
OpcodeMap ReMapC5[]={   
{0xC5,	Inst_I64,		Up_i64,	Op_Sys,		S_LDS,		Arg_ModRM,		{{G,z},		{M,p},	    {0},	{0}},0 },
{0xC5,	Inst_Vex1,		Up_o64,	0,			0,			0,				{{0},		{0},	    {0},	{0}},&ReMapVEX1[0]},
};


OpcodeMap ReMap40[]={
{0x40,	Inst_I64,		Up_i64,	Op_Calc,	C_INC,		Arg_NoModRM,	{{R_eAX},	{0},	    {0},	{0}},0},
{0x40,	Inst_Rex,		Up_o64,	0,			0,			0,				{{0},		{0},	    {0},	{0}},0},
{0x41,	Inst_I64,		Up_i64,	Op_Calc,	C_INC,		Arg_NoModRM,	{{R_eCX},	{0},	    {0},	{0}},0},
{0x41,	Inst_Rex,		Up_o64,	0,			0,			0,				{{0},		{0},	    {0},	{0}},0},
{0x42,	Inst_I64,		Up_i64,	Op_Calc,	C_INC,		Arg_NoModRM,	{{R_eDX},	{0},	    {0},	{0}},0},
{0x42,	Inst_Rex,		Up_o64,	0,			0,			0,				{{0},		{0},	    {0},	{0}},0},
{0x43,	Inst_I64,		Up_i64,	Op_Calc,	C_INC,		Arg_NoModRM,	{{R_eBX},	{0},	    {0},	{0}},0},
{0x43,	Inst_Rex,		Up_o64,	0,			0,			0,				{{0},		{0},	    {0},	{0}},0},
{0x44,	Inst_I64,		Up_i64,	Op_Calc,	C_INC,		Arg_NoModRM,	{{R_eSP},	{0},	    {0},	{0}},0},
{0x44,	Inst_Rex,		Up_o64,	0,			0,			0,				{{0},		{0},	    {0},	{0}},0},
{0x45,	Inst_I64,		Up_i64,	Op_Calc,	C_INC,		Arg_NoModRM,	{{R_eBP},	{0},	    {0},	{0}},0},
{0x45,	Inst_Rex,		Up_o64,	0,			0,			0,				{{0},		{0},	    {0},	{0}},0},
{0x46,	Inst_I64,		Up_i64,	Op_Calc,	C_INC,		Arg_NoModRM,	{{R_eSI},	{0},	    {0},	{0}},0},
{0x46,	Inst_Rex,		Up_o64,	0,			0,			0,				{{0},		{0},	    {0},	{0}},0},
{0x47,	Inst_I64,		Up_i64,	Op_Calc,	C_INC,		Arg_NoModRM,	{{R_eDI},	{0},	    {0},	{0}},0},
{0x47,	Inst_Rex,		Up_o64,	0,			0,			0,				{{0},		{0},	    {0},	{0}},0},
{0x48,	Inst_I64,		Up_i64,	Op_Calc,	C_DEC,		Arg_NoModRM,	{{R_eAX},	{0},	    {0},	{0}},0},
{0x48,	Inst_Rex,		Up_o64,	0,			0,			0,				{{0},		{0},	    {0},	{0}},0},
{0x49,	Inst_I64,		Up_i64,	Op_Calc,	C_DEC,		Arg_NoModRM,	{{R_eCX},	{0},	    {0},	{0}},0},
{0x49,	Inst_Rex,		Up_o64,	0,			0,			0,				{{0},		{0},	    {0},	{0}},0},
{0x4A,	Inst_I64,		Up_i64,	Op_Calc,	C_DEC,		Arg_NoModRM,	{{R_eDX},	{0},	    {0},	{0}},0},
{0x4A,	Inst_Rex,		Up_o64,	0,			0,			0,				{{0},		{0},	    {0},	{0}},0},
{0x4B,	Inst_I64,		Up_i64,	Op_Calc,	C_DEC,		Arg_NoModRM,	{{R_eBX},	{0},	    {0},	{0}},0},
{0x4B,	Inst_Rex,		Up_o64,	0,			0,			0,				{{0},		{0},	    {0},	{0}},0},
{0x4C,	Inst_I64,		Up_i64,	Op_Calc,	C_DEC,		Arg_NoModRM,	{{R_eSP},	{0},	    {0},	{0}},0},
{0x4C,	Inst_Rex,		Up_o64,	0,			0,			0,				{{0},		{0},	    {0},	{0}},0},
{0x4D,	Inst_I64,		Up_i64,	Op_Calc,	C_DEC,		Arg_NoModRM,	{{R_eBP},	{0},	    {0},	{0}},0},
{0x4D,	Inst_Rex,		Up_o64,	0,			0,			0,				{{0},		{0},	    {0},	{0}},0},
{0x4E,	Inst_I64,		Up_i64,	Op_Calc,	C_DEC,		Arg_NoModRM,	{{R_eSI},	{0},	    {0},	{0}},0},
{0x4E,	Inst_Rex,		Up_o64,	0,			0,			0,				{{0},		{0},	    {0},	{0}},0},
{0x4F,	Inst_I64,		Up_i64,	Op_Calc,	C_DEC,		Arg_NoModRM,	{{R_eDI},	{0},	    {0},	{0}},0},
{0x4F,	Inst_Rex,		Up_o64,	0,			0,			0,				{{0},		{0},	    {0},	{0}},0},
};


OpcodeMap OneByte[]={
{0x00,	Inst_Gen,		0,		Op_Calc,	C_ADD,		Arg_ModRM,		{{E,b},		{G,b},	    {0},	{0}},0},
{0x01,	Inst_Gen,		0,		Op_Calc,	C_ADD,		Arg_ModRM,		{{E,v},		{G,v},	    {0},	{0}},0},
{0x02,	Inst_Gen,		0,		Op_Calc,	C_ADD,		Arg_ModRM,		{{G,b},		{E,b},	    {0},	{0}},0},
{0x03,	Inst_Gen,		0,		Op_Calc,	C_ADD,		Arg_ModRM,		{{G,v},		{E,v},	    {0},	{0}},0},
{0x04,	Inst_Gen,		0,		Op_Calc,	C_ADD,		Arg_NoModRM,	{{R_AL},	{I,b},	    {0},	{0}},0},
{0x05,	Inst_Gen,		0,		Op_Calc,	C_ADD,		Arg_NoModRM,	{{R_rAX},	{I,z},	    {0},	{0}},0},
{0x06,	Inst_I64,		Up_i64,	Op_Stack,	K_PUSH_ES,	Arg_Seg,		{{S_ES},	{0},	    {0},	{0}},0},
{0x07,	Inst_I64,		Up_i64,	Op_Stack,	K_POP_ES,	Arg_Seg,		{{S_ES},	{0},	    {0},	{0}},0},
{0x08,	Inst_Gen,		0,		Op_Calc,	C_OR,		Arg_ModRM,		{{E,b},		{G,b},	    {0},	{0}},0},
{0x09,	Inst_Gen,		0,		Op_Calc,	C_OR,		Arg_ModRM,		{{E,v},		{G,v},	    {0},	{0}},0},
{0x0A,	Inst_Gen,		0,		Op_Calc,	C_OR,		Arg_ModRM,		{{G,b},		{E,b},	    {0},	{0}},0},
{0x0B,	Inst_Gen,		0,		Op_Calc,	C_OR,		Arg_ModRM,		{{G,v},		{E,v},	    {0},	{0}},0},
{0x0C,	Inst_Gen,		0,		Op_Calc,	C_OR,		Arg_NoModRM,	{{R_AL},	{I,b},	    {0},	{0}},0},
{0x0D,	Inst_Gen,		0,		Op_Calc,	C_OR,		Arg_NoModRM,	{{R_rAX},	{I,z},	    {0},	{0}},0},
{0x0E,	Inst_I64,		Up_i64,	Op_Stack,	K_PUSH_CS,	Arg_Seg,		{{S_CS},	{0},	    {0},	{0}},0},
{0x0F,	Inst_2Byte,		0,		0,			0,			0,				{{0},		{0},	    {0},	{0}},&TwoByte[0]},

{0x10,	Inst_Gen,		0,		Op_Calc,	C_ADC,		Arg_ModRM,		{{E,b},		{G,b},	    {0},	{0}},0},
{0x11,	Inst_Gen,		0,		Op_Calc,	C_ADC,		Arg_ModRM,		{{E,v},		{G,v},	    {0},	{0}},0},
{0x12,	Inst_Gen,		0,		Op_Calc,	C_ADC,		Arg_ModRM,		{{G,b},		{E,b},	    {0},	{0}},0},
{0x13,	Inst_Gen,		0,		Op_Calc,	C_ADC,		Arg_ModRM,		{{G,v},		{E,v},	    {0},	{0}},0},
{0x14,	Inst_Gen,		0,		Op_Calc,	C_ADC,		Arg_NoModRM,	{{R_AL},	{I,b},	    {0},	{0}},0},
{0x15,	Inst_Gen,		0,		Op_Calc,	C_ADC,		Arg_NoModRM,	{{R_rAX},	{I,z},	    {0},	{0}},0},
{0x16,	Inst_I64,		Up_i64,	Op_Stack,	K_PUSH_SS,	Arg_Seg,		{{S_SS},	{0},	    {0},	{0}},0},
{0x17,	Inst_I64,		Up_i64,	Op_Stack,	K_POP_SS,	Arg_Seg,		{{S_SS},	{0},	    {0},	{0}},0},
{0x18,	Inst_Gen,		0,		Op_Calc,	C_SBB,		Arg_ModRM,		{{E,b},		{G,b},	    {0},	{0}},0},
{0x19,	Inst_Gen,		0,		Op_Calc,	C_SBB,		Arg_ModRM,		{{E,v},		{G,v},	    {0},	{0}},0},
{0x1A,	Inst_Gen,		0,		Op_Calc,	C_SBB,		Arg_ModRM,		{{G,b},		{E,b},	    {0},	{0}},0},
{0x1B,	Inst_Gen,		0,		Op_Calc,	C_SBB,		Arg_ModRM,		{{G,v},		{E,v},	    {0},	{0}},0},
{0x1C,	Inst_Gen,		0,		Op_Calc,	C_SBB,		Arg_NoModRM,	{{R_AL},	{I,b},	    {0},	{0}},0},
{0x1D,	Inst_Gen,		0,		Op_Calc,	C_SBB,		Arg_NoModRM,	{{R_rAX},	{I,z},	    {0},	{0}},0},
{0x1E,	Inst_I64,		Up_i64,	Op_Stack,	K_PUSH_DS,	Arg_Seg,		{{S_DS},	{0},	    {0},	{0}},0},
{0x1F,	Inst_I64,		Up_i64,	Op_Stack,	K_POP_DS,	Arg_Seg,		{{S_DS},	{0},	    {0},	{0}},0},

{0x20,	Inst_Gen,		0,		Op_Calc,	C_AND,		Arg_ModRM,		{{E,b},		{G,b},	    {0},	{0}},0},
{0x21,	Inst_Gen,		0,		Op_Calc,	C_AND,		Arg_ModRM,		{{E,v},		{G,v},	    {0},	{0}},0},
{0x22,	Inst_Gen,		0,		Op_Calc,	C_AND,		Arg_ModRM,		{{G,b},		{E,b},	    {0},	{0}},0},
{0x23,	Inst_Gen,		0,		Op_Calc,	C_AND,		Arg_ModRM,		{{G,v},		{E,v},	    {0},	{0}},0},
{0x24,	Inst_Gen,		0,		Op_Calc,	C_AND,		Arg_NoModRM,	{{R_AL},	{I,b},	    {0},	{0}},0},
{0x25,	Inst_Gen,		0,		Op_Calc,	C_AND,		Arg_NoModRM,	{{R_rAX},	{I,z},	    {0},	{0}},0},
{0x26,	Inst_Pre,		P_Grp2,	0,			0,			Arg_Seg,		{{S_ES},	{0},	    {0},	{0}},0},
{0x27,	Inst_I64,		Up_i64,	Op_Other,	O_DAA,		Arg_Null,		{{0},		{0},	    {0},	{0}},0},
{0x28,	Inst_Gen,		0,		Op_Calc,	C_SUB,		Arg_ModRM,		{{E,b},		{G,b},	    {0},	{0}},0},
{0x29,	Inst_Gen,		0,		Op_Calc,	C_SUB,		Arg_ModRM,		{{E,v},		{G,v},	    {0},	{0}},0},
{0x2A,	Inst_Gen,		0,		Op_Calc,	C_SUB,		Arg_ModRM,		{{G,b},		{E,b},	    {0},	{0}},0},
{0x2B,	Inst_Gen,		0,		Op_Calc,	C_SUB,		Arg_ModRM,		{{G,v},		{E,v},	    {0},	{0}},0},
{0x2C,	Inst_Gen,		0,		Op_Calc,	C_SUB,		Arg_NoModRM,	{{R_AL},	{I,b},	    {0},	{0}},0},
{0x2D,	Inst_Gen,		0,		Op_Calc,	C_SUB,		Arg_NoModRM,	{{R_rAX},	{I,z},	    {0},	{0}},0},
{0x2E,	Inst_Pre,		P_Grp2,	0,			0,			Arg_Seg,		{{S_CS},	{0},	    {0},	{0}},0},
{0x2F,	Inst_I64,		Up_i64,	Op_Other,	O_DAS,		Arg_Null,		{{0},		{0},	    {0},	{0}},0},

{0x30,	Inst_Gen,		0,		Op_Calc,	C_XOR,		Arg_ModRM,		{{E,b},		{G,b},	    {0},	{0}},0},
{0x31,	Inst_Gen,		0,		Op_Calc,	C_XOR,		Arg_ModRM,		{{E,v},		{G,v},	    {0},	{0}},0},
{0x32,	Inst_Gen,		0,		Op_Calc,	C_XOR,		Arg_ModRM,		{{G,b},		{E,b},	    {0},	{0}},0},
{0x33,	Inst_Gen,		0,		Op_Calc,	C_XOR,		Arg_ModRM,		{{G,v},		{E,v},	    {0},	{0}},0},
{0x34,	Inst_Gen,		0,		Op_Calc,	C_XOR,		Arg_NoModRM,	{{R_AL},	{I,b},	    {0},	{0}},0},
{0x35,	Inst_Gen,		0,		Op_Calc,	C_XOR,		Arg_NoModRM,	{{R_rAX},	{I,z},	    {0},	{0}},0},
{0x36,	Inst_Pre,		P_Grp2,	0,			0,			Arg_Seg,		{{S_SS},	{0},	    {0},	{0}},0},
{0x37,	Inst_I64,		Up_i64,	Op_Other,	O_AAA,		Arg_Null,		{{0},		{0},	    {0},	{0}},0},
{0x38,	Inst_Gen,		0,		Op_Calc,	C_CMP,		Arg_ModRM,		{{E,b},		{G,b},	    {0},	{0}},0},
{0x39,	Inst_Gen,		0,		Op_Calc,	C_CMP,		Arg_ModRM,		{{E,v},		{G,v},	    {0},	{0}},0},
{0x3A,	Inst_Gen,		0,		Op_Calc,	C_CMP,		Arg_ModRM,		{{G,b},		{E,b},	    {0},	{0}},0},
{0x3B,	Inst_Gen,		0,		Op_Calc,	C_CMP,		Arg_ModRM,		{{G,v},		{E,v},	    {0},	{0}},0},
{0x3C,	Inst_Gen,		0,		Op_Calc,	C_CMP,		Arg_NoModRM,	{{R_AL},	{I,b},	    {0},	{0}},0},
{0x3D,	Inst_Gen,		0,		Op_Calc,	C_CMP,		Arg_NoModRM,	{{R_rAX},	{I,z},	    {0},	{0}},0},
{0x3E,	Inst_Pre,		P_Grp2,	0,			0,			Arg_Seg,		{{S_DS},	{0},	    {0},	{0}},0},
{0x3F,	Inst_I64,		Up_i64,	Op_Other,	O_AAS,		Arg_Null,		{{0},		{0},	    {0},	{0}},0},

{0x40,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMap40[2*0]},
{0x41,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMap40[2*1]},
{0x42,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMap40[2*2]},
{0x43,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMap40[2*3]},
{0x44,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMap40[2*4]},
{0x45,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMap40[2*5]},
{0x46,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMap40[2*6]},
{0x47,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMap40[2*7]},
{0x48,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMap40[2*8]},
{0x49,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMap40[2*9]},
{0x4A,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMap40[2*0xA]},
{0x4B,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMap40[2*0xB]},
{0x4C,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMap40[2*0xC]},
{0x4D,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMap40[2*0xD]},
{0x4E,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMap40[2*0xE]},
{0x4F,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMap40[2*0xF]},

{0x50,	Inst_Gen,		Up_d64,	Op_Stack,	K_PUSH,		Arg_NoModRM,	{{Rr_1},	{0},		{0},	{0}},0},
{0x51,	Inst_Gen,		Up_d64,	Op_Stack,	K_PUSH,		Arg_NoModRM,	{{Rr_2},	{0},		{0},	{0}},0},
{0x52,	Inst_Gen,		Up_d64,	Op_Stack,	K_PUSH,		Arg_NoModRM,	{{Rr_3},	{0},		{0},	{0}},0},
{0x53,	Inst_Gen,		Up_d64,	Op_Stack,	K_PUSH,		Arg_NoModRM,	{{Rr_4},	{0},		{0},	{0}},0},
{0x54,	Inst_Gen,		Up_d64,	Op_Stack,	K_PUSH,		Arg_NoModRM,	{{Rr_5},	{0},		{0},	{0}},0},
{0x55,	Inst_Gen,		Up_d64,	Op_Stack,	K_PUSH,		Arg_NoModRM,	{{Rr_6},	{0},		{0},	{0}},0},
{0x56,	Inst_Gen,		Up_d64,	Op_Stack,	K_PUSH,		Arg_NoModRM,	{{Rr_7},	{0},		{0},	{0}},0},
{0x57,	Inst_Gen,		Up_d64,	Op_Stack,	K_PUSH,		Arg_NoModRM,	{{Rr_8},	{0},		{0},	{0}},0},
{0x58,	Inst_Gen,		Up_d64,	Op_Stack,	K_POP,		Arg_NoModRM,	{{Rr_1},	{0},		{0},	{0}},0},
{0x59,	Inst_Gen,		Up_d64,	Op_Stack,	K_POP,		Arg_NoModRM,	{{Rr_2},	{0},		{0},	{0}},0},
{0x5A,	Inst_Gen,		Up_d64,	Op_Stack,	K_POP,		Arg_NoModRM,	{{Rr_3},	{0},		{0},	{0}},0},
{0x5B,	Inst_Gen,		Up_d64,	Op_Stack,	K_POP,		Arg_NoModRM,	{{Rr_4},	{0},		{0},	{0}},0},
{0x5C,	Inst_Gen,		Up_d64,	Op_Stack,	K_POP,		Arg_NoModRM,	{{Rr_5},	{0},		{0},	{0}},0},
{0x5D,	Inst_Gen,		Up_d64,	Op_Stack,	K_POP,		Arg_NoModRM,	{{Rr_6},	{0},		{0},	{0}},0},
{0x5E,	Inst_Gen,		Up_d64,	Op_Stack,	K_POP,		Arg_NoModRM,	{{Rr_7},	{0},		{0},	{0}},0},
{0x5F,	Inst_Gen,		Up_d64,	Op_Stack,	K_POP,		Arg_NoModRM,	{{Rr_8},	{0},		{0},	{0}},0},

{0x60,	Inst_I64,		Up_i64,	Op_Stack,	K_PUSHAD,	Arg_Null,		{{0},		{0},		{0},	{0}},0},
{0x61,	Inst_I64,		Up_i64,	Op_Stack,	K_POPAD,	Arg_Null,		{{0},		{0},		{0},	{0}},0},
{0x62,	Inst_I64,		Up_i64,	Op_Other,	O_BOUND,	Arg_ModRM,		{{G,v},		{M,a},	    {0},	{0}},0},
{0x63,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMap63[0]},
{0x64,	Inst_Pre,		P_Grp2,	0,			0,			Arg_Seg,		{{S_FS},	{0},		{0},	{0}},0},
{0x65,	Inst_Pre,		P_Grp2,	0,			0,			Arg_Seg,		{{S_GS},	{0},		{0},	{0}},0},
{0x66,	Inst_Pre,		P_Grp3,	0,			0,			0,				{{0},		{0},		{0},	{0}},0},
{0x67,	Inst_Pre,		P_Grp4,	0,			0,			0,				{{0},		{0},		{0},	{0}},0},
{0x68,	Inst_Gen,		Up_d64,	Op_Stack,	K_PUSH,		Arg_NoModRM,	{{I,z},		{0},		{0},	{0}},0},
{0x69,	Inst_Gen,		0,		Op_Calc,	C_IMUL,		Arg_ModRM,		{{G,v},		{E,v},	    {I,z},	{0}},0},
{0x6A,	Inst_Gen,		Up_d64,	Op_Stack,	K_PUSH,		Arg_NoModRM,	{{I,b},		{0},		{0},	{0}},0},
{0x6B,	Inst_Gen,		0,		Op_Calc,	C_IMUL,		Arg_ModRM,		{{G,v},		{E,v},	    {I,b},	{0}},0},
{0x6C,	Inst_Gen,		0,		Op_IO,		IO_INS,		Arg_NoModRM,	{{Y,b},		{R_DX},	    {0},	{0}},0},
{0x6D,	Inst_Gen,		0,		Op_IO,		IO_INS,		Arg_NoModRM,	{{Y,z},		{R_DX},	    {0},	{0}},0},
{0x6E,	Inst_Gen,		0,		Op_IO,		IO_OUTS,	Arg_NoModRM,	{{R_DX},	{X,b},	    {0},	{0}},0},
{0x6F,	Inst_Gen,		0,		Op_IO,		IO_OUTS,	Arg_NoModRM,	{{R_DX},	{X,z},	    {0},	{0}},0},

{0x70,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JO,		Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0x71,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JNO,		Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0x72,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JC,		Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0x73,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JNC,		Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0x74,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JE,		Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0x75,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JNE,		Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0x76,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JNA,		Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0x77,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JA,		Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0x78,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JS,		Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0x79,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JNS,		Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0x7A,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JP,		Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0x7B,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JNP,		Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0x7C,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JL,		Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0x7D,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JNL,		Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0x7E,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JNG,		Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0x7F,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JG,		Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},

{0x80,	Inst_Grp,		Grp_1,	0,			0,			0,				{{E,b},		{I,b},	    {0},	{0}},&ReMapGroup1[0]},
{0x81,	Inst_Grp,		Grp_1,	0,			0,			0,				{{E,v},		{I,z},	    {0},	{0}},&ReMapGroup1[0]},
{0x82,	Inst_Grp,		Grp_1,	0,			0,			0,				{{E,b},		{I,b},	    {0},	{0}},&ReMapGroup1[0]},
{0x83,	Inst_Grp,		Grp_1,	0,			0,			0,				{{E,v},		{I,b},	    {0},	{0}},&ReMapGroup1[0]},
{0x84,	Inst_Gen,		0,		Op_Calc,	C_TEST,		Arg_ModRM,		{{E,b},		{G,b},	    {0},	{0}},0},
{0x85,	Inst_Gen,		0,		Op_Calc,	C_TEST,		Arg_ModRM,		{{E,v},		{G,v},	    {0},	{0}},0},
{0x86,	Inst_Gen,		0,		Op_Data,	D_XCHG,		Arg_ModRM,		{{E,b},		{G,b},	    {0},	{0}},0},
{0x87,	Inst_Gen,		0,		Op_Data,	D_XCHG,		Arg_ModRM,		{{E,v},		{G,v},	    {0},	{0}},0},
{0x88,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_ModRM,		{{E,b},		{G,b},	    {0},	{0}},0},
{0x89,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_ModRM,		{{E,v},		{G,v},	    {0},	{0}},0},
{0x8A,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_ModRM,		{{G,b},		{E,b},	    {0},	{0}},0},
{0x8B,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_ModRM,		{{G,v},		{E,v},	    {0},	{0}},0},
{0x8C,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_ModRM,		{{E,v},		{S,w},	    {0},	{0}},0},
{0x8D,	Inst_Gen,		0,		Op_Data,	D_LEA,		Arg_ModRM,		{{G,v},		{M},	    {0},	{0}},0},
{0x8E,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_ModRM,		{{S,w},		{E,w},	    {0},	{0}},0},
{0x8F,	Inst_Grp,		Grp_1A,	Op_Stack,	K_POP,		Arg_ModRM,		{{E,v},		{0},	    {0},	{0}},&ReMapGroup1A[0]},

{0x90,	Inst_Gen,		0,		Op_Data,	D_XCHG,		Arg_NoModRM,	{{R_rAX},	{Rr_1},	    {0},	{0}},0},
{0x91,	Inst_Gen,		0,		Op_Data,	D_XCHG,		Arg_NoModRM,	{{R_rAX},	{Rr_2},	    {0},	{0}},0},
{0x92,	Inst_Gen,		0,		Op_Data,	D_XCHG,		Arg_NoModRM,	{{R_rAX},	{Rr_3},	    {0},	{0}},0},
{0x93,	Inst_Gen,		0,		Op_Data,	D_XCHG,		Arg_NoModRM,	{{R_rAX},	{Rr_4},	    {0},	{0}},0},
{0x94,	Inst_Gen,		0,		Op_Data,	D_XCHG,		Arg_NoModRM,	{{R_rAX},	{Rr_5},	    {0},	{0}},0},
{0x95,	Inst_Gen,		0,		Op_Data,	D_XCHG,		Arg_NoModRM,	{{R_rAX},	{Rr_6},	    {0},	{0}},0},
{0x96,	Inst_Gen,		0,		Op_Data,	D_XCHG,		Arg_NoModRM,	{{R_rAX},	{Rr_7},	    {0},	{0}},0},
{0x97,	Inst_Gen,		0,		Op_Data,	D_XCHG,		Arg_NoModRM,	{{R_rAX},	{Rr_8},	    {0},	{0}},0},
{0x98,	Inst_Gen,		0,		Op_Other,	O_CBW,		Arg_Null,		{{0},		{0},	    {0},	{0}},0},
{0x99,	Inst_Gen,		0,		Op_Other,	O_CWD,		Arg_Null,		{{0},		{0},	    {0},	{0}},0},
{0x9A,	Inst_I64,		Up_i64,	Op_Jcc,		J_CALL, 	Arg_NoModRM,	{{A,p},		{0},	    {0},	{0}},0},
{0x9B,	Inst_Gen,		0,		Op_Other,	O_FWAIT,	Arg_Null,		{{0},		{0},	    {0},	{0}},0},
{0x9C,	Inst_Gen,		Up_d64,	Op_Flags,	F_PUSHF,	Arg_NoModRM,	{{F,v},		{0},	    {0},	{0}},0},
{0x9D,	Inst_Gen,		Up_d64,	Op_Flags,	F_POPF,		Arg_NoModRM,	{{F,v},		{0},	    {0},	{0}},0},
{0x9E,	Inst_Gen,		0,		Op_Flags,	F_SAHF,		Arg_Null,		{{0},		{0},	    {0},	{0}},0},
{0x9F,	Inst_Gen,		0,		Op_Flags,	F_LAHF,		Arg_Null,		{{0},		{0},	    {0},	{0}},0},

{0xA0,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{R_AL},	{O,b},	    {0},	{0}},0},
{0xA1,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{R_rAX},	{O,v},	    {0},	{0}},0},
{0xA2,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{O,b},		{R_AL},	    {0},	{0}},0},
{0xA3,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{O,v},		{R_rAX},    {0},	{0}},0},
{0xA4,	Inst_Gen,		0,		Op_Data,	D_MOVS,		Arg_NoModRM,	{{Y,b},		{X,b},	    {0},	{0}},0},
{0xA5,	Inst_Gen,		0,		Op_Data,	D_MOVS,		Arg_NoModRM,	{{Y,v},		{X,v},	    {0},	{0}},0},
{0xA6,	Inst_Gen,		0,		Op_Data,	D_CMPS,		Arg_NoModRM,	{{X,b},		{Y,b},	    {0},	{0}},0},
{0xA7,	Inst_Gen,		0,		Op_Data,	D_CMPS,		Arg_NoModRM,	{{X,v},		{Y,v},	    {0},	{0}},0},
{0xA8,	Inst_Gen,		0,		Op_Calc,	C_TEST,		Arg_NoModRM,	{{R_AL},	{I,b},	    {0},	{0}},0},
{0xA9,	Inst_Gen,		0,		Op_Calc,	C_TEST,		Arg_NoModRM,	{{R_rAX},	{I,z},	    {0},	{0}},0},
{0xAA,	Inst_Gen,		0,		Op_Data,	D_STOS,		Arg_NoModRM,	{{Y,b},		{R_AL},	    {0},	{0}},0},
{0xAB,	Inst_Gen,		0,		Op_Data,	D_STOS,		Arg_NoModRM,	{{Y,v},		{R_rAX},    {0},	{0}},0},
{0xAC,	Inst_Gen,		0,		Op_Data,	D_LODS,		Arg_NoModRM,	{{R_AL},	{X,b},	    {0},	{0}},0},
{0xAD,	Inst_Gen,		0,		Op_Data,	D_LODS,		Arg_NoModRM,	{{R_rAX},	{X,v},	    {0},	{0}},0},
{0xAE,	Inst_Gen,		0,		Op_Data,	D_SCAS,		Arg_NoModRM,	{{R_AL},	{Y,b},	    {0},	{0}},0},
{0xAF,	Inst_Gen,		0,		Op_Data,	D_SCAS,		Arg_NoModRM,	{{R_rAX},	{Y,v},	    {0},	{0}},0},

{0xB0,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{Rb_1},	{I,b},	    {0},	{0}},0},
{0xB1,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{Rb_2},	{I,b},	    {0},	{0}},0},
{0xB2,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{Rb_3},	{I,b},	    {0},	{0}},0},
{0xB3,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{Rb_4},	{I,b},	    {0},	{0}},0},
{0xB4,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{Rb_5},	{I,b},	    {0},	{0}},0},
{0xB5,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{Rb_6},	{I,b},	    {0},	{0}},0},
{0xB6,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{Rb_7},	{I,b},	    {0},	{0}},0},
{0xB7,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{Rb_8},	{I,b},	    {0},	{0}},0},
{0xB8,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{Rr_1},	{I,v},	    {0},	{0}},0},
{0xB9,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{Rr_2},	{I,v},	    {0},	{0}},0},
{0xBA,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{Rr_3},	{I,v},	    {0},	{0}},0},
{0xBB,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{Rr_4},	{I,v},	    {0},	{0}},0},
{0xBC,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{Rr_5},	{I,v},	    {0},	{0}},0},
{0xBD,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{Rr_6},	{I,v},	    {0},	{0}},0},
{0xBE,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{Rr_7},	{I,v},	    {0},	{0}},0},
{0xBF,	Inst_Gen,		0,		Op_Data,	D_MOV,		Arg_NoModRM,	{{Rr_8},	{I,v},	    {0},	{0}},0},

{0xC0,	Inst_Grp,		Grp_2,	0,			0,			0,				{{E,b},		{I,b},	    {0},	{0}},&ReMapGroup2[0]},
{0xC1,	Inst_Grp,		Grp_2,	0,			0,			0,				{{E,v},		{I,b},	    {0},	{0}},&ReMapGroup2[0]},
{0xC2,	Inst_Gen,		Up_f64,	Op_Jcc,		J_RET,	    Arg_NoModRM,	{{I,w},		{0},	    {0},	{0}},0},
{0xC3,	Inst_Gen,		Up_f64,	Op_Jcc,		J_RET,	    Arg_Null,		{{0},		{0},	    {0},	{0}},0},
{0xC4,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},	    {0},	{0}},&ReMapC4[0]},
{0xC5,	Inst_IO64,		0,		0,			0,			0,				{{0},		{0},	    {0},	{0}},&ReMapC5[0]},
{0xC6,	Inst_Grp,		Grp_11,	0,			D_MOV,		Arg_E_ModRM,	{{E,b},		{I,b},	    {0},	{0}},&ReMapGroup11[0]},
{0xC7,	Inst_Grp,		Grp_11,	0,			D_MOV,		Arg_E_ModRM,	{{E,v},		{I,z},	    {0},	{0}},&ReMapGroup11[0]},
{0xC8,	Inst_Gen,		0,		Op_Other,	O_ENTER,	Arg_NoModRM,	{{I,w},		{I,b},	    {0},	{0}},0},
{0xC9,	Inst_Gen,		Up_d64,	Op_Other,	O_LEAVE,	Arg_Null,		{{0},		{0},	    {0},	{0}},0},
{0xCA,	Inst_Gen,		0,		Op_Jcc,		J_RET,	    Arg_NoModRM,	{{I,w},		{0},	    {0},	{0}},0},
{0xCB,	Inst_Gen,		0,		Op_Jcc,		J_RET,	    Arg_Null,		{{0},		{0},	    {0},	{0}},0},
{0xCC,	Inst_Gen,		0,		Op_Sys,		S_INT3,		Arg_NoModRM,	{{0},		{0},	    {0},	{0}},0},
{0xCD,	Inst_Gen,		0,		Op_Sys,		S_INT,		Arg_NoModRM,	{{I,b},		{0},	    {0},	{0}},0},
{0xCE,	Inst_I64,		Up_i64,	Op_Other,	O_INTO,		Arg_Null,		{{0},		{0},	    {0},	{0}},0},
{0xCF,	Inst_Gen,		0,		Op_Jcc,		J_IRET,	    Arg_Null,		{{0},		{0},	    {0},	{0}},0},

{0xD0,	Inst_Grp,		Grp_2,	0,			0,			0,				{{E,b},		{I,Imm1},   {0},    {0}},&ReMapGroup2[0]},
{0xD1,	Inst_Grp,		Grp_2,	0,			0,			0,				{{E,v},		{I,Imm1},   {0},    {0}},&ReMapGroup2[0]},
{0xD2,	Inst_Grp,		Grp_2,	0,			0,			0,				{{E,b},		{R_CL},	    {0},	{0}},&ReMapGroup2[0]},
{0xD3,	Inst_Grp,		Grp_2,	0,			0,			0,				{{E,v},		{R_CL},	    {0},	{0}},&ReMapGroup2[0]},
{0xD4,	Inst_I64,		Up_i64,	Op_Other,	O_AAM,		Arg_NoModRM,	{{I,b},		{0},		{0},	{0}},0},
{0xD5,	Inst_I64,		Up_i64,	Op_Other,	O_AAD,		Arg_NoModRM,	{{I,b},		{0},		{0},	{0}},0},
{0xD6,	Inst_UD2 },
{0xD7,	Inst_Gen,		0,		Op_Other,	O_XLAT,		Arg_Null,		{{0},		{0},		{0},	{0}},0},
{0xD8,	Inst_Esc,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReEscape[0]},
{0xD9,	Inst_Esc,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReEscape[1]},
{0xDA,	Inst_Esc,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReEscape[2]},
{0xDB,	Inst_Esc,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReEscape[3]},
{0xDC,	Inst_Esc,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReEscape[4]},
{0xDD,	Inst_Esc,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReEscape[5]},
{0xDE,	Inst_Esc,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReEscape[6]},
{0xDF,	Inst_Esc,		0,		0,			0,			0,				{{0},		{0},		{0},	{0}},&ReEscape[7]},

{0xE0,	Inst_Gen,		Up_f64,	Op_Jcc,		J_LOOPNE,	Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0xE1,	Inst_Gen,		Up_f64,	Op_Jcc,		J_LOOPE,	Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0xE2,	Inst_Gen,		Up_f64,	Op_Jcc,		J_LOOP,		Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0xE3,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JCXZ,		Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0xE4,	Inst_Gen,		0,		Op_IO,		IO_IN,		Arg_NoModRM,	{{R_AL},	{I,b},	    {0},	{0}},0},
{0xE5,	Inst_Gen,		0,		Op_IO,		IO_IN,		Arg_NoModRM,	{{R_eAX},	{I,b},	    {0},	{0}},0},
{0xE6,	Inst_Gen,		0,		Op_IO,		IO_OUT,		Arg_NoModRM,	{{I,b},		{R_AL},	    {0},	{0}},0},
{0xE7,	Inst_Gen,		0,		Op_IO,		IO_OUT,		Arg_NoModRM,	{{I,b},		{R_eAX},    {0},	{0}},0},
{0xE8,	Inst_Gen,		Up_f64,	Op_Jcc,		J_CALL,     Arg_NoModRM,	{{J,z},		{0},		{0},	{0}},0},
{0xE9,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JMP,	    Arg_NoModRM,	{{J,z},		{0},		{0},	{0}},0},
{0xEA,	Inst_I64,		Up_i64,	Op_Jcc,		J_JMP,	    Arg_NoModRM,	{{A,p},		{0},		{0},	{0}},0},
{0xEB,	Inst_Gen,		Up_f64,	Op_Jcc,		J_JMP,      Arg_NoModRM,	{{J,b},		{0},		{0},	{0}},0},
{0xEC,	Inst_Gen,		0,		Op_IO,		IO_IN,		Arg_NoModRM,	{{R_AL},	{R_DX},	    {0},	{0}},0},
{0xED,	Inst_Gen,		0,		Op_IO,		IO_IN,		Arg_NoModRM,	{{R_eAX},	{R_DX},	    {0},	{0}},0},
{0xEE,	Inst_Gen,		0,		Op_IO,		IO_OUT,		Arg_NoModRM,	{{R_DX},	{R_AL},	    {0},	{0}},0},
{0xEF,	Inst_Gen,		0,		Op_IO,		IO_OUT,		Arg_NoModRM,	{{R_DX},	{R_eAX},    {0},	{0}},0},

{0xF0,	Inst_Pre,		P_Grp1,	Op_Pre,		P_LOCK,		Arg_Null,		{{0},		{0},		{0},	{0}},0},
{0xF1,	Inst_Gen,		0,		Op_Sys,		S_INT1,		Arg_Null,		{{0},		{0},		{0},	{0}},0},
{0xF2,	Inst_Pre,		P_Grp1,	Op_Pre,		P_REPNE,	Arg_Null,		{{0},		{0},		{0},	{0}},0},
{0xF3,	Inst_Pre,		P_Grp1,	Op_Pre,		P_REP,		Arg_Null,		{{0},		{0},		{0},	{0}},0},
{0xF4,	Inst_Gen,		0,		Op_Sys,		S_HLT,		Arg_Null,		{{0},		{0},		{0},	{0}},0},
{0xF5,	Inst_Gen,		0,		Op_Flags,	F_CMC,		Arg_Null,		{{0},		{0},		{0},	{0}},0},
{0xF6,	Inst_Grp,		Grp_3,	0,			0,			0,				{{E,b},		{0},		{0},	{0}},&ReMapGroup3[0]},
{0xF7,	Inst_Grp,		Grp_3,	0,			0,			0,				{{E,v},		{0},		{0},	{0}},&ReMapGroup3[0]},
{0xF8,	Inst_Gen,		0,		Op_Flags,	F_CLC,		Arg_Null,		{{0},		{0},		{0},	{0}},0},
{0xF9,	Inst_Gen,		0,		Op_Flags,	F_STC,		Arg_Null,		{{0},		{0},		{0},	{0}},0},
{0xFA,	Inst_Gen,		0,		Op_Flags,	F_CLI,		Arg_Null,		{{0},		{0},		{0},	{0}},0},
{0xFB,	Inst_Gen,		0,		Op_Flags,	F_STI,		Arg_Null,		{{0},		{0},		{0},	{0}},0},
{0xFC,	Inst_Gen,		0,		Op_Flags,	F_CLD,		Arg_Null,		{{0},		{0},		{0},	{0}},0},
{0xFD,	Inst_Gen,		0,		Op_Flags,	F_STD,		Arg_Null,		{{0},		{0},		{0},	{0}},0},
{0xFE,	Inst_Grp,		Grp_4,	0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMapGroup4[0]},
{0xFF,	Inst_Grp,		Grp_5,	0,			0,			0,				{{0},		{0},		{0},	{0}},&ReMapGroup5[0]},
};
