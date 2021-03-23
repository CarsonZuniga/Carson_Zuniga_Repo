#include "excel.h"
#include <ctype.h>
#include <sstream>
#include <algorithm>

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
    std::cout << "Means:" << std::endl;
    std::vector<double> mean = getMean();
    for(int i = 0; i < labels.size(); i++){
        std::cout << mean[i] << " ";
    }
    std::cout << std::endl;
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

std::vector<double> excel::getMean(){
    std::vector<double> result(my_data.size());
    for(int i = 0; i < length; i++){
        for(int j = 0; j < my_data.size(); j++)
            result[j] += my_data[j][i];
    }
    
    for(int x = 0; x < my_data.size(); x++)
            result[x] /= length;

    return result;
}