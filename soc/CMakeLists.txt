cmake_minimum_required(VERSION 3.15)
project(soc CXX)

find_package(PkgConfig)
if(PKG_CONFIG_FOUND)
	pkg_check_modules(SystemC REQUIRED systemc)
else()
	link_libraries(systemc)
endif()

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(soc-emulator src/cpu.cpp src/main.cpp)
if(PKG_CONFIG_FOUND)
	target_link_libraries(soc ${SystemC_LIBRARIES})
	target_include_directories(soc PUBLIC ${SystemC_INCLUDE_DIRS})
	target_compile_options(soc PUBLIC ${SystemC_CFLAGS_OTHER})
endif()