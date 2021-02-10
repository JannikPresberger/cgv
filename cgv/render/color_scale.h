#pragma once

#include <cgv/media/color_scale.h>
#include "shader_program.h"

#include "lib_begin.h"

namespace cgv {
	namespace render {

/// <summary>
/// convenience function to configure a shader that uses color_scale.glsl
/// </summary>
/// <param name="ctx">render context</param>
/// <param name="prog">shader program using the color scale</param>
/// <param name="cs">color scale index that can surpass cgv::media::CS_NAMED to index named color scales</param>
extern CGV_API void configure_color_scale(cgv::render::context& ctx, cgv::render::shader_program& prog, cgv::media::ColorScale cs);

	}
}

#include <cgv/config/lib_end.h>