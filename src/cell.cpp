#include "cell.h"

Cell::Cell(QWidget* parent) : QPushButton(parent) { 
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

bool Cell::event(QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

        if ((mouseEvent->buttons() & Qt::LeftButton) 
         && (mouseEvent->buttons() & Qt::RightButton))
        {
            emit bothMouseButtonsClicked();

            return true;
        }
        else if (mouseEvent->button() == Qt::RightButton)
        {
            emit rightMouseButtonClicked();
            
            return true;
        }
        else if (mouseEvent->button() == Qt::LeftButton)
        {
            emit leftMouseButtonClicked();

            return true;
        }
    }
    else if (event->type() == QEvent::MouseButtonDblClick)
    {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

        if (mouseEvent->button() == Qt::LeftButton)
        {
            emit leftMouseButtonDoubleClicked();
            
            return true;
        }
    }

    return QPushButton::event(event);
}

