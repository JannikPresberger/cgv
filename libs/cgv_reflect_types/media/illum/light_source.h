#pragma once

#include <cgv/media/illum/light_source.hh>
#include <cgv_reflect_types/media/color.h>
#include <cgv_reflect_types/math/fvec.h>
#include <cgv/reflect/reflect_extern.h>

#include <cgv_reflect_types/lib_begin.h>

namespace cgv {
	namespace reflect {
		namespace media {
			namespace illum {

struct CGV_API light_source : public cgv::media::illum::light_source
{
	bool self_reflect(cgv::reflect::reflection_handler& rh);
};
			}
		}
	}
}

namespace cgv {
	namespace media {
		namespace illum {

extern CGV_API cgv::reflect::extern_reflection_traits<light_source, cgv::reflect::media::illum::light_source> get_reflection_traits(const light_source&);
extern CGV_API cgv::reflect::enum_reflection_traits<LightType> get_reflection_traits(const LightType&);

		}
	}
}

#include <cgv/config/lib_end.h>
