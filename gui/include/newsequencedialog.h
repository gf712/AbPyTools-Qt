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
    explicit newSequenceDialog(QWidget *parent = 0);
    ~newSequenceDialog();

private slots:
    void on_buttonBox_accepted();

signals:
    void buttonBoxAccepted(std::string name_, std::string sequence_);

private:
    Ui::newSequenceDialog *ui;
};

#endif // NEWSEQUENCEDIALOG_H
