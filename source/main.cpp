/* gomamayo - Gomamayo Analyzer
 * Copyright: JJ1LIS (Katasuiron) 2023.
 *
 * This software can be used, modified and redistributed under the MIT License.
 * See also gomamayo/LICENSE.
 */

#include <iostream>
#include <stdexcept>

// 日本語対応に時間が掛かるのでとりあえず応急処置
#include <clocale>

#include "core.hpp"
#include "judge.hpp"
#include "wrapper/mecab.hpp"
#include "option.hpp"

using namespace std;
using namespace gomamayo;

void parse(const string& input, Option option) {
    Text<wchar_t> text = mecab::parseText(input);

    if(option.optionFlags.find(OptEnum::Verbose) != option.optionFlags.end()) {
        for(auto& word : text.getWords()) {
            wcout << word.getReading().c_str() << L": length/mora length = " << word.getReading().size() << L"/" << word.getMoraSize() << L": ";
            for(const wstring& mora : word.getMoras()) {
                wcout << mora.c_str() << L" ";
            }
            wcout << endl;
        }
        wcout << endl;
    }

    auto gomamayoWordIndexes = judgeGomamayo(text, option.degree);

    for(auto& index: gomamayoWordIndexes) {
        wcout << text[index].getWord() << text[index + 1].getWord() << L"⁉️" << endl;
    }

}

int main(int argc, char** argv){
    // ロケールを日本語の UTF-8 にセット
    setlocale(LC_CTYPE, "ja_JP.UTF-8");

    string input;

    Option option = parseOption(argc, argv);

    try {
        // 入力がコマンドライン引数の場合
        if(option.optionFlags.find(OptEnum::CommandlineTextInput) != option.optionFlags.end()) {

            parse(option.commandlineText, option);


        // それ以外（ひたすら入力を受け付けて解析する）
        } else {
            wcout << L"gomamayo - Gomamayo Analyzer (c) 型推栄 @_jj1lis_uec 2023" << endl
                    << L"enter 'quit' or 'q' to exit program." << endl << endl;


            while(true) {
                wcout << L"text > ";
                cin >> input;

                if(input.compare("quit") == 0 || input.compare("q") == 0)
                    break;

                parse(input, option);
            }

            cout << "Bye." << endl;
        }
    } catch(exception& e) {
        cerr << e.what() << endl;
    }
}
