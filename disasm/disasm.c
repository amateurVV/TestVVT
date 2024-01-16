#include "type.h"
#include "disasm.h"
#include "instrType.h"
#include "instrMap.h"

uint64 MaxBit[9] = {0, MAX_BIT8, MAX_BIT16, 0, MAX_BIT32, 0, 0, 0, MAX_BIT64};
uint64 MaxSym[9] = {0, SYM_BIT8, SYM_BIT16, 0, SYM_BIT32, 0, 0, 0, SYM_BIT64};

char *_i64toa_s(long long value, char *buffer, int bufferSize, int radix)
{
	if (buffer == NULL || bufferSize == 0)
	{
		return NULL;
	}

	char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char isNegative = (value < 0);
	int index = 0;

	if (isNegative)
	{
		value = -value;
		buffer[index++] = '-';
	}

	do
	{
		buffer[index++] = digits[value % radix];
		value /= radix;
	} while (value != 0 && index < bufferSize);

	if (index >= bufferSize)
	{
		return NULL;
	}

	buffer[index] = '\0';

	// Reverse the number string
	int start = isNegative ? 1 : 0;
	int end = index - 1;

	while (start < end)
	{
		char temp = buffer[start];
		buffer[start] = buffer[end];
		buffer[end] = temp;

		start++;
		end--;
	}

	return buffer;
}

uint64 StrCopy(uint8 *StrOut, uint8 *begin, uint8 *StrIn);

uint64 GetAddr(DisInstr *Instr, uint64 Disp, uint8 DispSize)
{
	uint64 addr = Instr->Ex.Rip.u64 + Instr->Ex.instrLen;
	// if (Disp & (1 << (DispSize * 8 - 1)))
	if (Disp & MaxSym[DispSize])
	{
		return addr - (~Disp + 1 & MaxBit[DispSize]);
	}
	return addr + (Disp & MaxBit[DispSize]);
}
uint64 GetDisp(DisInstr *Instr, uint8 DispSize)
{
	DispSize = (DispSize == 0 ? Instr->Ex.Dsize : DispSize);
	return (*((uint64 *)(Instr->Ex.CodeRip.u64 + Instr->Ex.instrLen))) & MaxBit[DispSize];
}
uint8 GetArgSize(DisInstr *Instr, int8 size)
{
	switch (size)
	{
	case v:
	{
		return Instr->Ex.Dsize;
	}
	case z:
	{
		return Instr->Ex.Dsize > Bit32 ? Bit32 : Instr->Ex.Dsize;
	}
	case d:
	{
		return Bit32;
	}
	case w:
	{
		return Bit16;
	}
	case b:
	{
		return Bit8;
	}
	case p:
	{
		return Instr->Ex.Dsize + (uint8)2;
	}
	case s:
	{
		return Instr->Ex.mode == Bit32 ? Bit48 : Bit80;
	}
	case y:
	{
		// return Instr->Ex.mode==Bit64?Bit128:Bit64;
		return Instr->Ex.Dsize;
	}
	case ps:
	{
		return Bit128;
	}
	case pd:
	{
		return Bit128;
	}
	case q:
	{
		return Bit128;
	}
	case x:
	{
		return Bit128;
	}
	default:
	{
		return 0;
	}
	}
}
uint64 SetImme(DisInstr *Instr, uint8 pos, uint8 Size)
{
	Instr->DisType.Arg[pos].immeSize = Size;
	Instr->DisType.Arg[pos].use_imme = TRUE;
	Instr->DisHex.Imme[pos].imm64 = GetDisp(Instr, Size);
	Instr->Ex.instrLen += Size;
	return SUCESS;
}
uint64 SetDisp(DisInstr *Instr, uint8 pos, uint8 Size)
{
	Instr->DisType.Arg[pos].dispSize = Size;
	Instr->DisType.Arg[pos].use_disp = TRUE;
	Instr->DisHex.Disp[pos].disp64 = GetDisp(Instr, Size);
	Instr->Ex.instrLen += Size;
	return SUCESS;
}
uint64 SibSetBaseReg(DisInstr *Instr, uint8 pos, uint8 Size)
{
	Instr->DisType.Arg[pos].regSize = Size;
	Instr->DisType.Arg[pos].regBase = Instr->DisHex.SIB.ctx.Base;
	Instr->DisType.Arg[pos].regBase |= Instr->DisHex.Rex.ctx.B ? 8 : 0;
	Instr->DisType.Arg[pos].use_regBase = TRUE;
	return SUCESS;
}
uint64 SibSetIndexReg(DisInstr *Instr, uint8 pos, uint8 Size)
{
	Instr->DisType.Arg[pos].regSize = Size;
	Instr->DisType.Arg[pos].regIndex = Instr->DisHex.SIB.ctx.Index;
	Instr->DisType.Arg[pos].regIndex |= Instr->DisHex.Rex.ctx.X ? 8 : 0;
	Instr->DisType.Arg[pos].use_regIndex = TRUE;
	return SUCESS;
}
uint64 ModrmSetBaseReg(DisInstr *Instr, uint8 pos, uint8 Size)
{
	// Instr->DisType.Arg[pos].regSize = Size;
	Instr->DisType.Arg[pos].regBase = Instr->DisHex.ModRM.ctx.RM;
	Instr->DisType.Arg[pos].regBase |= Instr->DisHex.Rex.ctx.B ? 8 : 0;
	// Instr->DisType.Arg[pos].regBase |= Instr->DisHex.Rex.ctx.R ? 8 : 0;
	Instr->DisType.Arg[pos].use_regBase = TRUE;
	return SUCESS;
}
uint64 SetSymbol(DisInstr *Instr, uint8 pos)
{
	Instr->DisType.Arg[pos].use_ptr = TRUE;
	Instr->DisType.Arg[pos].use_seg = TRUE;
	Instr->DisType.Arg[pos].use_bra = TRUE;
	return SUCESS;
}

