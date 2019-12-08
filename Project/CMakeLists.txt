# CMakeList.txt : 최상위 CMake 프로젝트 파일, 전역 구성을 수행하고
# 여기에 하위 프로젝트를 포함합니다.
#
cmake_minimum_required (VERSION 3.8)
SET ( CMAKE_BUILD_TYPE Release )

SET ( PROBLEM_PATH ../Problem )
SET ( TARGET_PATH ./Project )
SET ( CMAKE_VERBOSE_MAKEFILE true )
set ( CMAKE_SUPPRESS_REGENERATION true )
set ( CMAKE_SKIP_INSTALL_ALL_DEPENDENCY false )


project ( CPP_Study )




# 하위 프로젝트를 포함합니다.
add_subdirectory (${PROBLEM_PATH}/BAE ./BAE )