#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "card.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public:
    int cardsCheck = 1;
    int hand = 0, enemyHand = 0;

private slots:
    void on_pushButton_hit_clicked();
    void on_pushButton_stand_clicked();
    void on_pushButton_continue_clicked();

private:
    QList<Card*> available_cards;
    QList<Card*> user_cards;
    QList<Card*> enemy_cards;

private:
    void update_cards();
    void update_hands();

    void user_pick_card();
    void enemy_pick_card();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
