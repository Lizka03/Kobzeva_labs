#include <iostream>
class Pipe
{
	float Lenght=0, Diameter=0;
	int Status=0;
public:
	Pipe();
	friend std::istream& operator >> (std::istream& in, Pipe& p);
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	void EditPipe();
	void SavePipe(std::ofstream& file) ;
	void ShowPipe() const;
	void LoadPipe(std::ifstream& file);
	void SetStatus(int);

};
