#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

std::map<std::string, int> opcode = {
    {"NOP", 0x00},
    {"LW", 0x01},
    {"SW", 0x02},
    {"ADD", 0x03},
    {"ADDI", 0x04},
    {"ADDU", 0x05},
    {"ADDUI", 0x06},
    {"SUB", 0x07},
    {"SUBI", 0x08},
    {"SUBU", 0x09},
    {"SUBUI", 0x0A},
    {"AND", 0x0B},
    {"ANDI", 0x0C},
    {"OR", 0x0D},
    {"ORI", 0x0E},
    {"XOR", 0x0F},
    {"XORI", 0x10},
    {"SLL", 0x11},
    {"SLLI", 0x12},
    {"SRL", 0x13},
    {"SRLI", 0x14},
    {"SRA", 0x15},
    {"SRAI", 0x16},
    {"SLT", 0x17},
    {"SLTI", 0x18},
    {"SLTU", 0x19},
    {"SLTUI", 0x1A},
    {"SGT", 0x1B},
    {"SGTI", 0x1C},
    {"SGTU", 0x1D},
    {"SGTUI", 0x1E},
    {"SLE", 0x1F},
    {"SLEI", 0x20},
    {"SLEU", 0x21},
    {"SLEUI", 0x22},
    {"SGE", 0x23},
    {"SGEI", 0x24},
    {"SGEU", 0x25},
    {"SGEUI", 0x26},
    {"SEQ", 0x27},
    {"SEQI", 0x28},
    {"SNE", 0x29},
    {"SNEI", 0x2A},
    {"BEQZ", 0x2B},
    {"BNEZ", 0x2C},
    {"J", 0x2D},
    {"JR", 0x2E},
    {"JAL", 0x2F},
    {"JALR", 0x30},
};

void write_data(ofstream& outfile, string line);
void write_code(ofstream& outfile, string line);

int main (int argc, char* argv[]){

    if (argc < 4) {
        cerr << "Not Enough Files";
        return 1;
    }

    string dlxFileName = argv[1];
    string dataFileName = argv[2];
    string codeFileName = argv[3];

    ifstream dlxFile(dlxFileName);

    if (!dlxFile) {
        cerr << "Error: Could not open input file " << dlxFileName << endl;
        return 1;
    }
h
    string line;
    ofstream dataFile(dataFileName);
    ofstream codeFile(codeFileName);
    bool data = 0;

    dataFile << "DEPTH = 1024;\n";
    dataFile << "WIDTH = 32;\n";
    dataFile << "ADDDRESS_RADIX = HEX;\n";
    dataFile << "DATA_RADIX = HEX;\n";
    dataFile << "CONTENT\n";
    dataFile << "BEGIN\n";

    codeFile << "DEPTH = 1024;\n";
    codeFile << "WIDTH = 32;\n";
    codeFile << "ADDDRESS_RADIX = HEX;\n";
    codeFile << "DATA_RADIX = HEX;\n";
    codeFile << "CONTENT\n";
    codeFile << "BEGIN\n";


    while (getline(dlxFile, line)) {
        if (line[0] != ';'){
            if (line == ".data"){
                data = 1;
            }

            if (line == ".text"){
                data = 0;
            }

            if (data == 1){
                write_data(dataFile, line);
            }
            else{
                write_code(codeFile, line);
            }
            
        }
    }

    dlxFile.close();

    dataFile << "END;";
    codeFile << "END;";

    dataFile.close();
    codeFile.close();
}

void write_data(ofstream& outfile, string line){


}

void write_code(ofstream& outfile, string line){


}