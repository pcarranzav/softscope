#include <Display.hpp>
#include <cmath>

using namespace std;

Display::Display(Configuration& configuration, State& state, Samples& samples, MiniRegs& miniRegs) : configuration(configuration), state(state), samples(samples), measurer(configuration, state, samples), mathematician(configuration, state, samples), miniFB("/dev/fb0", miniRegs)
{
}

void Display::print(void)
{
	clearScreen();
	printGrid(state.getGridCoordenates());
	if(configuration.getChannel(state.getUnselectedChannel()))
	{
		printSamples(samplesToPixels(samples.getSamples(state.getUnselectedChannel()), configuration.getOffset(state.getUnselectedChannel()), configuration.getVerticalScaleValue(state.getUnselectedChannel()), state.getPixelsPerDivision()), configuration.getMemoryDepth() / 2 - (configuration.getDelay() + 5) * state.getPixelsPerDivision(), configuration.getMemoryDepth(), configuration.getStep(), state.getColor(state.getUnselectedChannel()), state.getGridCoordenates());
	}
	if(configuration.getChannel(state.getSelectedChannel()))
	{
		printSamples(samplesToPixels(samples.getSamples(state.getSelectedChannel()), configuration.getOffset(state.getSelectedChannel()), configuration.getVerticalScaleValue(state.getSelectedChannel()), state.getPixelsPerDivision()), configuration.getMemoryDepth() / 2 - (configuration.getDelay() + 5) * state.getPixelsPerDivision(), configuration.getMemoryDepth(), configuration.getStep(), state.getColor(state.getSelectedChannel()), state.getGridCoordenates());
	}
	if(configuration.getMathematic() != Configuration::NOMATHEMATIC)
	{
		printSamples(samplesToPixels(mathematician.getSamples(), 0, configuration.getVerticalScaleValue(state.getSelectedChannel()), state.getPixelsPerDivision()), 0, configuration.getMemoryDepth(), 1, state.getColorMathematics(), state.getGridCoordenates());
	}
	if(state.getSelectedChannel() != Configuration::NO_CHANNEL)
	{
		printOffset(max(min(configuration.getOffset(state.getSelectedChannel()) / configuration.getVerticalScaleValue(state.getSelectedChannel()) * state.getPixelsPerDivision(), 3.5f * state.getPixelsPerDivision()), - 4.0f * state.getPixelsPerDivision()), configuration.getOffsetString(state.getSelectedChannel()), state.getColor(state.getSelectedChannel()), state.getGridCoordenates());
		printVerticalScale(configuration.getVerticalScaleString(state.getSelectedChannel()), state.getColor(state.getSelectedChannel()), state.getGridCoordenates());
	}
	printHorizontalScale(configuration.getHorizontalScaleString(), state.getGridCoordenates());
	printDelay(max(min(configuration.getDelay() * state.getPixelsPerDivision(), 3.5f * state.getPixelsPerDivision()), -5.0f * state.getPixelsPerDivision()), configuration.getDelayString(), state.getGridCoordenates());
	printChannelButton("Channel A", configuration.getChannel(Configuration::CHANNEL_A), state.getSelectedChannel() == Configuration::CHANNEL_A, state.getColor(Configuration::CHANNEL_A), state.getChannelCoordenates(Configuration::CHANNEL_A));
	printChannelButton("Channel B", configuration.getChannel(Configuration::CHANNEL_B), state.getSelectedChannel() == Configuration::CHANNEL_B, state.getColor(Configuration::CHANNEL_B), state.getChannelCoordenates(Configuration::CHANNEL_B));
	printCouplingButton(configuration.getCouplingString(Configuration::CHANNEL_A), state.getColor(Configuration::CHANNEL_A), state.getCouplingCoordenates(Configuration::CHANNEL_A));
	printCouplingButton(configuration.getCouplingString(Configuration::CHANNEL_B), state.getColor(Configuration::CHANNEL_B), state.getCouplingCoordenates(Configuration::CHANNEL_B));
	printButton("Measures", measurer.getMeasure(), state.getMeasuresButtonActive(), state.getMeasuresCoordenates());
	printButton("Mathematics", configuration.getMathematicString(), state.getMathematicsButtonActive(), state.getMathematicsCoordenates());
	printButton("Mode", configuration.getModeString(), state.getModeButtonActive(), state.getModeCoordenates());
	if(configuration.getMeasure() == Configuration::CURSORS)
	{
		vector<float> cursor = configuration.getCursor();
		vector<int> gridCoordenates = state.getGridCoordenates();
		vector<int> cursorCoordenates;
		cursorCoordenates.push_back(min(cursor[0], cursor[1]) * state.getPixelsPerDivision() + gridCoordenates[0] + 5 * state.getPixelsPerDivision());
		cursorCoordenates.push_back(max(cursor[0], cursor[1]) * state.getPixelsPerDivision() + gridCoordenates[0] + 5 * state.getPixelsPerDivision());
		cursorCoordenates.push_back(gridCoordenates[2] + 4 * state.getPixelsPerDivision() - max(cursor[2], cursor[3]) * state.getPixelsPerDivision());
		cursorCoordenates.push_back(gridCoordenates[2] + 4 * state.getPixelsPerDivision() - min(cursor[2], cursor[3]) * state.getPixelsPerDivision());
		printCursor(cursorCoordenates);
	}
	if(state.getMeasuresButtonActive())
	{
		printMenu(configuration.getAllMeasures(), state.getMeasuresMenuCoordenates());
	}
	if(state.getMathematicsButtonActive())
	{
		printMenu(configuration.getAllMathematics(), state.getMathematicsMenuCoordenates());
	}
	if(state.getModeButtonActive())
	{
		printMenu(configuration.getAllModes(), state.getModeMenuCoordenates());
	}
	if(state.getAverageActive())
	{
		printMenu(configuration.getAllAverages(), state.getModeMenuCoordenates());
	}
	if(state.getTriggerModeActive())
	{
		printMenu(configuration.getAllTriggerModes(), state.getModeMenuCoordenates());
	}
	if(state.getTriggerChannelActive())
	{
		printMenu(configuration.getAllChannels(), state.getModeMenuCoordenates());
	}
	if(state.getTriggerSlopeActive())
	{
		printMenu(configuration.getAllTriggerSlopes(), state.getModeMenuCoordenates());
	}
	if(state.getTriggerNoiseRejectActive())
	{
		printMenu(configuration.getAllTriggerNoiseRejects(), state.getModeMenuCoordenates());
	}
	if(state.getTriggerHighFrequencyRejectActive())
	{
		printMenu(configuration.getAllTriggerHighFrequencyRejects(), state.getModeMenuCoordenates());
	}
	if(state.getTriggerLevelActive())
	{
		printAlert("Select the trigger level and hold off", state.getGridCoordenates());
	}
	printMouse(state.getMouseX(), state.getMouseY());
	updateScreen();
}

