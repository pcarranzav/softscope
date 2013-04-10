#include <MiniRegs.hpp>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

MiniRegs::MiniRegs(string driver, int length, int base)
{
	//int fd = open(driver.data(), O_RDWR);
	//regsMap = (int*) mmap(0, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, base);
	//close(fd);
}

int MiniRegs::read(int address)
{
	//return regsMap[address >> 2];
}

void MiniRegs::write(int address, int value)
{
	//regsMap[address >> 2] = value;
}

