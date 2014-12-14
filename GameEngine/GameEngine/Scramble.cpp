#include "Scramble.h"
#include "ManipulateBmp.h"

Scramble *Scramble::Instance()
{
	static Scramble instance;
	return &instance;
}

void Scramble::Enter(ManipulateBmp *manipulateBmp)
{

}

void Scramble::Execute(ManipulateBmp *manipulateBmp)
{
	manipulateBmp->Scramble();
}

void Scramble::Exit(ManipulateBmp *manipulateBmp)
{

}
