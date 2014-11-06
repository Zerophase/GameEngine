#ifndef SINGLETON_H
#define SINGLETON_H

template<typename T>
class Singleton
{
private:
	Singleton(const Singleton<T> &);
	Singleton& operator=(const Singleton<T> &);

public:
	Singleton() {}
	~Singleton() {}

	virtual T *Get() = 0;
	virtual void StartUp() = 0;
	virtual void ShutDown() = 0;
};

#endif // !SINGLETON_H
