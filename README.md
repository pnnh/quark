### 构建

```bash
# 配置cmake
cmake --preset macos

# 生成库
cmake --build --preset macos --config Debug

# 安装库到指定目录
# #默认将安装到install目录
cmake --install build/macos --config Debug
```