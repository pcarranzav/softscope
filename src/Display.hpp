#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <Configuration.hpp>
#include <State.hpp>
#include <Samples.hpp>
#include <Measurer.hpp>
#include <Mathematician.hpp>
#include <MiniFB.hpp>
#include <MiniRegs.hpp>
#include <string>
#include <vector>

class Display
{
	private:
		Configuration& configuration;
		State& state;
		Samples& samples;
		Measurer measurer;
		Mathematician mathematician;
		MiniFB miniFB;

	public:
		Display(Configuration& configuration, State& state, Samples& samples, MiniRegs& miniRegs);
		void print(void);

	private:
		std::vector<int> samplesToPixels(const std::vector<float>& samples, float offset, float verticalScale, int pixelsPerDivision);
		void clearScreen(void);
		void updateScreen(void);
		void printGrid(const std::vector<int>& coordenates);
		void printOffset(int offsetValue, std::string offsetString, int color, const std::vector<int>& coordenates);
		void printVerticalScale(std::string verticalScale, int color, const std::vector<int>& coordenates);
		void printDelay(int delayValue, std::string delayString, const std::vector<int>& coordenates);
		void printHorizontalScale(std::string horizontalScale, const std::vector<int>& coordenates);
		void printChannelButton(std::string channel, bool isActive, bool isSelected, int color, const std::vector<int>& coordenates);
		void printCouplingButton(std::string text, int color, const std::vector<int>& coordenates);
		void printButton(std::string title, std::string text, bool isActive, const std::vector<int>& coordenates);
		void printMenu(const std::vector<std::string>& options, const std::vector<int>& coordenates);
		void printAlert(std::string text, const std::vector<int>& coordenates);
		void printSamples(const std::vector<int>& samples, int delay, int memoryDepth, float step, int color, const std::vector<int>& coordenates);
		void printCursor(const std::vector<int>& coordenates);
		void printMouse(int x, int y);
};

#endif

