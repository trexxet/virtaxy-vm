case NOP_NONE_NONE_NONE:
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case LD_REG_NUM_NONE:
	WRITE_REG(arg1, READ_MEM(arg2));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case LD_REG_REG_NONE:
	WRITE_REG(arg1, READ_MEM(READ_REG(arg2)));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case ST_NUM_NUM_NONE:
	WRITE_MEM(arg1, arg2);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case ST_NUM_REG_NONE:
	WRITE_MEM(arg1, READ_REG(arg2));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case ST_REG_NUM_NONE:
	WRITE_MEM(READ_REG(arg1), arg2);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case ST_REG_REG_NONE:
	WRITE_MEM(READ_REG(arg1), READ_REG(arg2));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case MOV_REG_NUM_NONE:
	WRITE_REG(arg1, arg2);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case MOV_REG_REG_NONE:
	WRITE_REG(arg1, READ_REG(arg2));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case INC_REG_NONE_NONE:
	WRITE_REG(arg1, READ_REG(arg1) + 1);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case DEC_REG_NONE_NONE:
	WRITE_REG(arg1, READ_REG(arg1) - 1);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case ADD_REG_NUM_NONE:
	WRITE_REG(arg1, READ_REG(arg1) + arg2);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case ADD_REG_REG_NONE:
	WRITE_REG(arg1, READ_REG(arg1) + READ_REG(arg2));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case SUB_REG_NUM_NONE:
	WRITE_REG(arg1, READ_REG(arg1) - arg2);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case SUB_REG_REG_NONE:
	WRITE_REG(arg1, READ_REG(arg1) - READ_REG(arg2));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case MUL_REG_NUM_NONE:
	WRITE_REG(arg1, READ_REG(arg1) * arg2);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case MUL_REG_REG_NONE:
	WRITE_REG(arg1, READ_REG(arg1) * READ_REG(arg2));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case DIV_REG_NUM_NONE:
	WRITE_REG(arg1, READ_REG(arg1) / arg2);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case DIV_REG_REG_NONE:
	WRITE_REG(arg1, READ_REG(arg1) / READ_REG(arg2));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case MOD_REG_NUM_NONE:
	WRITE_REG(arg1, READ_REG(arg1) % arg2);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case MOD_REG_REG_NONE:
	WRITE_REG(arg1, READ_REG(arg1) % READ_REG(arg2));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case AND_REG_NUM_NONE:
	WRITE_REG(arg1, READ_REG(arg1) & arg2);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case AND_REG_REG_NONE:
	WRITE_REG(arg1, READ_REG(arg1) & READ_REG(arg2));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case NAND_REG_NUM_NONE:
	WRITE_REG(arg1, ~(READ_REG(arg1) & arg2));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case NAND_REG_REG_NONE:
	WRITE_REG(arg1, ~(READ_REG(arg1) & READ_REG(arg2)));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case OR_REG_NUM_NONE:
	WRITE_REG(arg1, READ_REG(arg1) | arg2);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case OR_REG_REG_NONE:
	WRITE_REG(arg1, READ_REG(arg1) | READ_REG(arg2));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case NOR_REG_NUM_NONE:
	WRITE_REG(arg1, ~(READ_REG(arg1) | arg2));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case NOR_REG_REG_NONE:
	WRITE_REG(arg1, ~(READ_REG(arg1) | READ_REG(arg2)));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case XOR_REG_NUM_NONE:
	WRITE_REG(arg1, READ_REG(arg1) ^ arg2);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case XOR_REG_REG_NONE:
	WRITE_REG(arg1, READ_REG(arg1) ^ READ_REG(arg2));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case XNOR_REG_NUM_NONE:
	WRITE_REG(arg1, ~(READ_REG(arg1) ^ arg2));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case XNOR_REG_REG_NONE:
	WRITE_REG(arg1, ~(READ_REG(arg1) ^ READ_REG(arg2)));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case NOT_REG_NONE_NONE:
	WRITE_REG(arg1, ~READ_REG(arg1));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case SHL_REG_NUM_NONE:
	WRITE_REG(arg1, READ_REG(arg1) << arg2);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case SHL_REG_REG_NONE:
	WRITE_REG(arg1, READ_REG(arg1) << READ_REG(arg2));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case SHR_REG_NUM_NONE:
	WRITE_REG(arg1, READ_REG(arg1) >> arg2);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case SHR_REG_REG_NONE:
	WRITE_REG(arg1, READ_REG(arg1) >> READ_REG(arg2));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case RTL_REG_NUM_NONE:
	WRITE_REG(arg1, (READ_REG(arg1) << arg2) | (READ_REG(arg1) >> (64 - arg2)));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case RTL_REG_REG_NONE:
	WRITE_REG(arg1, (READ_REG(arg1) << READ_REG(arg2)) | (READ_REG(arg1) >> (64 - READ_REG(arg2))));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case RTR_REG_NUM_NONE:
	WRITE_REG(arg1, (READ_REG(arg1) >> arg2) | (READ_REG(arg1) << (64 - arg2)));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case RTR_REG_REG_NONE:
	WRITE_REG(arg1, (READ_REG(arg1) >> READ_REG(arg2)) | (READ_REG(arg1) << (64 - READ_REG(arg2))));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case PUSH_NUM_NONE_NONE:
	WRITE_REG(SP, READ_REG(SP) - 1);
	WRITE_MEM(READ_REG(SP), arg1);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case PUSH_REG_NONE_NONE:
	WRITE_REG(SP, READ_REG(SP) - 1);
	WRITE_MEM(READ_REG(SP), READ_REG(arg1));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case POP_NONE_NONE_NONE:
	WRITE_REG(SP, READ_REG(SP) + 1);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case POP_REG_NONE_NONE:
	WRITE_REG(arg1, READ_MEM(READ_REG(SP)));
	WRITE_REG(SP, READ_REG(SP) + 1);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case JMP_REG_NONE_NONE:
	WRITE_REG(IP, READ_REG(arg1));
	break;