uint64 DisArgSIB(DisInstr *Instr, OpcodeMap *map, uint8 pos)
{
	switch (Instr->DisHex.SIB.ctx.Scale)
	{
	case 0b00:
	{
		if (Instr->DisHex.SIB.ctx.Base == 0b101)
		{
			switch (Instr->DisHex.ModRM.ctx.Mod)
			{
			case 0b00:
			{
				// Instr->DisType.Arg[pos].use_disp = TRUE;
				Instr->DisType.Arg[pos].use_imme = TRUE;
				SetImme(Instr, pos, Bit32);
				break;
			}
			case 0b01:
			{
				SibSetBaseReg(Instr, pos, Instr->Ex.Dsize);
				break;
			}
			case 0b10:
			{
				SibSetBaseReg(Instr, pos, Instr->Ex.Dsize);
				break;
			}
			default:
				break;
			}
		}
		else
		{
			SibSetBaseReg(Instr, pos, Instr->Ex.Asize);
		}
		if (Instr->DisHex.SIB.ctx.Index != 0b100)
		{
			SibSetIndexReg(Instr, pos, Instr->Ex.Asize);
		}
		break;
	}
	case 0b01:
	{
		if (Instr->DisHex.SIB.ctx.Base == 0b101)
		{
			switch (Instr->DisHex.ModRM.ctx.Mod)
			{
			case 0b00:
			{
				Instr->DisType.Arg[pos].use_disp = TRUE;
				SetDisp(Instr, pos, Bit32);
				break;
			}
			case 0b01:
			{
				SibSetBaseReg(Instr, pos, Instr->Ex.Dsize);
				break;
			}
			case 0b10:
			{
				SibSetBaseReg(Instr, pos, Instr->Ex.Dsize);
				break;
			}
			default:
				break;
			}
		}
		else
		{
			SibSetBaseReg(Instr, pos, Instr->Ex.Dsize);
		}
		if (Instr->DisHex.SIB.ctx.Index != 0b100)
		{
			SibSetIndexReg(Instr, pos, Instr->Ex.Asize);
			Instr->DisType.Arg[pos].mulSize = 2;
			Instr->DisType.Arg[pos].use_mul = TRUE;
		}
		break;
	}
	case 0b10:
	{
		if (Instr->DisHex.SIB.ctx.Base == 0b101)
		{
			switch (Instr->DisHex.ModRM.ctx.Mod)
			{
			case 0b00:
			{
				Instr->DisType.Arg[pos].use_disp = TRUE;
				SetDisp(Instr, pos, Bit32);
				break;
			}
			case 0b01:
			{
				SibSetBaseReg(Instr, pos, Instr->Ex.Dsize);
				break;
			}
			case 0b10:
			{
				SibSetBaseReg(Instr, pos, Instr->Ex.Dsize);
				break;
			}
			default:
				break;
			}
		}
		else
		{
			SibSetBaseReg(Instr, pos, Instr->Ex.Dsize);
		}
		if (Instr->DisHex.SIB.ctx.Index != 0b100)
		{
			SibSetIndexReg(Instr, pos, Instr->Ex.Asize);
			Instr->DisType.Arg[pos].mulSize = 4;
			Instr->DisType.Arg[pos].use_mul = TRUE;
		}
		break;
	}
	case 0b11:
	{
		if (Instr->DisHex.SIB.ctx.Base == 0b101)
		{
			switch (Instr->DisHex.ModRM.ctx.Mod)
			{
			case 0b00:
			{
				Instr->DisType.Arg[pos].use_disp = TRUE;
				SetDisp(Instr, pos, Bit32);
				break;
			}
			case 0b01:
			{
				SibSetBaseReg(Instr, pos, Instr->Ex.Dsize);
				break;
			}
			case 0b10:
			{
				SibSetBaseReg(Instr, pos, Instr->Ex.Dsize);
				break;
			}
			default:
				break;
			}
		}
		else
		{
			SibSetBaseReg(Instr, pos, Instr->Ex.Dsize);
		}
		if (Instr->DisHex.SIB.ctx.Index != 0b100)
		{
			SibSetIndexReg(Instr, pos, Instr->Ex.Asize);
			Instr->DisType.Arg[pos].mulSize = 8;
			Instr->DisType.Arg[pos].use_mul = TRUE;
		}
		break;
	}
	default:
		break;
	}
	return SUCESS;
}
uint64 DisArgMordRM(DisInstr *Instr, OpcodeMap *map, uint8 pos)
{
	Instr->DisType.Arg[pos].regSize = Instr->Ex.Asize;

	switch (Instr->DisHex.ModRM.ctx.Mod)
	{
	case 0b00:
	{
		SetSymbol(Instr, pos);

		if (Instr->DisHex.ModRM.ctx.RM == 0b100)
		{
			DisArgSIB(Instr, map, pos);
		}
		else if (Instr->DisHex.ModRM.ctx.RM == 0b101)
		{
			// if (map->OpType == Op_Jcc && map->OpName == J_NEAR_JMP)
			// {
			// 	SetImme(Instr, pos, Bit32);
			// 	Instr->DisType.Arg[pos].use_imme = TRUE;
			// }
			// else
			// {
			SetDisp(Instr, pos, Bit32);
			Instr->DisType.Arg[pos].use_addr = TRUE;
			//}
		}
		else
		{
			ModrmSetBaseReg(Instr, pos, GetArgSize(Instr, Instr->Ex.pMap->Arg->s.lo));
		}
		break;
	}
	case 0b01:
	{
		SetSymbol(Instr, pos);

		if (Instr->DisHex.ModRM.ctx.RM == 0b100)
		{
			DisArgSIB(Instr, map, pos);
		}
		else
		{
			ModrmSetBaseReg(Instr, pos, GetArgSize(Instr, Instr->Ex.pMap->Arg->s.lo));
		}

		Instr->DisType.Arg[pos].use_disp = TRUE;
		SetDisp(Instr, pos, Bit8);

		break;
	}
	case 0b10:
	{
		SetSymbol(Instr, pos);

		if (Instr->DisHex.ModRM.ctx.RM == 0b100)
		{
			DisArgSIB(Instr, map, pos);
		}
		else
		{
			Instr->DisType.Arg[pos].regSize = Instr->Ex.Asize;
			// map->InstAttr == Up_f64 ? Instr->Ex.Asize : GetArgSize(Instr, map->Arg[pos].s.lo);
			ModrmSetBaseReg(Instr, pos, GetArgSize(Instr, Instr->Ex.pMap->Arg->s.lo));
		}

		Instr->DisType.Arg[pos].use_disp = TRUE;
		SetDisp(Instr, pos, Bit32);
		break;
	}
	case 0b11:
	{
		Instr->DisType.Arg[pos].regSize = map->InstAttr == Up_f64 ? Instr->Ex.Asize : GetArgSize(Instr, map->Arg[pos].s.lo);
		ModrmSetBaseReg(Instr, pos, GetArgSize(Instr, Instr->Ex.pMap->Arg->s.lo));
		break;
	}
	default:
		break;
	}
	return SUCESS;
}
uint64 DisArgParam(DisInstr *Instr, OpcodeMap *map, int8 pos)
{
	uint8 size = 0;

	switch (map->Arg[pos].s.hi)
	{
	case A:
	{
		SetImme(Instr, pos, Bit32);
		Instr->DisType.Arg[pos].use_imme = TRUE;
		Instr->DisType.Flags.Sel = TRUE;
		Instr->DisHex.Selector = *(uint16 *)(Instr->Ex.CodeRip.u64 + Instr->Ex.instrLen); // ČĄŇťďż˝ďż˝ďż˝ďż˝ďż˝ďż˝ÎŞďż˝ďż˝ŃĄďż˝ďż˝ďż˝ďż˝
		Instr->Ex.instrLen += 2;
		break;
	}
	case X:
	{
		Instr->DisType.Arg[pos].regSize = Instr->Ex.Asize;
		Instr->DisType.Arg[pos].ptrType = GetArgSize(Instr, map->Arg[pos].s.lo);
		Instr->DisType.Arg[pos].regBase = R_rDI - R_rAX;
		Instr->DisType.Arg[pos].use_regBase = TRUE;
		Instr->DisType.Arg[pos].use_ptr = TRUE;
		Instr->DisType.Arg[pos].use_seg = TRUE;
		Instr->DisType.Arg[pos].use_bra = TRUE;
		break;
	}
	case Y:
	{
		Instr->DisType.Arg[pos].regSize = Instr->Ex.Asize;
		Instr->DisType.Arg[pos].ptrType = GetArgSize(Instr, map->Arg[pos].s.lo);
		Instr->DisType.Arg[pos].regBase = R_rDI - R_rAX;
		Instr->DisType.Arg[pos].use_regBase = TRUE;
		Instr->DisType.Arg[pos].use_ptr = TRUE;
		Instr->DisType.Arg[pos].use_seg = TRUE;
		Instr->DisType.Arg[pos].use_bra = TRUE;
		break;
	}
	case O:
	{
		Instr->DisType.ctx.immeSize = Instr->Ex.Asize;
		Instr->DisHex.Imme[pos].imm64 = GetDisp(Instr, Instr->DisType.ctx.immeSize);
		Instr->DisType.Flags.imme = TRUE;
		Instr->DisType.Arg[pos].use_imme = TRUE;

		Instr->DisType.Arg[pos].ptrType = GetArgSize(Instr, map->Arg[pos].s.lo);
		Instr->DisType.Arg[pos].use_ptr = TRUE;
		Instr->DisType.Arg[pos].use_bra = TRUE;
		Instr->DisType.Arg[pos].use_seg = TRUE;

		Instr->Ex.instrLen += Instr->DisType.ctx.immeSize;
		break;
	}
	case M:
	{
		Instr->DisType.Arg[pos].ptrType = map->Arg[pos].s.lo ? GetArgSize(Instr, map->Arg[pos].s.lo) : Instr->Ex.Asize;
		DisArgMordRM(Instr, map, pos);
		break;
	}
	case E:
	{
		Instr->DisType.Arg[pos].ptrType = map->InstAttr == Up_f64 ? Instr->Ex.Asize : GetArgSize(Instr, map->Arg[pos].s.lo);
		DisArgMordRM(Instr, map, pos);
		break;
	}
	case I:
	{

		size = GetArgSize(Instr, map->Arg[pos].s.lo);
		Instr->DisHex.Imme[pos].imm64 = GetDisp(Instr, size);
		Instr->Ex.instrLen += size;
		// Instr->DisType.ctx.immeSize = size;
		Instr->DisType.Arg[pos].immeSize = size;
		Instr->DisType.Arg[pos].use_imme = TRUE;
		// Instr->DisType.Flags.imme = TRUE;
		break;
	}
	case J:
	{
		Instr->DisType.Arg[pos].use_disp = TRUE;
		Instr->DisType.Arg[pos].dispSize = GetArgSize(Instr, map->Arg[pos].s.lo);
		Instr->DisHex.Disp[pos].disp64 = GetDisp(Instr, Instr->DisType.ctx.dispSize);
		// Instr->DisType.Flags.disp = TRUE;
		Instr->Ex.instrLen += Instr->DisType.Arg[pos].dispSize;

		Instr->Ex.DestAddr.u64 = GetAddr(Instr, Instr->DisHex.Disp[pos].disp64, Instr->DisType.Arg[pos].dispSize);
		Instr->DisType.ctx.addrSize = Instr->Ex.Asize;
		Instr->DisType.Arg[pos].use_addr = TRUE;
		break;
	}
	case G:
	{
		Instr->DisType.Arg[pos].regSize = GetArgSize(Instr, map->Arg[pos].s.lo);
		Instr->DisType.Arg[pos].regBase = Instr->DisHex.ModRM.ctx.Reg;
		Instr->DisType.Arg[pos].regBase |= Instr->DisHex.Rex.ctx.R ? 8 : 0;
		Instr->DisType.Arg[pos].use_regBase = TRUE;
		break;
	}
	case Rr_1:
	case Rr_2:
	case Rr_3:
	case Rr_4:
	case Rr_5:
	case Rr_6:
	case Rr_7:
	case Rr_8:
	{
		Instr->DisType.Arg[pos].regSize = map->InstAttr == Up_d64 ? Instr->Ex.Asize : Instr->Ex.Dsize;
		Instr->DisType.Arg[pos].regBase = map->Arg[pos].s.hi - Rr_1;
		Instr->DisType.Arg[pos].regBase |= Instr->DisHex.Rex.ctx.B ? 8 : 0;
		Instr->DisType.Arg[pos].use_regBase = TRUE;
		break;
	}
	case Rb_1:
	case Rb_2:
	case Rb_3:
	case Rb_4:
	case Rb_5:
	case Rb_6:
	case Rb_7:
	case Rb_8:
	{
		Instr->DisType.Arg[pos].regSize = Bit8;
		Instr->DisType.Arg[pos].regBase = map->Arg[pos].s.hi - Rb_1;
		Instr->DisType.Arg[pos].regBase |= Instr->DisHex.Rex.ctx.B ? 8 : 0;
		Instr->DisType.Arg[pos].use_regBase = TRUE;
		break;
	}
	case R_rAX:
	{
		Instr->DisType.Arg[pos].regSize = Instr->Ex.Dsize;
		// Instr->DisType.Arg[pos].regBase = Instr->DisHex.REX.ctx.W ? 0b1000 : 0;
		Instr->DisType.Arg[pos].regBase |= map->Arg[pos].s.hi - R_rAX;
		Instr->DisType.Arg[pos].use_regBase = TRUE;
		break;
	}
	case R_eAX:
	case R_eCX:
	case R_eDX:
	case R_eBX:
	case R_eSP:
	case R_eBP:
	case R_eSI:
	case R_eDI:
	{
		Instr->DisType.Arg[pos].regSize = Instr->Ex.Dsize;
		Instr->DisType.Arg[pos].regBase = map->Arg[pos].s.hi - R_eAX;
		Instr->DisType.Arg[pos].use_regBase = TRUE;
		break;
	}
	case R_AL:
	case R_CL:
	case R_DL:
	case R_BL:
	{
		Instr->DisType.Arg[pos].regSize = Bit8;
		Instr->DisType.Arg[pos].regBase = map->Arg[pos].s.hi - R_AL;
		Instr->DisType.Arg[pos].use_regBase = TRUE;
		break;
	}
	case R_AX:
	case R_CX:
	case R_DX:
	case R_BX:
	{
		Instr->DisType.Arg[pos].regSize = Bit16;
		Instr->DisType.Arg[pos].regBase = map->Arg[pos].s.hi - R_AX;
		Instr->DisType.Arg[pos].use_regBase = TRUE;
		break;
	}
	case S:
	{
		Instr->DisType.Arg[pos].ptrType = GetArgSize(Instr, map->Arg[pos].s.lo);
		Instr->DisType.Arg[pos].regSize = 0;
		Instr->DisType.Arg[pos].regBase = Instr->DisHex.ModRM.ctx.Reg;
		Instr->DisType.Arg[pos].use_regBase = TRUE;
		break;
	}
	case C:
	{
		Instr->DisType.Arg[pos].regSize = Instr->Ex.mode == Bit64 ? 9 : 5; // ďż˝ďż˝ďż˝ĆźÄ´ďż˝ďż˝ďż˝ďż˝Öˇďż˝ďż˝ďż˝,ďż˝Ýˇďż˝ďż˝ďż˝4ďż˝Ö˝ďż˝ďż˝ďż˝8ďż˝Ö˝Úşďż˝ďż˝ďż˝
		Instr->DisType.Arg[pos].regBase = Instr->DisHex.ModRM.ctx.Reg;
		Instr->DisType.Arg[pos].regBase |= Instr->DisHex.Rex.ctx.R ? 8 : 0;
		Instr->DisType.Arg[pos].use_regBase = TRUE;
		break;
	}
	case D:
	{
		Instr->DisType.Arg[pos].regSize = Instr->Ex.mode == Bit64 ? 10 : 6; // ďż˝ďż˝ďż˝ÔźÄ´ďż˝ďż˝ďż˝ďż˝Öˇďż˝ďż˝ďż˝,ďż˝Ýˇďż˝ďż˝Úżďż˝ďż˝ĆźÄ´ďż˝ďż˝ďż˝ďż˝ďż˝ďż˝ďż˝,ďż˝ďż˝ďż˝Őżďż˝ďż˝ĆźÄ´ďż˝ďż˝ďż˝ [C];
		Instr->DisType.Arg[pos].regBase = Instr->DisHex.ModRM.ctx.Reg;
		Instr->DisType.Arg[pos].regBase |= Instr->DisHex.Rex.ctx.R ? 8 : 0;
		Instr->DisType.Arg[pos].use_regBase = TRUE;
		break;
	}
	case R:
	{
		Instr->DisType.Arg[pos].regSize = Instr->Ex.Asize; // GetArgSize(Instr, map->Arg[pos].s.lo);
		Instr->DisType.Arg[pos].regBase = Instr->DisHex.ModRM.ctx.RM;
		Instr->DisType.Arg[pos].regBase |= Instr->DisHex.Rex.ctx.B ? 8 : 0;
		Instr->DisType.Arg[pos].use_regBase = TRUE;
		break;
	}
	case S_ES:
	case S_CS:
	case S_SS:
	case S_DS:
	case S_FS:
	case S_GS:
	{
		break;
	}
	case P:
	{
		Instr->DisType.Arg[pos].ptrType = map->Arg[pos].s.lo ? GetArgSize(Instr, map->Arg[pos].s.lo) : Instr->Ex.Asize;
		DisArgMordRM(Instr, map, pos);
		break;
	}
	case H:
	{

		break;
	}
	case W:
	{
		Instr->DisType.Arg[pos].ptrType = map->Arg[pos].s.lo ? GetArgSize(Instr, map->Arg[pos].s.lo) : Instr->Ex.Asize;
		DisArgMordRM(Instr, map, pos);
		break;
	}
	case V:
	{
		Instr->DisType.Arg[pos].regSize = 16; // GetArgSize(Instr, map->Arg[pos].s.lo);
		Instr->DisType.Arg[pos].regBase = Instr->DisHex.ModRM.ctx.Reg | (Instr->DisHex.Rex.ctx.R ? 8 : 0);
		Instr->DisType.Arg[pos].use_regBase = TRUE;
		break;
	}
	case Imm1:
	{
		Instr->DisType.Arg[pos].use_imme = TRUE;
		Instr->DisHex.Imme[pos].imm8 = 1;
		break;
	}
	case Imm3:
	{
		Instr->DisType.Arg[pos].use_imme = TRUE;
		Instr->DisHex.Imme[pos].imm8 = 3;
		break;
	}
	default:
		break;
	}
	return SUCESS;
}
uint64 DisArg(DisInstr *Instr, OpcodeMap *map)
{
	for (int8 i = 0; map->Arg[i].attr != 0; i++)
	{
		DisArgParam(Instr, Instr->Ex.pMap, i);
		Instr->DisType.ctx.argc += 1;
	}
	for (int8 i = 0; map->Arg[i].attr != 0; i++)
	{
		if (Instr->DisType.Arg[i].use_disp)
		{
			Instr->Ex.DestAddr.u64 = GetAddr(Instr, Instr->DisHex.Disp[i].disp64, Instr->DisType.Arg[i].dispSize);
			Instr->DisType.ctx.addrSize = Instr->Ex.Asize;
		}
	}

	return SUCESS;
}
uint64 DisArgType(DisInstr *Instr, OpcodeMap *map)
{
	switch (map->ArgType)
	{
	case Arg_ModRM:
	{
		Instr->DisHex.ModRM.value = *(uint8 *)(Instr->Ex.CodeRip.u64 + Instr->Ex.instrLen);
		Instr->Ex.instrLen += 1;
		Instr->DisType.Flags.modrm = TRUE;
		if ((Instr->Ex.mode & 0xFF) >= Bit32)
		{
			if (Instr->DisHex.ModRM.ctx.Mod != 0B11)
			{
				if (Instr->DisHex.ModRM.ctx.RM == 0B100)
				{
					Instr->DisHex.SIB.value = *(uint8 *)(Instr->Ex.CodeRip.u64 + Instr->Ex.instrLen);
					Instr->Ex.instrLen += 1;
					Instr->DisType.Flags.sib = TRUE;
				}
			}
		}
		break;
	}
	case Arg_E_ModRM:
	{
		break;
	}
	case Arg_NoModRM:
	{
		break;
	}
	case Arg_Null:
	{
		break;
	}
	default:
		break;
	}
	return DisArg(Instr, Instr->Ex.pMap);
}
uint64 DiscodeEOP(DisInstr *Instr, OpcodeMap *map)
{
	Instr->DisType.ctx.opType = map->OpType;
	Instr->DisType.ctx.opName = map->OpName;

	return SUCESS;
}
uint64 DiscodeOP(DisInstr *Instr, OpcodeMap *map)
{
	Instr->DisHex.Op.Opcode[Instr->DisType.ctx.oplen] = *(uint8 *)(Instr->Ex.CodeRip.u64 + Instr->Ex.instrLen);
	Instr->DisType.ctx.opType = map->OpType;
	Instr->DisType.ctx.opName = map->OpName;
	Instr->DisType.ctx.oplen += 1;
	Instr->Ex.instrLen += 1;

	return SUCESS;
}

