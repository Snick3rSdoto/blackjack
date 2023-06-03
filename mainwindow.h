#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMultiMap>

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
    QMultiMap<QString, int> multiMap;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
