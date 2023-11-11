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

    template<class charType, class traits = std::char_traits<charType>, class Allocator = std::allocator<charType>>
        auto split(const std::basic_string<charType>& source, const std::basic_string<charType>& separator){
            auto list = new std::vector<std::basic_string<charType>>();

            if(separator.length() == 0)
                list->push_back(source);
            else{
                auto offset = static_cast<typename std::basic_string<charType>::size_type>(0);

                for(;;){
                    auto position = source.find(separator, offset);

                    if(position == std::basic_string<charType>::npos){
                        list->push_back(source.substr(offset));
                        break;
                    }

                    list->push_back(source.substr(offset, position - offset));
                    offset = position + separator.length();
                }
            }

            return list;
    }
}
