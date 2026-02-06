#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <string>
#include "student.h"
#include "../excel/exceldata.h"
using namespace std;

/**
 * 将wstring类型转换为double类型
 * @param str 待转换的wstring对象
 * @param success 转换是否成功的标志
 * @return 转换后的double值，如果转换失败返回0.0
 */
double wstringToDouble(const wstring &str, bool &success);

/**
 * 解析Excel数据到Student数组
 * @param excelData Excel数据对象
 * @param sheetName 工作表名称
 * @param nameColIndex 姓名所在列索引
 * @param scoreColIndex 分数所在列索引
 * @return 包含解析后学生信息的数组
 */
vector<Student> parseExcelData(const ExcelData &excelData, const wstring &sheetName, size_t nameColIndex, size_t scoreColIndex);

/**
 * Allocate seats to students based on the specified strategy
 * @param students Vector of students to allocate seats for
 * @param layers Number of score layers to create
 * @param strategy Allocation strategy (1 for score stratification, 2 for group uniform allocation)
 * @param groupSize Size of each group (only used for strategy 2)
 * @return Vector of students with allocated seats in order
 */
vector<Student> allocateSeats(vector<Student> students, int layers, int strategy, int groupSize = 4);

#endif // ALGORITHM_H
