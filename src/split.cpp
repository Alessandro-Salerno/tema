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

#include <cstddef>
#include <cwctype>
#include <optional>
#include <string>
#include <tema/split.hpp>
#include <utility>

namespace tema {
std::pair<std::size_t, std::optional<std::string>> Splitter::next_word() {
    std::string buf;
    std::size_t  start_pos = this->mLinePos;

    if (!this->can_advance()) {
        return std::make_pair(start_pos, std::nullopt);
    }

    // Skip leading whitespace
    this->skip_whitespace();

    // Collect word
    while (this->can_advance() && ' ' != this->peek()) {
        buf.push_back(this->consume());
    }

    // Skip trailing whitespace
    this->skip_whitespace();

    if (0 == buf.length()) {
        return std::make_pair(start_pos, std::nullopt);
    }

    this->mLinePos += buf.length() + 1; // + 1 is for the space
    return std::make_pair(start_pos, buf);
}

void Splitter::reset_line() {
    this->mLinePos = 0;
}

bool Splitter::words_left() {
    // Skip whitespace jsut for sure (this may be called before next_word);
    this->skip_whitespace();
    return this->can_advance();
}

bool Splitter::can_advance() const {
    return this->mPos < this->mText.length();
}

void Splitter::advance() {
    this->mPos++;
}

wchar_t Splitter::peek() const {
    if (this->can_advance()) {
        return this->mText.at(this->mPos);
    }

    return '\0';
}

wchar_t Splitter::consume() {
    wchar_t c = this->peek();
    this->advance();
    return c;
}

void Splitter::skip_whitespace() {
    while (this->can_advance() && ' ' == this->peek()) {
        this->consume();
    }
}
} // namespace tema
