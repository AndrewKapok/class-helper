#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
数据处理模块
"""

import pandas as pd
import numpy as np


class DataProcessor:
    """数据处理类"""
    
    def __init__(self):
        """初始化数据处理器"""
        self.students = pd.DataFrame()
        self.relations = {
            "must": [],
            "cannot": []
        }
    
    def import_excel(self, file_path):
        """
        导入Excel文件
        
        Args:
            file_path (str): Excel文件路径
            
        Returns:
            dict: 导入结果，包含成功/失败信息
        """
        try:
            # 读取Excel文件
            self.students = pd.read_excel(file_path)
            
            # 数据验证
            result = self.validate_data()
            if not result["success"]:
                return result
            
            return {
                "success": True,
                "message": f"成功导入 {len(self.students)} 条学生记录",
                "data": self.students
            }
        except Exception as e:
            return {
                "success": False,
                "message": f"导入失败: {str(e)}"
            }
    
    def validate_data(self):
        """
        验证数据格式
        
        Returns:
            dict: 验证结果
        """
        # 检查必要列
        required_columns = ["姓名", "学号"]
        missing_columns = [col for col in required_columns if col not in self.students.columns]
        
        if missing_columns:
            return {
                "success": False,
                "message": f"缺少必要列: {', '.join(missing_columns)}"
            }
        
        # 检查空值
        null_counts = self.students.isnull().sum()
        null_columns = [col for col, count in null_counts.items() if count > 0]
        
        if null_columns:
            null_info = ", ".join([f"{col}: {count}个" for col, count in null_counts.items() if count > 0])
            return {
                "success": False,
                "message": f"数据存在空值: {null_info}"
            }
        
        return {"success": True, "message": "数据验证通过"}
    
    def sort_students(self, by="总分", ascending=False):
        """
        排序学生
        
        Args:
            by (str): 排序依据
            ascending (bool): 是否升序
            
        Returns:
            pd.DataFrame: 排序后的学生数据
        """
        if by in self.students.columns:
            return self.students.sort_values(by=by, ascending=ascending)
        return self.students
    
    def add_relation(self, type_, student1, student2, relation_type):
        """
        添加座位关系
        
        Args:
            type_ (str): 关系类型，"must"或"cannot"
            student1 (str): 学生1姓名
            student2 (str): 学生2姓名
            relation_type (str): 关系类型，"同桌"或"小组"
        """
        if type_ in self.relations:
            self.relations[type_].append({
                "student1": student1,
                "student2": student2,
                "type": relation_type
            })
    
    def remove_relation(self, type_, index):
        """
        移除座位关系
        
        Args:
            type_ (str): 关系类型，"must"或"cannot"
            index (int): 关系索引
        """
        if type_ in self.relations and 0 <= index < len(self.relations[type_]):
            self.relations[type_].pop(index)
    
    def get_relations(self):
        """
        获取所有座位关系
        
        Returns:
            dict: 座位关系字典
        """
        return self.relations
    
    def save_relations(self, file_path):
        """
        保存座位关系到文件
        
        Args:
            file_path (str): 保存路径
        """
        import json
        with open(file_path, "w", encoding="utf-8") as f:
            json.dump(self.relations, f, ensure_ascii=False, indent=2)
    
    def load_relations(self, file_path):
        """
        从文件加载座位关系
        
        Args:
            file_path (str): 文件路径
        """
        import json
        try:
            with open(file_path, "r", encoding="utf-8") as f:
                self.relations = json.load(f)
        except Exception as e:
            print(f"加载关系失败: {str(e)}")
