#include "../include/editdialog.h"
#include "ui_editdialog.h"

editDialog::editDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editDialog)
{
    ui->setupUi(this);


}

editDialog::~editDialog()
{
    delete ui;
}

void editDialog::on_editDialogGroupName_currentIndexChanged(const QString &arg1)
{
//    groupName = arg1;

//    connect(this, )

//    ui->editDialogHValueDataset->setText(chainGroupReference.getNumberingScheme(arg1.toStdString()));
}

void editDialog::on_buttonBox_accepted()
{

    numberingScheme = ui->editDialogNumberingScheme->currentIndex();
    groupName = ui->editDialogGroupName->currentText();
    hydrophobicityDataSet = ui->editDialogHValueDataset->currentText();

    qDebug() << "numberingScheme: " << numberingScheme
             << "groupName: " << groupName
             << "hydrophobicityDataSet" << hydrophobicityDataSet;

    Q_EMIT editDialogUpdateGroup(groupName.toStdString(),
                                 hydrophobicityDataSet.toStdString(),
                                 numberingScheme);
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

