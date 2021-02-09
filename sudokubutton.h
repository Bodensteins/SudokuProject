#ifndef SUDOKUBUTTON_H
#define SUDOKUBUTTON_H

#include<QPushButton>

class SudokuButton : public QPushButton
{
public:
    SudokuButton();

    void setIsTipNumber(bool);
    bool checkIsTipNumber();
    void setNumber(int);
    int getNumber();

private:
    bool isTipNumber;
    int num;

};

#endif // SUDOKUBUTTON_H
