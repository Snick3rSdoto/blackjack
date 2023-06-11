#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "card.h"
#include <QMediaPlayer>

const int DECK_X = 800;
const int DECK_Y = 20;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
private:
    int hand = 0, enemyHand = 0;
    int ace = 0, enemyAce = 0;
    int balance = 50000;
    int currentBetIndex = 0;
    const int betAmounts[5] = {5, 10, 25, 50, 100};
    QPointer<QMediaPlayer> player;
    Ui::MainWindow *ui;

private slots:
    void on_pushButton_hit_clicked();
    void on_pushButton_stand_clicked();
    void on_pushButton_continue_clicked();

    void on_pushButton_minusBet_clicked();
    void on_pushButton_plusBet_clicked();

    bool check_blackJack();

private:
    QList<QSharedPointer<Card>> available_cards;
    QList<QSharedPointer<Card>> user_cards;
    QList<QSharedPointer<Card>> enemy_cards;
    QPointer<QLabel> winLabel;
    QPointer<QLabel> loseLabel;

private:
    void win();
    void lose();

    void update_cards();
    void update_hands();
    void update_balance();

    void user_pick_card();
    void enemy_pick_card();
    void enemy_pick_back();
};

#endif // MAINWINDOW_H
