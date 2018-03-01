#include "fileloaderdialog.h"
#include "ui_fileloaderdialog.h"

FileLoaderDialog::FileLoaderDialog(QWidget *parent, QStringList groupNames) :
    QDialog(parent),
    ui(new Ui::FileLoaderDialog)
{
    ui->setupUi(this);

    ui->fileLoaderGroupNames->addItems(groupNames);
}

FileLoaderDialog::~FileLoaderDialog()
{
    delete ui;
}

void FileLoaderDialog::on_fileLoaderDialogLoadFile_clicked()
{

    // open file dialog to choose FASTA file
    QFileDialog dialog;
    filename = dialog.getOpenFileName(this, tr("Open FASTA File"),"",tr("FASTA files (*.fasta)"));

}

void FileLoaderDialog::on_buttonBox_accepted()
{
    Q_EMIT fileLoaderDialogFilename(ui->fileLoaderGroupNames->currentText().toStdString(),
                                    filename);
}
