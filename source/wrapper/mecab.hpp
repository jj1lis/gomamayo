/* gomamayo - Gomamayo Analyzer
 * Copyright: JJ1LIS (Katasuiron) 2023.
 *
 * This software can be used, modified and redistributed under the MIT License.
 * See also gomamayo/LICENSE.
 */

#pragma once

#include <exception>
#include <mecab.h>
#include "../core.hpp"

namespace gomamayo{

    namespace mecab{

        class MeCabException : public std::exception{
            public:
                MeCabException(const MeCab::Tagger*);
                inline const char* what() const noexcept{
                    return message;
                }
            private:
                const char* message;
        };

        Text<char>* parseText(const char*);

        POS toPOS(const std::string);

    }
}
