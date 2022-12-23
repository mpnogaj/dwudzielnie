/** @file */ 

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

/**
 * @brief Parsuje argumenty i otwiera pliki 
 * 
 * @param argc Ilosc argumentow 
 * @param argv Tablica argumentow
 * @param inputFile Plik wejsciowy
 * @param outputFile Plik wynikowy
 * @return true parsowanie powiodlo sie
 * @return false parsowanie nie powiodlo sie
 */
bool parseArgs(int argc, char *argv[], ifstream &inputFile, ofstream &outputFile)
{
	string inputFilePath(""), outputFilePath("");
	for (int i = 1; i < argc; i++)
	{
		// sprawdz czy argv[i] jest przelacznikiem
		// jezeli nie to pomin
		if (argv[i] == NULL || strlen(argv[i]) != 2 || argv[i][0] != '-')
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

/// @brief Przeczytaj plik wejsciowy i dla kazdych 2 liczb w linni wywolaj callback
/// @param inputFile plik wejsciowy z danymi
/// @param callback wskaznik do funkcji bioracej dwa inty, zwracajacej void
void processFile(ifstream &inputFile, void (*callback)(int a, int b))
{
	string line;
	for (int lineNr = 1; getline(inputFile, line); lineNr++)
	{
		// przeczytaj dokladnie 2 liczby z linii
		istringstream iss(line);
		int a, b;
		iss >> a >> b;
		if (iss.fail())
		{
			// jezeli nie udalo sie przeczytac 2 liczb to wypisz blad i idz dalej
			cerr << "Empty or invalid line at: " << lineNr << endl;
			continue;
		}
		callback(a, b);
	}
}

int main(int argc, char *argv[])
{
	ifstream inputFile;
	ofstream outputFile;

	// jezeli nie udalo sie sparsowac argumentow to zakoncz programa
	if (!parseArgs(argc, argv, inputFile, outputFile))
		return 1;
	processFile(inputFile, [](int a, int b)
	{ 
		cout << "Line OK. Adding edge between: " << a << " " << b << endl;
	});
	return 0;
}