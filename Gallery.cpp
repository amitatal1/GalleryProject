#include <iostream>
#include <string>
#include "MemoryAccess.h"
#include "AlbumManager.h"
#include <chrono>
#include "DatabaseAccess.h"

int getCommandNumberFromUser()
{
	std::string message("\nPlease enter any command(use number): ");
	std::string numericStr("0123456789");
	std::cin.sync();
	std::cout << message << std::endl;
	std::string input;
	
	std::getline(std::cin, input);
	
	while (std::cin.fail() || std::cin.eof() || input.find_first_not_of(numericStr) != std::string::npos) {

		std::cout << "Please enter a number only!" << std::endl;

		if (input.find_first_not_of(numericStr) == std::string::npos) {
			std::cin.clear();
		}

		std::cout << std::endl << message << std::endl;
		std::getline(std::cin, input);
	}
	
	return std::atoi(input.c_str());
}

int main(void)
{
	// initialization data access
	DatabaseAccess dataAccess;

	// initialize album manager
	AlbumManager albumManager(dataAccess);


	std::string albumName;

	// Get the current time point
	auto currentTimePoint = std::chrono::system_clock::now();

	// Convert the current time point to a time_t
	std::time_t currentTime = std::chrono::system_clock::to_time_t(currentTimePoint);

	// Convert the time_t to a tm structure
	std::tm* timeInfo = std::localtime(&currentTime);

	// Format and print the current time
	char timeString[100];  
	std::strftime(timeString, sizeof(timeString), "%H:%M:%S, %d/%m/%Y", timeInfo);
	std::cout << "Created by Amit Atal\n";
	std::cout << "Current time: " << timeString << std::endl;

	std::cout << "Welcome to Gallery!" << std::endl;
	std::cout << "===================" << std::endl;
	std::cout << "Type " << HELP << " to a list of all supported commands" << std::endl;
	do {
		int commandNumber = getCommandNumberFromUser();
		
		try	{
			albumManager.executeCommand(static_cast<CommandType>(commandNumber));
		} catch (std::exception& e) {	
			std::cout << e.what() << std::endl;
		}
	} 
	while (true);
}


