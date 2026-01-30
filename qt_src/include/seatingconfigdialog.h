#ifndef SEATINGCONFIGDIALOG_H
#define SEATINGCONFIGDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class SeatingConfigDialog;
}
QT_END_NAMESPACE

class SeatingConfigDialog : public QDialog
{
    Q_OBJECT

public:
    SeatingConfigDialog(QWidget *parent = nullptr);
    ~SeatingConfigDialog();

private slots:
    void on_addTogetherBtn_clicked();
    void on_removeTogetherBtn_clicked();
    void on_addCannotBtn_clicked();
    void on_removeCannotBtn_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::SeatingConfigDialog *ui;
};
#endif // SEATINGCONFIGDIALOG_H
