#include <iostream>
#include <fstream> // For file handling
#include <vector>
#include <string>

class Plant {
private:
    std::string name;
    std::string species;
    double price;
    std::string description;
    std::string diseases;

public:
    Plant(std::string name, std::string species, double price, std::string description, std::string diseases)
        : name(name), species(species), price(price), description(description), diseases(diseases) {}

    std::string getName() const { return name; }
    std::string getSpecies() const { return species; }
    double getPrice() const { return price; }
    std::string getDescription() const { return description; }
    std::string getDiseases() const { return diseases; }

    // Function to cure diseases
    void cureDiseases() {
        diseases = "No diseases";
    }

    // Function to write plant information to a file
    void writeToFile(std::ofstream& outFile) const {
        outFile << name << ',' << species << ',' << price << ',' << description << ',' << diseases << '\n';
    }
};

class PlantNursery {
private:
    std::vector<Plant> plants;

public:
    void addPlant(const Plant& plant) {
        plants.push_back(plant);
    }

    void displayPlants() const {
        std::cout << "Available plants:\n";
        for (size_t i = 0; i < plants.size(); ++i) {
            std::cout << i + 1 << ". " << plants[i].getName() << "  ₹" << plants[i].getPrice() << std::endl;
        }
    }

    void buyPlant(int index, int quantity) {
        if (index >= 1 && index <= plants.size()) {
            double totalCost = plants[index - 1].getPrice() * quantity;
            std::cout << "You bought " << quantity << " " << plants[index - 1].getName() << "(s) for ₹" << totalCost << std::endl;

            // Prompt for buyer details and store in a file
            std::ofstream buyerFile("buyer_details.txt", std::ios_base::app);
            if (buyerFile.is_open()) {
                std::string name, address;
                std::cout << "Enter your name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter your address: ";
                std::getline(std::cin, address);
                buyerFile << "Plant Bought: " << plants[index - 1].getName() << "  Quantity: " << quantity << "  Total Cost: ₹" << totalCost
                          << "  Buyer Name: " << name << "  Address: " << address << std::endl;
                buyerFile.close();
                std::cout << "Buyer details saved to file: buyer_details.txt" << std::endl;
            } else {
                std::cout << "Unable to open file: buyer_details.txt" << std::endl;
            }
        } else {
            std::cout << "Invalid plant index!\n";
        }
    }

    void displayPlantInfo(int index) const {
        if (index >= 1 && index <= plants.size()) {
            std::cout << "Plant Information:\n";
            std::cout << "Name: " << plants[index - 1].getName() << std::endl;
            std::cout << "Species: " << plants[index - 1].getSpecies() << std::endl;
            std::cout << "Description: " << plants[index - 1].getDescription() << std::endl;
            std::cout << "Diseases: " << plants[index - 1].getDiseases() << std::endl;
        } else {
            std::cout << "Invalid plant index!\n";
        }
    }

    // Function to save plant information to a file
    void saveToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const auto& plant : plants) {
                plant.writeToFile(outFile);
            }
            outFile.close();
            std::cout << "Plant information saved to file: " << filename << std::endl;
        } else {
            std::cout << "Unable to open file: " << filename << std::endl;
        }
    }
};

int main() {
    PlantNursery nursery;
    
    // Adding sample plants to the nursery
    nursery.addPlant(Plant("Rose", "Rosa", 150.99, "Beautiful flowering plant. Cure Diseases: Spray fungicide once a week.", "Powdery mildew, Black spot"));
    nursery.addPlant(Plant("Fern", "Pteridophyta", 100.99, "Leafy green plant. Cure Diseases: Keep soil moist.", "Leaf blight, Root rot"));
    nursery.addPlant(Plant("Rhododendron", "Ericaceae", 1000, "Woody plant in hills. Cure Diseases: Apply neem oil every month.", "Petal blight, Bud blast"));

    // Save plant information to a file
    nursery.saveToFile("plants.txt");

    int choice;
    do {
        std::cout << "\nPlant Nursery Information System\n";
        std::cout << "1. Display available plants\n";
        std::cout << "2. Buy a plant\n";
        std::cout << "3. Display plant information\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                nursery.displayPlants();
                break;
            case 2: {
                int index, quantity;
                std::cout << "Enter the index of the plant you want to buy: ";
                std::cin >> index;
                std::cout << "Enter the quantity: ";
                std::cin >> quantity;
                nursery.buyPlant(index, quantity);
                break;
            }
            case 3: {
                int index;
                std::cout << "Enter the index of the plant you want to see information about: ";
                std::cin >> index;
                nursery.displayPlantInfo(index);
                break;
            }
            case 4:
                std::cout << "Exiting program...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}