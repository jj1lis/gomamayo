# gomamayo - Gomamayo Analyzer

gomamayo searches for Gomamayo substring from the input string and outputs it.

For more information about Gomamayo: [「ゴママヨサラダ」，しなちくシステム](https://thinaticsystem.com/glossary/gomamayo)

## dependency
You need prepare these environments and libraries to build and use gomamayo.

### charactor and locale
gomamayo requires the sysmem to support UTF-8 and to be able to set the locale to `ja_JP.UTF-8`.

### Morphological Analysis Library
gomamayo currently depends on one of the following morphological analysis libraries (MAL):

- MeCab (`mecab`)

## build

```bash
$ git clone git@github.com:jj1lis/gomamayo.git
$ cd gomamayo
$ make <MAL name>      # e.g. make mecab
```

Then the executable file `gomamayo` will be generated.

## usage

```
$ gomamayo (<option> <argument> | <option>)*
```

Arguments given to options that don't take arguments will be ignored.

`gomamayo` accepts the following options.

| option | abbreviation | argument |
|:-----:|:-----:|-----|
| `--input` | `-i` | string text |
| `--degree` | `-d` | number |
| `--verbose` | `-v` | (none) |

### option `--input`
`gomamayo` parses the string passed to this option and searches fort the Gomamayo part.

```bash
$ ./gomamayo -i 横須賀完熟果物のぞみトマト戸倉
横須賀完熟⁉️
完熟果物⁉️
果物のぞみ⁉️
トマト戸倉⁉️
```

If option `--input` is not specified, `gomamayo` will start as "sequencial Gomamayo mode." Type `quit` or `q` to exit execution.

```bash
$ ./gomamayo 
gomamayo - Gomamayo Analyzer (c) 型推栄 @_jj1lis_uec 2023
enter 'quit' or 'q' to exit program.

text > 林檎ゴリラ
林檎ゴリラ⁉️
text > 悪性インド銅鐸
悪性インド⁉️
インド銅鐸⁉️
text > 赤坂サカス
text > quit
```

### option `--degree`

You can specify the Gomamayo degree by argument of option `--degree`.


``` bash
$ ./gomamayo -i 株式公開買い付け -d 2
公開買い付け⁉️
$ ./gomamayo -i 聖遺物異物混入 -d 3
遺物異物⁉️
```

### option `--verbose`
If `--verbose` is specified, `gomamayo` outputs the readings and moras for each word.

```bash
$ ./gomamayo -i 新陳代謝社会人 -v
シンチンタイシャ: length/mora length = 8/7: シ ン チ ン タ イ シャ 
シャカイ: length/mora length = 4/3: シャ カ イ 
ジン: length/mora length = 2/2: ジ ン 

新陳代謝社会⁉️
```
