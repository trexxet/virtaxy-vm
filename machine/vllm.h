// Registers table interface
#define REG_TBL(id) (regTable[id])
#define REG_GRP(id) (REG_TBL(id).group)
#define REG_BITMASK(id) (REG_TBL(id).bitmask)
#define REG_SHL(id) (REG_TBL(id).shl)

// Registers interface
#define REG(id) (reg[REG_GRP(id)])
#define READ_REG(id) (REG(id) & REG_BITMASK(id))
#define WRITE_REG(id, value) REG(id) = ((REG(id) & (~REG_BITMASK(id))) | \
                                       ((value << REG_SHL(id)) & REG_BITMASK(id)))

// Memory interface
#define READ_MEM(addr) (M.data[addr])
#define WRITE_MEM(addr, value) M.data[addr] = value

