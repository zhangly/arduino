Git的使用魔法
==============

**不想每次push都输密码**  
所以协议一般选ssh，而不是https，用 ssh-keygen -t ras -C "xxx@xxx.xxx" 

**一个仓库不保险**  
比如github容易被墙，所以可以为项目设置多个远程仓库  
`git remote -v` 可以查看当前项目的远程仓库设置

`git remote add new_name git_url` 为当前项目设置另一个远程仓库，命名为new_name

`git push new_name --mirror` push到另一个镜像仓库 2020.1.23


**多台机器操作同一个账号**

采用ssh方式，将.ssh目录下（windows在当前用户的文档目录下）复制到目标机器  
在linux下时，如果报Permissions 0644 for '/home/pi/.ssh/id_rsa' are too open.之类的错，只需将相应文件降权为0600即可

**一台机器操作多个账号**

生成另一个账号时，指定特定名字：`ssh-keygen -t rsa -C "youremail@your.com” -f ~/.ssh/github-rsa`

添加私钥：`$ ssh-add ~/.ssh/id_rsa $ ssh-add ~/.ssh/github_rsa`

如果执行ssh-add时提示"Could not open a connection to your authentication agent"，可以现执行命令：`ssh-agent bash`

#### 可以通过 `ssh-add -l` 来确认私钥列表

在 ~/.ssh 目录下新建一个config文件:`touch config`

#### 为目标主机起个别名  blaze.com
```
Host blaze.com
    HostName code.csdn.net
	User blaze
    PreferredAuthentications publickey
    IdentityFile ~/.ssh/id_rsa
```	
#### 为目标主机起个别名
```
Host bird.com
    HostName code.csdn.net
	User sinat121212
    PreferredAuthentications publickey
    IdentityFile ~/.ssh/github_rsa
```
#### 查看状态  
git status  
提交  
git commit -a -m xxxx  
git push  

#### 远程库操作
git remote -v                 显示当前目录对应的git仓库  
git remote rm origin     删除对应
设置新的对应远程库：  
git remote add origin git@github.com:zhangly/hello-php.git  
git push --set-upstream origin master  
或  
git remote add origin https://github.com/zhangly/hello-php.git  
git push --set-upstream origin master  
	
	

**Markdown语法**  
到wiki编辑页面点问号看帮助
