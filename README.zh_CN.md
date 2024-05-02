<div style="text-align:center">
    <img src="documents/images/logo_256x256.png" , alt="logo" />
    <h1>Ultimate Conceptual Compiler</h1>
    <a href="LICENSE.md">
        <img src="https://img.shields.io/badge/License-Apache%202.0-green.svg" , alt="License" />
    </a>
    <a href="https://zh.cppreference.com">
        <img src="https://img.shields.io/badge/language-c++23-blue.svg" ,alt="cppreference" />
    </a>
    <a
        href="http://qm.qq.com/cgi-bin/qm/qr?_wv=1027&k=VwOd_SiQ31UIiX_QtI047ngYYgkzvvlB&authKey=HJecYKgB1HQCtIplBkNjeSxlat8OgNXtk47QURCS6y2c7dAifwHaKZaURIci6yE3&noverify=0&group_code=137136029">
        <img src="https://img.shields.io/badge/chat-on%20QQ-red.svg" , alt="QQ" />
    </a>
    <a
        href="https://discord.gg/xkvGy79e">
        <img src="https://img.shields.io/badge/chat-on%20Discord-7289da.svg" , alt="Discord" />
    </a>
</div>

|[English](README.md)|

## 联系我们

- [Discord](https://discord.gg/xkvGy79e)
- QQ: [137136029](http://qm.qq.com/cgi-bin/qm/qr?_wv=1027&k=VwOd_SiQ31UIiX_QtI047ngYYgkzvvlB&authKey=HJecYKgB1HQCtIplBkNjeSxlat8OgNXtk47QURCS6y2c7dAifwHaKZaURIci6yE3&noverify=0&group_code=137136029)
- 仓库: [Gitee](https://gitee.com/UltiELF/ucc), [GitHub](https://github.com/UltiELF/ucc)

## 介绍
Ultimate 概念化编译器

## Project
### ucx
C 家族编译器
* ucc (程序, GNU 风格 cc)
* u++ (程序, GNU 风格 cxx)
* ucl (程序, MSVC 风格 cl)
* ucu (程序, Ulti 风格 cu)
* ucx (动态链接库, 编译器主体)

### concept (header-only)
仅用于头文件的概念编译器
* cx (C 家族概念前端)
* optimizer (优化器)
* lc (汇编生成器)
* triplet (平台三连音)

## 特征
* 全概念化设计

## 如何构建
1. 安装 [[xmake]](https://github.com/xmake-io/xmake/)
2. 安装 [[gcc14+]](https://github.com/trcrsired/gcc-releases/releases) or [[llvm18+]](https://github.com/trcrsired/llvm-releases/releases)
3. 开始构建
```bash
$ xmake 
$ xmake install -o OutputPath 
```
4. 构建参数
```bash
$ xmake f -m [release|releasedbg|debug] -p [windows|mingw|linux|sun|msdosdjgpp|bsd|freebsd|dragonflybsd|netbsd|openbsd|macosx|iphoneos|watchos|wasm-wasip1|wasm-wasip2|cross ..] -a [x86_64|i386|arm|aarch64 ..] --cppstdlib=[default|libstdc++|libc++] ..
```
* 目前只支持 msvc 14.30+ ，gcc 14+ 以及 llvm 18+。
* 若要编译兼容 WIN10 (默认) 以下系统，请添加参数
```bash 
--min-win32-sys=[WIN10|WINBLUE|WIN8|WIN7|WS08|VISTA|WS03|WINXP|WIN2K]
```
* 对于WIN9X (i386-windows-gnu)
```bash
--min-win32-sys=[WINME|WIN98|WIN95]
```
* 使用llvm工具链
```bash 
--use-llvm=y|n(default)
```
* 编译使用本地指令集
```bash 
--native=y|n(default)
```
* 选择工具链
```bash 
--sdk=ToolchainPath
```
* 静态链接
```bash
--static=y(default)|n
```
* 设置 sysroot
```bash
--sysroot=<path>
```
* 记录每一步消耗的时间
```bash 
--timer=y|n(default)
```
* 启用清洁器
```bash
--policies=build.sanitizer.address --policies=build.sanitizer.leak
```
