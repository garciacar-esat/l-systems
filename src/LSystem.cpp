#include "LSystem.h"

#include <algorithm>
#include <iostream>
LSystem::~LSystem()
{
	ResetSystem();
}

void LSystem::AddVariables(std::initializer_list<char> var_init)
{
	//create final var initializer list
	std::vector<char> new_var_init;

	//check if any new variables are already in constants
	for (auto& s : var_init) {
		if (std::find(constants_.begin(), constants_.end(), s) != constants_.end()) {
			std::cout << "[ERROR]: " << s << " already in constants!" << std::endl;
		}
		else {
			new_var_init.emplace_back(s);
		}
	}



	//add to variables vector
	variables_.insert(variables_.begin(), new_var_init.begin(), new_var_init.end());



	//delete any variables that were already there
	sort(variables_.begin(), variables_.end());
	variables_.erase(std::unique(variables_.begin(), variables_.end()), variables_.end());
}

std::vector<char> LSystem::GetVariables()
{
	return variables_;
}

void LSystem::AddConstants(std::initializer_list<char> var_init)
{
	//create final var initializer list
	std::vector<char> new_var_init;

	//check if any new constants are already in variables
	for (auto& s : var_init) {
		if (std::find(variables_.begin(), variables_.end(), s) != variables_.end()) {
			std::cout << "[ERROR]: " << s << " already in variables!" << std::endl;
		}
		else {
			new_var_init.emplace_back(s);
		}
	}


	//add to constants vector
	constants_.insert(constants_.begin(), new_var_init.begin(), new_var_init.end());

	//delete any constants that were already there
	sort(constants_.begin(), constants_.end());
	constants_.erase(std::unique(constants_.begin(), constants_.end()), constants_.end());
}

std::vector<char> LSystem::GetConstants()
{
	return constants_;
}




void LSystem::AddRule(char input, std::vector<char> rule)
{
	//if the input is a constant
	if (std::find(constants_.begin(), constants_.end(), input) != constants_.end()) {
		std::cout << "[ERROR]: " << input << " is a constant!" << std::endl;
		return;
	}

	//if the input is not on the variables list
	if (std::find(variables_.begin(), variables_.end(), input) == variables_.end()) {
		std::cout << "[ERROR]: " << input << " not in variables!" << std::endl;
		return;
	}

	auto pair = std::pair<char, std::vector<char>>(input, rule);
	rules_.emplace_back(pair);
}

std::vector<std::pair<char, std::vector<char>>> LSystem::GetRules()
{
	return rules_;
}

void LSystem::AddAxiom(std::initializer_list<char> new_axiom)
{
	for (auto& s : new_axiom) {
		bool in_variables = (std::find(variables_.begin(), variables_.end(), s) != variables_.end());
		bool in_constants = (std::find(constants_.begin(), constants_.end(), s) != constants_.end());
		if (!in_variables && !in_constants) {
			std::cout << "[ERROR]: " << s << " not in variables or constants!" << std::endl;
			return;
		}
	}

	axiom_ = new_axiom;
}

std::vector<char> LSystem::GetAxiom()
{
	return axiom_;
}

static std::vector<char> ExecuteSystemOnceWithoutCheck(LSystem* ls, const std::vector<char>& predecessor) {
	std::vector<char> successor;
	
	auto rules = ls->GetRules();
	for (auto& e : predecessor) {
		auto found_it = std::find_if(rules.begin(), rules.end(),
			[&e](const std::pair<char, std::vector<char>>& element) { return element.first == e; });

		if (found_it != rules.end()) { //if has a rule, apply it
			successor.insert(successor.end(), found_it->second.begin(), found_it->second.end());
		}
		else { //if doesnt have a rule, put the usual value
			successor.push_back(e);
		}
	}
	
	return successor;
}

std::vector<char> LSystem::ExecuteSystem(size_t num_executions)
{
	std::vector<char> final_vec(axiom_);
	for (size_t i = 0; i < num_executions; ++i) {
		final_vec = ExecuteSystemOnceWithoutCheck(this, final_vec);
	}
	return final_vec;
}

void LSystem::ResetSystem()
{
	variables_.clear();
	constants_.clear();
	rules_.clear();
}


