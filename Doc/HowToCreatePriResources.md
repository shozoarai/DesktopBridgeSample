# How to create PRI resources.
[Desktop App Converter](https://docs.microsoft.com/en-us/windows/uwp/porting/desktop-to-uwp-run-desktop-app-converter) v1.0.6 used PRI resources, especially -MakeAppx option. PRI(Package Resource Index) Resources is new resources file by using new resource manager in UWP Apps. Of cource, you want to use scaling assets then you must create PRI resources.

First, ready PriConfig.xml and layout.resfiles.
1. Launch Desktop App Converter from start menu.
2. Launch task manager, then select "Open file location" for "DacTileLauncher.exe".
3. Open Icon_extract folder, then copy PriConfig.xml and layout.resfiles to your work folder.

For example folder structure:  
C:\DACWORK    
   - AppxLayout  : Appx Layout folder  
   - PriConfig.xml and layout.resfiles

Next, edit PriConfig.xml.

**before**  
`<index root="\" startIndexAt="layout.resfiles">`

**after**  
`<index root="\" startIndexAt="..\layout.resfiles">`

startIndexAt attribute is relative path of root attribute. So root attribute is root folder of appx layout.

layout.resfiles needs to be edited if the assets file has be renamed or if new assets have been added.

Then create PRI resource by using makepri utility. If AppxLayout folder contain pri files, you must delet it.

Current folder is "C:\DACWORK".  
`makepri.exe new /pr .\AppxLayout /cf .\PriConfig.xml /o`

Once complete, "Suucessfully Completed" is displayed. Then copy created PRI files to AppxLayout folde.

Finally, create appx package using makeappx utility.  
Current folder is "C:\DACWORK".  
````
SET PATH="C:\Program Files (x86)\Windows Kits\10\bin\x86";%PATH%  
makeappx.exe pack /d .\AppxLayout /l /p myApp.appx
````
Appx package creation is completed once you see the "Succeeded" message.



# PRI リソースの作成方法について
[Desktop App Converter](https://docs.microsoft.com/ja-jp/windows/uwp/porting/desktop-to-uwp-run-desktop-app-converter) v1.0.6 は、PRI リソースを使用します。 -MakeAppx オプションを使用すると、作成した Appx パッケージには PRI リソースが含まれています。 PRI(Package Resource Index) リソースは、UWP アプリ環境で提供される新しいリソース マネージャが使用するものです。この理由から、スケーリング対応アセットを使用する場合は、 PRI リソースを作成しなければなりません。

最初に、PriConfig.xml と layout.resfiles の準備をします。
1. スタート メニューより Desktop App Converter を起動します。
2. タスク マネージャを起動し、"DacTileLauncher.exe" のコンテキスト メニューより「ファイルの場所を開く」を選択します。
3. Icon_extract フォルダを開いてから、PriConfig.xml と layout.resfiles を作業フォルダーへコピーします。

作業フォルダの構造:  
C:\DACWORK    
   - AppxLayout  : Appx レイアウトが格納されています。  
   - PriConfig.xml と layout.resfiles

次に、 PriConfig.xml を編集します。

**変更前**  
`<index root="\" startIndexAt="layout.resfiles">`

**変更後**  
`<index root="\" startIndexAt="..\layout.resfiles">`

startIndexAt 属性は、root 属性に対する相対パスで指定します。root 属性は、Appx レイアウトのルート フォルダを示しています。

layout.resfiles は、Assets フォルダ内のファイルの一覧が含まれています。 Assets フォルダ内のファイル名などを変更する場合には、変更が必要になります。

makepri ユーティリティを使って、PRI リソースを作成します。 AppxLayout フォルダーに pri ファイルが存在する場合は、作成前に削除します。

カレント フォルダは "C:\DACWORK" を想定しています。  
`makepri.exe new /pr .\AppxLayout /cf .\PriConfig.xml /o`

正常に終了すると、"Suucessfully Completed" と表示されます。 作成された PRI ファイルを AppxLayout フォルダへコピーします。

最後に、makeappx ユーティリティを使って Appx パッケージを作成します。  
カレント フォルダは、 "C:\DACWORK" を想定しています。  
````
SET PATH="C:\Program Files (x86)\Windows Kits\10\bin\x86";%PATH%  
makeappx.exe pack /d .\AppxLayout /l /p myApp.appx
````
正常に終了すると、 "Succeeded" が表示されます。
