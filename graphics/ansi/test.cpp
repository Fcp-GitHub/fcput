#include <climits>
#include <iostream>

#include "ansi_seq.hpp"

int main(void)
{
	std::cout << FCPG_FG_CYAN << "Hello World!\n" << FCPG_RESET;
	std::cout << FCPG_FG_GREEN << "Hello World!\n" << FCPG_RESET;
	std::cout << FCPG_FG_YELLOW << "Hello World!\n" << FCPG_RESET;
	std::cout << FCPG_FG_BLUE << "Hello World!\n" << FCPG_RESET;
	std::cout << FCPG_FG_MAGENTA << "Hello World!\n" << FCPG_RESET;
	std::cout << FCPG_RAPIDBLINK << "Hello World!\n" << FCPG_RESET;
	std::cout << FCPG_FAINT << "Hello World!\n" << FCPG_RESET;
	std::cout << FCPG_BOLD << "Hello World!\n" << FCPG_RESET;
	std::cout << FCPG_REVERSEVIDEO << "Hello World!\n" << FCPG_RESET;
	std::cout << FCPG_UNDERLINE << "Hello World!\n" << FCPG_RESET; 
	std::cout << FCPG_ITALIC << "Hello World!\n" << FCPG_RESET; 


	return 0;
}
