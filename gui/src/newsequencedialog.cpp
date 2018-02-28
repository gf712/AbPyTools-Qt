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
    emit buttonBoxAccepted(ui->newSequenceDialogName->text().toStdString(),
                           ui->newSequenceDialogSequence->toPlainText().toStdString(),
                           std::string(numberingSchemesVector[ui->newSequenceDialogNumberingScheme->currentIndex()]));
    emit buttonBoxAccepted();
}
