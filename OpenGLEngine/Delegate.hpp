#ifndef _DELEGATE_HPP
#define _DELEGATE_HPP

template <class T, class ... Args>
class Delegate
{
public:
	void Invoke(Args ... a)
	{
		for (unsigned int x = functions.size() - 1; x != ~0; --x)
		{
			if (functions[x] == nullptr)
			{
				functions.erase(functions.begin() + x);
				continue;
			}
			functions[x](a ...);
		}
	}
	void operator()(Args ... a)
	{
		for (unsigned int x = functions.size() - 1; x != ~0; --x)
		{
			if (functions[x] == nullptr)
			{
				functions.erase(functions.begin() + x);
				continue;
			}
			functions[x](a ...);
		}
	}
	Delegate& operator+= (std::function<T(Args ...)> func)
	{
		functions.push_back(func);
		return *this;
	}
	Delegate& operator-= (std::function<T(Args ...)> func)
	{
		for (unsigned int x = 0; x < functions.size(); ++x)
		{
			if (functions[x].target<T(Args ...)>() == func.target<T(Args ...)>())
			{
				functions.erase(functions.begin() + x);
				break;
			}
		}
		return *this;
	}
	Delegate& operator=(std::function<T(Args ...)> func)
	{
		functions.clear();
		functions.push_back(func);
		return *this;
	}

private:
	std::vector<std::function<T(Args ...)>> functions;
};

#endif // !_DELEGATE_HPP