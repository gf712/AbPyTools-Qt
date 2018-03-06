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

    ui->plotSettingLayout->addWidget(new QLabel("Plot settings"), 0, 0);

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


void MainWindow::editGroup(std::string groupName_, std::string hydrophobicityDataSet, int numberingScheme) {

//    std::cout << groupName_ << hydrophobicityDataSet << numberingScheme;

    if (groupName_.compare("")) {

        qDebug() << "MAINWINDOW: \n"
                 << "numberingScheme: " << numberingSchemesVector[numberingScheme]
                 << "groupName: " << QString::fromStdString(groupName_)
                 << "hydrophobicityDataSet" << QString::fromStdString(hydrophobicityDataSet)
                 << hGroups->getDatasetNames();

        if (hydrophobicityDataSet.compare("")) {
            qDebug() << QString::fromStdString(hGroups->getHydrophobicityParser(hydrophobicityDataSet)->getBasename());
            // if this value isn't empty add the newly added hydrophobicity parser
            chainGroups->addHydrophobicityValues(groupName_, hGroups->getHydrophobicityParser(hydrophobicityDataSet));
        }
        chainGroups->setNumberingScheme(groupName_, numberingSchemesVector[numberingScheme]);
        updateWorkingWindowGroup();
    }

}


void MainWindow::sendHydophobicityDatasetNameToChildOnRequest(QString groupName_) {

    Q_EMIT sendHydophobicityDatasetNameToChildOnRequestSignal(chainGroups->getHydrophobicityParserName(groupName_.toStdString()));

}

// #####################################################################################################################
//                                               ANALYSIS MENU SLOTS
// #####################################################################################################################


void MainWindow::changeDatasetForPCA() {

    qDebug() << "Getting info from PCA plot combobox";

    // group has changed, replot PCs given values in xAxisData and yAxisData
    QComboBox *pc1Combobox = this->findChild<QComboBox*>("X_axis");
    QComboBox *pc2Combobox = this->findChild<QComboBox*>("Y_axis");
    QComboBox *nameCombobox = this->findChild<QComboBox*>("group_name");

    if (pc1Combobox == 0 or pc2Combobox == 0 or nameCombobox == 0) {
        qDebug() << "Could not find combobox";
        return;
    }
    else {
        qDebug() << "Found combobox";
    }


    qDebug() << "Got ui->plotSettingLayout children";

    int pc1 = pc1Combobox->currentIndex();
    int pc2 = pc2Combobox->currentIndex();
    QString groupname = nameCombobox->currentText();

    qDebug() << "Got current index";
    qDebug() << pc1 << pc2;

    auto x = chainGroups->getPrincipalComponent(groupname, pc1);
    auto y = chainGroups->getPrincipalComponent(groupname, pc2);

    ui->plotArea->graph(0)->setData(x, y);
    ui->plotArea->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->plotArea->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
//    ui->plotArea->rescaleAxes();
    ui->plotArea->xAxis->setRange(-1, 1);
    ui->plotArea->yAxis->setRange(-1, 1);

    ui->plotArea->replot();
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

void MainWindow::on_actionPlotPCA_triggered()
{

    auto *dataset = new QComboBox();
    auto *xAxisData = new QComboBox();
    auto *yAxisData = new QComboBox();

    dataset->setObjectName("group_name");
    xAxisData->setObjectName("X_axis");
    yAxisData->setObjectName("Y_axis");

    auto applyChanges = new QPushButton("Apply");

    for(auto const &name: chainGroups->getGroupNames()) {

        if (chainGroups->getPerformedPCA(name)) {
            // add group name if pca has been performed
            dataset->addItem(name);
        }
    }

    for (int i = 1; i < 10; ++i) {
        xAxisData->addItem(QString::number(i));
        yAxisData->addItem(QString::number(i));
    }

    xAxisData->setCurrentIndex(0);
    yAxisData->setCurrentIndex(1);

    ui->plotSettingLayout->addWidget(new QLabel("Group"), 1, 0);
    ui->plotSettingLayout->addWidget(dataset, 1, 1);
    ui->plotSettingLayout->addWidget(new QLabel("X-axis PC"), 2, 0);
    ui->plotSettingLayout->addWidget(xAxisData, 2, 1);
    ui->plotSettingLayout->addWidget(new QLabel("Y-axis PC"), 3, 0);
    ui->plotSettingLayout->addWidget(yAxisData, 3, 1);
    ui->plotSettingLayout->addWidget(applyChanges, 4, 1);

    ui->plotArea->addGraph();

    changeDatasetForPCA();

    connect(applyChanges, SIGNAL(clicked()), this, SLOT(changeDatasetForPCA()));
}

void MainWindow::on_actionApplyPCA_triggered()
{
    for(auto const &name: chainGroups->getGroupNames()) {

        qDebug() << "Checking: " << name;

        if (!chainGroups->getPerformedPCA(name)) {

            if (!chainGroups->getHasHDatabase(name)) {
                QMessageBox msgBox;
                msgBox.setText(QString("Group %1 does not have hydrophobicity values assigned to it!").arg(name));
                msgBox.exec();
                return;
            }

            try {
                // perform PCA on first 10 dims
                qDebug() << "Applying PCA to: " << name;
                chainGroups->performPCA(name, 10);
            }

            catch (ChainSequenceNotNumberedException) {
                QMessageBox msgBox;
                msgBox.setText(QString("Numbering was not applied to group %1!").arg(name));
                msgBox.exec();
                return;
            }
        }
    }
}
