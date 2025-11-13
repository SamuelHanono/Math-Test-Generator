#include <iostream>
#include <fstream>

int addDifficulty(int i, int j) {
    if (i == 0 || j == 0) {return 1;}
    if (i + j <= 10) {return 2;}
    return 3;
}

int subDifficulty(int i, int j) {
    return addDifficulty(i, j);
}

int mulDifficulty(int i, int j) {
    if (i == 0 || j == 0 || i == 1 || j == 1) {return 3;}
    if (i == 2 || j == 2 || i == 5 || j == 5) {return 4;}
    if (i != 7 && j != 7)                     {return 5;}
    return 6;
}

int divDifficulty(int i, int j) {
    if (j == 0) {
        throw std::runtime_error("Division by zero");
    }
    return mulDifficulty(i, j);
}


int main() {
    std::ofstream outputFile("arithmetic_problems.tex"); 
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }
    outputFile << "\\documentclass[12pt]{article}" << std::endl;
    outputFile << "\\usepackage[lmargin=2cm,rmargin=2.25cm,tmargin=1.75cm,bmargin=2cm]{geometry}" << std::endl;
    outputFile << "\\newcommand{\\answer}[1]{} %Don't print answers" << std::endl;
    outputFile << "\\newcommand{\\topic}[1]{} %Don't print topics" << std::endl;
    outputFile << "\\newcommand{\\difficulty}[1]{} %Don't print difficulties" << std::endl;
    outputFile << "\\begin{document}" << std::endl;
    outputFile << "\\begin{enumerate}" << std::endl << std::endl;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            outputFile << "\\item $" << i << " + " << j << "$" << std::endl;
            outputFile << "\\answer{" << i+j << "}" << std::endl;
            outputFile << "\\topic{addition}" << std::endl;
            outputFile << "\\difficulty{" << addDifficulty(i, j) << "}" << std::endl << std::endl;
            outputFile << "\\item $" << i+j << " - " << j << "$" << std::endl;
            outputFile << "\\answer{" << i << "}" << std::endl;
            outputFile << "\\topic{subtraction}" << std::endl;
            outputFile << "\\difficulty{" << subDifficulty(i, j) << "}" << std::endl << std::endl;
            outputFile << "\\item $" << i << " \\cdot " << j << "$" << std::endl;
            outputFile << "\\answer{" << i*j << "}" << std::endl;
            outputFile << "\\topic{multiplication}" << std::endl;
            outputFile << "\\difficulty{" << mulDifficulty(i, j) << "}" << std::endl << std::endl;
            if (j != 0) {
                outputFile << "\\item $" << i*j << " / " << j << "$" << std::endl;
                outputFile << "\\answer{" << i << "}" << std::endl;
                outputFile << "\\topic{division}" << std::endl;
                outputFile << "\\difficulty{" << divDifficulty(i, j) << "}" << std::endl << std::endl;
            }
        }
    }
    outputFile << "\\end{enumerate}" << std::endl << "\\end{document}";
}