uint64 GetHexInstr(uint8 *StrOut, uint8 *begin, uint8 *StrIn, uint8 copyLen)
{
	uint8 tempHigh, tempLow;

	for (uint8 i = 0; i < copyLen; i++)
	{
		tempHigh = (StrIn)[i] >> 4;
		tempLow = (StrIn)[i] & 0x0F;
		StrOut[(*begin)++] = Hex[tempHigh];
		StrOut[(*begin)++] = Hex[tempLow];
	}
	return 0;
}
uint64 GetStrAddr(uint8 *StrOut, uint8 *begin, uint64 imme, uint8 len)
{
	uint8 tempHigh, tempLow;
	for (int i = 1; i <= len; i++)
	{
		tempHigh = ((uint8 *)&imme)[len - i] >> 4;
		tempLow = ((uint8 *)&imme)[len - i] & 0x0F;
		StrOut[(*begin)++] = Hex[tempHigh];
		StrOut[(*begin)++] = Hex[tempLow];
	}

	return 0;
}
uint64 GetStrImmeWithSym(uint8 *StrOut, uint8 *begin, uint64 imme, uint8 len)
{
	char str[0x20] = {0};
	// size_t count = 0;
	uint64 bits = MaxBit[len];
	if (imme & (1ull << (len * 8 - 1)))
	{
		_i64toa_s((~imme + 1) & bits, str, 0x12, 16);
		StrCopy(StrOut, begin, "-0x");
	}
	else
	{
		_i64toa_s(imme, str, 0x12, 16);
		StrCopy(StrOut, begin, "+0x");
	}
	// char *Upstr = strupr(str);
	StrCopy(StrOut, begin, str);

	return 0;
}
uint64 GetStrImme(uint8 *StrOut, uint8 *begin, uint64 imme, uint8 len)
{
	char str[0x20] = {0};
	_i64toa_s(imme, str, 0x12, 16);
	// char* Upstr = strupr(str);
	StrCopy(StrOut, begin, "0x");
	StrCopy(StrOut, begin, str);
	return 0;
}
uint64 StrCopy(uint8 *StrOut, uint8 *begin, uint8 *StrIn)
{
	while (*StrIn != '\0')
	{
		StrOut[(*begin)++] = *StrIn++;
	}
	StrOut[*begin] = 0;
	return *begin;
}

