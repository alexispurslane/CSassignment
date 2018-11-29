//
//  main.cpp
//  FileIO
//
//  Created by Christopher Dumas on 11/28/18.
//  Copyright © 2018 Christopher Dumas. All rights reserved.
//

#include <iostream>
#include <fstream>

enum class Color {
                  Black = 30,
                  Red,
                  Green,
                  Yellow,
                  Blue,
                  Magenta,
                  Cyan,
                  White,
};

std::string colorize(Color color, std::string str) {
    std::string a = std::to_string(static_cast<int>(color));
    return "\u001b[" + a + ";1m" + str + "\u001b[0m";
}

int getFileSize(std::fstream& file) {
    file.seekg(0, file.beg);
    std::streampos b{file.tellg()};
    file.seekg(0, file.end);
    std::streampos e{file.tellg()};

    return e - b;
}

int main(int argc, const char * argv[]) {
    std::fstream file;
    while (true) {
        std::string filename;
        std::cout << colorize(Color::Yellow, "Output file path: ");
        std::getline(std::cin, filename);

        std::cout << colorize(Color::Green, "Loading '" + filename + "'...") << "\n";

        file.open(filename, std::ios::binary | std::ios::in);
        if (file.is_open()) {
            char answer = 'n';
            std::cout << colorize(Color::Red, "This file exists. Overwrite (Y/n)? ");
            std::cin >> answer;
            if (answer == 'n') {
                std::cout << "Ok.\n";
                continue;
            }

            std::cin.ignore();

        }

        file.close();
        file.open(filename, std::ios::binary | std::ios::out | std::ios::trunc | std::ios::in);

        std::cout << colorize(Color::Yellow, "\nBegin entering lines for file: \n");
        // get lines until user enters EOF or blank line.
        int count{1};
        while (true) {
            std::string line;
            std::cout << colorize(Color::Green, std::to_string(count)) << ": ";
            std::getline(std::cin, line);
            if (line == "" || line == "\n") break;
            file << line << "\n";
            count++;
        }
        // print the length
        std::cout << "File length is: " << getFileSize(file) << "\n";

        // get another line
        std::string line;
        std::cout << colorize(Color::Green, std::to_string(count)) << ": ";
        std::getline(std::cin, line);
        file << line;

        // print new length. Reverse order so we end up at the start of the file.
        std::cout << "File length is: " << getFileSize(file) << "\n";


        std::cout << colorize(Color::Yellow, "\nFile read-back: \n");

        file.seekg(0, file.beg);
        count = 0;
        std::string text;
        while (std::getline(file, text)) {
            std::cout << "Line " << count << ": " << text << "\n";
            count++;
        }
        break;
    }

    file.close();
    return 0;
}
