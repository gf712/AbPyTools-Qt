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
    // instantiate antibody object with empty constructor
    antibodyObjects = new AntibodyChainCPP();

    // opens new dialog to add sequence
    auto newSequenceDialogPointer = new newSequenceDialog(this);
    newSequenceDialogPointer->show();

    connect(newSequenceDialogPointer, SIGNAL(newSequenceDialogNameChange(std::string)), this,
            SLOT(newSequenceDialogNameGetter(std::string)));

    connect(newSequenceDialogPointer, SIGNAL(newSequenceDialogSequenceChange(std::string)), this,
            SLOT(newSequenceDialogSequenceGetter(std::string)));

    connect(newSequenceDialogPointer, SIGNAL(newSequenceDialogNumberingSchemeChange(std::string)), this,
            SLOT(newSequenceDialogNumberingSchemeGetter(std::string)));

    // debug window
//    timer = new QTimer(this);
//    timer->connect(timer, SIGNAL(timeout()), this, SLOT(refresh_values()));
//    timer->start(1000);

//    name = newSequenceDialogPointer->getDialogName();
//    sequence = newSequenceDialogPointer->getDialogSequence();
//    numberingScheme = newSequenceDialogPointer->getDialogNumberingScheme();

//    qDebug() << QString("name: %1\nsequence: %2\nnumbering scheme: %3").arg(QString::fromStdString(antibodyObjects->getName()),
//                                                                            QString::fromStdString(antibodyObjects->getSequence()),
//                                                                            QString::fromStdString(antibodyObjects->getNumberingScheme()));

}

void MainWindow::refresh_values() {

//    if (antibodyObjects != nullptr)
//
//        ui->debugAreaTextEdit->setText(QString("name: %1\nsequence: %2\nnumbering scheme: %3").arg(QString::fromStdString(antibodyObjects->getName()),
//                                                                                                   QString::fromStdString(antibodyObjects->getSequence()),
//                                                                                                   QString::fromStdString(antibodyObjects->getNumberingScheme())));

}

void MainWindow::newSequenceDialogNameGetter(std::string name_) {

    antibodyObjects->setName(name_);
}

void MainWindow::newSequenceDialogSequenceGetter(std::string sequence_) {
    antibodyObjects->setSequence(sequence_);
}

void MainWindow::newSequenceDialogNumberingSchemeGetter(std::string numberingScheme_) {
    antibodyObjects->setNumberingScheme(numberingScheme_);
}
