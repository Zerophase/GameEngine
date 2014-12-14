#include "FlipUpAndDown.h"
#include "ManipulateBmp.h"


FlipUpAndDown * FlipUpAndDown::Instance()
{
	static FlipUpAndDown instance;
	return &instance;
}

void FlipUpAndDown::Enter(ManipulateBmp *manipulateBmp)
{

}

void FlipUpAndDown::Execute(ManipulateBmp *manipulateBmp)
{
	manipulateBmp->FlipUpAndDown();
}

void FlipUpAndDown::Exit(ManipulateBmp *manipulateBmp)
{

}