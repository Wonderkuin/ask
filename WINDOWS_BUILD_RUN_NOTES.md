# Windows 编译与运行进度记录

## 当前结论

这个 2D 引擎理论上可以在 Windows 环境正常编译和运行。

项目是一个标准的 CMake + C++17 工程，使用 OpenGL 3.3 Core，主要依赖包括：

- GLFW：窗口创建和输入处理
- GLAD：OpenGL 函数加载
- GLM：数学库
- stb_image：图片加载

这些依赖都通过 CMake `FetchContent` 自动下载。

## 当前环境状态

已检查当前 Windows 环境，暂时没有检测到以下构建工具：

- `cmake`
- `cl`
- `g++`
- `ninja`

因此当前不能直接编译，需要先安装构建工具。

## 推荐安装工具

推荐安装：

1. CMake for Windows
   - 安装时勾选 `Add CMake to the system PATH`

2. Visual Studio 2022 Build Tools
   - 选择 `Desktop development with C++`
   - 需要包含 MSVC C++ compiler 和 Windows SDK

安装完成后，重新打开 PowerShell，或使用：

- `Developer PowerShell for VS 2022`
- `x64 Native Tools Command Prompt for VS 2022`

## 编译步骤

进入项目目录：

```powershell
cd C:\Users\TU\Documents\Workspace\ask
```

配置项目：

```powershell
cmake -S . -B build
```

编译 Debug 版本：

```powershell
cmake --build build --config Debug
```

## 运行步骤

README 中说明程序需要从 `build` 目录运行，因为程序会相对当前工作目录查找 `assets/` 下的资源。

运行 Debug 版本：

```powershell
cd build
.\example\Debug\example_game.exe
```

如果编译的是 Release 版本，则运行：

```powershell
.\example\Release\example_game.exe
```

## 一条龙命令

安装好构建工具后，可以尝试：

```powershell
cd C:\Users\TU\Documents\Workspace\ask
cmake -S . -B build
cmake --build build --config Debug
cd build
.\example\Debug\example_game.exe
```

## 常见问题

如果窗口打不开，可能原因包括：

- 显卡或驱动不支持 OpenGL 3.3 Core
- 没有从 `build` 目录运行，导致找不到 `assets/` 下的 shader 或 texture 资源
- CMake 下载 GitHub 依赖失败
- 没有安装 Visual Studio C++ 编译工具

## 下次继续时的建议

下一步应该先安装 CMake 和 Visual Studio 2022 Build Tools，然后重新打开终端，执行：

```powershell
cmake --version
cl
```

确认工具可用后，再执行配置、编译和运行命令。
