/* gomamayo - Gomamayo Analyzer
 * Copyright: JJ1LIS (Katasuiron) 2023.
 *
 * This software can be used, modified and redistributed under the MIT License.
 * See also gomamayo/LICENSE.
 */

#include <iostream>
#include <cstring>
#include <mecab.h>
#include <string>
#include <cstdlib>
#include "mecab.hpp"
#include "../core.hpp"
#include "../utils.hpp"

//debug
using namespace std;

namespace gomamayo{

    namespace mecab{

        MeCabException::MeCabException(const MeCab::Tagger* tagger){
            message = (tagger == NULL) ? MeCab::getTaggerError() : tagger->what();
        }

        // text を形態素解析して Text インスタンスでラップして返す
        Text<char> parseText(const std::string& text){

            try{
                // MeCab パーサを構築する
                MeCab::Tagger* tagger = MeCab::createTagger("");
                if(tagger == NULL)
                    throw new MeCabException(tagger);

                // text の形態素解析を実行
                // Node は形態素を表す構造体
                // Node* Node::next が次の形態素を指している
                const MeCab::Node* node = tagger->parseToNode(text.c_str());
                if(node == NULL)
                    throw new MeCabException(tagger);

                auto words = std::vector<Word<char>>();    // std::string == std::basic_string<char>


                // 形態素ノードを順番に舐める
                while(node != NULL){
                    // 始点終点ノードは除く
                    if(node->stat != MECAB_BOS_NODE && node->stat != MECAB_EOS_NODE){
                        // MeCab の出力はchar*文字列で node->feature に格納されており、
                        // 各項目は ',' で区切られているので vector にする

                        std::vector<std::string> splitted = split<char>(std::string(node->feature), ",");

                        // 単語は node-> surface にある
                        auto word = std::string(node->surface, node->length);

                        // 読みは node->feature の8番目の項目
                        // ただしカタカナの場合は node->feature は7番目までしか出力されないので、その場合は word そのものを読みとする
                        std::string reading;
                        if(splitted.size() <= 7) {
                            reading = word;
                        } else {
                            reading = splitted[7];
                        }

                        // 品詞（大分類）は node->feature の1番目の項目
                        POS pos = toPOS(splitted[0]);

                        // これらから Word<char> インスタンスを作って追加
                        words.push_back(Word<char>(std::string(node->surface, node->length), reading, pos));
                    }

                    node = node->next;
                }

                return Text<char>(words);

            } catch(MeCabException e){
                std::cerr << "Exception: " << e.what() << std::endl;
                exit(-1);
            }
        }


        POS toPOS(const std::string& str){
            if(!str.compare("その他"))
                return other;
            else if(!str.compare("フィラー"))
                return filler;
            else if(!str.compare("感動詞"))
                return interject;
            else if(!str.compare("記号"))
                return symbol;
            else if(!str.compare("形容詞"))
                return adject;
            else if(!str.compare("助詞"))
                return particle;
            else if(!str.compare("助動詞"))
                return auxiVerb;
            else if(!str.compare("接続詞"))
                return conjunct;
            else if(!str.compare("接頭詞"))
                return prefix;
            else if(!str.compare("動詞"))
                return verb;
            else if(!str.compare("副詞"))
                return adverb;
            else if(!str.compare("名詞"))
                return noun;
            else if(!str.compare("連体詞"))
                return rentai;
            else
                return unknown;
        }
    }
}
