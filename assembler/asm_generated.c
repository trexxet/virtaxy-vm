IF_INSTR(add)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = ADD_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = ADD_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(and)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = AND_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = AND_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(be)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == REG)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BE_REG_REG_REG;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = REG_NUM(arg3.str);
				ASSEMBLED;
			}
			if (arg3.type == NUM)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BE_REG_REG_NUM;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG_TO_NUM(arg3.str, &ARG3, &S);
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == REG)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BE_REG_NUM_REG;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = REG_NUM(arg3.str);
				ASSEMBLED;
			}
			if (arg3.type == NUM)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BE_REG_NUM_NUM;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG_TO_NUM(arg3.str, &ARG3, &S);
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(bg)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == REG)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BG_REG_REG_REG;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = REG_NUM(arg3.str);
				ASSEMBLED;
			}
			if (arg3.type == NUM)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BG_REG_REG_NUM;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG_TO_NUM(arg3.str, &ARG3, &S);
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == REG)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BG_REG_NUM_REG;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = REG_NUM(arg3.str);
				ASSEMBLED;
			}
			if (arg3.type == NUM)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BG_REG_NUM_NUM;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG_TO_NUM(arg3.str, &ARG3, &S);
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(bge)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == REG)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BGE_REG_REG_REG;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = REG_NUM(arg3.str);
				ASSEMBLED;
			}
			if (arg3.type == NUM)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BGE_REG_REG_NUM;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG_TO_NUM(arg3.str, &ARG3, &S);
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == REG)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BGE_REG_NUM_REG;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = REG_NUM(arg3.str);
				ASSEMBLED;
			}
			if (arg3.type == NUM)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BGE_REG_NUM_NUM;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG_TO_NUM(arg3.str, &ARG3, &S);
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(bl)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == REG)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BL_REG_REG_REG;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = REG_NUM(arg3.str);
				ASSEMBLED;
			}
			if (arg3.type == NUM)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BL_REG_REG_NUM;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG_TO_NUM(arg3.str, &ARG3, &S);
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == REG)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BL_REG_NUM_REG;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = REG_NUM(arg3.str);
				ASSEMBLED;
			}
			if (arg3.type == NUM)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BL_REG_NUM_NUM;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG_TO_NUM(arg3.str, &ARG3, &S);
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(ble)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == REG)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BLE_REG_REG_REG;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = REG_NUM(arg3.str);
				ASSEMBLED;
			}
			if (arg3.type == NUM)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BLE_REG_REG_NUM;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG_TO_NUM(arg3.str, &ARG3, &S);
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == REG)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BLE_REG_NUM_REG;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = REG_NUM(arg3.str);
				ASSEMBLED;
			}
			if (arg3.type == NUM)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BLE_REG_NUM_NUM;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG_TO_NUM(arg3.str, &ARG3, &S);
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(bne)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == REG)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BNE_REG_REG_REG;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = REG_NUM(arg3.str);
				ASSEMBLED;
			}
			if (arg3.type == NUM)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BNE_REG_REG_NUM;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG_TO_NUM(arg3.str, &ARG3, &S);
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == REG)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BNE_REG_NUM_REG;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = REG_NUM(arg3.str);
				ASSEMBLED;
			}
			if (arg3.type == NUM)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BNE_REG_NUM_NUM;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG_TO_NUM(arg3.str, &ARG3, &S);
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(bnz)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BNZ_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BNZ_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(bz)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BZ_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = BZ_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(call)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = CALL_REG_NONE_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = 0;
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NONE)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = CALL_NUM_NONE_NONE;
				ARG_TO_NUM(arg1.str, &ARG1, &S);
				ARG2 = 0;
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(dec)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = DEC_REG_NONE_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = 0;
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(div)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = DIV_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = DIV_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(dump)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = DUMP_NONE_NONE_NONE;
				ARG1 = 0;
				ARG2 = 0;
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(hlt)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = HLT_NONE_NONE_NONE;
				ARG1 = 0;
				ARG2 = 0;
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(in)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = IN_REG_NONE_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = 0;
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(inc)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = INC_REG_NONE_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = 0;
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(jmp)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = JMP_REG_NONE_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = 0;
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NONE)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = JMP_NUM_NONE_NONE;
				ARG_TO_NUM(arg1.str, &ARG1, &S);
				ARG2 = 0;
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(ld)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = LD_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = LD_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(mod)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = MOD_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = MOD_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(mov)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = MOV_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = MOV_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(mul)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = MUL_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = MUL_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(nand)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = NAND_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = NAND_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(nop)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = NOP_NONE_NONE_NONE;
				ARG1 = 0;
				ARG2 = 0;
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(nor)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = NOR_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = NOR_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(not)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = NOT_REG_NONE_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = 0;
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(or)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = OR_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = OR_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(out)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = OUT_REG_NONE_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = 0;
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(pop)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = POP_REG_NONE_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = 0;
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = POP_NONE_NONE_NONE;
				ARG1 = 0;
				ARG2 = 0;
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(push)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = PUSH_REG_NONE_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = 0;
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NONE)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = PUSH_NUM_NONE_NONE;
				ARG_TO_NUM(arg1.str, &ARG1, &S);
				ARG2 = 0;
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(ret)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = RET_NONE_NONE_NONE;
				ARG1 = 0;
				ARG2 = 0;
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(rtl)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = RTL_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = RTL_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(rtr)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = RTR_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = RTR_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(shl)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = SHL_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = SHL_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(shr)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = SHR_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = SHR_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(st)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = ST_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = ST_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = ST_NUM_REG_NONE;
				ARG_TO_NUM(arg1.str, &ARG1, &S);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = ST_NUM_NUM_NONE;
				ARG_TO_NUM(arg1.str, &ARG1, &S);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(sub)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = SUB_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = SUB_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(xnor)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = XNOR_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = XNOR_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(xor)
{
	if (arg1.type == REG)
	{
		if (arg2.type == REG)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = XOR_REG_REG_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG2 = REG_NUM(arg2.str);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		if (arg2.type == NUM)
		{
			if (arg3.type == NONE)
			{
				CHECK_PROGRAM_SIZE(OPSIZE);
				OPCODE = XOR_REG_NUM_NONE;
				ARG1 = REG_NUM(arg1.str);
				ARG_TO_NUM(arg2.str, &ARG2, &S);
				ARG3 = 0;
				ASSEMBLED;
			}
			INVALID_ARG3;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

