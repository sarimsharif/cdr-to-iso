#include <iostream>
#include <string>
#include <cstdlib> // for std::system

using namespace std;

int main(int argc, char* argv[]) {
    string cdrPath;
    string isoPath;

    // Check if at least three arguments are provided (-p, file1, file2)
    if (argc == 4 && string(argv[1]) == "-p") {
        cdrPath = argv[2]; // Store the .cdr file path
        isoPath = argv[3]; // Store the .iso file path

        // Remove .iso extension from the destination path, as hdiutil appends ".cdr"
        if (isoPath.size() > 4 && isoPath.substr(isoPath.size() - 4) == ".iso") {
            isoPath = isoPath.substr(0, isoPath.size() - 4);
        }

        // Correct command to convert .cdr to .iso
        string command = "hdiutil convert \"" + cdrPath + "\" -format UDTO -o \"" + isoPath + "\"";
        
        // Execute the command and check for errors
        int result = system(command.c_str());
        if (result != 0) {
            cerr << "Error executing command: " << command << endl;
            return 1; // Indicate an error
        } else {
            // Rename the file to have a .iso extension
            string renameCommand = "mv \"" + isoPath + ".cdr\" \"" + isoPath + ".iso\"";
            result = system(renameCommand.c_str());
            if (result != 0) {
                cerr << "Error renaming .cdr to .iso" << endl;
                return 1;
            }
        }

    } else {
        cout << "Usage: program -p \"<cdr_file_path>\" \"<iso_file_path>\"" << endl;
        return 1; // Indicate incorrect usage
    }

    return 0;
}

