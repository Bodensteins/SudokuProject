#include "playgame.h"
#include "mainmenu.h"
//#include<QDebug>

PlayGame::PlayGame(int d, QWidget *parent)
    : QWidget(parent),
      timeBySec(0),
      sudoku(d),
      timer(this),
      tip(NULL)
{
   setFixedSize(1000,580);

   x=y=-1;

   submit.setParent(this);
   submit.move(725,410);
   submit.setFixedSize(150,50);
   submit.setText("submit");
   submit.setVisible(true);
   quit.setParent(this);
   quit.move(725,465);
   quit.setFixedSize(150,50);
   quit.setText("quit");
   quit.setVisible(true);

   initialChooseNumberButtons();

   initialLabels();

   initialSudokuButtons();

   play();

}

void PlayGame::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::gray);
    pen.setWidth(6);
    painter.setPen(pen);

    painter.drawLine(180,5,180,535);
    painter.drawLine(360,5,360,535);
    painter.drawLine(5,180,535,180);
    painter.drawLine(5,360,535,360);

    pen.setWidth(3);
    painter.drawLine(2,2,538,2);
    painter.drawLine(2,2,2,538);
    painter.drawLine(2,538,538,538);
    painter.drawLine(538,2,538,538);
}

void PlayGame::initialChooseNumberButtons()
{
    QFont font("Microsoft SongTi",20,75);

    chooseNumber[0].move(725,200);
    chooseNumber[1].move(775,200);
    chooseNumber[2].move(825,200);
    chooseNumber[3].move(725,250);
    chooseNumber[4].move(775,250);
    chooseNumber[5].move(825,250);
    chooseNumber[6].move(725,300);
    chooseNumber[7].move(775,300);
    chooseNumber[8].move(825,300);

    for(int i=0;i<9;i++){
        chooseNumber[i].setParent(this);
        chooseNumber[i].setFixedSize(50,50);
        QChar c=i+1+'0';
        QString str(c);
        chooseNumber[i].setText(str);
        chooseNumber[i].setFont(font);
        chooseNumber[i].setVisible(true);
    }
}

void PlayGame::initialLabels()
{
    QFont font1("Microsoft SongTi",20,75);
    QFont font2("Microsoft YaHei",15,75);
    QPalette labelColor;
    labelColor.setColor(QPalette::WindowText,Qt::darkRed);

    showRow.setParent(this);
    showRow.move(700,10);
    showRow.setFixedSize(300,50);
    showRow.setText("Row:     ");
    showRow.setVisible(true);
    showRow.setFont(font1);

    showColumn.setParent(this);
    showColumn.move(700,50);
    showColumn.setFixedSize(300,50);
    showColumn.setText("Column:  ");
    showColumn.setFont(font1);
    showColumn.setVisible(true);

    showTime.setParent(this);
    showTime.setFixedSize(300,50);
    showTime.move(700,120);
    showTime.setPalette(labelColor);
    showTime.setFont(font2);
    showTime.setText("Time: 0 : 0 : 0");
    showTime.setVisible(true);

    labelColor.setColor(QPalette::WindowText,Qt::blue);
    for(int i=0;i<9;i++){

        row[i].setParent(this);
        QChar c=i+1+'0';
        QString str1(c);
        str1="R"+str1;
        row[i].setFont(font2);
        row[i].setPalette(labelColor);
        row[i].setText(str1);
        row[i].move(545,i*60+10);
        row[i].setVisible(true);

        column[i].setParent(this);
        c=i+1+'0';
        QString str2(c);
        str2="C"+str2;
        column[i].setPalette(labelColor);
        column[i].setFont(font2);
        column[i].setText(str2);
        column[i].move(i*60+10,540);
        column[i].setVisible(true);
    }

}

void PlayGame::initialSudokuButtons()
{
    QPalette tipColor;
    QFont font("Microsoft SongTi",12,75);

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){

            button[i][j].setParent(this);
            button[i][j].setFont(font);
            button[i][j].move(i*60+5,j*60+5);
            button[i][j].setFixedSize(50,50);
            button[i][j].setVisible(true);
            int n=sudoku.getProbNum(i,j);
            button[i][j].setNumber(n);

            if(n>0&&n<10){
                tipColor.setColor(QPalette::ButtonText,Qt::darkGreen);
                button[i][j].setPalette(tipColor);
                QChar c=n+'0';
                QString str(c);
                button[i][j].setIsTipNumber(true);
                button[i][j].setText(str);
            }
            else{
                tipColor.setColor(QPalette::ButtonText,Qt::black);
                button[i][j].setIsTipNumber(false);
                button[i][j].setText("*");
            }
        }
    }

}

