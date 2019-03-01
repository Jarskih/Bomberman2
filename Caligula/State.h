#pragma once

#include <string>

class State
{
protected:
	std::string m_name;
	std::string m_nextState;
public:
	State() : m_name(""), m_nextState("") {};
	virtual ~State() {};
	virtual void Enter() {};
	virtual bool Update() = 0; /*Should return false if state should be changed*/
	virtual void Exit() {};
	std::string NextState() { return m_nextState; };
	std::string GetName() { return m_name; };
};
