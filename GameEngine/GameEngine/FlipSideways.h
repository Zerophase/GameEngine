#ifndef FLIP_SIDEWAYS_H
#define FLIP_SIDEWAYS_H

#include "State.h"

class ManipulateBmp;

class FlipSideways : public State < ManipulateBmp >
{
private:
	FlipSideways() {}

	FlipSideways(const FlipSideways&);
	FlipSideways &operator=(const FlipSideways&);

public:
	static FlipSideways *Instance();

	virtual void Enter(ManipulateBmp *manipulateBmp) override;
	virtual void Execute(ManipulateBmp *manipulateBmp) override;
	virtual void Exit(ManipulateBmp *manipulateBmp) override;
};

#endif // !FLIP_SIDEWAYS_H