#ifndef assembler_class_hpp
#define assembler_class_hpp


#include "misc_includes.hpp"


#include "symbol_table_class.hpp"
#include "define_table_class.hpp"


namespace flare32
{

class Assembler
{
private:		// classes
	class ParsePos
	{
	public:		// variables
		s64 outer_index = 0;
		s64 inner_index = 0;
	};
	class ParseNode
	{
	public:		// variables
		PTok next_tok = nullptr;
		std::string next_sym_str;
		s64 next_num = -1;

	public:		// functions
		inline ParseNode()
		{
		}


		inline ParseNode(PTok s_next_tok, 
			const std::string& s_next_sym_str, s64 s_next_num)
			: next_tok(s_next_tok), next_sym_str(s_next_sym_str),
			next_num(s_next_num)
		{
		}

		inline ParseNode(const ParseNode& to_copy) = default;
		inline ParseNode(ParseNode&& to_move) = default;
		inline ParseNode& operator = (const ParseNode& to_copy) = default;
		inline ParseNode& operator = (ParseNode&& to_move) = default;
	};

private:		// variables
	static constexpr size_t define_expand_max_depth = 256;
	static constexpr size_t last_pass = 2;
	SymbolTable __builtin_sym_tbl, __user_sym_tbl;
	DefineTable __define_tbl;
	InstructionTable __instr_tbl;

	std::vector<std::string> __lines;


	// Where are we in the generated binary?
	size_t __addr = 0, __last_addr = -1;

	// Where are we in the file?
	size_t __line_num = 0;

	int __next_char = ' ';
	PTok __next_tok = nullptr;
	std::string __next_sym_str;
	s64 __next_num = -1;

	bool __changed = false;
	s32 __pass = 0;

	char* __input_filename = nullptr;
	std::FILE* __infile = nullptr;

public:		// functions
	Assembler(char* s_input_filename);

	int operator () ();



private:		// functions
	gen_getter_by_ref(builtin_sym_tbl);
	gen_getter_by_ref(user_sym_tbl);
	gen_getter_by_ref(define_tbl);
	gen_getter_by_ref(instr_tbl);

	gen_getter_and_setter_by_val(addr);
	gen_getter_and_setter_by_val(last_addr);
	gen_getter_and_setter_by_val(line_num);
	gen_getter_and_setter_by_val(next_char);
	gen_getter_and_setter_by_val(next_tok);
	gen_getter_and_setter_by_con_ref(next_sym_str);
	gen_getter_and_setter_by_val(next_num);
	gen_getter_and_setter_by_val(changed);
	gen_getter_and_setter_by_val(pass);
	gen_getter_and_setter_by_val(input_filename);
	gen_getter_and_setter_by_val(infile);


	void reinit();
	void fill_builtin_sym_tbl();

	template<typename... ArgTypes>
	void err_suffix(ArgTypes&&... args) const
	{
		printerr(", On line ", line_num(), ":  ", args..., "\n");
		exit(1);
	}
	template<typename... ArgTypes>
	void err(ArgTypes&&... args) const
	{
		printerr("Error");
		err_suffix(args...);
	}

	template<typename... ArgTypes>
	void expected(ArgTypes&&... args) const
	{
		err("Expected ", args...);
	}


	void __expected_tokens_innards() const
	{
	}
	template<typename... RemArgTypes>
	void __expected_tokens_innards(PTok tok, RemArgTypes&&... rem_args)
		const
	{
		printerr("\"", tok->str(), "\"");

		if (sizeof...(rem_args) > 0)
		{
			printerr(" or ");
			__expected_tokens_innards(rem_args...);
		}
	}
	
	template<typename... ArgTypes>
	void expected_tokens(ArgTypes&&... args) const
	{
		printerr("Error, On line ", line_num(), ":  ");
		printerr("Expected token of type ");
		__expected_tokens_innards(args...);
		printerr("!\n");
		exit(1);
	}


	void need(const std::vector<ParseNode>& some_parse_vec, size_t& index, 
		PTok tok);

	void __advance_innards(int& some_next_char, 
		PTok& some_next_tok, std::string& some_next_sym_str,
		s64& some_next_num, size_t& some_line_num,
		size_t& some_outer_index, size_t& some_inner_index,
		std::vector<std::string>* some_str_vec=nullptr);
	void __lex_innards(int& some_next_char, 
		PTok& some_next_tok, std::string& some_next_sym_str,
		s64& some_next_num, size_t& some_line_num,
		size_t& some_outer_index, size_t& some_inner_index,
		std::vector<std::string>* some_str_vec=nullptr,
		ParsePos* pos=nullptr);
	inline void advance(size_t& some_outer_index, size_t& some_inner_index,
		bool use_lines=false)
	{
		__advance_innards(__next_char, __next_tok,
			__next_sym_str, __next_num, __line_num, 
			some_outer_index, some_inner_index,
			(use_lines ? &__lines : nullptr));
	}
	inline void lex(size_t& some_outer_index, size_t& some_inner_index,
		bool use_lines=false)
	{
		__lex_innards(__next_char, __next_tok,
			__next_sym_str, __next_num, __line_num, 
			some_outer_index, some_inner_index,
			(use_lines ? &__lines : nullptr));
	}
	//inline void lex(size_t& some_outer_index, size_t& some_inner_index,
	//	std::vector<std::string>& some_lines)
	//{
	//	__lex_innards(__next_char, __next_tok,
	//		__next_sym_str, __next_num, __line_num, 
	//		some_outer_index, some_inner_index, &some_lines);
	//}

