#include "mainwindow.h"
#include "ui_mainwindow.h"

// static variable definitions
constexpr std::array<char[15], 3> MainWindow::numberingSchemesVector;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chainGroups = new ChainGroups;
    hGroups = new hydrophobicityGroups;
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
//                                               FILE MENU SLOTS
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
//    antibodyObject = new AntibodyChainCPP();

    // opens new dialog to add sequence
    auto newSequenceDialogPointer = new newSequenceDialog(this, chainGroups->getGroupNames());
    newSequenceDialogPointer->show();

    connect(newSequenceDialogPointer, SIGNAL(buttonBoxAccepted(std::string, std::string, std::string)),
            this, SLOT(addAntibodyObject(std::string, std::string, std::string)));

}

void MainWindow::on_actionOpen_triggered()
{

    auto fileLoaderPointer = new FileLoaderDialog(this, chainGroups->getGroupNames());

    fileLoaderPointer->show();

    connect(fileLoaderPointer, SIGNAL(fileLoaderDialogFilename(std::string, QString)),
            this, SLOT(addFASTA(std::string, QString)));
}

// #####################################################################################################################
//                                               ANALYSIS MENU SLOTS
// #####################################################################################################################


void MainWindow::on_actionApply_Numbering_triggered()
{

    chainGroups->applyNumbering();

    updateWorkingWindowGroup();
}

void MainWindow::on_actionImport_hydrophobicity_dataset_triggered()
{
    // load hydrophobicity dataset
    // open file dialog to choose FASTA file
    QFileDialog dialog;
    QString filename = dialog.getOpenFileName(this, tr("Open Hydrophobicity Data File"),"",tr("hpb files (*.hpb)"));

    bool response = hGroups->parseNewFile(filename.toStdString());

    QMessageBox msgBox;

    if (response) {

        QFileInfo fi(filename);

        msgBox.setText("Successfully loaded hpb file!");
    }
    else
        msgBox.setText("Failed to load hpb file!");
    msgBox.exec();
}


void MainWindow::addAntibodyObject(std::string name_, std::string sequence_, std::string groupName) {

    qDebug() << "ACCEPTED BUTTON RECEIVED";

    qDebug() << QString::fromStdString(groupName) << QString::fromStdString(name_) << QString::fromStdString(sequence_);
    chainGroups->addChain(groupName, name_, sequence_);

    qDebug() << "ADDED CHAIN";
    
    // write to windows
//    addAntibodyObjectText(groupName);
//    addAntibodyObjectDebugText();

}

void MainWindow::addChainGroup(std::string groupName_, std::string numberingScheme_) {

    chainGroups->addGroup(groupName_, numberingScheme_);

    updateWorkingWindowGroup();
}


void MainWindow::addFASTA(std::string groupName_, QString filename_) {

    qDebug() << "Parsing FASTA file";

    fastaParser = new FastaParser(filename_.toStdString());

    fastaParser->parse();

    qDebug() << "Parsed FASTA file";

    std::string name_i, sequence_i;

    auto names = fastaParser->getNames();
    auto sequences = fastaParser->getSequences();

    // it's like python in C++..
    BOOST_FOREACH(boost::tie(name_i, sequence_i), boost::combine(names, sequences)) {

        qDebug() << QString::fromStdString(name_i) << QString::fromStdString(sequence_i);

        addAntibodyObject(name_i, sequence_i, groupName_);

        auto chainObject = new AntibodyChainCPP(sequence_i, name_i, "chothia");

        addAntibodyObjectDebugText(chainObject);
    }

    updateWorkingWindowGroup();

}


// #####################################################################################################################
//                                               EDIT MENU SLOTS
// #####################################################################################################################


