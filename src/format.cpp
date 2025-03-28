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
#include <cwchar>
#include <sstream>
#include <string>
#include <tema/emit.hpp>
#include <tema/format.hpp>
#include <tema/split.hpp>
#include <tuple>

namespace tema {
std::string Indenter::ignored_before_line(std::stringstream &text_stream,
                                           std::size_t num_lines) const {
    std::string buf;

    for (std::size_t i = 0; i < num_lines; i++) {
        std::string line1;

        if (std::getline(text_stream, line1)) {
            if (0 != i) {
                buf.append(EmitterSettings::get_instance().eol());
            }

            buf.append(line1);
            continue;
        }

        break;
    }

    return buf;
}

std::string LeftIndenter::indent(const std::string text,
                                  std::size_t        indent_width,
                                  std::size_t        ignore_before_line) {
    if (0 == indent_width) {
        return text;
    }

    std::string spaces(indent_width, ' ');
    std::string buf;

    std::stringstream stream(text);
    std::string       line;
    std::string       next_line;

    if (0 != ignore_before_line) {
        buf.append(this->ignored_before_line(stream, ignore_before_line));
        next_line = EmitterSettings::get_instance().eol();
    }

    while (std::getline(stream, line)) {
        if (!next_line.empty()) {
            buf.append(spaces);
            buf.append(next_line);
            buf.append(EmitterSettings::get_instance().eol());
            next_line.clear();
        }

        buf.append(spaces);

        if (std::getline(stream, next_line)) {
            buf.append(line);
            buf.append(EmitterSettings::get_instance().eol());
        } else {
            buf.append(line);
        }
    }

    if (!next_line.empty()) {
        buf.append(spaces);
        buf.append(next_line);
    }

    return buf;
}

std::string RightIndenter::indent(const std::string text,
                                   std::size_t        indent_width,
                                   std::size_t        ignore_before_line) {
    if (0 == indent_width) {
        return text;
    }

    std::string spaces(indent_width, ' ');
    std::string buf;

    std::stringstream stream(text);
    std::string       line;
    std::string       next_line;

    if (0 != ignore_before_line) {
        buf.append(this->ignored_before_line(stream, ignore_before_line));
        next_line = EmitterSettings::get_instance().eol();
    }

    while (std::getline(stream, line)) {
        if (!next_line.empty()) {
            buf.append(next_line);
            buf.append(spaces);
            buf.append(EmitterSettings::get_instance().eol());
            next_line.clear();
        }

        if (std::getline(stream, next_line)) {
            buf.append(line);
            buf.append(EmitterSettings::get_instance().eol());
        } else {
            buf.append(line);
        }

        buf.append(spaces);
    }

    if (!next_line.empty()) {
        buf.append(next_line);
        buf.append(spaces);
    }

    return buf;
}

std::string LeftFormatter::format(const std::string text,
                                   std::size_t        max_line_width) {
    auto         splitter  = Splitter(text);
    std::size_t  space_off = 0;
    std::string buf;

    while (true) {
        auto [start_pos, word_opt] = splitter.next_word();

        if (!word_opt) {
            break;
        }

        std::string word = *word_opt;
        std::size_t  rem =
            max_line_width - start_pos - space_off - word.length();

        // TODO: Handle case in which word is longer than line

        if (start_pos + space_off + word.length() > max_line_width) {
            buf.append(EmitterSettings::get_instance().eol());
            splitter.reset_line();
            rem = max_line_width - word.length();
        }

        buf.append(word);

        if (rem >= 1) {
            buf.push_back(' ');
            space_off++;
        }
    }

    return buf;
}

std::string CenterFormatter::format(const std::string text,
                                     std::size_t        max_line_width) {
    auto         splitter = Splitter(text);
    std::string buf;
    std::string line;

    while (true) {
        auto [start_pos, word_opt] = splitter.next_word();

        if (!word_opt) {
            std::size_t edges = max_line_width - line.length();
            std::size_t left  = edges / 2;

            buf.append(std::string(left, ' '));
            buf.append(line);
            break;
        }

        std::string word = *word_opt;
        std::size_t  rem  = max_line_width - start_pos - word.length();

        // TODO: Handle case in which word is longer than line

        if (start_pos + word.length() > max_line_width) {
            std::size_t edges = max_line_width - line.length();
            std::size_t left  = edges / 2;

            buf.append(std::string(left, ' '));
            buf.append(line);
            buf.append(EmitterSettings::get_instance().eol());
            line.clear();

            splitter.reset_line();
            rem = max_line_width - word.length();
        }

        line.append(word);

        if (rem >= 1) {
            line.push_back(' ');
        }
    }

    return buf;
}
} // namespace tema
