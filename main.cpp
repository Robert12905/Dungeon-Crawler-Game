// File: main.cpp

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QKeyEvent>
#include <QRandomGenerator>

// GameRoom class declaration
class GameRoomWindow : public QWidget {
    Q_OBJECT

public:
    GameRoomWindow(int roomIndex, QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void setupRoomWithTiles();  // Method to set up tile-based cave rooms

private slots:
            void goToRandomRoom();

private:
    int currentRoomIndex;
    QLabel *characterLabel;
    QWidget *tileContainer;  // Container widget to hold the room tiles

    int getRandomRoomIndex();
    void moveCharacter(int dx, int dy);
};

// GameRoom class definition
GameRoomWindow::GameRoomWindow(int roomIndex, QWidget *parent) : QWidget(parent), currentRoomIndex(roomIndex) {
    setFixedSize(500, 500);

    // Character setup
    characterLabel = new QLabel(this);
    QPixmap characterPixmap(":/images/character.png");  // Replace with your character image
    characterLabel->setPixmap(characterPixmap);
    characterLabel->setFixedSize(50, 50);
    characterLabel->move(100, 100);

    // Setup tile-based room layout
    setupRoomWithTiles();

    // Doors setup
    QPushButton *topDoor = new QPushButton("Door (Top)", this);
    QPushButton *bottomDoor = new QPushButton("Door (Bottom)", this);
    QPushButton *leftDoor = new QPushButton("Door (Left)", this);
    QPushButton *rightDoor = new QPushButton("Door (Right)", this);

    topDoor->setGeometry((width() / 2) - 50, 10, 100, 30);
    bottomDoor->setGeometry((width() / 2) - 50, height() - 40, 100, 30);
    leftDoor->setGeometry(10, (height() / 2) - 50, 100, 30);
    rightDoor->setGeometry(width() - 110, (height() / 2) - 50, 100, 30);

    connect(topDoor, &QPushButton::clicked, this, &GameRoomWindow::goToRandomRoom);
    connect(bottomDoor, &QPushButton::clicked, this, &GameRoomWindow::goToRandomRoom);
    connect(leftDoor, &QPushButton::clicked, this, &GameRoomWindow::goToRandomRoom);
    connect(rightDoor, &QPushButton::clicked, this, &GameRoomWindow::goToRandomRoom);
}

void GameRoomWindow::setupRoomWithTiles() {
    // Create a container for the tiles
    tileContainer = new QWidget(this);
    tileContainer->setGeometry(0, 0, width(), height());

    QGridLayout *gridLayout = new QGridLayout(tileContainer);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    // Define tile images
    QPixmap floorTile("C:\\Users\\kobio\\Downloads\\pixel floor.jpg");  // Replace with floor tile image
    QPixmap wallTile("C:\\Users\\kobio\\Downloads\\pixel wall.jpg");    // Replace with wall tile image
    QPixmap decorationTile(":/images/decoration_tile.png");  // Replace with decoration tile

    // Example room layouts for each room
    int roomLayouts[5][10][10] = {
            // Room 1: Basic cave layout with walls surrounding the floor
            {
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 0, 0, 2, 0, 0, 0, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
            },
            // Room 2: Mossy cave layout with decorations
            {
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 0, 0, 2, 0, 0, 0, 2, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 2, 0, 0, 0, 0, 0, 2, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 2, 0, 0, 0, 0, 0, 0, 2, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 0, 2, 0, 0, 0, 2, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
            },
            // Room 3: Crystal cave layout
            {
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 0, 0, 0, 0, 2, 0, 0, 0, 1},
                    {1, 0, 0, 0, 2, 0, 0, 0, 0, 1},
                    {1, 0, 2, 0, 0, 0, 2, 0, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 2, 0, 0, 2, 0, 0, 0, 2, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
            },
            // Room 4: Stalactite cave layout
            {
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 2, 0, 0, 0, 0, 0, 0, 2, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 2, 0, 0, 0, 0, 0, 2, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 2, 0, 0, 0, 0, 0, 0, 2, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 0, 2, 0, 0, 0, 2, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
            },
            // Room 5: Lava cave layout
            {
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                    {1, 2, 0, 0, 0, 0, 0, 0, 2, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 2, 0, 0, 0, 0, 0, 2, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 0, 0, 0, 2, 0, 0, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
                    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
            }
    };

    // Populate grid with tiles based on room layout
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            QLabel *tile = new QLabel(this);
            int tileType = roomLayouts[currentRoomIndex][i][j];
            if (tileType == 0) {
                tile->setPixmap(floorTile);
            } else if (tileType == 1) {
                tile->setPixmap(wallTile);
            } else if (tileType == 2) {
                tile->setPixmap(decorationTile);
            }
            tile->setFixedSize(50, 50);
            gridLayout->addWidget(tile, i, j);
        }
    }
}

void GameRoomWindow::keyPressEvent(QKeyEvent *event) {
    int key = event->key();
    int step = 10;

    if (key == Qt::Key_W) {
        moveCharacter(0, -step);
    } else if (key == Qt::Key_A) {
        moveCharacter(-step, 0);
    } else if (key == Qt::Key_S) {
        moveCharacter(0, step);
    } else if (key == Qt::Key_D) {
        moveCharacter(step, 0);
    }
}

void GameRoomWindow::moveCharacter(int dx, int dy) {
    int x = characterLabel->x() + dx;
    int y = characterLabel->y() + dy;

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > width() - characterLabel->width()) x = width() - characterLabel->width();
    if (y > height() - characterLabel->height()) y = height() - characterLabel->height();

    characterLabel->move(x, y);
}

void GameRoomWindow::goToRandomRoom() {
    int nextRoom = getRandomRoomIndex();
    GameRoomWindow *nextRoomWindow = new GameRoomWindow(nextRoom);
    nextRoomWindow->show();
    this->close();
}

int GameRoomWindow::getRandomRoomIndex() {
    int newRoom;
    do {
        newRoom = QRandomGenerator::global()->bounded(5);
    } while (newRoom == currentRoomIndex);
    return newRoom;
}

// Main window with title screen
class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
            void openFirstRoom();
};

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    QLabel *titleImageLabel = new QLabel(this);
    QPixmap titlePixmap(":/images/title_screen.png");  // Replace with your actual image path
    titleImageLabel->setPixmap(titlePixmap);
    titleImageLabel->setAlignment(Qt::AlignCenter);

    QPushButton *startButton = new QPushButton("Start", this);
    QPushButton *quitButton = new QPushButton("Quit", this);

    startButton->setStyleSheet("QPushButton { color: white; background-color: black; border-radius: 10px; padding: 10px; font-size: 18px; }");
    quitButton->setStyleSheet("QPushButton { color: white; background-color: black; border-radius: 10px; padding: 10px; font-size: 18px; }");

    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(titleImageLabel, 0, Qt::AlignCenter);
    buttonLayout->addWidget(startButton, 0, Qt::AlignCenter);
    buttonLayout->addWidget(quitButton, 0, Qt::AlignCenter);
    setLayout(buttonLayout);

    connect(quitButton, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::openFirstRoom);
}

void MainWindow::openFirstRoom() {
    GameRoomWindow *firstRoom = new GameRoomWindow(0);
    firstRoom->show();
    this->close();
}

// Main application entry point
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}

#include "main.moc"
