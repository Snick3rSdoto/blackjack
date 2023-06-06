#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QString>
#include <QDebug>
#include <random>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->update_cards();
    this->update_hands();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_hit_clicked()
{
    if(hand < 21)
    {
        this->user_pick_card();

        qDebug()<<hand;
        if(hand == 21) {qDebug() << "you won"; }
        else if (hand > 21) {qDebug() << "you lose";}
    }
}


void MainWindow::on_pushButton_stand_clicked()
{
    this->ui->pushButton_hit->setEnabled(false);
    this->ui->pushButton_stand->setEnabled(false);
    this->ui->pushButton_continue->setEnabled(true);
    while(true)
    {

        if(enemyHand>hand && enemyHand < 22){
            qDebug()<<"you lose";
            break;
        }
        else if (enemyHand == hand && enemyHand > 16) {
            qDebug()<<"equal";
            break;
        }
        else if (enemyHand>21){
            qDebug()<<"you won";
            break;
        }
        else if (enemyHand < hand && enemyHand > 16) {
            qDebug()<<"you won";
            break;
        }

        this->enemy_pick_card();

        qDebug()<<enemyHand<<" en";

    }
}

void MainWindow::on_pushButton_continue_clicked()
{
    this->ui->pushButton_hit->setEnabled(true);
    this->ui->pushButton_stand->setEnabled(true);
    this->ui->pushButton_continue->setEnabled(false);
    this->update_hands();

}

void MainWindow::update_cards()
{
    this->available_cards.clear();

    this->available_cards = {
        new Card(this, "D", 1), new Card(this, "H", 1), new Card(this, "C", 1), new Card(this, "S", 1),
        new Card(this, "D", 2), new Card(this, "H", 2), new Card(this, "C", 2), new Card(this, "S", 2),        // D - (Бубы / Алмазы)
        new Card(this, "D", 3), new Card(this, "H", 3), new Card(this, "C", 3), new Card(this, "S", 3),        // H - (Черви / Сердца)
        new Card(this, "D", 4), new Card(this, "H", 4), new Card(this, "C", 4), new Card(this, "S", 4),        // C - (Трефы / Клубы)
        new Card(this, "D", 5), new Card(this, "H", 5), new Card(this, "C", 5), new Card(this, "S", 5),        // S - (Пики / Лопаты)
        new Card(this, "D", 6), new Card(this, "H", 6), new Card(this, "C", 6), new Card(this, "S", 6),        //------------------------
        new Card(this, "D", 7), new Card(this, "H", 7), new Card(this, "C", 7), new Card(this, "S", 7),        // J - (Валет / Джек)
        new Card(this, "D", 8), new Card(this, "H", 8), new Card(this, "C", 8), new Card(this, "S", 8),        // Q - (Дама / Королева)
        new Card(this, "D", 9), new Card(this, "H", 9), new Card(this, "C", 9), new Card(this, "S", 9),        // K - (Король)
        new Card(this, "D", 10),new Card(this, "H", 10),new Card(this, "C", 10),new Card(this, "S", 10),       // A - (Туз)
        new Card(this, "DJ", 10),new Card(this, "HJ", 10),new Card(this, "CJ", 10),new Card(this, "SJ", 10),
        new Card(this, "DQ", 10),new Card(this, "HQ", 10),new Card(this, "CQ", 10),new Card(this, "SQ", 10),
        new Card(this, "DK", 10),new Card(this, "HK", 10),new Card(this, "CK", 10),new Card(this, "SK", 10),
    };
    qDebug() << "nen";
    std::random_shuffle(this->available_cards.begin(), this->available_cards.end());
}


void MainWindow::update_hands()
{
    qDebug()<<hand;
    for(auto c: this->user_cards) {delete c;}
    for(auto c: this->enemy_cards) {delete c;}

    this->user_cards.clear();
    this->hand = 0;
    this->user_pick_card();
    this->user_pick_card();


    this->enemy_cards.clear();
    this->enemyHand = 0;
    this->enemy_pick_card();
    this->enemy_pick_card();

}

void MainWindow::user_pick_card()
{
    if (this->available_cards.isEmpty())  { this->update_cards(); }

    int posCard = 400 + 30 * this->user_cards.size();

    Card *card = this->available_cards.takeLast();

    hand += card->rank;
    card->draw_card(posCard, 400);

    user_cards.append(card);
}

void MainWindow::enemy_pick_card()
{
    if (this->available_cards.isEmpty())  { this->update_cards(); }

    int posCard = 400 + 30 * this->enemy_cards.size();

    Card *card = this->available_cards.takeLast();

    enemyHand += card->rank;
    card->draw_card(posCard, 50);

    enemy_cards.append(card);
}

















