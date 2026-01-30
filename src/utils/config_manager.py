#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
配置管理模块
"""

import json
import os


class ConfigManager:
    """配置管理类"""
    
    def __init__(self):
        """初始化配置管理器"""
        self.config_file = os.path.join(os.path.dirname(__file__), '../../resources/config.json')
        self.config = self._load_config()
    
    def _load_config(self):
        """
        加载配置文件
        
        Returns:
            dict: 配置字典
        """
        default_config = {
            'app': {
                'name': '自动座位分配系统',
                'version': '1.0.0',
                'language': 'zh_CN'
            },
            'algorithm': {
                'default': 'level',  # level: 成绩分层法, group: 分组均匀分配法
                'level': {
                    'levels': 3,
                    'sort_by': '总分'
                },
                'group': {
                    'groups': 4
                }
            },
            'classroom': {
                'default_rows': 8,
                'default_cols': 6,
                'templates': ['标准教室', '小班教室', '大教室']
            },
            'export': {
                'excel_format': 'xlsx',
                'image_format': 'png',
                'dpi': 300
            }
        }
        
        if os.path.exists(self.config_file):
            try:
                with open(self.config_file, 'r', encoding='utf-8') as f:
                    return json.load(f)
            except Exception as e:
                print(f"加载配置文件失败: {str(e)}")
                return default_config
        else:
            # 创建默认配置文件
            self._save_config(default_config)
            return default_config
    
    def _save_config(self, config):
        """
        保存配置文件
        
        Args:
            config (dict): 配置字典
        """
        config_dir = os.path.dirname(self.config_file)
        os.makedirs(config_dir, exist_ok=True)
        
        try:
            with open(self.config_file, 'w', encoding='utf-8') as f:
                json.dump(config, f, ensure_ascii=False, indent=2)
        except Exception as e:
            print(f"保存配置文件失败: {str(e)}")
    
    def get(self, key, default=None):
        """
        获取配置值
        
        Args:
            key (str): 配置键，支持点号分隔的路径
            default: 默认值
            
        Returns:
            配置值或默认值
        """
        keys = key.split('.')
        value = self.config
        
        for k in keys:
            if isinstance(value, dict) and k in value:
                value = value[k]
            else:
                return default
        
        return value
    
    def set(self, key, value):
        """
        设置配置值
        
        Args:
            key (str): 配置键，支持点号分隔的路径
            value: 配置值
        """
        keys = key.split('.')
        config = self.config
        
        # 遍历键路径
        for i, k in enumerate(keys[:-1]):
            if k not in config:
                config[k] = {}
            config = config[k]
        
        # 设置值
        config[keys[-1]] = value
        
        # 保存配置
        self._save_config(self.config)
    
    def reset(self):
        """
        重置配置到默认值
        """
        default_config = {
            'app': {
                'name': '自动座位分配系统',
                'version': '1.0.0',
                'language': 'zh_CN'
            },
            'algorithm': {
                'default': 'level',
                'level': {
                    'levels': 3,
                    'sort_by': '总分'
                },
                'group': {
                    'groups': 4
                }
            },
            'classroom': {
                'default_rows': 8,
                'default_cols': 6,
                'templates': ['标准教室', '小班教室', '大教室']
            },
            'export': {
                'excel_format': 'xlsx',
                'image_format': 'png',
                'dpi': 300
            }
        }
        
        self.config = default_config
        self._save_config(default_config)
    
    def get_all(self):
        """
        获取所有配置
        
        Returns:
            dict: 配置字典
        """
        return self.config
