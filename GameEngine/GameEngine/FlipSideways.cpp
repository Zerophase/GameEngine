#include "FlipSideways.h"
#include "ManipulateBmp.h"

FlipSideways *FlipSideways::Instance()
{
	static FlipSideways instance;
	return &instance;
}

void FlipSideways::Enter(ManipulateBmp *manipulateBmp)
{

}

void FlipSideways::Execute(ManipulateBmp *manipulateBmp)
{
	manipulateBmp->FlipSideways();
}

void FlipSideways::Exit(ManipulateBmp *manipulateBmp)
{

}
