#ifndef group_3_instructions_hpp
#define group_3_instructions_hpp


// Group 3 Instructions
// Non Block Moves Version:  
	// 11oo oooo aaaa bbbb  iiii iiii iiii iiii  iiii iiii iiii iiii

	// o:  opcode
	// a: rA
	// b: rB
	// i:  32-bit immediate value

// Block Moves Version (stmdb, ldmia, stmia, push, pop):  
	// 11oo oooo aaaa bbbb  cccc dddd eeee ffff  gggg hhhh xxxx 00ii

	// o:  opcode
	// a: rA
	// b: rB
	// c: rC
	// d: rD
	// e: rE
	// f: rF
	// g: rG
	// h: rH
	// x: rX
	// i:  2-bit immediate value


// 32-bit by 32-bit -> 64-bit Multiply Version:
	// 11oo oooo aaaa bbbb  cccc dddd 0000 0000  0000 0000 0000 0000

	// o:  opcode
	// a: rA
	// b: rB
	// c: rC
	// d: rD


// 64-bit by 64-bit -> 64-bit DivMod Version:
	// 11oo oooo aaaa bbbb  cccc dddd eeee ffff  gggg hhhh 0000 0000

	// o:  opcode
	// a: rA
	// b: rB
	// c: rC
	// d: rD
	// e: rE
	// f: rF
	// g: rG
	// h: rH

// 32-bit by 32-bit -> 32-bit DivMod Version:
	// 11oo oooo aaaa bbbb  cccc dddd 0000 0000  0000 0000 0000 0000

	// f:  1 if can affect flags (and instruction type supports it), 0 if
	// flags unchanged.

	// o:  opcode
	// a: rA
	// b: rB
	// c: rC
	// d: rD

// 64-bit bitshifted by 64-bit -> 64-bit Version:
	// 11oo oooo aaaa bbbb  cccc dddd eeee ffff  0000 0000 0000 0000

	// o:  opcode
	// a: rA
	// b: rB
	// c: rC
	// d: rD
	// e: rE
	// f: rF


#define LIST_OF_INSTR_G3_LDST_RA_RB_IMM32__COLLECTION_0(INSTR_STUFF) \
/* Load 32-bit value from address (absolute_addr + rB) into rA. */ \
INSTR_STUFF(3, LdStRaRbImm32, Ldra, "ldra") \
\
/* Load zero-extended 16-bit value from address (absolute_addr + rB) */ \
/* into rA. */ \
/* This zero-extends the value. */ \
INSTR_STUFF(3, LdStRaRbImm32, Ldha, "ldha") \
\
/* Load sign-extended 16-bit value from address (absolute_addr + rB) */ \
/* into rA. */ \
/* This sign-extends the value. */ \
INSTR_STUFF(3, LdStRaRbImm32, Ldsha, "ldsha") \
\
/* Load zero-extended 8-bit value from address (absolute_addr + rB) */ \
/* into rA. */ \
/* This zero-extends the value. */ \
INSTR_STUFF(3, LdStRaRbImm32, Ldba, "ldba") \
\
\
\
/* Load sign-extended 8-bit value from address (absolute_addr + rB) */ \
/* into rA. */ \
/* This sign-extends the value. */ \
INSTR_STUFF(3, LdStRaRbImm32, Ldsba, "ldsba") \
\
/* Store 32-bit value in rA to address (absolute_addr + rB). */ \
INSTR_STUFF(3, LdStRaRbImm32, Stra, "stra") \
\
/* Store low 16 bits of rA to address (absolute_addr + rB). */ \
INSTR_STUFF(3, LdStRaRbImm32, Stha, "stha") \
\
/* Store low 8 bits of rA to address (absolute_addr + rB). */ \
INSTR_STUFF(3, LdStRaRbImm32, Stba, "stba") \



#define LIST_OF_INSTR_G3_RA_RB_IMM32__COLLECTION_0(INSTR_STUFF) \
/* Subroutine call using (rA + rB + absolute_addr) as destination */ \
/* address. */ \
/* The return address is stored in the link register (lr). */ \
INSTR_STUFF(3, RaRbImm32, Calla, "calla") \
\
/* Set pc to destination address in (rA + rB + absolute_addr). */ \
INSTR_STUFF(3, RaRbImm32, Jumpa, "jumpa") \
\
\
/* rA = 32-bit immediate, rB = same 32-bit immediate */ \
/* If rA is the same register as rB, then the  */ \
/* register will only be written once. */ \
INSTR_STUFF(3, RaRbImm32, Cpypi, "cpypi") \



