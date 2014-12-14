#include "WavePattern.h"
#include "ManipulateBmp.h"

WavePattern * WavePattern::Instance()
{
	static WavePattern instance;
	return &instance;
}

void WavePattern::Enter(ManipulateBmp *manipulateBmp)
{

}

void WavePattern::Execute(ManipulateBmp *manipulateBmp)
{
	manipulateBmp->WavePattern();
}

void WavePattern::Exit(ManipulateBmp *manipulateBmp)
{

}
