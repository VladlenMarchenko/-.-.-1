#include <iostream> 
#include <fstream> 
#include <vector> 
 
// Структура для представления трубы 
struct Pipe { 
    std::string name; 
    double length; 
    double diameter; 
    bool inRepair; 
 
    void readFromConsole() { 
        std::cout << "Введите название трубы: "; 
        std::cin >> name; 
        std::cout << "Введите длину трубы (в километрах): "; 
        std::cin >> length; 
        std::cout << "Введите диаметр трубы: "; 
        std::cin >> diameter; 
        std::cout << "Труба в ремонте? (1 - да, 0 - нет): "; 
        std::cin >> inRepair; 
    } 
 
    void printToConsole() { 
        std::cout << "Название: " << name << std::endl; 
        std::cout << "Длина (км): " << length << std::endl; 
        std::cout << "Диаметр: " << diameter << std::endl; 
        std::cout << "В ремонте: " << (inRepair ? "Да" : "Нет") << std::endl; 
    } 
}; 
 
// Структура для представления КС 
struct CompressorStation { 
    std::string name; 
    int workshopCount; 
    int activeWorkshops; 
    double efficiency; 
 
    void readFromConsole() { 
        std::cout << "Введите название КС: "; 
        std::cin >> name; 
        std::cout << "Введите количество цехов: "; 
        std::cin >> workshopCount; 
        std::cout << "Введите количество активных цехов: "; 
        std::cin >> activeWorkshops; 
        std::cout << "Введите показатель эффективности: "; 
        std::cin >> efficiency; 
    } 
 
    void printToConsole() { 
        std::cout << "Название: " << name << std::endl; 
        std::cout << "Количество цехов: " << workshopCount << std::endl; 
        std::cout << "Активных цехов: " << activeWorkshops << std::endl; 
        std::cout << "Эффективность: " << efficiency << std::endl; 
    } 
}; 
 
// Функция для сохранения данных в файл 
void saveData(const std::vector<Pipe>& pipes, const std::vector<CompressorStation>& stations) { 
    std::ofstream file("data.txt"); 
    if (file.is_open()) { 
        file << pipes.size() << std::endl; 
        for (const auto& pipe : pipes) { 
            file << pipe.name << std::endl; 
            file << pipe.length << std::endl; 
            file << pipe.diameter << std::endl; 
            file << pipe.inRepair << std::endl; 
        } 
 
        file << stations.size() << std::endl; 
        for (const auto& station : stations) { 
            file << station.name << std::endl; 
            file << station.workshopCount << std::endl; 
            file << station.activeWorkshops << std::endl; 
            file << station.efficiency << std::endl; 
        } 
 
        file.close(); 
        std::cout << "Данные сохранены в файл." << std::endl; 
    } else { 
        std::cout << "Не удалось открыть файл для сохранения данных." << std::endl; 
    } 
} 
 
// Функция для загрузки данных из файла 
void loadData(std::vector<Pipe>& pipes, std::vector<CompressorStation>& stations) { 
    std::ifstream file("data.txt"); 
    if (file.is_open()) { 
        pipes.clear(); 
        stations.clear(); 
 
        int pipeCount; 
        file >> pipeCount; 
        file.ignore(); 
 
        for (int i = 0; i < pipeCount; ++i) { 
            Pipe pipe; 
            std::getline(file, pipe.name); 
            file >> pipe.length; 
            file >> pipe.diameter; 
            file >> pipe.inRepair; 
            file.ignore(); 
            pipes.push_back(pipe); 
        } 
 
        int stationCount; 
        file >> stationCount; 
        file.ignore(); 
 
        for (int i = 0; i < stationCount; ++i) { 
            CompressorStation station; 
            std::getline(file, station.name); 
            file >> station.workshopCount; 
            file >> station.activeWorkshops; 
            file >> station.efficiency; 
            file.ignore(); 
            stations.push_back(station); 
        } 
 
        std::cout << "Данные загружены из файла." << std::endl; 
    } else { 
        std::cout << "Не удалось открыть файл для загрузки данных." << std::endl; 
    } 
} 
 
int main() { 
    std::vector<Pipe> pipes; 
    std::vector<CompressorStation> stations; 
 
    int choice; 
    while (true) { 
        std::cout << "Меню:" << std::endl; 
        std::cout << "1. Добавить трубу" << std::endl; 
        std::cout << "2. Добавить КС" << std::endl; 
        std::cout << "3. Просмотр всех объектов" << std::endl; 
        std::cout << "4. Редактировать трубу" << std::endl; 
        std::cout << "5. Редактировать КС" << std::endl; 
        std::cout << "6. Сохранить" << std::endl; 
        std::cout << "7. Загрузить" << std::endl; 
        std::cout << "0. Выход" << std::endl; 
        std::cout << "Выберите действие: "; 
        std::cin >> choice; 
 
        if (choice == 1) { 
            Pipe pipe; 
            pipe.readFromConsole(); 
            pipes.push_back(pipe); 
        } else if (choice == 2) { 
            CompressorStation station; 
            station.readFromConsole(); 
            stations.push_back(station); 
        } else if (choice == 3) { 
            std::cout << "Трубы:" << std::endl; 
            for (const auto& pipe : pipes) { 
                pipe.printToConsole(); 
                std::cout << std::endl; 
            } 
 
            std::cout << "Компрессорные станции:" << std::endl; 
            for (const auto& station : stations) { 
                station.printToConsole(); 
                std::cout << std::endl; 
            } 
        } else if (choice == 4) { 
            int index; 
            std::cout << "Введите индекс трубы для редактирования: "; 
            std::cin >> index; 
 
            if (index >= 0 && index < pipes.size()) { 
                Pipe& pipe = pipes[index]; 
                std::cout << "Текущий статус ремонта: " << (pipe.inRepair ? "В ремонте" : "Не в ремонте") << std::endl; 
                std::cout << "Изменить статус ремонта? (1 - да, 0 - нет): "; 
                std::cin >> pipe.inRepair; 
            } else { 
                std::cout << "Неверный индекс трубы." << std::endl; 
            } 
        } else if (choice == 5) { 
            int index; 
            std::cout << "Введите индекс КС для редактирования: "; 
            std::cin >> index; 
 
            if (index >= 0 && index < stations.size()) { 
                CompressorStation& station = stations[index]; 
                std::cout << "Текущее количество активных цехов: " << station.activeWorkshops << std::endl; 
                std::cout << "Изменить количество активных цехов: "; 
                std::cin >> station.activeWorkshops; 
            } else { 
                std::cout << "Неверный индекс КС." << std::endl; 
            } 
        } else if (choice == 6) { 
            saveData(pipes, stations); 
        } else if (choice == 7) { 
            loadData(pipes, stations); 
        } else if (choice == 0) { 
            break; 
        } else { 
            std::cout << "Неверный выбор." << std::endl; 
        } 
 
        std::cout << std::endl; 
    } 
 
    return 0; 
}
