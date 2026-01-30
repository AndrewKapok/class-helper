#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Excel文件处理模块测试
"""

import unittest
import pandas as pd
import os
from utils.excel_handler import ExcelHandler


class TestExcelHandler(unittest.TestCase):
    """Excel文件处理模块测试类"""
    
    def setUp(self):
        """设置测试环境"""
        self.excel_handler = ExcelHandler()
        # 创建测试数据
        self.test_data = pd.DataFrame({
            '姓名': ['张三', '李四', '王五'],
            '学号': ['1001', '1002', '1003'],
            '总分': [95, 85, 75]
        })
        # 创建测试座位分配结果
        self.test_seating = [
            [
                {'姓名': '张三', '学号': '1001', '总分': 95},
                {'姓名': '李四', '学号': '1002', '总分': 85}
            ],
            [
                {'姓名': '王五', '学号': '1003', '总分': 75},
                None
            ]
        ]
    
    def tearDown(self):
        """清理测试环境"""
        for file in ['test_write.xlsx', 'test_export.xlsx']:
            if os.path.exists(file):
                os.remove(file)
    
    def test_read_excel(self):
        """测试读取Excel文件"""
        # 保存测试数据
        test_file = 'test_read.xlsx'
        self.test_data.to_excel(test_file, index=False)
        # 读取Excel文件
        data = self.excel_handler.read_excel(test_file)
        # 验证数据
        self.assertEqual(len(data), 3)
        self.assertEqual(data.iloc[0]['姓名'], '张三')
        # 清理
        if os.path.exists(test_file):
            os.remove(test_file)
    
    def test_write_excel(self):
        """测试写入Excel文件"""
        # 写入Excel文件
        test_file = 'test_write.xlsx'
        self.excel_handler.write_excel(test_file, self.test_data)
        # 验证文件是否存在
        self.assertTrue(os.path.exists(test_file))
        # 读取验证
        data = pd.read_excel(test_file)
        self.assertEqual(len(data), 3)
        self.assertEqual(data.iloc[0]['姓名'], '张三')
    
    def test_export_seating_result(self):
        """测试导出座位分配结果"""
        # 导出座位分配结果
        test_file = 'test_export.xlsx'
        self.excel_handler.export_seating_result(test_file, self.test_seating)
        # 验证文件是否存在
        self.assertTrue(os.path.exists(test_file))
        # 读取验证
        data = pd.read_excel(test_file)
        self.assertEqual(len(data), 3)
        self.assertEqual(data.iloc[0]['姓名'], '张三')
        self.assertEqual(data.iloc[0]['座位号'], 1)


if __name__ == '__main__':
    unittest.main()
