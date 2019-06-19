#ifndef _SINGLETON_HPP
#define _SINGLETON_HPP

#include <vector>

template<class T>
class Singleton
{
public:
	static T* GetInstance()
	{
		static T instance;
		return &instance;
	}
protected:
	Singleton() { }
	~Singleton() { }
private:
	Singleton(const Singleton&); //disallow copy constructor
	Singleton& operator=(const Singleton&);//disallow assignment
};
#endif // !_SINGLETON_HPP
