#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chain.h"
#include "chainCollectionCPP.h"
#include <QMainWindow>
#include <QTimer>
#include <QString>
#include <string>
#include <iostream>
#include <QDebug>
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
    Ui::MainWindow* getUI() { return ui;}

private slots:
    void on_actionOpen_triggered();
    void on_actionNew_triggered();
    void addAntibodyObject(std::string name_,
                           std::string sequence_,
                           std::string numberingScheme_);

private:
    Ui::MainWindow *ui;
    AntibodyChainCPP *antibodyObject; // = new AntibodyChainCPP();
    ChainCollectionCPP *antibodyObjects;
    std::string name;
    std::string sequence;
    std::string numberingScheme;
    QTimer *timer;
};

#endif // MAINWINDOW_H
