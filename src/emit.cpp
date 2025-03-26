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

#include <louvre/api.hpp>
#include <tema/emit.hpp>
#include <tema/format.hpp>

namespace tema {
std::wstring Emitter::emit(std::shared_ptr<louvre::Node> root) {
    return LeftIndenter::get_instance().indent(
        this->emit_recurisve(root,
                             this->max_line_width() - this->border_width() * 2,
                             LeftFormatter::get_instance()),
        this->border_width());
}

std::wstring Emitter::emit_recurisve(std::shared_ptr<louvre::Node> root,
                                     std::size_t                   avail_width,
                                     Formatter                    &formatter) {
    std::size_t indent = 0;

    switch (std::get<louvre::StandardNodeType>(root->type())) {
    case louvre::StandardNodeType::Left:
        break;

    case louvre::StandardNodeType::Center:
        break;

    case louvre::StandardNodeType::Right:
        break;

    case louvre::StandardNodeType::Justify:
        break;

    case louvre::StandardNodeType::LineBreak:
        return L"\r\n";

    case louvre::StandardNodeType::Text:
        return formatter.format(*root->text(), avail_width);

    case louvre::StandardNodeType::Paragraph:
        indent = this->indent_width();
        break;

    default:
        break;
    }

    std::wstring buf;
    for (auto &child : root->children()) {
        buf.append(formatter.indent(
            this->emit_recurisve(child, avail_width - indent, formatter),
            indent));
        buf.append(L"\r\n"); // TODO: no new line on last child
    }

    return buf;
}
} // namespace tema
