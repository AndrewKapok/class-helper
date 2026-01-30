#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
座位分配算法测试
"""

import unittest
import pandas as pd
from core.seating_algorithm import SeatingAlgorithm


class TestSeatingAlgorithm(unittest.TestCase):
    """座位分配算法测试类"""
    
    def setUp(self):
        """设置测试环境"""
        self.algorithm = SeatingAlgorithm()
        # 创建测试数据
        self.test_data = pd.DataFrame({
            '姓名': ['张三', '李四', '王五', '赵六', '钱七', '孙八'],
            '学号': ['1001', '1002', '1003', '1004', '1005', '1006'],
            '总分': [95, 90, 85, 80, 75, 70],
            '语文': [90, 85, 80, 75, 70, 65],
            '数学': [100, 95, 90, 85, 80, 75],
            '英语': [95, 90, 85, 80, 75, 70]
        })
        # 创建测试关系
        self.test_relations = {
            'must': [
                {'student1': '张三', 'student2': '李四', 'type': '同桌'},
                {'student1': '王五', 'student2': '赵六', 'type': '小组'}
            ],
            'cannot': [
                {'student1': '钱七', 'student2': '孙八', 'type': '同桌'}
            ]
        }
    
    def test_assign_by_level(self):
        """测试成绩分层法"""
        # 分配座位
        seating = self.algorithm.assign_by_level(self.test_data, rows=3, cols=2, levels=2, sort_by='总分')
        # 验证座位分配
        self.assertEqual(len(seating), 3)
        self.assertEqual(len(seating[0]), 2)
        # 检查是否有学生被分配
        student_count = 0
        for row in seating:
            for student in row:
                if student:
                    student_count += 1
        self.assertEqual(student_count, len(self.test_data))
    
    def test_assign_by_group(self):
        """测试分组均匀分配法"""
        # 分配座位
        seating = self.algorithm.assign_by_group(self.test_data, rows=3, cols=2, groups=2)
        # 验证座位分配
        self.assertEqual(len(seating), 3)
        self.assertEqual(len(seating[0]), 2)
        # 检查是否有学生被分配
        student_count = 0
        for row in seating:
            for student in row:
                if student:
                    student_count += 1
        self.assertEqual(student_count, len(self.test_data))
    
    def test_check_relations(self):
        """测试座位关系检查"""
        # 分配座位
        seating = self.algorithm.assign_by_level(self.test_data, rows=3, cols=2, levels=2, sort_by='总分')
        # 检查关系
        result = self.algorithm.check_relations(seating, self.test_relations)
        # 验证结果格式
        self.assertIn('must', result)
        self.assertIn('cannot', result)
        self.assertIn('total', result['must'])
        self.assertIn('satisfied', result['must'])
        self.assertIn('rate', result['must'])
        self.assertIn('total', result['cannot'])
        self.assertIn('satisfied', result['cannot'])
        self.assertIn('rate', result['cannot'])


if __name__ == '__main__':
    unittest.main()
