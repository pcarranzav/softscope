#include <Configuration.hpp>
#include <State.hpp>
#include <Samples.hpp>
#include <Touch.hpp>
#include <FPGA.hpp>
#include <Display.hpp>
#include <MiniRegs.hpp>

using namespace std;

int main(int argc, char** argv)
{
	Configuration configuration;
	State state;
	Samples samples;
	MiniRegs miniRegs("/dev/mem", 0xFFFFFFFF, 0x0);
	Touch touch(configuration, state, samples);
	FPGA fpga(configuration, state, samples, miniRegs);
	Display display(configuration, state, samples);
	while(true)
	{
		touch.getInput();
		fpga.fetchSamples();
		display.print();
	}
	return 0;
}

