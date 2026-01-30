#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
错误处理模块
"""


class ErrorHandler:
    """错误处理类"""
    
    def __init__(self):
        """初始化错误处理器"""
        pass
    
    def handle_error(self, error, context=None):
        """
        处理错误
        
        Args:
            error (Exception or str): 错误对象或错误信息
            context (str): 错误上下文
            
        Returns:
            dict: 错误信息字典
        """
        error_message = str(error)
        error_type = type(error).__name__ if isinstance(error, Exception) else "Error"
        
        # 生成错误信息
        error_info = {
            'type': error_type,
            'message': error_message,
            'context': context,
            'solution': self._get_solution(error_message, error_type)
        }
        
        # 记录错误
        self._log_error(error_info)
        
        return error_info
    
    def _get_solution(self, error_message, error_type):
        """
        获取错误解决方案
        
        Args:
            error_message (str): 错误信息
            error_type (str): 错误类型
            
        Returns:
            str: 解决方案
        """
        solutions = {
            'FileNotFoundError': '请检查文件路径是否正确，确保文件存在',
            'PermissionError': '请检查文件权限，确保有读写权限',
            'ValueError': '请检查输入数据是否正确，确保格式符合要求',
            'KeyError': '请检查数据结构是否正确，确保所需字段存在',
            'ImportError': '请检查依赖库是否安装，可使用 pip install 命令安装',
            'ExcelFileNotFoundError': '请检查Excel文件是否存在，路径是否正确',
            'EmptyDataError': 'Excel文件中没有数据，请检查文件内容',
        }
        
        # 通用解决方案
        if error_type in solutions:
            return solutions[error_type]
        
        # 根据错误信息判断
        if 'Excel' in error_message:
            return '请检查Excel文件格式是否正确，确保文件未损坏'
        elif 'permission' in error_message.lower():
            return '请检查文件权限，确保有读写权限'
        elif 'file' in error_message.lower() and 'not found' in error_message.lower():
            return '请检查文件路径是否正确，确保文件存在'
        else:
            return '请检查操作是否正确，或联系管理员'
    
    def _log_error(self, error_info):
        """
        记录错误
        
        Args:
            error_info (dict): 错误信息字典
        """
        # 这里可以扩展为写入日志文件
        print(f"[ERROR] {error_info['type']}: {error_info['message']}")
        if error_info['context']:
            print(f"[CONTEXT] {error_info['context']}")
        print(f"[SOLUTION] {error_info['solution']}")
    
    def validate_input(self, input_data, rules):
        """
        验证输入数据
        
        Args:
            input_data (dict): 输入数据
            rules (dict): 验证规则
            
        Returns:
            dict: 验证结果
        """
        errors = []
        
        for field, rule in rules.items():
            value = input_data.get(field)
            
            # 检查必填项
            if rule.get('required') and value is None:
                errors.append(f"{field} 是必填项")
            
            # 检查类型
            if value is not None and 'type' in rule:
                expected_type = rule['type']
                if not isinstance(value, expected_type):
                    errors.append(f"{field} 类型错误，期望 {expected_type.__name__} 类型")
            
            # 检查范围
            if value is not None:
                if 'min' in rule and value < rule['min']:
                    errors.append(f"{field} 最小值为 {rule['min']}")
                if 'max' in rule and value > rule['max']:
                    errors.append(f"{field} 最大值为 {rule['max']}")
        
        return {
            'valid': len(errors) == 0,
            'errors': errors
        }