OpcodeMap *GetMap(DisInstr *Instr, uint8 code)
{
	return &OneByte[code];
}

OpcodeMap *GetGrpMap(DisInstr *Instr, OpcodeMap *map)
{
	OpcodeMap *newMap = NULL;

	Instr->DisHex.Op.Opcode[Instr->DisType.ctx.oplen++] = *(uint8 *)(Instr->Ex.CodeRip.u64 + Instr->Ex.instrLen);
	Instr->Ex.instrLen += 1;
	Instr->DisHex.ModRM.value = *(uint8 *)(Instr->Ex.CodeRip.u64 + Instr->Ex.instrLen);
	Instr->Ex.instrLen += 1;
	Instr->DisType.Flags.modrm = TRUE;
	Instr->DisType.Flags.ExModRM = TRUE;

	if (Instr->DisHex.ModRM.ctx.Mod != 0B11)
	{
		if (Instr->DisHex.ModRM.ctx.RM == 0B100)
		{
			Instr->DisHex.SIB.value = *(uint8 *)(Instr->Ex.CodeRip.u64 + Instr->Ex.instrLen);
			Instr->Ex.instrLen += 1;
			Instr->DisType.Flags.sib = TRUE;
		}
	}
	switch (map->InstAttr)
	{
	case Grp_1:
	{
		return &(((OpcodeMap(*)[8])map->Extend)[map->code - 0x80][Instr->DisHex.ModRM.ctx.Reg]);
	}
	case Grp_2:
	{
		switch (map->code)
		{
		case 0xC0:
		{
			return &(((OpcodeMap(*)[8])map->Extend)[0][Instr->DisHex.ModRM.ctx.Reg]);
		}
		case 0xC1:
		{
			return &(((OpcodeMap(*)[8])map->Extend)[1][Instr->DisHex.ModRM.ctx.Reg]);
		}
		case 0xD0:
		{
			return &(((OpcodeMap(*)[8])map->Extend)[2][Instr->DisHex.ModRM.ctx.Reg]);
		}
		case 0xD1:
		{
			return &(((OpcodeMap(*)[8])map->Extend)[3][Instr->DisHex.ModRM.ctx.Reg]);
		}
		case 0xD2:
		{
			return &(((OpcodeMap(*)[8])map->Extend)[4][Instr->DisHex.ModRM.ctx.Reg]);
		}
		case 0xD3:
		{
			return &(((OpcodeMap(*)[8])map->Extend)[5][Instr->DisHex.ModRM.ctx.Reg]);
		}
		default:
			return NULL;
		}
	}
	case Grp_3:
	{
		return &(((OpcodeMap(*)[8])map->Extend)[map->code - 0xF6][Instr->DisHex.ModRM.ctx.Reg]);
	}
	case Grp_4:
	{
		return &(((OpcodeMap(*)[8])map->Extend)[0][Instr->DisHex.ModRM.ctx.Reg]);
	}
	case Grp_5:
	{
		return &(((OpcodeMap(*)[8])map->Extend)[0][Instr->DisHex.ModRM.ctx.Reg]);
	}
	case Grp_6:
	{
		return &(((OpcodeMap(*)[8])map->Extend)[0][Instr->DisHex.ModRM.ctx.Reg]);
	}
	case Grp_7:
	{
		if (Instr->DisHex.ModRM.ctx.Mod == 0b11)
		{
			return &(((OpcodeMap(*)[8])map->Extend)[Instr->DisHex.ModRM.ctx.RM + 1][Instr->DisHex.ModRM.ctx.Reg]);
		}
		else
		{
			return &(((OpcodeMap(*)[8])map->Extend)[0][Instr->DisHex.ModRM.ctx.Reg]);
		}
	}
	case Grp_8:
	{
		return &(((OpcodeMap(*)[8])map->Extend)[0][Instr->DisHex.ModRM.ctx.Reg]);
	}
	case Grp_9:
	{
		if (Instr->DisHex.ModRM.ctx.Mod != 0b11)
		{
			if (Instr->DisHex.Pre.type == 0)
			{
				return &(((OpcodeMap(*)[8])map->Extend)[0][Instr->DisHex.ModRM.ctx.Reg]);
			}
			else if (Instr->DisHex.Pre.type == Pre_66)
			{
				return &(((OpcodeMap(*)[8])map->Extend)[1][Instr->DisHex.ModRM.ctx.Reg]);
			}
			else if (Instr->DisHex.Pre.type == Pre_F3)
			{
				return &(((OpcodeMap(*)[8])map->Extend)[2][Instr->DisHex.ModRM.ctx.Reg]);
			}
		}
		else
		{
			if (Instr->DisHex.Pre.type == 0)
			{
				return &(((OpcodeMap(*)[8])map->Extend)[3][Instr->DisHex.ModRM.ctx.Reg]);
			}

			else if (Instr->DisHex.Pre.type == Pre_F3)
			{
				return &(((OpcodeMap(*)[8])map->Extend)[4][Instr->DisHex.ModRM.ctx.Reg]);
			}
		}
		return NULL;
	}
	case Grp_10:
	{
		return &(((OpcodeMap *)map->Extend)[0]);
	}
	case Grp_11:
	{

		if (Instr->DisHex.ModRM.ctx.Mod == 0b11)
		{
			if (Instr->DisHex.ModRM.ctx.Reg == 0b111 && Instr->DisHex.ModRM.ctx.RM == 0b000)
			{
				return &(((OpcodeMap(*)[8])map->Extend)[map->code - 0xC6][1]);
			}
		}
		if (Instr->DisHex.ModRM.ctx.Reg == 0b000)
		{
			return &(((OpcodeMap(*)[8])map->Extend)[map->code - 0xC6][Instr->DisHex.ModRM.ctx.Reg]);
		}
		return NULL;
	}
	case Grp_12:
	{
		if (Instr->DisHex.ModRM.ctx.Mod == 0b11)
		{
			if (Instr->DisHex.Pre.type == 0)
			{
				return &(((OpcodeMap(*)[8])map->Extend)[0][Instr->DisHex.ModRM.ctx.Reg]);
			}
			else if (Instr->DisHex.Pre.type == Pre_66)
			{
				return &(((OpcodeMap(*)[8])map->Extend)[1][Instr->DisHex.ModRM.ctx.Reg]);
			}
		}
		return NULL;
	}
	case Grp_13:
	{
		if (Instr->DisHex.ModRM.ctx.Mod == 0b11)
		{
			if (Instr->DisHex.Pre.type == 0)
			{
				return &(((OpcodeMap(*)[8])map->Extend)[0][Instr->DisHex.ModRM.ctx.Reg]);
			}
			else if (Instr->DisHex.Pre.type == Pre_66)
			{
				return &(((OpcodeMap(*)[8])map->Extend)[1][Instr->DisHex.ModRM.ctx.Reg]);
			}
		}
		return NULL;
	}
	case Grp_14:
	{
		if (Instr->DisHex.ModRM.ctx.Mod == 0b11)
		{
			if (Instr->DisHex.Pre.type == 0)
			{
				return &(((OpcodeMap(*)[8])map->Extend)[0][Instr->DisHex.ModRM.ctx.Reg]);
			}
			else if (Instr->DisHex.Pre.type == Pre_66)
			{
				return &(((OpcodeMap(*)[8])map->Extend)[1][Instr->DisHex.ModRM.ctx.Reg]);
			}
		}
		return NULL;
	}
	case Grp_15:
	{
		if (Instr->DisHex.ModRM.ctx.Mod != 0b11)
		{
			return &(((OpcodeMap(*)[8])map->Extend)[0][Instr->DisHex.ModRM.ctx.Reg]);
		}
		else
		{
			if (Instr->DisHex.Pre.type == 0)
			{
				return &(((OpcodeMap(*)[8])map->Extend)[1][Instr->DisHex.ModRM.ctx.Reg]);
			}
			else if (Instr->DisHex.Pre.type == Pre_F3)
			{
				return &(((OpcodeMap(*)[8])map->Extend)[2][Instr->DisHex.ModRM.ctx.Reg]);
			}
		}
		return NULL;
	}
	case Grp_16:
	{
		if (Instr->DisHex.ModRM.ctx.Mod != 0b11)
		{
			return &(((OpcodeMap(*)[8])map->Extend)[0][Instr->DisHex.ModRM.ctx.Reg]);
		}
		return NULL;
	}
	case Grp_1A:
	{
		return &(((OpcodeMap *)map->Extend)[Instr->DisHex.ModRM.ctx.Reg]);
	}
	default:
		newMap = &(((OpcodeMap *)map->Extend)[Instr->DisHex.ModRM.ctx.Reg]);
		break;
	}
	return newMap;
}
uint64 DisPrefixes(DisInstr *Instr, OpcodeMap *map)
{
	switch (map->InstAttr)
	{
	case P_Grp1:
	{
		// 0xF0,0xF2,0xF3
		// 0xF2,0xF3ďźäšĺ?äťĽćŻćŠĺąćäť¤ççźç ?
		Instr->DisType.ctx.preName = map->OpName;
		Instr->DisType.ctx.preType = Op_Pre;
		if (map->code == 0xF2)
		{
			Instr->DisHex.Pre.type |= 0b100;
		}
		else if (map->code == 0xF3)
		{
			Instr->DisHex.Pre.type |= 0b010;
		}
		break;
	}
	case P_Grp2:
	{
		// 0x26,0x2E,0x36,0x3E,0x64,0x65
		Instr->DisType.Flags.seg = TRUE;
		Instr->DisType.ctx.preSeg = map->Arg->s.hi;
		break;
	}
	case P_Grp3:
	{
		// 0x66 ćšĺć°ćŽĺŽ˝ĺşŚďźäšĺ?äťĽćŻćŠĺąçćäť¤çźç ?
		if (Instr->DisHex.Pre.type & 1)
		{
			break;
		}
		if (Instr->Ex.Dsize == Bit32)
			Instr->Ex.Dsize = Bit16;
		else
			Instr->Ex.Dsize = Bit32;
		Instr->DisHex.Pre.type |= 0b001;
		break;
	}
	case P_Grp4:
	{
		// 0x67
		// if (Instr->Ex.Asize == Bit32)
		// 	Instr->Ex.Asize = Bit16;
		// else
		// 	Instr->Ex.Asize = Bit32;

		break;
	}
	default:
		break;
	}
	Instr->DisType.Flags.pre = TRUE;
	Instr->DisHex.Pre.Pre[Instr->DisHex.Pre.count++] = map->code;
	Instr->Ex.instrLen += 1;
	return TRUE;
}

