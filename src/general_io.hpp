#pragma once
#include "stdafx.h"
#include "clara.hpp"
using namespace std;

extern const float version;
//defines the minimum verbosity level for each type of action
enum class verbosity :int {
	steps = 1,
	timing = 1,					//log the walltime at the start of each cout line
	write_defect_file = 2,		//write extra charge density, extra charge potential
	write_dielectric_file = 2,	//write the dielectric profile of model
	write_planarAvg_file = 3,	//writed the planar average of the CHGCAR-LOCPOT files for neutral/charged/defect/model 
	more_digits = 4,			//increase the number of digits in cout and vector output files
	detailed_progress = 4,		//show details of each caculation step for debuging
};

extern int verbos;
extern chrono::time_point<chrono::steady_clock> t0;

// writes each element of a vector in a seperate line inside a text file named "output_file"
void write_vec2file(const vector<double>& input, const string& output_file);

// reads the txt file with double in each line and return a vector
vector<double> read_file2vec(const string& input_file);

//converts the first letter of the string from "a-b-c"/"x-y-z" to 0/1/2
unsigned int xyz2int(const string& s);

// returns the time passed from the start of the program (if needed!)
string timing();

inline bool file_exists(const string& name) {
	ifstream f(name.c_str());
	return f.good();
}

//decides if a functionality is active with the current verbosity level
inline bool is_active(const verbosity& action) noexcept {
	return verbos >= static_cast<int>(verbosity(action));
}

string tolower(string in_str) noexcept;

// reads the commandline and sets the input_file and output_file
void parse_cli(int argc, char *argv[], string& input_file, string& output_file);