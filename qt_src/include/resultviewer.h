#ifndef RESULTVIEWER_H
#define RESULTVIEWER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class ResultViewer;
}
QT_END_NAMESPACE

class ResultViewer : public QWidget
{
    Q_OBJECT

public:
    ResultViewer(QWidget *parent = nullptr);
    ~ResultViewer();
    
    void setResult(const QString &result);

private:
    Ui::ResultViewer *ui;
    QString seatingResult;
    
    void displayResult();
};
#endif // RESULTVIEWER_H
