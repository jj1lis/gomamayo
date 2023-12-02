/* gomamayo - Gomamayo Analyzer
 * Copyright: JJ1LIS (Katasuiron) 2023.
 *
 * This software can be used, modified and redistributed under the MIT License.
 * See also gomamayo/LICENSE.
 */

#pragma once

#include "core.hpp"

namespace gomamayo{

    // text が表す文章からn次ゴママヨを探す
    // n == 0 の場合は無制限に探す
    template<class charType, class traits = std::char_traits<charType>, class Allocator = std::allocator<charType>>
        auto /* TODO write return type*/
            judgeGomamayo(Text<charType> text, std::basic_string<charType>::size_type n = 0){
            
                // i = 0...(size - 1) について、i番目とi+1番目の単語でゴママヨを探す
                for(std::vector<Word<charType>>::size_type i = 0; i < text.size() - 1; i++){
                    //TODO 
                }
             

        }
}
