cd ../YZZL_kewth/ || exit
# reset
g++ main.cpp umore.cpp \
	people.cpp maincity.cpp cutcity.cpp funcity.cpp workcity.cpp firstcity.cpp skycity.cpp \
	war.cpp shuju.cpp bag.cpp jn.cpp \
	-o ~/Desktop/Y"$(date "+%Y_%m_%d")" -lpthread -std=c++11
if [ "$1" = -n ]
then
	zenity --info
else
	cd ~/Desktop || exit
	./Y"$(date "+%Y_%m_%d")"
fi
