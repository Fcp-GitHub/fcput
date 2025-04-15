/*
 * bitmap.cpp -- Bitmap class' test code
 */

#include <iostream>
#include <string>
#include <string_view>
#include <array>
#include <random>

#define FCP_ALGODS_BITMAP_DEBUG
#include "algo_ds/bitmap/bitmap.hpp"

#define FLAGS_NUM 50
#define RANDOM_TESTS 15

void compare(const std::string_view& title, const std::array<bool, FLAGS_NUM>& expected, const fcp::algods::Bitmap<FLAGS_NUM>& result)
{
	std::cout << '\n' << title << '\n';
	std::cout << "\tExpected: ";
	//short _c{0};
	for (auto b : expected)
	//{
		std::cout << b << ' ';
	//	if (7 == _c++) {std::cout << '\n' << "\t          "; _c = 0;}
	//}
	std::cout << '\n';
	std::cout << "\tResult:   ";
	//_c = 0;
	for (std::size_t i{0}; i < FLAGS_NUM; i++)
	//{
		std::cout << result.at(i) << ' ';
	//	if (7 == _c++) {std::cout << '\n' << "\t          "; _c = 0;}
	//}
	std::cout << '\n';
}

void compare(const std::string_view& title, const bool& expected, const bool& result)
{
	if ("" != title)
		std::cout << '\n' << title << '\n';
	std::cout << "\tExpected: " << expected << '\n';
	std::cout << "\tResult  : " << result << '\n';
}

int main(void)
{
	// Utility and setup
	std::random_device dev;
  std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> init_dist(0,1);	// Random distribution in range [0,1] used to test the initialization list constructor
  std::uniform_int_distribution<std::mt19937::result_type> dist(0,FLAGS_NUM-1); // distribution in range [0, FLAGS_NUM)

	std::array<bool, FLAGS_NUM> init_rnd_values;	// Array of random values used to test the initialization list constructor
	for (auto& b : init_rnd_values)
		b = init_dist(rng);
	std::array<bool, FLAGS_NUM> rnd_values;	// Array of random values for the tests
	for (auto& b : rnd_values)
		b = dist(rng);

	// `FLAGS_NUM` flags with a random state each
	fcp::algods::Bitmap<FLAGS_NUM> rndflags{init_rnd_values};
		
	// `FLAGS_NUM` flags all with the same state
	fcp::algods::Bitmap<FLAGS_NUM> svflags(true);
	
	// Check size of bitmap
	std::cout << "sizeof(fcp::algods::Bitmap<" << FLAGS_NUM << ">): " << sizeof(svflags) << '\n'; 
	// Check `Bits` constant value
	std::cout << "`Bits` constant value: " << svflags._bits << '\n';
	// Check `FCP_COMPUTE_BYTES` value
	std::cout << "FCP_COMPUTE_BYTES value: " << FCP_COMPUTE_BYTES(svflags._bits) << '\n';

	// Check initialization list (array) constructor
	std::cout << '\n';
	for (auto b : init_rnd_values)
		std::cout << b << ' ';
	std::cout << '\n';
	compare("Init list constructor", init_rnd_values, rndflags);

	// Check single value constructor
	std::array<bool, FLAGS_NUM> svexpected;
	for (auto& b : svexpected)
		b = true;
	compare("Single value constructor", svexpected, svflags);

	// !
	// FROM NOW ON USING ONLY `svexpected` and `svflags`
	// !

	// flip() (rtime)  
	std::cout << "\nflip() (rtime) repeated for " << RANDOM_TESTS << " times\n";
	for (int i{0}; i < RANDOM_TESTS; i++)
	{
		auto _temp = dist(rng);
		auto _title = "flip(" + std::to_string(_temp) + ")";
		svexpected[_temp] = not svexpected[_temp];

		compare(_title, svexpected[_temp], svflags.flip(_temp).at(_temp));
	}
	std::cout << "Edge cases\n";
	svexpected[0] = not svexpected[0];
	compare("flip(0)", svexpected[0], svflags.flip(0).at<0>());
	svexpected[FLAGS_NUM-1] = not svexpected[FLAGS_NUM-1];
	compare("flip(" + std::to_string(FLAGS_NUM-1) + ")", svexpected[FLAGS_NUM-1], svflags.flip(FLAGS_NUM-1).at<FLAGS_NUM-1>());

	// flip() (ctime)  
	std::cout << "\nflip() (ctime) repeated for 2 times\n";
	constexpr std::size_t _t1 = RANDOM_TESTS / 5;
	auto _title = "flip(" + std::to_string(_t1) + ")";
	svexpected[_t1] = not svexpected[_t1];
	
	compare(_title, svexpected[_t1], svflags.flip<_t1>().at(_t1));

	constexpr std::size_t _t2 = RANDOM_TESTS / 2;
	_title = "flip(" + std::to_string(_t2) + ")";
	svexpected[_t2] = not svexpected[_t2];

	compare(_title, svexpected[_t2], svflags.flip<_t2>().at(_t2));

	std::cout << "Edge cases\n";
	svexpected[0] = not svexpected[0];
	compare("flip<0>()", svexpected[0], svflags.flip<0>().at<0>());
	svexpected[FLAGS_NUM-1] = not svexpected[FLAGS_NUM-1];
	compare("flip<" + std::to_string(FLAGS_NUM-1) + ">()", svexpected[FLAGS_NUM-1], svflags.flip<FLAGS_NUM-1>().at<FLAGS_NUM-1>());


	// at() (rtime)
	std::cout << "\nat() (rtime) repeated for " << RANDOM_TESTS << " times\n";
	for (int i{0}; i < RANDOM_TESTS; i++)
	{
		auto _temp = dist(rng);
		auto _title = "at(" + std::to_string(_temp) + ")";

		compare(_title, svexpected[_temp], svflags.at(_temp));
	}
	std::cout << "Edge cases\n";
	compare("at(0)", svexpected[0], svflags.at(0));
	compare("at(" + std::to_string(FLAGS_NUM-1) + ")", svexpected[FLAGS_NUM-1], svflags.at(FLAGS_NUM-1));



	// at() (ctime)
	std::cout << "\nat() (ctime) repeated for 2 times\n";

	_title = "at(" + std::to_string(_t1) + ")";
	svexpected[_t1] = not svexpected[_t1];
	
	compare(_title, svexpected[_t1], svflags.flip<_t1>().at(_t1));

	_title = "at(" + std::to_string(_t2) + ")";
	svexpected[_t2] = not svexpected[_t2];

	compare(_title, svexpected[_t2], svflags.flip<_t2>().at(_t2));
	std::cout << "Edge cases\n";
	compare("at<0>()", svexpected[0], svflags.at<0>());
	compare("at<" + std::to_string(FLAGS_NUM-1) + ">()", svexpected[FLAGS_NUM-1], svflags.at<FLAGS_NUM-1>());


	// flip_all()
	svflags.flip_all();
	for (auto& b : svexpected)
		b = not b;
	compare("flip_all()", svexpected, svflags);

	// set_all() (rtime)
	svflags.set_all(true);
	for (auto& b : svexpected)
		b = true;
	compare("set_all() (rtime)", svexpected, svflags);
	
	// set_all() (ctime)
	svflags.set_all<true>();
	for (auto& b : svexpected)
		b = true;
	compare("set_all() (ctime)", svexpected, svflags);

	// std::ostream& operator<<(std::ostream&, const fcp::algods::Bitmap&)
	std::cout << "\nstd::ostream& operator<<(std::ostream&, const fcp::algods::Bitmap&)\n";
	std::cout << svflags << '\n';

	return 0;
}
