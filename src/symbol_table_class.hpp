#ifndef symbol_table_class_hpp
#define symbol_table_class_hpp

#include "token_stuff.hpp"

namespace assembler
{

class symbol
{
private:		// variables
	string_view internal_name;
	tok internal_typ = 0;
	int internal_val = 0;
	size_t internal_instr_grp = 0;
	bool internal_has_dot_f = false;
	
private:		// functions
	gen_setter_by_con_ref(name);
	gen_setter_by_val(typ);
	gen_setter_by_val(val);
	gen_setter_by_val(instr_grp);
	gen_setter_by_val(has_dot_f);
	
public:		// functions
	inline symbol()
	{
	}
	inline symbol( const string_view& s_name, tok s_typ, int s_val,
		size_t s_instr_grp, bool s_has_dot_f )
	{
		set_name(s_name);
		set_typ(s_typ);
		set_val(s_val);
		set_instr_grp(s_instr_grp);
		set_has_dot_f(s_has_dot_f);
	}
	virtual inline ~symbol()
	{
	}
	
	inline symbol& operator = ( const symbol& other ) = default;
	
	gen_getter_by_con_ref(name);
	gen_getter_by_val(typ);
	gen_getter_by_val(val);
	gen_getter_by_val(instr_grp);
	gen_getter_by_val(has_dot_f);
	
	
};


class symbol_table
{
private:		// variables
	// Prevent duplicate std::strings, should be okay, not the fastest
	// thing I could ever do, though.
	std::unordered_set<std::string> internal_str_set;
	std::unordered_map< string_view, symbol > internal_table;
	
	
private:		// functions
	gen_getter_by_ref(str_set);
	gen_getter_by_ref(table);
	
	bool sym_name_has_dot_f( const string_view& name ) const;
	
	string_view get_name( std::string&& name_as_str );
	
public:		// functions
	inline symbol_table()
	{
	}
	virtual inline ~symbol_table()
	{
	}
	
	symbol& enter( std::string&& name_as_str, tok typ, 
		int val, size_t instr_grp=-1 );
	void erase( const std::string& name_as_str );
	
	gen_getter_by_con_ref(str_set);
	gen_getter_by_con_ref(table);
	
};


}


#endif		// symbol_table_class_hpp
