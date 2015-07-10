#include <iostream>
#include "bmp_parse.h"

using namespace std;

int main(int argc, char* argv[])
{
	BmpParse parser;

	if(argc < 4)
	{
		cout << "Usage: " << argv[0] << " <input file> <command> <output file>" << endl;
		return -1;
	}
	cout << "Got Past Usage!" << endl;
	int ret = 0;
	ret = parser.readfile(argv[1]);
	cout << "Got Past Initial Read!" << endl;
	if(ret == 0)
	{
		cout << "Read Success!" << endl;
		parser.printHeader();
		cout << "Modifying..." << endl;
		if(strcmp(argv[2], "flipx") == 0)
		{
			parser.flipx();
		}
		else if(strcmp(argv[2], "flipy") == 0)
		{
			parser.flipy();
		}
		else
		{
			cout << "Error: command not understood!" << endl;
			return 0;
		}
		cout << "Writing..." << endl;
		if(parser.writefile(argv[3]) != 0)
			cout << "Error writing file" << endl;
		else
			cout << "Completed." << endl;
	}
	else
	{
		cout << "Parsing Error: " << ret << endl;
		parser.printHeader();
	}

	return 0;
}