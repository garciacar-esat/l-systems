#pragma once

#include <vector>
#include <algorithm>

template<typename T>
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

	~LSystem(){
		ResetSystem();
	}


private:
	std::vector<T> variables_;
	std::vector<T> constants_;
	std::vector<T> axiom_;

	std::vector<std::pair<T, std::vector<T>>> rules_; //input is T and output is vector of chars

public:
	void AddVariables(std::initializer_list<T> var_init) {
		//create final var initializer list
		std::vector<T> new_var_init;

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
	std::vector<T> GetVariables() const{
		return variables_;
	}

	void AddConstants(std::initializer_list<T> var_init) {
		//create final var initializer list
		std::vector<T> new_var_init;

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
	std::vector<T> GetConstants() const {
		return constants_;
	}

	void AddRule(T input, std::vector<T> rule) {
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

		auto pair = std::pair<T, std::vector<T>>(input, rule);
		rules_.emplace_back(pair);
	}
	std::vector<std::pair<T, std::vector<T>>> GetRules() const{
		return rules_;
	}

	void AddAxiom(std::initializer_list<T> new_axiom) {
		//find if all elements in axiom are part of the variables / constants
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
	std::vector<T> GetAxiom() const {
		return axiom_;
	}
	
	std::vector<T> ExecuteSystem(size_t num_executions) {
		std::vector<T> final_vec(axiom_);
		for (size_t i = 0; i < num_executions; ++i) {
			final_vec = ExecuteSystemOnceWithoutCheck(this, final_vec);
		}
		return final_vec;
	}

	void ResetSystem() {
		variables_.clear();
		constants_.clear();
		rules_.clear();
	}

private:
	static std::vector<T> ExecuteSystemOnceWithoutCheck(LSystem* ls, const std::vector<T>& predecessor) {
		std::vector<T> successor;

		auto rules = ls->GetRules();
		for (auto& e : predecessor) {
			auto found_it = std::find_if(rules.begin(), rules.end(),
				[&e](const std::pair<T, std::vector<T>>& element) { return element.first == e; });

			if (found_it != rules.end()) { //if has a rule, apply it
				successor.insert(successor.end(), found_it->second.begin(), found_it->second.end());
			}
			else { //if doesnt have a rule, put the usual value
				successor.push_back(e);
			}
		}

		return successor;
	}
};