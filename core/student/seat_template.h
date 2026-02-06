#ifndef SEAT_TEMPLATE_H
#define SEAT_TEMPLATE_H

#include <vector>
#include <unordered_map>
#include "student.h"

class SeatTemplate
{
public:
    enum class SeatStatus {
        EMPTY,    // 空座位
        OCCUPIED  // 已占用
    };

    struct Group {
        int id;                    // 小组唯一标识
        std::vector<Student::Seat> seats; // 小组包含的座位
    };

private:
    int size; // 座位网格的初始大小（x×x）
    std::vector<std::vector<SeatStatus>> grid; // 座位网格状态
    std::vector<bool> isWalkwayRow; // 标识是否为走道行
    std::vector<bool> isWalkwayCol; // 标识是否为走道列
    std::vector<Group> groups; // 小组配置
    std::unordered_map<int, std::unordered_map<int, int>> seatToGroup; // 座位到小组的映射
    int nextGroupId; // 下一个小组的ID

public:
    // 构造函数和析构函数
    SeatTemplate(int size); // 构造函数，初始化size×size的座位网格
    ~SeatTemplate(); // 析构函数

    // 座位网格初始化
    void initializeGrid(int size); // 初始化座位网格和走道标记

    // 走道设置
    void insertWalkwayRow(int row); // 在指定行之后插入走道行
    void insertWalkwayCol(int col); // 在指定列之后插入走道列
    void removeWalkwayRow(int row); // 移除指定的走道行
    void removeWalkwayCol(int col); // 移除指定的走道列

    // 小组管理
    int addGroup(const std::vector<Student::Seat>& seats); // 添加小组，返回小组ID
    bool removeGroup(int groupId); // 移除指定ID的小组
    std::vector<Student::Seat> getGroupSeats(int groupId) const; // 获取小组包含的座位
    int getSeatGroup(int row, int col) const; // 获取座位所属的小组ID，返回-1表示不属于任何小组
    bool isSeatInGroup(int row, int col) const; // 检查座位是否已属于某个小组

    // 座位状态管理
    SeatStatus getSeatStatus(int row, int col) const; // 获取座位状态
    void setSeatStatus(int row, int col, SeatStatus status); // 修改座位状态

    // 网格信息查询
    int getGridSize() const; // 获取原始网格尺寸
    int getTotalRows() const; // 获取总行数（包括走道）
    int getTotalCols() const; // 获取总列数（包括走道）
    bool isValidPosition(int row, int col) const; // 检查位置坐标是否有效
    bool isWalkway(int row, int col) const; // 检查指定位置是否为走道
};

#endif // SEAT_TEMPLATE_H
