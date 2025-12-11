# Example GUI App CMakeLists.txt

# 第一行需要是`cmake_minimum_required`制定对应版本
cmake_minimum_required(VERSION 3.22)

# 【需要在此处修改项目名称，建议Ctrl+D统一修改】

project(GuiApp VERSION 0.0.1)

# 引入JUCE源文件，已在上一级目录下载JUCE，直接引用上一级目录

# find_package(JUCE CONFIG REQUIRED)        # If you've installed JUCE to your system
# or
add_subdirectory(../JUCE JUCE)                    # If you've put JUCE in a subdirectory called JUCE

# 如果需要VST2 SDK，请调用juce_set_vst2_sdk_path

# juce_set_vst2_sdk_path(...)

# 使用`juce_add_gui_app`建立可执行目标，【需要修改项目名称】
# 相当于`add_executable`的同时默认添加了许多JUCE相关配置，如链接必要模块等。
# Check the readme at `docs/CMake API.md` in the JUCE repo for the full list.

juce_add_gui_app(GuiApp
    # VERSION ...                       # Set this if the app version is different to the project version
    # ICON_BIG ...                      # ICON_* arguments specify a path to an image file to use as an icon
    # ICON_SMALL ...
    # DOCUMENT_EXTENSIONS ...           # Specify file extensions that should be associated with this app
    # COMPANY_NAME ...                  # Specify the name of the app's author
    PRODUCT_NAME "GuiApp")     # The name of the final executable, which can differ from the target name

# 考虑到Projucer默认使用JuceHeader.h，这里保留这句话不变，注意【修改项目名称】。
# `juce_generate_juce_header`根据项目配置的模块需求生成JuceHeader.h
# 猜测`juce_add_gui_app`这一函数配置了默认的模块。

juce_generate_juce_header(GuiApp)

# 使用`target_sources`添加源文件，标注为PRIVATE属性。
# 【需要按照实际情况填写源文件名称及路径】

target_sources(GuiApp
    PRIVATE
        Main.cpp
        MainComponent.cpp)

# 使用`target_compile_definitions`添加宏定义，标注为PRIVATE属性。
# 下面的宏定义是在部分模块用到的，根据实际使用情况添加或修改。

target_compile_definitions(GuiApp
    PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:GuiApp,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:GuiApp,JUCE_VERSION>")

# 可以将需要的非代码文件创建为新的静态库，并于程序链接以供食用。
# 第一个参数是给新的静态库命名，`SOURCES`之后是源文件列表。

# juce_add_binary_data(GuiAppData SOURCES ...)

# 使用`target_link_libraries`将库链接到当前可执行目标中
# 如果上一步使用了GuiAppData需要同样在下面更改
# PUBLIC的三个库是JUCE为项目提供的预配置模块，为目标设置推荐的编译器标志。

target_link_libraries(GuiApp
    PRIVATE
        # GuiAppData            # If we'd created a binary data target, we'd link to it here
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

# ===============================================================
# 总结：
# 整个CmakeLists主要需要修改项目名称和源文件名称
# 其他内容暂时保留-0826
# ===============================================================