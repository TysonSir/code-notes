#安装
https://docs.docker.com/install/linux/docker-ce/centos/#install-using-the-repository

sudo yum install -y yum-utils \
  device-mapper-persistent-data \
  lvm2

  yum-config-manager \
    --add-repo \
    https://download.docker.com/linux/centos/docker-ce.repo

sudo yum-config-manager --enable docker-ce-nightly

sudo yum-config-manager --enable docker-ce-test

sudo yum-config-manager --disable docker-ce-nightly

sudo yum install docker-ce docker-ce-cli containerd.io

#启动
systemctl start docker

#阿里云加速器地址
https://cr.console.aliyun.com/cn-hangzhou/instances/mirrors
https://ff3vg2ex.mirror.aliyuncs.com

#操作
sudo mkdir -p /etc/docker

sudo tee /etc/docker/daemon.json <<-'EOF'
{
  "registry-mirrors": ["https://ff3vg2ex.mirror.aliyuncs.com"]
}
EOF

sudo systemctl daemon-reload
sudo systemctl restart docker

#测试运行
docker run hello-world

#操作

#帮助命令
docker version
docker info
docker --help

#镜像命令
docker images [-a -q]# 列出本地镜像
-a/--all:查看所有镜像
-q:只查看所有镜像的ID

#查 start > 30 的镜像
docker search -s 30 ubuntu 

docker pull ubuntu:latest #拉最新的
docker pull ubuntu:16.04 #拉指定版本
docker pull nginx #拉指定版本

docker rmi hello-world:latest #在运行的镜像删除失败
docker rmi -f hello-world:latest [...] #强制删除 [多个]

#删除全部(删除参数可以是ID)
docker rmi -f $(docker iamges -qa)


#容器命令

#新建并启动容器
docker run -it --name myUbuntu ubuntu
-it: 打开终端，启动交互式容器
--name myUbuntu:起别名


#查看正在运行的容器
docker ps #非docker终端中使用

#退容器
exit #关闭并退出
ctrl + P + Q

#查看历史容器
docker ps -n 3

#启动容器
docker start [CONTAINER ID]

#重启容器
docker restart [CONTAINER ID]

#关闭容器
docker stop [ID or name]
docker kill [ID or name] #强制停止

#删除已关闭的容器
docker rm [-f] [ID]
-f:正在运行的容器强制删除

#删除所有容器
docker rm -f $(docker ps -qa)

# ---------- 重要 -----------#
#守护进程方式启动容器
docker run -it --name myUbuntu ubuntu
docker stop myUbuntu
docker run -d ubuntu:16.04 #镜像名
#此时容器启动马上退出，因为没有实际的东西运行

#以下命令 启动一个持续进程
docker run -d ubuntu:16.04 /bin/sh -c "while true;do echo hello zzyy;sleep 2;done"
docker run -d -v /volume_host:/volume_cont ubuntu1604/django:0.5 /bin/sh -c "while true;do echo hello zzyy;sleep 2;done"

## 不进入容器，操作容器

#查看运行日志，终端输出
docker logs -tf -tail 4
-t:显示时间
-f:实时打印
-tail:显示最新的n条

#查看容器内的进程
docker top [ID]

#查看容器内部细节
docker inspect [ID] #显示json格式信息

#交互(进入) 守护进程容器，可执行命令
docker attach [ID]

#交互(不进入) 守护进程容器，直接执行命令
docker exec -t [ID] ls -l /tmp
docker exec -t 9e8a4a1faac1 /bin/bash #同attach

#从容器内拷贝文件到主机上
docker cp [ID]:/tmp/yum.log [主机目录]

#提交新镜像(执行后，可使用 docker images 查看到镜像,并正常使用)
docker commit -m="ubuntu with ssh.vim.net-tools" -a="TysonSir" [CONT_ID] tysonsir/base_ubuntu:16.04

docker commit -m="ubuntu with ssh.vim.net-tools.pip3" -a="TysonSir" 1e8cbc3bc2ea ubuntu1604/django:0.1
docker commit -m="ubuntu with ssh.vim.net-tools.pip3.django" -a="TysonSir" 11 ubuntu1604/django:0.2
docker commit -m="ubuntu with ssh.vim.net-tools.pip3.django.office" -a="TysonSir" 11 ubuntu1604/django:0.3
docker commit -m="ubuntu with ssh.vim.net-tools.pip3.django.libreoffice.Fonts" -a="TysonSir" 11 ubuntu1604/django:0.4
docker commit -m="ubuntu with 0.4_imtest_djangorun" -a="TysonSir" 11 ubuntu1604/django:0.5
docker commit -m="ubuntu with 0.5_get report data" -a="TysonSir" f27ef42c2d81 ubuntu1604/django:0.6  #不放心备份，和0.5理论没什么区别
docker commit -m="ubuntu with 0.6_redis" -a="TysonSir" f27ef42c2d81 ubuntu1604/django:0.7
docker commit -m="ubuntu with 0.7_projectrun" -a="TysonSir" f27ef42c2d81 ubuntu1604/django:0.7.1  #不放心备份，和0.7理论没什么区别
docker commit -m="ubuntu with 0.7.1_test data ok" -a="TysonSir" f27ef42c2d81 ubuntu1604/django:0.8  #

