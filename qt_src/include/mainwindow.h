#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>

#include "importdialog.h"
#include "seatingconfigdialog.h"
#include "algorithmconfigdialog.h"
#include "resultviewer.h"
#include "exportdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onImport();
    void onConfig();
    void onAssign();
    void onExport();

private:
    Ui::MainWindow *ui;
    
    // UI components
    QTabWidget *tabWidget;
    QPushButton *importBtn;
    QPushButton *configBtn;
    QPushButton *assignBtn;
    QPushButton *exportBtn;
    
    // Dialogs
    ImportDialog *importDialog;
    SeatingConfigDialog *seatingConfigDialog;
    AlgorithmConfigDialog *algorithmConfigDialog;
    ExportDialog *exportDialog;
    ResultViewer *resultViewer;
    
    // Seating result
    QString seatingResult;
    
    // Methods
    void initUI();
    void connectSignals();
    void updateResultView(const QString &seating);
    QString executePythonScript(const QString &script, const QStringList &args);
};
#endif // MAINWINDOW_H
