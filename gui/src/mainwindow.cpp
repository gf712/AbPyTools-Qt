#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{

}


void MainWindow::on_actionNew_triggered()
{
    newSequenceDialogPointer = new newSequenceDialog(this);
    newSequenceDialogPointer->show();

//    name = newSequenceDialogPointer->getDialogName();
//    sequence = newSequenceDialogPointer->getDialogSequence();
//    numberingScheme = newSequenceDialogPointer->getDialogNumberingScheme();

//    qDebug() << QString("name: %1\nsequence: %2\nnumbering scheme: %3").arg(QString::fromStdString(name),
//                                                                            QString::fromStdString(sequence),
//                                                                            QString::fromStdString(numberingScheme));

}

void MainWindow::refresh_values() {

    ui->debugAreaTextEdit->setText(QString("name: %1\nsequence: %2\nnumbering scheme: %3").arg(QString::fromStdString(name),
                                                                                               QString::fromStdString(sequence),
                                                                                               QString::fromStdString(numberingScheme)));

}
