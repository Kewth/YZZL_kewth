// include files {{{1
#include <fstream>
#include "h/system.h"
#define NOTHING ;;;

// name of system {{{1
std::string System::Name() {
	switch(sys_typ) {
		default:
			return "";
		case 0:
			return "";
		case 1:
			NOTHING {
				system("whoami > just_now.txt"); 
				std::ifstream fin;
				fin.open("just_now.txt");
				std::string res;
				fin >> res;
				return res;
			}
	}
}

// Make a file {{{1
int System::make_file(std::string name) {
	switch(sys_typ) {
		default:
			return -1;
		case 0:
		case 1:
			if(name[name.size()-1] == '/') 
				return system(("mkdir -p " + name).c_str());
			else
				return system(("touch " + name).c_str());
	}
}

// Copy a file {{{1
int System::copy_file(std::string name,std::string to) {
	switch(sys_typ) {
		default:
			return -1;
		case 0:
			return system(("copy " + name + " " + to).c_str());
		case 1:
			return system(("cp " + name + " " + to).c_str());
	}
}

// System init {{{1
System::System(int typ) : sys_typ(typ) {
}
