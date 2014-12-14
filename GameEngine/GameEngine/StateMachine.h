#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "State.h"

template<class T>
class StateMachine
{
private:
		T *owner;

		State<T> *currentState;

public:
	State<T> *GetCurrentState() { return currentState; }
	void SetCurrentState(State<T> *state) { currentState = state; }

public:
	StateMachine(T *t)
	{
		owner = t;

		currentState = nullptr;
	}

	void Update() const
	{
		if (currentState != nullptr)
			currentState->Execute(owner);
	}

	void ChangeState(State<T> *newState)
	{
		if (currentState != nullptr)
			currentState->Exit(owner);

		currentState = newState;
		currentState->Enter(owner);
	}

};

#endif // !STATE_MACHINE_H



