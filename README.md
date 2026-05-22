# Monopoly

这是一个基于 EasyX 的 Windows 大富翁小游戏，适合已经学习 C/C++ 基础和面向对象思想的同学阅读、复现和继续扩展。

项目采用接近 MVC 的分层方式：

- `window`：负责 EasyX 窗口、地图、玩家状态、事件提示等界面显示。
- `controller`：负责处理用户点击骰子后的回合流程，并协调界面和游戏数据。
- `game`：负责保存游戏状态和处理移动、买房、升级、卡片、新闻事件等规则。
- `model`：负责玩家、地图、骰子、房屋、卡片等基础实体。

## 目录结构

```text
.
├── CMakeLists.txt
├── README.md
├── docs/
│   └── design/
│       └── V10-helper.mdj
├── include/
│   ├── app.h
│   ├── controller.h
│   ├── game.h
│   ├── window.h
│   └── model/
│       ├── card.h
│       ├── dice.h
│       ├── house.h
│       ├── map.h
│       └── player.h
└── src/
    ├── app.cpp
    ├── controller.cpp
    ├── game.cpp
    ├── main.cpp
    ├── window.cpp
    └── model/
        ├── card.cpp
        ├── dice.cpp
        ├── house.cpp
        ├── map.cpp
        └── player.cpp
```

## 构建环境

该项目依赖 Windows、EasyX 和 Windows API。推荐使用 Visual Studio 或支持 MSVC 的 CMake 环境构建。

```bash
cmake -S . -B build
cmake --build build
```

在 macOS 或 Linux 上可以执行 CMake 配置来检查项目结构，但不会生成可运行目标，因为 EasyX 只支持 Windows。

## 运行资源

界面代码会从 `images/` 目录读取地图、玩家、骰子和事件图片。如果仓库中只有压缩包，请先将资源解压到项目根目录下的 `images/` 目录，再运行游戏。

## 当前状态

代码已经按应用层、控制层、游戏逻辑层和模型层整理目录，并补充了 CMake 项目入口。后续如果继续优化，建议优先处理内存释放、随机数初始化、路径配置和游戏规则测试。
