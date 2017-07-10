# How to use In App Purchase API from Desktop App
This sample show how to use In App Purchase(IAP) API from Desktop Windows App. This sample contain two projects.
- StoreCppHelper: This is the Win32 DLL project. But set C++ compiler switch use /Zw /Gm-, So use [C++/CX](http://go.microsoft.com/fwlink/p/?LinkId=255561).
- StoreTestHelper: This is WPF Project by C#. It have two features. First, direct consume Windows Runtime by reference Windows metadata. Last, indirect consume Windows Runtime via C Dynamic Link Library.

 Provided senario is following.
- Get App License information.
- Get Durable add-on License information.
- Purchase App license on Trial version.
- Get Add-on list.
- Puchase Add-on.
- Get add-on list of lincensed add-on.
- Get consumable add-on balance remaining
- Report consumable fulfillment of add-on.


# アプリ内購入(IAP) API をデスクトップ アプリから使用する方法
このサンプルは、Windows のデスクトップ アプリケーション から アプリ内購入 API の使い方を示しています。このサンプルには、次の 2 つのプロジェクトが含まれています。 
- StoreCppHelper: このプロジェクトは、Win32 の DLL プロジェクトです。通常の DLL プロジェクトと異なるのは、コンパイラ スイッチに /Zw と /Gm- を使用して、[C++/CX](http://go.microsoft.com/fwlink/p/?LinkId=255561) で記述していることです。
- StoreTestHelper: このプロジェクトは、C# の WPF プロジェクトです。このサンプルは、2つの機能を持っています。1 つ目は、C# から Windows ランタイムを使用する機能です。最後は、関数をエクスポートした DLL を介して Windows ランタイムを使用する方法です。

IAP API の使い方には、以下の内容があります。
- アプリのライセンス情報を取得します。
- 永続アドオンのライセンス情報を取得します。
- 試用版からのアプリ ライセンスの購入。
- アドオンのリストを取得。
- アドオンの購入。
- 購入済みのアドオンのリストを取得。
- 開発者管理とストア管理の消費可能なアドオンの残数の取得。
- 開発者管理とストア管理の消費可能なアドオンの消費数の報告。

