#include "cell.h"

Minesweeper::Cell::Cell(int i, int j, int value, bool mined)
    : m_i(i), m_j(j), m_value(value), m_mined(mined)
{ }

void Minesweeper::Cell::setMarker(Marker marker) 
{
    if (m_covered)
    {
        m_marker = marker;
    }
}

void Minesweeper::Cell::uncover()
{
    m_covered = false;
}
