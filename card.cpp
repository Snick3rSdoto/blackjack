#include "card.h"
#include <QPixmap>
#include <QLabel>
#include <QDebug>

Card::Card(QObject *)
{}

Card::Card(QWidget* parent, QString suit, int rank): QWidget(parent), suit(suit), rank(rank)
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
    card_img = new QLabel(parent);
    card_img->setPixmap(card_pixmap.copy(card_x, card_y, card_width, card_height));
    card_img->setScaledContents(true);
    card_img->resize(100, 150);
    card_img->hide();

}



Card::~Card()
{
    this->card_img->deleteLater();
}


void Card::draw_card(int x, int y)
{
    this->card_img->move(x, y);
    this->card_img->raise();
    this->card_img->show();
}
