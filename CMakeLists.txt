cmake_minimum_required(VERSION 3.10)

project(QEDcmake)

set(PYTHON_LIBRARY "Build\\Python")
set(PYTHON_INCLUDE_DIR "External\\Vendor\\cpython\\Include")

add_subdirectory(External\\Vendor\\GLAD Build\\GLAD)
add_subdirectory(External\\Vendor\\GLFW Build\\GLFW)