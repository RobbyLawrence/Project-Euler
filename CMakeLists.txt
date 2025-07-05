cmake_minimum_required(VERSION 3.13)
project(MyProject VERSION 1.0 LANGUAGES CXX)

# 1) export compile_commands.json for clangd/other LSPs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 2) C++ settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-g -Wall -Wextra -O2)

# 3) find GMP via pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(GMP REQUIRED gmp)
# this will populate:
#   GMP_INCLUDE_DIRS  (e.g. /opt/homebrew/include)
#   GMP_LIBRARY_DIRS  (e.g. /opt/homebrew/lib)
#   GMP_LIBRARIES     (e.g. -lgmp -lgmpxx)

# 4) make sure those dirs are visible
include_directories(${GMP_INCLUDE_DIRS})
link_directories   (${GMP_LIBRARY_DIRS})

# 5) source / binary dirs
set(SRCDIR "${CMAKE_SOURCE_DIR}/src")
set(BINDIR "${CMAKE_SOURCE_DIR}/bin")
file(MAKE_DIRECTORY "${BINDIR}")
file(GLOB SRCS "${SRCDIR}/*.cpp")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINDIR}")

# 6) one executable per .cpp
foreach(src ${SRCS})
    get_filename_component(name ${src} NAME_WE)
    add_executable(${name} ${src})
    target_link_libraries(${name} ${GMP_LIBRARIES})
endforeach()
