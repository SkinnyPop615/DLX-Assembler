#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <cstdint>
#include <iomanip>

using namespace std;

const map <string, int> opcode = {
    {"NOP", 0},
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
    {"JALR", 0x30}
};

const map<string, string> OP_TYPE = {
    {"NOP", "Jump"},
    {"LW", "Memory"},
    {"SW", "Memory"},
    {"ADD", "Register"},
    {"ADDI", "Immediate"},
    {"ADDU", "Register"},
    {"ADDUI", "Immediate"},
    {"SUB", "Register"},
    {"SUBI", "Immediate"},
    {"SUBU", "Register"},
    {"SUBUI", "Immediate"},
    {"AND", "Register"},
    {"ANDI", "Immediate"},
    {"OR", "Register"},
    {"ORI", "Immediate"},
    {"XOR", "Register"},
    {"XORI", "Immediate"},
    {"SLL", "Register"},
    {"SLLI", "Immediate"},
    {"SRL", "Register"},
    {"SRLI", "Immediate"},
    {"SRA", "Register"},
    {"SRAI", "Immediate"},
    {"SLT", "Register"},
    {"SLTI", "Immediate"},
    {"SLTU", "Register"},
    {"SLTUI", "Immediate"},
    {"SGT", "Register"},
    {"SGTI", "Immediate"},
    {"SGTU", "Register"},
    {"SGTUI", "Immediate"},
    {"SLE", "Register"},
    {"SLEI", "Immediate"},
    {"SLEU", "Register"},
    {"SLEUI", "Immediate"},
    {"SGE", "Register"},
    {"SGEI", "Immediate"},
    {"SGEU", "Register"},
    {"SGEUI", "Immediate"},
    {"SEQ", "Register"},
    {"SEQI", "Immediate"},
    {"SNE", "Regeister"},
    {"SNEI", "Immediate"},
    {"BEQZ", "Branch"},
    {"BNEZ", "Branch"},
    {"J", "Jump"},
    {"JR", "Jump"},
    {"JAL", "Jump"},
    {"JALR", "Jump"}
};

struct {
  int opcode;
  int rd;
  int rs1;
  int rs2;
  int unused = 0;
} Register;

struct {
  int opcode;
  int rd;
  int rs1;
  int immmediate;
} Immediate;

struct {
  int opcode;
  int address;
} Jump;

struct {
  int opcode;
  int r_data;
  int r_offset;
  int base_address;
} Memory;

struct {
  int opcode;
  int rs1;
  int label;
} Branch;

map<string, int> labels;

void write_data(ofstream& outfile, string line, int* count);
void write_code(ofstream& outfile, string line, int* count);
void FIRST_PASS(ifstream& dlxFile);
int instruction_count = 0;

int main (int argc, char* argv[]){

    if (argc < 4) {
        cerr << "Not Enough Files";
        return 1;
    }

    string dlxFileName = argv[1];
    string dataFileName = argv[2];
    string codeFileName = argv[3];

    ifstream dlxFile1(dlxFileName);

    if (!dlxFile1.is_open()) {
        cerr << "Error: Could not open input file " << dlxFileName << endl;
        return 1;
    }

    string line;
    ofstream dataFile(dataFileName);
    ofstream codeFile(codeFileName);
    bool data = 0;
    int count = 0;

    dataFile << "DEPTH = 1024;\n";
    dataFile << "WIDTH = 32;\n";
    dataFile << "ADDDRESS_RADIX = HEX;\n";
    dataFile << "DATA_RADIX = HEX;\n";
    dataFile << "CONTENT\n";
    dataFile << "BEGIN\n\n";

    codeFile << "DEPTH = 1024;\n";
    codeFile << "WIDTH = 32;\n";
    codeFile << "ADDDRESS_RADIX = HEX;\n";
    codeFile << "DATA_RADIX = HEX;\n";
    codeFile << "CONTENT\n";
    codeFile << "BEGIN\n\n";

    //First pass 
    FIRST_PASS(dlxFile1);
    
    dlxFile1.close();
    ifstream dlxFile(dlxFileName);

     //Second pass through. Get the instructions
    while (getline(dlxFile, line)) {
                    // Get the first word of each line and ignore white space
        stringstream LINE(line);
        string command;
        LINE >> command;

        // if the line is empty ignore it and loop again
        if (command.empty()) continue;

        if (command[0] != ';'){
            if (command == ".data"){
                data = 1;
            }

            if (command == ".text"){
                data = 0;
            }

            if (data == 1){
                write_data(dataFile, line, &count);
            }
            else{
                write_code(codeFile, line, &count);
            }
            
        }
    }

    dlxFile.close();

    dataFile << "END;";
    codeFile << "END;";

    dataFile.close();
    codeFile.close();
}

void write_data(ofstream& outfile, string line, int* count){

    
}

