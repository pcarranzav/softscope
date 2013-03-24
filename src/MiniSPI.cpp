#include <MiniSPI.hpp>
#include <mxs-spi.h>
#include <regs-clkctrl.h>

MiniSPI::MiniSPI(MiniRegs& miniRegs) : miniRegs(miniRegs)
{
	miniRegs.write(HW_SSP_BASE + HW_SSP_CTRL0, 0x6EA30200);
	miniRegs.write(HW_SSP_BASE + HW_SSP_CMD0, 0x00100000);
	miniRegs.write(HW_SSP_BASE + HW_SSP_TIMING, 0x00010200);
	miniRegs.write(HW_SSP_BASE + HW_SSP_CTRL1, 0xCF03E273);
	miniRegs.write(HW_CLKCTRL_SSP_ADDR, 0x80000001);
}

