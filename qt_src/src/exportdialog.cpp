#include "exportdialog.h"
#include "ui_exportdialog.h"

#include <QFileDialog>
#include <QMessageBox>

ExportDialog::ExportDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExportDialog)
    , exportType(0)
{
    ui->setupUi(this);
    setWindowTitle("导出结果");
}

ExportDialog::~ExportDialog()
{
    delete ui;
}

QString ExportDialog::getFilePath() const
{
    return filePath;
}

int ExportDialog::getExportType() const
{
    return exportType;
}

void ExportDialog::on_browseBtn_clicked()
{
    QString filter = "Excel文件 (*.xlsx *.xls)";
    if (ui->exportTypeComboBox->currentIndex() == 1) {
        filter = "图片文件 (*.png *.jpg *.jpeg)";
    }
    
    QString fileName = QFileDialog::getSaveFileName(this, "保存文件", "", filter);
    if (!fileName.isEmpty()) {
        ui->filePathEdit->setText(fileName);
        filePath = fileName;
    }
}

void ExportDialog::on_buttonBox_accepted()
{
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "警告", "请选择保存路径");
        return;
    }
    
    exportType = ui->exportTypeComboBox->currentIndex();
    accept();
}

void ExportDialog::on_buttonBox_rejected()
{
    reject();
}
