require 'mxx_ru/cpp'

MxxRu::Cpp::exe_target {

	required_prj 'so_5/prj.rb'

	target '_unit.test.state.default_state_as_parent'

	cpp_source 'main.cpp'
}

