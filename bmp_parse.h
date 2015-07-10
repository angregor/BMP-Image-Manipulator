#ifndef BMP_PARSE
#define BMP_PARSE

#include <fstream>

using namespace std;

struct bmp_head
{
	unsigned char charbm[2];
	unsigned int filesize;
	unsigned short reserved1;
	unsigned short reserved2;
	unsigned int pixeloffset;
	unsigned int infoheadersize;
	unsigned int imgwidth;
	unsigned int imgheight;
	unsigned short numbitplanes;
	unsigned short numbitsperpixel;
	unsigned char random[24];
} __attribute__((packed));

struct pixels
{
	char bytes[3];
};

class BmpParse
{
public:
	BmpParse();
	~BmpParse();
	int readfile(char* filename);
	int writefile(char* filename);
	int padding;
	void printHeader();
	void flipx();
	void flipy();
	char tempbuff[4];
private:
	std::fstream infile;
	std::ofstream outfile;
	struct bmp_head bmp_header;
	unsigned char** image;
};

#endif