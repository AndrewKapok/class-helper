#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class ExportDialog;
}
QT_END_NAMESPACE

class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    ExportDialog(QWidget *parent = nullptr);
    ~ExportDialog();
    
    QString getFilePath() const;
    int getExportType() const;

private slots:
    void on_browseBtn_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::ExportDialog *ui;
    QString filePath;
    int exportType;
};
#endif // EXPORTDIALOG_H
