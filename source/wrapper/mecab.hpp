/* gomamayo - Gomamayo Analyzer
 * Copyright: JJ1LIS (Katasuiron) 2023.
 *
 * This software can be used, modified and redistributed under the MIT License.
 * See also gomamayo/LICENSE.
 */

#pragma once

#include <exception>
#include <mecab.h>
#include "../core.hpp"

namespace gomamayo{

    // MeCab の文字型は基本的に char
    namespace mecab{

        // MeCab 関連処理限定の例外
        class MeCabException : public std::exception{
            public:
                MeCabException(const MeCab::Tagger*);
                inline const char* what() const noexcept{
                    return message;
                }
            private:
                const char* message;
        };

        // 文章を生の文字列で受けて MeCab で形態素解析し、Text インスタンスにして返す
        Text<wchar_t> parseText(const std::string&);

        // MeCab の解析で得た品詞の文字列を POS にする
        POS toPOS(const std::string&);

    }
}
