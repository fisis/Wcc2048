#include "gui/mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include <iostream>
#include <glm/glm.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) ,
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameBoard = new QGameBoard(this);
    setCentralWidget(gameBoard);

    connect(ui->actionConnect, SIGNAL(triggered(bool)), this, SLOT(connects(bool)));
    connect(ui->actionRestart, SIGNAL(triggered()), this, SLOT(restartGame()));
    connect(&fifo, SIGNAL(pointsReady(std::vector<glm::vec2>)), this, SLOT(handlePoints(std::vector<glm::vec2>)));

    lastWasEmpty = true;
    l = r = u = d = 0.0f;
    timer = new (QTime);
}

MainWindow::~MainWindow()
{
    fifo.disconnectServer();
    delete timer;
    delete gameBoard;
    delete ui;
}

void MainWindow::connects(bool con)
{
    if(con)
    {
        if(!fifo.connectServer())
        {
            QMessageBox::warning(this, QString("Warning"), QString("Could not connect to main WebCamCap program"));
            ui->actionConnect->setChecked(false);
        }
    }
    else
    {
        fifo.disconnectServer();
    }
}

void MainWindow::restartGame()
{
    emit gameBoard->resetGame();
}

void MainWindow::handlePoints(std::vector<glm::vec2> pts)
{
    if(timer->isNull())
    {
        timer->start();
    }

    if(pts.size() != 1)
    {
        lastWasEmpty = true;
        return;
    }

    if(lastWasEmpty)
    {
        lastWasEmpty = false;
        point = pts[0];
    }
    else
    {
        dif = point;
        point = pts[0];
        handledirections();
    }
}

void MainWindow::handledirections()
{
    if(timer->elapsed() < 700)
    {
        return;
    }

    glm::vec2 diff = point - dif;

    float mindiff = 0.07;



    if(glm::abs(diff.x) > glm::abs(diff.y))
    {

        if(diff.x > mindiff)
        {
            l+=diff.x;
            if(l >= 0.3)
            {
                gameBoard->arrows(LEFT);
                timer->restart();
                l = r = u = d = 0.0f;
                std::cout << "LEFT" << l << std::endl;
            }

            r = u = d = 0.0f;
        }
        if(diff.x < -mindiff)
        {
            r+= diff.x;
            if(r <= -0.3f)
            {
                gameBoard->arrows(RIGHT);
                timer->restart();
                l = r = u = d = 0.0f;
                std::cout << "RIGHT" << l << std::endl;
            }
            l = u = d = 0.0f;
        }
    }
    else
    {
        if(diff.y > mindiff)
        {
            d+= diff.y;

            if(d >= 0.3f)
            {
                gameBoard->arrows(DOWN);
                timer->restart();
                l = r = u = d = 0.0f;
                std::cout << "DOWN" << l << std::endl;
            }

            l = r = u = 0.0f;
        }

        if(diff.y < -mindiff)
        {
            u+= diff.y;

            if(u <= -0.3f)
            {
                gameBoard->arrows(UP);
                timer->restart();
                l = r = u = d = 0.0f;
                std::cout << "UP" << l << std::endl;
            }
            l = r = d = 0.0f;
        }
    }
}
