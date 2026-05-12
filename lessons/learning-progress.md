# Shader 学习进度记录

记录时间：2026-05-12

## 当前状态

已为当前 MiniGL2D 引擎整理 shader 学习材料：

- `lessons/shader-course-plan.md`：完整课程计划
- `lessons/01-first-fragment-shader.md`：第 1 课，第一个 fragment shader

学习路线参考 The Book of Shaders，但练习会落到当前项目的 OpenGL 2D 引擎里。

## 当前引擎要点

当前项目使用固定的 sprite 渲染流程：

- 顶点 shader：`assets/shaders/sprite.vert`
- 片段 shader：`assets/shaders/sprite.frag`
- 示例入口：`example/main.cpp`
- 示例程序绘制一个可移动、可旋转的 sprite
- 初期课程主要修改 `assets/shaders/sprite.frag`

程序运行时会相对当前工作目录查找资源，因此需要从 `build` 目录运行。

## 下次继续的步骤

### 1. 打开第一课

阅读：

```text
lessons/01-first-fragment-shader.md
```

### 2. 修改 fragment shader

按第一课说明修改：

```text
assets/shaders/sprite.frag
```

第一步可以先改成固定颜色：

```glsl
#version 330 core

out vec4 frag_color;

void main() {
    frag_color = vec4(1.0, 0.2, 0.1, 1.0);
}
```

### 3. 构建并运行

在项目根目录执行：

```powershell
cmake --build build
```

然后从 `build` 目录运行：

```powershell
cd build
.\example\Debug\example_game.exe
```

如果没有 `Debug` 目录，试：

```powershell
cd build
.\example\example_game.exe
```

## 第一课验收标准

完成第一课时，应该能做到：

- 把 sprite 改成任意纯色
- 解释 `vec4(r, g, b, a)` 的四个分量
- 解释 `frag_color` 是 fragment shader 的最终输出
- 解释为什么去掉 `texture(image, v_uv)` 后图片细节会消失

## 下一步计划

完成第一课后，继续制作并学习：

```text
第 2 课：坐标与 UV
```

第 2 课会使用 `v_uv`，让颜色根据像素在 sprite 内的位置变化，做出横向、纵向和二维渐变。

## 注意事项

- 如果修改 shader 后画面没有变化，先重新执行 `cmake --build build`。
- 如果提示找不到 shader 或 assets，确认程序是从 `build` 目录启动的。
- 初期不要同时改 C++、vertex shader 和 fragment shader；先专注 fragment shader。