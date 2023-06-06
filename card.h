#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QDebug>
#include <QLabel>



class Card : public QWidget
{
    Q_OBJECT
public:
    QString suit = "";
    int rank = 0;
    QLabel* card_img;

public:
    explicit Card(QObject *parent = nullptr);
    Card(QWidget* parent, QString suit, int rank = 0);
    ~Card();


public:
    void draw_card(int x, int y);


signals:

};

#endif // CARD_H
