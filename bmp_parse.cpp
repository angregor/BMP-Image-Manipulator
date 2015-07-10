#include "bmp_parse.h"
#include <iostream>
#include <string.h>

using namespace std;
char tempbuff[4];
//Constructor for Bmp_Parse
BmpParse::BmpParse()
{
	bmp_header.charbm;
	bmp_header.filesize = 0;
	bmp_header.reserved1 = 0;
	bmp_header.reserved2 = 0;
	bmp_header.pixeloffset = 0;
	bmp_header.infoheadersize = 0;
	bmp_header.imgwidth = 0;
	bmp_header.imgheight = 0;	
	bmp_header.numbitplanes = 0;
	bmp_header.numbitsperpixel = 0;
	bmp_header.random;
	padding = 0;
}

BmpParse::~BmpParse()
{
	//deallocate 2-d array
	if(image != NULL)
	{
		for(int i = 0; i < bmp_header.imgheight; i++)
		{
			delete [] image[i];
		}
		delete [] image;
	}

	//close infile
	if(infile.is_open())
		infile.close();
	//close outfile
	if(outfile.is_open())
		outfile.close();	
}

int BmpParse::readfile(char* filename)
{
	int i;
	char buffer[4];
	infile.open(filename, ios::in | ios::binary);
	cout << "Started Read" << endl;

	if(!infile.is_open())
		return -1; // Could not open file.

	if(infile.good())
		infile.read((char*)&bmp_header, sizeof(struct bmp_head));
	else
		return -2; // Error reading header.
	
	if(!infile)
		return -2; // Error reading header.
	
	cout << "Opened File" << endl;
	/*
	// Verify BM block
	memcpy(buffer, bmp_header.charbm, 2);
	buffer[3] = '\0';
	if(strcmp(buffer, "BM") != 0)
	{
		return -3; // File type error
	}
	*/
	cout << "Verified BMP" << endl;
	//calculate padding
	padding = (4 - ((bmp_header.imgwidth * 3) % 4)) % 4;
	//allocate 2-d array
	infile.seekg(bmp_header.pixeloffset);
	image = new unsigned char*[bmp_header.imgheight];
	for(int k = 0; k < bmp_header.imgheight; k++)
	{
		image[k] = new unsigned char[bmp_header.imgwidth*3];
		infile.read((char*)image[k], (bmp_header.imgwidth*3));
		infile.read(tempbuff, padding);
	}
	//success
	return 0;
}

int BmpParse::writefile(char* filename)
{
	outfile.open(filename, ios::out | ios::binary);
	if(!outfile.is_open())
		return -1; // Could not open file error
	//write the header
	if(outfile.good())
	{
		outfile.write((char*)&bmp_header, sizeof(struct bmp_head));
	}
	else
	{
		return -2;
	}
	//new padding
	padding = (4 - ((bmp_header.imgwidth * 3) % 4)) % 4;
	//write the 2-d array
	
	for(int j = 0; j < bmp_header.imgheight; j++)
	{
		outfile.write((char*)image[j], (bmp_header.imgwidth*3));
		outfile.write(tempbuff, padding);
	}
	
	outfile.close();
	return 0;
}

void BmpParse::flipx() //DONE
{
	//create temprow for switching
	unsigned char temprow[bmp_header.imgwidth*3];
	//loop through rows, switching them
	cout << "Created Temp Row" << endl;
	for(int l = 0; l < bmp_header.imgheight/2; l++)
	{
		//implement switching
		memcpy(temprow,(char*)image[l], (bmp_header.imgwidth*3));
		memcpy((char*)image[l],image[(bmp_header.imgheight-1)-l], (bmp_header.imgwidth*3));
		memcpy((char*)image[(bmp_header.imgheight-1)-l],temprow, sizeof(temprow));
	}
}

void BmpParse::flipy() //DONE NO COLOR :(
{
	//create tempcolumn for switching
	unsigned char temppixel;

	//loop through columns, switching them
	for(int m = 0; m < bmp_header.imgheight; m++)
	{
		for(int o = 0; o < bmp_header.imgwidth*3/2; o++)
		{
			temppixel = image[m][o];
			image[m][o] = image[m][bmp_header.imgwidth*3-1-o];
			image[m][bmp_header.imgwidth*3-1-o] = temppixel;
		}
	}
}


void BmpParse::printHeader()
{
	cout << "CharBM: " << bmp_header.charbm << endl;
	cout << "FileSize:: " << bmp_header.filesize << endl;
	cout << "Reserved: " << bmp_header.reserved1 << endl;
	cout << "Reserved: " << bmp_header.reserved2 << endl;
	cout << "PixelOffset: " << bmp_header.pixeloffset << endl;
	cout << "InfoHeadSize: " << bmp_header.infoheadersize << endl;
	cout << "ImgWidth: " << bmp_header.imgwidth << endl;
	cout << "ImgHeight: " << bmp_header.imgheight << endl;	
	cout << "BitPlanes: " << bmp_header.numbitplanes << endl;
	cout << "BitsPerPixel: " << bmp_header.numbitsperpixel << endl;
}