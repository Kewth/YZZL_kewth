YZZL: bag.o cutcity.o firstcity.o funcity.o jn.o main.o maincity.o people.o shuju.o skycity.o umore.o war.o workcity.o
	g++ -o $@ $^ -lpthread -std=c++11
.c.o:
	g++ -c $<
clean:
	rm *.o YZZL
