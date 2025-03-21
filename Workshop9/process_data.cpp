/*
*****************************************************************************
						Workshop 9 - Part 2
Full Name  : Ali Rezk
Student ID#: 105593222
Email      : arezk1@myseneca.ca
Section    : ZBB
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

// Workshop 9 - Multi-Threading, Thread Class
// process_data.cpp
// 2021/1/5 - Jeevan Pant
// 2023/11/17 - Cornel

#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <thread>
#include "process_data.h"
#include <numeric>
namespace sdds
{
	// The following function receives array (pointer) as the first argument, number of array 
	//   elements (size) as second argument, divisor as the third argument, and avg as fourth argument. 
	//   size and divisor are not necessarily same. When size and divisor hold same value, avg will 
	//   hold average of the array elements. When they are different, avg will hold a value called 
	// 	 as average-factor. For part 1, you will be using same value for size and double. Use of 
	//   different values for size and divisor will be useful for multi-threaded implementation in part-2. 
	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		avg = 0;
		for (int i = 0; i < size; i++) {
			avg += arr[i];
		}
		avg /= divisor;
	}

	// The following function receives array (pointer) as the first argument, number of array elements  
	//   (size) as second argument, divisor as the third argument, computed average value of the data items
	//   as fourth argument, and var as fifth argument. Size and divisor are not necessarily same as in the 
	//   case of computeAvgFactor. When size and divisor hold same value, var will get total variance of 
	//   the array elements. When they are different, var will hold a value called as variance factor. 
	//   For part 1, you will be using same value for size and double. Use of different values for size 
	//   and divisor will be useful for multi-threaded implementation in part-2. 
	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		var = 0;
		for (int i = 0; i < size; i++) {
			var += (arr[i] - avg) * (arr[i] - avg);
		}
		var /= divisor;
	}

	// The following constructor of the functor receives name of the data file, opens it in 
	//   binary mode for reading, reads first int data as total_items, allocate memory space 
	//   to hold the data items, and reads the data items into the allocated memory space. 
	//   It prints first five data items and the last three data items as data samples. 
	//   
	ProcessData::ProcessData(const std::string& filename, int n_threads) {
		// TODO: Open the file whose name was received as parameter and read the content
		//         into variables "total_items" and "data". Don't forget to allocate
		//         memory for "data".
		//       The file is binary and has the format described in the specs.
		std::ifstream file(filename, std::ios::binary);

		if (!file) {
			throw "SORRY CAN NOT OPEN THE FILE!";
			
		}
		file.read(reinterpret_cast<char*>(&total_items), sizeof(int));

		data = new int[total_items];

		file.read(reinterpret_cast<char*>(data), total_items * sizeof(int));

		
		std::cout << "Item's count in file '" << filename << "': " << total_items << std::endl;
		std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
			<< data[total_items - 3] << ", " << data[total_items - 2] << ", "
			<< data[total_items - 1] << "]" << std::endl;

		// Following statements initialize the variables added for multi-threaded 
		//   computation
		num_threads = n_threads;
		averages = new double[num_threads] {};
		variances = new double[num_threads] {};
		p_indices = new int[num_threads + 1] {};
		for (int i = 0; i < num_threads; i++)
			p_indices[i] = i * (total_items / num_threads);
		p_indices[num_threads] = total_items;
	}
	ProcessData::~ProcessData() {
		delete[] data;
		delete[] averages;
		delete[] variances;
		delete[] p_indices;
	}

	ProcessData::operator bool() const {
		return total_items > 0 && data;
	}

	int ProcessData::operator()(const std::string& target_file, double& avg, double& var)
	{
		//to hold threads for average computation
		std::vector<std::thread> avgThreads;

		//to hold threads for variance computation
		std::vector<std::thread> varThreads;

		//to store partial averages and variances for each thread
		std::vector<double> partialAvgs(num_threads);
		std::vector<double> partialVars(num_threads);

		//to create threads for average computation
		for (int i = 0; i < num_threads; ++i)
		{
			avgThreads.push_back(std::thread(std::bind(computeAvgFactor,
			data, p_indices[i], p_indices[i + 1], std::ref(partialAvgs[i]))));
		}

		for (auto& thread : avgThreads) 
		{
			thread.join();
		}

		//to create threads for variance computation
		for (int i = 0; i < num_threads; ++i) 
		{
			varThreads.push_back(std::thread(std::bind(computeVarFactor, 
			data, p_indices[i], p_indices[i + 1], avg, std::ref(partialVars[i]))));
		}

		for (auto& thread : varThreads) 
		{
			thread.join();
		}

		//calculate the average of the partial averages and the partial variances
		avg = std::accumulate(partialAvgs.begin(), partialAvgs.end(), 0.0) / num_threads;
		var = std::accumulate(partialVars.begin(), partialVars.end(), 0.0) / num_threads;

		computeAvgFactor(data, total_items, total_items, avg);
		computeVarFactor(data, total_items, total_items, avg, var);

		std::ofstream targetFile(target_file, std::ios::binary);
		if (!targetFile.is_open()) 
		{
			throw "SORRY CAN NOT OPEN THE TARGET FILE FOR WRITING!";
		}

		targetFile.write(reinterpret_cast<const char*>(&total_items), sizeof(int));
		targetFile.write(reinterpret_cast<const char*>(data), total_items * sizeof(int));

		return 0;
	}

}