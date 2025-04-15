#ifndef FCPUT_COMPUTATIONAL_INTEGRATION
#define FCPUT_COMPUTATIONAL_INTEGRATION


#include "../../utility/utility.hpp"

#include <vector>

START_FCP_NAMESPACE
START_COMPUTATIONAL_NAMESPACE


enum int_method { RECTANGULAR, TRAPEZOIDAL, SIMPSON, GAUSS_LEGENDRE }; 

template <typename T, class Grid, class Function, int_method Method = int_method::SIMPSON, std::size_t Dimensions = 1/*, ...*/>
class Integrate
{
	public:
		Integrate();

		// Trigger points for lazy evaluation
		T at(const std::size_t& i) const;
		T operator[](const std::size_t& i) const;

		// Compute whole array and return it
		std::vector<T> data(void);
};

END_COMPUTATIONAL_NAMESPACE
END_FCP_NAMESPACE

#endif	//FCPUT_COMPUTATIONAL_INTEGRATION
