#ifndef FCPUT_GRAPHICS_ERROR
#define FCPUT_GRAPHICS_ERROR
#include <string>
#include <string_view>
#include <exception>

namespace fcp
{
	// Here are stored the possible error types.
	
	// Exception thrown when trying to bind an object with m_id = 0.
	class bad_binding_error : public std::exception
	{
		std::string m_error{};
	
		public:
			bad_binding_error(std::string_view error = "Fatal error: buffer object with null ID cannot be accessed.\n"): m_error{error} {}	
	
			const char* what() const noexcept override
			{ return m_error.c_str(); }
	};

}
#endif	// FCPUT_GRAPHICS_ERROR
