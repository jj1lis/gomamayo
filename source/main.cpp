/* gomamayo - Gomamayo Analyzer
 * Copyright: JJ1LIS (Katasuiron) 2023.
 *
 * This software can be used, modified and redistributed under the MIT License.
 * See also gomamayo/LICENSE.
 */

#include <iostream>
#include <stdexcept>

#include "core.hpp"
#include "judge.hpp"
#include "wrapper/mecab.hpp"
#include "option.hpp"

using namespace std;
using namespace gomamayo;

void parse(const string& input, Option option) {
    //debug
    cout << "degree = " << option.degree << endl;

    Text<char> text = mecab::parseText(input);

    //debug
    cout << "parse completed." << endl;
    for(auto& word : text.getWords()) {
        cout << word.getReading().c_str() << ": size/morasize = " << word.getReading().size() << "/" << word.getMoraSize() << endl;
        for(const string& mora : word.getMoras()) {
            cout << mora.c_str() << " ";
        }
        cout << endl;
    }
    cout << endl;

    auto gomamayoWordIndexes = judgeGomamayo(text, option.degree);

    for(auto& index: gomamayoWordIndexes)
        cout << index << endl;

}

int main(int argc, char** argv){
    string input;

    Option option = parseOption(argc, argv);

    // try {
        // 入力がコマンドライン引数の場合
        if(option.optionFlags.find(OptEnum::CommandlineTextInput) != option.optionFlags.end()) {

            parse(option.commandlineText, option);


        // それ以外（ひたすら入力を受け付けて解析する）
        } else {
            cout << "gomamayo - Gomamayo Analyzer (c) 型推栄 @_jj1lis_uec 2023" << endl
                    << "enter 'quit' to exit program." << endl << endl;


            while(true) {
                cout << "text > ";
                cin >> input;

                if(input.compare("quit") == 0 || input.compare("q") == 0)
                    break;

                parse(input, option);
            }

            cout << "Bye." << endl;
        }
    // } catch(exception& e) {
    //     cerr << e.what() << endl;
    // }
}