uint64 SetMap(DisInstr *Instr)
{
	Instr->Ex.pMap = GetMap(Instr, *(uint8 *)Instr->Ex.CodeRip.u64);

_Start:
	if (Instr->Ex.pMap == NULL)
		return ERROR_MAP;

	switch (Instr->Ex.pMap->InstType)
	{
	case Inst_Pre:
	{
		DisPrefixes(Instr, Instr->Ex.pMap);
		Instr->Ex.pMap = GetMap(Instr, *(uint8 *)(Instr->Ex.CodeRip.u64 + Instr->Ex.instrLen));
		goto _Start;
	}
	case Inst_Grp:
	{
		Instr->Ex.pMap = GetGrpMap(Instr, Instr->Ex.pMap);
		goto _Start;
	}
	case Inst_Rex:
	{
		if (Instr->DisType.Flags.rex)
			return ERROR_UD2;

		Instr->DisHex.Rex.value = *(uint8 *)(Instr->Ex.CodeRip.u64 + Instr->Ex.instrLen);
		Instr->DisType.Flags.rex = TRUE;
		Instr->Ex.instrLen += 1;
		if (Instr->DisHex.Rex.ctx.W)
			Instr->Ex.Dsize = Bit64;

		Instr->Ex.pMap = GetMap(Instr, *(uint8 *)(Instr->Ex.CodeRip.u64 + Instr->Ex.instrLen));
		goto _Start;
	}
	case Inst_2Byte:
	{
		Instr->DisHex.Op.Opcode[Instr->DisType.ctx.oplen] = *(uint8 *)(Instr->Ex.CodeRip.u64 + Instr->Ex.instrLen);
		Instr->DisType.ctx.oplen += 1;
		Instr->Ex.instrLen += 1;
		Instr->Ex.pMap = &(((POpcodeMap)(Instr->Ex.pMap->Extend))[*(uint8 *)(Instr->Ex.CodeRip.u64 + Instr->Ex.instrLen)]);
		goto _Start;
	}
	case Inst_ExPre:
	{
		switch (Instr->DisHex.Pre.type)
		{
		case 0: // 0
		{
			Instr->Ex.pMap = &(((POpcodeMap)(Instr->Ex.pMap->Extend))[0]);
			break;
		}
		case 1: // 66
		{
			Instr->Ex.pMap = &(((POpcodeMap)(Instr->Ex.pMap->Extend))[1]);
			break;
		}
		case 2: // F3
		{
			Instr->Ex.pMap = &(((POpcodeMap)(Instr->Ex.pMap->Extend))[2]);
			break;
		}
		case 4: // F2
		{
			Instr->Ex.pMap = &(((POpcodeMap)(Instr->Ex.pMap->Extend))[3]);
			break;
		}
		case 5: // 66&F2
		{
			Instr->Ex.pMap = &(((POpcodeMap)(Instr->Ex.pMap->Extend))[4]);
			break;
		}
		default:
			return ERROR_UD2;
			break;
		}
		goto _Start;
	}
	case Inst_IO64:
	{
		Instr->Ex.pMap = (OpcodeMap *)(Instr->Ex.pMap->Extend) + ((Instr->Ex.mode & 0xFF) == Bit64 ? 1 : 0);
		goto _Start;
	}
	case Inst_I64:
	{
		if (Instr->Ex.mode == Bit64)
			return ERROR_UD2;
		break;
	}
	case Inst_O64:
	{
		if (Instr->Ex.mode != Bit64)
			return ERROR_UD2;
		break;
	} // D64和栈有关，F64和跳转有关
	case Inst_Gen:
	{
		break;
	}
	case Inst_EModRM:
	{
		break;
	}
	case Inst_UD2:
	{
		return ERROR_UD2;
	}
	default:
		return ERROR_UD2;
	}
	return SUCESS;
}

