#ifndef TEST_OBJECT_H

#include <string>

class TestObject
{
private:
	std::string name;

public:
	TestObject();
	~TestObject();

	void SetName(std::string name)
	{
		this->name = name; 
	}

	std::string GetName()
	{
		return name;
	}
};

#endif // !TEST_OBJECT_H




