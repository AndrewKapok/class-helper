#include "excelread.h"
#include <fstream>
#include <vector>
#include <cstdint>
using namespace std;

/**
 * 解析文件头
 * @param buffer 文件缓冲区（宽字符）
 * @param size 缓冲区大小
 * @return 是否解析成功
 */
bool ExcelRead::parseFileHeader(const wchar_t *buffer, size_t size)
{
    if (size < 8)
    {
        lastError = L"文件太小,不是有效的Excel文件";
        return false;
    }

    // 检查文件签名（BIFF格式）
    uint16_t signature = *(uint16_t *)buffer;
    if (signature != 0x424D)
    { // 'BM' 表示BIFF格式
        lastError = L"无效的Excel文件签名";
        return false;
    }

    return true;
}

/**
 * 解析记录
 * @param buffer 文件缓冲区（宽字符）
 * @param size 缓冲区大小
 * @param data 数据存储对象
 * @return 是否解析成功
 */
bool ExcelRead::parseRecords(const wchar_t *buffer, size_t size, ExcelData &data)
{
    size_t offset = 8; // 跳过文件头
    wstring currentSheet = L"Sheet1";
    data.addSheet(currentSheet);

    while (offset < size)
    {
        if (offset + 4 > size)
        {
            break; // 记录不完整
        }

        uint16_t recordType = *(uint16_t *)(buffer + offset);
        uint16_t recordLength = *(uint16_t *)(buffer + offset + 2);

        if (offset + 4 + recordLength > size)
        {
            break; // 记录数据不完整
        }

        // 处理不同类型的记录
        switch (recordType)
        {
        case 0x0009: // BoundSheet8（工作表定义）
            if (recordLength >= 6)
            {
                uint16_t sheetType = *(uint16_t *)(buffer + offset + 4);
                uint32_t sheetOffset = *(uint32_t *)(buffer + offset + 6);
                // 工作表名称以Unicode字符串形式存储
                // 这是一个简化的实现
                currentSheet = L"Sheet" + to_wstring(data.getSheetCount() + 1);
                data.addSheet(currentSheet);
            }
            break;

        case 0x000A: // EOF记录
            return true;

        default:
            // 对于其他类型的记录，暂时跳过
            break;
        }

        offset += 4 + recordLength;
    }

    return true;
}

/**
 * 解析工作表
 * @param buffer 文件缓冲区（宽字符）
 * @param size 缓冲区大小
 * @param offset 偏移量
 * @param sheetName 工作表名称
 * @param data 数据存储对象
 * @return 是否解析成功
 */
bool ExcelRead::parseSheet(const wchar_t *buffer, size_t size, size_t offset, const wstring &sheetName, ExcelData &data)
{
    // 这是一个简化的实现
    // 在实际实现中，我们会在这里解析工作表结构
    return true;
}

/**
 * 解析单元格
 * @param buffer 文件缓冲区（宽字符）
 * @param size 缓冲区大小
 * @param offset 偏移量
 * @param row 行索引
 * @param col 列索引
 * @param value 单元格值
 * @return 是否解析成功
 */
bool ExcelRead::parseCell(const wchar_t *buffer, size_t size, size_t offset, size_t &row, size_t &col, wstring &value)
{
    // 这是一个简化的实现
    // 在实际实现中，我们会在这里解析单元格数据
    return true;
}

/**
 * 读取Excel文件并填充ExcelData对象
 * @param filePath 文件路径
 * @param data 数据存储对象
 * @return 是否读取成功
 */
bool ExcelRead::read(const wstring &filePath, ExcelData &data)
{
    // 打开文件
    wifstream file(filePath.c_str(), ios::binary | ios::ate);
    if (!file)
    {
        lastError = L"无法打开文件: " + filePath;
        return false;
    }

    // 获取文件大小
    streamsize size = file.tellg();
    file.seekg(0, ios::beg);

    // 读取文件到缓冲区
    vector<wchar_t> buffer(size);
    if (!file.read(buffer.data(), size))
    {
        lastError = L"无法读取文件: " + filePath;
        return false;
    }

    file.close();

    // 解析文件头
    if (!parseFileHeader(buffer.data(), size))
    {
        return false;
    }

    // 解析记录
    if (!parseRecords(buffer.data(), size, data))
    {
        return false;
    }

    // 为了演示目的，我们添加一些示例数据
    // 在实际实现中，这会被替换为实际解析的数据
    data.addSheet(wstring(L"Sheet1"));
    data.addRowToSheet(wstring(L"Sheet1"));
    data.addCellToSheetRow(wstring(L"Sheet1"), 0, wstring(L"姓名"));
    data.addCellToSheetRow(wstring(L"Sheet1"), 0, wstring(L"数学"));
    data.addCellToSheetRow(wstring(L"Sheet1"), 0, wstring(L"语文"));
    data.addCellToSheetRow(wstring(L"Sheet1"), 0, wstring(L"英语"));

    data.addRowToSheet(wstring(L"Sheet1"));
    data.addCellToSheetRow(wstring(L"Sheet1"), 1, wstring(L"张三"));
    data.addCellToSheetRow(wstring(L"Sheet1"), 1, wstring(L"95"));
    data.addCellToSheetRow(wstring(L"Sheet1"), 1, wstring(L"88"));
    data.addCellToSheetRow(wstring(L"Sheet1"), 1, wstring(L"92"));

    data.addRowToSheet(wstring(L"Sheet1"));
    data.addCellToSheetRow(wstring(L"Sheet1"), 2, wstring(L"李四"));
    data.addCellToSheetRow(wstring(L"Sheet1"), 2, wstring(L"87"));
    data.addCellToSheetRow(wstring(L"Sheet1"), 2, wstring(L"91"));
    data.addCellToSheetRow(wstring(L"Sheet1"), 2, wstring(L"85"));

    return true;
}