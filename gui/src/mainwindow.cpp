#include "mainwindow.h"
#include "ui_mainwindow.h"

// static variable definitions
constexpr std::array<char[15], 3> MainWindow::numberingSchemesVector;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Q_INIT_RESOURCE(sprites);

    ui->setupUi(this);

    startApp();

}

MainWindow::~MainWindow()
{
    Q_CLEANUP_RESOURCE(sprites);
    delete ui;
}
// #####################################################################################################################
//                                                  MAIN ROUTINES
// #####################################################################################################################

void MainWindow::startApp() {

    chainGroups = new ChainGroups();
    hGroups = new hydrophobicityGroups();

    ui->workingAreaTextBrowser->isReadOnly();
    ui->debugAreaTextBrowser->isReadOnly();
    ui->iconLayout->setAlignment(Qt::AlignRight);

    // display welcome message in working and debug windows
    updateWorkingWindow();
    updateDebugWindow();
    startedWorking = false;

    // routines that live throughout the application
    startConnection(); // starts connection thread
    plotSettings(); // plot settings
}


void MainWindow::startConnection() {

    // starts thread to check internet connection
    auto connectedPixmap = QPixmap(":/Sprites/Checkmark.png");
    abnumConnected = new QLabel();
    abnumConnected->setPixmap(connectedPixmap.scaled(15, 20, Qt::IgnoreAspectRatio,
                                                     Qt::FastTransformation));

    auto notConnectedPixmap = QPixmap(":/Sprites/Close-checkmark.png");
    abnumNotConnected = new QLabel();
    abnumNotConnected->setPixmap(notConnectedPixmap.scaled(15, 20, Qt::IgnoreAspectRatio,
                                                           Qt::FastTransformation));

    auto *connectionThread = new QThread();
    auto *abnumConnection = new abnumConnectionWorker();

    abnumConnection->moveToThread(connectionThread);

    connect(connectionThread, SIGNAL(started()), abnumConnection, SLOT(checkConnection()));
    connect(abnumConnection, SIGNAL(connectionStatus(bool)), this, SLOT(update_abnum_connection(bool)));

    connectionThread->start();
}


void MainWindow::plotSettings() {

    ui->plotSettingLayoutPermanent->setVerticalSpacing(1);
    ui->plotSettingLayoutCustom->setVerticalSpacing(1);

    // populate titles
    ui->plotSettingLayoutPermanent->addWidget(new QLabel("Plot settings"), 0, 0,  Qt::AlignTop);
    ui->plotSettingLayoutCustom->addWidget(new QLabel("Analyis plot settings"), 0, 0, Qt::AlignTop);

    // populates plot settings that are in every plot
    xAxisRangeLower = new QDoubleSpinBox();
    xAxisRangeUpper = new QDoubleSpinBox();
    yAxisRangeLower = new QDoubleSpinBox();
    yAxisRangeUpper = new QDoubleSpinBox();

    xAxisRangeLower->setRange(-10e6, 10e6);
    xAxisRangeUpper->setRange(-10e6, 10e6);
    yAxisRangeLower->setRange(-10e6, 10e6);
    yAxisRangeUpper->setRange(-10e6, 10e6);

    xAxisRangeLower->setValue(-1.0);
    xAxisRangeUpper->setValue( 1.0);
    yAxisRangeLower->setValue(-1.0);
    yAxisRangeUpper->setValue( 1.0);

    // Display x-axis range buttons
    ui->plotSettingLayoutPermanent->addWidget(new QLabel("X-axis"), 1, 0);
    ui->plotSettingLayoutPermanent->addWidget(new QLabel("Lower range"), 2, 0);
    ui->plotSettingLayoutPermanent->addWidget(xAxisRangeLower, 2, 1);
    ui->plotSettingLayoutPermanent->addWidget(new QLabel("Upper range"), 3, 0);
    ui->plotSettingLayoutPermanent->addWidget(xAxisRangeUpper, 3, 1);

    // Display y-axis range
    ui->plotSettingLayoutPermanent->addWidget(new QLabel("Y-axis"), 4, 0);
    ui->plotSettingLayoutPermanent->addWidget(new QLabel("Lower range"), 5, 0);
    ui->plotSettingLayoutPermanent->addWidget(yAxisRangeLower, 5, 1);
    ui->plotSettingLayoutPermanent->addWidget(new QLabel("Upper range"), 6, 0);
    ui->plotSettingLayoutPermanent->addWidget(yAxisRangeUpper, 6, 1);

    connect(xAxisRangeLower, SIGNAL(editingFinished()), this, SLOT(adjustXAxisLower()));
    connect(xAxisRangeUpper, SIGNAL(editingFinished()), this, SLOT(adjustXAxisUpper()));
    connect(yAxisRangeLower, SIGNAL(editingFinished()), this, SLOT(adjustYAxisLower()));
    connect(yAxisRangeUpper, SIGNAL(editingFinished()), this, SLOT(adjustYAxisUpper()));

    adjustXAxisLower();
    adjustXAxisUpper();
    adjustYAxisLower();
    adjustYAxisUpper();
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
    auto *pbar = new QProgressDialog("Numbering sequences.", "Cancel", 0, 100);
    pbar->show();

    auto *pBarhelperTimer = new QTimer(this);
    // update progress bar every 500ms
    pBarhelperTimer->start(500);

    // create thread to run chain numbering thread and use watcher to handle signals and slots
    QFuture<void> future = QtConcurrent::run(this, &MainWindow::numbering_helper);
    QFutureWatcher<void> watcher;

    // update progress bar
    // connect timer to slot that processes chainGroup progress
    connect(pBarhelperTimer, SIGNAL(timeout()), this, SLOT(pbar_numbering()));
    // which in turn sends back pbar_numbering_helper_signal(int) signal with progress value
    connect(this, SIGNAL(pbar_numbering_helper_signal(int)), pbar, SLOT(setValue(int)));

    // destroy thread if process is cancelled
    connect(pbar, SIGNAL(canceled()), &watcher, SLOT(cancel()));

    // when thread ends need to:
    // - cancel dialog -> hides it
    // - stop timer
    // - update working window
//    connect(&watcher, SIGNAL(finished()), pbar, SLOT(cancel()));
//    connect(&watcher, SIGNAL(finished()), pBarhelperTimer, SLOT(stop()));
//    connect(&watcher, SIGNAL(finished()), this, SLOT(updateWorkingWindowGroup()));
    connect(this, SIGNAL(numbering_helper_completed()), pbar, SLOT(cancel()));
    connect(this, SIGNAL(numbering_helper_completed()), pBarhelperTimer, SLOT(stop()));
    connect(this, SIGNAL(numbering_helper_completed()), this, SLOT(updateWorkingWindowGroup()));

    // assign future to watcher
    watcher.setFuture(future);
}

