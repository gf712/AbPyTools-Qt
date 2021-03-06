#ifndef NEWSEQUENCEDIALOG_H
#define NEWSEQUENCEDIALOG_H

#include <QDialog>
#include <vector>

namespace Ui {
class newSequenceDialog;
}

class newSequenceDialog : public QDialog
{
    Q_OBJECT

public:
    newSequenceDialog(QWidget *parent = 0, QStringList groupNames = QStringList());
    ~newSequenceDialog();

private Q_SLOTS:
    void on_buttonBox_accepted();

Q_SIGNALS:
    void buttonBoxAccepted(std::string name_, std::string sequence_, std::string groupName);

private:
    Ui::newSequenceDialog *ui;
};

#endif // NEWSEQUENCEDIALOG_H