#运行应用时设定端口
docker run -it -p 8888:80 nginx:latest
docker run -it -v /volume_host:/volume_cont -p 8888:80 ubuntu1604/django:0.5
-p:设定 主机端口：应用端口

docker run -it -P nginx:latest
-P: 随机分配端口

#在ubuntu镜像上安装软件，先 apt-get update

#启动容器
docker run -it 镜像名

## 容器数据卷（共享文件夹）
docker run -it -v /主机目录:/容器目录 --privileged=true 镜像名
docker run -it -v /volume_host:/volume_cont ubuntu1604/django:0.1
docker run -it -v /volume_host:/volume_cont ubuntu1604/django:0.2
docker run -it -v /volume_host:/volume_cont -p 8000:8000 -p 6379:6379 -p 2222:22 ubuntu1604/django:0.7.1

docker run -it -v /volume_host:/volume_cont -p 8000:8000 ubuntu1604/django:0.8

--privileged=true:若出现权限问题可用
#目录不需要准备，能直接建立

#容器中只读
docker run -it -v /volume_host:/volume_cont:ro ubuntu:16.04
:ro #read only

#查看绑定
docker inspect [ID] #显示json格式信息

## 容器数据卷——DockerFile 创建带数据卷的镜像

#DockerFile文件
#注释：DockerFile文件中没有指定主机路径，会默认生成一个
FROM ubuntu:16.04
VOLUME ["/volume_cont1","/volume_cont2"]
CMD touch /tmp/ip.txt
CMD /bin/bash

#执行dockerFile文件
docker build -f ./dockerfile -t tysonsir/base_ubuntu_vol:16:04 ~/docker_images
-f:dockerfile文件路径
-t:命名空间
~/docker_images:生成镜像文件路径

#查看默认容器卷路径
docker inspect [CONT_ID] 

#父容器
#创建父容器
docker run -it --name dc01 ubuntu:16.04
#创建子容器
docker run -it --name dc02 --volumes-from dc01 ubuntu:16.04
docker run -it --name dc03 --volumes-from dc01 ubuntu:16.04
#父容器中的容器数据卷可和子容器共享数据

#镜像/容器 导入导出
#https://blog.csdn.net/jctian000/article/details/82704252
docker save cd6d8154f1e1 > /home/myubuntu-save-1204.tar
docker save cd6d8154f1e1 > ~/docker_images/ubuntu1604-django-office-env-save.tar
docker save cd6d8154f1e1 > ~/docker_images/ubuntu1604-django-office-redis-env-save.tar
docker save cd6d8154f1e1 > ~/docker_images/ubuntu1604-django-webreport-ubuntu1604_django:0.8-save.tar

docker load < ./base_ubuntu-save-1604.tar

#导入时标签为None，下面命令改名
docker tag [image id] [name]:[版本]
docker tag b03b74b01d97 base_ubuntu:1604


#ubuntu 中安装中文字体

#缺少中文字体支付所致，所以先把 c:\Windows\Fonts文件夹复制一份到其它盘，然后打包成Fonts.zip，通过rz Fonts.zip 将压缩包传到服务器上面。
#mkfontscale需要安装
apt-get install ttf-mscorefonts-installe

[root@instance-32spzihn /]# cd /usr/share/fonts
[root@instance-32spzihn fonts]# rz
[root@instance-32spzihn fonts]# unzip Fonts.zip
[root@instance-32spzihn fonts]# mv Fonts win
[root@instance-32spzihn fonts]# cd win
[root@instance-32spzihn win]# chmod -Rf 755 *
[root@instance-32spzihn win]# mkfontscale
[root@instance-32spzihn win]# mkfontdir
[root@instance-32spzihn win]# fc-cache –fv
#若没有生效可以试下重启服务器，再重新执行转换命令就可以了。

#Linux下的压缩解压缩命令详解及实例
#实例：压缩服务器上当前目录的内容为xxx.zip文件
zip -r xxx.zip ./*
zip -r /volume_host_back/volume_host_djangorun_0.2.zip ./volume_host
#解压zip文件到当前目录
unzip filename.zip