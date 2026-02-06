#include <iostream>
#include "exceldata.h"
#include "excelread.h"
#include "excelwrite.h"
using namespace std;
/**
 * 测试Excel边界情况和异常处理
 */
int main()
{
    wcout << L"=== Excel边界和异常测试 ===" << endl;

    // 测试1: 空ExcelData
    wcout << L"\n测试1: 测试空ExcelData..." << endl;
    ExcelData emptyData;
    ExcelWrite writer;
    wstring emptyFile = L"empty_output.xls";
    if (writer.write(emptyFile, emptyData))
    {
        wcout << L"成功写入空数据到文件: " << emptyFile << endl;
    }
    else
    {
        wcout << L"写入空数据失败: " << writer.getLastError() << endl;
    }

    // 测试2: 不存在的文件
    wcout << L"\n测试2: 测试不存在的文件..." << endl;
    ExcelData nonExistentData;
    ExcelRead reader;
    wstring nonExistentFile = L"non_existent_file.xls";
    if (reader.read(nonExistentFile, nonExistentData))
    {
        wcout << L"成功从不存在的文件读取: " << nonExistentFile << endl;
    }
    else
    {
        wcout << L"从不存在的文件读取失败 (预期): " << reader.getLastError() << endl;
    }

    // 测试3: 单个单元格数据
    wcout << L"\n测试3: 测试单个单元格数据..." << endl;
    ExcelData singleCellData;
    singleCellData.addSheet(L"Sheet1");
    singleCellData.addRowToSheet(L"Sheet1");
    singleCellData.addCellToSheetRow(L"Sheet1", 0, L"Hello World");
    wstring singleCellFile = L"single_cell_output.xls";
    if (writer.write(singleCellFile, singleCellData))
    {
        wcout << L"成功写入单个单元格数据到文件: " << singleCellFile << endl;
    }
    else
    {
        wcout << L"写入单个单元格数据失败: " << writer.getLastError() << endl;
    }

    // 测试4: 大量行数据
    wcout << L"\n测试4: 测试大量行数据..." << endl;
    ExcelData largeData;
    largeData.addSheet(L"Sheet1");
    for (int i = 0; i < 100; i++)
    {
        largeData.addRowToSheet(L"Sheet1");
        largeData.addCellToSheetRow(L"Sheet1", i, L"Row " + to_wstring(i));
        largeData.addCellToSheetRow(L"Sheet1", i, L"Value " + to_wstring(i));
    }
    wstring largeFile = L"large_output.xls";
    if (writer.write(largeFile, largeData))
    {
        wcout << L"成功写入大量数据到文件: " << largeFile << endl;
    }
    else
    {
        wcout << L"写入大量数据失败: " << writer.getLastError() << endl;
    }

    wcout << L"\n=== 边界和异常测试完成 ===" << endl;
    return 0;
}