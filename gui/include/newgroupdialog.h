#ifndef NEWGROUPDIALOG_H
#define NEWGROUPDIALOG_H

#include <QDialog>

namespace Ui {
class NewGroupDialog;
}

class NewGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewGroupDialog(QWidget *parent = 0);
    ~NewGroupDialog();

signals:
    void newGrupDialogButtonBoxAccepted(std::string name_, std::string numberingScheme);

private slots:
    void on_newGroupDialogButtonBox_accepted();

private:
    Ui::NewGroupDialog *ui;
    constexpr static std::array<char[15], 3> numberingSchemesVector = {"chothia", "kabat", "chothia_ext"};
};

#endif // NEWGROUPDIALOG_H
