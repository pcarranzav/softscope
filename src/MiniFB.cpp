#include <MiniFB.hpp>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <cstdlib>
#include <sstream>
#include <fstream>

#define FONT_SIZE 8

using namespace std;

MiniFB::MiniFB(string fb, MiniRegs& miniRegs) : miniRegs(miniRegs)
{
	int fd = open(fb.data(), O_RDWR);
	struct fb_var_screeninfo screeninfo;
	ioctl(fd, FBIOGET_VSCREENINFO, &screeninfo);
	width = screeninfo.xres;
	height = screeninfo.yres;
	data = (unsigned int*) mmap(0, 4 * width * height, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	buffer = new unsigned int[width * height];
	for(char c = 'a'; c <= 'z'; c++)
	{
		addCharacter(c);
	}
	for(char c = 'A'; c <= 'Z'; c++)
	{
		addCharacter(c);
	}
	for(char c = '0'; c <= '9'; c++)
	{
		addCharacter(c);
	}
	addCharacter(' ');
	addCharacter('-');
	addCharacter('.');
	addCharacter('/');
	addCharacter(':');
	addCharacter(';');
	addCharacter('=');
	addCharacter('%');
	initLCDIF();
}

MiniFB::~MiniFB()
{
	munmap(data, 4 * width * height);
	delete[] buffer;
	for(map<char, bool*>::iterator i = characterMap.begin(); i != characterMap.end(); i++)
	{
		delete[] i->second;
	}
}

void MiniFB::clearScreen(void)
{
	drawRectangleFill(0, 0, width - 1, height - 1, 0x000000);
}

void MiniFB::updateScreen(void)
{
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			data[y * width + x] = buffer[y * width + x];
		}
	}
}

void MiniFB::drawPixel(int x, int y, int color)
{
	x += 40;	//TEMPORAL
	y += 48;	//TEMPORAL
	if((x >= 0) && (x < width) && (y >= 0) && (y < height))
	{
		buffer[y * width + x] = color;
	}
}

void MiniFB::drawLine(int x1, int y1, int x2, int y2, int color)
{
	if(abs(x2 - x1) > abs(y2 - y1))
	{
		int xStep = (x1 < x2) ? 1 : -1;
		float y = y1 + 0.5;
		float yStep = (float) (y2 - y1) / (x2 - x1);
		for(int x = x1; x != x2; x += xStep)
		{
			drawPixel(x, y, color);
			y += yStep;
		}
	}
	else
	{
		int yStep = (y1 < y2) ? 1 : -1;
		float x = x1 + 0.5;
		float xStep = (float) (x2 - x1) / (y2 - y1);
		for(int y = y1; y != y2; y += yStep)
		{
			drawPixel(x, y, color);
			x += xStep;
		}
	}
}

void MiniFB::drawRectangleFill(int x1, int y1, int x2, int y2, int color)
{
	int xStep = (x1 > x2) ? -1 : 1;
	int yStep = (y1 > y2) ? -1 : 1;
	for(int x = x1; x <= x2; x += xStep)
	{
		for(int y = y1; y <= y2; y += yStep)
		{
			drawPixel(x, y, color);
		}
	}
}

void MiniFB::drawRectangleBorder(int x1, int y1, int x2, int y2, int color)
{
	drawLine(x1, y1, x2, y1, color);
	drawLine(x1, y2, x2, y2, color);
	drawLine(x1, y1, x1, y2, color);
	drawLine(x2, y1, x2, y2, color);
}

void MiniFB::drawRectangle(int x1, int y1, int x2, int y2, int fillColor, int borderColor)
{
	drawRectangleFill(x1, y1, x2, y2, fillColor);
	drawRectangleBorder(x1, y1, x2, y2, borderColor);
}

void MiniFB::drawText(int x, int y, string text, int color)
{
	int xt = x;
	int yt = y;
	for(int i =0; i < text.size(); i++)
	{
		char character = text[i];
		if(character == '\n')
		{
			yt += 5 * FONT_SIZE / 4;
			xt = x;
		}
		else
		{
			bool* pixels = characterMap[character];
			for(int j = 0; j < FONT_SIZE; j++)
			{
				for(int k = 0; k < FONT_SIZE; k++)
				{
					if(pixels[j + k * FONT_SIZE])
					{
						drawPixel(xt + j, yt + k, color);
					}
				}
			}
			xt += FONT_SIZE;
		}
	}
}

int MiniFB::getTextWidth(string text)
{
	int width = 0;
	int tmpWidth = 0;
	for(int i = 0; i < text.size(); i++)
	{
		if(text[i] == '\n')
		{
			if(tmpWidth > width)
			{
				width = tmpWidth;
			}
			tmpWidth = 0;
		}
		else
		{
			tmpWidth += FONT_SIZE;
		}
	}
	if(tmpWidth > width)
	{
		width = tmpWidth;
	}
	return width;
}

int MiniFB::getTextHeight(string text)
{
	int height = FONT_SIZE;
	for(int i =0; i < text.size(); i++)
	{
		if(text[i] == '\n')
		{
			height += 5 * FONT_SIZE / 4;
		}
	}
	return height;
}

int MiniFB::thinColor(int color, int times)
{
	int r = color & 0xFF0000;
	int g = color & 0x00FF00;
	int b = color & 0x0000FF;
	r >>= times;
	g >>= times;
	b >>= times;
	r &= 0xFF0000;
	g &= 0x00FF00;
	b &= 0x0000FF;
	return r | g | b;
}

void MiniFB::addCharacter(char character)
{
	bool* pixels = new bool[FONT_SIZE * FONT_SIZE];
	stringstream ss;
	ss << "font/";
	switch(character)
	{
		case '/':
			ss << "slash";
			break;
		default:
			ss << character;
			break;
	}
	ss << ".txt";
	ifstream myFile(ss.str().data());
	string line;
	if(myFile.is_open())
	{
		for(int i = 0; i < FONT_SIZE; i++)
		{
			getline(myFile, line);
			for(int j = 0; j < FONT_SIZE; j++)
			{
				pixels[i * FONT_SIZE + j] = (line[j] == 'X');
			}
		}
		myFile.close();
	}
	characterMap[character] = pixels;
}

void MiniFB::initLCDIF(void)
{
	
}