void MainWindow::numbering_helper() {

    // running this with a slot allows to determine order
    // in which qt slots are called before the numbering starts
    chainGroups->applyNumbering(0);

    qDebug() << "COMPLETED NUMBERING";

    Q_EMIT(numbering_helper_completed());
}


void MainWindow::pbar_numbering() {

    qDebug() << static_cast<int>(std::ceil(chainGroups->numberingProgress()));

    auto progress = static_cast<int>(std::ceil(chainGroups->numberingProgress()));

    Q_EMIT(pbar_numbering_helper_signal(progress));

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

    auto *pbar = new QProgressDialog("Loading sequences.", "Cancel", 0, 100);

    auto *pBarhelperTimer = new QTimer(this);
    pbar->show();

    pBarhelperTimer->setProperty("groupName", QString::fromStdString(groupName_));
    // update progress bar every 1 ms
    pBarhelperTimer->start(1);

    // create thread to run chain numbering thread and use watcher to handle signals and slots
    QFuture<void> future = QtConcurrent::run(this, &MainWindow::addFASTA_helper, groupName_, filename_);
    QFutureWatcher<void> watcher;

    // assign future to watcher
    watcher.setFuture(future);

    // update progress bar
    // connect timer to slot that processes chainGroup progress
    connect(pBarhelperTimer, SIGNAL(timeout()), this, SLOT(pbar_addFASTA()));
    // which in turn sends back pbar_numbering_helper_signal(int) signal with progress value
    connect(this, SIGNAL(pbar_addFASTA_SIGNAL(int)), pbar, SLOT(setValue(int)));

    // destroy thread if process is cancelled
    connect(pbar, SIGNAL(canceled()), &watcher, SLOT(cancel()));

    connect(this, SIGNAL(FASTA_helper_completed()), pbar, SLOT(close()));
    connect(this, SIGNAL(FASTA_helper_completed()), pBarhelperTimer, SLOT(stop()));
    connect(this, SIGNAL(FASTA_helper_completed()), this, SLOT(updateWorkingWindowGroup()));
}


void MainWindow::addFASTA_helper(std::string groupName_, QString filename_) {

    qDebug() << "Calling chainGroups->loadFASTA(groupName_, filename_.toStdString())";

    chainGroups->loadFASTA(groupName_, filename_.toStdString());

    Q_EMIT(FASTA_helper_completed());
}