void MainWindow::on_actionGroup_triggered()
{

    auto editGroupPointer = new editDialog(this);

    editGroupPointer->show();

    // receive new settings when pressing OK
    connect(editGroupPointer, SIGNAL(editDialogUpdateGroup(std::string, std::string, int)),
            this, SLOT(editGroup(std::string, std::string, int)));

    connect(this, SIGNAL(sendGroupNamesToChild(QStringList)),
            editGroupPointer, SLOT(receiveGroupNamesFromParent(QStringList)));

    connect(this, SIGNAL(sendHydrophobicityDatasetNamesToChild(QStringList)),
            editGroupPointer, SLOT(receiveHydrophobicityDatasetNamesFromParent(QStringList)));

    connect(this, SIGNAL(sendNumberingSchemeNames(QStringList)),
            editGroupPointer, SLOT(receiveNumberingSchemeNamesFromParent(QStringList)));

    // receive message about changed group
//    connect(editGroupPointer, SIGNAL(),
//            this, SLOT());

    // and change text accordingly using signal
//    connect(editGroupPointer, SIGNAL(),
//            this, SLOT());

    QStringList numberingSchemes;
    numberingSchemes << "Chothia" << "Kabat" << "Martin";
    
    Q_EMIT(sendGroupNamesToChild(chainGroups->getGroupNames()));
    Q_EMIT(sendHydrophobicityDatasetNamesToChild(hGroups->getDatasetNames()));
    Q_EMIT(sendNumberingSchemeNames(numberingSchemes));

}


void MainWindow::sendHydophobicityDatasetNameToChildOnRequest(QString groupName_) {

    Q_EMIT sendHydophobicityDatasetNameToChildOnRequestSignal(chainGroups->getHydrophobicityParserName(groupName_.toStdString()));

}


void MainWindow::editGroup(std::string groupName_, std::string hydrophobicityDataSet, int numberingScheme) {

    std::cout << groupName_ << hydrophobicityDataSet << numberingScheme;

    chainGroups->addHydrophobicityValues(groupName_, hGroups->getHydrophobicityParser(groupName_));
    chainGroups->setNumberingScheme(groupName_, numberingSchemesVector[numberingScheme]);

    updateWorkingWindowGroup();
}


// #####################################################################################################################
//                                          MESSAGE DISPLAY ROUTINES
// #####################################################################################################################

void MainWindow::updateWorkingWindow() {

    ui->workingAreaTextBrowser->setText(cacheText);

}

void MainWindow::updateDebugWindow() {

    qDebug() << "Updating debug window";

    ui->debugAreaTextBrowser->setText(cacheDebugText);

}

//void MainWindow::addAntibodyObjectText(std::string name_) {
//
//    addGroupText(name_);
//
//}

//void MainWindow::addGroupText(std::string name) {
//
//    auto text = QString("\nGroup name: %1\n -numbering scheme: %2\n -number of sequences: %3\n -loaded: %4");
//    text = text.arg(QString::fromStdString(name),
//                    QString::fromStdString(chainGroups->getNumberingScheme(name)),
//                    QString::number(chainGroups->getNumberOfSequences(name)),
//                    "false");
//
//    if (!startedWorking) {
//        cacheText.replace("Nothing to display", "");
//        cacheText.append(text);
//        startedWorking = true;
//    }
//
//    else {
//
//        cacheText.append(text);
//
//    }
//
//    updateWorkingWindow();
//}

void MainWindow::updateWorkingWindowGroup() {

    qDebug() << "Updating working window...";

    cacheText = "Welcome to AbPyTools-Qt:\n"
                "------------------------\n";

    for (auto const &name: chainGroups->getGroupNames()) {

        cacheText.append(chainGroups->getInfo(name));

    }

    updateWorkingWindow();

}

void MainWindow::addAntibodyObjectDebugText(AntibodyChainCPP *object_) {

    qDebug() << "Reached addAntibodyObjectDebugText";

    auto debugText = QString("[%1]: addAntibodyObject\n name: %2\n sequence: %3\n numbering scheme: %4\n");

    debugText = debugText.arg(QDateTime::currentDateTime().toString(),
                              QString::fromStdString(object_->getName()),
                              QString::fromStdString(object_->getSequence()),
                              QString::fromStdString(object_->getNumberingScheme()));

    qDebug() << debugText;

    cacheDebugText.append(debugText);

    updateDebugWindow();

}


void MainWindow::loadFASTADebugText() {

    auto debugText = QString("[%1]: loadFASTA\n Number of entries: %2\n");

    debugText = debugText.arg(QDateTime::currentDateTime().toString(),
                              QString::number(fastaParser->getNames().size()));

    qDebug() << debugText << fastaParser->getNames().size();

    cacheDebugText.append(debugText);
    updateDebugWindow();
}
