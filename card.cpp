#include "card.h"
#include <QPixmap>
#include <QLabel>
#include <QDebug>
#include <QVBoxLayout>

Card::Card(QObject *)
{}

Card::Card(QString suit, int rank): suit(suit), rank(rank)
{}

Card::Card(const Card &c): suit(c.suit), rank(c.rank)
{}

Card& Card::operator= (const Card& c)
{
    if (this == &c)
        return *this;

    this->suit = suit;
    this->rank = rank;

    return *this;
}


void swap(Card& c1, Card& c2)
{
    std::swap(c1.rank, c2.rank);
    std::swap(c1.suit, c2.suit);
}




void Card::draw_card(QWidget *parent, int x, int y)
{
    int card_width = 167;
    int card_height = 243;

    int x_offset = this->rank - 1, y_offset = 0;

    if(this->suit == "back") y_offset = 4, x_offset = 2; else
    if(this->suit[0] == 'D') y_offset = 1; else
    if(this->suit[0] == 'H') y_offset = 2; else
    if(this->suit[0] == 'S') y_offset = 3;

    if(this->rank == 10 && this->suit.size() > 1 && this->suit != "back")
    {
        if(this->suit[1] == 'J') x_offset = 10; else
        if(this->suit[1] == 'Q') x_offset = 11; else
        if(this->suit[1] == 'K') x_offset = 12;
    }


    int card_x = x_offset * card_width;
    int card_y = y_offset * card_height;


    QString url = "./images/cards.jpg";
    QPixmap card_pixmap(url);
    QLabel *label = new QLabel(parent);
    label->setPixmap(card_pixmap.copy(card_x, card_y, card_width, card_height));
    label->setScaledContents(true);
    label->resize(100, 150);
    label->move(x, y);

    label->show();
}

