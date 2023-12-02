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

    // 文字列 source を separator で分割して vector にして返す
    template<class charType, class traits = std::char_traits<charType>, class Allocator = std::allocator<charType>>
        std::vector<std::basic_string<charType>>
        split(const std::basic_string<charType>& source, const std::basic_string<charType>& separator){

            using String = std::basic_string<charType>;
            auto list = std::vector<String>();

            // separator が空ならそのまま
            if(separator.length() == 0)
                list.push_back(source);
            else{
                typename String::size_type head = 0;   // list に追加する文字列の先頭位置

                for(;;){
                    typename String::size_type position = source.find(separator, head);    // 今回見つけた separator の位置

                    // これ以上 sperator がなくなったら残りを全て追加して終了
                    if(position == String::npos){
                        list.push_back(source.substr(head));
                        break;
                    }

                    // separator が見つかった場合、 前回見つけた separator の直後から今回見つけた separator の直前まで list に追加
                    list.push_back(source.substr(head, position - head));
                    // 先頭位置を今回見つけた separator の直後に更新
                    head = position + separator.length();
                }
            }

            return list;
        }

    // 捨て仮名判定
    template<class charType, class traits = std::char_traits<charType>, class Allocator = std::allocator<charType>>
        bool isSutegana(const std::basic_string<charType>& kana){

            if(!kana.compare("ャ"))
                return true;
            else if(!kana.compare("ュ"))
                return true;
            else if(!kana.compare("ョ"))
                return true;
            else if(!kana.compare("ァ"))
                return true;
            else if(!kana.compare("ィ"))
                return true;
            else if(!kana.compare("ゥ"))
                return true;
            else if(!kana.compare("ェ"))
                return true;
            else if(!kana.compare("ォ"))
                return true;
            else
                return false;
        }

    // 読みの列をモーラごとに分割して vector で返す
    template<class charType, class traits = std::char_traits<charType>, class Allocator = std::allocator<charType>>
        std::vector<std::basic_string<charType>> splitMora(const std::basic_string<charType>& reading){

            using String = std::basic_string<charType>;
            auto moras = std::vector<String>();

            for(typename String::size_type cursor = 0; cursor < reading.size(); cursor++){
                // 1文字先読みして、捨て仮名だったら cursor と cursor + 1 で1モーラ
                if(cursor + 1 < reading.length() && isSutegana(reading.substr(cursor + 1, 1))){
                    moras.push_back(reading.substr(cursor, 2));
                    cursor++;       // for 文のインクリメントと併せて次のループでは捨て仮名の次の文字を読む
                } else  // 普通は1文字1モーラ
                    moras.push_back(reading.substr(cursor, 1));
            }

            return moras;
        }

}
