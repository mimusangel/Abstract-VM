#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include "VMList.hpp"
#include "Manager.hpp"
#include "IOperand.hpp"

class Parser {
private:
	enum eInstructionType {
		PUSH,
		POP,
		DUMP,
		ASSERT,
		ADD,
		SUB,
		MUL,
		DIV,
		MOD,
		PRINT,
		EXIT
	};
	class Instruction {
	public:
		eInstructionType    type;
		eOperandType    	valueType;
		std::string     	value;

		Instruction(eInstructionType t, eOperandType vt = INT8, std::string v = std::string()) :
			type(t), valueType(vt), value(v)
		{}
		bool    execute(Manager &manager);
	};

	VMList<Instruction> _instruction;
	std::string         _file;
	bool                run;
	
	std::string             trim(std::string const &str);
	void                    replaceAll(std::string &str, const std::string &from, const std::string &to);
	void                    norme(std::string &str);
	VMList<std::string>     split(std::string const &str);
	bool                    arg_type_test(std::string const &arg);
	bool                    arg_digit_test(std::string const &type, std::string const &arg);
	bool                    arg_end_test(std::string const &arg);
	eOperandType			arg_get_type(std::string const &type);
	int                     line_interpret(int line, std::string &lineStr);
	void                    lines_interpret(std::ifstream *ifs, bool in);
public:
	Parser(std::string const &file);
	bool    interpret(void);
	void    execute(Manager &manager);
};

#endif
//ofstream