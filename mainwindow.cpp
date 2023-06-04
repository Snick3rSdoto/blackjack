
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QDebug>
#include <QPainter>
#include <random>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->update_cards();

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
    Card player_card =  this->available_cards.takeFirst();
    player_card.draw_card(this, 200, 300);













}


void MainWindow::on_pushButton_stand_clicked() {

}

void MainWindow::update_cards()
{
    this->available_cards.clear();

    this->available_cards = {
        {"D", 1}, {"H", 1}, {"C", 1}, {"S", 1},
        {"D", 2}, {"H", 2}, {"C", 2}, {"S", 2},        // D - (Бубы / Алмазы)
        {"D", 3}, {"H", 3}, {"C", 3}, {"S", 3},        // H - (Черви / Сердца)
        {"D", 4}, {"H", 4}, {"C", 4}, {"S", 4},        // C - (Трефы / Клубы)
        {"D", 5}, {"H", 5}, {"C", 5}, {"S", 5},        // S - (Пики / Лопаты)
        {"D", 6}, {"H", 6}, {"C", 6}, {"S", 6},        //------------------------
        {"D", 7}, {"H", 7}, {"C", 7}, {"S", 7},        // J - (Валет / Джек)
        {"D", 8}, {"H", 8}, {"C", 8}, {"S", 8},        // Q - (Дама / Королева)
        {"D", 9}, {"H", 9}, {"C", 9}, {"S", 9},        // K - (Король)
        {"D", 10},{"H", 10},{"C", 10},{"S", 10},       // A - (Туз)
        {"DJ", 10},{"HJ", 10},{"CJ", 10},{"SJ", 10},
        {"DQ", 10},{"HQ", 10},{"CQ", 10},{"SQ", 10},
        {"DK", 10},{"HK", 10},{"CK", 10},{"SK", 10},
         };

    std::random_shuffle(this->available_cards.begin(), this->available_cards.end());
}

void MainWindow::update_cards_on_hands()
{
//    this->cards_on_hands.clear();
}















