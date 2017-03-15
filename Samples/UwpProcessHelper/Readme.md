# How to detect UWP App process from Desktop App

This sample show how to detect the process type from Desktop Windows App. Detected process type is follow.
- Desktop App Process : Running on desktop.
- UWP App Process : Running on UWP app of desktop Bridge.

This sample use [GetCurrentPackageFullName function](https://msdn.microsoft.com/en-us/library/windows/desktop/hh446599(v=vs.85).aspx). This function's return value have APPMODEL_ERROR_NO_PACKAGE. So using it, can detect UWP App Process.


# デスクトップ アプリから、UWP アプリかどうかを判定するには

このサンプルは、デスクトップ アプリが UWP アプリとして動作しているかどうかを判定します。判定するのは、以下の 2種類の状態です。
- デスクトップ アプリのプロセス : デスクトップ上で動作
- UWP アプリ プロセス : デスクトップ ブリッジ機能によって、UWP アプリとして動作

このサンプルは、 [GetCurrentPackageFullName 関数](https://msdn.microsoft.com/en-us/library/windows/desktop/hh446599(v=vs.85).aspx) を使用しています。この関数の戻り値は、APPMODEL_ERROR_NO_PACKAGE を持っています。この値を使うことで、UWP アプリとして動作しているかを判断することはができます。
 
