#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <stdexcept>

class Student
{
public:
    // 座位结构体
    struct Seat
    {
        int row; // 行
        int col; // 列
    };

private:
    // 学生信息结构体
    struct StudentInfo
    {
        std::string name; // 姓名
        double score;     // 分数
        Seat seat;        // 座位
    };

    StudentInfo *students; // 学生信息数组
    int capacity;          // 数组容量
    int count;             // 实际学生数量

public:
    // 构造函数
    Student();                    // 默认构造函数
    Student(int initialCapacity); // 带初始容量的构造函数

    // 拷贝构造函数
    Student(const Student &other);

    // 赋值运算符重载
    Student &operator=(const Student &other);

    // 析构函数
    ~Student();

    // 数据访问方法
    std::string getName(int index) const;
    double getScore(int index) const;
    Seat getSeat(int index) const;

    // 数据修改方法
    void setName(int index, const std::string &name);
    void setScore(int index, double score);
    void setSeat(int index, const Seat &seat);

    // 学生管理方法
    void addStudent(const std::string &name, double score, const Seat &seat);
    void removeStudent(int index);

    // 辅助方法
    int getCount() const;    // 获取当前学生数量
    int getCapacity() const; // 获取当前数组容量

private:
    // 私有辅助方法
    void resize(int newCapacity);                 // 调整数组容量
    bool isSeatDuplicate(const Seat &seat) const; // 检查座位是否重复
};

#endif // STUDENT_H