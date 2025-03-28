/* Copyright 2025 Alessandro Salerno
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#pragma once

#include <cstddef>
#include <optional>
#include <string>
namespace tema {
class Splitter {
    private:
    const std::string &mText;
    std::size_t         mPos;
    std::size_t         mLinePos;

    public:
    Splitter(const std::string &text) : mText(text), mPos(0), mLinePos(0) {};

    std::pair<std::size_t, std::optional<std::string>> next_word();
    void                                                reset_line();
    bool                                                words_left();

    private:
    bool    can_advance() const;
    void    advance();
    wchar_t peek() const;
    wchar_t consume();
    void    skip_whitespace();
};
} // namespace tema
