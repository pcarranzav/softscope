# MACROS

LINKER = g++
LINKERPARAMS =
COMPILER = g++
COMPILERPARAMS = -c -O2
OUTPUT = -o
INCLUDE = -I
TOUCH = touch
MAKEDIRECTORY = mkdir
REMOVE = rm
REMOVEPARAMS = -r
SOURCE = src
REGS = $(SOURCE)/regs
TARGET = target
OBJ = $(TARGET)/obj
EXECUTABLE = $(TARGET)/softscope
OBJECTS = $(addprefix $(OBJ)/, $(addsuffix .o, main Configuration State Samples Measurer Mathematician Touch FPGA Display MiniFB MiniInput MiniRegs MiniSPI))
LIBRARIES = $(addprefix -l, fftw3 pthread)

# LINKING

$(EXECUTABLE) : $(OBJECTS)
	$(LINKER) $(LINKERPARAMS) $(OBJECTS) $(LIBRARIES) $(OUTPUT) $(EXECUTABLE) 

# COMPILING

$(OBJ)/main.o : $(SOURCE)/main.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/main.cpp $(INCLUDE) $(SOURCE) $(OUTPUT) $(OBJ)/main.o

$(OBJ)/Configuration.o : $(SOURCE)/Configuration.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/Configuration.cpp $(INCLUDE) $(SOURCE) $(OUTPUT) $(OBJ)/Configuration.o

$(OBJ)/State.o : $(SOURCE)/State.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/State.cpp $(INCLUDE) $(SOURCE) $(OUTPUT) $(OBJ)/State.o

$(OBJ)/Samples.o : $(SOURCE)/Samples.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/Samples.cpp $(INCLUDE) $(SOURCE) $(OUTPUT) $(OBJ)/Samples.o

$(OBJ)/Measurer.o : $(SOURCE)/Measurer.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/Measurer.cpp $(INCLUDE) $(SOURCE) $(OUTPUT) $(OBJ)/Measurer.o

$(OBJ)/Mathematician.o : $(SOURCE)/Mathematician.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/Mathematician.cpp $(INCLUDE) $(SOURCE) $(OUTPUT) $(OBJ)/Mathematician.o

$(OBJ)/Touch.o : $(SOURCE)/Touch.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/Touch.cpp $(INCLUDE) $(SOURCE) $(OUTPUT) $(OBJ)/Touch.o

$(OBJ)/FPGA.o : $(SOURCE)/FPGA.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/FPGA.cpp $(INCLUDE) $(SOURCE) $(OUTPUT) $(OBJ)/FPGA.o

$(OBJ)/Display.o : $(SOURCE)/Display.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/Display.cpp $(INCLUDE) $(SOURCE) $(OUTPUT) $(OBJ)/Display.o

$(OBJ)/MiniFB.o : $(SOURCE)/MiniFB.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/MiniFB.cpp $(INCLUDE) $(SOURCE) $(INCLUDE) $(REGS) $(OUTPUT) $(OBJ)/MiniFB.o

$(OBJ)/MiniInput.o : $(SOURCE)/MiniInput.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/MiniInput.cpp $(INCLUDE) $(SOURCE) $(OUTPUT) $(OBJ)/MiniInput.o

$(OBJ)/MiniRegs.o : $(SOURCE)/MiniRegs.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/MiniRegs.cpp $(INCLUDE) $(SOURCE) $(OUTPUT) $(OBJ)/MiniRegs.o

$(OBJ)/MiniSPI.o : $(SOURCE)/MiniSPI.cpp
	$(COMPILER) $(COMPILERPARAMS) $(SOURCE)/MiniSPI.cpp $(INCLUDE) $(SOURCE) $(INCLUDE) $(REGS) $(OUTPUT) $(OBJ)/MiniSPI.o

# SOURCES

$(SOURCE)/main.cpp : $(SOURCE)/Configuration.hpp $(SOURCE)/State.hpp $(SOURCE)/Samples.hpp $(SOURCE)/Touch.hpp $(SOURCE)/FPGA.hpp $(SOURCE)/Display.hpp $(SOURCE)/MiniRegs.hpp
	$(TOUCH) $(SOURCE)/main.cpp

$(SOURCE)/Configuration.cpp : $(SOURCE)/Configuration.hpp
	$(TOUCH) $(SOURCE)/Configuration.cpp

$(SOURCE)/State.cpp : $(SOURCE)/State.hpp
	$(TOUCH) $(SOURCE)/State.cpp

