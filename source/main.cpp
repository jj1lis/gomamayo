/* gomamayo - Gomamayo Analyzer
 * Copyright: JJ1LIS (Katasuiron) 2023.
 *
 * This software can be used, modified and redistributed under the MIT License.
 * See also gomamayo/LICENSE.
 */

#include <stdexept>

#include "core.hpp"
#include "judge.hpp"
#include "wrapper/mecab.hpp"
#include "option.hpp"

using namespace std;
using namespace gomamayo;

int main(int argc, char** argv){
    Option option = parseOption(argc, argv);

    try {
        // 入力がコマンドライン引数の場合
        if(option.optionFlags.contains(OptEnum::commandlineTextInput)) {
            // TODO
        // それ以外（ひたすら入力を受け付けて解析する）
        } else {
            // TODO
        }
    } catch(exception& e) {
        cout << e.what();
    }
}
