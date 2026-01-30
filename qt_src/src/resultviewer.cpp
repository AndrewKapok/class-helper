#include "resultviewer.h"
#include "ui_resultviewer.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ResultViewer::ResultViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ResultViewer)
{
    ui->setupUi(this);
}

ResultViewer::~ResultViewer()
{
    delete ui;
}

void ResultViewer::setResult(const QString &result)
{
    seatingResult = result;
    displayResult();
}

void ResultViewer::displayResult()
{
    if (seatingResult.isEmpty()) return;
    
    // Clear existing layout
    QLayoutItem *item;
    while ((item = ui->verticalLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    
    // Create scroll area
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    
    QWidget *scrollContent = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);
    
    // Display seating result
    QLabel *titleLabel = new QLabel("座位分配结果");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold;");
    scrollLayout->addWidget(titleLabel);
    
    // Parse the result (assuming it's in JSON format)
    QJsonDocument doc = QJsonDocument::fromJson(seatingResult.toUtf8());
    if (doc.isArray()) {
        QJsonArray seatingArray = doc.array();
        
        for (int i = 0; i < seatingArray.size(); ++i) {
            QJsonValue rowValue = seatingArray[i];
            if (rowValue.isArray()) {
                QJsonArray rowArray = rowValue.toArray();
                QHBoxLayout *rowLayout = new QHBoxLayout();
                
                for (int j = 0; j < rowArray.size(); ++j) {
                    QJsonValue seatValue = rowArray[j];
                    if (seatValue.isObject()) {
                        QJsonObject seatObj = seatValue.toObject();
                        QString name = seatObj["name"].toString();
                        double score = seatObj["score"].toDouble();
                        
                        QLabel *seatLabel = new QLabel(QString("%1\n%2").arg(name).arg(score));
                        seatLabel->setAlignment(Qt::AlignCenter);
                        seatLabel->setStyleSheet("border: 1px solid #ccc; padding: 10px; margin: 2px;");
                        seatLabel->setFixedSize(80, 80);
                        rowLayout->addWidget(seatLabel);
                    } else {
                        QLabel *emptyLabel = new QLabel("空");
                        emptyLabel->setAlignment(Qt::AlignCenter);
                        emptyLabel->setStyleSheet("border: 1px solid #ccc; padding: 10px; margin: 2px; background-color: #f0f0f0;");
                        emptyLabel->setFixedSize(80, 80);
                        rowLayout->addWidget(emptyLabel);
                    }
                }
                
                scrollLayout->addLayout(rowLayout);
            }
        }
    } else {
        // If not JSON, display raw result
        QLabel *resultLabel = new QLabel(seatingResult);
        resultLabel->setWordWrap(true);
        scrollLayout->addWidget(resultLabel);
    }
    
    scrollArea->setWidget(scrollContent);
    ui->verticalLayout->addWidget(scrollArea);
}
