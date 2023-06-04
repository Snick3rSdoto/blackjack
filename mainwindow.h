#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>
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

private slots:
    void on_pushButton_hit_clicked();
    void on_pushButton_stand_clicked();

private:
    QList<Card> available_cards;
    QList<Card> user_cards;
    QList<Card> enemy_cards;

private:
    void update_cards();
    void update_cards_on_hands();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
