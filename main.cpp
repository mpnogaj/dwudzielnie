#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

bool parseArgs(int argc, char *argv[], ifstream &inputFile, ofstream &outputFile)
{
	string inputFilePath(""), outputFilePath("");
	for (int i = 1; i < argc; i++)
	{
		if (argv[i] == NULL || strlen(argv[i]) != 2)
			continue;
		if (argv[i][0] != '-')
			continue;

		if (argv[i][1] == 'i')
		{
			if (i + 1 >= argc)
				continue;
			inputFilePath = string(argv[i + 1]);
		}
		else if (argv[i][1] == 'o')
		{
			if (i + 1 >= argc)
				continue;
			outputFilePath = string(argv[i + 1]);
		}
	}

	if (inputFilePath.empty() || outputFilePath.empty())
	{
		cerr << "Nie podano wymaganych przelacznikow." << endl;
		return false;
	}

	inputFile.open(inputFilePath);
	outputFile.open(outputFilePath);

	if (!inputFile.is_open() || !outputFile.is_open())
	{
		cerr << "Nie mozna otworzyc plikow. Byc moze nie istnieja, albo program nie ma wymaganych uprawnien." << endl;
		return false;
	}

	return true;
}

int main(int argc, char *argv[])
{
	ifstream inputFile;
	ofstream outputFile;

	if (!parseArgs(argc, argv, inputFile, outputFile))
		return 1;
	return 0;
}