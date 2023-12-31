/* gomamayo - Gomamayo Analyzer
 * Copyright: JJ1LIS (Katasuiron) 2023.
 *
 * This software can be used, modified and redistributed under the MIT License.
 * See also gomamayo/LICENSE.
 */

#include <string>
#include <set>
#include <stdexcept>

// debug
#include <iostream>
using namespace std;

#include "option.hpp"

namespace gomamayo {
    // コマンドライン引数を受け取って Option にすべて格納する
    Option parseOption(int argc, char** argv){
        size_t degree = 1;
        auto commandlineText = std::string();

        auto flags = std::set<OptEnum>();
        OptEnum option = OptEnum::Unknown;
        for(int i = 1; i < argc; i++){

            // オプション指定子
            if(argv[i][0] == '-') {
                if(argv[i][1] == '-') {
                    option = toOptEnum(&argv[i][2]);
                    flags.insert(option);
                } else  {
                    option = toOptEnum(&argv[i][1]);
                    flags.insert(option);
                }
            // オプション引数
            } else {
                switch(option) {
                    case OptEnum::SpecifyDegree:
                        degree = std::stoi(argv[i]);
                        option = OptEnum::Unknown;
                        break;
                    case OptEnum::CommandlineTextInput:
                        commandlineText = std::string(argv[i]);
                        option = OptEnum::Unknown;
                        break;
                    case OptEnum::Unknown:
                        throw std::runtime_error("Invalid option or argument.");
                    default:
                        ;   // nop （引数を持たないオプションに引数が渡されたときは無視する： e.g. "--verbose hoge"）
                }
            }
        }

        return Option(flags, degree, commandlineText);
    }

    // オプションの指定子（"-", "--" 以降）からOptEnumに変換する
    OptEnum toOptEnum(const char* const optionCharStr) {
        std::string option(optionCharStr);

        if(option.compare("input") == 0 || option.compare("i") == 0) {
            return OptEnum::CommandlineTextInput;
        }

        if(option.compare("degree") == 0 || option.compare("d") == 0) {
            return OptEnum::SpecifyDegree;
        }

        if(option.compare("verbose") == 0 || option.compare("v") == 0) {
            return OptEnum::Verbose;
        }

        return OptEnum::Unknown;
    }
}
