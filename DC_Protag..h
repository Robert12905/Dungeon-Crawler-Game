#include <QGraphicsRectItem>
#include <QKeyEvent>

#ifndef DC_PROTAG_H
#define DC_PROTAG_H

class DC_Protag : public QGraphicsRectItem {
    public:
//refactoring to creat a key macro for game movement
    void keyPressEvent(QKeyEvent *event);
};
//definition of 'Key-Press-Event' to recognize proper movement by button presses as a header file

//refraction - A simplification of code without changing functionality
inline void DC_Protag::keyPressEvent(QKeyEvent *event) {
#include "DC_Protag..h"

//fun fact: 0,0 of the computer screen grid is top left, meaning verticle movement is to be subtracted


    if (event->key() == Qt::Key_W) {
        setPos(x(), y()-40);
    }

    else if (event->key() == Qt::Key_S) {
        setPos(x(), y()+40);
    }

    else if (event->key() == Qt::Key_A) {
        setPos(x()-40, y());
    }
    else if (event->key() == Qt::Key_D) {
        setPos(x()+40, y());
    }
}

#endif //DC_PROTAG_H
