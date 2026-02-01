#include <iostream>
#include "exceldata.h"
#include "excelread.h"
#include "excelwrite.h"

/**
 * 测试Excel边界情况和异常处理
 */
int main()
{
    std::cout << "=== Excel边界和异常测试 ===" << std::endl;

    // 测试1: 空ExcelData
    std::cout << "\n测试1: 测试空ExcelData..." << std::endl;
    ExcelData emptyData;
    ExcelWrite writer;
    std::string emptyFile = "empty_output.xls";
    if (writer.write(emptyFile, emptyData))
    {
        std::cout << "成功写入空数据到文件: " << emptyFile << std::endl;
    }
    else
    {
        std::cout << "写入空数据失败: " << writer.getLastError() << std::endl;
    }

    // 测试2: 不存在的文件
    std::cout << "\n测试2: 测试不存在的文件..." << std::endl;
    ExcelData nonExistentData;
    ExcelRead reader;
    std::string nonExistentFile = "non_existent_file.xls";
    if (reader.read(nonExistentFile, nonExistentData))
    {
        std::cout << "成功从不存在的文件读取: " << nonExistentFile << std::endl;
    }
    else
    {
        std::cout << "从不存在的文件读取失败 (预期): " << reader.getLastError() << std::endl;
    }

    // 测试3: 单个单元格数据
    std::cout << "\n测试3: 测试单个单元格数据..." << std::endl;
    ExcelData singleCellData;
    singleCellData.addSheet("Sheet1");
    singleCellData.addRowToSheet("Sheet1");
    singleCellData.addCellToSheetRow("Sheet1", 0, "Hello World");
    std::string singleCellFile = "single_cell_output.xls";
    if (writer.write(singleCellFile, singleCellData))
    {
        std::cout << "成功写入单个单元格数据到文件: " << singleCellFile << std::endl;
    }
    else
    {
        std::cout << "写入单个单元格数据失败: " << writer.getLastError() << std::endl;
    }

    // 测试4: 大量行数据
    std::cout << "\n测试4: 测试大量行数据..." << std::endl;
    ExcelData largeData;
    largeData.addSheet("Sheet1");
    for (int i = 0; i < 100; i++)
    {
        largeData.addRowToSheet("Sheet1");
        largeData.addCellToSheetRow("Sheet1", i, "Row " + std::to_string(i));
        largeData.addCellToSheetRow("Sheet1", i, "Value " + std::to_string(i));
    }
    std::string largeFile = "large_output.xls";
    if (writer.write(largeFile, largeData))
    {
        std::cout << "成功写入大量数据到文件: " << largeFile << std::endl;
    }
    else
    {
        std::cout << "写入大量数据失败: " << writer.getLastError() << std::endl;
    }

    std::cout << "\n=== 边界和异常测试完成 ===" << std::endl;
    return 0;
}