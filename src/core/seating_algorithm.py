#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
座位分配算法模块
"""

import random
import numpy as np


class SeatingAlgorithm:
    """座位分配算法类"""
    
    def __init__(self):
        """初始化座位分配算法"""
        pass
    
    def assign_by_level(self, students, rows, cols, levels=3, sort_by="总分", relations=None):
        """
        成绩分层法
        
        Args:
            students (pd.DataFrame): 学生数据
            rows (int): 行数
            cols (int): 列数
            levels (int): 层次数量
            sort_by (str): 排序依据
            relations (dict): 座位关系
            
        Returns:
            list: 座位分配结果
        """
        # 排序学生
        sorted_students = students.sort_values(by=sort_by, ascending=False)
        student_list = sorted_students.to_dict('records')
        
        # 分层
        level_size = len(student_list) // levels
        levels_list = []
        for i in range(levels):
            start = i * level_size
            end = (i + 1) * level_size if i < levels - 1 else len(student_list)
            levels_list.append(student_list[start:end])
        
        # 初始化座位
        seating = [[None for _ in range(cols)] for _ in range(rows)]
        total_seats = rows * cols
        
        # 分配座位
        seat_index = 0
        for level in levels_list:
            for student in level:
                if seat_index >= total_seats:
                    break
                row = seat_index // cols
                col = seat_index % cols
                seating[row][col] = student
                seat_index += 2  # 间隔一个座位
                
                # 如果到达行尾，换行
                if seat_index % cols == 0:
                    seat_index += 1
        
        # 处理剩余座位
        remaining_seats = [(i, j) for i in range(rows) for j in range(cols) if seating[i][j] is None]
        remaining_students = [s for s in student_list if not any(s['学号'] == seat.get('学号') for row in seating for seat in row if seat)]
        
        for i, (row, col) in enumerate(remaining_seats):
            if i < len(remaining_students):
                seating[row][col] = remaining_students[i]
        
        return seating
    
    def assign_by_group(self, students, rows, cols, groups=4, relations=None):
        """
        分组均匀分配法
        
        Args:
            students (pd.DataFrame): 学生数据
            rows (int): 行数
            cols (int): 列数
            groups (int): 小组数量
            relations (dict): 座位关系
            
        Returns:
            list: 座位分配结果
        """
        # 随机打乱学生
        student_list = students.to_dict('records')
        random.shuffle(student_list)
        
        # 分组
        group_size = len(student_list) // groups
        group_list = []
        for i in range(groups):
            start = i * group_size
            end = (i + 1) * group_size if i < groups - 1 else len(student_list)
            group_list.append(student_list[start:end])
        
        # 初始化座位
        seating = [[None for _ in range(cols)] for _ in range(rows)]
        total_seats = rows * cols
        
        # 分配座位
        seat_index = 0
        for group in group_list:
            for student in group:
                if seat_index >= total_seats:
                    break
                row = seat_index // cols
                col = seat_index % cols
                seating[row][col] = student
                seat_index += 1
        
        # 处理剩余座位
        remaining_seats = [(i, j) for i in range(rows) for j in range(cols) if seating[i][j] is None]
        remaining_students = [s for s in student_list if not any(s['学号'] == seat.get('学号') for row in seating for seat in row if seat)]
        
        for i, (row, col) in enumerate(remaining_seats):
            if i < len(remaining_students):
                seating[row][col] = remaining_students[i]
        
        return seating
    
    def check_relations(self, seating, relations):
        """
        检查座位关系是否满足
        
        Args:
            seating (list): 座位分配结果
            relations (dict): 座位关系
            
        Returns:
            dict: 关系满足情况
        """
        must_count = len(relations.get('must', []))
        cannot_count = len(relations.get('cannot', []))
        must_satisfied = 0
        cannot_satisfied = 0
        
        # 构建学生位置映射
        student_positions = {}
        for i, row in enumerate(seating):
            for j, student in enumerate(row):
                if student:
                    student_positions[student['姓名']] = (i, j)
        
        # 检查必须坐在一起的关系
        for relation in relations.get('must', []):
            s1 = relation['student1']
            s2 = relation['student2']
            if s1 in student_positions and s2 in student_positions:
                pos1 = student_positions[s1]
                pos2 = student_positions[s2]
                # 检查是否相邻
                if (abs(pos1[0] - pos2[0]) <= 1 and abs(pos1[1] - pos2[1]) <= 1):
                    must_satisfied += 1
        
        # 检查不能坐在一起的关系
        for relation in relations.get('cannot', []):
            s1 = relation['student1']
            s2 = relation['student2']
            if s1 in student_positions and s2 in student_positions:
                pos1 = student_positions[s1]
                pos2 = student_positions[s2]
                # 检查是否不相邻
                if not (abs(pos1[0] - pos2[0]) <= 1 and abs(pos1[1] - pos2[1]) <= 1):
                    cannot_satisfied += 1
        
        return {
            'must': {
                'total': must_count,
                'satisfied': must_satisfied,
                'rate': must_satisfied / must_count if must_count > 0 else 1
            },
            'cannot': {
                'total': cannot_count,
                'satisfied': cannot_satisfied,
                'rate': cannot_satisfied / cannot_count if cannot_count > 0 else 1
            }
        }
