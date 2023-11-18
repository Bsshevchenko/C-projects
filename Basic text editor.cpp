#include <iostream>
#include <fstream>
#include <string>

void displayMenu() {
    std::cout << "1. Ввести текст\n";
    std::cout << "2. Показать текст\n";
    std::cout << "3. Сохранить в файл\n";
    std::cout << "4. Выйти\n";
    std::cout << "Выберите действие (1-4): ";
}

int main() {
    std::string text;
    std::string fileName;

    int choice;
    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Введите текст (для завершения введите 'end'):\n";
                std::cin.ignore(); // Очищаем буфер ввода
                while (true) {
                    std::string line;
                    std::getline(std::cin, line);
                    if (line == "end")
                        break;
                    text += line + "\n";
                }
                break;
            case 2:
                std::cout << "Текущий текст:\n" << text << "\n";
                break;
            case 3:
                std::cout << "Введите имя файла для сохранения: ";
                std::cin >> fileName;
                std::ofstream outFile(fileName);
                if (outFile.is_open()) {
                    outFile << text;
                    std::cout << "Текст успешно сохранен в файле '" << fileName << "'\n";
                    outFile.close();
                } else {
                    std::cerr << "Ошибка открытия файла\n";
                }
                break;
            case 4:
                std::cout << "До свидания!\n";
                break;
            default:
                std::cerr << "Некорректный ввод. Попробуйте еще раз.\n";
        }
    } while (choice != 4);

    return 0;
}
