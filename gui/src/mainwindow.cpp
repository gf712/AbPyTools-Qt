#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chainGroups = new ChainGroups;
    antibodyObjects = new ChainCollectionCPP();
    ui->workingAreaTextBrowser->isReadOnly();
    ui->debugAreaTextBrowser->isReadOnly();

    startedWorking = false;

    // display welcome message in working and debug windows
    updateWorkingWindow();
    updateDebugWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// #####################################################################################################################
//                                          FILE MENU
// #####################################################################################################################

void MainWindow::on_actionNew_group_triggered()
{
    // creates new group
    auto newGroupDialogPointer = new NewGroupDialog(this);

    newGroupDialogPointer->show();

    connect(newGroupDialogPointer, SIGNAL(newGrupDialogButtonBoxAccepted(std::string, std::string)),
            this, SLOT(addChainGroup(std::string, std::string)));

}

void MainWindow::on_actionNew_triggered()
{
    // instantiate antibody object with empty constructor
    antibodyObject = new AntibodyChainCPP();

    // opens new dialog to add sequence
    auto newSequenceDialogPointer = new newSequenceDialog(this, chainGroups->getGroupNames());
    newSequenceDialogPointer->show();

    connect(newSequenceDialogPointer, SIGNAL(buttonBoxAccepted(std::string, std::string)),
            this, SLOT(addAntibodyObject(std::string, std::string)));

}

void MainWindow::on_actionOpen_triggered()
{

    QFileDialog dialog;

    QString filename = dialog.getOpenFileName(this, tr("Open FASTA File"),"",tr("FASTA files (*.fasta)"));

    fastaParser = new FastaParser(filename.toStdString());

    fastaParser->parse();

    loadFASTADebugText();
}


void MainWindow::addAntibodyObject(std::string name_, std::string sequence_) {

    qDebug() << "ACCEPTED BUTTON RECEIVED";

    antibodyObject->setName(name_);

    antibodyObject->setSequence(sequence_);

    antibodyObjects->append(*antibodyObject);

    // write to windows
    addAntibodyObjectText();
    addAntibodyObjectDebugText();

}

void MainWindow::addChainGroup(std::string groupName_, std::string numberingScheme_) {

    chainGroups->addGroup(groupName_, numberingScheme_);

    addGroupText(groupName_);
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

void MainWindow::addGroupText(std::string name) {

    auto text = QString("\nGroup name: %1\n -numbering scheme: %2\n -number of sequences: %3\n -loaded: %4");
    text = text.arg(QString::fromStdString(name),
                    QString::fromStdString(chainGroups->getNumberingScheme(name)),
                    QString::number(chainGroups->getNumberOfSequences(name)),
                    "false");

    if (!startedWorking) {
        cacheText.replace("Nothing to display", "");
        cacheText.append(text);
        startedWorking = true;
    }

    else {

        cacheText.append(text);

    }

    updateWorkingWindow();
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


void MainWindow::loadFASTADebugText() {

    auto debugText = QString("[%1]: loadFASTA\n Number of entries: %2\n");

    debugText = debugText.arg(QDateTime::currentDateTime().toString(),
                              QString::number(fastaParser->getNames().size()));

    qDebug() << debugText << fastaParser->getNames().size();

    cacheDebugText.append(debugText);
    updateDebugWindow();
}
