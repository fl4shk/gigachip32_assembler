#include "assembler_class.hpp"

namespace flare32
{

// Constructor stuff
void assembler::insert_grp_0_instructions()
{
	static constexpr size_t grp = 0;
	size_t opcode = 0;
	symbol * sym, * sym_dot_f;
	std::string real_instr_name, real_instr_name_dot_f;
	size_t real_instr_index = 0, real_instr_index_dot_f = 0;
	
	auto insert_instr_keep_opcode = [ this, &opcode ]
		( symbol*& some_sym, const std::string& some_orig_name, 
		const instr_args& iargs, 
		const std::string& some_real_instr_name="", 
		size_t some_real_instr_index=0 ) 
		-> void
	{
		some_sym = &special_sym_tbl.enter( some_orig_name, 
			cast_typ(tok_defn::instr), 0, true );
		instr_tbl.enter( some_orig_name, opcode, grp, iargs, 
			some_real_instr_name, some_real_instr_index );
	};
	auto insert_instr = [ this, &insert_instr_keep_opcode, &opcode ]
		(  symbol*& some_sym, const std::string& some_orig_name, 
		const instr_args& iargs, 
		const std::string& some_real_instr_name="",
		size_t some_real_instr_index=0 )
		-> void
	{
		insert_instr_keep_opcode( some_sym, some_orig_name, iargs, 
			some_real_instr_name, some_real_instr_index );
		++opcode;
	};
	// This inserts an instruction and also one with ".f" appended to its
	// name.
	auto insert_instr_and_with_dot_f = [&]( const std::string& orig_name, 
		const instr_args& iargs ) -> void
	{
		std::string temp_name_0 = orig_name;
		std::string temp_name_1 = temp_name_0 + std::string(".f");
		insert_instr_keep_opcode( sym, temp_name_0, iargs,
			real_instr_name, real_instr_index );
		insert_instr_keep_opcode( sym_dot_f, temp_name_1, iargs,
			real_instr_name_dot_f, real_instr_index_dot_f );
		
		++opcode;
	};
	auto find_real_instr = [this]( std::string& some_real_instr_name,
		size_t& some_real_instr_index, const std::string& some_orig_name, 
		const instr_args& iargs, size_t eek_number=1 ) -> void
	{
		symbol* some_sym;
		
		if (!special_sym_tbl.find( some_sym, some_orig_name ))
		{
			we.error( "assembler constructor (", some_orig_name, 
				", group ", grp, "):  Eek ", eek_number, "!\n" );
		}
		
		const auto& some_instr_vec = instr_tbl.at(some_orig_name);
		
		some_real_instr_name = "";
		some_real_instr_index = 0;
		for ( size_t i=0; i<some_instr_vec.size(); ++i )
		{
			const instruction& iter = some_instr_vec.at(i);
			if ( iter.iargs() == iargs )
			{
				some_real_instr_name = iter.name();
				some_real_instr_index = i;
				break;
			}
		}
		
		if ( some_real_instr_name.size() == 0 )
		{
			we.error( "assembler constructor (", some_orig_name, 
				", group ", grp, "):  Eek ", ( eek_number + 1 ), "!\n" );
		}
	};
	// This is used for pseudo instructions.
	auto find_real_instr_and_with_dot_f = [&]
		( const std::string& orig_name, const instr_args& iargs ) -> void
	{
		const std::string orig_name_dot_f = orig_name + std::string(".f");
		find_real_instr( real_instr_name, real_instr_index, orig_name, 
			iargs, 1 );
		find_real_instr( real_instr_name_dot_f, real_instr_index_dot_f, 
			orig_name_dot_f, iargs, 3 );
	};
	
	// Instructions:
	// rA = rA + rB
	// This instruction can affect N, V, Z, and C flags.
	//add rA, rB
	insert_instr_and_with_dot_f( "add", instr_args::ra_rb );
	
	// rA = rA + rB + carry_flag
	// Add with carry
	// This instruction can affect N, V, Z, and C flags.
	//adc rA, rB
	insert_instr_and_with_dot_f( "adc", instr_args::ra_rb );
	
	// rA = rA - rB
	// This instruction can affect N, V, Z, and C flags.
	//sub rA, rB
	insert_instr_and_with_dot_f( "sub", instr_args::ra_rb );
	
	// rA = rA + (~rB) + carry_flag
	// Subtract with borrow (6502 style)
	// This instruction can affect N, V, Z, and C flags.
	//sbc rA, rB
	insert_instr_and_with_dot_f( "sbc", instr_args::ra_rb );
	
	
	
	// rA = rB - rA
	// This instruction can affect N, V, Z, and C flags.
	//rsb rA, rB
	insert_instr_and_with_dot_f( "rsb", instr_args::ra_rb );
	
	// rA = rA * rB
	//mul rA, rB
	insert_instr_and_with_dot_f( "mul", instr_args::ra_rb );
	
	// rA = rA & rB
	// This instruction can affect the N and Z flags.
	//and rA, rB
	insert_instr_and_with_dot_f( "and", instr_args::ra_rb );
	
	// rA = rA | rB
	// This instruction can affect the N and Z flags.
	//or rA, rB
	insert_instr_and_with_dot_f( "or", instr_args::ra_rb );
	
	
	
	// rA = rA ^ rB
	// This instruction can affect the N and Z flags.
	//xor rA, rB
	insert_instr_and_with_dot_f( "xor", instr_args::ra_rb );
	
	// Logical shift left
	// rA = rA << rB
	//lsl rA, rB
	insert_instr_and_with_dot_f( "lsl", instr_args::ra_rb );
	
	// Logical shift right
	//lsr rA, rB
	insert_instr_and_with_dot_f( "lsr", instr_args::ra_rb );
	
	// Arithmetic shift right
	//asr rA, rB
	insert_instr_and_with_dot_f( "asr", instr_args::ra_rb );
	
	
	
	// Rotate rB left by rB bits, then store result in rA.
	//rol rA, rB
	insert_instr_and_with_dot_f( "rol", instr_args::ra_rb );
	
	// Rotate rB right by rB bits, then store result in rA.
	//ror rA, rB
	insert_instr_and_with_dot_f( "ror", instr_args::ra_rb );
	
	// Rotate rB left (THROUGH carry) by 1 bit, then store result in rA.
	// This instruction can only affect the C flag.
	//rlc rA, rB
	insert_instr_and_with_dot_f( "rlc", instr_args::ra_rb );
	
	// Rotate rB right (THROUGH carry) by 1 bit, then store result in rA.
	// This instruction can only affect the C flag.
	//rrc rA, rB
	insert_instr_and_with_dot_f( "rrc", instr_args::ra_rb );
	
	
	
	// rA = Sign extend of low 16 bits in rB
	// Note that the high 16 bits of rB are ignored
	//seh rA, rB
	insert_instr_and_with_dot_f( "seh", instr_args::ra_rb );
	
	// rA = Sign extend of low 8 bits in rB
	//seb rA, rB
	insert_instr_and_with_dot_f( "seb", instr_args::ra_rb );
	
	// Push registers rA and rb (as a pair) onto the 
	// stack (in that order)
	//push rA, rB
	insert_instr_and_with_dot_f( "push", instr_args::ra_rb );
	
	// Pop two 32-bit values off the stack, storing the first popped
	// value into rB and the second popped value into rA
	//pop rA, rB
	insert_instr_and_with_dot_f( "pop", instr_args::ra_rb );
	
	
	
	// Push flags as 8-bit value onto the stack (high 4 bits of pushed
	// value are set to zero before the push)
	//push flags
	insert_instr_and_with_dot_f( "push", instr_args::flags );
	
	// Pop 8-bit value from the stack and store low 4 bits to flags
	//pop flags
	insert_instr_and_with_dot_f( "pop", instr_args::flags );
	
	// Clear rA, then CoPY FRom Flags to rA
	//cpy rA, flags
	insert_instr_and_with_dot_f( "cpy", instr_args::ra_flags );
	
	// Copy to flags from rA
	// This instruction can affect N, V, Z, and C flags.
	//cpy flags, rA
	insert_instr_and_with_dot_f( "cpy", instr_args::flags_ra );
	
	
	
	// ENable Interrupts
	//eni
	insert_instr_and_with_dot_f( "eni", instr_args::noargs );
	
	// DIsable Interrupts
	//dii
	insert_instr_and_with_dot_f( "dii", instr_args::noargs );
	
	// Set the PC to interrupt RETurn address and enable Interrupts
	//reti
	insert_instr_and_with_dot_f( "reti", instr_args::noargs );
	
	// Set the PC to the Interrupt Return Address, but DON'T enable
	// interrupts
	//jump ira
	insert_instr_and_with_dot_f( "jump", instr_args::ira );
	
	
	
	// Copy rA to the Interrupt Return Address
	//cpy ira, rA
	insert_instr_and_with_dot_f( "cpy", instr_args::ira_ra );
	
	// Copy the Interrupt Return Address to rA
	//cpy rA, ira
	insert_instr_and_with_dot_f( "cpy", instr_args::ra_ira );
	
	// Subroutine call using (rA + rB) as destination address. 
	// The return address is stored in the link register (lr).
	//callx rA, rB
	insert_instr_and_with_dot_f( "callx", instr_args::ra_rb );
	
	// Copy pc to rA (this can be used for pc-relative loads
	// and stores)
	//cpy rA, pc
	insert_instr_and_with_dot_f( "cpy", instr_args::ra_pc );
	
	
	// Pseudo instruction:
	//// Subroutine call using rB as destination address. 
	//// Encoded like this:  callx r0, rB
	//call rB
	find_real_instr_and_with_dot_f( "callx", instr_args::ra_rb );
	insert_instr_and_with_dot_f( "call", instr_args::pseudo_r0hidden_rb );
}
void assembler::insert_grp_1_instructions()
{
	static constexpr size_t grp = 1;
	size_t opcode = 0;
	symbol * sym, * sym_dot_f;
	std::string real_instr_name, real_instr_name_dot_f;
	size_t real_instr_index = 0, real_instr_index_dot_f = 0;
	
	auto insert_instr_keep_opcode = [ this, &opcode ]
		( symbol*& some_sym, const std::string& some_orig_name, 
		const instr_args& iargs, 
		const std::string& some_real_instr_name="", 
		size_t some_real_instr_index=0 ) 
		-> void
	{
		some_sym = &special_sym_tbl.enter( some_orig_name, 
			cast_typ(tok_defn::instr), 0, true );
		instr_tbl.enter( some_orig_name, opcode, grp, iargs, 
			some_real_instr_name, some_real_instr_index );
	};
	auto insert_instr = [ this, &insert_instr_keep_opcode, &opcode ]
		(  symbol*& some_sym, const std::string& some_orig_name, 
		const instr_args& iargs, 
		const std::string& some_real_instr_name="",
		size_t some_real_instr_index=0 )
		-> void
	{
		insert_instr_keep_opcode( some_sym, some_orig_name, iargs, 
			some_real_instr_name, some_real_instr_index );
		++opcode;
	};
	// This inserts an instruction and also one with ".f" appended to its
	// name.
	auto insert_instr_and_with_dot_f = [&]( const std::string& orig_name, 
		const instr_args& iargs ) -> void
	{
		std::string temp_name_0 = orig_name;
		std::string temp_name_1 = temp_name_0 + std::string(".f");
		insert_instr_keep_opcode( sym, temp_name_0, iargs,
			real_instr_name, real_instr_index );
		insert_instr_keep_opcode( sym_dot_f, temp_name_1, iargs,
			real_instr_name_dot_f, real_instr_index_dot_f );
		
		++opcode;
	};
	auto find_real_instr = [this]( std::string& some_real_instr_name,
		size_t& some_real_instr_index, const std::string& some_orig_name, 
		const instr_args& iargs, size_t eek_number=1 ) -> void
	{
		symbol* some_sym;
		
		if (!special_sym_tbl.find( some_sym, some_orig_name ))
		{
			we.error( "assembler constructor (", some_orig_name, 
				", group ", grp, "):  Eek ", eek_number, "!\n" );
		}
		
		const auto& some_instr_vec = instr_tbl.at(some_orig_name);
		
		some_real_instr_name = "";
		some_real_instr_index = 0;
		for ( size_t i=0; i<some_instr_vec.size(); ++i )
		{
			const instruction& iter = some_instr_vec.at(i);
			if ( iter.iargs() == iargs )
			{
				some_real_instr_name = iter.name();
				some_real_instr_index = i;
				break;
			}
		}
		
		if ( some_real_instr_name.size() == 0 )
		{
			we.error( "assembler constructor (", some_orig_name, 
				", group ", grp, "):  Eek ", ( eek_number + 1 ), "!\n" );
		}
	};
	// This is used for pseudo instructions.
	auto find_real_instr_and_with_dot_f = [&]
		( const std::string& orig_name, const instr_args& iargs ) -> void
	{
		const std::string orig_name_dot_f = orig_name + std::string(".f");
		find_real_instr( real_instr_name, real_instr_index, orig_name, 
			iargs, 1 );
		find_real_instr( real_instr_name_dot_f, real_instr_index_dot_f, 
			orig_name_dot_f, iargs, 3 );
	};
	
	
	// Instructions:
	// rA = rB + (zero-extended imm)
	// This instruction can affect N, V, Z, and C flags.
	//addi rA, rB, imm
	insert_instr_and_with_dot_f( "addi", instr_args::ra_rb_imm16u );
	
	// rA = rB + (zero-extended imm) + carry_flag
	// Add with carry
	// This instruction can affect N, V, Z, and C flags.
	//adci rA, rB, imm
	insert_instr_and_with_dot_f( "adci", instr_args::ra_rb_imm16u );
	
	// rA = rB - (zero-extended imm)
	// This instruction can affect N, V, Z, and C flags.
	//subi rA, rB, imm
	insert_instr_and_with_dot_f( "subi", instr_args::ra_rb_imm16u );
	
	// rA = rB + (~(zero-extended imm)) + carry_flag
	// Subtract with borrow (6502 style)
	// This instruction can affect N, V, Z, and C flags.
	//sbci rA, rB, imm
	insert_instr_and_with_dot_f( "sbci", instr_args::ra_rb_imm16u );
	
	
	
	// rA = (zero-extended imm) - rB
	// This instruction can affect N, V, Z, and C flags.
	//rsbi rA, rB, imm
	insert_instr_and_with_dot_f( "rsbi", instr_args::ra_rb_imm16u );
	
	// rA = rB * (zero-extended imm)
	//muli rA, rB, imm
	insert_instr_and_with_dot_f( "muli", instr_args::ra_rb_imm16u );
	
	// rA = rB & (zero-extended imm)
	// This instruction can affect the N and Z flags.
	//andi rA, rB, imm
	insert_instr_and_with_dot_f( "andi", instr_args::ra_rb_imm16u );
	
	// rA = rB | (zero-extended imm)
	// This instruction can affect the N and Z flags.
	//ori rA, rB, imm
	insert_instr_and_with_dot_f( "ori", instr_args::ra_rb_imm16u );
	
	
	
	// rA = rB ^ (zero-extended imm)
	// This instruction can affect the N and Z flags.
	//xori rA, rB, imm
	insert_instr_and_with_dot_f( "xori", instr_args::ra_rb_imm16u );
	
	// Logical shift left
	// rA = rB << (zero-extended imm)
	//lsli rA, rB, imm
	insert_instr_and_with_dot_f( "lsli", instr_args::ra_rb_imm16u );
	
	// Logical shift right
	//lsri rA, rB, imm
	insert_instr_and_with_dot_f( "lsri", instr_args::ra_rb_imm16u );
	
	// Arithmetic shift right
	//asri rA, rB, imm
	insert_instr_and_with_dot_f( "asri", instr_args::ra_rb_imm16u );
	
	
	
	// Rotate rB left by (zero-extended imm) bits, then store result in rA.
	//roli rA, rB, imm
	insert_instr_and_with_dot_f( "roli", instr_args::ra_rb_imm16u );
	
	// Rotate rB right by (zero-extended imm) bits, then store result in rA.
	//rori rA, rB, imm
	insert_instr_and_with_dot_f( "rori", instr_args::ra_rb_imm16u );
	
	// Branch always, 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bra imm
	insert_instr_and_with_dot_f( "bra", instr_args::branchoffset );
	
	// Branch when Z == 0, 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bne imm
	insert_instr_and_with_dot_f( "bne", instr_args::branchoffset );
	
	
	
	// Branch when Z == 1, 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//beq imm
	insert_instr_and_with_dot_f( "beq", instr_args::branchoffset );
	
	// Branch when C == 0 [unsigned less than], 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bcc imm
	insert_instr_and_with_dot_f( "bcc", instr_args::branchoffset );
	
	// Branch when C == 1 [unsigned greater than or equal], 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bcs imm
	insert_instr_and_with_dot_f( "bcs", instr_args::branchoffset );
	
	// Branch when ( C == 0 or Z == 1 ) [unsigned less than or equal], 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bls imm
	insert_instr_and_with_dot_f( "bls", instr_args::branchoffset );
	
	
	
	// Branch when ( C == 1 and Z == 0 ) [unsigned greater than], 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bhi imm
	insert_instr_and_with_dot_f( "bhi", instr_args::branchoffset );
	
	// Branch when N == 0, 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bpl imm
	insert_instr_and_with_dot_f( "bpl", instr_args::branchoffset );
	
	// Branch when N == 1, 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bmi imm
	insert_instr_and_with_dot_f( "bmi", instr_args::branchoffset );
	
	// Branch when V == 0, 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bvc imm
	insert_instr_and_with_dot_f( "bvc", instr_args::branchoffset );
	
	
	
	// Branch when V == 1, 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bvs imm
	insert_instr_and_with_dot_f( "bvs", instr_args::branchoffset );
	
	// Branch when N == V [signed greater than or equal], 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bge imm
	insert_instr_and_with_dot_f( "bge", instr_args::branchoffset );
	
	// Branch when N != V [signed less than], 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//blt imm
	insert_instr_and_with_dot_f( "blt", instr_args::branchoffset );
	
	// Branch when ( N == V and Z == 0 ) [signed greater than], 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//bgt imm
	insert_instr_and_with_dot_f( "bgt", instr_args::branchoffset );
	
	
	
	// Branch when ( N != V or Z == 1 ) [signed less than or equal], 
	// to ( (pc when instruction starts)
	// + (sign-extended 16-bit immediate value) )
	//ble imm
	insert_instr_and_with_dot_f( "ble", instr_args::branchoffset );
	
	// rA = rB & (sign-extended imm)
	// This instruction can affect the N and Z flags.
	//andsi rA, rB, imm
	insert_instr_and_with_dot_f( "andsi", instr_args::ra_rb_imm16s );
	
	// rA = rB | (sign-extended imm)
	// This instruction can affect the N and Z flags.
	//orsi rA, rB, imm
	insert_instr_and_with_dot_f( "orsi", instr_args::ra_rb_imm16s );
	
	// rA = rB ^ (sign-extended imm)
	// This instruction can affect the N and Z flags.
	//xorsi rA, rB, imm
	insert_instr_and_with_dot_f( "xorsi", instr_args::ra_rb_imm16s );
	
	
	
	// Pseudo instruction:
	//// Compare rB to (zero-extended imm)
	//// temp = rB - (zero-extended imm)
	//// Encoded like this:  subi.f r0, rB, imm
	//// This instruction can affect N, V, Z, and C flags.
	//cmpi rB, imm
	find_real_instr( real_instr_name_dot_f, real_instr_index_dot_f, "subi.f", 
		instr_args::ra_rb_imm16u );
	insert_instr( sym_dot_f, std::string("cmpi"), 
		instr_args::pseudo_r0hidden_rb_imm16u, real_instr_name_dot_f, real_instr_index_dot_f );
	
	// Pseudo instruction:
	//// Compare rB to negated (zero-extended imm)
	//// temp = rB - (-(zero-extended imm))
	//// Encoded like this:  addi.f r0, rB, imm
	//// This instruction can affect N, V, Z, and C flags.
	//cmni rB, imm
	find_real_instr( real_instr_name_dot_f, real_instr_index_dot_f, "addi.f", 
		instr_args::ra_rb_imm16u );
	insert_instr( sym_dot_f, std::string("cmni"), 
		instr_args::pseudo_r0hidden_rb_imm16u, real_instr_name_dot_f, real_instr_index_dot_f );
	
	// Pseudo instruction:
	//// Compare reversed with immediate value
	//// temp = (zero-extended imm) - rB
	//// Encoded like this:  rsbi.f r0, rB, imm
	//// This instruction can affect N, V, Z, and C flags.
	//cmri rB, imm
	find_real_instr( real_instr_name_dot_f, real_instr_index_dot_f, "rsbi.f", 
		instr_args::ra_rb_imm16u );
	insert_instr( sym_dot_f, std::string("cmri"), 
		instr_args::pseudo_r0hidden_rb_imm16u, real_instr_name_dot_f, real_instr_index_dot_f );
	
	// Pseudo instruction:
	//// Copy Negated
	//// rA = -rB
	//// Encoded like this:  rsbi rA, rB, 0
	//cpn rA, rB
	find_real_instr_and_with_dot_f( "rsbi", instr_args::ra_rb_imm16u );
	insert_instr_and_with_dot_f( "cpn", 
		instr_args::pseudo_ra_rb_imm0hidden );
	
	// Pseudo instruction:
	//// Copy Complemented
	//// rA = ~rB
	//// Encoded like this:  xorsi rA, rB, -1
	//cpc rA, rB
	find_real_instr_and_with_dot_f( "xorsi", instr_args::ra_rb_imm16s );
	insert_instr_and_with_dot_f( "cpc",
		instr_args::pseudo_ra_rb_imm16sneg1hidden );
	
	
	
	
	// Pseudo instruction:
	//// temp = rB & (zero-extended imm)
	//// Encoded like this:  andi r0, rB, imm
	//// This instruction can affect the N and Z flags.
	//tsti rB, imm
	find_real_instr_and_with_dot_f( "andi", instr_args::ra_rb_imm16u );
	insert_instr_and_with_dot_f( "tsti", 
		instr_args::pseudo_r0hidden_rb_imm16u );
}
void assembler::insert_grp_2_instructions()
{
	static constexpr size_t grp = 2;
	size_t opcode = 0;
	symbol * sym, * sym_dot_f;
	std::string real_instr_name, real_instr_name_dot_f;
	size_t real_instr_index = 0, real_instr_index_dot_f = 0;
	
	auto insert_instr_keep_opcode = [ this, &opcode ]
		( symbol*& some_sym, const std::string& some_orig_name, 
		const instr_args& iargs, 
		const std::string& some_real_instr_name="", 
		size_t some_real_instr_index=0 ) 
		-> void
	{
		some_sym = &special_sym_tbl.enter( some_orig_name, 
			cast_typ(tok_defn::instr), 0, true );
		instr_tbl.enter( some_orig_name, opcode, grp, iargs, 
			some_real_instr_name, some_real_instr_index );
	};
	auto insert_instr = [ this, &insert_instr_keep_opcode, &opcode ]
		(  symbol*& some_sym, const std::string& some_orig_name, 
		const instr_args& iargs, 
		const std::string& some_real_instr_name="",
		size_t some_real_instr_index=0 )
		-> void
	{
		insert_instr_keep_opcode( some_sym, some_orig_name, iargs, 
			some_real_instr_name, some_real_instr_index );
		++opcode;
	};
	// This inserts an instruction and also one with ".f" appended to its
	// name.
	auto insert_instr_and_with_dot_f = [&]( const std::string& orig_name, 
		const instr_args& iargs ) -> void
	{
		std::string temp_name_0 = orig_name;
		std::string temp_name_1 = temp_name_0 + std::string(".f");
		insert_instr_keep_opcode( sym, temp_name_0, iargs,
			real_instr_name, real_instr_index );
		insert_instr_keep_opcode( sym_dot_f, temp_name_1, iargs,
			real_instr_name_dot_f, real_instr_index_dot_f );
		
		++opcode;
	};
	auto find_real_instr = [this]( std::string& some_real_instr_name,
		size_t& some_real_instr_index, const std::string& some_orig_name, 
		const instr_args& iargs, size_t eek_number=1 ) -> void
	{
		symbol* some_sym;
		
		if (!special_sym_tbl.find( some_sym, some_orig_name ))
		{
			we.error( "assembler constructor (", some_orig_name, 
				", group ", grp, "):  Eek ", eek_number, "!\n" );
		}
		
		const auto& some_instr_vec = instr_tbl.at(some_orig_name);
		
		some_real_instr_name = "";
		some_real_instr_index = 0;
		for ( size_t i=0; i<some_instr_vec.size(); ++i )
		{
			const instruction& iter = some_instr_vec.at(i);
			if ( iter.iargs() == iargs )
			{
				some_real_instr_name = iter.name();
				some_real_instr_index = i;
				break;
			}
		}
		
		if ( some_real_instr_name.size() == 0 )
		{
			we.error( "assembler constructor (", some_orig_name, 
				", group ", grp, "):  Eek ", ( eek_number + 1 ), "!\n" );
		}
	};
	// This is used for pseudo instructions.
	auto find_real_instr_and_with_dot_f = [&]
		( const std::string& orig_name, const instr_args& iargs ) -> void
	{
		const std::string orig_name_dot_f = orig_name + std::string(".f");
		find_real_instr( real_instr_name, real_instr_index, orig_name, 
			iargs, 1 );
		find_real_instr( real_instr_name_dot_f, real_instr_index_dot_f, 
			orig_name_dot_f, iargs, 3 );
	};
	
	
	// Instructions:
	// Load 32-bit value from address (rB + rC + (sign-extended imm)) into
	// rA.
	//ldrxx rA, rB, rC, imm
	insert_instr_and_with_dot_f( "ldrxx", instr_args::ra_rb_rc_imm12s );
	
	// Load zero-extended 16-bit value from address 
	// (rB + rC + (sign-extended imm)) into rA.
	// This zero-extends the value.
	//ldhxx rA, rB, rC, imm
	insert_instr_and_with_dot_f( "ldhxx", instr_args::ra_rb_rc_imm12s );
	
	// Load sign-extended 16-bit value from address 
	// (rB + rC + (sign-extended imm)) into rA.
	// This sign-extends the value.
	//ldshxx rA, rB, rC, imm
	insert_instr_and_with_dot_f( "ldshxx", instr_args::ra_rb_rc_imm12s );
	
	// Load zero-extended 8-bit value from address 
	// (rB + rC + (sign-extended imm)) into rA.
	// This zero-extends the value.
	//ldbxx rA, rB, rC, imm
	insert_instr_and_with_dot_f( "ldbxx", instr_args::ra_rb_rc_imm12s );
	
	
	
	// Load sign-extended 8-bit value from address 
	// (rB + rC + (sign-extended imm)) into rA.
	// This sign-extends the value.
	//ldsbxx rA, rB, rC, imm
	insert_instr_and_with_dot_f( "ldsbxx", instr_args::ra_rb_rc_imm12s );
	
	// Store 32-bit value in rA to address (rB + rC + (sign-extended imm)).
	//strxx rA, rB, rC, imm
	insert_instr_and_with_dot_f( "strxx", instr_args::ra_rb_rc_imm12s );
	
	// Store low 16 bits of rA to address (rB + rC + (sign-extended imm)).
	//sthxx rA, rB, rC, imm
	insert_instr_and_with_dot_f( "sthxx", instr_args::ra_rb_rc_imm12s );
	
	// Store low 8 bits of rA to address (rB + rC + (sign-extended imm)).
	//stbxx rA, rB, rC, imm
	insert_instr_and_with_dot_f( "stbxx", instr_args::ra_rb_rc_imm12s );
	
	
	// rA = rB + rC
	// This instruction can affect N, V, Z, and C flags.
	//add rA, rB, rC
	insert_instr_and_with_dot_f( "add", instr_args::ra_rb_rc );
	
	// rA = rB + rC + carry_flag
	// Add with carry
	// This instruction can affect N, V, Z, and C flags.
	//adc rA, rB, rC
	insert_instr_and_with_dot_f( "adc", instr_args::ra_rb_rc );
	
	// rA = rB - rC
	// This instruction can affect N, V, Z, and C flags.
	//sub rA, rB, rC
	insert_instr_and_with_dot_f( "sub", instr_args::ra_rb_rc );
	
	// rA = rB + (~rC) + carry_flag
	// Subtract with borrow (6502 style)
	// This instruction can affect N, V, Z, and C flags.
	//sbc rA, rB, rC
	insert_instr_and_with_dot_f( "sbc", instr_args::ra_rb_rc );
	
	
	
	// rA = rC - rB
	// This instruction can affect N, V, Z, and C flags.
	//rsb rA, rB, rC
	insert_instr_and_with_dot_f( "rsb", instr_args::ra_rb_rc );
	
	// rA = rB * rC
	//mul rA, rB, rC
	insert_instr_and_with_dot_f( "mul", instr_args::ra_rb_rc );
	
	// rA = rB & rC
	// This instruction can affect the N and Z flags.
	//and rA, rB, rC
	insert_instr_and_with_dot_f( "and", instr_args::ra_rb_rc );
	
	// rA = rB | rC
	// This instruction can affect the N and Z flags.
	//or rA, rB, rC
	insert_instr_and_with_dot_f( "or", instr_args::ra_rb_rc );
	
	
	
	// rA = rB ^ rC
	// This instruction can affect the N and Z flags.
	//xor rA, rB, rC
	insert_instr_and_with_dot_f( "xor", instr_args::ra_rb_rc );
	
	// Logical shift left
	// rA = rB << rC
	//lsl rA, rB, rC
	insert_instr_and_with_dot_f( "lsl", instr_args::ra_rb_rc );
	
	// Logical shift right
	//lsr rA, rB, rC
	insert_instr_and_with_dot_f( "lsr", instr_args::ra_rb_rc );
	
	// Arithmetic shift right
	//asr rA, rB, rC
	insert_instr_and_with_dot_f( "asr", instr_args::ra_rb_rc );
	
	
	
	// Rotate rB left by rC bits, then store result in rA.
	//rol rA, rB, rC
	insert_instr_and_with_dot_f( "rol", instr_args::ra_rb_rc );
	
	// Rotate rB right by rC bits, then store result in rA.
	//ror rA, rB, rC
	insert_instr_and_with_dot_f( "ror", instr_args::ra_rb_rc );
	
	// Fused multiply-add
	// rA = rA + (rB * rC)
	//fma rA, rB, rC
	insert_instr_and_with_dot_f( "fma", instr_args::ra_rb_rc );
	
	// Copy rC to rA and to rB
	// If rA is the same register as rB, then the 
	// register will only be written once.
	//cpyp rA, rB, rC
	insert_instr_and_with_dot_f( "cpyp", instr_args::ra_rb_rc );
	
	
	
	// Set pc to destination address in (rA + rB).
	//jumpx rA, rB
	insert_instr_and_with_dot_f( "jumpx", instr_args::ra_rb );
	
	// Add 4 to rB, then load from address in rB into
	// rA
	// LoaD Register, Add Before
	//ldrpb rA, rB
	insert_instr_and_with_dot_f( "ldrpb", instr_args::ra_rb );
	
	// Store rA to address in rB, then subtract 4 from
	// rB
	// STore Register, Subtract After
	//strma rA, rB
	insert_instr_and_with_dot_f( "strma", instr_args::ra_rb );
	
	// Reserved for future expansion.
	
	
	
	// Reserved for future expansion.
	// Reserved for future expansion.
	// Reserved for future expansion.
	// Reserved for future expansion.
	
	
	
	// Pseudo instruction:
	//// Load 32-bit value from address rB into rA.
	//// Encoded like this:  ldrxx rA, rB, r0, 0 
	//ldr rA, rB
	find_real_instr_and_with_dot_f( "ldrxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "ldr",
		instr_args::pseudo_ra_rb_r0hidden_imm0hidden );
	
	// Pseudo instruction:
	//// Load zero-extended 16-bit value from address rB into rA.
	//// This zero-extends the value.
	//// Encoded like this:  ldhxx rA, rB, r0, 0 
	//ldh rA, rB
	find_real_instr_and_with_dot_f( "ldhxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "ldh",
		instr_args::pseudo_ra_rb_r0hidden_imm0hidden );
	
	// Pseudo instruction:
	//// Load sign-extended 16-bit value from address rB into rA.
	//// This sign-extends the value.
	//// Encoded like this:  ldshxx rA, rB, r0, 0 
	//ldsh rA, rB
	find_real_instr_and_with_dot_f( "ldshxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "ldsh",
		instr_args::pseudo_ra_rb_r0hidden_imm0hidden );
	
	// Pseudo instruction:
	//// Load zero-extended 8-bit value from address rB into rA.
	//// This zero-extends the value.
	//// Encoded like this:  ldbxx rA, rB, r0, 0 
	//ldb rA, rB
	find_real_instr_and_with_dot_f( "ldbxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "ldb",
		instr_args::pseudo_ra_rb_r0hidden_imm0hidden );
	
	
	
	// Pseudo instruction:
	//// Load sign-extended 8-bit value from address rB into rA.
	//// This sign-extends the value.
	//// Encoded like this:  ldsbxx rA, rB, r0, 0 
	//ldsb rA, rB
	find_real_instr_and_with_dot_f( "ldsbxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "ldsb",
		instr_args::pseudo_ra_rb_r0hidden_imm0hidden );
	
	// Pseudo instruction:
	//// Store 32-bit value in rA to address rB.
	//// Encoded like this:  strxx rA, rB, r0, 0 
	//str rA, rB
	find_real_instr_and_with_dot_f( "strxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "str",
		instr_args::pseudo_ra_rb_r0hidden_imm0hidden );
	
	// Pseudo instruction:
	//// Store low 16 bits of rA to address rB.
	//// Encoded like this:  sthxx rA, rB, r0, 0 
	//sth rA, rB
	find_real_instr_and_with_dot_f( "sthxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "sth",
		instr_args::pseudo_ra_rb_r0hidden_imm0hidden );
	
	// Pseudo instruction:
	//// Store low 8 bits of rA to address rB.
	//// Encoded like this:  stbxx rA, rB, r0, 0 
	//stb rA, rB
	find_real_instr_and_with_dot_f( "stbxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "stb",
		instr_args::pseudo_ra_rb_r0hidden_imm0hidden );
	
	
	
	// Pseudo instruction:
	//// Load 32-bit value from address (rB + rC) into rA.
	//// Encoded like this:  ldrxx rA, rB, rC, 0 
	//ldrx rA, rB, rC
	find_real_instr_and_with_dot_f( "ldrxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "ldrx",
		instr_args::pseudo_ra_rb_rc_imm0hidden );
	
	// Pseudo instruction:
	//// Load zero-extended 16-bit value from address (rB + rC) into rA.
	//// This zero-extends the value.
	//// Encoded like this:  ldhxx rA, rB, rC, 0 
	//ldhx rA, rB, rC
	find_real_instr_and_with_dot_f( "ldhxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "ldhx",
		instr_args::pseudo_ra_rb_rc_imm0hidden );
	
	// Pseudo instruction:
	//// Load sign-extended 16-bit value from address (rB + rC) into rA.
	//// This sign-extends the value.
	//// Encoded like this:  ldshxx rA, rB, rC, 0 
	//ldshx rA, rB, rC
	find_real_instr_and_with_dot_f( "ldshxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "ldshx",
		instr_args::pseudo_ra_rb_rc_imm0hidden );
	
	// Pseudo instruction:
	//// Load zero-extended 8-bit value from address (rB + rC) into rA.
	//// This zero-extends the value.
	//// Encoded like this:  ldbxx rA, rB, rC, 0 
	//ldbx rA, rB, rC
	find_real_instr_and_with_dot_f( "ldbxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "ldbx",
		instr_args::pseudo_ra_rb_rc_imm0hidden );
	
	
	
	// Pseudo instruction:
	//// Load sign-extended 8-bit value from address (rB + rC) into rA.
	//// This sign-extends the value.
	//// Encoded like this:  ldsbxx rA, rB, rC, 0 
	//ldsbx rA, rB, rC
	find_real_instr_and_with_dot_f( "ldsbxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "ldsbx",
		instr_args::pseudo_ra_rb_rc_imm0hidden );
	
	// Pseudo instruction:
	//// Store 32-bit value in rA to address (rB + rC).
	//// Encoded like this:  strxx rA, rB, rC, 0 
	//strx rA, rB, rC
	find_real_instr_and_with_dot_f( "strxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "strx",
		instr_args::pseudo_ra_rb_rc_imm0hidden );
	
	// Pseudo instruction:
	//// Store low 16 bits of rA to address (rB + rC).
	//// Encoded like this:  sthxx rA, rB, rC, 0 
	//sthx rA, rB, rC
	find_real_instr_and_with_dot_f( "sthxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "sthx",
		instr_args::pseudo_ra_rb_rc_imm0hidden );
	
	// Pseudo instruction:
	//// Store low 8 bits of rA to address (rB + rC).
	//// Encoded like this:  stbxx rA, rB, rC, 0 
	//stbx rA, rB, rC
	find_real_instr_and_with_dot_f( "stbxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "stbx",
		instr_args::pseudo_ra_rb_rc_imm0hidden );
	
	
	
	// Pseudo instruction:
	//// Load 32-bit value from address (rB + (sign-extended imm)) into rA.
	//// Encoded like this:  ldrxx rA, rB, r0, imm 
	//ldrxi rA, rB, imm
	find_real_instr_and_with_dot_f( "ldrxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "ldrxi",
		instr_args::pseudo_ra_rb_r0hidden_imm12s );
	
	// Pseudo instruction:
	//// Load zero-extended 16-bit value from address (rB + (sign-extended imm)) into rA.
	//// This zero-extends the value.
	//// Encoded like this:  ldhxx rA, rB, r0, imm 
	//ldhxi rA, rB, imm
	find_real_instr_and_with_dot_f( "ldhxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "ldhxi",
		instr_args::pseudo_ra_rb_r0hidden_imm12s );
	
	// Pseudo instruction:
	//// Load sign-extended 16-bit value from address (rB + (sign-extended imm)) into rA.
	//// This sign-extends the value.
	//// Encoded like this:  ldshxx rA, rB, r0, imm 
	//ldshxi rA, rB, imm
	find_real_instr_and_with_dot_f( "ldshxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "ldshxi",
		instr_args::pseudo_ra_rb_r0hidden_imm12s );
	
	// Pseudo instruction:
	//// Load zero-extended 8-bit value from address (rB + (sign-extended imm)) into rA.
	//// This zero-extends the value.
	//// Encoded like this:  ldbxx rA, rB, r0, imm 
	//ldbxi rA, rB, imm
	find_real_instr_and_with_dot_f( "ldbxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "ldbxi",
		instr_args::pseudo_ra_rb_r0hidden_imm12s );
	
	
	
	// Pseudo instruction:
	//// Load sign-extended 8-bit value from address (rB + (sign-extended imm)) into rA.
	//// This sign-extends the value.
	//// Encoded like this:  ldsbxx rA, rB, r0, imm 
	//ldsbxi rA, rB, imm
	find_real_instr_and_with_dot_f( "ldsbxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "ldsbxi",
		instr_args::pseudo_ra_rb_r0hidden_imm12s );
	
	// Pseudo instruction:
	//// Store 32-bit value in rA to address (rB + (sign-extended imm)).
	//// Encoded like this:  strxx rA, rB, r0, imm 
	//strxi rA, rB, imm
	find_real_instr_and_with_dot_f( "strxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "strxi",
		instr_args::pseudo_ra_rb_r0hidden_imm12s );
	
	// Pseudo instruction:
	//// Store low 16 bits of rA to address (rB + (sign-extended imm)).
	//// Encoded like this:  sthxx rA, rB, r0, imm 
	//sthxi rA, rB, imm
	find_real_instr_and_with_dot_f( "sthxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "sthxi",
		instr_args::pseudo_ra_rb_r0hidden_imm12s );
	
	// Pseudo instruction:
	//// Store low 8 bits of rA to address (rB + (sign-extended imm)).
	//// Encoded like this:  stbxx rA, rB, r0, imm 
	//stbxi rA, rB, imm
	find_real_instr_and_with_dot_f( "stbxx", 
		instr_args::ra_rb_rc_imm12s );
	insert_instr_and_with_dot_f( "stbxi",
		instr_args::pseudo_ra_rb_r0hidden_imm12s );
	
	
	
	// Pseudo instruction:
	//// temp = rB - rC
	//// This instruction can affect N, V, Z, and C flags.
	//// Encoded like this:  sub.f r0, rB, rC
	//cmp rB, rC
	find_real_instr( real_instr_name_dot_f, real_instr_index_dot_f, 
		"sub.f", instr_args::ra_rb_rc );
	insert_instr( sym_dot_f, std::string("cmp"), 
		instr_args::pseudo_r0hidden_rb_rc, real_instr_name_dot_f, 
		real_instr_index_dot_f );
	
	// Pseudo instruction:
	//// temp = rB - (-rC)
	//// This instruction can affect N, V, Z, and C flags.
	//// Encoded like this:  add.f r0, rB, rC
	//cmn rB, rC
	find_real_instr( real_instr_name_dot_f, real_instr_index_dot_f, 
		"add.f", instr_args::ra_rb_rc );
	insert_instr( sym_dot_f, std::string("cmn"), 
		instr_args::pseudo_r0hidden_rb_rc, real_instr_name_dot_f, 
		real_instr_index_dot_f );
	
	// Pseudo instruction:
	//// temp = rC - rB
	//// This instruction can affect N, V, Z, and C flags.
	//// Encoded like this:  rsb.f r0, rB, rC
	//cmr rB, rC
	find_real_instr( real_instr_name_dot_f, real_instr_index_dot_f, 
		"rsb.f", instr_args::ra_rb_rc );
	insert_instr( sym_dot_f, std::string("cmr"), 
		instr_args::pseudo_r0hidden_rb_rc, real_instr_name_dot_f, 
		real_instr_index_dot_f );
	
	// Pseudo instruction:
	//// temp = rB & rC
	//// Encoded like this:  and.f r0, rB, rC
	//// This instruction can affect the N and Z flags.
	//tst rB, rC
	find_real_instr_and_with_dot_f( "and", instr_args::ra_rb_rc );
	insert_instr_and_with_dot_f( "tst", 
		instr_args::pseudo_r0hidden_rb_rc );
	
	
	
	// Pseudo instruction:
	//// Copy
	//// rA = rC
	//// Encoded like this:  cpyp rA, rA, rC
	//cpy rA, rC
	find_real_instr_and_with_dot_f( "cpyp", instr_args::ra_rb_rc );
	insert_instr_and_with_dot_f( "cpy", 
		instr_args::pseudo_ra_rahidden_rc );
	
	// Pseudo instruction:
	//// Set pc to destination address in rB.
	//// Encoded like this:  jumpx r0, rB
	//jump rB
	find_real_instr_and_with_dot_f( "jumpx", instr_args::ra_rb );
	insert_instr_and_with_dot_f( "jump", instr_args::pseudo_r0hidden_rb );
	
	// Pseudo instruction:
	//// Set pc to destination address in rB.
	//// Encoded like this:  jumpx r0, rB
	//cpy pc, rB
	find_real_instr_and_with_dot_f( "jumpx", instr_args::ra_rb );
	insert_instr_and_with_dot_f( "cpy", instr_args::pseudo_pc_rb );
	
	// Pseudo instruction:
	//// Push register rA onto the stack
	//// Encoded like this:  strma rA, sp
	//push rA
	find_real_instr_and_with_dot_f( "strma", instr_args::ra_rb );
	insert_instr_and_with_dot_f( "push", instr_args::pseudo_ra_sphidden );
	
	
	
	// Pseudo instruction:
	//// Pop 32-bit value off the stack into register rA
	//// Encoded like this:  ldrpb rA, sp
	//pop rA
	find_real_instr_and_with_dot_f( "ldrpb", instr_args::ra_rb );
	insert_instr_and_with_dot_f( "pop", instr_args::pseudo_ra_sphidden );
}
void assembler::insert_grp_3_instructions()
{
	static constexpr size_t grp = 3;
	size_t opcode = 0;
	symbol * sym, * sym_dot_f;
	std::string real_instr_name, real_instr_name_dot_f;
	size_t real_instr_index = 0, real_instr_index_dot_f = 0;
	
	auto insert_instr_keep_opcode = [ this, &opcode ]
		( symbol*& some_sym, const std::string& some_orig_name, 
		const instr_args& iargs, 
		const std::string& some_real_instr_name="", 
		size_t some_real_instr_index=0 ) 
		-> void
	{
		some_sym = &special_sym_tbl.enter( some_orig_name, 
			cast_typ(tok_defn::instr), 0, true );
		instr_tbl.enter( some_orig_name, opcode, grp, iargs, 
			some_real_instr_name, some_real_instr_index );
	};
	auto insert_instr = [ this, &insert_instr_keep_opcode, &opcode ]
		(  symbol*& some_sym, const std::string& some_orig_name, 
		const instr_args& iargs, 
		const std::string& some_real_instr_name="",
		size_t some_real_instr_index=0 )
		-> void
	{
		insert_instr_keep_opcode( some_sym, some_orig_name, iargs, 
			some_real_instr_name, some_real_instr_index );
		++opcode;
	};
	// This inserts an instruction and also one with ".f" appended to its
	// name.
	auto insert_instr_and_with_dot_f = [&]( const std::string& orig_name, 
		const instr_args& iargs ) -> void
	{
		std::string temp_name_0 = orig_name;
		std::string temp_name_1 = temp_name_0 + std::string(".f");
		insert_instr_keep_opcode( sym, temp_name_0, iargs,
			real_instr_name, real_instr_index );
		insert_instr_keep_opcode( sym_dot_f, temp_name_1, iargs,
			real_instr_name_dot_f, real_instr_index_dot_f );
		
		++opcode;
	};
	auto find_real_instr = [this]( std::string& some_real_instr_name,
		size_t& some_real_instr_index, const std::string& some_orig_name, 
		const instr_args& iargs, size_t eek_number=1 ) -> void
	{
		symbol* some_sym;
		
		if (!special_sym_tbl.find( some_sym, some_orig_name ))
		{
			we.error( "assembler constructor (", some_orig_name, 
				", group ", grp, "):  Eek ", eek_number, "!\n" );
		}
		
		const auto& some_instr_vec = instr_tbl.at(some_orig_name);
		
		some_real_instr_name = "";
		some_real_instr_index = 0;
		for ( size_t i=0; i<some_instr_vec.size(); ++i )
		{
			const instruction& iter = some_instr_vec.at(i);
			if ( iter.iargs() == iargs )
			{
				some_real_instr_name = iter.name();
				some_real_instr_index = i;
				break;
			}
		}
		
		if ( some_real_instr_name.size() == 0 )
		{
			we.error( "assembler constructor (", some_orig_name, 
				", group ", grp, "):  Eek ", ( eek_number + 1 ), "!\n" );
		}
	};
	// This is used for pseudo instructions.
	auto find_real_instr_and_with_dot_f = [&]
		( const std::string& orig_name, const instr_args& iargs ) -> void
	{
		const std::string orig_name_dot_f = orig_name + std::string(".f");
		find_real_instr( real_instr_name, real_instr_index, orig_name, 
			iargs, 1 );
		find_real_instr( real_instr_name_dot_f, real_instr_index_dot_f, 
			orig_name_dot_f, iargs, 3 );
	};
	
	
	// Instructions:
	// Load 32-bit value from address (absolute_addr + rB) into rA.
	//ldra rA, rB, absolute_addr
	insert_instr_and_with_dot_f( "ldra", instr_args::ra_rb_abs );
	
	// Load zero-extended 16-bit value from address (absolute_addr + rB)
	// into rA.
	// This zero-extends the value.
	//ldha rA, rB, absolute_addr
	insert_instr_and_with_dot_f( "ldha", instr_args::ra_rb_abs );
	
	// Load sign-extended 16-bit value from address (absolute_addr + rB)
	// into rA.
	// This sign-extends the value.
	//ldsha rA, rB, absolute_addr
	insert_instr_and_with_dot_f( "ldsha", instr_args::ra_rb_abs );
	
	// Load zero-extended 8-bit value from address (absolute_addr + rB)
	// into rA.
	// This zero-extends the value.
	//ldba rA, rB, absolute_addr
	insert_instr_and_with_dot_f( "ldba", instr_args::ra_rb_abs );
	
	
	
	// Load sign-extended 8-bit value from address (absolute_addr + rB)
	// into rA.
	// This sign-extends the value.
	//ldsba rA, rB, absolute_addr
	insert_instr_and_with_dot_f( "ldsba", instr_args::ra_rb_abs );
	
	// Store 32-bit value in rA to address (absolute_addr + rB).
	//stra rA, rB, absolute_addr
	insert_instr_and_with_dot_f( "stra", instr_args::ra_rb_abs );
	
	// Store low 16 bits of rA to address (absolute_addr + rB).
	//stha rA, rB, absolute_addr
	insert_instr_and_with_dot_f( "stha", instr_args::ra_rb_abs );
	
	// Store low 8 bits of rA to address (absolute_addr + rB).
	//stba rA, rB, absolute_addr
	insert_instr_and_with_dot_f( "stba", instr_args::ra_rb_abs );
	
	
	
	// Set pc to destination address in (rA + rB + absolute_addr).
	//jumpa rA, rB, absolute_addr
	insert_instr_and_with_dot_f( "jumpa", instr_args::ra_rb_abs );
	
	// Subroutine call using (rA + rB + absolute_addr) as destination
	// address. 
	// The return address is stored in the link register (lr).
	//calla rA, rB, absolute_addr
	insert_instr_and_with_dot_f( "calla", instr_args::ra_rb_abs );
	
	// rA = 32-bit immediate, rB = same 32-bit immediate
	// If rA is the same register as rB, then the 
	// register will only be written once.
	//cpypi rA, rB, imm
	insert_instr_and_with_dot_f( "cpypi", instr_args::ra_rb_abs );
	
	// Reserved for future expansion.
	
	
	
	// Reserved for future expansion.
	// Reserved for future expansion.
	// Reserved for future expansion.
	// Reserved for future expansion.
	
	
	
	// Reserved for future expansion.
	// Reserved for future expansion.
	// Reserved for future expansion.
	// Reserved for future expansion.
	
	
	
	// Reserved for future expansion.
	// Reserved for future expansion.
	// Reserved for future expansion.
	// Reserved for future expansion.
	
	
	
	// Reserved for future expansion.
	// Reserved for future expansion.
	// Reserved for future expansion.
	// Reserved for future expansion.
	
	
	
	// Reserved for future expansion.
	// Reserved for future expansion.
	// Reserved for future expansion.
	// Reserved for future expansion.
	
	
	
	// Pseudo instruction:
	//// Set pc to destination address in (rA + absolute_addr).
	//// Encoded like this:  jumpa rA, r0, absolute_addr
	//jumpa rA, absolute_addr
	find_real_instr_and_with_dot_f( "jumpa", instr_args::ra_rb_abs );
	insert_instr_and_with_dot_f( "jumpa",
		instr_args::pseudo_ra_r0hidden_abs );
	
	// Pseudo instruction:
	//// Set pc to destination address in (absolute_addr).
	//// Encoded like this:  jumpa r0, r0, absolute_addr
	//jumpa absolute_addr
	find_real_instr_and_with_dot_f( "jumpa", instr_args::ra_rb_abs );
	insert_instr_and_with_dot_f( "jumpa",
		instr_args::pseudo_r0hidden_r0hidden_abs );
	
	
	// Pseudo instruction:
	//// Subroutine call using (rA + absolute_addr) as 
	//// destination address.  The return address is stored in the link
	//// register (lr).
	// Encoded like this:  calla rA, r0, absolute_addr
	//calla rA, absolute_addr
	find_real_instr_and_with_dot_f( "calla", instr_args::ra_rb_abs );
	insert_instr_and_with_dot_f( "calla",
		instr_args::pseudo_ra_r0hidden_abs );
	
	// Pseudo instruction:
	//// Subroutine call using (absolute_addr) as destination address. 
	//// The return address is stored in the link register (lr).
	//// Encoded like this:  calla r0, r0, absolute_addr
	//calla absolute_addr
	find_real_instr_and_with_dot_f( "calla", instr_args::ra_rb_abs );
	insert_instr_and_with_dot_f( "calla",
		instr_args::pseudo_r0hidden_r0hidden_abs );
	
	
	
	// Pseudo instruction:
	//// rA = 32-bit immediate
	//// Encoded like this:  cpypi rA, rA, imm
	//cpyi rA, imm
	find_real_instr_and_with_dot_f( "cpypi", instr_args::ra_rb_abs );
	insert_instr_and_with_dot_f( "cpyi",
		instr_args::pseudo_ra_rahidden_abs );
}



}
