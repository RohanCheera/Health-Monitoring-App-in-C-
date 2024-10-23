#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// Data structure to store health data
struct HealthData {
    std::string date;
    int heartRate;
    int activityLevel;
    int sleepHours;
};

// Data Collector module
class DataCollector {
public:
    HealthData collectData() {
        HealthData data;
        std::cout << "Enter date (YYYY-MM-DD): ";
        std::cin >> data.date;
        std::cout << "Enter heart rate (bpm): ";
        std::cin >> data.heartRate;
        std::cout << "Enter activity level (1-5): ";
        std::cin >> data.activityLevel;
        std::cout << "Enter sleep hours: ";
        std::cin >> data.sleepHours;
        return data;
    }
};

// Data Analyzer module
class DataAnalyzer {
public:
    std::string analyzeData(const std::vector<HealthData>& data) {
        // Determine patterns and provide recommendations
        int averageHeartRate = 0;
        int averageActivityLevel = 0;
        int averageSleepHours = 0;
        for (const auto& entry : data) {
            averageHeartRate += entry.heartRate;
            averageActivityLevel += entry.activityLevel;
            averageSleepHours += entry.sleepHours;
        }
        averageHeartRate /= data.size();
        averageActivityLevel /= data.size();
        averageSleepHours /= data.size();

        std::string recommendation;
        if (averageHeartRate > 100) {
            recommendation += "Your heart rate is higher than average. Consider exercising regularly.\n";
        }
        if (averageActivityLevel < 3) {
            recommendation += "Your activity level is lower than average. Consider increasing your physical activity.\n";
        }
        if (averageSleepHours < 7) {
            recommendation += "You are not getting enough sleep. Aim for 7-8 hours of sleep per night.\n";
        }
        return recommendation;
    }
};

// Data Storage module
class DataStorage {
public:
    void storeData(const HealthData& data) {
        std::ofstream file("health_data.txt", std::ios_base::app);
        file << data.date << "," << data.heartRate << "," << data.activityLevel << "," << data.sleepHours << std::endl;
        file.close();
    }

    std::vector<HealthData> retrieveData() {
        std::vector<HealthData> data;
        std::ifstream file("health_data.txt");
        std::string line;
        while (std::getline(file, line)) {
            HealthData entry;
            size_t pos = line.find(",");
            entry.date = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = line.find(",");
            entry.heartRate = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            pos = line.find(",");
            entry.activityLevel = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            entry.sleepHours = std::stoi(line);
            data.push_back(entry);
        }
        file.close();
        return data;
    }
};

// User Interface module
class UserInterface {
public:
    void displayMenu() {
        std::cout << "Health Monitoring Application\n";
        std::cout << "1. Input health data\n";
        std::cout << "2. View recommendations\n";
        std::cout << "3. Exit\n";
    }

    void inputHealthData(DataCollector& collector, DataStorage& storage) {
        HealthData data = collector.collectData();
        storage.storeData(data);
    }

    void viewRecommendations(DataAnalyzer& analyzer, DataStorage& storage) {
        std::vector<HealthData> data = storage.retrieveData();
        std::string recommendation = analyzer.analyzeData(data);
        std::cout << "Recommendations:\n" << recommendation;
    }
};

int main() {
    DataCollector collector;
    DataAnalyzer analyzer;
    DataStorage storage;
    UserInterface interface;

    while (true) {
        interface.displayMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            interface.inputHealthData(collector, storage);
            break;
        case 2:
            interface.viewRecommendations(analyzer, storage);
            break;
        case 3:
            return 0;
        default:
            std::cout << "Invalid choice. Please choose again.\n";
        }
    }

    return 0;
}
