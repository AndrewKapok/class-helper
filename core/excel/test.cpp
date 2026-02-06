#include <iostream>
#include <string>
#include "exceldata.h"
#include "excelread.h"
#include "excelwrite.h"
using namespace std;
/**
 * 测试Excel处理功能
 */
int main()
{
    wcout << L"=== Excel处理测试 ===" << endl;

    // 测试1: 创建并填充ExcelData
    wcout << L"\n测试1: 创建并填充ExcelData..." << endl;
    ExcelData data;

    // 添加工作表
    data.addSheet(L"Sheet1");
    data.addSheet(L"Sheet2");

    // 向Sheet1添加数据
    data.addRowToSheet(L"Sheet1");
    data.addCellToSheetRow(L"Sheet1", 0, L"姓名");
    data.addCellToSheetRow(L"Sheet1", 0, L"数学");
    data.addCellToSheetRow(L"Sheet1", 0, L"语文");
    data.addCellToSheetRow(L"Sheet1", 0, L"英语");

    data.addRowToSheet(L"Sheet1");
    data.addCellToSheetRow(L"Sheet1", 1, L"张三");
    data.addCellToSheetRow(L"Sheet1", 1, L"95");
    data.addCellToSheetRow(L"Sheet1", 1, L"88");
    data.addCellToSheetRow(L"Sheet1", 1, L"92");

    data.addRowToSheet(L"Sheet1");
    data.addCellToSheetRow(L"Sheet1", 2, L"李四");
    data.addCellToSheetRow(L"Sheet1", 2, L"87");
    data.addCellToSheetRow(L"Sheet1", 2, L"91");
    data.addCellToSheetRow(L"Sheet1", 2, L"85");

    data.addRowToSheet(L"Sheet1");
    data.addCellToSheetRow(L"Sheet1", 3, L"王五");
    data.addCellToSheetRow(L"Sheet1", 3, L"92");
    data.addCellToSheetRow(L"Sheet1", 3, L"85");
    data.addCellToSheetRow(L"Sheet1", 3, L"90");

    // 向Sheet2添加数据
    data.addRowToSheet(L"Sheet2");
    data.addCellToSheetRow(L"Sheet2", 0, L"姓名");
    data.addCellToSheetRow(L"Sheet2", 0, L"物理");
    data.addCellToSheetRow(L"Sheet2", 0, L"化学");
    data.addCellToSheetRow(L"Sheet2", 0, L"生物");

    data.addRowToSheet(L"Sheet2");
    data.addCellToSheetRow(L"Sheet2", 1, L"张三");
    data.addCellToSheetRow(L"Sheet2", 1, L"90");
    data.addCellToSheetRow(L"Sheet2", 1, L"88");
    data.addCellToSheetRow(L"Sheet2", 1, L"92");

    data.addRowToSheet(L"Sheet2");
    data.addCellToSheetRow(L"Sheet2", 2, L"李四");
    data.addCellToSheetRow(L"Sheet2", 2, L"85");
    data.addCellToSheetRow(L"Sheet2", 2, L"90");
    data.addCellToSheetRow(L"Sheet2", 2, L"88");

    // 测试2: 显示数据
    wcout << L"\n测试2: 显示ExcelData..." << endl;
    auto sheetNames = data.getSheetNames();
    for (const auto &sheetName : sheetNames)
    {
        wcout << L"\n工作表: " << sheetName << endl;
        size_t rowCount = data.getRowCountInSheet(sheetName);
        size_t colCount = data.getMaxColumnCount(sheetName);

        for (size_t row = 0; row < rowCount; row++)
        {
            for (size_t col = 0; col < colCount; col++)
            {
                const wstring &value = data.getCellValue(sheetName, row, col);
                wcout << value << L"\t";
            }
            wcout << endl;
        }
    }

    // 测试3: 写入数据到Excel文件
    wcout << L"\n测试3: 写入数据到Excel文件..." << endl;
    ExcelWrite writer;
    wstring outputFile = L"test_output.xls";
    if (writer.write(outputFile, data))
    {
        wcout << L"成功写入文件: " << outputFile << endl;
    }
    else
    {
        wcout << L"写入文件失败: " << writer.getLastError() << endl;
    }

    // 测试4: 从Excel文件读取数据
    wcout << L"\n测试4: 从Excel文件读取数据..." << endl;
    ExcelData readData;
    ExcelRead reader;
    if (reader.read(outputFile, readData))
    {
        wcout << L"成功从文件读取: " << outputFile << endl;

        // 显示读取的数据
        wcout << L"\n显示读取的数据..." << endl;
        auto readSheetNames = readData.getSheetNames();
        for (const auto &sheetName : readSheetNames)
        {
            wcout << L"\n工作表: " << sheetName << endl;
            size_t rowCount = readData.getRowCountInSheet(sheetName);
            size_t colCount = readData.getMaxColumnCount(sheetName);

            for (size_t row = 0; row < rowCount; row++)
            {
                for (size_t col = 0; col < colCount; col++)
                {
                    const wstring &value = readData.getCellValue(sheetName, row, col);
                    wcout << value << L"\t";
                }
                wcout << endl;
            }
        }
    }
    else
    {
        wcout << L"从文件读取失败: " << reader.getLastError() << endl;
    }

    // 测试5: 测试现有Excel文件
    wcout << L"\n测试5: 测试现有Excel文件..." << endl;
    wstring existingFile = L"../工作簿1.xlsx";
    ExcelData existingData;
    if (reader.read(existingFile, existingData))
    {
        wcout << L"成功从现有文件读取: " << existingFile << endl;

        // 显示读取的数据
        wcout << L"\n显示现有文件数据..." << endl;
        auto existingSheetNames = existingData.getSheetNames();
        for (const auto &sheetName : existingSheetNames)
        {
            wcout << L"\n工作表: " << sheetName << endl;
            size_t rowCount = existingData.getRowCountInSheet(sheetName);
            size_t colCount = existingData.getMaxColumnCount(sheetName);

            for (size_t row = 0; row < rowCount; row++)
            {
                for (size_t col = 0; col < colCount; col++)
                {
                    const wstring &value = existingData.getCellValue(sheetName, row, col);
                    wcout << value << L"\t";
                }
                wcout << endl;
            }
        }
    }
    else
    {
        wcout << L"从现有文件读取失败: " << reader.getLastError() << endl;
    }

    wcout << L"\n=== 测试完成 ===" << endl;
    return 0;
}