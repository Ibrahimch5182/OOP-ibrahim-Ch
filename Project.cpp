#include<iostream>
#include <string>

using namespace std;

class Entity{
    public:
    static int number;

    int autoid;

    Entity() : autoid(number++) {}

    virtual void displayDetails() const = 0;

    friend ostream& operator <<(ostream& os, const Entity& entity){
        entity.displayDetails();
        return os;
    }


};

int Entity :: number = 1;

class Bus : public Entity{
public:
    string BusNumber;
    bool isReserved;

    Bus(string bus_number) : BusNumber(bus_number), isReserved(false) {}

    void displayDetails()  const {
        cout << "Bus ID: " << autoid << "  Bus Number: " << BusNumber;
        if (isReserved){
            cout<< " (Reserved) " ;
        }
        cout << endl;

    }

    bool isAvailable() const {
        return !isReserved;
    }
};

class Reservation : public Entity{
public:
    string CustomerName;
    int seatNumber;

    Reservation(string CustomerName, int seatNum) : CustomerName(CustomerName), seatNumber(seatNum) {}

    void displayDetails() const{
        cout << "Reservation ID: " << autoid << "  Customer : " << CustomerName << " seatNumber : " << seatNumber << endl;

    }

    bool isValidSeat() const{
        return seatNumber > 0;
    }

};

class BusReservationSystem{
public:
    Entity* entities[10];

    int numEntities;

    BusReservationSystem() : numEntities(0) {}

    void addEntity(Entity* entity) {
        if (numEntities < 10){
            entities[numEntities++] = entity;
            cout << "Entity added successfully" << endl;

        }
        else {
            throw "cannot add more entities. maximimum limit reached";
        }
    }

    void displayAllEntities() const{
        if(numEntities == 0){
            cout << "no entities to display" << endl;
        }
        else{
            for (int i = 0; i < numEntities; ++i) {
                cout << *entities[i] << endl; //operator overloading
            }
        }
    }

    Entity* searchEntitybyID(int id) const{
        for (int i = 0; i < numEntities; ++i) {
            if (entities[i]->autoid == id){
                return entities[i];
            }
        }
        return nullptr;
    }
};

int main(){
    try{
        BusReservationSystem reservationSystem;

        Bus bus1("A123");
        Bus bus2("B456");
//        Bus bus3("B456");
//        Bus bus4("B456");
//        Bus bus5("B456");
//        Bus bus6("B456");
//        Bus bus7("B456");
//        Bus bus8("B456");
//        Bus bus9("B456");
//        Bus bus10("B456");

        Reservation reservation("IBRAHIM CH", 1);

        reservationSystem.addEntity(&bus1);
        reservationSystem.addEntity(&bus2);
//        reservationSystem.addEntity(&bus3);
//        reservationSystem.addEntity(&bus4);
//        reservationSystem.addEntity(&bus5);
//        reservationSystem.addEntity(&bus6);
//        reservationSystem.addEntity(&bus7);
//        reservationSystem.addEntity(&bus8);
//        reservationSystem.addEntity(&bus9);
//        reservationSystem.addEntity(&bus10);
        reservationSystem.addEntity(&reservation);

        reservationSystem.displayAllEntities();

        // check if bus is available for reservation.
        if(bus1.isAvailable()){
            cout << "Bus: " <<bus1.autoid << " is available for reservation" << endl;
        }
        else{
            cout << "Bus: " <<bus1.autoid << " is not available for reservation" << endl;
        }

        // check if seat is valid
        if (reservation.isValidSeat()){
            cout << "seat number : " << reservation.seatNumber << " is valid" <<endl;
        }
        else {
            cout << "seat number : " << reservation.seatNumber << " is not valid" <<endl;
        }

        // using search id function -- searching entity by ID
        int searchID = 2;
        Entity* foundEntity = reservationSystem.searchEntitybyID(searchID);

        if(foundEntity) {
            cout<< "Found Entity by ID: " <<searchID <<" : "<<endl;
            cout<< *foundEntity;
        } else{cout<< "Entity by ID: " <<searchID <<" not found "<<endl; }




    }
    catch (const char* msg){
        cout << "Exception : " << msg << endl;
    }
    return 0;

}