vector<int> Display::samplesToPixels(const vector<float>& samples, float offset, float verticalScale, int pixelsPerDivision)
{
	vector<int> pixels(samples.size(), 0);
	for(int i = 0; i < samples.size(); i++)
	{
		pixels[i] = (int) ((samples[i] + offset) * pixelsPerDivision / verticalScale);
	}
	return pixels;
}

void Display::clearScreen(void)
{
	miniFB.clearScreen();
}

void Display::updateScreen(void)
{
	miniFB.updateScreen();
}

void Display::printGrid(const vector<int>& coordenates)
{
	int color = miniFB.thinColor(state.getColorGeneral(), 1);
	for(int x = coordenates[0]; x <= coordenates[1]; x += ((coordenates[1] - coordenates[0]) / 10))
	{
		miniFB.drawLine(x, coordenates[2], x, coordenates[3], color);
	}
	for(int y = coordenates[2]; y <= coordenates[3]; y += ((coordenates[3] - coordenates[2]) / 8))
	{
		miniFB.drawLine(coordenates[0], y, coordenates[1], y, color);
	}
}

void Display::printOffset(int offsetValue, string offsetString, int color, const vector<int>& coordenates)
{
	miniFB.drawText(coordenates[0] + 5, (coordenates[2] + coordenates[3]) / 2 - offsetValue - miniFB.getTextHeight(offsetString), offsetString, color);
}

void Display::printVerticalScale(string verticalScale, int color, const vector<int>& coordenates)
{
	miniFB.drawText(coordenates[1] - miniFB.getTextWidth(verticalScale) - 5, (coordenates[2] + coordenates[3]) / 2 - miniFB.getTextHeight(verticalScale), verticalScale, color);
}

void Display::printDelay(int delayValue, std::string delayString, const vector<int>& coordenates)
{
	miniFB.drawText((coordenates[0] + coordenates[1]) / 2 + delayValue, coordenates[3] - miniFB.getTextHeight(delayString) -5, delayString, state.getColorGeneral());
}

void Display::printHorizontalScale(string horizontalScale, const vector<int>& coordenates)
{
	miniFB.drawText((coordenates[0] + coordenates[1]) / 2 + 5, coordenates[2] + 5, horizontalScale, state.getColorGeneral());
}

