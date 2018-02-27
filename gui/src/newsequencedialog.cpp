#include "newsequencedialog.h"
#include "ui_newsequencedialog.h"

// static variable definitions
constexpr std::array<char[15], 3> newSequenceDialog::numberingSchemesVector;

newSequenceDialog::newSequenceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newSequenceDialog)
{
    ui->setupUi(this);
}

newSequenceDialog::~newSequenceDialog()
{
    delete ui;
}

void newSequenceDialog::on_buttonBox_accepted()
{
    
}

void newSequenceDialog::on_newSequenceDialogName_editingFinished()
{
    emit newSequenceDialogNameChange(ui->newSequenceDialogName->text().toStdString());
}

void newSequenceDialog::on_newSequenceDialogSequence_textChanged()
{
    emit newSequenceDialogSequenceChange(ui->newSequenceDialogSequence->toPlainText().toStdString());
}

void newSequenceDialog::on_newSequenceDialogNumberingScheme_currentIndexChanged(int index)
{
    emit newSequenceDialogNumberingSchemeChange(std::string(numberingSchemesVector[ui->newSequenceDialogNumberingScheme->currentIndex()]));
}
