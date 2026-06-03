# 要求使用的 CMake 最低版本。
# FetchContent 在较新的 CMake 中更好用，这里要求至少 3.14。
cmake_minimum_required(VERSION 3.14)

# 定义当前工程：
# - 工程名：minigl2d
# - 版本号：0.1.0
# - 使用语言：C 和 C++
# 注意：这里启用 C 是因为部分第三方库/生成代码可能包含 C 源码。
project(minigl2d VERSION 0.1.0 LANGUAGES C CXX)

# 设置整个工程使用 C++17 标准。
set(CMAKE_CXX_STANDARD 17)

# 要求必须支持 C++17。
# 如果编译器不支持 C++17，CMake 会直接报错，而不是降级到旧标准。
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------------------------------------------------------
# 第三方依赖：通过 CMake FetchContent 自动下载
# -----------------------------------------------------------------------------
# FetchContent 的作用：
# 1. 在执行 `cmake -S . -B build` 配置项目时，从 GitHub 下载依赖源码；
# 2. 默认下载到构建目录下，例如：`build/_deps/xxx-src`；
# 3. 把下载下来的依赖加入当前 CMake 工程，之后就可以 target_link_libraries 使用。
include(FetchContent)

# -----------------------------------------------------------------------------
# GLFW：窗口创建、键盘鼠标输入、OpenGL 上下文创建
# -----------------------------------------------------------------------------
# 声明 GLFW 依赖来自哪里，以及使用哪个版本。
# FetchContent_Declare 只是“登记信息”，还不会真正下载。
FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.3.9
)

# 关闭 GLFW 自带的文档、测试和示例，避免编译不需要的内容，加快构建速度。
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# 真正下载并加入 GLFW。
# 执行后，项目里就可以链接名为 `glfw` 的 CMake target。
FetchContent_MakeAvailable(glfw)

# -----------------------------------------------------------------------------
# GLAD：OpenGL 函数加载器
# -----------------------------------------------------------------------------
# OpenGL 的很多函数不能直接调用，需要先通过 GLAD 加载函数地址。
# 这里使用 GLAD v2，并生成 OpenGL 3.3 Core Profile 对应的加载代码。
FetchContent_Declare(glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG        v2.0.8
)

# 下载并加入 GLAD 源码。
# 下载后，glad_SOURCE_DIR 变量会指向 GLAD 源码目录，例如：build/_deps/glad-src。
FetchContent_MakeAvailable(glad)

# 引入 GLAD 提供的 CMake 脚本，这样下面才能使用 glad_add_library。
include("${glad_SOURCE_DIR}/cmake/CMakeLists.txt")

# 生成一个静态库 target：glad_gl_core_33。
# 含义：
# - STATIC：生成静态库
# - API gl:core=3.3：生成 OpenGL 3.3 Core Profile 的函数加载器
# - EXTENSIONS NONE：不额外生成 OpenGL 扩展函数
glad_add_library(glad_gl_core_33 STATIC API gl:core=3.3 EXTENSIONS NONE)

# -----------------------------------------------------------------------------
# GLM：数学库
# -----------------------------------------------------------------------------
# GLM 是一个 header-only C++ 数学库，常用于图形开发中的向量、矩阵计算。
# 例如 glm::vec2、glm::vec3、glm::mat4 等。
FetchContent_Declare(glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1
)

# 下载并加入 GLM。
# 执行后，项目里可以链接 `glm::glm`。
FetchContent_MakeAvailable(glm)

# -----------------------------------------------------------------------------
# stb_image：图片加载库
# -----------------------------------------------------------------------------
# stb_image 是 header-only 单头文件库，用来加载 png/jpg 等图片。
# 它没有标准的 CMake target，所以这里手动创建一个 interface target。
FetchContent_Declare(stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG        master
)

# 下载 stb 源码。
# 下载后，stb_SOURCE_DIR 变量会指向 stb 源码目录，例如：build/_deps/stb-src。
FetchContent_MakeAvailable(stb)

# 创建一个只传递头文件路径的 target。
# INTERFACE 表示它本身不编译源码，只给使用者提供 include 路径等信息。
add_library(stb_image INTERFACE)

# 告诉使用 stb_image 的目标：编译时需要把 stb 源码目录加入头文件搜索路径。
# 这样代码里才能 `#include <stb_image.h>`。
target_include_directories(stb_image INTERFACE ${stb_SOURCE_DIR})

# -----------------------------------------------------------------------------
# 子项目
# -----------------------------------------------------------------------------
# 加入 engine 子目录。
# CMake 会继续读取 engine/CMakeLists.txt，生成 engine 静态库。
# engine 会链接 glfw、glad_gl_core_33、glm::glm、stb_image。
add_subdirectory(engine)

# 加入 example 子目录。
# CMake 会继续读取 example/CMakeLists.txt，生成 example_game 可执行程序。
# example_game 会链接 engine，因此间接使用上面的第三方库。
add_subdirectory(example)