uint64 SetMode(DisInstr *Instr, uint64 ExecRip, uint64 Addr, uint8 mode)
{
	Instr->Ex.mode = mode;
	Instr->Ex.Rip.u64 = Addr ? Addr : ExecRip;
	Instr->Ex.CodeRip.u64 = ExecRip;
	switch (mode)
	{
	case Bit64:
	{
		Instr->Ex.Dsize = Bit32;
		Instr->Ex.Asize = Bit64;
		break;
	}
	case Bit32:
	{
		Instr->Ex.Dsize = Instr->Ex.Asize = Bit32;
		break;
	}
	case Bit16:
	{
		Instr->Ex.Dsize = Instr->Ex.Asize = Bit16;
		break;
	}
	default:
		return ERROR_MODE;
	}
	return SUCESS;
}
uint64 InstrToHex(DisInstr *Instr)
{
	// uint8* Rip = (uint8*)Instr->Ex.Rip.u64;
	uint8 addrlen = Instr->Ex.mode;

	if (Instr->Ex.Rip.u64)
	{
		GetStrAddr(Instr->DisAsm.sAddr.str, &Instr->DisAsm.sAddr.len, Instr->Ex.Rip.u64, addrlen);
	}
	if (Instr->DisType.Flags.pre)
	{
		for (uint8 i = 0; i < Instr->DisHex.Pre.count; i++)
		{
			GetHexInstr(Instr->DisAsm.sHex.str, &Instr->DisAsm.sHex.len, &Instr->DisHex.Pre.Pre[i], 1);
		}
		StrCopy(Instr->DisAsm.sHex.str, &Instr->DisAsm.sHex.len, ":");
	}
	if (Instr->DisType.Flags.rex)
	{
		GetHexInstr(Instr->DisAsm.sHex.str, &Instr->DisAsm.sHex.len, &Instr->DisHex.Rex.value, 1);
		StrCopy(Instr->DisAsm.sHex.str, &Instr->DisAsm.sHex.len, ":");
	}
	if (Instr->DisType.ctx.oplen)
	{
		GetHexInstr(Instr->DisAsm.sHex.str, &Instr->DisAsm.sHex.len, &Instr->DisHex.Op.Opcode[0], Instr->DisType.ctx.oplen);
	}
	if (Instr->DisType.Flags.modrm)
	{
		GetHexInstr(Instr->DisAsm.sHex.str, &Instr->DisAsm.sHex.len, &Instr->DisHex.ModRM.value, 1);
		if (Instr->DisType.Flags.sib)
		{
			GetHexInstr(Instr->DisAsm.sHex.str, &Instr->DisAsm.sHex.len, &Instr->DisHex.SIB.value, 1);
		}
	}
	StrCopy(Instr->DisAsm.sHex.str, &Instr->DisAsm.sHex.len, " ");

	for (uint8 i = 0; i < 2; i++)
	{
		if (Instr->DisType.Arg[i].use_disp)
		{
			GetHexInstr(Instr->DisAsm.sHex.str, &Instr->DisAsm.sHex.len, (uint8 *)&Instr->DisHex.Disp[i].disp64, Instr->DisType.Arg[i].dispSize);

			StrCopy(Instr->DisAsm.sHex.str, &Instr->DisAsm.sHex.len, " ");
		}
		if (Instr->DisType.Arg[i].use_imme)
		{
			GetHexInstr(Instr->DisAsm.sHex.str, &Instr->DisAsm.sHex.len, (uint8 *)&Instr->DisHex.Imme[i].imm64, Instr->DisType.Arg[i].immeSize);
		}
	}

	if (Instr->DisType.Flags.Sel)
	{
		StrCopy(Instr->DisAsm.sHex.str, &Instr->DisAsm.sHex.len, " ");
		GetHexInstr(Instr->DisAsm.sHex.str, &Instr->DisAsm.sHex.len, (uint8 *)&Instr->DisHex.Selector, Bit16);
	}
	return SUCESS;
}
uint64 InstrToAsm(DisInstr *Instr)
{
	if (Instr->DisType.Flags.pre)
	{
		if (Instr->DisType.ctx.preType == Op_Pre)
		{
			StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, (uint8 *)OpStr[Instr->DisType.ctx.preType][Instr->DisType.ctx.preName]);
			StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, " ");
		}
	}
	if (Instr->DisType.ctx.oplen)
	{
		StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, (uint8 *)OpStr[Instr->DisType.ctx.opType][Instr->DisType.ctx.opName]);
	}
	if (Instr->DisType.Flags.Sel)
	{
		StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, " ");
		GetStrImme(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, Instr->DisHex.Selector, Bit16);
		StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, ":");
	}
	for (uint8 i = 0; i < Instr->DisType.ctx.argc; i++)
	{
		if (i == 0)
			StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, " ");
		if (i >= 1)
			StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, ",");

		if (Instr->DisType.Arg[i].use_ptr)
		{
			StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, (uint8 *)SizePtr[Instr->DisType.Arg[i].ptrType]);
			StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, " ");
		}
		if (Instr->DisType.Arg[i].use_seg)
		{
			if (Instr->DisType.Flags.seg)
			{
				StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, (uint8 *)PreSeg[Instr->DisType.ctx.preSeg - S_ES]);
			}
			else
			{
				StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, (uint8 *)DefSeg[Instr->DisType.Arg[i].regBase & 0b111]);
			}
			StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, ":");
		}
		if (Instr->DisType.Arg[i].use_bra)
		{
			StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, "[");
		}
		if (Instr->DisType.Arg[i].use_regBase)
		{
			Instr->Ex.mode == Bit64
				? StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, (uint8 *)Reg64[Instr->DisType.Arg[i].regSize][Instr->DisType.Arg[i].regBase])
				: StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, (uint8 *)Reg32[Instr->DisType.Arg[i].regSize][Instr->DisType.Arg[i].regBase]);
		}
		if (Instr->DisType.Arg[i].use_regIndex)
		{
			if (Instr->DisType.Arg[i].use_regBase)
				StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, "+");
			if (Instr->Ex.mode == Bit64)
			{
				StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, (uint8 *)Reg64[Instr->DisType.Arg[i].regSize][Instr->DisType.Arg[i].regIndex]);
			}
			else
			{
				StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, (uint8 *)Reg32[Instr->DisType.Arg[i].regSize][Instr->DisType.Arg[i].regIndex]);
			}
		}
		if (Instr->DisType.Arg[i].use_mul)
		{
			StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, "*");
			char str[] = {Instr->DisType.Arg[i].mulSize | 0x30, 0};
			StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, str);
		}
		if (Instr->DisType.Arg[i].use_addr)
		{
			GetStrAddr(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, Instr->Ex.DestAddr.u64, Instr->DisType.ctx.addrSize);
			Instr->Ex.isAddr = TRUE;
		}
		else
		{
			if (Instr->DisType.Arg[i].use_disp)
			{
				GetStrImmeWithSym(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, Instr->DisHex.Disp[i].disp64, Instr->DisType.Arg[i].dispSize);
			}
			if (Instr->DisType.Arg[i].use_imme)
			{
				GetStrImme(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, Instr->DisHex.Imme[i].imm64, Instr->DisType.Arg[i].immeSize);
			}
		}

		if (Instr->DisType.Arg[i].use_bra)
		{
			StrCopy(Instr->DisAsm.sAsm.str, &Instr->DisAsm.sAsm.len, "]");
		}
	}
	return SUCESS;
}
/***************************
 * @brief 反汇编解码.
 * @param Instr IN OUT 结构.
 * @param ExecRip IN 二进制代码的内存地址.
 * @param Addr IN OPTION 反汇编结果以此地址为准,如果是实际内存为地址应填为 0.
 * @param Mode 以什么模式解码(bit16,bit32,bit64).
 * @return 忽略返回值.
 ***************************/
uint64 Decode(DisInstr *Instr, uint64 ExecRip, uint64 Addr, uint8 Mode)
{
	OpcodeMap map = {0};
	uint64 ret = 0;

	ret = SetMode(Instr, ExecRip, Addr, Mode);
	ret = SetMap(Instr);
	if (ret != SUCESS)
		return ret;
	ret = Instr->Ex.pMap->InstType == Inst_EModRM ? DiscodeEOP(Instr, Instr->Ex.pMap) : DiscodeOP(Instr, Instr->Ex.pMap);

	ret = DisArgType(Instr, Instr->Ex.pMap);

	return ret;
}
