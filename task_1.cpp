#include <iostream>
bool f (int val)
{
	return val > 0 && (val & (val - 1)) == 0; //проверка с помощью побитового умножения
}

int main()
{
	std::cout << f(127) << "\n";
}
