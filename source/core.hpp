/* gomamayo - Gomamayo Analyzer
 * Copyright: JJ1LIS (Katasuiron) 2023.
 *
 * This software can be used, modified and redistributed under the MIT License.
 * See also gomamayo/LICENSE.
 */

#pragma once
#include <string>
#include <vector>

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
            Word(String word, String reading, POS pos) : word(word), reading(reading), pos(pos) {}

            POS      getpos()       const { return pos; }
            String*  getword()      const { return word; }
            String*  getreading()   const { return reading; }

            private:
            const String word;                  // 単語（元の表現）
            const String reading;               // word の読み（カタカナ）
            const std::vector<String> moras;    // reading のモーラ分割
            const POS pos;                      // 品詞
        };


    // 文章クラス
    template<class charType, class traits = std::char_traits<charType>, class Allocator = std::allocator<charType>>
        class Text{
            using String = std::basic_string<charType>;

            public:
            Text(std::vector<Word<charType>> words) : words(words) {}

            std::vector<Word<charType>> getords() { return &words; }

            private:
            const std::vector<Word<charType>> words;    // 単語の配列（元の文章の出現順に保持）
        };

}
