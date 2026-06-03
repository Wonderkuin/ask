# 第 1 课：第一个 fragment shader

## 本课目标

完成这一课后，你应该能回答三个问题：

1. fragment shader 控制什么？
2. `vec4(1.0, 0.0, 0.0, 1.0)` 为什么是红色？
3. 当前引擎里的 `sprite.frag` 是如何影响屏幕上 sprite 的？

本课只修改一个文件：

```text
assets/shaders/sprite.frag
```

## 背景概念

当前引擎绘制的是一个 2D sprite。渲染时大致分两步：

1. `sprite.vert` 决定四边形顶点最终出现在屏幕哪里。
2. `sprite.frag` 决定四边形覆盖到的每个像素是什么颜色。

也就是说，今天你主要关心第二步：**每个像素输出什么颜色**。

当前原始 fragment shader 类似这样：

```glsl
#version 330 core

in vec2 v_uv;

uniform sampler2D image;
uniform vec4 tint;

out vec4 frag_color;

void main() {
    frag_color = texture(image, v_uv) * tint;
}
```

它的意思是：从图片 `image` 里按 `v_uv` 取颜色，再乘上 `tint`，最后输出到 `frag_color`。

本课先把图片采样拿掉，直接输出固定颜色。

## 颜色的 vec4

GLSL 中常用 `vec4` 表示 RGBA 颜色：

```glsl
vec4(red, green, blue, alpha)
```

每个分量通常在 `0.0` 到 `1.0` 之间：

| 写法 | 含义 |
|---|---|
| `vec4(1.0, 0.0, 0.0, 1.0)` | 不透明红色 |
| `vec4(0.0, 1.0, 0.0, 1.0)` | 不透明绿色 |
| `vec4(0.0, 0.0, 1.0, 1.0)` | 不透明蓝色 |
| `vec4(1.0, 1.0, 1.0, 1.0)` | 不透明白色 |
| `vec4(0.0, 0.0, 0.0, 1.0)` | 不透明黑色 |

alpha 是透明度，`1.0` 表示完全不透明，`0.0` 表示完全透明。

## 动手：输出固定颜色

把 `assets/shaders/sprite.frag` 改成：

```glsl
#version 330 core

out vec4 frag_color;

void main() {
    frag_color = vec4(1.0, 0.2, 0.1, 1.0);
}
```

这段 shader 不再使用图片，也不再使用 `tint`。它会把 sprite 覆盖的所有像素都变成同一种橙红色。

## 运行

在项目根目录构建：

```powershell
cmake --build build
```

然后从 `build` 目录运行：

```powershell
cd build
.\example\Debug\example_game.exe
```

如果没有 `Debug` 目录，试这个：

```powershell
cd build
.\example\example_game.exe
```

你应该看到原来的 sprite 变成一个纯色方块。

## 观察

运行后检查这些现象：

1. sprite 是否还在屏幕中央？
2. WASD 或方向键是否还能移动它？
3. 鼠标移动时它是否还会旋转？
4. 颜色是否不再显示原始图片细节？

如果 1、2、3 都正常，说明顶点位置、输入和 C++ 逻辑仍然工作；如果 4 成立，说明 fragment shader 已经接管了像素颜色。

## 练习 1：改颜色

只改这一行：

```glsl
frag_color = vec4(1.0, 0.2, 0.1, 1.0);
```

分别尝试：

```glsl
frag_color = vec4(0.0, 1.0, 0.0, 1.0);
```

```glsl
frag_color = vec4(0.0, 0.0, 1.0, 1.0);
```

```glsl
frag_color = vec4(1.0, 0.0, 1.0, 1.0);
```

每改一次，重新运行程序，观察颜色变化。

## 练习 2：保留 tint

现在把 `tint` 加回来：

```glsl
#version 330 core

uniform vec4 tint;

out vec4 frag_color;

void main() {
    frag_color = vec4(1.0, 1.0, 1.0, 1.0) * tint;
}
```

当前示例程序里 `sprite_.tint` 是偏蓝色，所以你应该看到 sprite 变成蓝绿色调。

然后把白色改成红色：

```glsl
frag_color = vec4(1.0, 0.0, 0.0, 1.0) * tint;
```

思考：为什么结果不是纯红色？

提示：颜色相乘是逐通道相乘。当前 C++ 里 tint 大致是：

```cpp
sprite_.tint = {0.3f, 0.7f, 1.0f, 1.0f};
```

所以：

```text
红色 vec4(1.0, 0.0, 0.0, 1.0)
乘以 tint vec4(0.3, 0.7, 1.0, 1.0)
得到 vec4(0.3, 0.0, 0.0, 1.0)
```

## 练习 3：恢复图片采样

最后恢复到接近原始版本：

```glsl
#version 330 core

in vec2 v_uv;

uniform sampler2D image;
uniform vec4 tint;

out vec4 frag_color;

void main() {
    vec4 image_color = texture(image, v_uv);
    frag_color = image_color * tint;
}
```

这次你应该重新看到图片细节，同时仍然带有 tint 的颜色影响。

## 常见错误

### 运行时提示找不到 shader

确保从 `build` 目录运行程序。当前程序会相对当前工作目录查找：

```text
assets/shaders/sprite.vert
assets/shaders/sprite.frag
assets/textures/player.png
```

### 改了 shader 但画面没变化

可能原因：

1. 你改的是 `assets/shaders/sprite.frag`，但 `build/assets/shaders/sprite.frag` 没更新。
2. 没有重新执行 `cmake --build build`。
3. 程序还在运行旧版本，需要关闭后重新打开。

### shader 编译失败

检查：

1. 每行结尾是否有分号。
2. `vec4` 是否有 4 个分量。
3. `frag_color` 是否声明为 `out vec4 frag_color;`。
4. GLSL 里浮点数建议写成 `1.0`，不要写成 `1`。

## 本课验收

你完成本课的标准：

- 能把 sprite 改成任意纯色。
- 能解释 `vec4(r, g, b, a)` 四个分量。
- 能说明 `frag_color` 是 fragment shader 的最终输出。
- 能说明为什么去掉 `texture(image, v_uv)` 后图片细节会消失。

## 下一课预告

下一课会使用 `v_uv`。你将不再让整个 sprite 都是同一个颜色，而是根据像素在 sprite 内的位置生成渐变。