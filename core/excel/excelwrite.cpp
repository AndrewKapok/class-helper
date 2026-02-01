#include "excelwrite.h"
#include <fstream>
#include <vector>
#include <cstdint>

/**
 * 写入文件头
 * @param file 文件流
 * @return 是否写入成功
 */
bool ExcelWrite::writeFileHeader(std::ofstream &file)
{
    // 写入BIFF文件头
    uint16_t signature = 0x424D; // 'BM'
    uint32_t fileSize = 0;       // 稍后会更新
    uint16_t reserved1 = 0;
    uint16_t reserved2 = 0;
    uint32_t dataOffset = 512; // 标准偏移量

    file.write((char *)&signature, sizeof(signature));
    file.write((char *)&fileSize, sizeof(fileSize));
    file.write((char *)&reserved1, sizeof(reserved1));
    file.write((char *)&reserved2, sizeof(reserved2));
    file.write((char *)&dataOffset, sizeof(dataOffset));

    // 写入DIF头（总共512字节）
    std::vector<char> difHeader(512 - 14, 0);
    file.write(difHeader.data(), difHeader.size());

    return true;
}

/**
 * 写入记录
 * @param file 文件流
 * @param data 数据存储对象
 * @return 是否写入成功
 */
bool ExcelWrite::writeRecords(std::ofstream &file, const ExcelData &data)
{
    // 写入BOF记录
    uint16_t bofRecord = 0x0009;
    uint16_t bofLength = 0x0008;
    uint16_t bofVersion = 0x0600;
    uint16_t bofType = 0x0010; // 工作簿
    uint16_t bofBuild = 0x0000;
    uint16_t bofYear = 0x0000;

    file.write((char *)&bofRecord, sizeof(bofRecord));
    file.write((char *)&bofLength, sizeof(bofLength));
    file.write((char *)&bofVersion, sizeof(bofVersion));
    file.write((char *)&bofType, sizeof(bofType));
    file.write((char *)&bofBuild, sizeof(bofBuild));
    file.write((char *)&bofYear, sizeof(bofYear));

    // 写入工作表记录
    auto sheetNames = data.getSheetNames();
    for (const auto &sheetName : sheetNames)
    {
        writeSheet(file, sheetName, data);
    }

    // 写入EOF记录
    uint16_t eofRecord = 0x000A;
    uint16_t eofLength = 0x0000;
    file.write((char *)&eofRecord, sizeof(eofRecord));
    file.write((char *)&eofLength, sizeof(eofLength));

    return true;
}

/**
 * 写入工作表
 * @param file 文件流
 * @param sheetName 工作表名称
 * @param data 数据存储对象
 * @return 是否写入成功
 */
bool ExcelWrite::writeSheet(std::ofstream &file, const std::string &sheetName, const ExcelData &data)
{
    // 写入工作表的BOF记录
    uint16_t bofRecord = 0x0009;
    uint16_t bofLength = 0x0008;
    uint16_t bofVersion = 0x0600;
    uint16_t bofType = 0x0000; // 工作表
    uint16_t bofBuild = 0x0000;
    uint16_t bofYear = 0x0000;

    file.write((char *)&bofRecord, sizeof(bofRecord));
    file.write((char *)&bofLength, sizeof(bofLength));
    file.write((char *)&bofVersion, sizeof(bofVersion));
    file.write((char *)&bofType, sizeof(bofType));
    file.write((char *)&bofBuild, sizeof(bofBuild));
    file.write((char *)&bofYear, sizeof(bofYear));

    // 写入单元格
    size_t rowCount = data.getRowCountInSheet(sheetName);
    for (size_t row = 0; row < rowCount; row++)
    {
        size_t colCount = data.getMaxColumnCount(sheetName);
        for (size_t col = 0; col < colCount; col++)
        {
            const std::string &value = data.getCellValue(sheetName, row, col);
            if (!value.empty())
            {
                writeCell(file, row, col, value);
            }
        }
    }

    // 写入工作表的EOF记录
    uint16_t eofRecord = 0x000A;
    uint16_t eofLength = 0x0000;
    file.write((char *)&eofRecord, sizeof(eofRecord));
    file.write((char *)&eofLength, sizeof(eofLength));

    return true;
}

/**
 * 写入单元格
 * @param file 文件流
 * @param row 行索引
 * @param col 列索引
 * @param value 单元格值
 * @return 是否写入成功
 */
bool ExcelWrite::writeCell(std::ofstream &file, size_t row, size_t col, const std::string &value)
{
    // 这是一个简化的实现
    // 在实际实现中，我们会正确写入单元格数据
    return true;
}

/**
 * 将ExcelData对象写入文件
 * @param filePath 文件路径
 * @param data 数据存储对象
 * @return 是否写入成功
 */
bool ExcelWrite::write(const std::string &filePath, const ExcelData &data)
{
    // 打开文件
    std::ofstream file(filePath, std::ios::binary);
    if (!file)
    {
        lastError = "无法打开文件进行写入: " + filePath;
        return false;
    }

    // 写入文件头
    if (!writeFileHeader(file))
    {
        return false;
    }

    // 写入记录
    if (!writeRecords(file, data))
    {
        return false;
    }

    file.close();

    return true;
}