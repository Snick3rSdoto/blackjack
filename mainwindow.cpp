#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

multiMap = {{"D", 2}, {"H", 2}, {"C", 2}, {"S", 2},        // D - (Бубы / Алмазы)
            {"D", 3}, {"H", 3}, {"C", 3}, {"S", 3},        // H - (Черви / Сердца)
            {"D", 4}, {"H", 4}, {"C", 4}, {"S", 4},        // C - (Трефы / Клубы)
            {"D", 5}, {"H", 5}, {"C", 5}, {"S", 5},        // S - (Пики / Лопаты)
            {"D", 6}, {"H", 6}, {"C", 6}, {"S", 6},        //------------------------
            {"D", 7}, {"H", 7}, {"C", 7}, {"S", 7},        // J - (Валет / Джек)
            {"D", 8}, {"H", 8}, {"C", 8}, {"S", 8},        // Q - (Дама / Королева)
            {"D", 9}, {"H", 9}, {"C", 9}, {"S", 9},        // K - (Король)
            {"D", 10},{"H", 10},{"C", 10},{"S", 10},       // A - (Туз)
//          {"DJ",10},{"JH",10},{"CJ",10},{"SJ",10},
//          {"DQ",10},{"HQ",10},{"CQ",10},{"SQ",10},
//          {"DK",10},{"HK",10},{"CK",10},{"SK",10},
//          {"DA",11},{"HA",11},{"CA",11},{"SA",11},
};
//    for(int i = 0; i<4; ++i){
//    int randStartCard = rand() % multiMap.size();
//    QMultiMap<QString, int>::iterator it = multiMap.begin();

//    while (it != multiMap.end() && randStartCard > 0) {
//           ++it;
//           --randStartCard;
//       }
//    QString suit = it.key();
//    int value = it.value();

//    QString cardValue = QString::number(value);
//    QString combinedString = QString("%1\n%2").arg(suit).arg(cardValue);
//    it = multiMap.erase(it);

//    if(i==0) {
//        ui->label_1->setText(combinedString);
//    } else if (i==1) {
//        ui->label_2->setText(combinedString);
//    } else if (i==2) {
//        ui->enemy_label_1->setText(combinedString);
//    } else if (i==3) {
//        ui->enemy_label_2->setText(combinedString);
//    }
//    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

int cardsCheck = 1;
int hand = 0, enemyHand = 0;
bool checkStand = false;


void MainWindow::on_pushButton_hit_clicked()
{

if(multiMap.size()>0 && hand < 21 && checkStand == false){
    int randCards = rand() % multiMap.size();
    QMultiMap<QString, int>::iterator it = multiMap.begin();

    while (it != multiMap.end() && randCards > 0) {
           ++it;
           --randCards;
       }

    QString suit = it.key();
    int value = it.value();

    QString cardValue = QString::number(value);
    QString combinedString = QString("%1\n%2").arg(suit).arg(cardValue);
    it = multiMap.erase(it);

    if(cardsCheck == 1 ) {
        ui->label_1->setText(combinedString);
    } else if (cardsCheck == 2) {
        ui->label_2->setText(combinedString);
    } else if (cardsCheck == 3) {
        ui->label_3->setText(combinedString);
    } else if (cardsCheck == 4) {
        ui->label_4->setText(combinedString);
    } else if (cardsCheck == 5) {
        ui->label_5->setText(combinedString);
    }
    cardsCheck++;

    hand += value;
    QString strHand = QString::number(hand);
    ui->label->setText(strHand);
    if(hand == 21)
        ui->label->setText("you won");
    else if (hand > 21)
        ui->label->setText("you lose");
}

}


void MainWindow::on_pushButton_stand_clicked() {

    if(!checkStand){
        checkStand = true;
        cardsCheck = 1;
    }
    while (enemyHand<=hand && enemyHand<21){
    int randCards = rand() % multiMap.size();
    QMultiMap<QString, int>::iterator it = multiMap.begin();

    while (it != multiMap.end() && randCards > 0) {
           ++it;
           --randCards;
       }

    QString suit = it.key();
    int value = it.value();

    QString cardValue = QString::number(value);
    QString combinedString = QString("%1\n%2").arg(suit).arg(cardValue);
    it = multiMap.erase(it);

    if(cardsCheck == 1 ) {
        ui->enemy_label_1->setText(combinedString);
    } else if (cardsCheck == 2) {
        ui->enemy_label_2->setText(combinedString);
    } else if (cardsCheck == 3) {
        ui->enemy_label_3->setText(combinedString);
    } else if (cardsCheck == 4) {
        ui->enemy_label_4->setText(combinedString);
    } else if (cardsCheck == 5) {
        ui->enemy_label_5->setText(combinedString);
    }
    cardsCheck++;

    enemyHand += value;
    QString strEnemyHand = QString::number(enemyHand);
    ui->enemy_label->setText(strEnemyHand);
}
}
