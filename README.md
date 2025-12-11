> 0826:version0.1，根据使用情况还会实时更新

### JUCE GUI App 模板

这是一个基本的 JUCE 应用程序模板，使用 CMake 构建系统，帮助你快速启动 GUI 项目。

#### 包含的文件

  * **`CMakeLists.txt`**：项目的 CMake 构建文件。
  * **`Main.cpp`**：应用程序的入口点，负责创建主窗口。
  * **`MainComponent.h`**：主 GUI 组件的头文件。
  * **`MainComponent.cpp`**：主 GUI 组件的实现文件。

#### 快速开始

0. **使用本模版**：

    点击右上方使用模版，新建你的仓库。

1.  **克隆仓库**：

    ```bash
    git clone https://github.com/你的用户名/你的仓库名.git
    cd 你的仓库名
    ```

2.  **创建 CMake 构建目录**：

    ```bash
    mkdir build
    cd build
    ```

3.  **配置和生成项目文件**：

    ```bash
    # 在 macOS/Linux 上，生成 Makefile
    cmake ..

    # 在 Windows 上，生成 Visual Studio 解决方案
    cmake .. -G "Visual Studio 17 2022"
    ```

    *（注意：请根据你的系统和已安装的构建工具选择合适的生成器。）*

4.  **构建项目**：

    ```bash
    cmake --build .
    ```

5.  **运行程序**：构建成功后，你可以在 `build` 目录中找到生成的可执行文件并运行它。

#### 核心文件说明

  * **`MainComponent.h` 和 `MainComponent.cpp`**：这是你项目的核心。所有的 GUI 控件和逻辑都应该在这里实现。目前，它只是一个简单的“Hello World\!”示例。
  * **`CMakeLists.txt`**：这个文件包含了构建项目的所有配置。
      * `project()`：设置项目名称。
      * `juce_add_gui_app()`：创建一个可执行文件。
      * `target_sources()`：将你的 `.cpp` 文件添加到项目中。
      * `target_link_libraries()`：链接必要的 JUCE 模块。

#### 如何添加新的源文件

如果你添加了新的 `.cpp` 文件，记得在 `CMakeLists.txt` 中使用 `target_sources` 命令将它添加到你的目标中，例如：

```cmake
target_sources(YourAppTargetName PRIVATE
    Main.cpp
    MainComponent.cpp
    YourNewFile.cpp
)
```

**提示**：为了保持代码整洁，你可以将新类的声明（`.h`）和实现（`.cpp`）分开，并只在 `CMakeLists.txt` 中添加 `.cpp` 文件。
