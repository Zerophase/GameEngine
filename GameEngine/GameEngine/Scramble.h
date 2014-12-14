#ifndef SCRAMBLE_H
#define SCRAMBLE_H

#include "State.h"

class ManipulateBmp;

class Scramble : public State < ManipulateBmp >
{
private:
	Scramble() {}

	Scramble(const Scramble&);
	Scramble &operator=(const Scramble&);

public:
	static Scramble *Instance();

	virtual void Enter(ManipulateBmp *manipulateBmp) override;
	virtual void Execute(ManipulateBmp *manipulateBmp) override;
	virtual void Exit(ManipulateBmp *manipulateBmp) override;
};

#endif // !SCRAMBLE_H
