#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

std::string readfile(const std::string& pattern, int aenc) {

    if ( aenc !=1 && aenc != 2) {
        std::cout << "Я же сказал 1 или 2!\n";
        return "нужно читать что пишут и да я повторю это дважды";
    }
    std::vector<std::string> foundFiles;

    std::string searchStr = (aenc == 1) ? "notenc" : "enc";

    for (const auto& entry : std::filesystem::directory_iterator(".")) {
        std::string name = entry.path().filename().string();

        if (name.find(searchStr) == std::string::npos)
            continue;

        if (name.find(pattern) == std::string::npos)
            continue;

        if (entry.path().extension() != ".txt")
            continue;

        foundFiles.push_back(name);
    }

    if (foundFiles.empty()) {
        std::cout << "Файлов с таким названием нет\n";
        return "";
    }
    if (foundFiles.size() > 1) {
        std::cout << "Есть несколько файлов с таким названием\n";
        return "";
    }

    std::string inputFile = foundFiles[0];

    std::ifstream fin(inputFile);
    if (!fin) {
        std::cout << "Ошибка открытия файла\n";
        return "";
    }

    std::string input_massage;
    fin >> input_massage; 
    fin.close();

    return input_massage;
}

void createEncfile(const std::string& pattern, const std::string& output_massage, int aenc) {
    if ( aenc !=1 && aenc != 2) {
        std::cout << "Я же сказал 1 или 2!\n";
        return;
    }
    
    
    std::vector<std::string> foundFiles;
    std::string sttr = (aenc == 1) ? "notenc" : "enc";

    for (const auto& entry : std::filesystem::directory_iterator(".")) {
        std::string name = entry.path().filename().string();

        if (name.find(sttr) == std::string::npos)
            continue;

        if (name.find(pattern) == std::string::npos)
            continue;

        if (entry.path().extension() != ".txt")
            continue;

        foundFiles.push_back(name);
    }

    if (foundFiles.empty()) {
        std::cout << "Файлов с таким названием нет\n";
        return;
    }
    if (foundFiles.size() > 1) {
        std::cout << "Есть несколько файлов с таким названием\n";
        return;
    }

    std::string inputFile = foundFiles[0];

    std::string outputFile = inputFile;
    if (aenc == 1) { 
        size_t pos = outputFile.find("notenc");
        if (pos != std::string::npos) {
            outputFile.replace(pos, 6, "enc");
        }
    } else {
        size_t pos = outputFile.find("enc");
        if (pos != std::string::npos) {
            outputFile.replace(pos, 3, "notenc");
        }
    }

    std::ofstream fout(outputFile);
    if (!fout) {
        std::cout << "Ошибка создания файла\n";
        return;
    }

    fout << output_massage;
    fout.close();

    std::cout << "Файл: " << outputFile << " создан" << "\n";
}

int main() {
    std::string pattern;
    int aenc;

    std::cout << "Введите часть или полное название файла для поиска файла: ";
    std::cin >> pattern;

    std::cout << "Введите 1 для кодировки или 2 для декодировки: ";
    std::cin >> aenc;

    std::string input_massage = readfile(pattern, aenc);

    if (!input_massage.empty()) {
        std::cout << input_massage << "\n";
 
        createEncfile(pattern, input_massage, aenc);
    }

    return 0;
}