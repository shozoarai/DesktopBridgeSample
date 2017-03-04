# How to use Windows Runtime API from Desktop App
This sample show how to use Windows Runtime API from Desktop Windows App. This sample contain two projects.
- WinRtHelper: This is the Win32 DLL project. But set C++ compiler switch use /Zw /Gm-, So use [C++/CX](http://go.microsoft.com/fwlink/p/?LinkId=255561).
- WpfAppUsingWinRT: This is WPF Project by C#. It have two features. First, direct consume Windows Runtime by reference Windows metadata. Last, indirect consume Windows Runtime via C Dynamic Link Library.

# Windows ランタイム API をデスクトップ アプリから使用する方法
- WinRtHelper: このプロジェクトは、Win32 の DLL プロジェクトです。通常の DLL プロジェクトと異なるのは、コンパイラ スイッチに /Zw と /Gm- を使用して、[C++/CX](http://go.microsoft.com/fwlink/p/?LinkId=255561) で記述していることです。
-  WpfAppUsingWinRT: このプロジェクトは、C# の WPF プロジェクトです。2つの機能を持っています。1 つ目は、C# から Windows ランタイムを使用する機能です。最後は、関数をエクスポートした DLL を介して Windows ランタイムを使用する方法です。
