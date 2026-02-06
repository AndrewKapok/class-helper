#include "student.h"

// 默认构造函数
Student::Student() : name(L""), score(0.0), seat({0, 0})
{
}

// 带参数的构造函数
Student::Student(const wstring &name, double score, const Student::Seat &seat)
{
    // 验证数据合法性
    if (score < 0)
    {
        throw invalid_argument("分数不能为负数");
    }
    if (seat.row <= 0 || seat.col <= 0)
    {
        throw invalid_argument("座位的行和列必须为正数");
    }

    this->name = name;
    this->score = score;
    this->seat = seat;
}

// 拷贝构造函数
Student::Student(const Student &other)
{
    name = other.name;
    score = other.score;
    seat = other.seat;
}

// 赋值运算符重载
Student &Student::operator=(const Student &other)
{
    if (this != &other)
    {
        name = other.name;
        score = other.score;
        seat = other.seat;
    }
    return *this;
}

// 析构函数
Student::~Student()
{
    // 无需释放动态内存，因为成员变量都是栈上的或具有自动析构函数的类型
}

// 获取姓名
wstring Student::getName() const
{
    return name;
}

// 获取分数
double Student::getScore() const
{
    return score;
}

// 获取座位
Student::Seat Student::getSeat() const
{
    return seat;
}

// 设置姓名
void Student::setName(const wstring &name)
{
    this->name = name;
}

// 设置分数
void Student::setScore(double score)
{
    if (score < 0)
    {
        throw invalid_argument("分数不能为负数");
    }
    this->score = score;
}

// 设置座位
void Student::setSeat(const Student::Seat &seat)
{
    if (seat.row <= 0 || seat.col <= 0)
    {
        throw invalid_argument("座位的行和列必须为正数");
    }
    this->seat = seat;
}