case JMP_NUM_NONE_NONE:
	WRITE_REG(IP, arg1);
	break;
case BZ_REG_REG_NONE:
	IF (READ_REG(arg1) == 0) WRITE_REG(IP, READ_REG(arg2));
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BZ_REG_NUM_NONE:
	IF (READ_REG(arg1) == 0) WRITE_REG(IP, arg2);
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BNZ_REG_REG_NONE:
	IF (READ_REG(arg1) != 0) WRITE_REG(IP, READ_REG(arg2));
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BNZ_REG_NUM_NONE:
	IF (READ_REG(arg1) != 0) WRITE_REG(IP, arg2);
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BE_REG_REG_REG:
	IF (READ_REG(arg1) == READ_REG(arg2)) WRITE_REG(IP, READ_REG(arg3));
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BE_REG_REG_NUM:
	IF (READ_REG(arg1) == READ_REG(arg2)) WRITE_REG(IP, arg3);
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BE_REG_NUM_REG:
	IF (READ_REG(arg1) == arg2) WRITE_REG(IP, READ_REG(arg3));
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BE_REG_NUM_NUM:
	IF (READ_REG(arg1) == arg2) WRITE_REG(IP, arg3);
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BNE_REG_REG_REG:
	IF (READ_REG(arg1) != READ_REG(arg2)) WRITE_REG(IP, READ_REG(arg3));
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BNE_REG_REG_NUM:
	IF (READ_REG(arg1) != READ_REG(arg2)) WRITE_REG(IP, arg3);
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BNE_REG_NUM_REG:
	IF (READ_REG(arg1) != arg2) WRITE_REG(IP, READ_REG(arg3));
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BNE_REG_NUM_NUM:
	IF (READ_REG(arg1) != arg2) WRITE_REG(IP, arg3);
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BG_REG_REG_REG:
	IF (READ_REG(arg1) > READ_REG(arg2)) WRITE_REG(IP, READ_REG(arg3));
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BG_REG_REG_NUM:
	IF (READ_REG(arg1) > READ_REG(arg2)) WRITE_REG(IP, arg3);
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BG_REG_NUM_REG:
	IF (READ_REG(arg1) > arg2) WRITE_REG(IP, READ_REG(arg3));
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BG_REG_NUM_NUM:
	IF (READ_REG(arg1) > arg2) WRITE_REG(IP, arg3);
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BL_REG_REG_REG:
	IF (READ_REG(arg1) < READ_REG(arg2)) WRITE_REG(IP, READ_REG(arg3));
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BL_REG_REG_NUM:
	IF (READ_REG(arg1) < READ_REG(arg2)) WRITE_REG(IP, arg3);
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BL_REG_NUM_REG:
	IF (READ_REG(arg1) < arg2) WRITE_REG(IP, READ_REG(arg3));
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BL_REG_NUM_NUM:
	IF (READ_REG(arg1) < arg2) WRITE_REG(IP, arg3);
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BGE_REG_REG_REG:
	IF (READ_REG(arg1) >= READ_REG(arg2)) WRITE_REG(IP, READ_REG(arg3));
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BGE_REG_REG_NUM:
	IF (READ_REG(arg1) >= READ_REG(arg2)) WRITE_REG(IP, arg3);
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BGE_REG_NUM_REG:
	IF (READ_REG(arg1) >= arg2) WRITE_REG(IP, READ_REG(arg3));
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BGE_REG_NUM_NUM:
	IF (READ_REG(arg1) >= arg2) WRITE_REG(IP, arg3);
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BLE_REG_REG_REG:
	IF (READ_REG(arg1) <= READ_REG(arg2)) WRITE_REG(IP, READ_REG(arg3));
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BLE_REG_REG_NUM:
	IF (READ_REG(arg1) <= READ_REG(arg2)) WRITE_REG(IP, arg3);
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BLE_REG_NUM_REG:
	IF (READ_REG(arg1) <= arg2) WRITE_REG(IP, READ_REG(arg3));
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case BLE_REG_NUM_NUM:
	IF (READ_REG(arg1) <= arg2) WRITE_REG(IP, arg3);
	ELSE WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case CALL_REG_NONE_NONE:
	WRITE_REG(SP, READ_REG(SP) - 1);
	WRITE_MEM(READ_REG(SP), READ_REG(IP));
	WRITE_REG(IP, READ_REG(arg1));
	break;
case CALL_NUM_NONE_NONE:
	WRITE_REG(SP, READ_REG(SP) - 1);
	WRITE_MEM(READ_REG(SP), READ_REG(IP));
	WRITE_REG(IP, arg1);
	break;
case RET_NONE_NONE_NONE:
	WRITE_REG(IP, READ_MEM(READ_REG(SP)) + 4);
	WRITE_REG(SP, READ_REG(SP) + 1);
	break;
case IN_REG_NONE_NONE:
	scanf("%lld", &REG(arg1));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case OUT_REG_NONE_NONE:
	printf("%lld\n", READ_REG(arg1));
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case DUMP_NONE_NONE_NONE:
	dumpRegisters();
	memDump(&M);
	WRITE_REG(IP, READ_REG(IP) + 4);
	break;
case HLT_NONE_NONE_NONE:
	HALT;
	break;
