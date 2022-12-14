#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int coreSeatID = 10000;

class Seat {
public:
    std::string number;
    std::string price;
    std::string name;
    int id;
    bool isBooked;
    Seat(std::string number, std::string price, int id) {
        this->number = number;
        this->price = price;
        this->id = id;
        this->name = "blank";
        this->isBooked = false;

    }

    void bookSeat(std::string iname){
        this->name = iname;
        this->isBooked = true;
        std::cout <<  "Your seat was booked with id of " << this->id << std::endl;
        std::cout <<  "Your seat was booked with name of " << this->name << std::endl;
    }

    void unbookSeat(){
        std::cout <<  "Confirmed " << this->price << " refund for " << this->name << std::endl;
        this->name = "blank";
        this->isBooked = false;
    }

};

class Flight {
public:
    std::string date;
    std::string flightNo;
    std::vector<Seat> seats;
    Flight(std::string date, std::string flightNo, std::vector<Seat> seats) {
        this->date = date;
        this->flightNo = flightNo;
        this->seats = seats;
    };


    void listAvailableSeats(){
        std::vector<Seat> availableSeats;
        for (int i = 0; i < seats.size(); ++i) {
            if(!seats[i].isBooked){
                availableSeats.push_back(seats[i]);
            }
        }
        for (int i = 0; i < availableSeats.size(); ++i) {
            std::cout << availableSeats[i].number << " " << availableSeats[i].price << std::endl;
        }
    }

    Seat& findSeatByNo(std::string number){
        for (int i = 0; i < seats.size(); ++i) {
            if (seats[i].number == number){
                return seats[i];
            }
        }
    }

    Seat& findSeatById(int ID){
        for (int i = 0; i < seats.size(); ++i) {
            if (seats[i].id == ID){
                return seats[i];
            }
        }
    }

    void findSeatByIdAndInfo(int ID){
        for (int i = 0; i < seats.size(); ++i) {
            if (seats[i].id == ID){
                std::cout << "Flight " << this->flightNo << " " << this->date << " seat " << seats[i].number << " price " << seats[i].price << " " << seats[i].name << std::endl;
            }
        }
    }

};

void tokenize(std::string const &str, const char* delim, std::vector<std::string> &out)
{
    char *token = strtok(const_cast<char*>(str.c_str()), delim);
    while (token != nullptr)
    {
        out.push_back(std::string(token));
        token = strtok(nullptr, delim);
    }
}

std::vector<Seat> seatDivider(std::string seats, std::string rows, std::string price){
    std::vector<std::string> seatNumbersStartAndEnd;
    std::vector<std::string> seatNumbersColsString;
    std::vector<std::string> seatNumbers;
    std::vector<int> seatNumbersStartAndEndInt;
    std::vector<int> seatNumbersCols;
    std::vector<Seat> seatsFinal;


    tokenize(seats, "-", seatNumbersStartAndEnd);

    for (int i = 0; i < seatNumbersStartAndEnd.capacity(); i++) { //mb change to size
        seatNumbersStartAndEndInt.push_back(std::stoi(seatNumbersStartAndEnd[i]));
    }

    for (int i = seatNumbersStartAndEndInt[0]; i <= seatNumbersStartAndEndInt[1]; i++) {
        seatNumbersCols.push_back(i);
    }
    int rowsInt = std::stoi(rows);

    for (int i = 0; i < seatNumbersCols.size(); i++) {
        seatNumbersColsString.push_back(std::to_string(seatNumbersCols[i]));
    }

    std::vector<char> Alphabet = { 'A','B','C','D','E','F',
                        'G','H','I','J','K','L','M','N','O','P',
                        'Q','R','S','T','U','V','W','X','Y','Z'};


    for (int i = 0; i < seatNumbersColsString.size(); i++) {
        for (int j = 0; j < rowsInt; j++) {
            seatNumbers.push_back(seatNumbersColsString[i] + Alphabet[j]);
        }
    }
    for (int i = 0; i < seatNumbers.size(); i++) {
        coreSeatID++;
        seatsFinal.push_back(Seat(seatNumbers[i], price, coreSeatID));
    }

    return seatsFinal;
}



void UI(std::vector<Flight>& Flights) {
    while(true){
        std::string input;
        std::cout << std::endl;
        std::vector<std::string> inputVec;
        std::getline(std::cin, input);
        tokenize(input, " ", inputVec);
        int command = std::stoi(inputVec[0]);// 1-check 2-book 3-return 4-view by id 5-view by user

        if(command == 1){
            std::string date = inputVec[1];
            std::string flightNo = inputVec[2];
            std::vector<Seat> placeholder;
            // Flight FlightNeeded; = new Flight("placeholder", "placeholder", placeholder);
            for (int i = 0; i < Flights.size(); ++i) {
                if(Flights[i].flightNo == flightNo && Flights[i].date == date){
                    Flights[i].listAvailableSeats();
                }
            }

        }
        if (command == 2){
            std::string date = inputVec[1];
            std::string flightNo = inputVec[2];
            std::string seatNo = inputVec[3];
            std::string username = inputVec[4];
            for (int i = 0; i < Flights.size(); ++i) {
                if(Flights[i].flightNo == flightNo && Flights[i].date == date){
                    Seat& test = Flights[i].findSeatByNo(seatNo);
                    test.bookSeat(username);
                }
            }
        }
        if (command == 3){
            int id = std::stoi(inputVec[1]);
            for (int j = 0; j < Flights.size(); ++j) {
                for (int i = 0; i < Flights[j].seats.size(); ++i) {
                    if(Flights[j].seats[i].id == id){
                        Flights[j].findSeatById(id).unbookSeat();
                    }
                }
            }
        }

        if (command == 4){
            int id = std::stoi(inputVec[1]);
            for (int j = 0; j < Flights.size(); ++j) {
                for (int i = 0; i < Flights[j].seats.size(); ++i) {
                    if(Flights[j].seats[i].id == id){
                        Flights[j].findSeatByIdAndInfo(id);
                    }
                }
            }
        }

    }
}


int main() {
    std::fstream newFile;
    std::string filepath = "data.txt";
    newFile.open(filepath, std::ios::in);

    // std::vector<std::string> out;
    std::vector<Flight> Flights;
    if (newFile.is_open()){
        std::string curr;

        while(getline(newFile, curr)){
            std::vector<std::string> out;
            std::cout << curr << std::endl;
            auto first_token = curr.substr(0, curr.find(' '));
            tokenize(curr, " ", out);
            //plane add
            std::vector<Seat> seatsOne = seatDivider(out[3], out[2], out[4]);
            std::vector<Seat> seatsTwo = seatDivider(out[5], out[2], out[6]);
            //std::vector<Seat> seatsConcatted;

            seatsOne.insert( seatsOne.end(), seatsTwo.begin(), seatsTwo.end());

            Flight* Flight1 = new Flight(out[0], out[1], seatsOne);
            Flights.push_back(*Flight1);
        }
        newFile.close();
    }
    std::cout  << "Hello" << std::endl;
    UI(Flights);

    return 0;
}
