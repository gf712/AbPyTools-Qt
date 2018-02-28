#include <QtCore/QDateTime>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    antibodyObjects = new ChainCollectionCPP();
    ui->workingAreaTextBrowser->isReadOnly();
    ui->debugAreaTextBrowser->isReadOnly();

    startedWorking = false;

    // display welcome message in working window
    updateWorkingWindow();
    updateDebugWindow();
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

    connect(newSequenceDialogPointer, SIGNAL(buttonBoxAccepted()),
            this, SLOT(updateDebugWindow()));

    connect(newSequenceDialogPointer, SIGNAL(buttonBoxAccepted()),
            this, SLOT(updateWorkingWindow()));

}

void MainWindow::addAntibodyObject(std::string name_, std::string sequence_, std::string numberingScheme_) {

    qDebug() << "ACCEPTED BUTTON RECEIVED";

    antibodyObject->setName(name_);

    antibodyObject->setSequence(sequence_);

    antibodyObject->setNumberingScheme(numberingScheme_);

    antibodyObjects->append(*antibodyObject);

    // write to windows
    addAntibodyObjectText();
    addAntibodyObjectDebugText();

}

void MainWindow::updateWorkingWindow() {

    ui->workingAreaTextBrowser->setText(cacheText);

}

void MainWindow::updateDebugWindow() {

    qDebug() << "Updating debug window";

    ui->debugAreaTextBrowser->setText(cacheDebugText);

}

// #####################################################################################################################
//                                          MESSAGE DISPLAY ROUTINES
// #####################################################################################################################


void MainWindow::addAntibodyObjectText() {

    QRegularExpression re("Loaded antibody chains: \\d+");

    auto text = QString("Loaded antibody chains: %1");
    text = text.arg(antibodyObjects->getNumberOfChains());

    if (!startedWorking) {
        cacheText.replace("Nothing to display", "");
        cacheText.append(text);
        startedWorking = true;
    }

    else
        cacheText.replace(re, text);

}

void MainWindow::addAntibodyObjectDebugText() {

    auto debugText = QString("[%1]: addAntibodyObject\n name: %2\n sequence: %3\n numbering scheme: %4\n");

    debugText = debugText.arg(QDateTime::currentDateTime().toString(),
                              QString::fromStdString(antibodyObject->getName()),
                              QString::fromStdString(antibodyObject->getSequence()),
                              QString::fromStdString(antibodyObject->getNumberingScheme()));

    qDebug() << debugText;

    cacheDebugText.append(debugText);

}