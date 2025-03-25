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
    return this->emit_recurisve(
        root, this->max_line_width() - this->border_width() * 2);
}

std::wstring Emitter::emit_recurisve(std::shared_ptr<louvre::Node> root,
                                     std::size_t avail_width) {
    switch (std::get<louvre::StandardNodeType>(root->type())) {
    case louvre::StandardNodeType::Left:
        this->mFormatter = LeftFormatter::get_instance();
        break;

    default:
        break;
    }

    // TODO: implement this
    return nullptr;
}
} // namespace tema