void MainWindow::pbar_addFASTA() {

    QString groupName = (static_cast<QProgressDialog*>(sender())->property("groupName")).toString();

    auto progress = static_cast<int>(std::ceil(chainGroups->fastaParsingProgress(groupName.toStdString())));

    qDebug() << "pbar_addFASTA() progress: " << progress;

    Q_EMIT(pbar_addFASTA_SIGNAL(progress));

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
//                                                 PLOTTING SLOTS
// #####################################################################################################################

void MainWindow::adjustXAxisLower() {

    ui->plotArea->xAxis->setRange(xAxisRangeLower->value(), ui->plotArea->xAxis->range().upper);
    ui->plotArea->replot();

}

void MainWindow::adjustYAxisLower() {

    ui->plotArea->yAxis->setRange(xAxisRangeLower->value(), ui->plotArea->yAxis->range().upper);
    ui->plotArea->replot();

}

void MainWindow::adjustXAxisUpper() {

    ui->plotArea->xAxis->setRange(ui->plotArea->xAxis->range().lower, xAxisRangeUpper->value());
    ui->plotArea->replot();

}

void MainWindow::adjustYAxisUpper() {

    ui->plotArea->yAxis->setRange(ui->plotArea->yAxis->range().lower, yAxisRangeUpper->value());
    ui->plotArea->replot();

}

// #####################################################################################################################
//                                               ANALYSIS MENU SLOTS
// #####################################################################################################################

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

    ui->plotSettingLayoutCustom->addWidget(new QLabel("Group"), 1, 0);
    ui->plotSettingLayoutCustom->addWidget(dataset, 1, 1);
    ui->plotSettingLayoutCustom->addWidget(new QLabel("X-axis PC"), 2, 0);
    ui->plotSettingLayoutCustom->addWidget(xAxisData, 2, 1);
    ui->plotSettingLayoutCustom->addWidget(new QLabel("Y-axis PC"), 3, 0);
    ui->plotSettingLayoutCustom->addWidget(yAxisData, 3, 1);
    ui->plotSettingLayoutCustom->addWidget(applyChanges, 4, 1);

    ui->plotArea->addGraph();

    changeDatasetForPCA();

    connect(applyChanges, SIGNAL(clicked()), this, SLOT(changeDatasetForPCA()));
}



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


    qDebug() << "Got ui->plotSettingLayoutCustom children";

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

    bool foundX, foundY;

    auto xrange = ui->plotArea->graph(0)->data()->keyRange(foundX);
    auto yrange = ui->plotArea->graph(0)->data()->valueRange(foundY);

    double xmin = xmin < 0 ? xrange.lower * 1.1 : xrange.lower * 0.9;
    double xmax = xmax < 0 ? xrange.upper * 0.9 : xrange.upper * 1.1;
    double ymin = ymin < 0 ? yrange.lower * 1.1 : yrange.lower * 0.9;
    double ymax = ymax < 0 ? yrange.upper * 0.9 : yrange.upper * 1.1;

    std::cout << "PRE ADJUSTMENT: \n";
    std::cout << "X_MIN: " << xrange.lower << std::endl;
    std::cout << "X_MAX: " << xrange.upper << std::endl;
    std::cout << "Y_MIN: " << yrange.lower << std::endl;
    std::cout << "Y_MAX: " << yrange.upper << std::endl;

    std::cout << "\nADJUSTED:\n";
    std::cout << "X_MIN: " << xmin << std::endl;
    std::cout << "X_MAX: " << xmax << std::endl;
    std::cout << "Y_MIN: " << ymin << std::endl;
    std::cout << "Y_MAX: " << ymax << std::endl;

    double delta = (fabs(xmax) - fabs(xmin) > fabs(ymax) - fabs(ymax)) ? fabs(xmax) - fabs(xmin) : fabs(ymax) - fabs(ymax);

    ui->plotArea->xAxis->setRange(xmin - delta, xmax + delta);
    ui->plotArea->yAxis->setRange(ymin - delta, ymax + delta);

    ui->plotArea->replot();
}

// #####################################################################################################################
//                                              ICON SLOTS
// #####################################################################################################################

void MainWindow::update_abnum_connection(bool isConnected_) {

    if (isConnected_) {

        qDebug() << "Connected";
        auto temp = ui->iconLayout->takeAt(0);
        ui->iconLayout->removeItem(temp);
        abnumNotConnected->hide();
        ui->iconLayout->addWidget(abnumConnected, 0);
        abnumConnected->show();
    }

    else {

        qDebug() << "Not connected";
        auto temp = ui->iconLayout->takeAt(0);
        ui->iconLayout->removeItem(temp);
        abnumConnected->hide();
        ui->iconLayout->addWidget(abnumNotConnected, 0);
        abnumNotConnected->show();
    }

    qDebug() << "Updated connection image";
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