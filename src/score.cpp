//
// Created by Michał Markuzel on 12/05/2023.
//

#include "score.h"

void score::swap(int i, int j)
{
    int temp = value[j];
    value[j] = value[i];
    value[i] = temp;
}

score::score(std::string file_name) : file_name(file_name){
    file_read.open(file_name);

    assert(file_read);

    std::string x;
    while (file_read) { // equivalent to myfile.good()
        std::getline(file_read, x);
        try {
            value.push_back(stoi(x));
        }
        catch (const std::invalid_argument &e)
        {
            // ignorowanie '\n'
        }

    }
    file_read.close();
}

void score::sort() {
    for (int i = 0; i < value.size() - 1; i++)
        for (int j = 0; j < value.size() - i - 1; j++)
            if (value[j] < value[j + 1])
                swap(j, j + 1);
}

void score::add_new_score(int i){
    value.push_back(i);
}

void score::save_file() {
    file_write.open(file_name);
    if (file_write.is_open())
        for (int i = 0; i < 10; i++)
            file_write << value[i] << std::endl;
    file_write.close();
}

std::vector<int> score::get_score_table(){
    return value;
}