cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/Tools/vcpkg-2025.08.27/scripts/buildsystems/vcpkg.cmake")

project(Blackjack)

set(SOURCES_EXE src/BJ_main.cpp)

set(SOURCE_LIB src/Func.cpp src/Methods.cpp)

add_library(BJ_Func STATIC ${SOURCE_LIB})

find_package(raylib REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(Blackjack ${SOURCES_EXE})

# target_link_libraries(BJ_Func PRIVATE raylib)

# target_link_libraries(Blackjack PRIVATE BJ_Func PRIVATE raylib)

# find_package(raylib REQUIRED)




set(LINUX_LIBS m pthread dl rt X11)

target_link_libraries(BJ_Func PRIVATE raylib)
target_link_libraries(Blackjack PRIVATE BJ_Func PRIVATE raylib glfw)
# target_link_libraries(Blackjack PRIVATE BJ_Func PRIVATE raylib ${LINUX_LIBS})

