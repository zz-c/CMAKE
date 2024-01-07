# 中英文翻译合并对照表
源码地址 https://github.com/zz-c/CMAKE/tree/main/lang_file_read 
版本发布地址 https://github.com/zz-c/CMAKE/releases/tag/lang_file_read_v1  
## 使用说明
将中文说明放在zh-CN文件夹下，格式
```
{
  "workspace": "工作台",
  "devices": "设备管理",
  "wiFi": "Wi-Fi配置",
  "radioSetting": "射频配置",
  "wirelessRateLimiting": "无线限速",
  "blocklistAllowlist": "黑白名单",
  "reboot": "网络重启",
  "psssword": "登录密码",
  "reset": "恢复出厂"
}
```
将英文说明放在en文件夹下，格式
```
{
  "workspace": "Workspace",
  "devices": "Devices",
  "wiFi": "Wi-Fi",
  "radioSetting": "Radio Setting",
  "wirelessRateLimiting": "Wireless Rate Limiting",
  "blocklistAllowlist": "Blocklist/Allowlist",
  "reboot": "Reboot",
  "psssword": "Psssword",
  "reset": "Reset",
  "test": "test",
}
```
点击lang_file_read.exe，运行后生成对照表out.csv