	void line(size_t& some_outer_index, size_t& some_inner_index, 
		bool just_find_defines=false);
	void finish_line(const std::vector<ParseNode>& some_parse_vec);

	void fill_lines();
	void find_defines();
	void expand_defines();


	bool parse_instr(PInstr instr, 
		const std::vector<ParseNode>& some_parse_vec);

	bool __parse_instr_no_args
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_uimm16
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_simm16
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_imm32
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);

	bool __parse_instr_ra
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ra_uimm16
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ra_rb
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ra_rb_uimm16
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ra_rb_simm16
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ra_rb_rc
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ra_rb_rc_simm12
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);

	bool __parse_instr_ldst_ra_rb
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ldst_ra_rb_rc_simm12
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ldst_ra_rb_rc
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ldst_ra_rb_simm12
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);


	bool __parse_instr_branch
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);


	bool __parse_instr_ldst_ra_rb_imm32
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ra_rb_imm32
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);


	// Block moves (ldmia, stmia, stmdb) with number of {} args
	bool __parse_instr_ldst_block_1_to_4
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ldst_block_5_to_8
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);

	bool __parse_instr_ira
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ra_ira
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_ira_ra
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);

	bool __parse_instr_ra_flags
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_flags
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);
	bool __parse_instr_flags_ra
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);

	bool __parse_instr_ra_pc
		(const std::vector<ParseNode>& some_parse_vec, PInstr instr);


	s64 handle_term(const std::vector<ParseNode>& some_parse_vec, 
		size_t& index);
	s64 handle_factor(const std::vector<ParseNode>& some_parse_vec, 
		size_t& index);
	s64 handle_expr(const std::vector<ParseNode>& some_parse_vec, 
		size_t& index);

	bool tok_is_punct(PTok some_tok) const;
	bool tok_is_ident_ish(PTok some_tok) const;
	bool tok_is_comment(PTok some_tok) const;

	//inline bool next_tok_is_punct() const
	//{
	//	return tok_is_punct(next_tok());
	//}
	//inline bool next_tok_is_ident_ish() const
	//{
	//	return tok_is_ident_ish(next_tok());
	//}

	// Code generator stuff
	inline void __encode_instr_group(u16& high_hword, PInstr instr) const
	{
		clear_and_set_bits_with_range(high_hword, instr->enc_group(),
			15, 14);
	}
	inline void __encode_affects_flags(u16& high_hword, PInstr instr) const
	{
		clear_and_set_bits_with_range(high_hword, instr->affects_flags(),
			13, 13);
	}
	void __encode_opcode(u16& high_hword, PInstr instr) const;
	void __encode_high_hword(u16& high_hword, 
		const std::vector<std::string>& regs, s64 expr_result,
		PInstr instr);
	void __encode_low(u16& g1g2_low, u32& g3_low, 
		const std::vector<std::string>& regs, s64 expr_result,
		PInstr instr);
	void __gen_low(u16 g1g2_low, u32 g3_low, PInstr instr);
	void encode_and_gen(const std::vector<std::string>& regs, 
		s64 expr_result, PInstr instr);
	
	void split(std::vector<ParseNode>& ret, 
		std::vector<std::string>& to_split,
		std::vector<ParsePos>* pos_vec=nullptr);



	bool __check_tokens_innards
		(const std::vector<ParseNode>& some_parse_vec, size_t index, 
		PTok tok) const
	{
		return (some_parse_vec.at(index).next_tok == tok);
	}

	inline bool check_tokens(const std::vector<ParseNode>& some_parse_vec,
		size_t& index) const
	{
		return true;
	}

	template<typename... RemArgTypes>
	bool check_tokens(const std::vector<ParseNode>& some_parse_vec,
		size_t& index, PTok tok, RemArgTypes&&... rem_args) const
	{
		if (__check_tokens_innards(some_parse_vec, index++, tok))
		{
			return check_tokens(some_parse_vec, index, rem_args...);
		}

		return false;
	}

	void gen8(s32 v);
	void gen16(s32 v);
	void gen32(s32 v);


};

}

#endif		// assembler_class_hpp
