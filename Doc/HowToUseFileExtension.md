# How to use file extension settings

Converted apps have a variety of options for registering to handle certain file types and integrating into File Explorer. This allows users to easily access your app as part of their normal workflow. For example, coverterd VLC media player's appxmanifest contain follow.

````
<uap3:Extension Category="windows.fileTypeAssociation">
  <uap3:FileTypeAssociation 
  　 Name="3g2"
  　 Parameters="--started-from-file &quot;%1&quot;">
    <uap:SupportedFileTypes>
      <uap:FileType>.3g2</uap:FileType>
    </uap:SupportedFileTypes>
    <uap2:SupportedVerbs>
       <uap3:Verb
       　 Id="AddToPlaylistVLC"
       　 Parameters="--started-from-file --playlist-enqueue &quot;%1&quot;">AddToPlaylistVLC</uap3:Verb>
       <uap3:Verb
       　 Id="PlayWithVLC"
       　 Parameters="--started-from-file --no-playlist-enqueue &quot;%1&quot;">PlayWithVLC</uap3:Verb>
    </uap2:SupportedVerbs>
  </uap3:FileTypeAssociation>
</uap3:Extension>
<uap3:Extension Category="windows.fileTypeAssociation">
  <uap3:FileTypeAssociation
  　 Name="3ga"
  　 Parameters="--started-from-file &quot;%1&quot;">
    <uap:SupportedFileTypes>
              <uap:FileType>.3ga</uap:FileType>
    </uap:SupportedFileTypes>
    <uap2:SupportedVerbs>
       <uap3:Verb
       　 Id="AddToPlaylistVLC"
       　 Parameters="--started-from-file --playlist-enqueue &quot;%1&quot;">AddToPlaylistVLC</uap3:Verb>
       <uap3:Verb
       　 Id="PlayWithVLC"
       　 Parameters="--started-from-file --no-playlist-enqueue &quot;%1&quot;">PlayWithVLC</uap3:Verb>
    </uap2:SupportedVerbs>
  </uap3:FileTypeAssociation>
</uap3:Extension>
````

Or Below is a substitute above.
````
<uap3:Extension Category="windows.fileTypeAssociation">
  <uap3:FileTypeAssociation 
  　 Name="3g2"
  　 Parameters="&quot;%1&quot;">
    <uap:SupportedFileTypes>
      <uap:FileType>.3g2</uap:FileType>
    </uap:SupportedFileTypes>
  </uap3:FileTypeAssociation>
</uap3:Extension>
<uap3:Extension Category="windows.fileTypeAssociation">
  <uap3:FileTypeAssociation
  　 Name="3ga"
  　 Parameters="&quot;%1&quot;">
    <uap:SupportedFileTypes>
              <uap:FileType>.3ga</uap:FileType>
    </uap:SupportedFileTypes>
  </uap3:FileTypeAssociation>
</uap3:Extension>
````

If you want to chose executable file per file extension, you can use Executable attribute.
````
<uap3:Extension Category="windows.fileTypeAssociation">
  <uap3:FileTypeAssociation 
  　 Name="3g2"
  　 Parameters="&quot;%1&quot;">
    <uap:SupportedFileTypes>
      <uap:FileType>.3g2</uap:FileType>
    </uap:SupportedFileTypes>
  </uap3:FileTypeAssociation>
</uap3:Extension>
<uap3:Extension
      Category="windows.fileTypeAssociation"
      Executable="YourChosen.exe"
      EntryPoint="Windows.FullTrustApplication" >
  <uap3:FileTypeAssociation
  　 Name="3ga"
  　 Parameters="&quot;%1&quot;">
    <uap:SupportedFileTypes>
              <uap:FileType>.3ga</uap:FileType>
    </uap:SupportedFileTypes>
  </uap3:FileTypeAssociation>
</uap3:Extension>
````

When use Executable attribute, must use EntryPoint attribute. EntryPoint attribute chose follo one.
- Entry point of UWP App.
- Windows.FullTrustApplication. it's converted app.

Of course, Executable Attribute can use "Windows.Protocol" too.

If you want to show "Type of file" on file property page, please set uap:DisplayName element to FileTypeAssociation child element.
- uap:Logo : show file icon per file extension. If don't use it, use Square44x44Logo instead of it.
- uap:DisplayName : "Type of File" on file property page.
- uap:InfoTip : show tooltip on Windows Explorer.

If can't work of multiple file extension setting, please try follow methodologies.
- descending order of Extension define, for example z --> a order.  
This is same of Visual Studio manifest designer.
- uap prefix instead of uap3.

Not resolve yet, please investigate registry, especially HKEY_CLASSES_ROOT and HKEY_CURRENT_USER\Software\Classes.

# ファイルの拡張子の関連付けを使用する方法について
変換したアプリは、Windows エクスプローラで処理できる拡張子を登録する機能を持っています。拡張子の関連付けによって、用意にアプリへアクセスできるようになります。たとえば、変換した VLC メディア プレーヤーには、次のような定義が appxmanifest に含まれています。

