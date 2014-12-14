#include "State.h"

class ManipulateBmp;

class FlipUpAndDown : public State < ManipulateBmp >
{
private:
	FlipUpAndDown();

	FlipUpAndDown(const FlipUpAndDown &);
	FlipUpAndDown &operator=(const FlipUpAndDown&);

public:
	static FlipUpAndDown *Instance();

	virtual void Enter(ManipulateBmp *manipulateBmp) override;
	virtual void Execute(ManipulateBmp *manipulateBmp) override;
	virtual void Exit(ManipulateBmp *manipulateBmp) override;
};