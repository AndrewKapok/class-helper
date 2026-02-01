#include "student.h"

// 默认构造函数
Student::Student() : capacity(10), count(0)
{
    students = new StudentInfo[capacity];
}

// 带初始容量的构造函数
Student::Student(int initialCapacity) : capacity(initialCapacity), count(0)
{
    if (initialCapacity <= 0)
    {
        throw std::invalid_argument("初始容量必须大于0");
    }
    students = new StudentInfo[capacity];
}

// 拷贝构造函数
Student::Student(const Student &other) : capacity(other.capacity), count(other.count)
{
    // 深拷贝
    students = new StudentInfo[capacity];
    for (int i = 0; i < count; i++)
    {
        students[i] = other.students[i];
    }
}

// 赋值运算符重载
Student &Student::operator=(const Student &other)
{
    if (this != &other)
    {
        // 释放原有内存
        delete[] students;

        // 深拷贝
        capacity = other.capacity;
        count = other.count;
        students = new StudentInfo[capacity];
        for (int i = 0; i < count; i++)
        {
            students[i] = other.students[i];
        }
    }
    return *this;
}

// 析构函数
Student::~Student()
{
    delete[] students;
}

// 调整数组容量
void Student::resize(int newCapacity)
{
    if (newCapacity <= count)
    {
        throw std::invalid_argument("新容量必须大于当前学生数量");
    }

    StudentInfo *newStudents = new StudentInfo[newCapacity];
    for (int i = 0; i < count; i++)
    {
        newStudents[i] = students[i];
    }

    delete[] students;
    students = newStudents;
    capacity = newCapacity;
}

// 检查座位是否重复
bool Student::isSeatDuplicate(const Student::Seat &seat) const
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].seat.row == seat.row && students[i].seat.col == seat.col)
        {
            return true;
        }
    }
    return false;
}

// 获取姓名
std::string Student::getName(int index) const
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("索引越界：学生不存在");
    }
    return students[index].name;
}

// 获取分数
double Student::getScore(int index) const
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("索引越界：学生不存在");
    }
    return students[index].score;
}

// 获取座位
Student::Seat Student::getSeat(int index) const
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("索引越界：学生不存在");
    }
    return students[index].seat;
}

// 设置姓名
void Student::setName(int index, const std::string &name)
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("索引越界：学生不存在");
    }
    students[index].name = name;
}

// 设置分数
void Student::setScore(int index, double score)
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("索引越界：学生不存在");
    }
    if (score < 0)
    {
        throw std::invalid_argument("分数不能为负数");
    }
    students[index].score = score;
}

// 设置座位
void Student::setSeat(int index, const Student::Seat &seat)
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("索引越界：学生不存在");
    }
    if (seat.row <= 0 || seat.col <= 0)
    {
        throw std::invalid_argument("座位的行和列必须为正数");
    }
    // 检查是否与其他学生的座位重复
    for (int i = 0; i < count; i++)
    {
        if (i != index && students[i].seat.row == seat.row && students[i].seat.col == seat.col)
        {
            throw std::invalid_argument("座位重复");
        }
    }
    students[index].seat = seat;
}

// 添加学生信息
void Student::addStudent(const std::string &name, double score, const Student::Seat &seat)
{
    // 验证数据合法性
    if (score < 0)
    {
        throw std::invalid_argument("分数不能为负数");
    }
    if (seat.row <= 0 || seat.col <= 0)
    {
        throw std::invalid_argument("座位的行和列必须为正数");
    }
    if (isSeatDuplicate(seat))
    {
        throw std::invalid_argument("座位重复");
    }

    // 检查容量是否足够，不够则扩容
    if (count >= capacity)
    {
        resize(capacity * 2);
    }

    // 添加学生信息
    students[count].name = name;
    students[count].score = score;
    students[count].seat = seat;
    count++;
}

// 删除学生信息
void Student::removeStudent(int index)
{
    if (index < 0 || index >= count)
    {
        throw std::out_of_range("索引越界：学生不存在");
    }

    // 从索引位置开始，将后面的学生信息前移
    for (int i = index; i < count - 1; i++)
    {
        students[i] = students[i + 1];
    }
    count--;
}

// 获取当前学生数量
int Student::getCount() const
{
    return count;
}

// 获取当前数组容量
int Student::getCapacity() const
{
    return capacity;
}