#define LIST_OF_INSTR_G3_LDST_BLOCK_5_TO_8__COLLECTION_0(INSTR_STUFF) \
/* STore Multiple, Decrement Before */ \
/* Note that this instruction takes multiple forms */ \
	/* Syntax:  stmdb rX, {rA, rB, rC, rD, rE} */ \
INSTR_STUFF(3, LdStBlock5To8, Stmdb, "stmdb") \
\
\
\
/* LoaD Multiple, Increment After */ \
/* Note that this instruction takes multiple forms */ \
	/* Syntax:  ldmia rX, {rA, rB, rC, rD, rE} */ \
INSTR_STUFF(3, LdStBlock5To8, Ldmia, "ldmia") \
\
\
/* STore Multiple, Increment After */ \
/* Note that this instruction takes multiple forms */ \
	/* Syntax:  stmia rX, {rA, rB, rC, rD, rE} */ \
INSTR_STUFF(3, LdStBlock5To8, Stmia, "stmia") \


#define LIST_OF_INSTR_G3_LONG_MUL__COLLECTION_0(INSTR_STUFF) \
/* 32-bit by 32-bit -> 64-bit result Unsigned Multiply */ \
INSTR_STUFF(3, LongMul, UMul, "umul") \
\
/* 32-bit by 32-bit -> 64-bit result Signed Multiply */ \
INSTR_STUFF(3, LongMul, SMul, "smul") \


#define LIST_OF_INSTR_G3_LONG_DIVMOD__COLLECTION_0(INSTR_STUFF) \
/* 64-bit by 64-bit -> 64-bit quotient and 64-bit remainder Unsigned */ \
/* Division */ \
INSTR_STUFF(3, LongDivMod, UDivMod, "udivmod") \
/* 64-bit by 64-bit -> 64-bit quotient and 64-bit remainder Signed */ \
/* Division */ \
INSTR_STUFF(3, LongDivMod, SDivMod, "sdivmod") \

#define LIST_OF_INSTR_G3_DIVMOD__COLLECTION_0(INSTR_STUFF) \
/* 32-bit by 32-bit -> 32-bit quotient and 32-bit remainder Unsigned */ \
/* Division */ \
INSTR_STUFF(3, DivMod, UDivMod, "udivmod") \
/* 32-bit by 32-bit -> 32-bit quotient and 32-bit remainder Signed */ \
/* Division */ \
INSTR_STUFF(3, DivMod, SDivMod, "sdivmod") \



#define LIST_OF_INSTR_G3_LONG_BITSHIFT__COLLECTION_0(INSTR_STUFF) \
/* lsl, lsr, asr */ \
INSTR_STUFF(3, LongBitShift, Lsl, "lsl") \
INSTR_STUFF(3, LongBitShift, Lsr, "lsr") \
INSTR_STUFF(3, LongBitShift, Asr, "asr") \
/* Reserved for future expansion. */



/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */

/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */



/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */

/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */

/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */

/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */



/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */

/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */

/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */

/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */
/* Reserved for future expansion. */


// Pseudo instruction:
//// Subroutine call using (rA + absolute_addr) as destination address. 
//// The return address is stored in the link register (lr).
//// Encoded like this:  calla rA, r0, absolute_addr
//RA_IMM(calla)

// Pseudo instruction:
//// Subroutine call using (absolute_addr) as destination address. 
//// The return address is stored in the link register (lr).
//// Encoded like this:  calla r0, r0, absolute_addr
//IMM(calla)


// Pseudo instruction:
//// Set pc to destination address in (rA + absolute_addr).
//// Encoded like this:  jumpa rA, r0, absolute_addr
//RA_IMM(jumpa)

// Pseudo instruction:
//// Set pc to destination address in (absolute_addr).
//// Encoded like this:  jumpa r0, r0, absolute_addr
//IMM(jumpa)



// Pseudo instruction:
//// rA = 32-bit immediate
//// Encoded like this:  cpypi rA, rA, imm
//RA_IMM(cpyi)



// Pseudo instruction:
// Pop
// Note that this instruction takes multiple forms
	// Syntax:  pop rA, rB, rC, rD, rE


// Pseudo instruction:
// Push
// Note that this instruction takes multiple forms
	// Syntax:  push rA, rB, rC, rD, rE

#define LIST_OF_GROUP_3_INSTRUCTIONS(INSTR_STUFF) \
LIST_OF_INSTR_G3_LDST_RA_RB_IMM32__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G3_RA_RB_IMM32__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G3_LDST_BLOCK_5_TO_8__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G3_LONG_MUL__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G3_LONG_DIVMOD__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G3_DIVMOD__COLLECTION_0(INSTR_STUFF) \
LIST_OF_INSTR_G3_LONG_BITSHIFT__COLLECTION_0(INSTR_STUFF) \


#endif		// group_3_instructions_hpp
