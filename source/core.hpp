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

    template<class charType, class traits = std::char_traits<charType>, class Allocator = std::allocator<charType>>
        class Word{
            using String = std::basic_string<charType>;

            public:
            Word(String* word, String* reading, POS pos) : word(word), reading(reading), pos(pos) {}

            ~Word(){
                delete word;
                delete reading;
            }

            inline POS      getpos()        { return pos; }
            inline String*  getword()       { return word; }
            inline String*  getreading()    { return reading; }

            private:
            String* const word;
            String* const reading;
            const POS pos;
        };

    template<class charType, class traits = std::char_traits<charType>, class Allocator = std::allocator<charType>>
        class Text{
            using String = std::basic_string<charType>;

            public:
            Text(std::vector<Word<charType>*>* words) : words(words) {}

            ~Text(){
                for(auto word : *words)
                    delete word;

                delete words;
            }

            inline std::vector<Word<charType>*>* getwords() { return words; }

            private:
            std::vector<Word<charType>*>* const words;
        };

}
