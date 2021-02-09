#include "mainmenu.h"
#include "sudoku.h"
#include <QDebug>

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent),
      game(NULL)
{
    initialMenu();

    connect(&easy,&QPushButton::clicked,[=](){
        game=new PlayGame(EASY);
        game->show();
        close();

        connect(game,&PlayGame::returnMenu,[=](){
           show();
        });
    });

    connect(&middle,&QPushButton::clicked,[=](){
        game=new PlayGame(MIDDLE);
        game->show();
        close();

        connect(game,&PlayGame::returnMenu,[=](){
           show();
        });
    });

    connect(&hard,&QPushButton::clicked,[=](){
        game=new PlayGame(HARD);
        game->show();
        close();

        connect(game,&PlayGame::returnMenu,[=](){
           show();
        });
    });

    connect(&exit,&QPushButton::clicked,[=](){
        close();
    });


    if(game!=NULL)
        delete game;

}

void MainMenu::initialMenu()
{
    setFixedSize(500,500);

    QFont titleFont("Microsoft yahei", 20, 87);
    QFont buttonFont("Microsoft songti", 12, 67);

    title.setParent(this);
    title.move(173,10);
    title.setFixedSize(150,50);
    title.setFont(titleFont);
    title.setText("Sudoku");

    easy.setParent(this);
    easy.move(150,100);
    easy.setFixedSize(200,70);
    easy.setVisible(true);
    easy.setFont(buttonFont);
    easy.setText("Easy");

    middle.setParent(this);
    middle.move(150,200);
    middle.setFixedSize(200,70);
    middle.setVisible(true);
    middle.setFont(buttonFont);
    middle.setText("Middle");

    hard.setParent(this);
    hard.move(150,300);
    hard.setFixedSize(200,70);
    hard.setVisible(true);
    hard.setFont(buttonFont);
    hard.setText("Hard");

    exit.setParent(this);
    exit.move(150,400);
    exit.setFixedSize(200,70);
    exit.setVisible(true);
    exit.setFont(buttonFont);
    exit.setText("Exit");
}


