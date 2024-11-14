//Project By: Robert B., Nicholas P., Stance.O

//********//

#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGraphicsScene>
#include "DC_Protag..h"
#include <QGraphicsView>
#include <QBrush>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//code which is open to editing. . . helps place character in middle of map

    //screen size
    int screenXSize = 1440;
    int screenYsize = 846;

    int center_X_Pos = (screenXSize-100) / 2;
    int center_Y_Pos = (screenYsize-100) / 2;


//sets game screen as a scene (WIP)
    QGraphicsScene * scene = new QGraphicsScene();


//scans header file 'DC_Protag..h' and reads the definition: key-press-events
    DC_Protag * rect = new DC_Protag();
    rect->setRect(center_X_Pos,center_Y_Pos,100,100);

//Protagonist is now visible in the 'scene window'
    scene->addItem(rect);


//Focuses key-presses toward the protagonist object
    rect->setFlag(QGraphicsItem::ItemIsFocusable);
    rect->setFocus();


    QGraphicsView * view = new QGraphicsView(scene);

//sets the screen-size ratio
    view->setFixedSize(screenXSize,screenYsize);

//sets 'floor' (background) color
    view -> setBackgroundBrush(QBrush(QColor(255,255,255)));
    view->show();

    //QWidget window;
    //window.resize(1920, 1080);
    //window.setWindowTitle("Hello, Qt!");
    //window.show();

    return app.exec();
}
