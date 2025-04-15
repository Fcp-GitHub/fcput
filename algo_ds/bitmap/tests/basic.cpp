/*
 * basic.cpp -- Test for internal::basic_bitmap
 */

#include <iostream>
#include <array>
#include <string_view>
#include <iomanip>

#include "algo_ds/bitmap/bitmap.hpp"

#define BIT_PATTERN {true, true, true, true, true, true, true, true}
std::array<bool, CHAR_BIT> bit_pattern{BIT_PATTERN};

std::ostream& operator<<(std::ostream& o, std::array<bool, 8> _a)
{
	for (auto _b : _a)
		o << _b << ' ';
	return o;
}

std::ostream& operator<<(std::ostream& o, fcp::algods::internal::basic_bitmap _b)
{
	for (int i{0}; i < CHAR_BIT; i++)
		o << _b.at(i) << ' ';
	return o;
}

void compare(const std::string_view& _title, const std::array<bool, 8>& _a, const fcp::algods::internal::basic_bitmap& _b)
{
	std::cout << "\nTest: " << _title << '\n';
	std::cout << "Expected: " << _a << '\n';
	std::cout << std::left << std::setw(10) << "Result: " << _b << '\n';
}

int main(void)
{
	// Utility
	namespace fcpint = fcp::algods::internal;

	// Title
	std::cout << "Tests for internal::basic_bitmap\n";

	// Create object from array of values
	fcpint::basic_bitmap array_bitmap(BIT_PATTERN);
	
	compare("init list constructor", bit_pattern, array_bitmap);
	
	// Create object from a single value
	fcpint::basic_bitmap value_bitmap(true);

	compare("single value constructor", bit_pattern, value_bitmap);

	// Test compile time functions
	// flip<>()
	array_bitmap.flip<2>();
	bit_pattern[2] = not bit_pattern[2];

	compare("flip (ctime)", bit_pattern, array_bitmap);

	// at<>()
	
	std::cout << "\nTest: at (ctime)\n";
	std::cout << "Expected: " << bit_pattern[0] << '\n';
	std::cout << std::setw(10) << "Result: " << array_bitmap.at<0>() << '\n';

	// Test runtime functions
	// flip()
	array_bitmap.flip(5);
	bit_pattern[5] = not bit_pattern[5];

	compare("flip (rtime)", bit_pattern, array_bitmap);

	// at()
	std::cout << "\nTest: at (rtime)\n";
	std::cout << "Expected: " << bit_pattern[0] << '\n';
	std::cout << std::setw(10) << "Result: " << array_bitmap.at(1) << '\n';

	// flip_all()
	array_bitmap.flip_all();
	for (auto& _b : bit_pattern)
		_b = not _b;

	compare("flip_all", bit_pattern, array_bitmap);

	// set()
	array_bitmap.set(3, false);
	bit_pattern[3] = false;

	compare("set", bit_pattern, array_bitmap);

	// set_all() (ctime)
	array_bitmap.set_all<true>();
	for (auto& _b : bit_pattern)
		_b = true;

	compare("set_all (ctime)", bit_pattern, array_bitmap);

	// set_all() (rtime)
	array_bitmap.set_all(false);
	for (auto& _b : bit_pattern)
		_b = false;

	compare("set_all (rtime)", bit_pattern, array_bitmap);


	return 0;
}
