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
#include <cwchar>
#include <louvre/api.hpp>
#include <tema/format.hpp>

namespace tema {
class Emitter {
    private:
    const std::size_t mMaxLineWidth;
    const std::size_t mBorderWidth;
    const std::size_t mIndentWidth;
    Formatter        &mFormatter;

    public:
    Emitter(std::size_t max_line_width,
            std::size_t border_width,
            std::size_t indent_width)
        : mMaxLineWidth(max_line_width), mBorderWidth(border_width),
          mIndentWidth(indent_width),
          mFormatter(LeftFormatter::get_instance()) {};

    std::wstring emit(std::shared_ptr<louvre::Node> root);
    std::wstring emit_recurisve(std::shared_ptr<louvre::Node> root,
                                std::size_t                   avail_width);

    inline std::size_t max_line_width() const {
        return this->mMaxLineWidth;
    }

    inline std::size_t border_width() const {
        return this->mBorderWidth;
    }

    inline std::size_t indent_width() const {
        return this->mIndentWidth;
    }
};
} // namespace tema
