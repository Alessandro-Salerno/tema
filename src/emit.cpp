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
#include <louvre/api.hpp>
#include <string>
#include <tema/emit.hpp>
#include <tema/format.hpp>

namespace tema {
std::string Emitter::emit(std::shared_ptr<louvre::Node> root) {
    return LeftIndenter::get_instance().indent(
        this->emit_recurisve(root,
                             this->max_line_width() - this->border_width() * 2,
                             LeftFormatter::get_instance()),
        this->border_width());
}

std::string Emitter::emit_recurisve(std::shared_ptr<louvre::Node> root,
                                    std::size_t                   avail_width,
                                    Formatter                    &formatter) {
    std::size_t indent              = 0;
    std::size_t indent_ignore_lines = 0;
    std::string prefix;
    Formatter  *children_formatter = &formatter;

    switch (std::get<louvre::StandardNodeType>(root->type())) {
    case louvre::StandardNodeType::Left:
        children_formatter = &LeftFormatter::get_instance();
        break;

    case louvre::StandardNodeType::Center:
        children_formatter = &CenterFormatter::get_instance();
        break;

    case louvre::StandardNodeType::Right:
        break;

    case louvre::StandardNodeType::Justify:
        break;

    case louvre::StandardNodeType::LineBreak:
        return EmitterSettings::get_instance().eol();

    case louvre::StandardNodeType::Text:
        return formatter.format(*root->text(), avail_width);

    case louvre::StandardNodeType::Paragraph:
    case louvre::StandardNodeType::Bullets:
    case louvre::StandardNodeType::Numebrs:
        indent = this->indent_width();
        break;

    case louvre::StandardNodeType::Item:
        prefix              = "-  ";
        indent              = 3;
        indent_ignore_lines = 1;
        break;

    default:
        break;
    }

    std::string buf;
    for (std::size_t i = 0; i < root->children().size(); i++) {
        auto child = root->children().at(i);

        // Print leading new line when separating blocks
        if (0 != i && !child->children().empty()) {
            buf.append(EmitterSettings::get_instance().eol());
        }

        std::string child_content = prefix;
        child_content.append(this->emit_recurisve(
            child, avail_width - indent, *children_formatter));
        buf.append(
            formatter.indent(child_content, indent, indent_ignore_lines));

        // Print trailing new line when separating blcks
        if (i != root->children().size() - 1 && !child->children().empty()) {
            buf.append(EmitterSettings::get_instance().eol());
        }
    }

    return buf;
}
} // namespace tema
