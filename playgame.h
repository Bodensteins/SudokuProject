/*
 *本类为游戏界面ui类，是主要的界面
 */

#ifndef PLAYGAME_H
#define PLAYGAME_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QLabel>
#include <QTimer>
#include "sudoku.h"
#include "sudokubutton.h"
#include "tipwindow.h"

class PlayGame : public QWidget
{
    Q_OBJECT
public:
    explicit PlayGame(int, QWidget *parent = nullptr);

    ~PlayGame();

signals:
    void returnMenu();
    void qualified();
    void unqualified();

private:
    void paintEvent(QPaintEvent *) override;

    void initialChooseNumberButtons();
    void initialLabels();
    void initialSudokuButtons();
    QString timeToString();//时间转换为字符串
    void play();
    void checkConfliction(int,int);//冲突检测

    int x, y;
    int timeBySec;
    Sudoku sudoku;
    QPushButton submit, quit;
    QPushButton chooseNumber[9];
    QLabel showColumn, showRow, showTime;
    QTimer timer;
    QLabel column[9], row[9];
    SudokuButton button[9][9];
    TipWindow *tip;

};

#endif // PLAYGAME_H
