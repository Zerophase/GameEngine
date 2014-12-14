#include "MemoryManager.h"
#include "AllocationSchemas.h"
#include "TestObject.h"
#include "ManipulateBmp.h"

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

	char check = ' ';
	while (check != 'q')
	{
		
		cout << "Select the type of manipulation you want to do to your image." << endl;
		cout << "1: Flip up and Down" << endl;
		cout << "2: flip side ways" << endl;
		cout << "3: Wave Pattern" << endl;
		cout << "4: Scramble image" << endl;
		cout << "Input Selected: ";

		
		check = cin.get();
		cin.ignore();
		cin.clear();
		switch (check)
		{
		case '1':
		{
			BMP bmp;
			manipulateBmp->LoadBMP("C:\\Users\\Zerophase\\Desktop\\GameEngine\\GameEngine\\Debug\\punkmonkey.bmp",
				&bmp);
			manipulateBmp->WriteBMP(&bmp);
			break;
		}
		case '2':
		{
			break;
		}
		case '3':
		{
			break;
		}
		case '4':
		{
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

	deleteDeallocate<ManipulateBmp>(memoryManager.Get()->GetFreeListAllocator(), *manipulateBmp);

	memoryManager.ShutDown();
	return 0;
}