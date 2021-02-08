#pragma once

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

	~LSystem() = default;


private:

};