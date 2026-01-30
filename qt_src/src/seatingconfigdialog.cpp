#include "seatingconfigdialog.h"
#include "ui_seatingconfigdialog.h"

SeatingConfigDialog::SeatingConfigDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SeatingConfigDialog)
{
    ui->setupUi(this);
    setWindowTitle("座位关系配置");
}

SeatingConfigDialog::~SeatingConfigDialog()
{
    delete ui;
}

void SeatingConfigDialog::on_addTogetherBtn_clicked()
{
    // Add students to sit together
}

void SeatingConfigDialog::on_removeTogetherBtn_clicked()
{
    // Remove students from sit together list
}

void SeatingConfigDialog::on_addCannotBtn_clicked()
{
    // Add students who cannot sit together
}

void SeatingConfigDialog::on_removeCannotBtn_clicked()
{
    // Remove students from cannot sit together list
}

void SeatingConfigDialog::on_buttonBox_accepted()
{
    accept();
}

void SeatingConfigDialog::on_buttonBox_rejected()
{
    reject();
}
