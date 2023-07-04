#include <iostream>
#include <string>
using namespace std;

const int MAX_FLIGHTS = 10;
const int MAX_PASSENGERS = 100;

struct Passenger {
    string name;
    string flight;
};

struct Flight {
    string flightNumber;
    string destination;
    int availableSeats;
    Passenger passengers[MAX_PASSENGERS];
};

Flight flights[MAX_FLIGHTS];
int flightCount = 0;

void addFlight(const string& flightNumber, const string& destination, int availableSeats) {
    Flight flight;
    flight.flightNumber = flightNumber;
    flight.destination = destination;
    flight.availableSeats = availableSeats;
    flights[flightCount++] = flight;
}

void displayFlights() {
    cout << "Available Flights:\n";
    for (int i = 0; i < flightCount; i++) {
        cout << i + 1 << ". " << flights[i].flightNumber << " - " << flights[i].destination << endl;
    }
    cout << endl;
}

int findFlightIndex(const string& flightNumber) {
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].flightNumber == flightNumber) {
            return i;
        }
    }
    return -1;
}

void bookTicket() {
    string flightNumber;
    int flightIndex;
    string passengerName;

    cout << "Enter the flight number you want to book: ";
    cin >> flightNumber;
    flightIndex = findFlightIndex(flightNumber);

    if (flightIndex == -1) {
        cout << "Flight not found!" << endl;
        return;
    }

    Flight& flight = flights[flightIndex];

    if (flight.availableSeats <= 0) {
        cout << "No available seats for this flight!" << endl;
        return;
    }

    cout << "Enter passenger name: ";
    cin.ignore();
    getline(cin, passengerName);

    Passenger passenger;
    passenger.name = passengerName;
    passenger.flight = flightNumber;

    flight.passengers[flight.availableSeats - 1] = passenger;
    flight.availableSeats--;

    cout << "Ticket booked successfully!" << endl;
}

void displayPassengers() {
    string flightNumber;
    int flightIndex;

    cout << "Enter the flight number to display passengers: ";
    cin >> flightNumber;
    flightIndex = findFlightIndex(flightNumber);

    if (flightIndex == -1) {
        cout << "Flight not found!" << endl;
        return;
    }

    const Flight& flight = flights[flightIndex];

    cout << "Passengers for Flight " << flight.flightNumber << " - " << flight.destination << ":\n";
    for (int i = 0; i < flight.availableSeats; i++) {
        cout << i + 1 << ". " << flight.passengers[i].name << endl;
    }
    cout << endl;
}

int main() {
    addFlight("F1001", "New York", 5);
    addFlight("F1002", "Los Angeles", 3);
    addFlight("F1003", "Chicago", 7);

    int choice;

    while (1) {
        cout << "----- Airlines Reservation System -----" << endl;
        cout << "1. Display Available Flights" << endl;
        cout << "2. Book Ticket" << endl;
        cout << "3. Display Passengers of a Flight" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayFlights();
                break;
            case 2:
                bookTicket();
                cout << endl;
                break;
            case 3:
                displayPassengers();
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
                cout << endl;
        }
    }

    return 0;
}
