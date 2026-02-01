#ifndef EXCELWRITE_H
#define EXCELWRITE_H

#include <string>
#include "exceldata.h"

/**
 * Excel文件写入类
 * 用于直接生成Excel文件格式并写入数据
 */
class ExcelWrite
{
private:
    // 写入辅助函数
    /**
     * 写入文件头
     * @param file 文件流
     * @return 是否写入成功
     */
    bool writeFileHeader(std::ofstream &file);

    /**
     * 写入记录
     * @param file 文件流
     * @param data 数据存储对象
     * @return 是否写入成功
     */
    bool writeRecords(std::ofstream &file, const ExcelData &data);

    /**
     * 写入工作表
     * @param file 文件流
     * @param sheetName 工作表名称
     * @param data 数据存储对象
     * @return 是否写入成功
     */
    bool writeSheet(std::ofstream &file, const std::string &sheetName, const ExcelData &data);

    /**
     * 写入单元格
     * @param file 文件流
     * @param row 行索引
     * @param col 列索引
     * @param value 单元格值
     * @return 是否写入成功
     */
    bool writeCell(std::ofstream &file, size_t row, size_t col, const std::string &value);

public:
    /**
     * 构造函数
     */
    ExcelWrite() {}

    /**
     * 析构函数
     */
    ~ExcelWrite() {}

    /**
     * 将ExcelData对象写入文件
     * @param filePath 文件路径
     * @param data 数据存储对象
     * @return 是否写入成功
     */
    bool write(const std::string &filePath, const ExcelData &data);

    /**
     * 错误处理
     * @return 最后一次错误信息
     */
    std::string getLastError() const
    {
        return lastError;
    }

private:
    std::string lastError; ///< 错误信息
};

#endif // EXCELWRITE_H