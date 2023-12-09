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

int main(int argc, char** argv){
    string input;

    Option option = parseOption(argc, argv);

    try {
        // 入力がコマンドライン引数の場合
        if(option.optionFlags.find(OptEnum::CommandlineTextInput) != option.optionFlags.end()) {
            input = option.commandlineText;

            Text<char> text = mecab::parseText(input);

            auto gomamayoWordIndexes = judgeGomamayo(text, option.degree);

            for(auto& index: gomamayoWordIndexes)
                cout << index << endl;

        // それ以外（ひたすら入力を受け付けて解析する）
        } else {
            cout << "gomamayo - Gomamayo Analyzer" << endl
                    << "enter 'quit' to exit program." << endl << endl;


            while(true) {
                cout << "text > ";
                cin >> input;

                if(input.compare("quit") == 0 || input.compare("q") == 0)
                    break;

                Text<char> text = mecab::parseText(input);

                auto gomamayoWordIndexes = judgeGomamayo(text, option.degree);

                for(auto& index: gomamayoWordIndexes)
                    cout << index << endl;
            }

            cout << "Bye." << endl;
        }
    } catch(exception& e) {
        cout << e.what();
    }
}
