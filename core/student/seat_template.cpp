#include "seat_template.h"
#include <stdexcept>
#include <algorithm>

// 构造函数
SeatTemplate::SeatTemplate(int size)
    : size(size), nextGroupId(1)
{
    if (size <= 0) {
        throw std::invalid_argument("Size must be a positive integer");
    }
    initializeGrid(size);
}

// 析构函数
SeatTemplate::~SeatTemplate()
{
}

// 初始化座位网格和走道标记
void SeatTemplate::initializeGrid(int size)
{
    this->size = size;
    grid.resize(size, std::vector<SeatStatus>(size, SeatStatus::EMPTY));
    isWalkwayRow.clear();
    isWalkwayRow.resize(size, false);
    isWalkwayCol.clear();
    isWalkwayCol.resize(size, false);
    seatToGroup.clear();
    groups.clear();
    nextGroupId = 1;
}

// 检查位置坐标是否有效
bool SeatTemplate::isValidPosition(int row, int col) const
{
    int totalRows = getTotalRows();
    int totalCols = getTotalCols();
    return row >= 0 && row < totalRows && col >= 0 && col < totalCols;
}

// 检查指定位置是否为走道
bool SeatTemplate::isWalkway(int row, int col) const
{
    if (!isValidPosition(row, col)) {
        throw std::out_of_range("Invalid position");
    }
    return isWalkwayRow[row] || isWalkwayCol[col];
}

// 在指定行之后插入走道行
void SeatTemplate::insertWalkwayRow(int row)
{
    int totalRows = getTotalRows();
    if (row < 0 || row >= totalRows) {
        throw std::out_of_range("Invalid row index");
    }
    
    // 插入走道标记
    isWalkwayRow.insert(isWalkwayRow.begin() + row + 1, true);
    
    // 调整小组中的座位位置
    for (auto& group : groups) {
        for (auto& seat : group.seats) {
            if (seat.row > row) {
                seat.row++;
            }
        }
    }
    
    // 调整座位到小组的映射
    std::unordered_map<int, std::unordered_map<int, int>> newSeatToGroup;
    for (const auto& rowMap : seatToGroup) {
        int oldRow = rowMap.first;
        int newRow = oldRow > row ? oldRow + 1 : oldRow;
        for (const auto& colMap : rowMap.second) {
            newSeatToGroup[newRow][colMap.first] = colMap.second;
        }
    }
    seatToGroup = newSeatToGroup;
}

// 在指定列之后插入走道列
void SeatTemplate::insertWalkwayCol(int col)
{
    int totalCols = getTotalCols();
    if (col < 0 || col >= totalCols) {
        throw std::out_of_range("Invalid column index");
    }
    
    // 插入走道标记
    isWalkwayCol.insert(isWalkwayCol.begin() + col + 1, true);
    
    // 调整小组中的座位位置
    for (auto& group : groups) {
        for (auto& seat : group.seats) {
            if (seat.col > col) {
                seat.col++;
            }
        }
    }
    
    // 调整座位到小组的映射
    std::unordered_map<int, std::unordered_map<int, int>> newSeatToGroup;
    for (const auto& rowMap : seatToGroup) {
        int row = rowMap.first;
        for (const auto& colMap : rowMap.second) {
            int oldCol = colMap.first;
            int newCol = oldCol > col ? oldCol + 1 : oldCol;
            newSeatToGroup[row][newCol] = colMap.second;
        }
    }
    seatToGroup = newSeatToGroup;
}

// 移除指定的走道行
void SeatTemplate::removeWalkwayRow(int row)
{
    int totalRows = getTotalRows();
    if (row < 0 || row >= totalRows) {
        throw std::out_of_range("Invalid row index");
    }
    
    if (!isWalkwayRow[row]) {
        throw std::invalid_argument("Specified row is not a walkway");
    }
    
    // 移除走道标记
    isWalkwayRow.erase(isWalkwayRow.begin() + row);
    
    // 调整小组中的座位位置
    for (auto& group : groups) {
        auto it = std::remove_if(group.seats.begin(), group.seats.end(),
            [row](const Student::Seat& seat) {
                return seat.row == row;
            });
        group.seats.erase(it, group.seats.end());
        
        for (auto& seat : group.seats) {
            if (seat.row > row) {
                seat.row--;
            }
        }
    }
    
    // 调整座位到小组的映射
    std::unordered_map<int, std::unordered_map<int, int>> newSeatToGroup;
    for (const auto& rowMap : seatToGroup) {
        int oldRow = rowMap.first;
        if (oldRow == row) {
            continue; // 跳过走道行
        }
        int newRow = oldRow > row ? oldRow - 1 : oldRow;
        for (const auto& colMap : rowMap.second) {
            newSeatToGroup[newRow][colMap.first] = colMap.second;
        }
    }
    seatToGroup = newSeatToGroup;
}

