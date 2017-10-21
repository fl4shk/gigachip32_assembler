#ifndef group_2_instructions_hpp
#define group_2_instructions_hpp

// Group 2 Instructions
// Non Block Moves Version:  
	// 10oo oooo aaaa bbbb  cccc iiii iiii iiii

	// o:  opcode
	// a: rA
	// b: rB
	// c: rC
	// i:  12-bit immediate value

// Block Moves Version (stmdb, ldmia, stmia, push, pop):  
	// 10oo oooo aaaa bbbb  cccc dddd xxxx 00ii

	// o:  opcode
	// a: rA
	// b: rB
	// c: rC
	// d: rD
	// x: rX
	// i:  2-bit immediate value


#define LIST_OF_INSTR_G2_LDST_RA_RB_RC_SIMM12__COLLECTION_0(INSTR_STUFF) \
/* Load 32-bit value from address (rB + rC + (sign-extended imm)) into 
rA. */ \
INSTR_STUFF(2, LdStRaRbRcSImm12, Ldr, "ldr") \
\
/* Load zero-extended 16-bit value from address (rB + rC + (sign-extended
imm)) into rA. */ \
/* This zero-extends the value. */ \
INSTR_STUFF(2, LdStRaRbRcSImm12, Ldh, "ldh") \
\
/* Load sign-extended 16-bit value from address (rB + rC + (sign-extended
imm)) into rA. */ \
/* This sign-extends the value. */ \
INSTR_STUFF(2, LdStRaRbRcSImm12, Ldsh, "ldsh") \
\
/* Load zero-extended 8-bit value from address (rB + rC + (sign-extended
 imm)) into rA. */ \
/* This zero-extends the value. */ \
INSTR_STUFF(2, LdStRaRbRcSImm12, Ldb, "ldb") \
\
\
\
/* Load sign-extended 8-bit value from address (rB + rC + (sign-extended
imm)) into rA. */ \
/* This sign-extends the value. */ \
INSTR_STUFF(2, LdStRaRbRcSImm12, Ldsb, "ldsb") \
\
/* Store 32-bit value in rA to address (rB + rC + (sign-extended 
imm)). */ \
INSTR_STUFF(2, LdStRaRbRcSImm12, Str, "str") \
\
/* Store low 16 bits of rA to address (rB + rC + (sign-extended imm)). */ \
INSTR_STUFF(2, LdStRaRbRcSImm12, Sth, "sth") \
\
/* Store low 8 bits of rA to address (rB + rC + (sign-extended imm)). */ \
INSTR_STUFF(2, LdStRaRbRcSImm12, Stb, "stb")


