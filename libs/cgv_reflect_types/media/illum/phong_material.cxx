#include "phong_material.h"
#include <cgv/reflect/reflection_handler.h>


namespace cgv {
	namespace reflect {
		namespace media {
			namespace illum {

bool phong_material::self_reflect(cgv::reflect::reflection_handler& rh)
{
	return 
		rh.reflect_member("ambient", ambient) &&
		rh.reflect_member("diffuse", diffuse) &&
		rh.reflect_member("specular", specular) &&
		rh.reflect_member("emission", emission) &&
		rh.reflect_member("shininess", shininess);
}

			}
		}
	}
}

namespace cgv {
	namespace media {
		namespace illum {

cgv::reflect::extern_reflection_traits<phong_material, cgv::reflect::media::illum::phong_material> get_reflection_traits(const phong_material&)
{
	return cgv::reflect::extern_reflection_traits<phong_material, cgv::reflect::media::illum::phong_material>();
}

		}
	}
}

