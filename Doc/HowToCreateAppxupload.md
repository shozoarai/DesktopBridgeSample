# How to create appxupload file.
You can upload appxupload file to Windows Store. Appxupload file include two or many files, Appx packages and Symbol packge. You upload appxupload file, then you can confirm the detail report of app's crush information.   

## How to create Appx package.

You can create appx package using [makeappx uitility](https://msdn.microsoft.com/en-us/library/windows/desktop/hh446767(v=vs.85).aspx).  

For example folder structure:  
C:\DACWORK    
   - AppxLayout  : locate Appx layout.  

Next, create appx package using makeappx utility.

**Command**  
`makeAppx pack /d <input directory> /p <output appx name> /l`

**Appx file name**is <App Name>_<Version>_<Architecture>.appx. For example , **FileTest_1.1.2.0_x86.appx**.

Next sign an Appx package.  

**Command**  
`signtool.exe sign -f <input pfx name> -fd SHA256 -v <appx name>`  

You want to extract Appx package, please use unpack option.  
`makeAppx unpack /p <input appx name> /d <output directory> /l`  
  

## How to create AppxBundle package.
AppxBundle package include program's appx and resources appx.  
C:\DACWORK    
   - AppPackages  : locate signed appx packages.  

Next, cretae AppxBundle package using  makeappx utility.

**Command**  
`makeAppx bundle /d <input directory> /p <output appxbundle name> /l`

**AppxBundle file name** is <App Name>_<Version>_<Architecture>.appxbundle. For example , **FileTest_1.1.2.0_x86.appxbundle**.

Mext sign an AppxBundle package. Of course, pfx file is same file as siged appx package. 

**Command**  
`signtool.exe sign -f <input pfx name> -fd SHA256 -v <appx bundle name>`  

You want to extract AppxBundle package, please use unbudle option.  
`makeAppx unbundle /p <input appxbundle name> /d <output directory> /l`


## How to create Symbol package.  
Symbol package is a zip format file, include PDB files only.  
**Symbol Package file name** is <App Name>_<Version>_<Architecture>.appxsym. For example, **FileTest_1.1.2.0_x86.appxsym** .  


## How to crate appxupload file.  
appxupload file is a ZIP format, include Appx package, or AppxBundle package, and Symbol package. The file name is <App Name>_<Version>_<Architecture>.appxupload. For example, **FileTest_1.1.2.0_x86.appxupload** .  
You upload it to Windows Store, then you can see detail report of app's crush report.  

 



# appxupload ファイルの作成方法について
appxupload ファイルは、Appx パッケージとシンボル パッケージを含めたファイルです。このファイルをWindows ストアへ提出することで、アプリのクラッシュ レポートなどで詳細情報を確認できるようになります。  

## Appx パッケージの作成方法について

[makeappx ユーティリティ](https://msdn.microsoft.com/en-us/library/windows/desktop/hh446767(v=vs.85).aspx)を使用することで、Appx パッケージを作成できます。  

作業フォルダの構造:  
C:\DACWORK    
   - AppxLayout  : Appx レイアウトが格納されています。  

次に、 makeappx ユーティリティを使用してappx を作成します。

**コマンド**  
`makeAppx pack /d <input directory> /p <output appx name> /l`

**Appx のファイル名**は、<App Name>_<Version>_<Architecture>.appx とします。たとえば、**FileTest_1.1.2.0_x86.appx** などにします。

次に、作成した Appx パッケージに署名します。  

**コマンド**  
`signtool.exe sign -f <input pfx name> -fd SHA256 -v <appx name>`  

Appx パッケージを展開する場合は、unpack オプションを使用します。  
`makeAppx unpack /p <input appx name> /d <output directory> /l`  
  

 
## AppxBundle パッケージの作成方法について
AppxBundle パッケージは、アプリをプログラムのAppx パッケージと言語リソースなどの Appx パッケージを1つにまとめたパッケージになります。  
C:\DACWORK    
   - AppPackages  : 署名済みの Appx パッケージを配置します。  

次に、 makeappx ユーティリティを使用してAppxBundle を作成します。

**コマンド**  
`makeAppx bundle /d <input directory> /p <output appxbundle name> /l`

**AppxBundle のファイル名**は、<App Name>_<Version>_<Architecture>.appxbundle とします。たとえば、**FileTest_1.1.2.0_x86.appxbundle** などにします。

次に、作成した AppxBundle パッケージに署名します。 AppxBudle パッケージは、収録された Appx パッケージを含めて同じ証明書で署名されている必要があることに注意してください。 

**コマンド**  
`signtool.exe sign -f <input pfx name> -fd SHA256 -v <appx bundle name>`  

AppxBundle パッケージを展開する場合は、unbudle オプションを使用します。  
`makeAppx unbundle /p <input appxbundle name> /d <output directory> /l`


## シンボル パッケージの作成方法について  
シンボル パッケージは、ZIP フォーマットのファイルで、PDB ファイルのみを収録しています。  
**シンボル パッケージのファイル名**は、<App Name>_<Version>_<Architecture>.appxsym とします。たとえば、**FileTest_1.1.2.0_x86.appxsym** などにします。  


## appxupload ファイルの作成方法について  
appxupload ファイルは、ZIP フォーマットのファイルで、Appx パッケージ、あるいは AppxBundle パッケージに加えて シンボル パッケージを収録します。ファイル名は、<App Name>_<Version>_<Architecture>.appxupload とします。 たとえば、**FileTest_1.1.2.0_x86.appxupload** などにします。  
このファイルを Windows ストアへ提出することで、クラッシュ レポートなどの詳細分析が可能になります。  

