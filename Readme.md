# XG_JSON简介

一款个人基于 C++11 开发的json parser,支持六种基本的数据类型:<br>
1. 数字（整数或浮点数）
2. 逻辑值（true 或 false）
3. 字符串（在双引号中）
4. 数组（在方括号中）
5. 对象（在大括号中）
6. null


## 预期功能
1. 读取json文件
2. 根据对象类型格式化输出对象
3. 创建json
4. 索引（数组，obj）
5. 添加（add）
6. 解析文本内容成为一系列Json项
7. 格式化输出Json项

## API设计

JsonItem: 
1. 基本json对象，包括对象、数组、布尔值、字符串、数字、null

JsonParser:
1. 负责json文本的解析

Json:
1. 负责载入与格式化输出



