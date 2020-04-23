# Usb2WebSocketService
WebSocket libusb-win32 QT service

在Web项目中用到USB扫码枪或者USB接口的下位机时，USB设备采集的数据通常需要在屏幕首先获取焦点才能输出
该工程通过libusb-win32驱动拦截USB设备的输入信息，转发到websocket端口上，web项目可以通过连接websocket服务获取USB输入信息

websocket默认端口为9009
libusb-win32安装配置借鉴该文章
https://blog.csdn.net/weijory/article/details/80943950
websocket服务采用qtservice 项目地址
https://github.com/tubaluga/qtservice

安装编译：
本项目为QT项目，在QT 5.14.2  MinGW 7.3.0 32-bit 下编译运行正常
clone项目后用QT打开ConsoleService.pro
选择MinGW 7.3.0 32-bit编译器
编译项目

编译后运行QT的MinGW 7.3.0 32-bit 命令行工具
进入项目下Release_x86或者Debug_x86文件夹中
输入命令导入依赖库
windeployqt UsbMonitor.exe

管理员权限运行cmd工具 进入UsbMonitor.exe所在目录
运行命令安装服务
UsbMonitor.exe -i

系统服务中启动服务


