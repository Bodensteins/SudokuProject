#include "sudokubutton.h"

SudokuButton::SudokuButton()
{

}

void SudokuButton::setIsTipNumber(bool itn)
{
    isTipNumber=itn;
}

bool SudokuButton::checkIsTipNumber()
{
    return isTipNumber;
}

void SudokuButton::setNumber(int n)
{
    num=n;
}

int SudokuButton::getNumber()
{
    return num;
}
