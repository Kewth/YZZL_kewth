YZZL: bag.o cutcity.o firstcity.o funcity.o jn.o main.o maincity.o people.o shuju.o skycity.o umore.o war.o workcity.o system.o 
	g++ -o $@ $^ -lpthread -std=c++11 
	# -I/usr/include/python2.7 -lpython2.7
umore.o: more.cpp umore.cpp
	g++ -c umore.cpp 
.c.o:
	g++ -c $<
clean:
	rm *.o YZZL