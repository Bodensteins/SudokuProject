#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "playgame.h"

class MainMenu : public QWidget
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = nullptr);

private:
    void initialMenu();

    QLabel title;
    QPushButton easy, middle, hard, exit;
    PlayGame *game;
};

#endif // MAINMENU_H
