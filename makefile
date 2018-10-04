YZZL : main.o umore.o more.o Pmore.o people.o maincity.o cutcity.o funcity.o workcity.o firstcity.o war.o shuju.o bag.o jn.o skycity.o
	g++ -o $@ $^
%.o : %.cpp
	g++ -c $< -std=c++11 -lpthread -Wall
	echo '>>SUCESS'
clean :  
	rm *.o YZZL
