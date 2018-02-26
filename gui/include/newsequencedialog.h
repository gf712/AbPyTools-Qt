#ifndef NEWSEQUENCEDIALOG_H
#define NEWSEQUENCEDIALOG_H

#include <QDialog>

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

private:
    Ui::newSequenceDialog *ui;
};

#endif // NEWSEQUENCEDIALOG_H
