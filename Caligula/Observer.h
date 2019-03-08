#pragma once
#include "Config.h"
class Entity;

/*
 * Observer.h
 * Receives messages from Subject and handles them depending on event type
 *
 */

class Observer
{
public:
	virtual ~Observer() {}
	virtual void onNotify(const Entity& entity, Config::Event event) = 0;
};
