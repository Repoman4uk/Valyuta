#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    struct Tree
    {
        double moneyInCourse;
        int level;
        Tree *left;
        Tree *right;
    };

private slots:
    void on_table_cellChanged(int row, int column);

    void on_okButton_clicked();

    void on_pushBegin_clicked();

    void on_calculateButton_clicked();

private:
    Ui::MainWindow *ui;
    int beginCourse;
    Tree *root;
    void getMax(Tree *tree, QVector<int> track);
    double ** courses;
    int n;
    void deleteTree(Tree *tree);
    Tree *max;
    QVector <int> track;
    double getMoneyInFirst(QVector <int> tr,double some);
    QString showResults();
};

#endif // MAINWINDOW_H
