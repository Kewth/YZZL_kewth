#!/bin/bash  

" echo "alias yz
read -p "�������û���(����home/����һ��������ļ���)" user
mkdir /home/$user/
cd /home/$user/
rm .yzzl -r
mkdir .yzzl
cd .yzzl
for((i=1;i<=10;i++));  
do
	echo -e "\e[37;40m �����ļ�:informa$i.txt\033[0m\033[1A"
	sleep 0.1
	touch informa$i.txt
done
city=("maincity" "cutcity" "funcity","workcity")
for c in ${city[@]};
do
	echo -e "\e[37;40m �����ļ�:$c.txt       \033[0m\033[1A"
	sleep 0.05
	touch $c.txt
	echo -e "\e[37;40m д���ļ�:$c.txt       \033[0m\033[1A"
	echo ......... > $c.txt
	sleep 0.05
done
touch add.rc
touch common.dat
