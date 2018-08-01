
print("Tips: 请以管理员身份运行,否则退出重试" )
import os
user = input( "请输入用户名(以在home/建立一个必须的文件夹)" ) + '/'
os.system('mkdir /home/' + user)
user = '/home/' + user
