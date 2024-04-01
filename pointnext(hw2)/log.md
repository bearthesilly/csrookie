# Log

[PointNeXt: Revisiting PointNet++ with Improved Training and Scaling Strategies | Papers With Code](https://paperswithcode.com/paper/pointnext-revisiting-pointnet-with-improved)

首先看README文件， 想要安装环境：

````bash
git clone --recurse-submodules git@github.com:guochengqian/PointNeXt.git
cd PointNeXt
source update.sh
source install.sh
````

但是在进入了计算节点之后发现报错：

``please make sure you have the correct access``

因此尝试开始解决问题：

````bash
git config --global user.name "yourname"

git config --global user.email "your@email.com" 
````

``git config --list # 注意确保邮箱不是在双引号里面``

``ssh-keygen -t rsa -C "your@email.com"（请填你设置的邮箱地址）``

会出现： 

``Generating public/private rsa key pair.``

``Enter file in which to save the key (/Users/your_user_directory/.ssh/id_rsa):``

然后登录自己的github，在settings里面找到SSH and GPG keys，进入

然后将``.SSH/id_rsa.pub``里面的东西复制进去，然后点击``Add SHH key``

然后``ssh -T git@github.com``

最后就能成功连接了（如果不行，**试一下重启**）