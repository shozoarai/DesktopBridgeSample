========================================================================
    DYNAMIC LINK LIBRARY : StoreCppHelper Project Overview
========================================================================

AppWizard has created this StoreCppHelper DLL for you.

This file contains a summary of what you will find in each of the files that
make up your StoreCppHelper application.


StoreCppHelper.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

StoreCppHelper.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

StoreCppHelper.cpp
    This is the main DLL source file.

	When created, this DLL does not export any symbols. As a result, it
	will not produce a .lib file when it is built. If you wish this project
	to be a project dependency of some other project, you will either need to
	add code to export some symbols from the DLL so that an export library
	will be produced, or you can set the Ignore Input Library property to Yes
	on the General propert page of the Linker folder in the project's Property
	Pages dialog box.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named StoreCppHelper.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

Follow steps : for using Windows Runtime Object
Windows Runtime オブジェクトを使用するために行った作業

Modify project settings
プロジェクト ファイルの設定変更
1.[Configuration Properties]-[General]-[Target Platform Version]
  Set 10.0.14393 to Target Platform Version( Before Windows 8)
  [構成プロパティ]-[全般]-[ターゲット プラットフォーム バージョン]を
  10.0.14393 に変更(変更前は、Windows 8.1)

2.[C++]-[General]-[Consume Windows Runtime Extension]
  Set Yes(/ZW) to it (Before No)
  [C++]-[全般]-[Windows ランタイムの使用]
　はい(/ZW) に変更(変更前は、いいえ)

3.[C++]-[Code Generation]-[Enable Minimal Rebuild]
  Set No(/Gm-) to it (Before Yes Gm+)
  [C++]-[コード生成]-[最小リビルドを有効にする]
　いいえ(/Gm-) に変更(変更前は、はい Gm+)

4.[C++]-[General]-[Additional #using directories] add following items 
  [C++]-[全般]-[追加の #using ディレクトリ]
  $(SystemDrive)\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcpackages
  $(SystemDrive)\Program Files (x86)\Windows Kits\10\UnionMetadata
  $(SystemDrive)\Program Files (x86)\Windows Kits\10\References\Windows.Foundation.UniversalApiContract\1.0.0.0
  $(SystemDrive)\Program Files (x86)\Windows Kits\10\References\Windows.Foundation.FoundationContract\1.0.0.0
  を追加

  Set this settings  to per Configuration and Platform.
上記の 2 から 4 の設定を、構成(デバッグ、リリース)とプラットフォームごとに設定します。


Modify stdfx.h. add following items.
stdafx.h に対する変更
以下の内容を追加
// Collection header for Windows Runtime
#include <collection.h>
// For IInitializeWithWindow
#include "Shobjidl.h"


Write code in StoreCppHelper.cpp and etc.
StoreCppHelper.cpp のコードを記述

Add StoreCppHelper.def file.
  Add module definition file on Solution exprorer. Then wrote exported function.
StoreCppHelper.def の追加
　モジュール定義ファイルをソリューション エクスプローラから追加して、
　エクスポートする関数を記述しました。
