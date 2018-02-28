#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chain.h"
#include "chainCollectionCPP.h"
#include "fastaParser.h"
#include <QMainWindow>
#include <QTimer>
#include <QString>
#include <string>
#include <iostream>
#include <QDebug>
#include <QFileDialog>
#include <QDateTime>
#include "newsequencedialog.h"

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
    void addAntibodyObjectText();
    void addAntibodyObjectDebugText();
    void loadFASTADebugText();

private slots:
    void on_actionOpen_triggered();
    void on_actionNew_triggered();
    void addAntibodyObject(std::string name_,
                           std::string sequence_,
                           std::string numberingScheme_);

    void updateWorkingWindow();
    void updateDebugWindow();

private:
    Ui::MainWindow *ui;
    AntibodyChainCPP *antibodyObject;
    ChainCollectionCPP *antibodyObjects;
    FastaParser *fastaParser;
    std::string name;
    std::string sequence;
    std::string numberingScheme;
    QTimer *timer;

    QString cacheText = "Welcome to AbPyTools-Qt:\nNothing to display"; // stores text to display in working window
    QString cacheDebugText = "Welcome to AbPyTools-Qt Debug Mode:\n"; // stores text to display in working window

    bool startedWorking;
};

#endif // MAINWINDOW_H
