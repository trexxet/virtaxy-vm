IF_INSTR(add)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = ADD_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = ADD_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(and)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = AND_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = AND_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
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
			CHECK_PROGRAM_SIZE;
			OPCODE = CALL_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = CALL_NUM_NONE;
			ARG_TO_NUM(arg1.str, &ARG1, &S);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(cmp)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = CMP_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = CMP_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = CMP_NUM_REG;
			ARG_TO_NUM(arg1.str, &ARG1, &S);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
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
			CHECK_PROGRAM_SIZE;
			OPCODE = DEC_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(div)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = DIV_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = DIV_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
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
			CHECK_PROGRAM_SIZE;
			OPCODE = DUMP_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
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
			CHECK_PROGRAM_SIZE;
			OPCODE = IN_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
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
			CHECK_PROGRAM_SIZE;
			OPCODE = INC_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(ja)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JA_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JA_NUM_NONE;
			ARG_TO_NUM(arg1.str, &ARG1, &S);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(jae)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JAE_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JAE_NUM_NONE;
			ARG_TO_NUM(arg1.str, &ARG1, &S);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(jb)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JB_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JB_NUM_NONE;
			ARG_TO_NUM(arg1.str, &ARG1, &S);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(jbe)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JBE_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JBE_NUM_NONE;
			ARG_TO_NUM(arg1.str, &ARG1, &S);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(je)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JE_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JE_NUM_NONE;
			ARG_TO_NUM(arg1.str, &ARG1, &S);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(jg)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JG_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JG_NUM_NONE;
			ARG_TO_NUM(arg1.str, &ARG1, &S);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(jge)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JGE_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JGE_NUM_NONE;
			ARG_TO_NUM(arg1.str, &ARG1, &S);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(jl)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JL_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JL_NUM_NONE;
			ARG_TO_NUM(arg1.str, &ARG1, &S);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(jle)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JLE_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JLE_NUM_NONE;
			ARG_TO_NUM(arg1.str, &ARG1, &S);
			ARG2 = 0;
			ASSEMBLED;
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
			CHECK_PROGRAM_SIZE;
			OPCODE = JMP_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JMP_NUM_NONE;
			ARG_TO_NUM(arg1.str, &ARG1, &S);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(jne)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JNE_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JNE_NUM_NONE;
			ARG_TO_NUM(arg1.str, &ARG1, &S);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(jnz)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JNZ_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JNZ_NUM_NONE;
			ARG_TO_NUM(arg1.str, &ARG1, &S);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(jz)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JZ_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = JZ_NUM_NONE;
			ARG_TO_NUM(arg1.str, &ARG1, &S);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(ld)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = LD_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = LD_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(mod)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = MOD_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = MOD_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(mov)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = MOV_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = MOV_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(mul)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = MUL_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = MUL_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(nand)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = NAND_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = NAND_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
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
			CHECK_PROGRAM_SIZE;
			OPCODE = NOP_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(nor)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = NOR_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = NOR_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
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
			CHECK_PROGRAM_SIZE;
			OPCODE = NOT_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(or)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = OR_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = OR_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
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
			CHECK_PROGRAM_SIZE;
			OPCODE = OUT_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
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
			CHECK_PROGRAM_SIZE;
			OPCODE = POP_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = POP_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(popf)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = POPF_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
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
			CHECK_PROGRAM_SIZE;
			OPCODE = PUSH_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = PUSH_NUM_NONE;
			ARG_TO_NUM(arg1.str, &ARG1, &S);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(pushf)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = PUSHF_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
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
			CHECK_PROGRAM_SIZE;
			OPCODE = RET_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(rtl)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = RTL_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = RTL_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(rtr)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = RTR_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = RTR_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(sadd)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SADD_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(sand)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SAND_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(sdec)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SDEC_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(sdiv)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SDIV_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(shl)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SHL_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SHL_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(shr)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SHR_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SHR_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(sinc)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SINC_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(smod)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SMOD_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(smov)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SMOV_REG_NONE;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(smul)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SMUL_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(snand)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SNAND_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(snor)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SNOR_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(snot)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SNOT_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(sor)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SOR_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(srtl)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SRTL_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(srtr)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SRTR_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(sshl)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SSHL_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(sshr)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SSHR_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(ssub)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SSUB_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(st)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = ST_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = ST_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	if (arg1.type == NUM)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = ST_NUM_NUM;
			ARG_TO_NUM(arg1.str, &ARG1, &S);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = ST_NUM_REG;
			ARG_TO_NUM(arg1.str, &ARG1, &S);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(sub)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SUB_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SUB_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(sxnor)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SXNOR_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(sxor)
{
	if (arg1.type == NONE)
	{
		if (arg2.type == NONE)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = SXOR_NONE_NONE;
			ARG1 = 0;
			ARG2 = 0;
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(test)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = TEST_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = TEST_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(xnor)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = XNOR_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = XNOR_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

IF_INSTR(xor)
{
	if (arg1.type == REG)
	{
		if (arg2.type == NUM)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = XOR_REG_NUM;
			ARG1 = REG_NUM(arg1.str);
			ARG_TO_NUM(arg2.str, &ARG2, &S);
			ASSEMBLED;
		}
		if (arg2.type == REG)
		{
			CHECK_PROGRAM_SIZE;
			OPCODE = XOR_REG_REG;
			ARG1 = REG_NUM(arg1.str);
			ARG2 = REG_NUM(arg2.str);
			ASSEMBLED;
		}
		INVALID_ARG2;
	}
	INVALID_ARG1;
}

