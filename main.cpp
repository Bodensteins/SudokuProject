/*
 *本程序的核心类为Sudoku类，因此重点介绍Sudoku类
 */

#include "playgame.h"
#include "mainmenu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainMenu m;
    m.show();
    return a.exec();
}
