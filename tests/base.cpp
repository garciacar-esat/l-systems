#include "LSystem.h"

#include <iostream>

int main(int argc, char** argv) {
	LSystem l_system;


	l_system.AddVariables({ 'c', 'a', 'b', 'b', 'x' });
	auto var = l_system.GetVariables();
	std::cout << "Variables:" << std::endl;
	for (auto& c : var) {
		std::cout << c << std::endl;
	}

	l_system.AddConstants({ 'z', 'y', 'z' });
	var = l_system.GetConstants();
	std::cout << "Constants:" << std::endl;
	for (auto& c : var) {
		std::cout << c << std::endl;
	}

	l_system.AddAxiom({'a'});
	var = l_system.GetAxiom();
	std::cout << "Axiom:" << std::endl;
	for (auto& c : var) {
		std::cout << c << std::endl;
	}

	char input = 'a';
	std::vector<char> rule = std::vector<char>({'a', 'b'});
	l_system.AddRule(input, rule);

	input = 'b';
	rule = std::vector<char>({ 'a' });
	l_system.AddRule(input, rule);

	auto executed = l_system.ExecuteSystem(3);
	std::cout << "Executed:" << std::endl;
	for (auto& c : executed) {
		std::cout << c;
	}
	std::cout << std::endl;

	l_system.ResetSystem();

	return 0;
}