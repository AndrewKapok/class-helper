#include <iostream>
#include <fstream>
#include <io.h>
#include <fcntl.h>
#include "algorithm.h"
using namespace std;

/**
 * 测试座位分配功能
 */
int main()
{
    // 打开文件用于写入UTF-8文本
    FILE* fp = fopen("test_output.txt", "w");
    if (fp == NULL) {
        return 1;
    }

    // 创建测试学生数据
    vector<Student> students;
    
    // 添加测试学生
    Student student1;
    student1.setName(L"张三");
    student1.setScore(95);
    students.push_back(student1);
    
    Student student2;
    student2.setName(L"李四");
    student2.setScore(92);
    students.push_back(student2);
    
    Student student3;
    student3.setName(L"王五");
    student3.setScore(88);
    students.push_back(student3);
    
    Student student4;
    student4.setName(L"赵六");
    student4.setScore(85);
    students.push_back(student4);
    
    Student student5;
    student5.setName(L"钱七");
    student5.setScore(82);
    students.push_back(student5);
    
    Student student6;
    student6.setName(L"孙八");
    student6.setScore(78);
    students.push_back(student6);
    
    Student student7;
    student7.setName(L"周九");
    student7.setScore(75);
    students.push_back(student7);
    
    Student student8;
    student8.setName(L"吴十");
    student8.setScore(72);
    students.push_back(student8);
    
    fprintf(fp, "=== 座位分配测试 ===\n\n");

    // 测试1: 策略1 - 成绩分层法
    fprintf(fp, "测试1: 策略1 - 成绩分层法 (2层)\n");
    fprintf(fp, "座位分配结果:\n");
    vector<Student> result1 = allocateSeats(students, 2, 1, 4);
    
    for (size_t i = 0; i < result1.size(); ++i)
    {
        Student::Seat seat = result1[i].getSeat();
        // 将wstring转换为UTF-8字符串
        wstring name = result1[i].getName();
        string utf8Name;
        for (wchar_t c : name) {
            if (c < 0x80) {
                utf8Name += (char)c;
            } else if (c < 0x800) {
                utf8Name += (char)(0xC0 | (c >> 6));
                utf8Name += (char)(0x80 | (c & 0x3F));
            } else {
                utf8Name += (char)(0xE0 | (c >> 12));
                utf8Name += (char)(0x80 | ((c >> 6) & 0x3F));
                utf8Name += (char)(0x80 | (c & 0x3F));
            }
        }
        fprintf(fp, "座位 %zu: %s (分数: %.1f, 位置: %d排%d列)\n", 
                i + 1, utf8Name.c_str(), result1[i].getScore(), 
                seat.row, seat.col);
    }
    
    // 测试2: 策略2 - 分组均匀分配法
    fprintf(fp, "\n测试2: 策略2 - 分组均匀分配法 (2层, 每组4人)\n");
    fprintf(fp, "座位分配结果:\n");
    vector<Student> result2 = allocateSeats(students, 2, 2, 4);
    
    for (size_t i = 0; i < result2.size(); ++i)
    {
        Student::Seat seat = result2[i].getSeat();
        wstring name = result2[i].getName();
        string utf8Name;
        for (wchar_t c : name) {
            if (c < 0x80) {
                utf8Name += (char)c;
            } else if (c < 0x800) {
                utf8Name += (char)(0xC0 | (c >> 6));
                utf8Name += (char)(0x80 | (c & 0x3F));
            } else {
                utf8Name += (char)(0xE0 | (c >> 12));
                utf8Name += (char)(0x80 | ((c >> 6) & 0x3F));
                utf8Name += (char)(0x80 | (c & 0x3F));
            }
        }
        fprintf(fp, "座位 %zu: %s (分数: %.1f, 位置: %d排%d列)\n", 
                i + 1, utf8Name.c_str(), result2[i].getScore(), 
                seat.row, seat.col);
    }
    
    // 测试3: 边界情况 - 学生人数少于层数
    fprintf(fp, "\n测试3: 边界情况 - 学生人数少于层数\n");
    fprintf(fp, "座位分配结果:\n");
    vector<Student> smallGroup;
    smallGroup.push_back(student1);
    smallGroup.push_back(student2);
    
    vector<Student> result3 = allocateSeats(smallGroup, 5, 1, 4);
    
    for (size_t i = 0; i < result3.size(); ++i)
    {
        Student::Seat seat = result3[i].getSeat();
        wstring name = result3[i].getName();
        string utf8Name;
        for (wchar_t c : name) {
            if (c < 0x80) {
                utf8Name += (char)c;
            } else if (c < 0x800) {
                utf8Name += (char)(0xC0 | (c >> 6));
                utf8Name += (char)(0x80 | (c & 0x3F));
            } else {
                utf8Name += (char)(0xE0 | (c >> 12));
                utf8Name += (char)(0x80 | ((c >> 6) & 0x3F));
                utf8Name += (char)(0x80 | (c & 0x3F));
            }
        }
        fprintf(fp, "座位 %zu: %s (分数: %.1f, 位置: %d排%d列)\n", 
                i + 1, utf8Name.c_str(), result3[i].getScore(), 
                seat.row, seat.col);
    }
    
    fprintf(fp, "\n=== 测试完成 ===\n");
    fclose(fp);
    
    return 0;
}
