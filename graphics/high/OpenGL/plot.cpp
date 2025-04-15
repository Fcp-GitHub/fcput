#include "graphics/common.hpp"

#include <array>
#include <vector>
#include <string_view>


FCP_NAMESPACE_BEGIN
FCP_GRAPHICS_NAMESPACE_BEGIN

namespace internal
{
	// Default shader policy for the Plotter class
	// Specifies the default shaders that will be used by the class
	class DefaultShaderPolicy
	{
		public:
			FCPUT_GRAPHICS_API inline DefaultShaderPolicy(void) noexcept;
			FCPUT_GRAPHICS_API inline constexpr unsigned char* vshader(void) noexcept;
			FCPUT_GRAPHICS_API inline constexpr unsigned char* fshader(void) noexcept;
		
		private:
			static constexpr std::string_view m_vertshader = ""; 
			static constexpr std::string_view m_fragshader = "";
	};
}

enum class primitives { DOT, LINE };

/// @Brief Plot class
/// Requires the number of dimensions as template parameter 
/// as well as the data type that will have to be stored
/// @Detail The `ShaderPolicy` template parameter specifies
/// where is the plot's underlying shader stored
template <std::size_t C, typename T, short N, typename ShaderPolicy = internal::DefaultShaderPolicy>
class Plot
{
	public:
		/// @Brief Initialize Plotter class
		FCPUT_GRAPHICS_API inline constexpr Plot(void) noexcept {}

		/// @Brief Initialize Plotter class with data to plot
		FCPUT_GRAPHICS_API inline constexpr Plot(
				const std::array<std::array<T,C>,N>& data, 
				const std::array<std::array<T,3>,N>& rgb_colors,
				const bool& normalized = false
		) noexcept;

		/// @Brief Add data for the `Dim` axis passing a pointer, since 
		/// data arrays can be quite big				// ! Actually, save the data. There should be an array
		/// 																		// with all the values (data, RGB, ...) stored in order
		/// 																		// to maximize efficency for the VBO (OpenGL)
		/// @Detail 0 is for x-data, 1 for y-data, 2 for z-data and so on
		template <short Dim>
		FCPUT_GRAPHICS_API inline constexpr void add_data(
				const std::array<T,C>& data, 
				const std::array<T,3>& rgb_color,
				const bool& normalized = false
		) noexcept;

		/// @Brief Plot what has been specified
		FCPUT_GRAPHICS_API inline constexpr void plot(const primitives& primitive = primitives::DOT) noexcept; 

	private:
		std::array<std::vector<T>, N> m_data;
};

class Histogram;


FCP_GRAPHICS_NAMESPACE_END
FCP_NAMESPACE_END
