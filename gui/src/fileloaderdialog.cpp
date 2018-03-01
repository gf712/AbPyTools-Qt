#include "fileloaderdialog.h"
#include "ui_fileloaderdialog.h"

FileLoaderDialog::FileLoaderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileLoaderDialog)
{
    ui->setupUi(this);
}

FileLoaderDialog::~FileLoaderDialog()
{
    delete ui;
}
