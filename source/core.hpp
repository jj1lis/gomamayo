/* gomamayo - Gomamayo Analyzer
 * Copyright: JJ1LIS (Katasuiron) 2023.
 *
 * This software can be used, modified and redistributed under the MIT License.
 * See also gomamayo/LICENSE.
 */

#pragma once
#include <string>
#include <vector>
#include <numeric>
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
            Word(String _word, String _reading, POS _pos) :
                word(_word), reading(_reading), moras(splitMora(_reading)), pos(_pos) {}

            // getter
            POS                         getPos()        const { return pos; }
            const String&               getWord()       const { return &word; }
            const String&               getReading()    const { return &reading; }
            const std::vector<String>&  getMoras()      const { return &moras; }

            // モーラのサイズを取得する
            typename std::vector<String>::size_type getMoraSize() const {
                return moras.size();
            }

            // 読みの先頭 length モーラを取得する
            String getMoraHead(typename String::size_type length) const {
                // length がモーラ数より大きければ例外を投げる
                if(length > moras.size()) {
                    // TODO 投げる例外クラスを作る
                } 

                // 先頭から length モーラを結合して返す
                return std::accumulate(moras.begin(), moras.begin() + length, String());
            }

            // 読みの末尾 length モーラを取得する
            String getMoraTail(typename String::size_type length) const {
                // length がモーラ数より大きければ例外を投げる
                if(length > moras.size()) {
                    // TODO 投げる例外クラスを作る
                } 

                // 先頭から length モーラを結合して返す
                return std::accumulate(moras.end() - length, moras.end(), String());
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
            Text(typename std::vector<CWord> words) : words(words) {}

            // getter
            const std::vector<CWord>& getWords() const { return &words; }

            // 含まれる単語のサイズを取得する
            typename std::vector<CWord>::size_type size() const { return words.size(); }

            // i 番目の単語への const 参照を直接投げる
            const CWord& at(typename std::vector<CWord>::size_type i) const {
                return words[i];
            }
            
            // at の operator overload 版
            const CWord& operator[](typename std::vector<CWord>::size_type i) const {
                return words[i];
            }

            private:
            const std::vector<CWord> words;    // 単語の配列（元の文章の出現順に保持）
        };

}
