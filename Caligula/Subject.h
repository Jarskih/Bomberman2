#pragma once
#include "Observer.h"
#include <vector>

/*
 * Subject.h
 * Subject can send events to observers which are listening to it.
 * Observers can be removed and added
 * Notify could be private method if entity inherited this class (currently public because no time to refactor)
 */

class Subject
{
public:
	Subject();
	void addObserver(Observer* observer)
	{
		m_observers.push_back(observer);
		m_numObservers = static_cast<int>(m_observers.size());
	}

	void removeObserver(Observer* observer)
	{
		const auto it = std::find(m_observers.begin(), m_observers.end(), observer);
		if (it != m_observers.end())
		{
			m_observers.erase(it);
			m_numObservers = static_cast<int>(m_observers.size());
		}
	}
	void notify(const Entity& entity, Config::Event event)
	{
		for (int i = 0; i < m_numObservers; i++)
		{
			m_observers[i]->onNotify(entity, event);
		}
	}
private:
	std::vector<Observer*> m_observers;
	int m_numObservers;
};
