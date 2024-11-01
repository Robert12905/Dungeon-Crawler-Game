#include <QGraphicsRectItem>
#include <Qdebug>


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

//********//qDebug() << "DC_Protag::keyPressEvent";//********//
}
#endif //DC_PROTAG_H
