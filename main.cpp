#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Seat {
public:
    std::string number;
    std::string price;
    std::string name;
    int id;
};

class Flight {
public:
    std::string date;
    std::string flightNo;
    std::vector<Seat> seats;
};

void seatsToNormal(Flight Plane){
    //

}

void tokenize(std::string const &str, const char* delim, std::vector<std::string> &out)
{
    char *token = strtok(const_cast<char*>(str.c_str()), delim);
    while (token != nullptr)
    {
        out.push_back(std::string(token));
        token = strtok(nullptr, delim);
    }
}

int main() {
    std::fstream newFile;
    std::string filepath = "data.txt";
    newFile.open(filepath, std::ios::in);
    std::vector<std::string> out;
    if (newFile.is_open()){
        std::string curr;
        while(getline(newFile, curr)){
            std::cout << curr << std::endl;
            auto first_token = curr.substr(0, curr.find(' '));
            tokenize(curr, " ", out);
        }
        newFile.close();
    }

    return 0;
}
