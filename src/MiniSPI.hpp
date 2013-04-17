#ifndef MINISPI_HPP
#define MINISPI_HPP

#include <MiniRegs.hpp>
#include <vector>

class MiniSPI
{
	private:
		MiniRegs& miniRegs;

	public:
		MiniSPI(MiniRegs& miniRegs);
		void start(std::vector<int>& cmd);
};

#endif

