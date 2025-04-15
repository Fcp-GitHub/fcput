#include "graphics/high/plot.hpp"

#include <array>

int main(void)
{
	// Instantiate Plotter object
	fcp::graphics::Plotter<5, double, 2> plotter;

	// Initialize data
	std::array<double, 5> x {1.5, 3.6, 4.2, 2.5, 25};	
	std::array<double, 5> y {0.7, 2.8, 3.9, 4.2, 10};	

	// Store data in Plotter object
	plotter.add_data<0>(x, {1.,.3,.5});
	plotter.add_data<1>(y, {.2,.4,.6});

	// Or do all the above in fewer steps
	fcp::graphics::Plotter<5, double, 2> plotter1({x,y}, {{1.,.3,.5},{.2,.4,.6}});

	plotter.plot();

	return 0;
}
