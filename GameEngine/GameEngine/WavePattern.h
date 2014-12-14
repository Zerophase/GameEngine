#ifndef WAVE_PATTERN_H
#define WAVE_PATTERN_H

#include "State.h"

class ManipulateBmp;

class WavePattern : public State < ManipulateBmp >
{
private:
	WavePattern() {}

	WavePattern(const WavePattern&);
	WavePattern &operator=(const WavePattern&);

public:
	static WavePattern *Instance();

	virtual void Enter(ManipulateBmp *manipulateBmp) override;
	virtual void Execute(ManipulateBmp *manipulateBmp) override;
	virtual void Exit(ManipulateBmp *manipulateBmp) override;
};

#endif // !WAVE_PATTERN_H
