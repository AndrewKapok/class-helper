#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Excel文件处理模块
"""

import pandas as pd
import openpyxl


class ExcelHandler:
    """Excel文件处理类"""
    
    def __init__(self):
        """初始化Excel处理器"""
        pass
    
    def read_excel(self, file_path):
        """
        读取Excel文件
        
        Args:
            file_path (str): 文件路径
            
        Returns:
            pd.DataFrame: 读取的数据
        """
        try:
            return pd.read_excel(file_path)
        except Exception as e:
            raise Exception(f"读取Excel文件失败: {str(e)}")
    
    def write_excel(self, file_path, data, sheet_name='Sheet1'):
        """
        写入Excel文件
        
        Args:
            file_path (str): 文件路径
            data (pd.DataFrame or list): 要写入的数据
            sheet_name (str): 工作表名称
        """
        try:
            if isinstance(data, pd.DataFrame):
                data.to_excel(file_path, sheet_name=sheet_name, index=False)
            else:
                # 如果是列表，转换为DataFrame
                df = pd.DataFrame(data)
                df.to_excel(file_path, sheet_name=sheet_name, index=False)
        except Exception as e:
            raise Exception(f"写入Excel文件失败: {str(e)}")
    
    def export_seating_result(self, file_path, seating):
        """
        导出座位分配结果到Excel
        
        Args:
            file_path (str): 文件路径
            seating (list): 座位分配结果
        """
        try:
            # 准备数据
            result_data = []
            seat_number = 1
            
            for row_idx, row in enumerate(seating):
                for col_idx, student in enumerate(row):
                    if student:
                        result_data.append({
                            '座位号': seat_number,
                            '行数': row_idx + 1,
                            '列数': col_idx + 1,
                            '姓名': student.get('姓名', ''),
                            '学号': student.get('学号', ''),
                            '总分': student.get('总分', ''),
                            '语文': student.get('语文', ''),
                            '数学': student.get('数学', ''),
                            '英语': student.get('英语', '')
                        })
                        seat_number += 1
            
            # 写入Excel
            df = pd.DataFrame(result_data)
            df.to_excel(file_path, sheet_name='座位分配结果', index=False)
        except Exception as e:
            raise Exception(f"导出座位结果失败: {str(e)}")
