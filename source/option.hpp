/* gomamayo - Gomamayo Analyzer
 * Copyright: JJ1LIS (Katasuiron) 2023.
 *
 * This software can be used, modified and redistributed under the MIT License.
 * See also gomamayo/LICENSE.
 */

#include <cstddef>
#include <string>
#include <set>

namespace gomamayo {
    
    // 実行時のコマンドラインオプション
    
    enum OptEnum {
        SpecifyDegree,
        CommandlineTextInput,
        unknown,
    };

    struct Option {
        public:
            const std::set<OptEnum> optionFlags;

            const size_t degree;
            const std::string commandlineText;

            Option(std::set<OptEnum> optionFlags,
                    size_t degree = 1, std::string commandlineText = std::string()) :
                optionFlags(optionFlags), degree(degree), commandlineText(commandlineText) {}
    };

    // コマンドライン引数を受け取って Option にすべて格納する
    Option parseOption(int, char**);

    // オプションの指定子（"-", "--" 以降）からOptEnumに変換する
    OptEnum toOptEnum(const char* const);
}
