#include "newsequencedialog.h"
#include "ui_newsequencedialog.h"

newSequenceDialog::newSequenceDialog(QWidget *parent, QStringList groupNames) :
    QDialog(parent),
    ui(new Ui::newSequenceDialog)
{
    ui->setupUi(this);

    ui->comboBox->addItems(groupNames);
}

newSequenceDialog::~newSequenceDialog()
{
    delete ui;
}

void newSequenceDialog::on_buttonBox_accepted()
{
    emit buttonBoxAccepted(ui->newSequenceDialogName->text().toStdString(),
                           ui->newSequenceDialogSequence->toPlainText().toStdString());
}
