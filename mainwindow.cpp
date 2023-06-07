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
    this->update_balance();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_hit_clicked()
{
        this->user_pick_card();
        while (hand > 21 && ace > 0) {
            hand -= 10;
            ace--;
        }
        qDebug() << hand;
        if(hand == 21) {
            qDebug() << "you won";
            this->ui->pushButton_hit->setEnabled(false);
            this->ui->pushButton_stand->setEnabled(false);
            this->ui->pushButton_continue->setEnabled(true);

            balance += betAmounts[currentBetIndex];
            this->update_balance();
            this->ui->pushButton_minusBet->setEnabled(true);
            this->ui->pushButton_plusBet->setEnabled(true);
        }
        else if (hand > 21) {
            qDebug() << "you lose";
            this->ui->pushButton_hit->setEnabled(false);
            this->ui->pushButton_stand->setEnabled(false);
            this->ui->pushButton_continue->setEnabled(true);

            balance -= betAmounts[currentBetIndex];
            this->update_balance();
            this->ui->pushButton_minusBet->setEnabled(true);
            this->ui->pushButton_plusBet->setEnabled(true);
        }
}


void MainWindow::on_pushButton_stand_clicked()
{
    this->ui->pushButton_hit->setEnabled(false);
    this->ui->pushButton_stand->setEnabled(false);
    this->ui->pushButton_continue->setEnabled(true);
    while (enemyHand > 21 && enemyAce > 0) {
        enemyHand -= 10;
        enemyAce--;
    }
    while(true)
    {

        if(enemyHand > hand && enemyHand < 22){
            qDebug() << "you lose";
            balance -= betAmounts[currentBetIndex];
            this->update_balance();
            this->ui->pushButton_minusBet->setEnabled(true);
            this->ui->pushButton_plusBet->setEnabled(true);
            break;
        }
        else if (enemyHand == hand && enemyHand > 16) {
            qDebug() << "push";
            this->ui->pushButton_minusBet->setEnabled(true);
            this->ui->pushButton_plusBet->setEnabled(true);
            break;
        }
        else if (enemyHand > 21) {
            qDebug() << "you won";
            balance += betAmounts[currentBetIndex];
            this->update_balance();
            this->ui->pushButton_minusBet->setEnabled(true);
            this->ui->pushButton_plusBet->setEnabled(true);
            break;
        }
        else if (enemyHand < hand && enemyHand > 16) {
            qDebug() << "you won";
            balance += betAmounts[currentBetIndex];
            this->update_balance();
            this->ui->pushButton_minusBet->setEnabled(true);
            this->ui->pushButton_plusBet->setEnabled(true);
            break;
        }

        this->enemy_pick_card();

        qDebug() << enemyHand << " en";

    }
}

void MainWindow::on_pushButton_continue_clicked()
{
    ace = 0;
    enemyAce = 0;
    if(balance>=betAmounts[currentBetIndex]) {
        this->update_hands();
        if (!this->check_blackJack()) {
            this->ui->pushButton_hit->setEnabled(true);
            this->ui->pushButton_stand->setEnabled(true);
            this->ui->pushButton_continue->setEnabled(false);
            this->ui->pushButton_minusBet->setEnabled(false);
            this->ui->pushButton_plusBet->setEnabled(false);
        }

        qDebug() << hand << ' ' << enemyHand;
    }
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
    qDebug() << "----";
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


void MainWindow::update_balance()
{
    QString strbBal = QString::number(balance);
    ui->label_balance->setText(strbBal);
}


void MainWindow::user_pick_card()
{
    if (this->available_cards.isEmpty())  { this->update_cards(); }

    int posCard = 400 + 30 * this->user_cards.size();

    Card *card = this->available_cards.takeLast();

    if (card->rank == 1) {
        hand += 11;
        ace++;
    }
    else { hand += card->rank; }

    card->draw_card(posCard, 400);

    user_cards.append(card);

}


void MainWindow::enemy_pick_card()
{
    if (this->available_cards.isEmpty()) { this->update_cards(); }

    int posCard = 400 + 30 * this->enemy_cards.size();

    Card *card = this->available_cards.takeLast();

    if (card->rank == 1) {
        enemyHand += 11;
        enemyAce++;
    }
    else { enemyHand += card->rank; }

    card->draw_card(posCard, 50);

    enemy_cards.append(card);
}


void MainWindow::on_pushButton_minusBet_clicked()
{
    if(currentBetIndex > 0)
        currentBetIndex--;
    QString strBet = QString::number(betAmounts[currentBetIndex]);
    ui->label_bet->setText(strBet);
}


void MainWindow::on_pushButton_plusBet_clicked()
{
    if(currentBetIndex < 4)
        currentBetIndex++;
    QString strBet = QString::number(betAmounts[currentBetIndex]);
    ui->label_bet->setText(strBet);
}

bool MainWindow::check_blackJack()
{
    if(hand == 21 && enemyHand == 21) {
        qDebug() << "push";
        return true;
    }
    else if (hand == 21) {
        qDebug() << "plaeyr has blackJack";
        balance += betAmounts[currentBetIndex];
        return true;
    }
    else if (enemyHand == 21) {
        qDebug() << "diller had blackJack";
        balance -= betAmounts[currentBetIndex];
        return true;
    }
    return false;
}
