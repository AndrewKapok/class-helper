#ifndef EXCELREAD_H
#define EXCELREAD_H

#include <string>
#include "exceldata.h"
using namespace std;

/**
 * Excel文件读取类
 * 用于直接解析Excel文件格式并读取数据
 */
class ExcelRead
{
private:
    // 解析辅助函数
    /**
     * 解析文件头
     * @param buffer 文件缓冲区（宽字符）
     * @param size 缓冲区大小
     * @return 是否解析成功
     */
    bool parseFileHeader(const wchar_t *buffer, size_t size);

    /**
     * 解析记录
     * @param buffer 文件缓冲区（宽字符）
     * @param size 缓冲区大小
     * @param data 数据存储对象
     * @return 是否解析成功
     */
    bool parseRecords(const wchar_t *buffer, size_t size, ExcelData &data);

    /**
     * 解析工作表
     * @param buffer 文件缓冲区（宽字符）
     * @param size 缓冲区大小
     * @param offset 偏移量
     * @param sheetName 工作表名称
     * @param data 数据存储对象
     * @return 是否解析成功
     */
    bool parseSheet(const wchar_t *buffer, size_t size, size_t offset, const wstring &sheetName, ExcelData &data);

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
    bool parseCell(const wchar_t *buffer, size_t size, size_t offset, size_t &row, size_t &col, wstring &value);

public:
    /**
     * 构造函数
     */
    ExcelRead() {}

    /**
     * 析构函数
     */
    ~ExcelRead() {}

    /**
     * 读取Excel文件并填充ExcelData对象
     * @param filePath 文件路径（宽字符）
     * @param data 数据存储对象
     * @return 是否读取成功
     */
    bool read(const wstring &filePath, ExcelData &data);

    /**
     * 错误处理
     * @return 最后一次错误信息（宽字符）
     */
    wstring getLastError() const
    {
        return lastError;
    }

private:
    wstring lastError; ///< 错误信息（宽字符）
};

#endif // EXCELREAD_H