# utf8bom_changer

[English](#en)  
[Japanese](#jp)

<a id="en"></a>
## Add or remove UTF-8 BOM

I often end up with garbage when I open a UTF-8 CSV file with MS Excel.  
Why on earth do they require BOM of UTF-8 file??  
Anyway, it is tiresome to open the CSV file with a text editor and save it with BOM.  
So I made a simple tool to add or removde UTF-8 BOM.

Compiling: Use C-compiler of your choice.
```shell
cc -o utf8bom_changer utf8bom_changer.c
```

Usage: Give the file path(s) as parameters.
```shell
utf8bom_changer file1 file2 ...
```
Or drag and drop the files to the compiled binary.

If you give a file without UTF-8 BOM, the program adds it;  
if you give one with UTF-8 BOM, it is removed from the file;  
and then a new file whose name has '_' at the end is saved.

<a id="jp"></a>
## UTF-8のBOMを付加または除去
エクセルでCSVファイルを開くと文字化けすることがあります。  
なぜエクセルはUTF-8のファイルにBOMを要求するのでしょうか？  
ともかく，いちいちエディタで開いてBOM付きで保存し直すのは手間です。  
そこで，ごく簡単なツールを作りました。

コンパイル: お好みのCコンパイラをお使いください
```shell
cc -o utf8bom_changer utf8bom_changer.c
```

使い方: 引数にファイルパスを指定して実行してください。
```shell
utf8bom_changer file1 file2 ...
```
もしくは，ファイルをコンパイルしたバイナリにドラッグ＆ドロップしてください。

BOM無しのファイルはBOM付きに，BOM付きのファイルはBOM無しにして，  
元のファイル名の末尾に '_' を付加した新しいファイルを生成します。