// 移除指定的走道列
void SeatTemplate::removeWalkwayCol(int col)
{
    int totalCols = getTotalCols();
    if (col < 0 || col >= totalCols) {
        throw std::out_of_range("Invalid column index");
    }
    
    if (!isWalkwayCol[col]) {
        throw std::invalid_argument("Specified column is not a walkway");
    }
    
    // 移除走道标记
    isWalkwayCol.erase(isWalkwayCol.begin() + col);
    
    // 调整小组中的座位位置
    for (auto& group : groups) {
        auto it = std::remove_if(group.seats.begin(), group.seats.end(),
            [col](const Student::Seat& seat) {
                return seat.col == col;
            });
        group.seats.erase(it, group.seats.end());
        
        for (auto& seat : group.seats) {
            if (seat.col > col) {
                seat.col--;
            }
        }
    }
    
    // 调整座位到小组的映射
    std::unordered_map<int, std::unordered_map<int, int>> newSeatToGroup;
    for (const auto& rowMap : seatToGroup) {
        int row = rowMap.first;
        for (const auto& colMap : rowMap.second) {
            int oldCol = colMap.first;
            if (oldCol == col) {
                continue; // 跳走过道列
            }
            int newCol = oldCol > col ? oldCol - 1 : oldCol;
            newSeatToGroup[row][newCol] = colMap.second;
        }
    }
    seatToGroup = newSeatToGroup;
}

// 获取座位状态
SeatTemplate::SeatStatus SeatTemplate::getSeatStatus(int row, int col) const
{
    if (!isValidPosition(row, col)) {
        throw std::out_of_range("Invalid position");
    }
    
    if (isWalkway(row, col)) {
        throw std::invalid_argument("Position is a walkway, not a seat");
    }
    
    return grid[row][col];
}

// 修改座位状态
void SeatTemplate::setSeatStatus(int row, int col, SeatStatus status)
{
    if (!isValidPosition(row, col)) {
        throw std::out_of_range("Invalid position");
    }
    
    if (isWalkway(row, col)) {
        throw std::invalid_argument("Position is a walkway, not a seat");
    }
    
    grid[row][col] = status;
}

// 获取原始网格尺寸
int SeatTemplate::getGridSize() const
{
    return size;
}

// 获取总行数（包括走道）
int SeatTemplate::getTotalRows() const
{
    return isWalkwayRow.size();
}

// 获取总列数（包括走道）
int SeatTemplate::getTotalCols() const
{
    return isWalkwayCol.size();
}

// 添加小组
int SeatTemplate::addGroup(const std::vector<Student::Seat>& seats)
{
    // 检查所有座位是否有效且不是走道
    for (const auto& seat : seats) {
        if (!isValidPosition(seat.row, seat.col)) {
            throw std::out_of_range("Invalid position in group");
        }
        if (isWalkway(seat.row, seat.col)) {
            throw std::invalid_argument("Cannot include walkway in group");
        }
        if (seatToGroup.count(seat.row) && seatToGroup[seat.row].count(seat.col)) {
            throw std::invalid_argument("Seat already belongs to a group");
        }
    }
    
    // 创建新小组
    Group newGroup;
    newGroup.id = nextGroupId++;
    newGroup.seats = seats;
    groups.push_back(newGroup);
    
    // 更新座位到小组的映射
    for (const auto& seat : seats) {
        seatToGroup[seat.row][seat.col] = newGroup.id;
    }
    
    return newGroup.id;
}

// 移除指定ID的小组
bool SeatTemplate::removeGroup(int groupId)
{
    auto it = std::find_if(groups.begin(), groups.end(),
        [groupId](const Group& group) {
            return group.id == groupId;
        });
    
    if (it == groups.end()) {
        return false;
    }
    
    // 从映射中移除小组的所有座位
    for (const auto& seat : it->seats) {
        seatToGroup[seat.row].erase(seat.col);
    }
    
    // 从小组列表中移除
    groups.erase(it);
    return true;
}

// 获取小组包含的座位
std::vector<Student::Seat> SeatTemplate::getGroupSeats(int groupId) const
{
    auto it = std::find_if(groups.begin(), groups.end(),
        [groupId](const Group& group) {
            return group.id == groupId;
        });
    
    if (it == groups.end()) {
        throw std::invalid_argument("Group not found");
    }
    
    return it->seats;
}

// 获取座位所属的小组ID，返回-1表示不属于任何小组
int SeatTemplate::getSeatGroup(int row, int col) const
{
    if (!isValidPosition(row, col)) {
        throw std::out_of_range("Invalid position");
    }
    
    if (isWalkway(row, col)) {
        throw std::invalid_argument("Position is a walkway, not a seat");
    }
    
    if (seatToGroup.count(row) && seatToGroup.at(row).count(col)) {
        return seatToGroup.at(row).at(col);
    }
    
    return -1;
}

// 检查座位是否已属于某个小组
bool SeatTemplate::isSeatInGroup(int row, int col) const
{
    return getSeatGroup(row, col) != -1;
}
