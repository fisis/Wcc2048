#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gui/qgameboard.h"
#include "webcamcap.h"

#include <QMainWindow>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;
    QGameBoard *gameBoard;
    webcamcap::MyFifo fifo;


    QTime *timer;
    bool lastWasEmpty;

    float l,r,u,d;
    glm::vec2 dif;
    glm::vec2 point;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void connects(bool con);
    void restartGame();
    void handlePoints(std::vector<glm::vec2> pts);

private:
    void handledirections();
};

#endif // MAINWINDOW_H
