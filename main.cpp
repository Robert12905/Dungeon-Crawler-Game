#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QColor>
#include <vector>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>

class Character : public QGraphicsPixmapItem {
public:
    enum Direction { Up, Down, Left, Right };

    Character() {
        // Load different sprites for each direction
        sprites[Up] = QPixmap(//Insert File Directory For Up Sprite);
        sprites[Down] = QPixmap(//Insert File Directory For Down Sprite);
        sprites[Left] = QPixmap(//Insert File Directory For Left Sprite);
        sprites[Right] = QPixmap(//Insert File Directory For Right Sprite);

        // Resize the sprites to fit within a 32x32 grid square
        for (int i = 0; i < 4; ++i) {
            sprites[i] = sprites[i].scaled(32, 32, Qt::KeepAspectRatio);
        }

        // Set initial direction (Down by default)
        currentDirection = Down;
        setPixmap(sprites[currentDirection]);
    }

    void move(Direction dir, QGraphicsScene* scene, const std::vector<std::vector<int>>& layout, int tileSize) {
        currentDirection = dir;
        setPixmap(sprites[currentDirection]); // Update sprite based on direction

        // Calculate the new position based on the direction
        int newX = x();
        int newY = y();

        switch (dir) {
            case Up:
                newY -= tileSize;
            break;
            case Down:
                newY += tileSize;
            break;
            case Left:
                newX -= tileSize;
            break;
            case Right:
                newX += tileSize;
            break;
        }

        // Calculate the new row and column based on the new position
        int newCol = static_cast<int>(newX) / tileSize; // Using integer division to map to the grid
        int newRow = static_cast<int>(newY) / tileSize;

        // Adjust position to make sure we're aligned correctly with the grid
        int alignedX = newCol * tileSize;
        int alignedY = newRow * tileSize;

        // Check if the new position is valid (no collisions with walls or obstacles)
        if (isValidMove(newRow, newCol, layout)) {
            // Set the new aligned position
            setPos(alignedX, alignedY);
        }
    }



    bool isValidMove(int row, int col, const std::vector<std::vector<int>>& layout) const {
        // Make sure the row and column are within bounds
        if (row < 0 || col < 0 || row >= layout.size() || col >= layout[0].size()) {
            return false;
        }

        // Check if the tile is a wall (0) or an obstacle (2)
        int tileType = layout[row][col];
        return tileType != 0 && tileType != 2; // Can't move onto walls or obstacles
    }

private:
    Direction currentDirection;
    QPixmap sprites[4]; // Array to store the four sprites for each direction
};

class MatrixBasedCircularArenaRoom : public QGraphicsView {
public:
    MatrixBasedCircularArenaRoom(QWidget* parent = nullptr) : QGraphicsView(parent) {
        scene = new QGraphicsScene(this);
        setScene(scene);
        setRenderHint(QPainter::Antialiasing);
        setResizeAnchor(QGraphicsView::AnchorViewCenter);
        createArenaLayout();
        character = nullptr;
    }

    void setCharacter(Character* charPtr) {
        character = charPtr;
    }

    QGraphicsScene* getScene() const { // Public accessor for the scene
        return scene;
    }

private:
    QGraphicsScene* scene;
    Character* character; // Pointer to the character object
    const int tileSize = 32;

    const std::vector<std::vector<int>> layout = {

            {0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 0, 0, 0},
            {0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 0, 0},
            {0, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 0},
            {0, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 0, 0},
            {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
            {0, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
            {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
            {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    void createArenaLayout() {
        for (int row = 0; row < layout.size(); ++row) {
            for (int col = 0; col < layout[row].size(); ++col) {
                int tileType = layout[row][col];
                QGraphicsRectItem* tile = new QGraphicsRectItem(col * tileSize, row * tileSize, tileSize, tileSize);
                switch (tileType) {
                case 0:
                    tile->setBrush(QBrush(Qt::black));  // Wall
                    break;
                case 1:
                    tile->setBrush(QColor(80, 80, 80));  // Floor
                    break;
                case 2:
                    tile->setBrush(QBrush(QColorConstants::Svg::black));  // Obstacle

                    break;
                case 3:
                    tile->setBrush(QBrush(Qt::green));   // Water or special area
                    break;
                case 4:
                    tile->setBrush(QBrush(Qt::red));    // Exit/Entrance
                    break;
                }
                scene->addItem(tile);
            }
        }
    }

protected:
    void keyPressEvent(QKeyEvent* event) override {
        if (!character) return;

        if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up) {
            character->move(Character::Up, scene, layout, tileSize);
        } else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down) {
            character->move(Character::Down, scene, layout, tileSize);
        } else if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left) {
            character->move(Character::Left, scene, layout, tileSize);
        } else if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right) {
            character->move(Character::Right, scene, layout, tileSize);
        }
    }

    void resizeEvent(QResizeEvent* event) override {
        QGraphicsView::resizeEvent(event);
        fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MatrixBasedCircularArenaRoom arena;
    Character* character = new Character();
    arena.setCharacter(character);
    arena.getScene()->addItem(character);

    // Start the character at a specific position
    character->setPos(320, 452);  // Initial position within the arena
    arena.show();

    return a.exec();
}

#include "main.moc"
