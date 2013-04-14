#include <MiniSPI.hpp>
#include <regsssp.h>
#include <regsclkctrl.h>

MiniSPI::MiniSPI(MiniRegs& miniRegs) : miniRegs(miniRegs)
{
	miniRegs.write(HW_SSP_CTRL0_CLR_ADDR, 0x915CFDFF);
	miniRegs.write(HW_SSP_CTRL0_SET_ADDR, 0x6EA30200);
	miniRegs.write(HW_SSP_CMD0_CLR_ADDR, 0xFFEFFFFF);
	miniRegs.write(HW_SSP_CMD0_SET_ADDR, 0x00100000);
	miniRegs.write(HW_SSP_TIMING_ADDR, 0x00010200);
	miniRegs.write(HW_SSP_CTRL1_CLR_ADDR, 0x30FC1D8C);
	miniRegs.write(HW_SSP_CTRL1_SET_ADDR, 0xCF03E273);
	miniRegs.write(HW_CLKCTRL_SSP_ADDR, 0x80000001);
}

