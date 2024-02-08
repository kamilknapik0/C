#include <iostream>
#include <fstream>
#include <cstring>

class RideReport {
private:
    const char* fileName; 
	char* data; 
    int speedUpCount_;
    int slowDownCount_;
    int leftTurnCount_;
    int rightTurnCount_;

public:
    RideReport(const char* fileName) : fileName(fileName), data(nullptr),
                                       speedUpCount_(0), slowDownCount_(0),
                                       leftTurnCount_(0), rightTurnCount_(0) {}

    ~RideReport() {
        delete[] data; 

    bool readData() {
        std::ifstream file(fileName);

        if (file.is_open()) {
            file.seekg(0, std::ios::end);
            std::streampos fileSize = file.tellg();
            file.seekg(0, std::ios::beg);

            std::size_t numericFileSize = static_cast<std::size_t>(fileSize);

            data = new char[numericFileSize + 1]; 

            file.read(data, fileSize);
            data[numericFileSize] = '\0'; 

            file.close();

            return true;
        }
        else {
            std::cout << "Nie mo¿na otworzyæ pliku." << std::endl;
            return false;
        }
    }

    bool processData() {
        if (data != nullptr) {
            for (int i = 0; data[i] != '\0'; i++) {
                if (data[i] == 'a')
                    speedUpCount_++;
                else if (data[i] == 'd')
                    slowDownCount_++;
                else if (data[i] == 'l')
                    leftTurnCount_++;
                else if (data[i] == 'r')
                    rightTurnCount_++;
            }

            std::cout << "Liczba przyspieszeñ: " << speedUpCount_ << std::endl;
            std::cout << "Liczba zwolnieñ: " << slowDownCount_ << std::endl;
            std::cout << "Liczba skrêtów w lewo: " << leftTurnCount_ << std::endl;
            std::cout << "Liczba skrêtów w prawo: " << rightTurnCount_ << std::endl;

            return true;
        }
        else {
            std::cout << "Brak danych do przetworzenia." << std::endl;
            return false;
        }
    }

    int getSpeedUpCount() {
        return speedUpCount_;
    }

    int getSlowDownCount() {
        return slowDownCount_;
    }

    int getLeftTurnCount() {
        return leftTurnCount_;
    }

    int getRightTurnCount() {
        return rightTurnCount_;
    }

    bool saveCleanedData(const char* fileName) {
        if (data != nullptr) {
            std::ofstream file(fileName);

            if (file.is_open()) {
                for (int i = 0; data[i] != '\0'; i++) {
                    if (data[i] == 'a' || data[i] == 'd' || data[i] == 'l' || data[i] == 'r')
                        file << data[i];
                }

                file.close();

                return true;
            }
            else {
                std::cout << "Nie mo¿na zapisaæ oczyszczonych danych do pliku." << std::endl;
                return false;
            }
        }
        else {
            std::cout << "Brak danych do zapisu." << std::endl;
            return false;
        }
    }

    bool saveAsText(const char* fileName) {
        if (data != nullptr) {
            std::ofstream file(fileName);

            if (file.is_open()) {
                file << "Liczba przyspieszeñ: " << getSpeedUpCount() << std::endl;
                file << "Liczba zwolnieñ: " << getSlowDownCount() << std::endl;
                file << "Liczba skrêtów w lewo: " << getLeftTurnCount() << std::endl;
                file << "Liczba skrêtów w prawo: " << getRightTurnCount() << std::endl;

                file.close();

                return true;
            }
            else {
                std::cout << "Nie mo¿na zapisaæ raportu tekstowego do pliku." << std::endl;
                return false;
            }
        }
        else {
            std::cout << "Brak danych do zapisu." << std::endl;
            return false;
        }
    }

    bool saveAsXML(const char* fileName) {
        if (data != nullptr) {
            std::ofstream file(fileName);

            if (file.is_open()) {
                file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
                file << "<report>" << std::endl;
                file << "    <speedUpCount>" << getSpeedUpCount() << "</speedUpCount>" << std::endl;
                file << "    <slowDownCount>" << getSlowDownCount() << "</slowDownCount>" << std::endl;
                file << "    <leftTurnCount>" << getLeftTurnCount() << "</leftTurnCount>" << std::endl;
                file << "    <rightTurnCount>" << getRightTurnCount() << "</rightTurnCount>" << std::endl;
                file << "</report>" << std::endl;

                file.close();

                return true;
            }
            else {
                std::cout << "Nie mo¿na zapisaæ raportu XML do pliku." << std::endl;
                return false;
            }
        }
        else {
            std::cout << "Brak danych do zapisu." << std::endl;
            return false;
        }
    }
};

	int main() {
    RideReport report("data.txt");

    if (report.readData()) {
        if (report.processData()) {
            std::cout << "\nPrzyspieszenia: " << report.getSpeedUpCount();
            std::cout << "\nHamowania: " << report.getSlowDownCount();
            std::cout << "\nW lewo: " << report.getLeftTurnCount();
            std::cout << "\nW prawo: " << report.getRightTurnCount();

            if (report.saveCleanedData("dane_czyste.txt"))
                std::cout << "\nOczyszczone dane zapisane";
            if (report.saveAsText("raport.txt"))
                std::cout << "\nRaport tekstowy zapisany";
            if (report.saveAsXML("raport.xml"))
                std::cout << "\nPlik XML zapisany";
        }
    }

    return 0;
}

