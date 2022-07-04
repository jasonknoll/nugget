/*

MIT License

Copyright (c) 2022 PCSX-Redux authors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#pragma once

template <size_t Fragments>
class psyqo::Font : public psyqo::FontBase {
  public:
    virtual ~Font() {}

  private:
    virtual GlyphsFragment& getGlyphFragment(bool increment) override {
        auto& fragment = m_fragments[m_index];
        if (increment) {
            if (++m_index == Fragments) {
                m_index = 0;
            }
        }
        return fragment;
    }
    virtual void forEach(eastl::function<void(GlyphsFragment&)>&& cb) override {
        for (auto& fragment : m_fragments) {
            cb(fragment);
        }
    }
    eastl::array<GlyphsFragment, Fragments> m_fragments;
    unsigned m_index = 0;
};