# searchEngine
第一次编程作业——简易搜索引擎

* 接触编程语言的第一次C语言大作业
* 代码质量很差，仅留作纪念
* 具体功能及要求见clabFinalProject.pdf
* 使用方法，在命令行中执行可执行文件，其后跟随参数（实现模式的选择）

  格式：```name.exe mode [specifiedMode1] [specifiedMode2] [specifiedMode3]```
  
  mode: script || manual
  
  specifiedMode: exactSearch || topSearch || topKSearch

  比如：
  
  ```filename.exe manual```表示手动模式的普通搜索
  
  ```filename.exe script exactSearch```表示脚本模式的精确查找
  
  ```filename.exe script topSearch exactSearch```表示同时实现脚本模式的精确搜索以及top搜索
