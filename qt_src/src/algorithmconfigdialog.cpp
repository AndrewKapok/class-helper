#include "algorithmconfigdialog.h"
#include "ui_algorithmconfigdialog.h"

AlgorithmConfigDialog::AlgorithmConfigDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AlgorithmConfigDialog)
    , algorithm(0)
    , rows(6)
    , cols(8)
{
    ui->setupUi(this);
    setWindowTitle("算法配置");
    
    // Set default values
    ui->algorithmComboBox->setCurrentIndex(0);
    ui->rowsSpinBox->setValue(6);
    ui->colsSpinBox->setValue(8);
}

AlgorithmConfigDialog::~AlgorithmConfigDialog()
{
    delete ui;
}

int AlgorithmConfigDialog::getAlgorithm() const
{
    return algorithm;
}

int AlgorithmConfigDialog::getRows() const
{
    return rows;
}

int AlgorithmConfigDialog::getCols() const
{
    return cols;
}

void AlgorithmConfigDialog::on_buttonBox_accepted()
{
    algorithm = ui->algorithmComboBox->currentIndex();
    rows = ui->rowsSpinBox->value();
    cols = ui->colsSpinBox->value();
    
    accept();
}

void AlgorithmConfigDialog::on_buttonBox_rejected()
{
    reject();
}