````
<uap3:Extension Category="windows.fileTypeAssociation">
  <uap3:FileTypeAssociation 
  　 Name="3g2"
  　 Parameters="--started-from-file &quot;%1&quot;">
    <uap:SupportedFileTypes>
      <uap:FileType>.3g2</uap:FileType>
    </uap:SupportedFileTypes>
    <uap2:SupportedVerbs>
       <uap3:Verb
       　 Id="AddToPlaylistVLC"
       　 Parameters="--started-from-file --playlist-enqueue &quot;%1&quot;">AddToPlaylistVLC</uap3:Verb>
       <uap3:Verb
       　 Id="PlayWithVLC"
       　 Parameters="--started-from-file --no-playlist-enqueue &quot;%1&quot;">PlayWithVLC</uap3:Verb>
    </uap2:SupportedVerbs>
  </uap3:FileTypeAssociation>
</uap3:Extension>
<uap3:Extension Category="windows.fileTypeAssociation">
  <uap3:FileTypeAssociation
  　 Name="3ga"
  　 Parameters="--started-from-file &quot;%1&quot;">
    <uap:SupportedFileTypes>
              <uap:FileType>.3ga</uap:FileType>
    </uap:SupportedFileTypes>
    <uap2:SupportedVerbs>
       <uap3:Verb
       　 Id="AddToPlaylistVLC"
       　 Parameters="--started-from-file --playlist-enqueue &quot;%1&quot;">AddToPlaylistVLC</uap3:Verb>
       <uap3:Verb
       　 Id="PlayWithVLC"
       　 Parameters="--started-from-file --no-playlist-enqueue &quot;%1&quot;">PlayWithVLC</uap3:Verb>
    </uap2:SupportedVerbs>
  </uap3:FileTypeAssociation>
</uap3:Extension>
````

上記の代わりとして、次の表記でも構いません。
````
<uap3:Extension Category="windows.fileTypeAssociation">
  <uap3:FileTypeAssociation 
  　 Name="3g2"
  　 Parameters="&quot;%1&quot;">
    <uap:SupportedFileTypes>
      <uap:FileType>.3g2</uap:FileType>
    </uap:SupportedFileTypes>
  </uap3:FileTypeAssociation>
</uap3:Extension>
<uap3:Extension Category="windows.fileTypeAssociation">
  <uap3:FileTypeAssociation
  　 Name="3ga"
  　 Parameters="&quot;%1&quot;">
    <uap:SupportedFileTypes>
              <uap:FileType>.3ga</uap:FileType>
    </uap:SupportedFileTypes>
  </uap3:FileTypeAssociation>
</uap3:Extension>
````

拡張子ごとに実行ファイルを指定したい場合は、Executable 属性を使用します。
````
<uap3:Extension Category="windows.fileTypeAssociation">
  <uap3:FileTypeAssociation 
  　 Name="3g2"
  　 Parameters="&quot;%1&quot;">
    <uap:SupportedFileTypes>
      <uap:FileType>.3g2</uap:FileType>
    </uap:SupportedFileTypes>
  </uap3:FileTypeAssociation>
</uap3:Extension>
<uap3:Extension
      Category="windows.fileTypeAssociation"
      Executable="YourChosen.exe"
      EntryPoint="Windows.FullTrustApplication" >
  <uap3:FileTypeAssociation
  　 Name="3ga"
  　 Parameters="&quot;%1&quot;">
    <uap:SupportedFileTypes>
              <uap:FileType>.3ga</uap:FileType>
    </uap:SupportedFileTypes>
  </uap3:FileTypeAssociation>
</uap3:Extension>
````

Executable 属性を使用すると、EntryPoint 属性も使用しなければばりません。 EntryPoint 属性は、次の中から 1 つを指定します。
- UWP アプリのエントリー ポイント。
- Windows.FullTrustApplication。 これは、変換したアプリの場合です。

Executable 属性は、"Windows.Protocol" でも同じように使用することができます。

ファイルのプロパティのファイルの種類を使う場合は、 FileTypeAssociation の子要素として、uap:DiaplyName 要素を設定してください。
- uap:Logo : 拡張子ごとのアイコンを表示します。指定しない場合は、Square44x44Logo が使用されます。
- uap:DisplayName : プロパティのファイルの種類へ表示します。
- uap:InfoTip : Windows エクスプローラでツールチップに表示します。


複数の拡張子の関連付けを行って、動作がおかしい場合は、次に示す方法を試してみます。
- Extension の定義を、z から a の順序にします。  
Visual Studio の マニフェスト デザイナは、このように出力します。
- uap3 の代わりに、uap を使用します。

まだ解決しない場合は、基本に立ち返ってレジストリを調査してください。特に HKEY_CLASSES_ROOT と HKEY_CURRENT_USER\Software\Classes を確認してみてください。
