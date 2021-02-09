#ifndef TIPWINDOW_H
#define TIPWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

class TipWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TipWindow(bool, QString, QWidget *parent = nullptr);

private:
    bool isQualified;
    QLabel label, timeLabel;
    QPushButton back;
    QString finishTime;

signals:
    void returnMenu();
    void returnGame();

};

#endif // TIPWINDOW_H
