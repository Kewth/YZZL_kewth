// include files {{{1
#include <string>

// class system {{{1
class System {
private:
	int sys_typ;
public:
	std::string Name();
	int make_file(std::string);
	int copy_file(std::string , std::string);
	System(int);
};
