#include <iostream>
#include <string>
using namespace std;

class Vehicle
{
protected:
    int vehicleID;
    string manufacturer;
    string model;
    int year;
    static int totalVehicles;

public:
    Vehicle()
    {
        totalVehicles++;
    }

    virtual ~Vehicle()
    {
        totalVehicles--;
    }

    virtual void SetData()
    {
        cout << "Enter Vehicle ID: ";
        cin >> vehicleID;
        cin.ignore();

        cout << "Enter Manufacturer: ";
        getline(cin, manufacturer);

        cout << "Enter Model: ";
        getline(cin, model);

        cout << "Enter Year: ";
        cin >> year;
    }

    virtual void GetData()
    {
        cout << "Vehicle ID: " << vehicleID << endl;
        cout << "Manufacturer: " << manufacturer << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
    }

    int Get_Vehicle_ID()
    {
        return vehicleID;
    }

    static int Get_Total_Vehicles()
    {
        return totalVehicles;
    }
};

int Vehicle::totalVehicles = 0;

/*==================== Car ====================*/
class Car : virtual public Vehicle
{
protected:
    string fuelType;

public:
    void SetData()
    {
        Vehicle::SetData();
        cin.ignore();
        cout << "Enter Fuel Type: ";
        getline(cin, fuelType);
    }

    void GetData()
    {
        Vehicle::GetData();
        cout << "Fuel Type: " << fuelType << endl;
    }
};

/*==================== Electric Car ====================*/
class ElectricCar : public Car
{
protected:
    int batteryCapacity;

public:
    void SetData()
    {
        Car::SetData();
        cout << "Enter Battery Capacity (AH): ";
        cin >> batteryCapacity;
    }

    void GetData()
    {
        Car::GetData();
        cout << "Battery Capacity: " << batteryCapacity << " AH" << endl;
    }
};

/*==================== Aircraft ====================*/
class Aircraft : virtual public Vehicle
{
protected:
    int flightRange;

public:
    void SetData()
    {
        Vehicle::SetData();
        cout << "Enter Flight Range (KM): ";
        cin >> flightRange;
    }

    void GetData()
    {
        Vehicle::GetData();
        cout << "Flight Range: " << flightRange << " KM" << endl;
    }
};

/*==================== Flying Car ====================*/
class FlyingCar : public Car, public Aircraft
{
public:
    void SetData()
    {
        Car::SetData();
        cout << "Enter Flight Range (KM): ";
        cin >> flightRange;
    }

    void GetData()
    {
        Car::GetData();
        cout << "Flight Range: " << flightRange << " KM" << endl;
    }
};

/*==================== Sports Car ====================*/
class SportsCar : public ElectricCar
{
private:
    int topSpeed;

public:
    void SetData()
    {
        ElectricCar::SetData();
        cout << "Enter Top Speed (km/h): ";
        cin >> topSpeed;
    }

    void GetData()
    {
        ElectricCar::GetData();
        cout << "Top Speed: " << topSpeed << " km/h" << endl;
    }
};

/*==================== Sedan ====================*/
class Sedan : public Car
{
public:
    void SetData()
    {
        Car::SetData();
    }

    void GetData()
    {
        Car::GetData();
    }
};

/*==================== SUV ====================*/
class SUV : public Car
{
public:
    void SetData()
    {
        Car::SetData();
    }

    void GetData()
    {
        Car::GetData();
    }
};

/*==================== Vehicle Registry ====================*/
class VehicleRegistry
{
private:
    Vehicle *v1[100];
    int count;

public:
    VehicleRegistry()
    {
        count = 0;
    }

    ~VehicleRegistry()
    {
        for (int i = 0; i < count; i++)
        {
            delete v1[i];
        }
    }

    void Add_Vehicle()
    {
        if (count >= 100)
        {
            cout << "Registry is full." << endl;
            return;
        }

        int choice;
        cout << "Select Vehicle Type to Add:" << endl;
        cout << "1. Car" << endl;
        cout << "2. Electric Car" << endl;
        cout << "3. Aircraft" << endl;
        cout << "4. Flying Car" << endl;
        cout << "5. Sports Car" << endl;
        cout << "6. Sedan" << endl;
        cout << "7. SUV" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            v1[count] = new Car;
            break;
        case 2:
            v1[count] = new ElectricCar;
            break;
        case 3:
            v1[count] = new Aircraft;
            break;
        case 4:
            v1[count] = new FlyingCar;
            break;
        case 5:
            v1[count] = new SportsCar;
            break;
        case 6:
            v1[count] = new Sedan;
            break;
        case 7:
            v1[count] = new SUV;
            break;
        default:
            cout << "Invalid Choice." << endl;
            return;
        }

        v1[count]->SetData();
        count++;
        cout << "Vehicle added successfully." << endl;
    }

    void Display()
    {
        if (count == 0)
        {
            cout << "No vehicles in the registry." << endl;
            return;
        }

        for (int i = 0; i < count; i++)
        {
            cout << "Vehicle #" << i + 1 << endl;
            v1[i]->GetData();
        }
    }

    void Searching_Vehicles()
    {
        if (count == 0)
        {
            cout << "No vehicles in the registry." << endl;
            return;
        }

        int vehno;
        cout << "Enter Vehicle ID to search: ";
        cin >> vehno;

        for (int i = 0; i < count; i++)
        {
            if (v1[i]->Get_Vehicle_ID() == vehno)
            {
                v1[i]->GetData();
                return;
            }
        }

        cout << "Vehicle not found." << endl;
    }
};

/*==================== MAIN ====================*/
int main()
{
    VehicleRegistry vhre;
    int vh_choice;

    do
    {
        cout << "========= VEHICLE REGISTRY SYSTEM =========" << endl;
        cout << "1. Add Vehicle" << endl;
        cout << "2. View All Vehicles" << endl;
        cout << "3. Search Vehicle by ID" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> vh_choice;

        switch (vh_choice)
        {
        case 1:
            vhre.Add_Vehicle();
            break;
        case 2:
            vhre.Display();
            break;
        case 3:
            vhre.Searching_Vehicles();
            break;
        case 4:
            cout << "Exiting Vehicle Registry System..." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (vh_choice != 4);

    cout << "Total Vehicles: " << Vehicle::Get_Total_Vehicles() << endl;
}