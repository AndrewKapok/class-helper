#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
数据处理模块测试
"""

import unittest
import pandas as pd
import os
from core.data_processor import DataProcessor


class TestDataProcessor(unittest.TestCase):
    """数据处理模块测试类"""
    
    def setUp(self):
        """设置测试环境"""
        self.data_processor = DataProcessor()
        # 创建测试数据
        self.test_data = pd.DataFrame({
            '姓名': ['张三', '李四', '王五'],
            '学号': ['1001', '1002', '1003'],
            '总分': [95, 85, 75],
            '语文': [90, 80, 70],
            '数学': [100, 90, 80],
            '英语': [95, 85, 75]
        })
        # 保存测试数据到Excel
        self.test_file = 'test_data.xlsx'
        self.test_data.to_excel(self.test_file, index=False)
    
    def tearDown(self):
        """清理测试环境"""
        if os.path.exists(self.test_file):
            os.remove(self.test_file)
        if os.path.exists('relations.json'):
            os.remove('relations.json')
    
    def test_import_excel(self):
        """测试导入Excel文件"""
        result = self.data_processor.import_excel(self.test_file)
        self.assertTrue(result['success'])
        self.assertEqual(len(result['data']), 3)
    
    def test_validate_data(self):
        """测试数据验证"""
        # 导入数据
        self.data_processor.import_excel(self.test_file)
        # 验证数据
        result = self.data_processor.validate_data()
        self.assertTrue(result['success'])
    
    def test_sort_students(self):
        """测试学生排序"""
        # 导入数据
        self.data_processor.import_excel(self.test_file)
        # 按总分排序
        sorted_data = self.data_processor.sort_students(by='总分', ascending=False)
        self.assertEqual(sorted_data.iloc[0]['姓名'], '张三')
        self.assertEqual(sorted_data.iloc[-1]['姓名'], '王五')
    
    def test_add_relation(self):
        """测试添加座位关系"""
        # 添加必须坐在一起的关系
        self.data_processor.add_relation('must', '张三', '李四', '同桌')
        relations = self.data_processor.get_relations()
        self.assertEqual(len(relations['must']), 1)
        self.assertEqual(relations['must'][0]['student1'], '张三')
        self.assertEqual(relations['must'][0]['student2'], '李四')
        self.assertEqual(relations['must'][0]['type'], '同桌')
    
    def test_remove_relation(self):
        """测试移除座位关系"""
        # 添加关系
        self.data_processor.add_relation('must', '张三', '李四', '同桌')
        self.data_processor.add_relation('must', '李四', '王五', '小组')
        # 移除关系
        self.data_processor.remove_relation('must', 0)
        relations = self.data_processor.get_relations()
        self.assertEqual(len(relations['must']), 1)
        self.assertEqual(relations['must'][0]['student1'], '李四')
    
    def test_save_load_relations(self):
        """测试保存和加载座位关系"""
        # 添加关系
        self.data_processor.add_relation('must', '张三', '李四', '同桌')
        self.data_processor.add_relation('cannot', '王五', '张三', '同桌')
        # 保存关系
        self.data_processor.save_relations('relations.json')
        # 创建新的数据处理器
        new_processor = DataProcessor()
        # 加载关系
        new_processor.load_relations('relations.json')
        relations = new_processor.get_relations()
        self.assertEqual(len(relations['must']), 1)
        self.assertEqual(len(relations['cannot']), 1)


if __name__ == '__main__':
    unittest.main()
