#ifndef MINIREGS_HPP
#define MINIREGS_HPP

#include <string>

class MiniRegs
{
	private:
		int* regsMap;
	
	public:
		MiniRegs(std::string driver, int length, int base);
		int read(int address);
		void write(int address, int value);
};

#endif

