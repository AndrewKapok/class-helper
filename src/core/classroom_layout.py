#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
教室布局管理模块
"""

import json
import os


class ClassroomLayout:
    """教室布局管理类"""
    
    def __init__(self):
        """初始化教室布局管理器"""
        self.rows = 8
        self.cols = 6
        self.aisles = []  # 过道位置
        self.templates = []  # 布局模板
        self.load_templates()
    
    def set_layout(self, rows, cols):
        """
        设置教室布局
        
        Args:
            rows (int): 行数
            cols (int): 列数
        """
        self.rows = rows
        self.cols = cols
    
    def add_aisle(self, row=None, col=None):
        """
        添加过道
        
        Args:
            row (int): 行位置
            col (int): 列位置
        """
        if row is not None or col is not None:
            self.aisles.append({'row': row, 'col': col})
    
    def remove_aisle(self, index):
        """
        移除过道
        
        Args:
            index (int): 过道索引
        """
        if 0 <= index < len(self.aisles):
            self.aisles.pop(index)
    
    def get_aisles(self):
        """
        获取过道位置
        
        Returns:
            list: 过道位置列表
        """
        return self.aisles
    
    def save_template(self, name):
        """
        保存布局模板
        
        Args:
            name (str): 模板名称
        """
        template = {
            'name': name,
            'rows': self.rows,
            'cols': self.cols,
            'aisles': self.aisles
        }
        self.templates.append(template)
        self._save_templates_to_file()
    
    def load_template(self, name):
        """
        加载布局模板
        
        Args:
            name (str): 模板名称
            
        Returns:
            bool: 是否加载成功
        """
        for template in self.templates:
            if template['name'] == name:
                self.rows = template['rows']
                self.cols = template['cols']
                self.aisles = template['aisles']
                return True
        return False
    
    def delete_template(self, name):
        """
        删除布局模板
        
        Args:
            name (str): 模板名称
        """
        self.templates = [t for t in self.templates if t['name'] != name]
        self._save_templates_to_file()
    
    def get_templates(self):
        """
        获取所有模板
        
        Returns:
            list: 模板列表
        """
        return self.templates
    
    def load_templates(self):
        """
        从文件加载模板
        """
        template_dir = os.path.join(os.path.dirname(__file__), '../../resources/templates')
        template_file = os.path.join(template_dir, 'layouts.json')
        
        if os.path.exists(template_file):
            try:
                with open(template_file, 'r', encoding='utf-8') as f:
                    self.templates = json.load(f)
            except Exception as e:
                print(f"加载模板失败: {str(e)}")
        else:
            # 创建默认模板
            self._create_default_templates()
            self._save_templates_to_file()
    
    def _save_templates_to_file(self):
        """
        保存模板到文件
        """
        template_dir = os.path.join(os.path.dirname(__file__), '../../resources/templates')
        os.makedirs(template_dir, exist_ok=True)
        template_file = os.path.join(template_dir, 'layouts.json')
        
        try:
            with open(template_file, 'w', encoding='utf-8') as f:
                json.dump(self.templates, f, ensure_ascii=False, indent=2)
        except Exception as e:
            print(f"保存模板失败: {str(e)}")
    
    def _create_default_templates(self):
        """
        创建默认模板
        """
        self.templates = [
            {
                'name': '标准教室',
                'rows': 8,
                'cols': 6,
                'aisles': [{'row': None, 'col': 2}, {'row': None, 'col': 5}]
            },
            {
                'name': '小班教室',
                'rows': 6,
                'cols': 5,
                'aisles': [{'row': None, 'col': 2}]
            },
            {
                'name': '大教室',
                'rows': 10,
                'cols': 8,
                'aisles': [{'row': None, 'col': 3}, {'row': None, 'col': 7}]
            }
        ]
