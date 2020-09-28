#include "include/libtorch.h"

#include <iostream>

namespace cgv {
	namespace nn {

		tn_ptr load_net_from_file(std::string const& filepath, bool* const success) {
			try {
				tn_ptr ret = std::make_shared<tn_ptr::element_type>();
				*ret = torch::jit::load(filepath);
				if(success)
					*success = true;

				return ret;
			} catch(const c10::Error& e) {
				std::cerr << "Error: Could not load the PyTorch model! Maybe you are not using a maching build (debug/release of libtorch)." << std::endl;
				if(success)
					*success = false;
				return {};
			}
		}

		module_map get_named_modules(tn_ptr nn) {

			module_map modules;

			if(nn) {
				torch::jit::named_module_list nml = nn->named_modules();
				for(auto it = nml.begin(); it != nml.end(); ++it) {
					std::string name = (*it).name;
					torch::jit::Module value = (*it).value;
					
					if(name != "")
						modules.insert(std::make_pair(name, value));
				}
			}

			return modules;
		}

		int64_t typesize(c10::ScalarType scalar_type) {

			int64_t size = 0;
			switch(scalar_type) {
			case c10::ScalarType::Byte:
			case c10::ScalarType::Char:
			case c10::ScalarType::QInt8:
			case c10::ScalarType::QUInt8: size = 1; break;
			case c10::ScalarType::Short:
			case c10::ScalarType::Half:
			case c10::ScalarType::ComplexHalf:
			case c10::ScalarType::BFloat16: size = 2; break;
			case c10::ScalarType::Int:
			case c10::ScalarType::Float:
			case c10::ScalarType::ComplexFloat: size = 4; break;
			case c10::ScalarType::Long:
			case c10::ScalarType::Double:
			case c10::ScalarType::ComplexDouble: size = 8; break;
			case c10::ScalarType::Bool: size = sizeof(bool); break;
			}
			return size;
		}

		int64_t element_count(at::Tensor t) {
			int64_t count = 0;
			for(int64_t i = 0; i < t.ndimension(); ++i)
				count += t.size(i);
			return count;
		}

		template<>
		std::vector<float> to_vector(at::Tensor t) {
			int64_t count = element_count(t);
			int64_t size = typesize(t.scalar_type());

			std::vector<float> v(0);
			if(size == 4) {
				v.resize(count);
				memcpy((void*)v.data(), (void*)(t.data<float>()), size * count);
			}
			return v;
		}

		template<>
		std::vector<double> to_vector(at::Tensor t) {
			int64_t count = element_count(t);
			int64_t size = typesize(t.scalar_type());

			std::vector<double> v(0);
			if(size == 8) {
				v.resize(count);
				memcpy((void*)v.data(), (void*)(t.data<double>()), size * count);
			}
			return v;
		}
	}
}
