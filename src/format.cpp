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
#include <string>
#include <tema/format.hpp>
#include <tema/split.hpp>

namespace tema {
std::wstring LeftIndenter::indent(const std::wstring text,
                                  std::size_t        indent_width) {
    // TODO: actually indent things
    return text;
}

std::wstring LeftFormatter::format(const std::wstring text,
                                   std::size_t        max_line_width) {
    auto         splitter = Splitter(text);
    std::wstring buf;

    while (true) {
        auto [start_pos, word_opt] = splitter.next_word();

        if (!word_opt) {
            break;
        }

        std::wstring word = *word_opt;
        std::size_t  rem  = max_line_width - start_pos - word.length();

        // TODO: Handle case in which word is longer than line

        if (start_pos + word.length() > max_line_width) {
            buf.append(L"\r\n");
            splitter.reset_line();
            rem = max_line_width - word.length();
        }

        buf.append(word);

        if (rem >= 1) {
            buf.push_back(' ');
        }
    }

    return buf;
}
} // namespace tema
