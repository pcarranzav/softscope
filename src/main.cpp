#include <Configuration.hpp>
#include <State.hpp>
#include <Samples.hpp>
#include <Touch.hpp>
#include <FPGA.hpp>
#include <Display.hpp>
#include <MiniRegs.hpp>

#include <vector>

using namespace std;

int main(int argc, char** argv)
{
	/*Configuration configuration;
	State state;
	Samples samples;*/
	MiniRegs miniRegs("/dev/mem", 0x8000000, 0x80000000);
	MiniSPI miniSPI(miniRegs);
	//vector<int> cmd;
	//cmd.push_back(0xAAAAAAAA);
	//cmd.push_back(0x000000AA);
	//miniSPI.start(cmd);
	/*Touch touch(configuration, state, samples);
	FPGA fpga(configuration, state, samples, miniRegs);
	Display display(configuration, state, samples, miniRegs);
	while(true)
	{
		touch.getInput();
		fpga.fetchSamples();
		display.print();
	}*/
	return 0;
}

