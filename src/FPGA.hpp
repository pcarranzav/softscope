#ifndef FPGA_HPP
#define FPGA_HPP

#include <Configuration.hpp>
#include <State.hpp>
#include <Samples.hpp>
#include <MiniSPI.hpp>
#include <MiniRegs.hpp>

class FPGA
{
	private:
		Configuration& configuration;
		State& state;
		Samples& samples;
		MiniSPI miniSPI;

	public:
		FPGA(Configuration& configuration, State& state, Samples& samples, MiniRegs& miniRegs);
		void fetchSamples(void);
	
	private:
		int getMask(int bits);
		int quantize(bool value, int shift);
		int quantize(float value, float minimum, int bits, int shift);
		int getFirstMessage(void);
		int getSecondMessage(void);
};

#endif
