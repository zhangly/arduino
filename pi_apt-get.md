#树莓派上常用apt-get命令

apt-get update  
定期运行这一命令以确保软件包列表是最新的  

apt-get install packagename   
安装软件包   

apt-get remove packagename  
卸载一个已安装的软件包（保留配置文档），apt-get remove --purge packagename 不留配置文档

apt-get dist-upgrade  
将系统升级到新版本  

dpkg -l  
列出所有已安装的软件包

apt-get autoclean
定期运行这个命令来清除那些已卸载的软件包的.deb文档。

apt-get clean  
安装的软件的备份删除，但是这样不会影响软件的使用  




