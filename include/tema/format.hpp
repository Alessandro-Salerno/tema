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
#include <cstdio>
#include <sstream>
#include <string>
#include <tema/split.hpp>
#include <tema/util.hpp>

namespace tema {
class Indenter {
    public:
    virtual std::wstring indent(const std::wstring text,
                                std::size_t        indent_width,
                                std::size_t        ignore_before_line = 0) = 0;

    protected:
    std::wstring ignored_before_line(std::wstringstream &text_stream,
                                     std::size_t         num_lines) const;
};

class NullIndenter : public Singleton<NullIndenter>, public Indenter {
    friend class Singleton<NullIndenter>;

    public:
    std::wstring indent(const std::wstring text,
                        std::size_t        indent_width,
                        std::size_t        ignore_before_line = 0) override {
        return text;
    }
};

class LeftIndenter : public Singleton<LeftIndenter>, public Indenter {
    friend class Singleton<LeftIndenter>;

    public:
    std::wstring indent(const std::wstring text,
                        std::size_t        indent_width,
                        std::size_t        ignore_before_line = -1) override;
};

class RightIndenter : public Singleton<RightIndenter>, public Indenter {
    friend class Singleton<RightIndenter>;

    public:
    std::wstring indent(const std::wstring text,
                        std::size_t        indent_width,
                        std::size_t        ignore_before_line = 0) override;
};

class Formatter {
    private:
    Indenter &mIndenter;

    public:
    Formatter(Indenter &indenter = NullIndenter::get_instance())
        : mIndenter(indenter) {};

    virtual std::wstring format(const std::wstring text,
                                std::size_t        max_line_width) = 0;

    std::wstring indent(const std::wstring text,
                        std::size_t        indent_width,
                        std::size_t        ignore_before_line = 0) {
        return this->mIndenter.indent(text, indent_width, ignore_before_line);
    }
};

class LeftFormatter : public Singleton<LeftFormatter>, public Formatter {
    friend class Singleton<LeftFormatter>;
    LeftFormatter() : Formatter(LeftIndenter::get_instance()) {};
    ~LeftFormatter() = default;

    std::wstring format(const std::wstring text,
                        std::size_t        max_line_width) override;
};

class CenterFormatter : public Singleton<CenterFormatter>, public Formatter {
    friend class Singleton<CenterFormatter>;

    std::wstring format(const std::wstring text,
                        std::size_t        max_line_width) override;
};

class RightFormatter : public Singleton<RightFormatter>, public Formatter {
    friend class Singleton<RightFormatter>;

    std::wstring format(const std::wstring text,
                        std::size_t        max_line_width) override;
};

class JustifyFormatter : public Singleton<JustifyFormatter>, public Formatter {
    friend class Singleton<JustifyFormatter>;

    std::wstring format(const std::wstring text,
                        std::size_t        max_line_width) override;
};
} // namespace tema
