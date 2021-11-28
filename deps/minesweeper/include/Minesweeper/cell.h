#pragma once

namespace Minesweeper
{
    class Cell
    {
    public:
        enum Marker 
        {
            None,
            Flag,
            Question
        };

        Cell(int i, int j, int value, bool mined);

        int i() const;
        int j() const;
        int value() const;
        Marker marker() const;
        bool isMined() const;
        bool isCovered() const;
        void switchMarker();
        void uncover();

    private:
        int m_i;
        int m_j;
        int m_value;
        bool m_mined;
        bool m_covered = true;
        Marker m_marker = None;
    };

    inline int Cell::i() const
    {
        return m_i;
    }

    inline int Cell::j() const
    {
        return m_j;
    }

    inline int Cell::value() const
    {
        return m_value;
    }

    inline Cell::Marker Cell::marker() const
    {
        return m_marker;
    }

    inline bool Cell::isMined() const
    {
        return m_mined;
    }

    inline bool Cell::isCovered() const
    {
        return m_covered;
    }
}
