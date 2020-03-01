# 为小派安装USB摄像头，使用 fswebcam 定时抓拍，并上传yeelink
1.安装USB摄像头一般驱动缺省已装    
 ls -l /dev/video0 

2.安装fswebcam  
 sudo apt-get install fswebcam  
 
3.使用fswebcam 抓拍一张照片并存盘  
sudo fswebcam -d /dev/video0 -r 320x240 --bottom-banner --title "RaspberryPi @ Yeelink" --no-timestamp /home/pi/yeelink.jpg

4.上传照片到yeelink，先行开设好yeelink.net账号     
curl --request POST --data-binary @"/home/pi/yeelink.jpg" --header "U-ApiKey: xxxxxxxxxxxxxxxxxxxx" http://api.yeelink.net/v1.0/device/1022/sensor/1294/photos

5.将上述二行命令合到一个yeelink.sh脚本增加执行权限之后，加入cronjob  
 crontab -e  
 
 加入下面一行, 让脚本每分钟运行一次, 保存退出.  
*/1 * * * * /home/pi/yeelink.sh  
