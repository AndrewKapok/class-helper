#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
命令行版本的自动座位分配系统
"""

import os
import sys
import json
from datetime import datetime


class SimpleDataProcessor:
    """简化的数据处理器"""
    
    def __init__(self):
        """初始化数据处理器"""
        self.students = []
        self.relations = {
            "must": [],
            "cannot": []
        }
    
    def load_sample_data(self):
        """加载示例数据"""
        self.students = [
            {"姓名": "张三", "学号": "1001", "总分": 95, "语文": 90, "数学": 100, "英语": 95},
            {"姓名": "李四", "学号": "1002", "总分": 90, "语文": 85, "数学": 95, "英语": 90},
            {"姓名": "王五", "学号": "1003", "总分": 85, "语文": 80, "数学": 90, "英语": 85},
            {"姓名": "赵六", "学号": "1004", "总分": 80, "语文": 75, "数学": 85, "英语": 80},
            {"姓名": "钱七", "学号": "1005", "总分": 75, "语文": 70, "数学": 80, "英语": 75},
            {"姓名": "孙八", "学号": "1006", "总分": 70, "语文": 65, "数学": 75, "英语": 70},
            {"姓名": "周九", "学号": "1007", "总分": 65, "语文": 60, "数学": 70, "英语": 65},
            {"姓名": "吴十", "学号": "1008", "总分": 60, "语文": 55, "数学": 65, "英语": 60}
        ]
        return self.students


class SimpleSeatingAlgorithm:
    """简化的座位分配算法"""
    
    def __init__(self):
        """初始化算法"""
        pass
    
    def assign_by_level(self, students, rows=3, cols=3):
        """成绩分层法"""
        # 按总分排序
        sorted_students = sorted(students, key=lambda x: x["总分"], reverse=True)
        
        # 初始化座位
        seating = [[None for _ in range(cols)] for _ in range(rows)]
        
        # 分配座位
        index = 0
        for i in range(rows):
            for j in range(cols):
                if index < len(sorted_students):
                    seating[i][j] = sorted_students[index]
                    index += 1
        
        return seating
    
    def assign_by_group(self, students, rows=3, cols=3, groups=4):
        """分组均匀分配法"""
        import random
        # 随机打乱
        shuffled_students = students.copy()
        random.shuffle(shuffled_students)
        
        # 初始化座位
        seating = [[None for _ in range(cols)] for _ in range(rows)]
        
        # 分配座位
        index = 0
        for i in range(rows):
            for j in range(cols):
                if index < len(shuffled_students):
                    seating[i][j] = shuffled_students[index]
                    index += 1
        
        return seating


class SimpleExport:
    """简化的导出功能"""
    
    def __init__(self):
        """初始化导出"""
        pass
    
    def export_to_json(self, seating, filename="seating_result.json"):
        """导出到JSON文件"""
        result = []
        seat_number = 1
        
        for row_idx, row in enumerate(seating):
            for col_idx, student in enumerate(row):
                if student:
                    result.append({
                        "座位号": seat_number,
                        "行数": row_idx + 1,
                        "列数": col_idx + 1,
                        "姓名": student.get("姓名", ""),
                        "学号": student.get("学号", ""),
                        "总分": student.get("总分", "")
                    })
                    seat_number += 1
        
        with open(filename, "w", encoding="utf-8") as f:
            json.dump(result, f, ensure_ascii=False, indent=2)
        
        print(f"结果已导出到 {filename}")
    
    def print_seating(self, seating):
        """打印座位分配结果"""
        print("\n座位分配结果:")
        print("-" * 80)
        
        for row_idx, row in enumerate(seating):
            row_str = f"第{row_idx + 1}行: "
            for col_idx, student in enumerate(row):
                if student:
                    row_str += f"[{student['姓名']}({student['总分']})] "
                else:
                    row_str += "[空] "
            print(row_str)
        
        print("-" * 80)


def main():
    """主函数"""
    print("=== 自动座位分配系统（命令行版） ===")
    print("1. 加载示例数据")
    print("2. 成绩分层法分配")
    print("3. 分组均匀分配法")
    print("4. 导出结果")
    print("5. 退出")
    
    data_processor = SimpleDataProcessor()
    algorithm = SimpleSeatingAlgorithm()
    exporter = SimpleExport()
    
    students = []
    seating_result = None
    
    while True:
        choice = input("\n请选择操作 (1-5): ")
        
        if choice == "1":
            students = data_processor.load_sample_data()
            print(f"\n已加载 {len(students)} 条学生数据")
            for student in students:
                print(f"{student['姓名']} - 学号: {student['学号']} - 总分: {student['总分']}")
        
        elif choice == "2":
            if not students:
                print("请先加载数据")
                continue
            seating_result = algorithm.assign_by_level(students)
            exporter.print_seating(seating_result)
        
        elif choice == "3":
            if not students:
                print("请先加载数据")
                continue
            seating_result = algorithm.assign_by_group(students)
            exporter.print_seating(seating_result)
        
        elif choice == "4":
            if not seating_result:
                print("请先进行座位分配")
                continue
            exporter.export_to_json(seating_result)
        
        elif choice == "5":
            print("退出系统")
            break
        
        else:
            print("无效选择，请重新输入")


if __name__ == "__main__":
    main()
