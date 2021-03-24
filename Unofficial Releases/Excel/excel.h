#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

class excel{
    private:
    std::vector<std::string> labels;
    std::vector<std::vector<double>> my_data;
    std::string file_name;
    int length;

    public:
    excel();
    excel(std::string input_file);
    int getNumLabels();
    int getDataLength();
    std::string getFileName();
    void printData();
    void sort();
    void sort(std::string label);
    void sort(int index);
    int findSmallestInLabel(int index);
    int findSmallestInLabel(int index, int min_index, int max_index); // returns index of smallest value of given label, between given indices, inclusive
    std::vector<double> getSum();
    std::vector<double> getMean();
    std::vector<double> getStDev();
    std::string getLinearTrendline(std::string x, std::string y);
    std::string getLinearTrendline(int x, int y);   // returns line of best fit for y(x)
    double getCorrelationCoefficient(std::string x, std::string y);
    double getCorrelationCoefficient(int x, int y); // returns Correlation Coefficient, R
};