#include <stdio.h>
#include <string>

//	Simple test class with 1 constructor argument
class TestClass1
{
public:
	TestClass1(int Var)
	{
		printf("Var: %i\n", Var);
	}
};

//	Complicated test class with 3 constructor arguments
class TestClass2
{
public:
	TestClass2(std::string Var1, std::string Var2, int Var3)
	{
		printf("Var: %s %s %i\n", Var1.c_str(), Var2.c_str(), Var3);
	}
};


//	Variadic Template Factory Class
//
//	Creates instances of "Class" from a variable number of constructor arguments
template <class Class, typename...Args>
class Factory
{
public:
	inline Class* Create(Args...Val)
	{
		return new Class(Val...);
	}
};


int main()
{
	Factory<TestClass1,int> ClassFactory1;
	ClassFactory1.Create(4);

	Factory<TestClass2,std::string, std::string, int> ClassFactory2;
	ClassFactory2.Create(std::string("Hello"), std::string("Number"), 7);

	std::system("pause");
    return 0;
}
