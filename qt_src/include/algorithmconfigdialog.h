#ifndef ALGORITHMCONFIGDIALOG_H
#define ALGORITHMCONFIGDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class AlgorithmConfigDialog;
}
QT_END_NAMESPACE

class AlgorithmConfigDialog : public QDialog
{
    Q_OBJECT

public:
    AlgorithmConfigDialog(QWidget *parent = nullptr);
    ~AlgorithmConfigDialog();
    
    int getAlgorithm() const;
    int getRows() const;
    int getCols() const;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::AlgorithmConfigDialog *ui;
    int algorithm;
    int rows;
    int cols;
};
#endif // ALGORITHMCONFIGDIALOG_H