#define LIST_OF_INSTR_G2_RA_RB_RC__COLLECTION_0(INSTR_STUFF) \
/* rA = rB + rC */ \
/* This instruction can affect N, V, Z, and C Flags. */ \
INSTR_STUFF(2, RaRbRc, Add, "add") \
\
/* rA = rB + rC + carry_flag */ \
/* Add with carry */ \
/* This instruction can affect N, V, Z, and C Flags. */ \
INSTR_STUFF(2, RaRbRc, Adc, "adc") \
\
/* rA = rB - rC */ \
/* This instruction can affect N, V, Z, and C Flags. */ \
INSTR_STUFF(2, RaRbRc, Sub, "sub") \
\
/* rA = rB + (~rC) + carry_flag */ \
/* Subtract with borrow (6502 style) */ \
/* This instruction can affect N, V, Z, and C Flags. */ \
INSTR_STUFF(2, RaRbRc, Sbc, "sbc") \
\
\
\
/* rA = rC - rB */ \
/* This instruction can affect N, V, Z, and C Flags. */ \
INSTR_STUFF(2, RaRbRc, Rsb, "rsb") \
\
/* rA = rB * rC */ \
INSTR_STUFF(2, RaRbRc, Mul, "mul") \
\
/* rA = rB & rC */ \
/* This instruction can affect the N and Z Flags. */ \
INSTR_STUFF(2, RaRbRc, And, "and") \
\
/* rA = rB | rC */ \
/* This instruction can affect the N and Z Flags. */ \
INSTR_STUFF(2, RaRbRc, Or, "or") \
\
\
\
/* rA = rB ^ rC */ \
/* This instruction can affect the N and Z Flags. */ \
INSTR_STUFF(2, RaRbRc, Xor, "xor") \
\
/* Logical shift left */ \
/* rA = rB << rC */ \
INSTR_STUFF(2, RaRbRc, Lsl, "lsl") \
\
/* Logical shift right */ \
INSTR_STUFF(2, RaRbRc, Lsr, "lsr") \
\
/* Arithmetic shift right */ \
INSTR_STUFF(2, RaRbRc, Asr, "asr") \
\
\
\
/* Rotate rC left by rC bits, then store result in rA. */ \
INSTR_STUFF(2, RaRbRc, Rol, "rol") \
\
/* Rotate rC right by rC bits, then store result in rA. */ \
INSTR_STUFF(2, RaRbRc, Ror, "ror") \
\
\
/* rA = rB + rC */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_STUFF(1, RaRbRc, AddDotF, "add.f") \
\
/* rA = rB + rC + carry_flag */ \
/* Add with carry */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_STUFF(1, RaRbRc, AdcDotF, "adc.f") \
\
\
\
/* rA = rB - rC */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_STUFF(1, RaRbRc, SubDotF, "sub.f") \
\
/* rA = rA + (~rB) + carry_flag */ \
/* Subtract with borrow (6502 style) */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_STUFF(1, RaRbRc, SbcDotF, "sbc.f") \
\
/* rA = rB - rA */ \
/* This instruction can affect N, V, Z, and C flags. */ \
INSTR_STUFF(1, RaRbRc, RsbDotF, "rsb.f") \
\
/* rA = rB * rC */ \
INSTR_STUFF(1, RaRbRc, MulDotF, "mul.f") \
\
\
\
/* rA = rB & rC */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_STUFF(1, RaRbRc, AndDotF, "and.f") \
\
/* rA = rB | rC */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_STUFF(1, RaRbRc, OrDotF, "or.f") \
\
/* rA = rB ^ rC */ \
/* This instruction can affect the N and Z flags. */ \
INSTR_STUFF(1, RaRbRc, XorDotF, "xor.f") \
\
/* Logical shift left */ \
/* rA = rB << rC */ \
INSTR_STUFF(1, RaRbRc, LslDotF, "lsl.f") \
\
\
\
/* Logical shift right */ \
INSTR_STUFF(1, RaRbRc, LsrDotF, "lsr.f") \
\
/* Arithmetic shift right */ \
INSTR_STUFF(1, RaRbRc, AsrDotF, "asr.f") \
\
/* Rotate rB left by rC bits, then store result in rA. */ \
INSTR_STUFF(1, RaRbRc, RolDotF, "rol.f") \
\
/* Rotate rB right by rB bits, then store result in rA. */ \
INSTR_STUFF(1, RaRbRc, RorDotF, "ror.f") \
\
\
\
/* Fused multiply-add */ \
/* rA = rA + (rB * rC) */ \
INSTR_STUFF(2, RaRbRc, Fma, "fma") \
\
/* Copy rC to rA and to rB */ \
/* If rA is the same register as rB, then the  */ \
/* register will only be written once. */ \
INSTR_STUFF(2, RaRbRc, Cpyp, "cpyp")


#define LIST_OF_INSTR_G2_LDST_BLOCK_1_TO_4__COLLECTION_0(INSTR_STUFF) \
/* STore Multiple, Decrement Before */ \
/* Note that this instruction takes multiple forms */ \
INSTR_STUFF(2, LdStBlock1To4, Stmdb, "stmdb") \
\
\
/* LoaD Multiple, Increment After */ \
/* Note that this instruction takes multiple forms */ \
INSTR_STUFF(2, LdStBlock1To4, Ldmia, "ldmia") \
\
\
/* STore Multiple, Increment After */ \
/* Note that this instruction takes multiple forms */ \
INSTR_STUFF(2, LdStBlock1To4, Stmia, "stmia")



/* Reserved for future expansion. */


/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */





// Pseudo instruction:
//// Load 32-bit value from address (rB + rC) into rA.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldr,rB,rC,0)
//INSTR_LDST_RA_RB_RC(ldrx)

// Pseudo instruction:
//// Load zero-extended 16-bit value from address (rB + rC) into rA.
//// This zero-extends the value.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldh,rB,rC,0)
//INSTR_LDST_RA_RB_RC(ldhx)

