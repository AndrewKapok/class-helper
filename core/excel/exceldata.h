#ifndef EXCELDATA_H
#define EXCELDATA_H

#include <string>
#include <vector>
#include <map>

/**
 * Excel数据存储类
 * 用于存储和管理Excel文件中的数据，以sheet为单位组织
 */
class ExcelData
{
private:
    /**
     * 单元格结构体
     * 存储单个单元格的值
     */
    struct Cell
    {
        std::string value; ///< 单元格值
        Cell(const std::string &v) : value(v) {}
    };

    /**
     * 行结构体
     * 存储一行中的多个单元格
     */
    struct Row
    {
        std::vector<Cell> cells; ///< 行中的单元格

        /**
         * 添加单元格到行
         * @param value 单元格值
         */
        void addCell(const std::string &value)
        {
            cells.emplace_back(value);
        }

        /**
         * 获取行中的单元格数量
         * @return 单元格数量
         */
        size_t getCellCount() const
        {
            return cells.size();
        }

        /**
         * 获取指定索引的单元格值
         * @param index 单元格索引
         * @return 单元格值
         */
        const std::string &getCellValue(size_t index) const
        {
            static std::string empty;
            if (index < cells.size())
            {
                return cells[index].value;
            }
            return empty;
        }
    };

    /**
     * 工作表结构体
     * 存储一个工作表中的多行数据
     */
    struct Sheet
    {
        std::string name;      ///< 工作表名称
        std::vector<Row> rows; ///< 工作表中的行

        /**
         * 构造函数
         * @param n 工作表名称
         */
        Sheet(const std::string &n) : name(n) {}

        /**
         * 添加行到工作表
         */
        void addRow()
        {
            rows.emplace_back(Row());
        }

        /**
         * 向指定行添加单元格
         * @param rowIndex 行索引
         * @param value 单元格值
         */
        void addCellToRow(size_t rowIndex, const std::string &value)
        {
            if (rowIndex < rows.size())
            {
                rows[rowIndex].addCell(value);
            }
        }

        /**
         * 获取工作表中的行数
         * @return 行数
         */
        size_t getRowCount() const
        {
            return rows.size();
        }

        /**
         * 获取指定索引的行
         * @param index 行索引
         * @return 行对象
         */
        const Row &getRow(size_t index) const
        {
            static Row empty;
            if (index < rows.size())
            {
                return rows[index];
            }
            return empty;
        }
    };

    std::map<std::string, Sheet> sheets; ///< 存储所有工作表

public:
    /**
     * 构造函数
     */
    ExcelData() {}

    // 工作表操作

    /**
     * 添加工作表
     * @param sheetName 工作表名称
     */
    void addSheet(const std::string &sheetName)
    {
        if (sheets.find(sheetName) == sheets.end())
        {
            sheets.emplace(sheetName, Sheet(sheetName));
        }
    }

    /**
     * 检查是否存在指定名称的工作表
     * @param sheetName 工作表名称
     * @return 是否存在
     */
    bool hasSheet(const std::string &sheetName) const
    {
        return sheets.find(sheetName) != sheets.end();
    }

    /**
     * 获取工作表数量
     * @return 工作表数量
     */
    size_t getSheetCount() const
    {
        return sheets.size();
    }

    /**
     * 获取所有工作表名称
     * @return 工作表名称列表
     */
    std::vector<std::string> getSheetNames() const
    {
        std::vector<std::string> names;
        for (const auto &pair : sheets)
        {
            names.push_back(pair.first);
        }
        return names;
    }

    // 行操作

    /**
     * 向指定工作表添加行
     * @param sheetName 工作表名称
     */
    void addRowToSheet(const std::string &sheetName)
    {
        auto it = sheets.find(sheetName);
        if (it != sheets.end())
        {
            it->second.addRow();
        }
    }

    /**
     * 获取指定工作表中的行数
     * @param sheetName 工作表名称
     * @return 行数
     */
    size_t getRowCountInSheet(const std::string &sheetName) const
    {
        auto it = sheets.find(sheetName);
        if (it != sheets.end())
        {
            return it->second.getRowCount();
        }
        return 0;
    }

    // 单元格操作

    /**
     * 向指定工作表的指定行添加单元格
     * @param sheetName 工作表名称
     * @param rowIndex 行索引
     * @param value 单元格值
     */
    void addCellToSheetRow(const std::string &sheetName, size_t rowIndex, const std::string &value)
    {
        auto it = sheets.find(sheetName);
        if (it != sheets.end())
        {
            it->second.addCellToRow(rowIndex, value);
        }
    }

    /**
     * 获取指定工作表、行、列的单元格值
     * @param sheetName 工作表名称
     * @param rowIndex 行索引
     * @param colIndex 列索引
     * @return 单元格值
     */
    const std::string &getCellValue(const std::string &sheetName, size_t rowIndex, size_t colIndex) const
    {
        static std::string empty;
        auto it = sheets.find(sheetName);
        if (it != sheets.end())
        {
            const Row &row = it->second.getRow(rowIndex);
            return row.getCellValue(colIndex);
        }
        return empty;
    }

    /**
     * 获取指定工作表中的最大列数
     * @param sheetName 工作表名称
     * @return 最大列数
     */
    size_t getMaxColumnCount(const std::string &sheetName) const
    {
        auto it = sheets.find(sheetName);
        if (it != sheets.end())
        {
            size_t maxCols = 0;
            for (const auto &row : it->second.rows)
            {
                if (row.getCellCount() > maxCols)
                {
                    maxCols = row.getCellCount();
                }
            }
            return maxCols;
        }
        return 0;
    }
};

#endif // EXCELDATA_H