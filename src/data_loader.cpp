#include "data_loader.h"
#include<fstream>
#include<stdexcept>
using namespace std;

vector<string>DataLoader::load_file(const string& filename)
{
    ifstream file(filename);

    //error check
    if(!file.is_open())
    {
        throw runtime_error("Cannot open file: " + filename);
    }

    //set up buffering
    char buffer[65536]; //[64KB Buffer]
    file.rdbuf()->pubsetbuf(buffer, 65536); //Now OS reads 65KB chunks, not 1 line at a time
    
    //read all lines
    vector<string>lines;
    string line;
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    return lines;
}