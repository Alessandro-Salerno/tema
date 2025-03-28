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
#include <iostream>
#include <louvre/api.hpp>
#include <string>
#include <tema/emit.hpp>
#include <tema/format.hpp>
#include <variant>

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
    std::string child_prefix;
    bool        prefix_new_line    = false;
    bool        postfix_new_line   = false;
    Formatter  *children_formatter = &formatter;

    switch (std::get<louvre::StandardNodeType>(root->type())) {
    case louvre::StandardNodeType::Center:
        children_formatter = &CenterFormatter::get_instance();
        postfix_new_line   = true;
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
        indent           = this->indent_width();
        prefix_new_line  = true;
        postfix_new_line = true;
        break;

    case louvre::StandardNodeType::Item:
        child_prefix        = "-  ";
        indent              = 3;
        indent_ignore_lines = 1;
        postfix_new_line    = true;
        break;

    default:
        break;
    }

    std::string buf;

    if (prefix_new_line && 0 != root->number()) {
        buf.append(EmitterSettings::get_instance().eol());
    }

    for (std::size_t i = 0; i < root->children().size(); i++) {
        auto child = root->children().at(i);

        std::string child_content = child_prefix;
        child_content.append(this->emit_recurisve(
            child, avail_width - indent, *children_formatter));
        buf.append(
            formatter.indent(child_content, indent, indent_ignore_lines));
    }

    if (postfix_new_line && *root->parent() &&
        root->number() < (*root->parent())->children().size() - 1) {
        buf.append(EmitterSettings::get_instance().eol());
    }

    return buf;
}

inline bool Emitter::can_ignore_prev_line_break(
    std::shared_ptr<louvre::Node> prev_child) const {
    return std::holds_alternative<louvre::StandardNodeType>(
               prev_child->type()) &&
           louvre::StandardNodeType::LineBreak ==
               std::get<louvre::StandardNodeType>(prev_child->type());
}
} // namespace tema