// Pseudo instruction:
//// Load sign-extended 16-bit value from address (rB + rC) into rA.
//// This sign-extends the value.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldsh,rB,rC,0)
//INSTR_LDST_RA_RB_RC(ldshx)

// Pseudo instruction:
//// Load zero-extended 8-bit value from address (rB + rC) into rA.
//// This zero-extends the value.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldb,rB,rC,0)
//INSTR_LDST_RA_RB_RC(ldbx)



// Pseudo instruction:
//// Load sign-extended 8-bit value from address (rB + rC) into rA.
//// This sign-extends the value.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldsb,rB,rC,0)
//INSTR_LDST_RA_RB_RC(ldsbx)

// Pseudo instruction:
//// Store 32-bit value in rA to address (rB + rC).
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(str,rB,rC,0)
//INSTR_LDST_RA_RB_RC(strx)

// Pseudo instruction:
//// Store low 16 bits of rA to address (rB + rC).
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(sth,rB,rC,0)
//INSTR_LDST_RA_RB_RC(sthx)

// Pseudo instruction:
//// Store low 8 bits of rA to address (rB + rC).
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(stb,rB,rC,0)
//INSTR_LDST_RA_RB_RC(stbx)



// Pseudo instruction:
//// Load 32-bit value from address (rB + (sign-extended imm)) into rA.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldr,rB,r0)
//INSTR_LDST_RA_RB_IMM(ldrxi)

// Pseudo instruction:
//// Load zero-extended 16-bit value from address (rB + (sign-extended imm)) into rA.
//// This zero-extends the value.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldh,rB,r0)
//INSTR_LDST_RA_RB_IMM(ldhxi)

// Pseudo instruction:
//// Load sign-extended 16-bit value from address (rB + (sign-extended imm)) into rA.
//// This sign-extends the value.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldsh,rB,r0)
//INSTR_LDST_RA_RB_IMM(ldshxi)

// Pseudo instruction:
//// Load zero-extended 8-bit value from address (rB + (sign-extended imm)) into rA.
//// This zero-extends the value.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldb,rB,r0)
//INSTR_LDST_RA_RB_IMM(ldbxi)



// Pseudo instruction:
//// Load sign-extended 8-bit value from address (rB + (sign-extended imm)) into rA.
//// This sign-extends the value.
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(ldsb,rB,r0)
//INSTR_LDST_RA_RB_IMM(ldsbxi)

// Pseudo instruction:
//// Store 32-bit value in rA to address (rB + (sign-extended imm)).
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(str,rB,r0)
//INSTR_LDST_RA_RB_IMM(strxi)

// Pseudo instruction:
//// Store low 16 bits of rA to address (rB + (sign-extended imm)).
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(sth,rB,r0)
//INSTR_LDST_RA_RB_IMM(sthxi)

// Pseudo instruction:
//// Store low 8 bits of rA to address (rB + (sign-extended imm)).
//// Encoded like this:  INSTR_LDST_GENERIC_RA_RB_RC_IMM(stb,rB,r0)
//INSTR_LDST_RA_RB_IMM(stbxi)



// Pseudo instruction:
//// temp = rB - (-rC)
//// This instruction can affect N, V, Z, and C Flags.
//// Encoded like this:  add.f r0, rB, rC
//PSEUDO_INSTR_RB_RC(cmn)

// Pseudo instruction:
//// temp = rC - rB
//// This instruction can affect N, V, Z, and C Flags.
//// Encoded like this:  rsb.f r0, rB, rC
//PSEUDO_INSTR_RB_RC(cmr)

// Pseudo instruction:
//// temp = rB & rC
//// Encoded like this:  and.f r0, rB, rC
//// This instruction can affect the N and Z Flags.
//PSEUDO_INSTR_RB_RC(tst)




// Pseudo instruction:
// Pop
// Note that this instruction takes multiple forms
	// Syntax:  pop rA

// Pseudo instruction:
// Push
// Note that this instruction takes multiple forms
	// Syntax:  push rA

#define LIST_OF_GROUP_2_INSTRUCTIONS(INSTR_STUFF) \
LIST_OF_INSTR_G2_LDST_RA_RB_RC_SIMM12__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G2_RA_RB_RC__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G2_LDST_BLOCK_1_TO_4__COLLECTION_0(INSTR_STUFF) \

#endif		// group_2_instructions_hpp
