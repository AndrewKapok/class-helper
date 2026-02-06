#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <stdexcept>
using namespace std;

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
    wstring name; // 姓名（UTF-8 编码）
    double score; // 分数
    Seat seat;    // 座位

public:
    // 构造函数
    Student();                                                    // 默认构造函数
    Student(const wstring &name, double score, const Seat &seat); // 带参数的构造函数

    // 拷贝构造函数
    Student(const Student &other);

    // 赋值运算符重载
    Student &operator=(const Student &other);

    // 析构函数
    ~Student();

    // 数据访问方法
    wstring getName() const;
    double getScore() const;
    Seat getSeat() const;

    // 数据修改方法
    void setName(const wstring &name);
    void setScore(double score);
    void setSeat(const Seat &seat);
};

#endif // STUDENT_H