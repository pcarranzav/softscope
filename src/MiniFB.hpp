#ifndef MINIFB_HPP
#define MINIFB_HPP

#include <string>

class MiniFB
{
	public:
		enum FONTS {SMALL, MEDIUM, LARGE};

	private:
		int width;
		int height;
		unsigned int* data;

	public:
		MiniFB(std::string fb);
		~MiniFB();
		void drawPixel(int x, int y, int color);
		void drawLine(int x1, int y1, int x2, int y2, int color);
		void drawRectangleFill(int x1, int y1, int x2, int y2, int color);
		void drawRectangleBorder(int x1, int y1, int x2, int y2, int color);
		void drawRectangle(int x1, int y1, int x2, int y2, int fillColor, int borderColor);
		void drawText(int x, int y, std::string text, int color, FONTS font);
		int getTextWidth(std::string text, FONTS font);
		int getTextHeight(std::string text, FONTS font);
		int thinColor(int color, int times);
};

#endif

