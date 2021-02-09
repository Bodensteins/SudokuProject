#include "tipwindow.h"

TipWindow::TipWindow(bool b, QString str, QWidget *parent) :
    QWidget(parent),
    isQualified(b),
    finishTime(str)
{
    setFixedSize(300,200);

    QFont font("Microsoft yahei", 12, 65);

    setWindowModality(Qt::ApplicationModal);

    back.setParent(this);
    back.setFixedSize(100,50);
    back.move(100, 100);
    back.setVisible(true);

    label.setParent(this);
    label.setFixedSize(200,50);
    label.setFont(font);

    timeLabel.setParent(this);
    timeLabel.setFixedSize(200,50);
    timeLabel.move(70,40);
    timeLabel.setFont(font);

    if(isQualified){
        label.move(100,10);
        label.setText("Succeed");
        timeLabel.setText("Time: "+finishTime);
        back.setText("quit");
        connect(&back, &QPushButton::clicked, [=](){
            close();
            emit returnMenu();
        });
    }
    else{
        label.move(85,10);
        label.setText("Fail to solve");
        timeLabel.setText("Time: "+finishTime);
        back.setText("back");
        connect(&back,&QPushButton::clicked,[=](){
            close();
            emit returnGame();
        });
    }
}