void Display::printChannelButton(string channel, bool isActive, bool isSelected, int color, const vector<int>& coordenates)
{
	int fillColor;
	if(isSelected)
	{
		fillColor = miniFB.thinColor(color, 2);
	}
	else
	{
		fillColor = miniFB.thinColor(color, 4);
	}
	miniFB.drawRectangle(coordenates[0], coordenates[2], coordenates[1], coordenates[3], fillColor, color);
	if(isActive)
	{
		fillColor = color;
	}
	else
	{
		fillColor = miniFB.thinColor(color, 4);
	}
	miniFB.drawRectangle(coordenates[0] + (coordenates[3] - coordenates[2]) / 4 , (3 * coordenates[2] + coordenates[3]) / 4, coordenates[0] + 3 * (coordenates[3] - coordenates[2]) / 4, (coordenates[2] + 3 * coordenates[3]) / 4, fillColor, color);
	miniFB.drawText(coordenates[0] + (coordenates[3] - coordenates[2]), (coordenates[2] + coordenates[3] - miniFB.getTextHeight(channel)) / 2, channel, color);
}

void Display::printCouplingButton(string text, int color, const vector<int>& coordenates)
{
	miniFB.drawRectangle(coordenates[0], coordenates[2], coordenates[1], coordenates[3], miniFB.thinColor(color, 4), color);
	miniFB.drawText((coordenates[0] + coordenates[1] - miniFB.getTextWidth("Coupling")) / 2, (2 * coordenates[2] + coordenates[3]) / 3 - miniFB.getTextHeight("Coupling") / 2, "Coupling", color);
	miniFB.drawText((coordenates[0] + coordenates[1] - miniFB.getTextWidth(text)) / 2, (coordenates[2] + 2 * coordenates[3]) / 3 - miniFB.getTextHeight(text) / 2, text, color);
}

void Display::printButton(string title, string text, bool isActive, const vector<int>& coordenates)
{
	int color = state.getColorGeneral();
	int fillColor;
	if(isActive)
	{
		fillColor = miniFB.thinColor(color, 1);
	}
	else
	{
		fillColor = miniFB.thinColor(color, 2);
	}
	miniFB.drawRectangle(coordenates[0], coordenates[2], coordenates[1], coordenates[3], fillColor, color);
	miniFB.drawText((coordenates[0] + coordenates[1] - miniFB.getTextWidth(title)) / 2, (6 * coordenates[2] + coordenates[3]) / 7 - miniFB.getTextHeight(title) / 2, title, color);
	miniFB.drawText((coordenates[0] + coordenates[1] - miniFB.getTextWidth(text)) / 2, (3 * coordenates[2] + 4 * coordenates[3]) / 7 - miniFB.getTextHeight(text) / 2, text, color);
}

void Display::printMenu(const vector<string>& options, const vector<int>& coordenates)
{
	int color = state.getColorGeneral();
	miniFB.drawRectangle(coordenates[0], coordenates[3] - options.size() * (coordenates[3] - coordenates[2]), coordenates[1], coordenates[3], miniFB.thinColor(color, 2), color);
	for(int i = 0; i < options.size(); i++)
	{
		miniFB.drawText((coordenates[0] + coordenates[1] - miniFB.getTextWidth(options[i])) / 2, coordenates[3] - (options.size() - i - 0.5) * (coordenates[3] - coordenates[2]) - miniFB.getTextHeight(options[i]) / 2, options[i], color);
	}
}

void Display::printAlert(string text, const vector<int>& coordenates)
{
	miniFB.drawText(coordenates[0] + state.getPixelsPerDivision(), coordenates[2] - state.getPixelsPerDivision() - miniFB.getTextHeight(text), text, state.getColorGeneral());
}

void Display::printSamples(const std::vector<int>& samples, int delay, int memoryDepth, float step, int color, const vector<int>& coordenates)
{
	int upStep = max(1.0, round(step));
	int start = (delay - memoryDepth / 2) * step + memoryDepth / 2;
	for(int i = max(start, 0); i < min((int) (start + round((coordenates[1] - coordenates[0]) * step)), memoryDepth - upStep); i += upStep)
	{
		int ya = (coordenates[2] + coordenates[3]) / 2 - samples[i];
		int yb = (coordenates[2] + coordenates[3]) / 2 - samples[i + upStep];
		if(ya < coordenates[2])
		{
			ya = coordenates[2];
		}
		else if(ya > coordenates[3])
		{
			ya = coordenates[3];
		}
		if(yb < coordenates[2])
		{
			yb = coordenates[2];
		}
		else if(yb > coordenates[3])
		{
			yb = coordenates[3];
		}
		miniFB.drawLine(round(coordenates[0] + (i - start) / step), ya, round(coordenates[0] + (i - start + upStep) / step), yb, color);
	}
}

void Display::printCursor(const vector<int>& coordenates)
{
	miniFB.drawRectangleBorder(coordenates[0], coordenates[2], coordenates[1], coordenates[3], state.getColorGeneral());
}

void Display::printMouse(int x, int y)
{
	miniFB.drawText(x - miniFB.getTextWidth("X") / 2, y - miniFB.getTextHeight("X") / 2, "X", 0xFF0077);
}

