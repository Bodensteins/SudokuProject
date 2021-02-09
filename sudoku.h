/*
 * 该类为数独程序的核心逻辑类，负责生成一个合格的数独题目，
 * 并实际执行答案检查，冲突检测等工作
*/

#ifndef SUDOKU_H
#define SUDOKU_H

//简单挖空31个，普通41个，困难51个
#define EASY 31
#define	MIDDLE 41
#define HARD 51


class Sudoku
{
public:
    Sudoku(int);//构造函数
    void output();//在终端输出数独答案
    bool checkWin();//答案检查
    void setProbNum(int,int,int);//设置某格的值
    int getProbNum(int,int);//查询某格的值
    bool check(int, int);//冲突检测

private:
    void disruptNum();//将num[9]中元素（1-9）随机打乱顺序
    bool checkRow(int, int);//行冲突检测
    bool checkColumn(int, int);//列冲突检测
    bool checkBox(int, int);//宫冲突检测
    void randomDelete(int);//对终盘进行随机的挖空函数
    //生成终盘的函数
    bool initial(int, int);
    void initial();
    //检查是否多解的函数
    int checkAnswer();
    void checkAnswer(int,int);

    int ansNum;//记录当前数独题目答案个数
    int ans[9][9];//记录数独答案
    int prob[9][9];//记录数独题目
    int num[9];//数字1-9的随机排列
    bool isDelete[9][9];//储存某格是否被挖空
    int difficulty;//难度变量
};


#endif // SUDOKU_H
