/* gomamayo - Gomamayo Analyzer
 * Copyright: JJ1LIS (Katasuiron) 2023.
 *
 * This software can be used, modified and redistributed under the MIT License.
 * See also gomamayo/LICENSE.
 */

#pragma once
#include <string>
#include <vector>
#include "utils.hpp"

namespace gomamayo{

    // POS: Parts of Speech
    // 品詞判別用の列挙型
    enum POS{
        other,      // その他
        filler,     // フィラー
        interject,  // 感動詞
        symbol,     // 記号
        adject,     // 形容詞
        particle,   // 助詞
        auxiVerb,   // 助動詞
        conjunct,   // 接続詞
        prefix,     // 接頭詞
        verb,       // 動詞
        adverb,     // 副詞
        noun,       // 名詞
        rentai,     // 連体詞
        unknown,
    };

    
    // 単語（形態素）クラス
    template<class charType, class traits = std::char_traits<charType>, class Allocator = std::allocator<charType>>
        class Word{
            using String = std::basic_string<charType>;

            public:
            Word(String word, String reading, POS pos) : word(word), reading(reading), moras(splitMora(reading)), pos(pos) {}

            // getter
            POS                 getPos()        const { return pos; }
            String              getWord()       const { return word; }
            String              getReading()    const { return reading; }
            std::vector<String> getMoras()      const { return moras; }

            std::vector<String>::size_type getMoraSize() const {
                return moras.size();
            }

            private:
            const String word;                  // 単語（元の表現）
            const String reading;               // word の読み（カタカナ）
            const POS pos;                      // 品詞
            const std::vector<String> moras;    // reading のモーラ分割
        };


    // 文章クラス
    template<class charType, class traits = std::char_traits<charType>, class Allocator = std::allocator<charType>>
        class Text{
            using String    = std::basic_string<charType>;
            using CWord     = Word<charType>;

            public:
            Text(std::vector<CWord> words) : words(words) {}

            std::vector<CWord> getWords()           const { return words; }
            std::vector<CWord>::size_type size()    const { return words.size(); }

            private:
            const std::vector<CWord> words;    // 単語の配列（元の文章の出現順に保持）
        };

}
