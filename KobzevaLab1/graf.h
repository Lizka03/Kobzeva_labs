#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <float.h>
#include <unordered_map>
#include <unordered_set>
#include "Pipe.h"
#include "CS.h"
using namespace std;
class System
	{
	public:
		unordered_map <int, Pipe> PGroup;
		unordered_map <int, CS> CsGroup;
		unordered_set<int> pipe;
		unordered_set<int> cs;
		void information();
		void SaveData();
		void LoadData();
		void EditCs();
		unordered_set<int> SearchCs();
		void EditPipe();
		unordered_set<int> SearchPipe();
		struct Graph {
			static int max_idg;
			int id;
			Graph(){id = max_idg++;}
			int id_entrance;
			int id_exit;	
			int id_pipe;
			void save_edge(ofstream& file);
			void load_edge(ifstream& file);
		};
		friend istream& operator >> (istream& in, System& s);
		friend ostream& operator <<(ostream& out, unordered_set<int> s);
		unordered_map <int, Graph> graphs;
		int check_pipe(int x);
		bool checking(int x);
		int edge(int x);
		int check_graph(int x);
		int check_existing(int x);
		bool check_only(int x, int y);
		bool check_obj(int x);
};

