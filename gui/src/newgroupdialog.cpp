#include "newgroupdialog.h"
#include "ui_newgroupdialog.h"

// static variable definitions
constexpr std::array<char[15], 3> NewGroupDialog::numberingSchemesVector;


NewGroupDialog::NewGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewGroupDialog)
{
    ui->setupUi(this);
}

NewGroupDialog::~NewGroupDialog()
{
    delete ui;
}

void NewGroupDialog::on_newGroupDialogButtonBox_accepted()
{
    emit newGrupDialogButtonBoxAccepted(ui->newGroupDialogGroupName->text().toStdString(),
                                        std::string(numberingSchemesVector[ui->newGroupDialogNumberingScheme->currentIndex()]));
}