QString PlayGame::timeToString()
{
    int second,minute,hour,temp;
    second=timeBySec%60;
    temp=timeBySec/60;
    minute=temp%60;
    hour=temp/60;
    QString strH,strM,strS;
    strH=tr("%1").arg(hour);
    strM=tr("%1").arg(minute);
    strS=tr("%1").arg(second);
    QString str(strH+" : "+strM+" : "+strS);
    return str;
}

void PlayGame::play()
{
    timer.setInterval(1000);
    timer.start();

    connect(&timer, &QTimer::timeout,[=](){
        timeBySec++;
        showTime.setText("Time: "+timeToString());
    });

    //checkConfliction();

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(!button[i][j].checkIsTipNumber()){
                connect(&button[i][j],&QPushButton::clicked,[=](){

                    checkConfliction(x,y);
                    QPalette palette;
                    x=i,y=j;
                    palette.setColor(QPalette::ButtonText, Qt::blue);
                    button[x][y].setPalette(palette);
                    QChar r=y+'0'+1,c=x+'0'+1;
                    QString str1(r),str2(c);
                    str1="Row:     "+str1;
                    str2="Column:  "+str2;
                    showRow.setText(str1);
                    showColumn.setText(str2);
                });

            }
        }
    }

     for(int i=0;i<9;i++){
        connect(&chooseNumber[i], &QPushButton::clicked,[=](){
            if(x!=-1&&y!=-1){
                   button[x][y].setNumber(i+1);
                   sudoku.setProbNum(i+1,x,y);
                   QChar c=i+1+'0';
                   QString str(c);
                   button[x][y].setText(str);
             }
        });
    }

    connect(&submit,&QPushButton::clicked,[=](){
       timer.stop();
       if(sudoku.checkWin()){
           //qDebug()<<"Win";
           tip=new TipWindow(true, timeToString());
           tip->show();
           connect(tip, &TipWindow::returnMenu,[=](){
               timeBySec=0;
               close();
               emit returnMenu();
           });
       }
       else{
           //qDebug()<<"no";
           if(tip!=NULL)
               delete tip;
           tip=new TipWindow(false,timeToString());
           tip->show();
           connect(tip, &TipWindow::returnGame,[=](){
               timer.start();
           });
       }
    });

    connect(&quit,&QPushButton::clicked,[=](){
        //qDebug()<<"!";
        timer.stop();
        timeBySec=0;
        close();
        emit returnMenu();
    });


}

void PlayGame::checkConfliction(int x,int y)
{
    if(x==-1||y==-1)
        return;
    for (int i = 0; i < 9; i++) {
        if(!button[i][y].checkIsTipNumber()){
            QPalette palette;
            if(sudoku.check(i,y)
                    &&button[i][y].getNumber()!=-1)
                palette.setColor(QPalette::ButtonText,Qt::red);
            else
                palette.setColor(QPalette::ButtonText,Qt::black);
            button[i][y].setPalette(palette);
        }
    }
    for(int j=0;j<9;j++){
        if(!button[x][j].checkIsTipNumber()){
            QPalette palette;
            if(sudoku.check(x,j)
                    &&button[x][j].getNumber()!=-1)
                palette.setColor(QPalette::ButtonText,Qt::red);
            else
                palette.setColor(QPalette::ButtonText,Qt::black);
            button[x][j].setPalette(palette);
        }
    }
    int x0 = (x / 3) * 3;
    int y0 = (y / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if(!button[i+x0][j+y0].checkIsTipNumber()){
                QPalette palette;
                if(sudoku.check(i+x0,j+y0)
                        &&button[i+x0][j+y0].getNumber()!=-1)
                    palette.setColor(QPalette::ButtonText,Qt::red);
                else
                    palette.setColor(QPalette::ButtonText,Qt::black);
                button[i+x0][j+y0].setPalette(palette);
            }
        }
    }
}

PlayGame::~PlayGame()
{

}

