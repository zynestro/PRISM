## PRISM 产品需求文档 (PRD)

项目名称：PRISM（暂定）
类型：VST3 / AU 音频效果插件
核心理念：Tone / Space / Character —— 极简操作，一步到位的混音着色器
视觉风格：现代极简、方形视窗、暗色模式、动态视觉反馈

### 1. UI/UX
- 窗口：正方形 500×500（支持矢量缩放）
- 布局：上 70% 为 Visualizer Stage；下 30% 为 Control Deck（3 旋钮）
- 控件：
  - WILD（Width，中等）：0%→100%→200%，控制立体声宽度
  - TILT（Tone，最大）：-100→0→+100，频谱倾斜均衡
  - SATURA（Character，中等）：0%→100%，饱和/染色
- TILT 交互：右转提升高频并衰减低频；左转提升低频并衰减高频

### 2. DSP 规格
- Visualizer：后处理信号，平滑填充 FFT，快 Attack、慢 Release，默认半透明冷灰
- Tilt EQ：
  - Pivot：推荐 700Hz
  - 架构：Low Shelf + High Shelf
  - 设旋钮值 K ∈ [-1, 1]，MaxGain = 6 dB
  - High = K×MaxGain，Low = -K×MaxGain
- WILD / Width（M/S）：
  - 编码：M=(L+R)/2，S=(L-R)/2
  - 处理：S_new = S×W，W ∈ [0, 2]，默认 1
  - 解码：L_out = M + S_new，R_out = M - S_new
- SATURA：
  - 软失真：Output = tanh(Input×Drive)
  - Auto-Gain：Drive 增大时自动衰减输出保持响度一致
  - 过采样：建议 2× 或 4× 降低混叠

### 3. 视觉反馈
- Tilt：在频谱上叠加亮白细线；中心为直线，右转“/”，左转“\”
- WILD：左右边缘 Vignette Glow；>100% 发青蓝柔光向中心延展；<100% 变暗并向中心挤压
- SATURA：整体清晰度变化；增大时出现模糊与噪点，带 Bloom 质感

### 4. 技术栈
- 框架：JUCE（C++）
- 图形：JUCE Graphics 或 OpenGL（建议用 Shader 实现模糊与光晕）
- 兼容：Windows（VST3）、macOS（VST3/AU）

### 5. 下一步
- 先实现哪一部分：
  - GUI：搭建方形窗口与三旋钮，打通参数绑定与视觉反馈框架
  - DSP：实现 Tilt/Wild/Satura 三大算法，提供可测试的处理链
- 建议流程：先通 DSP 骨架与参数；再做 Visualizer 与反馈；最后微调 UI 细节

---

### 构建与运行（CMake + JUCE）
1. 创建构建目录：
```bash
mkdir build && cd build
```
2. 配置项目：
```bash
cmake ..
# Windows 例：
# cmake .. -G "Visual Studio 17 2022"
```
3. 构建：
```bash
cmake --build .
```
4. 运行：在 `build` 目录寻找生成的可执行文件
