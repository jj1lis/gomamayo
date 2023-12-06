/* gomamayo - Gomamayo Analyzer
 * Copyright: JJ1LIS (Katasuiron) 2023.
 *
 * This software can be used, modified and redistributed under the MIT License.
 * See also gomamayo/LICENSE.
 */

#include <string>
#include <map>

#include "option.hpp"

namespace gomamayo {
    // コマンドライン引数を受け取って Option にすべて格納する
    Option parseOption(int argc, char** argv){
        size_t degree = 0;
        auto commandlineText = std::string();

        auto flags = std::map<OptEnum, bool>;
        for(int i = 1; i < argc; i++){

            // オプション指定子
            if(argv[i][0] == '-') {
                // TODO
            } 
        }
    }

    // オプションの指定子（"-", "--" 以降）からOptEnumに変換する
    OptEnum toOptEnum(const char* const _option) {
        std::string option(_option);

        if(option.compare("input") == 0 || option.compare("i") == 0)
            return OptEnum::CommandlineTextInput;

        if(option.compare("degree") == 0 || option.compare("d") == 0)
            return OptEnum::SepcifyDegree;

        return OptEnum::unknown;
    }
}
