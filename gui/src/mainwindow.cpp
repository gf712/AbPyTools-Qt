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
    antibodyObject = new AntibodyChainCPP();

    // opens new dialog to add sequence
    auto newSequenceDialogPointer = new newSequenceDialog(this);
    newSequenceDialogPointer->show();

    connect(newSequenceDialogPointer, SIGNAL(buttonBoxAccepted(std::string, std::string, std::string)),
            this, SLOT(addAntibodyObject(std::string, std::string, std::string)));


}

void MainWindow::addAntibodyObject(std::string name_, std::string sequence_, std::string numberingScheme_) {

    qDebug() << "BUTTON ACCEPTED RECEIVED";

    antibodyObject->setName(name_);

    antibodyObject->setSequence(sequence_);

    antibodyObject->setNumberingScheme(numberingScheme_);

    ui->debugAreaTextEdit->setText(QString("name: %1\nsequence: %2\nnumbering scheme: %3").arg(QString::fromStdString(antibodyObject->getName()),
                                                                                               QString::fromStdString(antibodyObject->getSequence()),
                                                                                               QString::fromStdString(antibodyObject->getNumberingScheme())));

}
