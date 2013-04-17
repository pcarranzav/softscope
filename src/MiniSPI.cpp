#include <MiniSPI.hpp>
#include <regsssp.h>
#include <regsclkctrl.h>
#include <regspinctrl.h>

using namespace std;

MiniSPI::MiniSPI(MiniRegs& miniRegs) : miniRegs(miniRegs)
{
	miniRegs.write(HW_PINCTRL_MUXSEL0_CLR_ADDR, 0x00000055);
	miniRegs.write(HW_PINCTRL_MUXSEL0_SET_ADDR, 0x000000AA);
	miniRegs.write(HW_PINCTRL_MUXSEL1_CLR_ADDR, 0x05510140);
	miniRegs.write(HW_PINCTRL_MUXSEL1_SET_ADDR, 0x0AA20280);
	miniRegs.write(HW_PINCTRL_DRIVE0_CLR_ADDR, 0x11111111);
	miniRegs.write(HW_PINCTRL_DRIVE0_SET_ADDR, 0x22222222);
	miniRegs.write(HW_PINCTRL_DRIVE2_CLR_ADDR, 0x00011000);
	miniRegs.write(HW_PINCTRL_DRIVE2_SET_ADDR, 0x00022000);
	miniRegs.write(HW_PINCTRL_DRIVE3_CLR_ADDR, 0x00000001);
	miniRegs.write(HW_PINCTRL_DRIVE3_SET_ADDR, 0x00000002);
	miniRegs.write(HW_SSP_CTRL0_CLR_ADDR, 0x915CFDFF);
	miniRegs.write(HW_SSP_CTRL0_SET_ADDR, 0x6EA30200);
	miniRegs.write(HW_SSP_CMD0_CLR_ADDR, 0xFFEFFFFF);
	miniRegs.write(HW_SSP_CMD0_SET_ADDR, 0x00100000);
	miniRegs.write(HW_SSP_TIMING_ADDR, 0x00010200);
	miniRegs.write(HW_SSP_CTRL1_CLR_ADDR, 0x30FC1D8C);
	miniRegs.write(HW_SSP_CTRL1_SET_ADDR, 0xCF03E273);
	miniRegs.write(HW_CLKCTRL_SSP_ADDR, 0x80000001);
}

void MiniSPI::start(vector<int>& cmd)
{
	miniRegs.write(HW_SSP_CMD1_ADDR, cmd[0]);
	miniRegs.write(HW_SSP_CMD0_CLR_ADDR, (~cmd[1]) & 0x000000FF);
	miniRegs.write(HW_SSP_CMD0_SET_ADDR, cmd[1]);
	miniRegs.write(HW_SSP_CTRL0_SET_ADDR, 0x20000000);
}

