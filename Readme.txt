softscope
=========

A oscilloscope software

=== SET LCD REGISTERS ===

BM_LCDIF_CTRL_SFTRST ---------------------> BIT MASK FOR SFTRST BIT ON HW_LCDIF_CTRL REGISTER
BV_LCDIF_CTRL_DATA_SELECT__CMD_MODE ------> BIT VALUE. Hay 2^n bit values.
BP_LCDIF_CTRL_SHIFT_NUM_BITS -------------> BIT POSITION en el reg
BF_LCDIF_CTRL_SHIFT_NUM_BITS(v) ----------> BIT FUNCTION. Devuelve valor shifteado y enmascarado. 

gpio_mmap[REG_BASE + REG_OFF] = (gpio_mmap[REG_BASE + REG_OFF] & (~BM)) | BF(BV);

=== LED TEST ===

Pins:

OUT: Olinuxino#28 - micro 81 ("gpmi_ce1n") - Bank 2 Pin 27
GND: Olinuxino#2

GPIO Init:

HW_PINCTRL_MUXSEL5 (0x80018150) --> 23:22 = 11 (Select GPIO function)
HW_PINCTRL_DRIVE11 (0x800182b0) --> 13:12 = 10 (12mA drive)
HW_PINCTRL_PULL2   (0x80018420) --> 27 = 0           (disable pull-up res)
HW_PINCTRL_DOUT2   (0x80018520) --> 27 = 1     (OUT=1)
HW_PINCTRL_DOE2    (0x80018720) --> 27 = 1     (Enable output)

void led(MiniRegs miniRegs)
{
	miniRegs.write(HW_PINCTRL_MUXSEL5_SET_ADDR, 0x00C00000);
	miniRegs.write(HW_PINCTRL_DRIVE11_CLR_ADDR, 0x00001000);
	miniRegs.write(HW_PINCTRL_DRIVE11_SET_ADDR, 0x00002000);
	miniRegs.write(HW_PINCTRL_PULL2_CLR_ADDR, 0x08000000);
	miniRegs.write(HW_PINCTRL_DOUT2_SET_ADDR, 0x08000000);
	miniRegs.write(HW_PINCTRL_DOE2_SET_ADDR, 0x08000000);
	while(true)
	{
		miniRegs.write(HW_PINCTRL_DOUT2_CLR_ADDR, 0x08000000);
		sleep(1);
		miniRegs.write(HW_PINCTRL_DOUT2_SET_ADDR, 0x08000000);
		sleep(1);
	}
}

