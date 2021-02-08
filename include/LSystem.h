#pragma once

#include <vector>
#include <string>

class LSystem {

public:
	//default constructor
	LSystem() = default;

	//copy constructor
	LSystem(const LSystem& o) = default;
	//copy assignment
	LSystem& operator =(const LSystem& o) = default;

	//move constructor
	LSystem(LSystem&& o) = default;
	//move assignment
	LSystem& operator =(LSystem&& o) = default;

	~LSystem();


	void AddVariables(std::initializer_list<char> var_init);
	std::vector<char> GetVariables();

	void AddConstants(std::initializer_list<char> var_init);
	std::vector<char> GetConstants();

	void AddRule(char input, std::vector<char> rule);
	std::vector<std::pair<char, std::vector<char>>> GetRules();

	void AddAxiom(std::initializer_list<char> new_axiom);
	std::vector<char> GetAxiom();
	
	std::vector<char> ExecuteSystem(size_t num_executions);
	void ResetSystem();

private:
	std::vector<char> variables_;
	std::vector<char> constants_;
	std::vector<char> axiom_;

	std::vector<std::pair<char, std::vector<char>>> rules_; //input is char and output is vector of chars

};