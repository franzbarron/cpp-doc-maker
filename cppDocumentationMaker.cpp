/**
    @progName cppDocumentationMaker
    @desc Program that creates an HTML file with the documentation of a CPP file
    @author Juan Francisco Barrón Camacho
    @date 23 / January / 2018
 */


#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/**
    @funcName createHTML
    @desc Creates the HTML file with the CPP file's name and the first basic lines (head, title, body)
    @param filename name of the CPP file from which the HTML file will be created
*/
void createHTML(string filename) {
    ofstream html(filename.c_str());
    filename = filename.erase(filename.length() - 5);
    html << "<!DOCTYPE html>\n<html>\n\t<head>\n\t\t<meta charset=\"UTF-8\">\n";
    html << "\t\t<title>" << filename << ".cpp documentation</title>";
    html << "\n\t</head>\n\t<body>" << endl;
    html.close();
}

/**
    @funcName editHTML
    @desc Add the documentation using the tag to create the corresponding format (h1, p, etc)
    @param tag determines the documentation tag. documentation is the documentation per se. filename is the name of the HTML file to be opened and edited
*/
void editHTML(string tag, string documentation, string filename) {
    ofstream html(filename.c_str(), ios::app); // ios::app evita que se sobreescriba el archivo.

    if(tag == "@progName") {
        html << "\t\t<h1>Program:" << documentation << "</h1>" << endl;
    }
    if(tag == "@author") {
        html << "\t\t<p><b>Author:</b>" << documentation << endl;
    }
    if(tag == "@date") {
        html << "\t\t<p><b>Date:</b>" << documentation << endl;
    }
    if(tag == "@funcName") {
        html << "\t\t<hr><h3>Function:" << documentation << "</h3>" << endl;
    }
    if(tag == "@desc") {
        html << "\t\t<p><b>Description:</b>" << documentation << endl;
    }
    if(tag == "@param") {
        html << "\t\t<p><b>Parameters:</b>" << documentation << endl;
    }
    if(tag == "@return") {
        html << "\t\t<p><b>Return value:</b>" << documentation << endl;
    }

    html.close();
}

/**
    @funcName tagSearch
    @desc Looks for a documentation tag in a given line of the CPP file
    @param line is the content of a line in the CPP file. filename is the file's name to be sent to editHTML
*/
void tagSearch(string line, string filename) {
    int i;
    unsigned int j;
    string documentation, htmlTag;
    string tags[7] {"@progName", "@author", "@date", "@funcName", "@desc",
                    "@param", "@return"};

    for(i = 0; i < 7; i++) {
        j = line.find(tags[i]);
        if(j != string::npos) {
            htmlTag = tags[i];
            documentation = line.substr(j + htmlTag.length());
            editHTML(htmlTag, documentation, filename);
        }
    }
}

/**
    @funcName main
    @desc Asks for the name of a CPP file (add the extension if omitted by the user) and creates an HTML file with the documentation
*/
int main() {
    bool flag = false;
    string filename, htmlFilename, line;

    ifstream cppFile;

    cout << "Insert the name of the cpp file." << endl;
    getline(cin, filename);
    if(filename.substr(filename.length() - 4) != ".cpp") {
        htmlFilename = filename + ".html";
        filename += ".cpp";
    }
    else {
        htmlFilename = filename;
        htmlFilename = htmlFilename.erase(filename.length() - 4);
        htmlFilename += ".html";
    }

    cppFile.open(filename.c_str());
    if(!cppFile.is_open()) {
        cout << "Error opening the file.\nPress any key to exit.";
        cin.get();
        return -1;
    }
    createHTML(htmlFilename);
    while(cppFile) {
        getline(cppFile, line);
        if(line == "/**") {
            flag = true;
        }
        if(flag == true) {
            tagSearch(line, htmlFilename);
        }
        if(line == "*/") {
            flag = false;
        }
    }

    ofstream htmlFile(htmlFilename.c_str(), ios::app);
    htmlFile << "\t</body>\n</html>";
    htmlFile.close();

    cout << "Documentation file created\nPress any key to exit.";
    cin.get();

    return 0;
}
