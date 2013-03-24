softscope
=========

A oscilloscope software

BM_LCDIF_CTRL_SFTRST ---------------------> BIT MASK FOR SFTRST BIT ON HW_LCDIF_CTRL REGISTER
BV_LCDIF_CTRL_DATA_SELECT__CMD_MODE ------> BIT VALUE. Hay 2^n bit values.
BP_LCDIF_CTRL_SHIFT_NUM_BITS -------------> BIT POSITION en el reg
BF_LCDIF_CTRL_SHIFT_NUM_BITS(v) ----------> BIT FUNCTION. Devuelve valor shifteado y enmascarado. 

gpio_mmap[REG_BASE + REG_OFF] = (gpio_mmap[REG_BASE + REG_OFF] & (~BM)) | BF(BV);
