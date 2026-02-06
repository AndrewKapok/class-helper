#include "algorithm.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <random>
#include "../excel/exceldata.h"
using namespace std;
vector<Student> arr;

/**
 * 将wstring类型转换为double类型
 * @param str 待转换的wstring对象
 * @param success 转换是否成功的标志
 * @return 转换后的double值，如果转换失败返回0.0
 */
double wstringToDouble(const wstring &str, bool &success)
{
    success = false;
    if (str.empty())
    {
        return 0.0;
    }
    wstringstream ws(str);
    double result = 0.0;
    ws >> result;
    if (ws.fail() || !ws.eof())
    {
        return 0.0;
    }
    success = true;
    return result;
}

/**
 * 解析Excel数据到Student数组
 * @param excelData Excel数据对象
 * @param sheetName 工作表名称
 * @param nameColIndex 姓名所在列索引
 * @param scoreColIndex 分数所在列索引
 * @return 包含解析后学生信息的数组
 */
vector<Student> parseExcelData(const ExcelData &excelData, const wstring &sheetName, size_t nameColIndex, size_t scoreColIndex)
{
    vector<Student> result;
    if (!excelData.hasSheet(sheetName))
    {
        return result;
    }
    size_t rowCount = excelData.getRowCountInSheet(sheetName);
    for (size_t i = 0; i < rowCount; ++i)
    {
        const wstring &nameStr = excelData.getCellValue(sheetName, i, nameColIndex);
        const wstring &scoreStr = excelData.getCellValue(sheetName, i, scoreColIndex);
        if (nameStr.empty() || scoreStr.empty())
        {
            continue;
        }
        bool success = false;
        double score = wstringToDouble(scoreStr, success);
        if (!success)
        {
            continue;
        }
        Student student;
        student.setName(nameStr);
        student.setScore(score);
        Student::Seat seat = {0, 0};
        student.setSeat(seat);
        result.push_back(student);
    }
    return result;
}

/**
 * Allocate seats to students based on the specified strategy
 * @param students Vector of students to allocate seats for
 * @param layers Number of score layers to create
 * @param strategy Allocation strategy (1 for score stratification, 2 for group uniform allocation)
 * @param groupSize Size of each group (only used for strategy 2)
 * @return Vector of students with allocated seats in order
 */
vector<Student> allocateSeats(vector<Student> students, int layers, int strategy, int groupSize)
{
    // Validate input parameters
    if (students.empty())
    {
        return students;
    }
    
    if (layers <= 0)
    {
        layers = 1;
    }
    
    // Handle edge case: layers > number of students
    if (layers > students.size())
    {
        layers = students.size();
    }
    
    // Sort students by score in descending order, then by name
    sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        if (a.getScore() != b.getScore())
        {
            return a.getScore() > b.getScore();
        }
        return a.getName() < b.getName();
    });
    
    // Calculate layer sizes
    int studentCount = students.size();
    int baseSize = studentCount / layers;
    int remainder = studentCount % layers;
    
    // Create layers
    vector<vector<Student>> studentLayers;
    int currentIndex = 0;
    
    for (int i = 0; i < layers; ++i)
    {
        int layerSize = baseSize + (i < remainder ? 1 : 0);
        vector<Student> layer(students.begin() + currentIndex, students.begin() + currentIndex + layerSize);
        studentLayers.push_back(layer);
        currentIndex += layerSize;
    }
    
    vector<Student> result;
    
    if (strategy == 1)
    {
        // Strategy 1: Score stratification
        for (auto &layer : studentLayers)
        {
            // Shuffle the layer
            shuffle(layer.begin(), layer.end(), default_random_engine(random_device{}()));
            // Add to result
            result.insert(result.end(), layer.begin(), layer.end());
        }
    }
    else
    {
        // Strategy 2: Group uniform allocation
        // Shuffle each layer first
        for (auto &layer : studentLayers)
        {
            shuffle(layer.begin(), layer.end(), default_random_engine(random_device{}()));
        }
        
        // Form groups with students from each layer
        int currentLayerIndex = 0;
        while (true)
        {
            bool hasStudents = false;
            vector<Student> group;
            
            for (int i = 0; i < layers; ++i)
            {
                if (currentLayerIndex < studentLayers[i].size())
                {
                    group.push_back(studentLayers[i][currentLayerIndex]);
                    hasStudents = true;
                }
            }
            
            if (!hasStudents)
            {
                break;
            }
            
            result.insert(result.end(), group.begin(), group.end());
            currentLayerIndex++;
        }
    }
    
    // Assign seat positions
    int row = 1, col = 1;
    for (auto &student : result)
    {
        Student::Seat seat = {row, col};
        student.setSeat(seat);
        col++;
        if (col > 6) // Assuming 6 seats per row
        {
            col = 1;
            row++;
        }
    }
    
    // Store result in global arr
    arr = result;
    
    return result;
}
