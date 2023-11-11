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

namespace gomamayo{

    namespace mecab{

        MeCabException::MeCabException(const MeCab::Tagger* tagger){
            message = (tagger == NULL) ? MeCab::getTaggerError() : tagger->what();
        }

        Text<char>* parseText(const char *text){
            try{
                MeCab::Tagger *tagger = MeCab::createTagger("");
                if(tagger == NULL)
                    throw new MeCabException(tagger);

                const MeCab::Node* node = tagger->parseToNode(text);
                if(node == NULL)
                    throw new MeCabException(tagger);

                auto words = new std::vector<Word<char>*>();    // std::string == std::basic_string<char>
                while(node != NULL){
                    { //test
                        #include <iostream>
                        //std::cout << std::string(node->surface, node->length) << " : " << node->feature << std::endl;
                    }

                    if(node->stat != MECAB_BOS_NODE && node->stat != MECAB_EOS_NODE){
                        auto splitted = split<char>(node->feature, ",");

                        words->push_back(new Word<char>(new std::string(node->surface, node->length), &(splitted->at(6)), toPOS(splitted->at(0))));
                    }

                    node = node->next;
                }

                return new Text<char>(words);

            } catch(MeCabException e){
                std::cerr << "Exception: " << e.what() << std::endl;
                exit(-1);
            }
        }

        POS toPOS(const std::string str){
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
