#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    root=0;
    courses=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_table_cellChanged(int row, int column)
{
    if (row==column) return;
    if ( ui->table->item(column,row)==0)
    {
        QTableWidgetItem *item=new QTableWidgetItem(QString::number(1/(ui->table->item(row,column)->text().toDouble())));
        ui->table->setItem(column,row,item);
    }
    else ui->table->item(column,row)->setText(QString::number(1/(ui->table->item(row,column)->text().toDouble())));
}

void MainWindow::on_okButton_clicked()
{
    n=ui->countLine->text().toInt();
    ui->table->setRowCount(n);
    ui->table->setColumnCount(n);
    for (int i=0;i<n;i++)
    {
        QTableWidgetItem *item=new QTableWidgetItem("1");
        ui->table->setItem(i,i,item);
    }
}

void MainWindow::on_pushBegin_clicked()
{
    beginCourse=ui->lineBegin->text().toInt()-1;
}
double MainWindow::getMoneyInFirst(QVector<int> tr,double some)
{
    return some*courses[(tr.size()==0? 0 : tr.last())][0];
}

void MainWindow::getMax(Tree *tree,QVector <int> track)
{
    if (tree->level==n-1)
    {
        if (max->moneyInCourse<getMoneyInFirst(track,tree->moneyInCourse))
        {
            this->track=track;
            max=tree;
        }
    }
    else
    {
        tree->left=new Tree;
        tree->left->moneyInCourse=tree->moneyInCourse;
        tree->left->left=0;
        tree->left->right=0;
        tree->left->level=tree->level+1;
        getMax(tree->left,track);
        tree->right=new Tree;
        if (track.size()==0)
        {
            tree->right->moneyInCourse=courses[0][tree->level+1]*tree->moneyInCourse;
        }
        else
        {
            tree->right->moneyInCourse=courses[track.last()][tree->level+1]*tree->moneyInCourse;
        }
        tree->right->right=0;
        tree->right->left=0;
        tree->right->level=tree->level+1;
        track.append(tree->level+1);
        getMax(tree->right,track);
    }
}
QString MainWindow::showResults()
{
    QString tmp="1,";
    for (int i=0;i<track.size();i++) tmp+=QString::number(track[i]+1)+",";
    tmp+="1";
    return tmp;
}

void MainWindow::deleteTree(Tree *tree)
{
    if (tree->left)deleteTree(tree->left);
    if (tree->right)deleteTree(tree->right);
    delete tree;
}

void MainWindow::on_calculateButton_clicked()
{
    track.clear();
    if (courses) delete courses;
    courses=new double*[ui->table->rowCount()];
    for (int i=0;i<ui->table->rowCount();i++)
    {
        courses[i]=new double[ui->table->rowCount()];
    }
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++) courses[i][j]=ui->table->item(i,j)->text().toDouble();
    }
    if (root) deleteTree(root);
    root=new Tree;
    root->left=0;
    root->right=0;
    root->moneyInCourse=ui->lineBegin->text().toDouble();
    root->level=0;
    max=root;
    QVector<int> some;
    getMax(root,some);
    ui->result->append(showResults());
    ui->result->append(QString::number(max->moneyInCourse));
}

