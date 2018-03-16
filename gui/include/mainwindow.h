#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// backend headers + 3rd party non-gui headers
#include "chain.h"
#include "chainCollectionCPP.h"
#include "fastaParser.h"
#include "hydrophobicityParser.h"
#include "connection_check.h"
#include <cmath>

// group class headers
#include "chainGroups.h"
#include "hydrophobicityGroup.h"
#include "qcustomplot.h"
#include "abnumConnectionWorker.h"

// ui class headers
#include "newsequencedialog.h"
#include "newgroupdialog.h"
#include "fileloaderdialog.h"
#include "editdialog.h"

// Qt headers
#include <QMainWindow>
#include <QTimer>
#include <QString>
#include <string>
#include <iostream>
#include <QDebug>
#include <QFileDialog>
#include <QDateTime>
#include <QMessageBox>
#include <QStringList>
#include <QDialog>
#include <QVector>
#include <QtConcurrent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // GETTERS
    Ui::MainWindow* getUI() {return ui;}

    // Display message editors
//    void addAntibodyObjectText(std::string name_);
    void addAntibodyObjectDebugText(AntibodyChainCPP *object_);
    void loadFASTADebugText();
    void startApp();
    void startConnection();
//    void addGroupText(std::string name);

//    void updateWorkingWindowGroup();

Q_SIGNALS:
    void sendGroupNamesToChild(QStringList groupNames);
    void sendHydrophobicityDatasetNamesToChild(QStringList datasetNames);
    void sendNumberingSchemeNames(QStringList numberingSchemes);

    void sendHydophobicityDatasetNameToChildOnRequestSignal(QString);
    void pbar_numbering_helper_signal(int);
    void numbering_helper_completed();
    void pbar_addFASTA_SIGNAL(int);
    void FASTA_helper_completed();

private Q_SLOTS:

    void updateWorkingWindowGroup();

    void numbering_helper();
    void pbar_numbering();

    void addFASTA_helper(std::string groupName_, QString filename_);
    void pbar_addFASTA();

    void sendHydophobicityDatasetNameToChildOnRequest(QString);

    void on_actionOpen_triggered();
    void on_actionNew_triggered();
    void on_actionNew_group_triggered();
    void on_actionApply_Numbering_triggered();
    void on_actionImport_hydrophobicity_dataset_triggered();

    void addAntibodyObject(std::string name_, std::string sequence_, std::string groupName_);
    void addChainGroup(std::string groupName_, std::string numberingScheme_);
    void addFASTA(std::string groupName_, QString filename_);

    void editGroup(std::string groupName_, std::string hydrophobicityDataSet, int numberingScheme);

    void updateWorkingWindow();
    void updateDebugWindow();

    void on_actionGroup_triggered();

    void changeDatasetForPCA();

    void on_actionPlotPCA_triggered();

    void on_actionApplyPCA_triggered();

    void update_abnum_connection(bool isConnected_);

private:
    Ui::MainWindow *ui;
    ChainGroups *chainGroups;
    hydrophobicityGroups *hGroups;
    FastaParser *fastaParser;
    std::string name;
    std::string sequence;
    std::string numberingScheme;
    QTimer *timer;

    QLabel *abnumConnected;
    QLabel *abnumNotConnected;

    bool abnumConnectionStatus;

    QString cacheText = "Welcome to AbPyTools-Qt:\n"
                        "------------------------\n"
                        "Nothing to display"; // stores text to display in working window

    QString cacheDebugText = "Welcome to AbPyTools-Qt Debug Mode:\n"; // stores text to display in working window

    bool startedWorking;
    constexpr static std::array<char[15], 3> numberingSchemesVector = {"chothia", "kabat", "chothia_ext"};

};

#endif // MAINWINDOW_H
