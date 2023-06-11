#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    player = new QMediaPlayer;
    player->setMedia(QUrl(":/music/background.mp3"));
    player->setVolume(50);
    player->play();

    Card *deck = new Card(this, "back");
    deck->draw_card(DECK_X, DECK_Y);

    this->winLabel = new QLabel(this);
    this->loseLabel = new QLabel(this);

    this->winLabel->setPixmap(QPixmap(":/images/win.png"));
    this->winLabel->setScaledContents(true);
    this->winLabel->resize(300, 200);
    this->winLabel->move(300, 250);

    this->loseLabel->setPixmap(QPixmap(":/images/lose.png"));
    this->loseLabel->setScaledContents(true);
    this->loseLabel->resize(300, 200);
    this->loseLabel->move(300, 250);

    this->winLabel->hide();
    this->loseLabel->hide();



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
            this->win();
            this->ui->pushButton_hit->setEnabled(false);
            this->ui->pushButton_stand->setEnabled(false);
            this->ui->pushButton_continue->setEnabled(true);

            balance += betAmounts[currentBetIndex];
            this->update_balance();
            this->ui->pushButton_minusBet->setEnabled(true);
            this->ui->pushButton_plusBet->setEnabled(true);


        }
        else if (hand > 21) {
            this->lose();
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
    QSharedPointer<Card> c = this->enemy_cards.takeLast();
    c->card_img->deleteLater();

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
            this->lose();
            balance -= betAmounts[currentBetIndex];
            this->update_balance();
            this->ui->pushButton_minusBet->setEnabled(true);
            this->ui->pushButton_plusBet->setEnabled(true);
            break;
        }
        else if (enemyHand == hand && enemyHand > 16) {
//            qDebug() << "push";
            this->ui->pushButton_minusBet->setEnabled(true);
            this->ui->pushButton_plusBet->setEnabled(true);
            break;
        }
        else if (enemyHand > 21) {
            this->win();
            balance += betAmounts[currentBetIndex];
            this->update_balance();
            this->ui->pushButton_minusBet->setEnabled(true);
            this->ui->pushButton_plusBet->setEnabled(true);
            break;
        }
        else if (enemyHand < hand && enemyHand > 16) {
            this->win();
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
    this->winLabel->hide();
    this->loseLabel->hide();
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
        QSharedPointer<Card>(new Card(this, "D", 1)), QSharedPointer<Card>(new Card(this, "H", 1)), QSharedPointer<Card>(new Card(this, "C", 1)), QSharedPointer<Card>(new Card(this, "S", 1)),        // D - (Бубы / Алмазы))
        QSharedPointer<Card>(new Card(this, "D", 2)), QSharedPointer<Card>(new Card(this, "H", 2)), QSharedPointer<Card>(new Card(this, "C", 2)), QSharedPointer<Card>(new Card(this, "S", 2)),        // H - (Черви / Сердца))
        QSharedPointer<Card>(new Card(this, "D", 3)), QSharedPointer<Card>(new Card(this, "H", 3)), QSharedPointer<Card>(new Card(this, "C", 3)), QSharedPointer<Card>(new Card(this, "S", 3)),        // C - (Трефы / Клубы))
        QSharedPointer<Card>(new Card(this, "D", 4)), QSharedPointer<Card>(new Card(this, "H", 4)), QSharedPointer<Card>(new Card(this, "C", 4)), QSharedPointer<Card>(new Card(this, "S", 4)),        // S - (Пики / Лопаты))
        QSharedPointer<Card>(new Card(this, "D", 5)), QSharedPointer<Card>(new Card(this, "H", 5)), QSharedPointer<Card>(new Card(this, "C", 5)), QSharedPointer<Card>(new Card(this, "S", 5)),        //------------------------
        QSharedPointer<Card>(new Card(this, "D", 6)), QSharedPointer<Card>(new Card(this, "H", 6)), QSharedPointer<Card>(new Card(this, "C", 6)), QSharedPointer<Card>(new Card(this, "S", 6)),        // J - (Валет / Джек))
        QSharedPointer<Card>(new Card(this, "D", 7)), QSharedPointer<Card>(new Card(this, "H", 7)), QSharedPointer<Card>(new Card(this, "C", 7)), QSharedPointer<Card>(new Card(this, "S", 7)),        // Q - (Дама / Королева))
        QSharedPointer<Card>(new Card(this, "D", 8)), QSharedPointer<Card>(new Card(this, "H", 8)), QSharedPointer<Card>(new Card(this, "C", 8)), QSharedPointer<Card>(new Card(this, "S", 8)),        // K - (Король))
        QSharedPointer<Card>(new Card(this, "D", 9)), QSharedPointer<Card>(new Card(this, "H", 9)), QSharedPointer<Card>(new Card(this, "C", 9)), QSharedPointer<Card>(new Card(this, "S", 9)),        // A - (Туз))
        QSharedPointer<Card>(new Card(this, "D", 10)),QSharedPointer<Card>(new Card(this, "H", 10)),QSharedPointer<Card>(new Card(this, "C", 10)),QSharedPointer<Card>(new Card(this, "S", 10)),
        QSharedPointer<Card>(new Card(this, "DJ", 10)),QSharedPointer<Card>(new Card(this, "HJ", 10)),QSharedPointer<Card>(new Card(this, "CJ", 10)),QSharedPointer<Card>(new Card(this, "SJ", 10)),
        QSharedPointer<Card>(new Card(this, "DQ", 10)),QSharedPointer<Card>(new Card(this, "HQ", 10)),QSharedPointer<Card>(new Card(this, "CQ", 10)),QSharedPointer<Card>(new Card(this, "SQ", 10)),
        QSharedPointer<Card>(new Card(this, "DK", 10)),QSharedPointer<Card>(new Card(this, "HK", 10)),QSharedPointer<Card>(new Card(this, "CK", 10)),QSharedPointer<Card>(new Card(this, "SK", 10)),
    };
    qDebug() << "====";
    std::random_shuffle(this->available_cards.begin(), this->available_cards.end());
}


void MainWindow::update_hands()
{
    qDebug() << "----";

    this->user_cards.clear();
    this->hand = 0;
    this->user_pick_card();
    this->user_pick_card();

    this->enemy_cards.clear();
    this->enemyHand = 0;
    this->enemy_pick_card();
    this->enemy_pick_card();
    enemy_pick_back();

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

    QSharedPointer<Card> card = this->available_cards.takeLast();

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

    QSharedPointer<Card> card = this->available_cards.takeLast();

    if (card->rank == 1) {
        enemyHand += 11;
        enemyAce++;
    }
    else { enemyHand += card->rank; }

    card->draw_card(posCard, 50);

    enemy_cards.append(card);
}


void MainWindow::enemy_pick_back()
{
    QSharedPointer<Card> dealerCard2Back(new Card(this, "back"));
    dealerCard2Back->draw_card(430, 50);
    enemy_cards.append(dealerCard2Back);
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
        this->win();
        balance += betAmounts[currentBetIndex];
        this->update_balance();
        return true;
    }
    else if (enemyHand == 21) {
        qDebug() << "dealler has blackJack";
        lose();
        balance -= betAmounts[currentBetIndex];

        QSharedPointer<Card> c = this->enemy_cards.takeLast();
        c->card_img->deleteLater();

        this->update_balance();
        return true;
    }
    return false;
}

void MainWindow::win()
{
    this->winLabel->show();
}

void MainWindow::lose()
{
    this->loseLabel->show();
}

