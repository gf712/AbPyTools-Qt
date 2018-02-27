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
    void on_newSequenceDialogName_editingFinished();
    void on_newSequenceDialogSequence_textChanged();
    void on_newSequenceDialogNumberingScheme_currentIndexChanged(int index);

signals:
    void buttonBoxAccepted(std::string name_, std::string sequence_, std::string numberingScheme_);

private:
    Ui::newSequenceDialog *ui;
    constexpr static std::array<char[15], 3> numberingSchemesVector = {"chothia", "kabat", "chothia_ext"};
};

#endif // NEWSEQUENCEDIALOG_H
