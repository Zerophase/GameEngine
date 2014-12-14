#include "MemoryManager.h"
#include "AllocationSchemas.h"
#include "TestObject.h"
#include "ManipulateBmp.h"
#include "FlipUpAndDown.h"
#include "Scramble.h"
#include "FlipSideways.h"
#include "WavePattern.h"
#include "Main.h"

#include <iostream>

using namespace Utilities;
using namespace allocator;
using namespace std;

MemoryManager memoryManager;
ManipulateBmp *manipulateBmp;

int main()
{
	memoryManager.StartUp();

	manipulateBmp = newAllocate<ManipulateBmp>(memoryManager.Get()->GetFreeListAllocator());

	update();

	deleteDeallocate<ManipulateBmp>(memoryManager.Get()->GetFreeListAllocator(), *manipulateBmp);

	memoryManager.ShutDown();
	return 0;
}

void update()
{
	char check = ' ';
	while (check != 'q')
	{
		displaySelections();

		switchState(check);

		manipulateBmp->Update();
	}
}

void switchState(char &check)
{
	check = cin.get();
	cin.ignore();
	cin.clear();
	switch (check)
	{
		case '1':
		{
			manipulateBmp->GetStateMachine()->SetCurrentState(FlipUpAndDown::Instance());
			break;
		}
		case '2':
		{
			manipulateBmp->GetStateMachine()->SetCurrentState(FlipSideways::Instance());
			break;
		}
		case '3':
		{
			manipulateBmp->GetStateMachine()->SetCurrentState(WavePattern::Instance());
			break;
		}
		case '4':
		{
			manipulateBmp->GetStateMachine()->SetCurrentState(Scramble::Instance());
			break;
		}
		default:
		{
			if (check != 'q')
				cout << "Unrecognized input. Please try another input." << endl;
			break;
		}
	}
	cout << endl;
}

void displaySelections()
{
	cout << "Select the type of manipulation you want to do to your image." << endl;
	cout << "1: Flip up and Down" << endl;
	cout << "2: flip side ways" << endl;
	cout << "3: Wave Pattern" << endl;
	cout << "4: Scramble image" << endl;
	cout << "Input Selected: ";
}