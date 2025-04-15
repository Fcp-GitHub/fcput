#include "computational/differentiation/diff.hpp"

#include <exception>
#include <iostream>

#define NUM_POINTS 10
#define TYPE float

// Define a mathematical function (functor)
struct QuadraticFunction
{
	inline const float operator()(float x) const
	{
		return x*x;	
	};
};
// For easy-printing a vector
std::ostream& operator<<(std::ostream& out, std::vector<float> v)
{
	for (auto i : v)
		out << i << ' ';
	return out;
}

int main(void)
{
	namespace fcpc = fcp::computational;

	// Generate a Grid object of some kind
	fcpc::UniformGrid<TYPE> grid(0.f, 10.f, NUM_POINTS);

	// Generate a Differentiate object
	fcpc::Differentiate<TYPE, QuadraticFunction, fcpc::UniformGrid<TYPE>> diff(grid);

	std::vector<TYPE> data(NUM_POINTS), der(NUM_POINTS);
	QuadraticFunction fun;
	
	for (std::size_t i{0}; i < NUM_POINTS; i++)
	{
		data[i] = fun(grid[i]);
		der[i] = 2*grid[i];
	}

	std::cout << grid << '\n';

	std::cout << "Data:\n" << data << '\n'; 
	std::cout << "Derivative:\n" << der << '\n';
	std::cout << "diff.at(2):\n" << diff.at(2) << '\n';
	std::cout << "diff.at_range(3, 5):\n";
	for (auto i : diff.at_range(3, 5))
		std::cout << i << '\n';
	std::cout << "diff.data():\n";
	try {
		std::cout << diff.data() << '\n';
	} catch (const std::exception& e)
	{
		std::cout << "diff.data() won't work because of out-of-bounds errors:\n" << e.what() << std::endl;
	}
	return 0;
}
