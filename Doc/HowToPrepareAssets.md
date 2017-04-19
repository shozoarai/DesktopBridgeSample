# How to prepare what is the kind of assets.
[タイルとアイコン アセットのガイドライン](https://docs.microsoft.com/ja-jp/windows/uwp/controls-and-patterns/tiles-and-notifications-app-assets) describe about variety assets by using Apps and to use scaling assets.

First, describe about the relationship of assets and AppxManifest.xml.
1. Logo element of Properties element's children：display icon on Windows Store.
2. Square150x150Logo element : Medium of Tile icon.
3. Square44x44Logo element : Apps list.
4. Wide310x150Logo element : Wide of Tile icon.
5. Square310x310Logo element : Large of Tile icon.
6. Square71x71Logo element : Small of Tile icon.
7. uap:Logo element of uap3:FileTypeAssociation element's children : file icon.

Especially the attention thing is Square44x44Logo element. It use 2 patterns. 
1. Apps icon on Taskbar, Apps list. So, use by Windows shell.
2. if not uap:Logo element, use file icon.

The assets by using Windows shell have two target-base (plated and un-plated) assets. 
   - Plated : File name is **filename.targetsize-*.png**, have background color.
   - Un-plated : File name is **filename.targetsize-*_altform-unplated.png**, background color is transparent. 
The icon of taskbar use **un-plated icon**. You ready filename.targetsize-*_altform-unplated.png assets, so you can show same icon of desktop applivation. This target-base asset's size is fllow size.
   - Minimum：16 x 16、24 x 24、32 x 32、48 x 48、256 x 256
   - Max：Adding minimum and 20 x 20、30 x 30、36 x 36、40 x 40、60 x 60、64 x 64、72 x 72、80 x 80、96 x 96  
The file name is filename.targetsize-16_altform-unplated.png, replace size instead of * .

When use file extension, recommended follow size.  
   - 63 x 63、129 x 129、336 x 336  
MSN video app have this assets. 

You prepared this variety assets, can show right assets on desktop, taskbar and Windows explorer.   

Require PRI resources for using target-base assets, please create PRI resources.  





# アセットの準備について
[タイルとアイコン アセットのガイドライン](https://docs.microsoft.com/ja-jp/windows/uwp/controls-and-patterns/tiles-and-notifications-app-assets) では、アプリが使用する様々なアセットとスケーリング対応のアセットについて説明しています。

最初に、アセットの AppxManifest.xml の関係を説明します。
1. Properties 要素の子要素である Logo：ストアに表示するアイコンです。
2. Square150x150Logo要素：タイルの中アイコンです。
3. Square44x44Logo要素：アプリの一覧です。
4. Wide310x150Logo要素：タイルの横長アイコンです。
5. Square310x310Logo要素：タイルの大アイコンです。
6. Square71x71Logo要素：タイル要素の小アイコンです。
7. uap3:FileTypeAssociation 要素の子要素である uap:Logo要素： ファイルのアイコンです。

注意が必要なものとしては、Square44x44Logo要素 になります。 この要素は、2種類の目的で使用されます。 
1. タスクバーのアプリアイコン、アプリの一覧。つまり、Windows シェルが使用します。
2. uap:Logo 要素が無い場合に、拡張子の関連付けアイコンになります。

Windows シェルが使用するアセットには、 ターゲット ベース(プレート付きとプレート無し)の 2種類があります。 
   - プレート付き：**filename.targetsize-*.png** で、背景色があります。
   - プレート無し：**filename.targetsize-*_altform-unplated.png** で、背景色が透明です。 
タスクバーに表示されるアイコンは、**プレート無し**を使用しますので、 filename.targetsize-*_altform-unplated.png を用意することでデスクトップ アプリと同じイメージでアイコンを表示できるようになります。このターゲット ベースのアセットのサイズは、次のように設定します。
   - 最小：16 x 16、24 x 24、32 x 32、48 x 48、256 x 256
   - 最大：最小に加えて、20 x 20、30 x 30、36 x 36、40 x 40、60 x 60、64 x 64、72 x 72、80 x 80、96 x 96  
ファイル名は、filename.targetsize-16_altform-unplated.png のように、* をサイズで置き換えます。

拡張子の関連付けを行っている場合は、以下のサイズも推奨しています。  
   - 63 x 63、129 x 129、336 x 336  
これは、MSN ビデオ アプリとドキュメントを参考に算出しています。 

これだけの種類のアセットを用意することで、デスクトップや Windows エクスプローラなどでアイコンが正しく表示されるようになります。  

ターゲット ベース アセットを使用するには、PRI リソースが必須となりますので、PRI リソースの作成をお願いします。
