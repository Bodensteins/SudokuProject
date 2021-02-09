

#include "sudoku.h"

#include<cstdlib>
#include<ctime>
#include<iostream>
#include<QDebug>



Sudoku::Sudoku(int d) :difficulty(d) {//数独类的构造函数
    for (int i = 0; i < 9; i++) {//初始时isDelete全部赋值为false
        for (int j = 0; j < 9; j++) {
            prob[i][j] = 0;
            isDelete[i][j] = false;
        }
    }
    initial();//生成终盘
    output();
}

void Sudoku::disruptNum() {//随机打乱num[9]
    int rec = 0;
    int n;
    for (int i = 0; i < 9; i++) {
        int bit;
        do {
            n = rand() % 9 + 1;
            bit = 1 << (n - 1);
        } while (bit & rec);
        num[i] = n;
        rec |= 1 << (n - 1);
    }
}

bool Sudoku::checkRow(int x, int y) {//行冲突检测
    int num = prob[x][y];
    for (int i = 0; i < 9; i++) {
        if (num == prob[x][i] && i != y)
            return true;
    }
    return false;
}

bool Sudoku::checkColumn(int x, int y) {//列冲突检测
    int num = prob[x][y];
    for (int i = 0; i < 9; i++) {
        if (num == prob[i][y] && i != x)
            return true;
    }
    return false;
}

bool Sudoku::checkBox(int x, int y) {//宫冲突检测
    int num = prob[x][y];
    int x0 = (x / 3) * 3;
    int y0 = (y / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (prob[i + x0][j + y0] == num && (i + x0 != x || j + y0 != y))
                return true;
        }
    }
    return false;
}

bool Sudoku::check(int x, int y) {//冲突检测
    return checkColumn(x, y) || checkRow(x, y) || checkBox(x, y);
}

bool Sudoku::initial(int x, int y) {//实际执行终盘生成的函数
    if (9 == x)
        return true;//若x==9表明全部生成完毕，函数可以退出了
    disruptNum();//打乱num[9]，保证生成的随机性
    for (int n = 0; n < 9; n++) {//对于1-9(打乱后)的每个值进行搜索
        prob[x][y] = num[n];
        if (check(x, y))//检查是否冲突，若冲突则搜索下一个
            continue;
        int nx = x, ny = y + 1;//否则前进至下一格
        if (y == 8) {
            nx++;
            ny = 0;
        }
        if (initial(nx, ny))//递归调用，若下一格之后均生成成功，则返回true
            return true;
    }
    prob[x][y] = 0;//若1-9均不符合要求，则返回false
    return false;
}

void Sudoku::randomDelete(int deleteNum) {//随机挖空
    for (int i = 0; i < deleteNum; i++) {
        int x, y;
        do {
            x = rand() % 9;//生成随机数
            y = rand() % 9;
        } while (isDelete[x][y]);//若已经删除则重新生成
        prob[x][y] = -1;
        isDelete[x][y] = true;
    }
}

void Sudoku::initial() {
    srand((unsigned)time(NULL));
    initial(0, 0);
    for (int i = 0; i < 9; i++)//拷贝答案
        for (int j = 0; j < 9; j++)
            ans[i][j] = prob[i][j];
    do {
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++) {//答案再次拷贝
                prob[i][j] = ans[i][j];
                isDelete[i][j] = false;//全部清空
            }
        randomDelete(difficulty);//随机删除
        //printf("%d\n", checkAnswer());
    } while (checkAnswer() > 1);//若最终的解个数大于1则重新挖空
}

void Sudoku::output() {//终端输出答案
    std::cout<<"********************\n";
    for (int i = 0; i < 9; i++) {
        std::cout<<"*";
        for (int j = 0; j < 9; j++)
               std::cout<<ans[j][i]<<' ';
        std::cout<<"*\n";
    }
    std::cout << "********************"<<std::endl;
}

bool Sudoku::checkWin() {//答案检查
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (prob[i][j] != ans[i][j])
                return false;
    return true;
}

int Sudoku::checkAnswer() {//检查多解
    ansNum = 0;
    checkAnswer(0, 0);
    return ansNum;
}
void Sudoku::checkAnswer(int x, int y) {//实际检查多解，思路与生成函数类似
    //printf("%d %d\n", x, y);
    if (x == 9) {//x==9表明搜索到了终点，答案个数加1
        ansNum ++;
        return;
    }
    int nx = x, ny = y + 1;//nx,ny为下一点位置
    if (ny == 9) {
        nx ++;
        ny = 0;
    }
    if (!isDelete[x][y]) {//若该点为提示数则直接到下一点
        checkAnswer(nx, ny);
        return;
    }
    for (int n = 1; n <= 9; n++) {//否则从1-9开始搜索答案
        prob[x][y] = n;
        if (check(x, y))//冲突检查
            continue;
        checkAnswer(nx, ny);//若不冲突则前往下一点
        if (ansNum > 1){//若已经有两个答案则停止搜索
            prob[x][y]=-1;
            return;
        }
    }
    prob[x][y] = -1;//搜索不到则返回上一级
    return;
}

void Sudoku::setProbNum(int num, int x, int y)
{
    prob[x][y]=num;
}

int Sudoku::getProbNum(int x, int y)
{
    return prob[x][y];
}
