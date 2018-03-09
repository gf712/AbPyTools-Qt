#ifndef FILELOADERDIALOG_H
#define FILELOADERDIALOG_H

#include <QDialog>
#include <QtWidgets/QFileDialog>

namespace Ui {
class FileLoaderDialog;
}

class FileLoaderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileLoaderDialog(QWidget *parent = 0, QStringList groupNames = QStringList());
    ~FileLoaderDialog();

Q_SIGNALS:

    void fileLoaderDialogFilename(std::string, QString);

private Q_SLOTS:

    void on_fileLoaderDialogLoadFile_clicked();

    void on_buttonBox_accepted();

private:
    Ui::FileLoaderDialog *ui;
    QString filename;
};

#endif // FILELOADERDIALOG_H
