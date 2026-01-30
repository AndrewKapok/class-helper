#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class ImportDialog;
}
QT_END_NAMESPACE

class ImportDialog : public QDialog
{
    Q_OBJECT

public:
    ImportDialog(QWidget *parent = nullptr);
    ~ImportDialog();
    
    QString getFilePath() const;

private slots:
    void on_browseBtn_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::ImportDialog *ui;
    QString filePath;
};
#endif // IMPORTDIALOG_H
