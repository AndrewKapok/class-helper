#include "importdialog.h"
#include "ui_importdialog.h"

#include <QFileDialog>
#include <QMessageBox>

ImportDialog::ImportDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ImportDialog)
{
    ui->setupUi(this);
    setWindowTitle("导入成绩文件");
}

ImportDialog::~ImportDialog()
{
    delete ui;
}

QString ImportDialog::getFilePath() const
{
    return filePath;
}

void ImportDialog::on_browseBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择成绩文件", "", "Excel文件 (*.xlsx *.xls)");
    if (!fileName.isEmpty()) {
        ui->filePathEdit->setText(fileName);
        filePath = fileName;
    }
}

void ImportDialog::on_buttonBox_accepted()
{
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "警告", "请选择成绩文件");
        return;
    }
    
    accept();
}

void ImportDialog::on_buttonBox_rejected()
{
    reject();
}
