#pragma once
#include <iostream>
#include <string>
class Pipe
{
	float Lenght=0, Diameter=0;
	int IdPipe = -1;

public:
	int GetId();
	double GetD() { return Diameter; }
	static int MaxIdPipe;
	int Status = 0;
	Pipe();
	std::string Name = "";
	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	void EditPipe();
	void SavePipe(std::ofstream& fout) ;
	void LoadPipe(std::ifstream& fin);
	void CheckStatus(int status);

};
