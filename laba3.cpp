#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>

// Структура для представления трубы
struct Pipe {
    std::string id;
    std::string name;
    double length;
    double diameter;
    bool inRepair;
    std::vector<std::string> connectedStations; // Добавлено для хранения связанных станций
};

// Структура для представления КС
struct CompressorStation {
    std::string id;
    std::string name;
    int workshopCount;
    int activeWorkshops;
    double efficiency;
};

// Новая структура для представления соединения трубы и КС
struct Connection {
    std::string pipeId;
    std::string stationId;
    double diameter;
};

std::vector<Connection> connections; // Вектор для хранения соединений

// Функция для соединения трубы с КС
void connectPipeToStation(std::vector<Pipe>& pipes, std::vector<CompressorStation>& stations) {
    std::string pipeId, stationId;
    double diameter;
    std::cout << "Введите ID трубы: ";
    std::cin >> pipeId;
    std::cout << "Введите ID КС: ";
    std::cin >> stationId;
    std::cout << "Введите диаметр трубы: ";
    std::cin >> diameter;

    // Поиск свободной трубы с указанным диаметром
    auto it = std::find_if(pipes.begin(), pipes.end(), [&](const Pipe& pipe) {
        return pipe.diameter == diameter && pipe.connectedStations.empty();
    });

    if (it != pipes.end()) {
        // Соединение найденной трубы с КС
        it->connectedStations.push_back(stationId);
        connections.push_back({pipeId, stationId, diameter});
        std::cout << "Труба успешно соединена с КС." << std::endl;
    } else {
        // Создание новой трубы и соединение ее с КС
        Pipe newPipe;
        newPipe.id = pipeId;
        newPipe.diameter = diameter;
        newPipe.connectedStations.push_back(stationId);
        pipes.push_back(newPipe);
        connections.push_back({pipeId, stationId, diameter});
        std::cout << "Новая труба успешно создана и соединена с КС." << std::endl;
    }
}

// Функция для топологической сортировки
void topologicalSort(const std::vector<Pipe>& pipes, const std::vector<CompressorStation>& stations) {
    std::vector<std::string> sortedIds;
    std::unordered_set<std::string> visited;

    // Вспомогательная функция для DFS
    std::function<void(const std::string&)> dfs = [&](const std::string& id) {
        visited.insert(id);

        // Обработка связанных труб
        for (const auto& pipe : pipes) {
            if (pipe.id == id) {
                for (const auto& stationId : pipe.connectedStations) {
                    if (visited.find(stationId) == visited.end()) {
                        dfs(stationId);
                    }
                }
                break;
            }
        }

        // Обработка связанных станций
        for (const auto& station : stations) {
            if (station.id == id) {
                // Обработка связанных станций
                // (аналогично обработке связанных труб)
                for (const auto& connectedStation : station.connectedStations) {
                    if (visited.find(connectedStation) == visited.end()) {
                        dfs(connectedStation);
                    }
                }
                break;
            }
        }

        sortedIds.push_back(id);
    };

    // Выполнение DFS для каждой непосещенной трубы или станции
    for (const auto& pipe : pipes) {
        if (visited.find(pipe.id) == visited.end()) {
            dfs(pipe.id);
        }
    }

    for (const auto& station : stations) {
        if (visited.find(station.id) == visited.end()) {
            dfs(station.id);
        }
    }

        // Реверсирование отсортированных ID для получения правильного порядка
    std::reverse(sortedIds.begin(), sortedIds.end());

    // Вывод отсортированных ID
    std::cout << "Топологическая сортировка:" << std::endl;
    for (const auto& id : sortedIds) {
        std::cout << id << std::endl;
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
        std::cout << "8. Соединить трубу с КС" << std::endl; // Новая опция для соединения
        std::cout << "9. Топологическая сортировка" << std::endl; // Новая опция для сортировки
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        if (choice == 1) {
            // ... (остальной код остается без изменений)
        } else if (choice == 2) {
            // ... (остальной код остается без изменений)
        } else if (choice == 3) {
            // ... (остальной код остается без изменений)
        } else if (choice == 4) {
            // ... (остальной код остается без изменений)
        } else if (choice == 5) {
            // ... (остальной код остается без изменений)
        } else if (choice == 6) {
            // ... (остальной код остается без изменений)
        } else if (choice == 7) {
            // ... (остальной код остается без изменений)
        } else if (choice == 8) {
            connectPipeToStation(pipes, stations); // Вызов функции для соединения
        } else if (choice == 9) {
            topologicalSort(pipes, stations); // Вызов функции для сортировки
        } else if (choice == 0) {
            break;
        } else {
            std::cout << "Неверный выбор." << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}
