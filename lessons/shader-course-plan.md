# Shader 学习计划

这套课程以 The Book of Shaders 的学习顺序为主线，但练习会落到当前 MiniGL2D 引擎里。你每节课都应完成三件事：读懂一个概念、改一次 `assets/shaders/sprite.frag`、运行示例观察画面变化。

## 使用方式

1. 从第一课开始，不跳课。
2. 每课先备份或记录当前 `assets/shaders/sprite.frag` 的内容。
3. 按文档替换 fragment shader。
4. 从 `build` 目录运行示例程序，因为程序会相对工作目录查找 `assets/` 下的资源。
5. 完成课后练习，再进入下一课。

常用命令：

```powershell
cmake --build build
cd build
.\example\Debug\example_game.exe
```

如果你的生成器不是 Visual Studio，运行路径可能是：

```powershell
cd build
.\example\example_game.exe
```

## 课程路线

### 阶段一：理解 shader 管线

#### 第 1 课：第一个 fragment shader

目标：知道 fragment shader 控制每个像素的最终颜色。

你会学到：

- `#version 330 core`
- `in` / `uniform` / `out`
- `vec4` 颜色
- `frag_color` 的意义
- 当前引擎如何加载 `sprite.vert` 与 `sprite.frag`

产出：把 sprite 渲染成固定颜色，并能解释 RGBA 四个分量。

#### 第 2 课：坐标与 UV

目标：理解 `v_uv` 是每个像素在图片/四边形上的局部坐标。

你会学到：

- `vec2`
- `v_uv.x` / `v_uv.y`
- 用坐标生成渐变色
- OpenGL 颜色范围 `0.0` 到 `1.0`

产出：做出横向、纵向和二维渐变。

#### 第 3 课：uniform 与外部控制

目标：理解 CPU 侧程序如何把数据传给 shader。

你会学到：

- `uniform vec4 tint`
- 当前引擎的 `Shader::set_vec4()`
- `Sprite::tint` 如何影响 fragment shader

产出：通过 C++ 修改 sprite tint，并在 shader 中组合固定色、贴图色和 tint。

### 阶段二：用数学画 2D 图形

#### 第 4 课：造型函数

目标：用函数塑造颜色变化。

你会学到：

- `smoothstep()`
- `step()`
- `pow()`
- `mix()`

产出：做出硬边、软边、曲线渐变。

#### 第 5 课：画线和矩形

目标：用 UV 坐标判断一个像素是否属于某个形状。

你会学到：

- 条件判断的数学写法
- 用 `step()` 组合遮罩
- 矩形、边框、十字线

产出：在 sprite 内画一个可调大小的矩形。

#### 第 6 课：圆与距离场

目标：用 `distance()` 画圆和圆环。

你会学到：

- 坐标中心化
- `length()` / `distance()`
- signed distance field 的直觉

产出：画圆、圆环、软边圆。

#### 第 7 课：颜色混合

目标：掌握颜色组合方式。

你会学到：

- RGB 通道
- alpha
- `mix()`
- 颜色遮罩

产出：用图形遮罩在两种颜色之间切换。

### 阶段三：变换、图案与重复

#### 第 8 课：平移、缩放、旋转

目标：改变坐标，而不是直接改变图形。

你会学到：

- 坐标变换的思维
- 旋转矩阵
- 以中心点旋转

产出：让一个图案在局部坐标中旋转。

#### 第 9 课：重复图案

目标：用 `fract()` 制作平铺。

你会学到：

- `fract()`
- `floor()`
- 网格坐标
- tile 内局部坐标

产出：做出棋盘格、条纹、重复圆点。

### 阶段四：生成式图案

#### 第 10 课：伪随机

目标：理解 shader 中的随机不是传统随机，而是确定性函数。

你会学到：

- hash 风格随机函数
- 基于格子的随机值
- 随机颜色和随机大小

产出：每个格子生成不同亮度或颜色。

#### 第 11 课：噪声

目标：从离散随机过渡到连续随机。

你会学到：

- 插值噪声
- 平滑插值
- value noise

产出：做出云雾状灰度纹理。

#### 第 12 课：分形布朗运动 FBM

目标：叠加多层噪声形成自然纹理。

你会学到：

- octave
- frequency
- amplitude
- 多层噪声叠加

产出：做出类似烟、云、地形的纹理。

### 阶段五：项目练习

#### 第 13 课：制作一个可复用 shader 效果

目标：把前面内容组合成一个完整视觉效果。

可选方向：

- 能量护盾
- 扫描线
- 发光圆环
- 像素风传送门
- 动态水波纹理

产出：一个可截图展示的 shader 效果，并记录关键参数。

## 学习节奏建议

每课控制在 30 到 60 分钟：

1. 10 分钟读概念。
2. 10 分钟跑通给定代码。
3. 20 分钟做练习。
4. 10 分钟总结：这个 shader 里，颜色由哪些变量决定？

## 当前引擎学习重点

当前 MiniGL2D 使用固定的 sprite 渲染管线：

- 顶点阶段在 `assets/shaders/sprite.vert` 中处理位置和 UV。
- 片段阶段在 `assets/shaders/sprite.frag` 中决定像素颜色。
- 示例程序绘制一个 100x100 的 sprite。
- 初期课程只改 `sprite.frag`，避免同时学习太多 C++ 和 OpenGL 管线细节。

等你完成前 3 课后，再考虑给引擎增加 `time`、`resolution`、`mouse` 这类 The Book of Shaders 常用 uniform。