void write_code(ofstream& outfile, string line, int* count){
        stringstream LINE(line);
        string Instruction, variable1, variable2, variable3;
        LINE >> Instruction;
        int combined = 0;
        //Find out what kind of instruction it is
        if (OP_TYPE.contains(Instruction)){
            string type = OP_TYPE.at(Instruction); //store the type in a string
            if (type == "Register"){
                LINE >> variable1 >> variable2 >> variable3;
                //call Register decode
                variable1.erase(0, 1); //delete the r
                variable2.erase(0, 1);
                variable3.erase(0, 1);
                Register.rd= stoi(variable1); //store the integer address of the registers into our struct
                Register.rs1 = stoi(variable2);
                Register.rs2 = stoi(variable3);
                Register.opcode = opcode.at(Instruction); //store the op code
                //combine all the parts of the instruction together
                combined = (Register.opcode << 26) | (Register.rd << 21) | (Register.rs1 << 16) | (Register.rs2 << 11);

                outfile << hex << uppercase << setfill('0') << setw(3) << *count;
                outfile << " : " << hex << uppercase << setfill('0') << setw(8) << combined << ";";
                outfile << " --" << line << "\n";
            }
            else if (type == "Immediate"){
                // Process Immediate type instruction
                LINE >> variable1 >> variable2 >> variable3;
                //call Register decode
                variable1.erase(0, 1); //delete the r
                variable2.erase(0, 1);
                Immediate.rd= stoi(variable1); //store the integer address of the registers into our struct
                Immediate.rs1 = stoi(variable2);
                Immediate.immmediate = stoi(variable3);
                Immediate.opcode = opcode.at(Instruction); //store the op code
                //combine all the parts of the instruction together
                combined = (Immediate.opcode << 26) | (Immediate.rd << 21) | (Immediate.rs1 << 16) | (Immediate.immmediate << 0);

                outfile << hex << uppercase << setfill('0') << setw(3) << *count;
                outfile << " : " << hex << uppercase << setfill('0') << setw(8) << combined << ";";
                outfile << " --" << line << "\n";
            }
            else if (type == "Jump"){
                LINE >> variable1;
                // Process Jump type instruction
                Jump.opcode = opcode.at(Instruction);

                if (Jump.opcode == 0x2D || Jump.opcode == 0x2F){
                    Jump.address = labels.at(variable1);
                }
                else {
                     variable1.erase(0, 1); //delete the r
                     Jump.address = stoi(variable1);
                }

                combined = (Jump.opcode << 26) | (Jump.address << 0);

                outfile << hex << uppercase << setfill('0') << setw(3) << *count;
                outfile << " : " << hex << uppercase << setfill('0') << setw(8) << combined << ";";
                outfile << " --  " << Instruction << " \t\t" << hex << uppercase << setfill('0') << setw(3) << Jump.address << "\n";

            }
            else if (type == "Memory"){
                LINE >> variable1 >> variable2 >> variable3;
                // Process Memory type instruction
            }
            else if (type == "Branch"){
                LINE >> variable1 >> variable2;
                // Process Branch type instruction
                Branch.opcode = opcode.at(Instruction);
                variable1.erase(0, 1); //delete the r
                Branch.rs1 = stoi(variable1);
                Branch.label = labels.at(variable2);   

                combined = (Branch.opcode << 26) | (Branch.rs1 << 21) | (Branch.label << 0);

                outfile << hex << uppercase << setfill('0') << setw(3) << *count;
                outfile << " : " << hex << uppercase << setfill('0') << setw(8) << combined << ";";
                outfile << " --  " << Instruction << " \t" << "R" << variable1 << " " << hex << uppercase << setfill('0') << setw(3) << Branch.label << "\n";
            }
            (*count)++;
        }

}

   void FIRST_PASS(ifstream& dlxFile)
{
    string line;
    bool inText = false;
    int instruction_count = 0;

    while (getline(dlxFile, line)) {
                // Get the first word of each line and ignore white space
        stringstream LINE(line);
        string command;
        LINE >> command;

        // if the line is empty ignore it and loop again
        if (command.empty()) continue;

        // Ignore comments and loop again
        if (command[0] == ';') continue;

        // Wait for .text to show up
        if (!inText) {
            if (command == ".text") {
                inText = true;
            }
            continue;
        }

        if (opcode.contains(command)){ //if our line is in our instruction set
                instruction_count++; //increment the counter
            }
            else {
                //if it is a label, don't touch the counter and just store the instruction count
                labels[command] = instruction_count; 
            }
    }
    // Debug: Print all labels after first pass
    cout << "\n=== FIRST PASS DEBUG ===" << endl;
    cout << "Total instructions: " << instruction_count << endl;
    cout << "\nLabels found:" << endl;
    for (const auto& [label, address] : labels) {
        cout << "  " << label << " -> instruction " << address << endl;
    }
    cout << "======================\n" << endl;

}
