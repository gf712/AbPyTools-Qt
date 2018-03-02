#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include "chainGroups.h"
#include <QDialog>

namespace Ui {
class editDialog;
}

class editDialog : public QDialog
{
    Q_OBJECT

public:
//    editDialog(ChainGroups &chainGroups, QWidget *parent = 0);
    editDialog(QWidget *parent = 0);
    ~editDialog();

Q_SIGNALS:
    void editDialogUpdateGroup(std::string groupName, std::string hydrophobicityDataSet, std::string numberingScheme);

private Q_SLOTS:
    void on_editDialogGroupName_currentIndexChanged(const QString &arg1);
    void on_buttonBox_accepted();
    void receiveGroupNamesFromParent(QStringList groupNames);
    void receiveHydrophobicityDatasetNamesFromParent(QStringList datasetNames);
    void receiveNumberingSchemeNamesFromParent(QStringList numberingSchemes);

private:
    Ui::editDialog *ui;
//    ChainGroups &chainGroupReference;
    QString groupName, hydrophobicityDataSet, numberingScheme;
};

#endif // EDITDIALOG_H
