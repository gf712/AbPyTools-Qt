#include "../include/editdialog.h"
#include "ui_editdialog.h"

//editDialog::editDialog(ChainGroup &chainGroup_, QWidget *parent) :
editDialog::editDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editDialog)
{
    ui->setupUi(this);

//    ui->editDialogGroupName->addItems(groupNames);
//    chainGroupReference = chainGroup_;

}

editDialog::~editDialog()
{
    delete ui;
}

void editDialog::on_editDialogGroupName_currentIndexChanged(const QString &arg1)
{
    groupName = arg1;
//    ui->editDialogHValueDataset->setText(chainGroupReference.getNumberingScheme(arg1.toStdString()));
}

void editDialog::on_buttonBox_accepted()
{
    Q_EMIT editDialogUpdateGroup(groupName.toStdString(),
                                 hydrophobicityDataSet.toStdString(),
                                 numberingScheme.toStdString());
}

void editDialog::receiveGroupNamesFromParent(QStringList groupNames) {

    ui->editDialogGroupName->addItems(groupNames);

};

void editDialog::receiveHydrophobicityDatasetNamesFromParent(QStringList datasetNames) {

    ui->editDialogHValueDataset->addItems(datasetNames);

};

void editDialog::receiveNumberingSchemeNamesFromParent(QStringList numberingSchemes) {

    ui->editDialogNumberingScheme ->addItems(numberingSchemes);

};

