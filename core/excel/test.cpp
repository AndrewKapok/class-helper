#include <iostream>
#include "exceldata.h"
#include "excelread.h"
#include "excelwrite.h"

/**
 * 测试Excel处理功能
 */
int main()
{
    std::cout << "=== Excel处理测试 ===" << std::endl;

    // 测试1: 创建并填充ExcelData
    std::cout << "\n测试1: 创建并填充ExcelData..." << std::endl;
    ExcelData data;

    // 添加工作表
    data.addSheet("Sheet1");
    data.addSheet("Sheet2");

    // 向Sheet1添加数据
    data.addRowToSheet("Sheet1");
    data.addCellToSheetRow("Sheet1", 0, "姓名");
    data.addCellToSheetRow("Sheet1", 0, "数学");
    data.addCellToSheetRow("Sheet1", 0, "语文");
    data.addCellToSheetRow("Sheet1", 0, "英语");

    data.addRowToSheet("Sheet1");
    data.addCellToSheetRow("Sheet1", 1, "张三");
    data.addCellToSheetRow("Sheet1", 1, "95");
    data.addCellToSheetRow("Sheet1", 1, "88");
    data.addCellToSheetRow("Sheet1", 1, "92");

    data.addRowToSheet("Sheet1");
    data.addCellToSheetRow("Sheet1", 2, "李四");
    data.addCellToSheetRow("Sheet1", 2, "87");
    data.addCellToSheetRow("Sheet1", 2, "91");
    data.addCellToSheetRow("Sheet1", 2, "85");

    data.addRowToSheet("Sheet1");
    data.addCellToSheetRow("Sheet1", 3, "王五");
    data.addCellToSheetRow("Sheet1", 3, "92");
    data.addCellToSheetRow("Sheet1", 3, "85");
    data.addCellToSheetRow("Sheet1", 3, "90");

    // 向Sheet2添加数据
    data.addRowToSheet("Sheet2");
    data.addCellToSheetRow("Sheet2", 0, "姓名");
    data.addCellToSheetRow("Sheet2", 0, "物理");
    data.addCellToSheetRow("Sheet2", 0, "化学");
    data.addCellToSheetRow("Sheet2", 0, "生物");

    data.addRowToSheet("Sheet2");
    data.addCellToSheetRow("Sheet2", 1, "张三");
    data.addCellToSheetRow("Sheet2", 1, "90");
    data.addCellToSheetRow("Sheet2", 1, "88");
    data.addCellToSheetRow("Sheet2", 1, "92");

    data.addRowToSheet("Sheet2");
    data.addCellToSheetRow("Sheet2", 2, "李四");
    data.addCellToSheetRow("Sheet2", 2, "85");
    data.addCellToSheetRow("Sheet2", 2, "90");
    data.addCellToSheetRow("Sheet2", 2, "88");

    // 测试2: 显示数据
    std::cout << "\n测试2: 显示ExcelData..." << std::endl;
    auto sheetNames = data.getSheetNames();
    for (const auto &sheetName : sheetNames)
    {
        std::cout << "\n工作表: " << sheetName << std::endl;
        size_t rowCount = data.getRowCountInSheet(sheetName);
        size_t colCount = data.getMaxColumnCount(sheetName);

        for (size_t row = 0; row < rowCount; row++)
        {
            for (size_t col = 0; col < colCount; col++)
            {
                const std::string &value = data.getCellValue(sheetName, row, col);
                std::cout << value << "\t";
            }
            std::cout << std::endl;
        }
    }

    // 测试3: 写入数据到Excel文件
    std::cout << "\n测试3: 写入数据到Excel文件..." << std::endl;
    ExcelWrite writer;
    std::string outputFile = "test_output.xls";
    if (writer.write(outputFile, data))
    {
        std::cout << "成功写入文件: " << outputFile << std::endl;
    }
    else
    {
        std::cout << "写入文件失败: " << writer.getLastError() << std::endl;
    }

    // 测试4: 从Excel文件读取数据
    std::cout << "\n测试4: 从Excel文件读取数据..." << std::endl;
    ExcelData readData;
    ExcelRead reader;
    if (reader.read(outputFile, readData))
    {
        std::cout << "成功从文件读取: " << outputFile << std::endl;

        // 显示读取的数据
        std::cout << "\n显示读取的数据..." << std::endl;
        auto readSheetNames = readData.getSheetNames();
        for (const auto &sheetName : readSheetNames)
        {
            std::cout << "\n工作表: " << sheetName << std::endl;
            size_t rowCount = readData.getRowCountInSheet(sheetName);
            size_t colCount = readData.getMaxColumnCount(sheetName);

            for (size_t row = 0; row < rowCount; row++)
            {
                for (size_t col = 0; col < colCount; col++)
                {
                    const std::string &value = readData.getCellValue(sheetName, row, col);
                    std::cout << value << "\t";
                }
                std::cout << std::endl;
            }
        }
    }
    else
    {
        std::cout << "从文件读取失败: " << reader.getLastError() << std::endl;
    }

    // 测试5: 测试现有Excel文件
    std::cout << "\n测试5: 测试现有Excel文件..." << std::endl;
    std::string existingFile = "../工作簿1.xlsx";
    ExcelData existingData;
    if (reader.read(existingFile, existingData))
    {
        std::cout << "成功从现有文件读取: " << existingFile << std::endl;

        // 显示读取的数据
        std::cout << "\n显示现有文件数据..." << std::endl;
        auto existingSheetNames = existingData.getSheetNames();
        for (const auto &sheetName : existingSheetNames)
        {
            std::cout << "\n工作表: " << sheetName << std::endl;
            size_t rowCount = existingData.getRowCountInSheet(sheetName);
            size_t colCount = existingData.getMaxColumnCount(sheetName);

            for (size_t row = 0; row < rowCount; row++)
            {
                for (size_t col = 0; col < colCount; col++)
                {
                    const std::string &value = existingData.getCellValue(sheetName, row, col);
                    std::cout << value << "\t";
                }
                std::cout << std::endl;
            }
        }
    }
    else
    {
        std::cout << "从现有文件读取失败: " << reader.getLastError() << std::endl;
    }

    std::cout << "\n=== 测试完成 ===" << std::endl;
    return 0;
}