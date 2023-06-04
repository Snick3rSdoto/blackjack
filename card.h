#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QDebug>



class Card : public QObject
{
    Q_OBJECT
public:
    QString suit = "";
    int rank = 0;

public:
    explicit Card(QObject *parent = nullptr);
    Card(QString suit, int rank = 0);
    Card(const Card& c);
    Card& operator= (const Card& card);

    // Needs to be implemented in order to use std::random_shuffle
    friend void swap(Card& c1, Card& c2);


public:
    void draw_card(QWidget* parent, int x, int y);


signals:

};

#endif // CARD_H
