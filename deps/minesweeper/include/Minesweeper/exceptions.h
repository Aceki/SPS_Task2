#pragma once

#include <exception>

namespace Minesweeper
{
    class OutOfBounds : public std::exception
    {
    public:
        explicit OutOfBounds(const char* what = "Coordinates should be in field bounds.") 
            : m_what(what) { }
        const char* what() const noexcept;
    private:
        const char* m_what;
    };

    inline const char* OutOfBounds::what() const noexcept
    {
        return m_what;
    }

    class RangeError : public std::exception
    {
    public:
        explicit RangeError(const char* what) : m_what(what) { }
        const char* what() const noexcept;
    private:
        const char* m_what;
    };

    inline const char* RangeError::what() const noexcept
    {
        return m_what;
    }

    class LogicError : public std::exception
    {
    public:
        explicit LogicError(const char* what) : m_what(what) { }
        const char* what() const noexcept;
    private:
        const char* m_what;
    };

    inline const char* LogicError::what() const noexcept
    {
        return m_what;
    }
}

