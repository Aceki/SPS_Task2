#include "exceptions.h"
#include "cell.h"

Minesweeper::Cell::Cell(int i, int j, int value, bool mined)
    : m_i(i), m_j(j), m_value(value), m_mined(mined)
{ }

void Minesweeper::Cell::switchMarker() 
{
    if (m_covered)
    {
        if (m_marker == None)
            m_marker = Flag;
        else if (m_marker == Flag)
            m_marker = Question;
        else
            m_marker = None;
    }
}

void Minesweeper::Cell::uncover()
{
    m_covered = false;
}