$(SOURCE)/Samples.cpp : $(SOURCE)/Samples.hpp
	$(TOUCH) $(SOURCE)/Samples.cpp

$(SOURCE)/Measurer.cpp : $(SOURCE)/Measurer.hpp
	$(TOUCH) $(SOURCE)/Measurer.cpp

$(SOURCE)/Mathematician.cpp : $(SOURCE)/Mathematician.hpp
	$(TOUCH) $(SOURCE)/Mathematician.cpp

$(SOURCE)/Touch.cpp : $(SOURCE)/Touch.hpp
	$(TOUCH) $(SOURCE)/Touch.cpp

$(SOURCE)/FPGA.cpp : $(SOURCE)/FPGA.hpp
	$(TOUCH) $(SOURCE)/FPGA.cpp

$(SOURCE)/Display.cpp : $(SOURCE)/Display.hpp
	$(TOUCH) $(SOURCE)/Display.cpp

$(SOURCE)/MiniFB.cpp : $(SOURCE)/MiniFB.hpp $(REGS)/regspinctrl.h $(REGS)/regsclkctrl.h $(REGS)/regslcdif.h
	$(TOUCH) $(SOURCE)/MiniFB.cpp

$(SOURCE)/MiniInput.cpp : $(SOURCE)/MiniInput.hpp
	$(TOUCH) $(SOURCE)/MiniInput.cpp

$(SOURCE)/MiniRegs.cpp : $(SOURCE)/MiniRegs.hpp
	$(TOUCH) $(SOURCE)/MiniRegs.cpp

$(SOURCE)/MiniSPI.cpp : $(SOURCE)/MiniSPI.hpp $(REGS)/regsssp.h $(REGS)/regsclkctrl.h
	$(TOUCH) $(SOURCE)/MiniSPI.cpp

# HEADERS

$(SOURCE)/Configuration.hpp :
	$(TOUCH) $(SOURCE)/Configuration.hpp

$(SOURCE)/State.hpp : $(SOURCE)/Configuration.hpp
	$(TOUCH) $(SOURCE)/State.hpp

$(SOURCE)/Samples.hpp : $(SOURCE)/Configuration.hpp
	$(TOUCH) $(SOURCE)/Samples.hpp

$(SOURCE)/Measurer.hpp : $(SOURCE)/Configuration.hpp $(SOURCE)/State.hpp $(SOURCE)/Samples.hpp
	$(TOUCH) $(SOURCE)/Measurer.hpp

$(SOURCE)/Mathematician.hpp : $(SOURCE)/Configuration.hpp $(SOURCE)/State.hpp $(SOURCE)/Samples.hpp
	$(TOUCH) $(SOURCE)/Mathematician.hpp

$(SOURCE)/Touch.hpp : $(SOURCE)/Configuration.hpp $(SOURCE)/State.hpp $(SOURCE)/Samples.hpp $(SOURCE)/MiniInput.hpp
	$(TOUCH) $(SOURCE)/Touch.hpp

$(SOURCE)/FPGA.hpp : $(SOURCE)/Configuration.hpp $(SOURCE)/State.hpp $(SOURCE)/Samples.hpp $(SOURCE)/MiniRegs.hpp $(SOURCE)/MiniSPI.hpp
	$(TOUCH) $(SOURCE)/FPGA.hpp

$(SOURCE)/Display.hpp : $(SOURCE)/Configuration.hpp $(SOURCE)/State.hpp $(SOURCE)/Samples.hpp $(SOURCE)/Measurer.hpp $(SOURCE)/MiniFB.hpp $(SOURCE)/MiniRegs.hpp
	$(TOUCH) $(SOURCE)/Display.hpp

$(SOURCE)/MiniFB.hpp : $(SOURCE)/MiniRegs.hpp
	$(TOUCH) $(SOURCE)/MiniFB.hpp

$(SOURCE)/MiniInput.hpp :
	$(TOUCH) $(SOURCE)/MiniInput.hpp

$(SOURCE)/MiniRegs.hpp :
	$(TOUCH) $(SOURCE)/MiniRegs.hpp

$(SOURCE)/MiniSPI.hpp : $(SOURCE)/MiniRegs.hpp
	$(TOUCH) $(SOURCE)/MiniSPI.hpp

# MAKING DIRECTORIES

$(OBJECTS) : | $(OBJ)

$(OBJ) : | $(TARGET)
	$(MAKEDIRECTORY) $(OBJ)

$(TARGET) :
	$(MAKEDIRECTORY) $(TARGET)

#CLEANING

clean :
	$(REMOVE) $(REMOVEPARAMS) $(TARGET)

