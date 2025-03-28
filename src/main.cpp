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

#include <fstream>
#include <iostream>
#include <louvre/api.hpp>
#include <string>
#include <tema/emit.hpp>
#include <variant>

int main(int argc, const char *const argv[]) {
    if (argc != 2) {
        std::cerr << "ERROR: Need exactly one argument: file path" << std::endl;
        return -1;
    }

    std::wifstream input(argv[1]);

    std::string source((std::istreambuf_iterator<wchar_t>(input)),
                        std::istreambuf_iterator<wchar_t>());

    auto parser = louvre::Parser(source);

    std::variant<std::shared_ptr<louvre::Node>,
                 louvre::SyntaxError,
                 louvre::TagError,
                 louvre::NodeError>
        parse_result = parser.parse();

    if (auto rootp =
            std::get_if<std::shared_ptr<louvre::Node>>(&parse_result)) {
        auto root = *rootp;
        tema::EmitterSettings::get_instance().set_eol("\n");
        tema::Emitter emitter(80, 4, 4);
        std::string  out = emitter.emit(root);
        std::wcout << out;
    }
}
