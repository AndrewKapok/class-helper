#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("自动座位分配系统");
    setGeometry(100, 100, 1000, 700);
    
    initUI();
    connectSignals();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    // Create tab widget
    tabWidget = new QTabWidget(this);
    ui->verticalLayout->addWidget(tabWidget);
    
    // Create import tab
    QWidget *importTab = new QWidget();
    QVBoxLayout *importLayout = new QVBoxLayout(importTab);
    QLabel *importLabel = new QLabel("请点击下方按钮导入成绩文件");
    importLabel->setAlignment(Qt::AlignCenter);
    importLayout->addWidget(importLabel);
    tabWidget->addTab(importTab, "成绩导入");
    
    // Create config tab
    QWidget *configTab = new QWidget();
    QVBoxLayout *configLayout = new QVBoxLayout(configTab);
    QLabel *configLabel = new QLabel("请点击下方按钮配置座位关系");
    configLabel->setAlignment(Qt::AlignCenter);
    configLayout->addWidget(configLabel);
    tabWidget->addTab(configTab, "座位配置");
    
    // Create assign tab
    QWidget *assignTab = new QWidget();
    QVBoxLayout *assignLayout = new QVBoxLayout(assignTab);
    QLabel *assignLabel = new QLabel("请点击下方按钮开始座位分配");
    assignLabel->setAlignment(Qt::AlignCenter);
    assignLayout->addWidget(assignLabel);
    tabWidget->addTab(assignTab, "座位分配");
    
    // Create result tab
    QWidget *resultTab = new QWidget();
    QVBoxLayout *resultLayout = new QVBoxLayout(resultTab);
    resultViewer = new ResultViewer(this);
    resultLayout->addWidget(resultViewer);
    tabWidget->addTab(resultTab, "结果查看");
    
    // Create buttons
    importBtn = ui->importBtn;
    configBtn = ui->configBtn;
    assignBtn = ui->assignBtn;
    exportBtn = ui->exportBtn;
    
    // Initialize dialogs
    importDialog = new ImportDialog(this);
    seatingConfigDialog = new SeatingConfigDialog(this);
    algorithmConfigDialog = new AlgorithmConfigDialog(this);
    exportDialog = new ExportDialog(this);
}

void MainWindow::connectSignals()
{
    connect(importBtn, &QPushButton::clicked, this, &MainWindow::onImport);
    connect(configBtn, &QPushButton::clicked, this, &MainWindow::onConfig);
    connect(assignBtn, &QPushButton::clicked, this, &MainWindow::onAssign);
    connect(exportBtn, &QPushButton::clicked, this, &MainWindow::onExport);
}

QString MainWindow::executePythonScript(const QString &script, const QStringList &args)
{
    QProcess process;
    QStringList fullArgs;
    fullArgs << script;
    fullArgs << args;
    
    process.start("python", fullArgs);
    process.waitForFinished();
    
    if (process.exitCode() != 0) {
        QString error = process.readAllStandardError();
        qDebug() << "Python script error:" << error;
        return "";
    }
    
    return process.readAllStandardOutput();
}

void MainWindow::onImport()
{
    if (importDialog->exec() == QDialog::Accepted) {
        // Handle import result
        QString filePath = importDialog->getFilePath();
        if (!filePath.isEmpty()) {
            // Execute Python script to import data
            QStringList args;
            args << "import" << filePath;
            QString result = executePythonScript("../src/cli_main.py", args);
            
            if (result.contains("成功")) {
                QMessageBox::information(this, "成功", "成绩文件导入成功");
            } else {
                QMessageBox::critical(this, "错误", "成绩文件导入失败");
            }
        }
    }
}

void MainWindow::onConfig()
{
    if (seatingConfigDialog->exec() == QDialog::Accepted) {
        // Handle config result
    }
}

void MainWindow::onAssign()
{
    if (algorithmConfigDialog->exec() == QDialog::Accepted) {
        // Get algorithm parameters
        int algorithm = algorithmConfigDialog->getAlgorithm();
        int rows = algorithmConfigDialog->getRows();
        int cols = algorithmConfigDialog->getCols();
        
        // Execute Python script to assign seats
        QStringList args;
        args << "assign" << QString::number(algorithm) << QString::number(rows) << QString::number(cols);
        QString result = executePythonScript("../src/cli_main.py", args);
        
        if (result.contains("成功")) {
            QMessageBox::information(this, "成功", "座位分配成功");
            seatingResult = result;
            updateResultView(seatingResult);
        } else {
            QMessageBox::critical(this, "错误", "座位分配失败");
        }
    }
}

void MainWindow::onExport()
{
    if (seatingResult.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先进行座位分配");
        return;
    }
    
    if (exportDialog->exec() == QDialog::Accepted) {
        // Handle export result
        QString filePath = exportDialog->getFilePath();
        int exportType = exportDialog->getExportType();
        
        if (!filePath.isEmpty()) {
            // Execute Python script to export result
            QStringList args;
            args << "export" << filePath << QString::number(exportType);
            QString result = executePythonScript("../src/cli_main.py", args);
            
            if (result.contains("成功")) {
                QMessageBox::information(this, "成功", "结果导出成功");
            } else {
                QMessageBox::critical(this, "错误", "结果导出失败");
            }
        }
    }
}

void MainWindow::updateResultView(const QString &seating)
{
    seatingResult = seating;
    tabWidget->setCurrentIndex(3);
    resultViewer->setResult(seating);
}
