#ifndef MINISPI_HPP
#define MINISPI_HPP

#include <MiniRegs.hpp>

class MiniSPI
{
	private:
		MiniRegs& miniRegs;

	public:
		MiniSPI(MiniRegs& miniRegs);
};

#endif

