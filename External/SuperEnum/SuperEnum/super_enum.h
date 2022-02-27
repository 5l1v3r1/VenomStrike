/****************************************************************************
**
** The MIT License
** SPDX short identifier: MIT
**
** Copyright 2017 Dmitry Bravikov (email: dmitry@bravikov.pro)
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and associated documentation files (the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and/or sell copies of the Software, and to permit persons to whom the
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
** DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

#pragma once
#ifndef SUPER_ENUM_H_20171221_143544
#define SUPER_ENUM_H_20171221_143544

#include <map>
#include <cassert>

template<typename T, typename E>
class SuperEnum
{
public:
    SuperEnum();
    explicit SuperEnum(const E& value);
    virtual ~SuperEnum();

    operator E() const;

    static const SuperEnum<T, E>* object(const E& value);

    static E size() { return getArchive().size(); }

private:
    const E m_value;

    static E m_freeValue;

    typedef std::map<E, const SuperEnum<T, E>*> Container;

    static Container& getArchive()
    {
        static Container archive;
        return archive;
    }

    SuperEnum(const SuperEnum& other);
    SuperEnum& operator=(const SuperEnum& other);
};

template<typename T, typename E>
E SuperEnum<T, E>::m_freeValue = 0;

template<typename T, typename E>
SuperEnum<T, E>::SuperEnum() :
    m_value(m_freeValue++)
{
    getArchive()[m_value] = this;
}

template<typename T, typename E>
SuperEnum<T, E>::SuperEnum(const E& value) :
    m_value(value)
{
    assert(getArchive().find(m_value) == getArchive().end());

    if (getArchive().empty()) {
        m_freeValue = m_value + 1;
    }
    else {
        if (m_freeValue <= m_value) {
            m_freeValue = m_value + 1;
        }
    }

    getArchive()[m_value] = this;
}

template<typename T, typename E>
SuperEnum<T, E>::~SuperEnum()
{
    getArchive().erase(m_value);

    if (getArchive().empty()) {
        m_freeValue = 0;
        return;
    }

    m_freeValue = getArchive().rbegin()->first + 1;
}

template<typename T, typename E>
const SuperEnum<T, E>* SuperEnum<T, E>::object(const E& value)
{
    typename Container::iterator iterator = getArchive().find(value);

    if (iterator == getArchive().end()) {
        return 0;
    }

    return iterator->second;
}

template<typename T, typename E>
SuperEnum<T, E>::operator E() const
{
    return m_value;
}

#endif /* #ifndef SUPER_ENUM_H_20171221_143544 */