require 'mxx_ru/cpp'

MxxRu::Cpp::exe_target {

	required_prj 'so_5/prj.rb'

	target '_unit.test.env_infrastructure.simple_mtsafe_st.unknown_exception_init_fn_2'

	cpp_source 'main.cpp'
}

