#include "excel.h"
#include <ctype.h>
#include <sstream>
#include <algorithm>
#include <cmath>

excel::excel(){
    labels = {""};
    my_data= {{}};
    file_name = "";
    length = 0;
}

excel::excel(std::string input_file){
    std::ifstream my_file;
    my_file.open(input_file);
    if(!my_file){
        std::cout << "Could Not Open File." << std::endl;
        return;
    }

    std::cout << "Processing file: " << input_file << std::endl;
    file_name = input_file;
    std::string line;
    while(std::getline(my_file, line)){
        // if a comment, skip
        if(line[0] == ';')
            continue;
        // if first character is a letter, detect as label
        if(isalpha(line[0])){
            std::vector<std::string> input_labels;
            std::stringstream s_stream(line);
            while(s_stream.good()){
                std::string substring;
                std::getline(s_stream, substring, ',');
                input_labels.push_back(substring);
            }
            std::cout << "Setting Labels As: ";
            labels = input_labels;
            for(int i = 0; i < labels.size() - 1; i++){
                std::cout << labels[i] << ", ";
            } 
            std::cout << labels[labels.size() - 1] << std::endl;
            my_data.resize(labels.size());
        }
        else {
            std::vector<std::string> input_vals;
            std::stringstream s_stream(line);
            while(s_stream.good()){
                std::string substring;
                std::getline(s_stream, substring, ',');
                input_vals.push_back(substring);
            }
            for(int i = 0; i < labels.size(); i++){
                my_data[i].push_back(std::stod(input_vals[i]));
            }
        }
        // std::cout << line << std::endl;
    }
    length = my_data[0].size();

    std::cout << "Done processing " << input_file << std::endl;
    std::cout << "Processed " << length * labels.size() << " values from " << length << " lines." << std::endl;
    my_file.close();
}

int excel::getNumLabels(){
    return labels.size();
}

int excel::getDataLength(){
    return length;
}

std::string excel::getFileName(){
    return file_name;
}

