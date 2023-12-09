/* gomamayo - Gomamayo Analyzer
 * Copyright: JJ1LIS (Katasuiron) 2023.
 *
 * This software can be used, modified and redistributed under the MIT License.
 * See also gomamayo/LICENSE.
 */

#pragma once

#include <string>
#include <vector>

#include "core.hpp"

namespace gomamayo{

    // text が表す文章から n 次ゴママヨを探す
    template<class charType, class traits = std::char_traits<charType>, class Allocator = std::allocator<charType>>
        std::vector<typename std::vector<Word<charType>>::size_type>
            judgeGomamayo(Text<charType> text, typename std::basic_string<charType>::size_type n = 1){

                using String = std::basic_string<charType>;

                // ゴママヨが見つかった単語のインデックス（前側）
                std::vector<typename std::vector<Word<charType>>::size_type> gomamayoWordIndexes;
            
                // i = 0...(size - 1) について、i 番目と i + 1 番目の単語でゴママヨを探す
                for(typename std::vector<Word<charType>>::size_type i = 0; i < text.size() - 1; i++){

                    // i 番目の単語の末尾 n モーラ
                    String now  = text[i].getMoraTail(n);
                    // i + 1 番目の単語の先頭 n モーラ
                    String next = text[i + 1].getMoraHead(n);

                    // now と next が文字列として等しい <=> ゴママヨ発見
                    if(now.compare(next) == 0)
                        gomamayoWordIndexes.push_back(i);
                }
             
            return gomamayoWordIndexes;
        }
}
