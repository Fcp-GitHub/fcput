#ifndef FCPUT_GRAPHICS_LOWER_API_H
#define FCPUT_GRAPHICS_LOWER_API_H

#include "graphics/common.hpp"

FCP_NAMESPACE_BEGIN
FCP_GRAPHICS_NAMESPACE_BEGIN
FCP_GRAPHICS_LOWER_NAMESPACE_BEGIN

////////////////  DATA ///////////////

/// @Brief Store data in API-specific storage units 
FCPUT_GRAPHICS_API void store_data(void);

/////////////// TEXTURES ///////////////

/////////////// SHADERS ///////////////
class ShaderManager;	// Maybe?
	// Add/Remove uniforms
	// Add/Remove shaders ("bounds" checking)
	// Other things?

//TODO: have to find a way to manage shaders with as most
//      freedom as possible. I wonder how the hell you do that

/////////////// DRAWING ///////////////

/// @Brief Draw specified vertices
FCPUT_GRAPHICS_API void draw(void);

FCP_GRAPHICS_LOWER_NAMESPACE_END
FCP_GRAPHICS_NAMESPACE_END
FCP_NAMESPACE_END

#endif	// FCPUT_GRAPHICS_LOWER_API_H
