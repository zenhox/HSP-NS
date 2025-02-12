# HSP-NS

这个项目指在重新实现一套离散事件模拟器调度机制，从而提高模拟器的执行效率。
本项目做了模块化构建方式，新的模型可以复用core中的接口。test既是一个测试，也是使用core的样例。
新的模型可以新建一个子目录，并粘贴CMakeLists.txt.example作为新模块的编译配置文件。
主要有两个阶段：

* 实现NS3调度机制，达到和NS3不相上下的执行时间。
* 实现基于时间片的调度机制，对比两种方法的执行效果。

其中：

* core目录下是模拟器核心模块，包括模拟器，事件管理器，时间模块等。
* lib目录下存放了本项目用到的日志模块， g3log是一个高性能的异步日志框架。
* test目录初步展示的core中模拟器的使用方法，包括事件的生成。
* CMakeLists.txt.example 在core基础下，新建模拟场景时所需要的cmake配置模板.

## test_core 模块

测试将类方法作为event，传入模拟器不同时间执行，同时测试了在一个event中生成新的event.

## network 模块

作为一个基本模块，初步主要实现节点(Node) 和 连接(Link)模型概念, 实现send和receive等基本功能.

## test_network 模块

测试网络模块的功能, 实现了点对点的 发包测试.

## udpflood

模拟一个规模可以拓展的udpflood场景：

* 基于Node实现 udpclient 和 udpserver功能.
* 构建拓扑开启模拟.

## ns3work

这个目录围绕着ns3所做的事情，包括事件解析器，以及udpflood ns3仿真代码，仅作为保存点.



