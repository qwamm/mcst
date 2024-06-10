#include <iostream>
#include <vector>
#include <random>

std::vector<int> random_sample (int n, std::vector<int> &A) //reservoir sampling algorithm
{
	if (n > A.size())
	{
		throw(std::runtime_error("size of sample can't be bigger than a size of vector"));
	}
	std::vector <int> result;
	for (int i = 0; i < n; i++)
	{
		result.push_back(A[i]);
	}

	for (int i = 0; i < A.size(); i++)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, A.size() - 1);
		int j = dis(gen);
		if (j <= n)
			result[j] = A[i];
	}
	return result;
}

int main()
{
	std::vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i+1);
	}
	int n = 10;
	std::vector<int> res = random_sample(n, v);
	for (int i = 0; i < n; i++)
        {
                std::cout << res[i] << "\t";
        }
	std::cout << "\n";
}