void excel::printData(){
    if(length == 0)
        return;
    
    std::cout << "Printing data from " << file_name << std::endl;
    for(int i = 0; i < labels.size(); i++){
        std::cout << labels[i] << " ";
    }
    std::cout << std::endl;

    for(int i = 0; i < length; i++){
        for(int j = 0; j < my_data.size(); j++){
            std::cout << my_data[j][i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Sums:" << std::endl;
    std::vector<double> sum = getSum();
    for(int i = 0; i < labels.size(); i++){
        std::cout << sum[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Means:" << std::endl;
    std::vector<double> mean = getMean();
    for(int i = 0; i < labels.size(); i++){
        std::cout << mean[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "StDevs:" << std::endl;
    std::vector<double> StDev = getStDev();
    for(int i = 0; i < labels.size(); i++){
        std::cout << StDev[i] << " ";
    }
    std::cout << std::endl;

    std::cout << getLinearTrendline("t", "y(t)") << std::endl;

    std::cout << "R: " << getCorrelationCoefficient("t", "y(t)") << std::endl;

}

void excel::sort(){
    sort(0);
}

void excel::sort(std::string label){
    if(length == 0)
        return;
    for(int i = 0; i < labels.size(); i++){
        if(labels[i] == label){
            sort(i);
            return;
        }
    }
    std::cout << "Could Not Find Label: " << label << std::endl;
    std::cout << "Valid Labels: ";
    for(int i = 0; i < labels.size(); i++){
        std::cout << labels[i] << " ";
    }
    std::cout << std::endl;
}

void excel::sort(int index){
    if(length == 0)
        return;
    std::cout << "Now sorting " << file_name << " with respect to " << labels[index] << std::endl;
    for(int i = 0; i < length; i++){
        int min_index = findSmallestInLabel(index, i, length - 1);
        for(int j = 0; j < labels.size(); j++)
            std::swap(my_data[j][i], my_data[j][min_index]);
    }
}

int excel::findSmallestInLabel(int index){
    return findSmallestInLabel(index, 0, length - 1);
}

int excel::findSmallestInLabel(int index, int min_index, int max_index){
    double min = my_data[index][min_index];
    int min_index_result = min_index;
    for(int i = min_index; i <= max_index && i < length; i++){
        double new_value = my_data[index][i];
        if(new_value < min){
            min = new_value;
            min_index_result = i;
        }
    }
    return min_index_result;
}

std::vector<double> excel::getSum(){
    std::vector<double> result(labels.size());
    for(int i = 0; i < length; i++)
        for(int j = 0; j < labels.size(); j++)
            result[j] += my_data[j][i];

    return result;
}

std::vector<double> excel::getMean(){
    std::vector<double> result = getSum();
    
    for(int x = 0; x < my_data.size(); x++)
            result[x] /= length;

    return result;
}

std::vector<double> excel::getStDev(){
    std::vector<double> mean = getMean();
    std::vector<double> sum(labels.size());
    for(int i = 0; i < length; i++){
        for(int j = 0; j < labels.size(); j++){
            sum[j] += (my_data[j][i] - mean[j]) * (my_data[j][i] - mean[j]);
        }
    }
    for(int j = 0; j < labels.size(); j++){
        sum[j] /= length;
        sum[j] = sqrt(sum[j]);
    }
    return sum;
}

std::string excel::getLinearTrendline(std::string x, std::string y){
    if(x == y)
        return x + " = " + y + ". Could Not Find Linear Trendline.";
    int x_index = -1, y_index = -1;
    for(int i = 0; i < labels.size(); i++){
        if(x == labels[i])
            x_index = i;
        if(y == labels[i])
            y_index = i;
    }
    if(x_index != -1 && y_index != -1)
        return getLinearTrendline(x_index, y_index);
    else if(x_index == -1)
        return "Could Not Find Label: " + x;
    else
        return "Could Not Find Label: " + y;
}

std::string excel::getLinearTrendline(int x, int y){
    std::vector<double> mean = getMean();
    double mean_x = mean[x], mean_y = mean[y];
    double numerator = 0;
    double denominator = 0;
    for(int i = 0; i < length; i++){
        numerator += (my_data[x][i] - mean_x) * (my_data[y][i] - mean_y);
        denominator += (my_data[x][i] - mean_x) * (my_data[x][i] - mean_x);
    }
    double slope = numerator / denominator;
    double y_intercept = mean_y - slope*mean_x;
    return labels[y] + " = " + std::to_string(slope) + " * " + labels[x] + " + " + std::to_string(y_intercept);
}

double excel::getCorrelationCoefficient(std::string x, std::string y){
    if(x == y){
        std::cout << x << " = " << y << ". Could Not Find Correlation Coefficient." << std::endl;
        return 0;
    }
    
    int x_index = -1, y_index = -1;
    for(int i = 0; i < labels.size(); i++){
        if(x == labels[i])
            x_index = i;
        if(y == labels[i])
            y_index = i;
    }
    if(x_index != -1 && y_index != -1)
        return getCorrelationCoefficient(x_index, y_index);
    else if(x_index == -1){
        std::cout << "Could Not Find Label: " << x << std::endl;
        return 0;
    }
    else{
        std::cout << "Could Not Find Label: " << y << std::endl;
        return 0;
    }
}

double excel::getCorrelationCoefficient(int x, int y){
    std::vector<double> mean = getMean();
    double mean_x = mean[x], mean_y = mean[y];
    double numerator = 0;
    double denominator_x = 0;
    double denominator_y = 0;
    for(int i = 0; i < length; i++){
        numerator += (my_data[x][i] - mean_x) * (my_data[y][i] - mean_y);
        denominator_x += (my_data[x][i] - mean_x) * (my_data[x][i] - mean_x);
        denominator_y += (my_data[y][i] - mean_y) * (my_data[y][i] - mean_y);
        //(my_data[x][i] - mean_x) * (my_data[x][i] - mean_x)
    }
    return numerator / sqrt(denominator_x * denominator_y);
}