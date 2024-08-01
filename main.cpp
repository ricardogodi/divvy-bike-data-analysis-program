/* program_4.cpp
 Divvy Bike Data Analysis program.
 Author: Ricardo Gonzalez
 Date: 11/3/2021
 Class: CS 141, Fall 2021, UIC
 Menu Option 5 Extra Credit URL: https://www.google.com/maps/@41.91992,-87.6954165,44m/data=!3m1!1e3
 Coordinates for Home I would like to live in: 41.91996220071493, -87.69551876444997
 */

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <cctype>     // access to tolower() or toupper() function
#include <vector>     // For vectors
#include <string>     // String operations
#include <algorithm>  // use of vector algorithms
#include <cmath>      // For math functions
#include <iomanip>    // For setw()

using namespace std;

class Ride {
    
public:
    string getRideID() {return rideID;}
    string getRideType() {return rideType;};
    string getDateAndTimeStart() { return dateAndTimeStart;}
    string getDateAndTimeEnd() { return dateAndTimeEnd;}
    string getStationNameStart() { return stationNameStart;}
    string getStationNameEnd() { return stationNameEnd; }
    string getLatitudeStart() {return latitudeStart;}
    string getLongitudeStart() {return longitudeStart;}
    string getLatitudeEnd() {return latitudeEnd;}
    string getLongitudeEnd() { return longitudeEnd;}
    string getMemberType() {return memberOrCasual;}
    
    void setRideID(string rideID) {this->rideID = rideID;}
    void setRideType(string rideType) {this-> rideType = rideType;};
    void setDateAndTimeStart(string dateAndTimeStart) { this-> dateAndTimeStart = dateAndTimeStart;}
    void setDateAndTimeEnd(string dateAndTimeEnd) { this-> dateAndTimeEnd = dateAndTimeEnd;}
    void setStationNameStart(string stationNameStart) { this-> stationNameStart = stationNameStart;}
    void setStationNameEnd(string stationNameEnd) { this-> stationNameEnd = stationNameEnd; }
    void setLatitudeStart(string latitudeStart) {this-> latitudeStart = latitudeStart;}
    void setLongitudeStart(string longitudeStart) {this-> longitudeStart = longitudeStart;}
    void setLatitudeEnd(string latitudeEnd) {this-> latitudeEnd = latitudeEnd;}
    void setLongitudeEnd(string longitudeEnd) { this-> longitudeEnd = longitudeEnd;}
    void setMemberOrCasual(string memberOrCasual) {this-> memberOrCasual = memberOrCasual;}
    
    bool isClean() {        // Returns false if there is a sigle empty data field
        
        if (rideID == "" || rideType == "" || dateAndTimeStart == "" || rideID == "" || stationNameStart == "" ||
            stationNameEnd == "" || latitudeStart == "" || longitudeStart == "" || latitudeEnd == "" || longitudeEnd == "" ||
            memberOrCasual == "") {
            return false;
        } else {
            return true;
        } 
    }
    
private:
    string rideID;
    string rideType;
    string dateAndTimeStart;
    string dateAndTimeEnd;
    string stationNameStart;
    string stationNameEnd;
    string latitudeStart;
    string longitudeStart;
    string latitudeEnd;
    string longitudeEnd;
    string memberOrCasual;
};


void readData(vector <string> & myVector, int option) {
    
    ifstream inStream;
    
    // Read data file depending on the chosen option
    if (option == 1) {
        inStream.open("divvyridesampledata.csv");
        assert( inStream.fail() == false );
    }
    
    if (option == 2) {
        inStream.open("weekdayweekend.csv");
        assert( inStream.fail() == false );
    }
    
    if (option == 3) {
        inStream.open("all_divvy_rides_september.csv");
        assert( inStream.fail() == false );
    }
    
    myVector.clear();
    
    string nextLine;
    while (getline(inStream,nextLine)) {
       
        int size = nextLine.length();

        if (nextLine.at(size - 1) == '\r') {
            nextLine.pop_back();
        }
        myVector.push_back( nextLine);
    }
    inStream.close();
}

// Utility functions getting distant between two map points
// Attribution: https://www.geeksforgeeks.org/program-distance-two-points-earth/
// converting degrees to radians
long double toRadians(const long double degree)
{
    // cmath library in C++
    // defines the constant
    // M_PI as the value of
    // pi accurate to 1e-30
    long double one_deg = (3.14159265358979323846) / 180;
    return (one_deg * degree);
}

long double distance(long double lat1, long double long1,
                     long double lat2, long double long2)
{
    // Convert the latitudes
    // and longitudes
    // from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);
    
    // Haversine Formula
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;
    
    long double ans = pow(sin(dlat / 2), 2) +
    cos(lat1) * cos(lat2) *
    pow(sin(dlong / 2), 2);
    
    ans = 2 * asin(sqrt(ans));
    
    // Radius of Earth in
    // Kilometers, R = 6371
    // Use R = 3956 for miles
    long double R = 3956;
    
    // Calculate the result
    ans = ans * R;
    
    return ans;
}

// Fill each data field of every Ride Object
void fillRideData(Ride &theRide, string data, int index){
    
    switch (index) {
        case 0:
            theRide.setRideID(data);
            break;
        case 1:
            theRide.setRideType(data);
            break;
        case 2:
            theRide.setDateAndTimeStart(data);
            break;
        case 3:
            theRide.setDateAndTimeEnd(data);
            break;
        case 4:
            theRide.setStationNameStart(data);
            break;
        case 5:
            theRide.setStationNameEnd(data);
            break;
        case 6:
            theRide.setLatitudeStart(data);
            break;
        case 7:
            theRide.setLongitudeStart(data);
            break;
        case 8:
            theRide.setLatitudeEnd(data);
            break;
        case 9:
            theRide.setLongitudeEnd(data);
            break;
        case 10:
            theRide.setMemberOrCasual(data);
            break;
            
        default:
            break;
    }
}

// Create vector of Ride Objects by extracting the data from the vector of strings
vector<Ride> createVectorOfRideObj(const vector<string> &vectorOfRideStrings){
    
    vector<Ride> vectorOfRideObjects;
    
    int const numberOfDataFields = 11;
    long const vectorSize = vectorOfRideStrings.size();
    
    int startOfNextStringIndex;
    int nextComaIndex;
    int nextLineLength;
    int nextDataFieldLength;
    string nextDataField;
    
    // This loops traverses the vector of strings containing each ride in each element
    for (int i = 1; i < vectorSize; i++) {   // We know the first string is not useful data so we start from i = 1
        startOfNextStringIndex = 0;
        nextComaIndex = 0;
        Ride nextRide;
        
        // This loop extracts the eleven different data fields, taking the comma as the character that separates them
        for (int j = 0; j < numberOfDataFields; j++) {
            
            nextComaIndex = vectorOfRideStrings.at(i).find(',',startOfNextStringIndex);

            if (nextComaIndex > 0) {    // If a coma was found
                nextDataFieldLength = nextComaIndex - startOfNextStringIndex; // Number of characters we are extracting
                nextDataField = vectorOfRideStrings.at(i).substr(startOfNextStringIndex, nextDataFieldLength);
                startOfNextStringIndex = nextComaIndex + 1; // Update starting point from which we will start searching for the next coma
            } else {                    // If a coma was not found
                nextLineLength = vectorOfRideStrings.at(i).length();
                nextDataFieldLength = nextLineLength - startOfNextStringIndex;  // Number of characters we are extracting in the last iteration
                nextDataField = vectorOfRideStrings.at(i).substr(startOfNextStringIndex, nextDataFieldLength);
            }
            fillRideData(nextRide,nextDataField,j); // Fill up the nextRide object in each inner loop iteration
        }
        vectorOfRideObjects.push_back(nextRide);    // Add nextRide to the vector of Ride objects
    }
    return vectorOfRideObjects;
}

// Helper function that helps keep track of the Ride objects
void displayData(vector<Ride> &vectorOfRideObjects) {
    
    cout << "Size of Vector of Ride Objects: " << vectorOfRideObjects.size() << endl;
    
    cout << "Printing objects' data: " << endl;
    for (int i = 0; i < vectorOfRideObjects.size(); i++) {
        cout << "Object " << i + 1 << ":" << endl;
        
        cout << setw(4) << "" << " Ride ID: " << vectorOfRideObjects.at(i).getRideID() << endl;
        cout << setw(4) << "" << " Ride Type: " << vectorOfRideObjects.at(i).getRideType() << endl;
        cout << setw(4) << "" << " Date Start: " << vectorOfRideObjects.at(i).getDateAndTimeStart() << endl;
        cout << setw(4) << "" << " Date End: " << vectorOfRideObjects.at(i).getDateAndTimeEnd() << endl;
        cout << setw(4) << "" << " Station Name Start: " << vectorOfRideObjects.at(i).getStationNameStart() << endl;
        cout << setw(4) << "" << " Station Name End: " << vectorOfRideObjects.at(i).getStationNameEnd() << endl;
        cout << setw(4) << "" << " Latitude Start: " << vectorOfRideObjects.at(i).getLatitudeStart() << endl;
        cout << setw(4) << "" << " Longitude Start: " << vectorOfRideObjects.at(i).getLongitudeStart() << endl;
        cout << setw(4) << "" << " Latitude End: " << vectorOfRideObjects.at(i).getLatitudeEnd() << endl;
        cout << setw(4) << "" << " Longitude End: " << vectorOfRideObjects.at(i).getLongitudeEnd() << endl;
        cout << setw(4) << "" << " Member or Casual: " << vectorOfRideObjects.at(i).getMemberType() << endl;
    }
}

// This function uses a Ride member function that checks wheather the object actually has information in every data field.
// If the next Ride object is complete, we push it into a new vector of Rides and we return that vector
vector<Ride> extractCleanData(vector<Ride> &vectorOfRideObjects) {
    
    vector<Ride> cleanData;
    
    for(int i = 0; i < vectorOfRideObjects.size(); i++) {
        if(vectorOfRideObjects.at(i).isClean()) {
            cleanData.push_back(vectorOfRideObjects.at(i));
        }
    }
    return cleanData;
}

void displayOverallTripInfo(vector<Ride> &rides) {
    
    double sumOfDistances = 0;
    double largestDistance = 0;
    double averageDistance;
    double nextDistance;
    
    int indexLargestDistance = 0;
    
    double latitudeStart;
    double longitudeStart;
    double latitudeEnd;
    double longitudeEnd;
    
    // Find largest distance and calculate the sum of all distances
    for (int i = 0 ; i < rides.size(); i++) {
        latitudeStart = stod(rides.at(i).getLatitudeStart());
        longitudeStart = stod(rides.at(i).getLongitudeStart());
        latitudeEnd = stod(rides.at(i).getLatitudeEnd());
        longitudeEnd = stod(rides.at(i).getLongitudeEnd());
        
        nextDistance = distance(latitudeStart,longitudeStart,latitudeEnd,longitudeEnd);
        
        sumOfDistances = sumOfDistances + nextDistance;
        
        if (largestDistance < nextDistance) {
            largestDistance = nextDistance;
            indexLargestDistance = i;
        }
    }
    
    averageDistance = sumOfDistances / rides.size();
    
    cout << "Total # of miles traveled: " <<  round(sumOfDistances) << endl;
    
    if (averageDistance < 1.3) {
    cout << "Average length of trips in miles: " << round(averageDistance*10)/10 << endl;
    } else {
        cout << "Average length of trips in miles: " << round(averageDistance*10)/10 << endl;
    }

    cout << endl;
    
    cout << "Longest trip information below: " << endl;
    cout << "-------------------------------" << endl;
    
    cout << "Trip ID: " << rides.at(indexLargestDistance).getRideID() << endl;
    cout << "Trip start location: " << rides.at(indexLargestDistance).getStationNameStart() << endl;
    cout << "Trip end location: " <<  rides.at(indexLargestDistance).getStationNameEnd() << endl;
    cout << "Trip distance in miles: " << round(largestDistance*10)/10 << endl;
}

void displayMenu() {
    cout << " Select a menu option: " << endl;
    cout << "   1. Select datafile, display rides totals and clean data" << endl;
    cout << "   2. Display overall trip information" << endl;
    cout << "   3. Display percentage of members vs. casual riders" << endl;
    cout << "   4. Display weekday vs weekend usage" << endl;
    cout << "   5. Extra Credit: find closest station" << endl;
    cout << "   6. Exit " << endl;
}

void displayPercentCasualVsMember(vector<Ride> &rides) {
    
    int totalNumOfRides = rides.size();
   
    int memberCounter = 0;
    int casualCounter = 0;
    
    double memberPercent;
    double casualPercent;
    
    string nextString;
    
    // Find out how many rides have a member type member
    for (int i = 0; i < totalNumOfRides; i++) {
        nextString = rides.at(i).getMemberType();
        
        if(nextString == "member") {
            memberCounter++;
        }
    }
    // Calculate number of casual riders
    casualCounter = totalNumOfRides - memberCounter;
    
    // Calculate percentages
    casualPercent = (double (casualCounter) / (totalNumOfRides)) * 100.0;
    memberPercent = 100.0 - casualPercent;
    
    cout << "Casual Rider Percentage: ";
    printf("%.1f", casualPercent);
    cout << "%" << endl;
    
    cout << "Member Rider Percentage: ";
    printf("%.1f", memberPercent);
    cout << "%" << endl;
}

vector<Ride> selectDataFile() {
    
    vector<string> vectorOfRideStrings;     // Here we will read the data into
    vector<Ride> vectorOfRideObjects;       // Here we will transfer the data from vectorOfRideStrings in the form of Ride objects
    vector<Ride> cleanData;                 // Here we wil store the clean Data
    int choice;
    
    do {
        
        cout << " Select datafile: " << endl;
        cout << "   1. Small subset of data with 14 rides to help create your program" << endl;
        cout << "   2. Week day vs weekend rides" << endl;
        cout << "   3. All September 2021 data (not tested in Zybooks)" << endl;
        
        cin >> choice;
        // cout << "Your selection --> " << choice << endl;
        cout << "Your selection --> " << endl;
        
        switch (choice) {
            case 1:
                readData(vectorOfRideStrings, choice);      // Read from divvyridesampledata
                vectorOfRideObjects = createVectorOfRideObj(vectorOfRideStrings);
                break;
                
            case 2:
                readData(vectorOfRideStrings, choice);      // Read from weekdayweekend
                vectorOfRideObjects = createVectorOfRideObj(vectorOfRideStrings);
                break;
                
            case 3:
                readData(vectorOfRideStrings, choice);      // Read from all_divvy_rides_september
                vectorOfRideObjects = createVectorOfRideObj(vectorOfRideStrings);
                break;
                
            default:
                break;
        }
        
    } while (choice < 1 || choice > 3);
    
    cleanData = extractCleanData(vectorOfRideObjects);      // Store clean data into cleanData
    
    cout << "   Total # of trips found in datafile: " << vectorOfRideObjects.size() << endl;
    cout << "   Total # of trips in clean data: " << cleanData.size() << endl;
    
    return cleanData;
}

// This function extracts every single ride from the day provided.
// For our purpose, we only need the rides for the days 1 and 4 of
// September, but this is a general function
vector<Ride> extractRidesByDay(vector<Ride> &rides, int day){
    
    vector<Ride> ridesPerDay;
    string nextStartDayString;
    int nextStartDayInt;
    string nextRideDate;
    int indexOfFirstSlash;
    int indexOfSecondSlash;
    
    // This loop extracts the day of the ride, and stores the Ride in a vector if the
    // day happens to be the one we provided
    for (int i = 0; i < rides.size(); i++) {
        nextRideDate = rides.at(i).getDateAndTimeStart();
        indexOfFirstSlash = nextRideDate.find('/', 0);
        indexOfSecondSlash = nextRideDate.find('/', indexOfFirstSlash + 1);
        nextStartDayString = nextRideDate.substr(indexOfFirstSlash + 1, indexOfSecondSlash - (indexOfFirstSlash + 1 ));
        nextStartDayInt = stod(nextStartDayString);

        if(nextStartDayInt == day) {
            ridesPerDay.push_back(rides.at(i));
        }
    }
    return ridesPerDay;
}

// This function extracts the hour in which the next ride started and counts
// the number of rides per hour
vector<int> countRidesPerHour(vector<Ride> ridesPerDay) {
    vector<int> ridesPerHourCounter(24); // Vector with 24 elements, one for each hour of the day
    int indexOfSpace;
    int indexOfColon;
    string hourStr;
    int hourInt;
    string nextRideStartDate;
    

    for (int i = 0; i < ridesPerDay.size(); i++) {
        nextRideStartDate = ridesPerDay.at(i).getDateAndTimeStart();
        indexOfSpace = nextRideStartDate.find(' ',0);
        indexOfColon = nextRideStartDate.find(':',0);
        hourStr = nextRideStartDate.substr(indexOfSpace + 1, indexOfColon - (indexOfSpace + 1));
        hourInt = stod(hourStr);
        ridesPerHourCounter.at(hourInt)++;
    }

    return ridesPerHourCounter;
}

// Display a table showing the number of rides per hour in a weekday and in the weekend
void displayWeekdayVsWeekendTable(vector<int> &ridesPerHourCounterWeekday, vector<int> &ridesPerHourCounterWeekend) {
    
    cout << "Rides per hour for weekday and weekend:" << endl;
    
    for (int i = 0; i < 24; i++) {
        cout << setw(5) << i << ":" << setw(7) << ridesPerHourCounterWeekday.at(i) << setw(7) << ridesPerHourCounterWeekend.at(i) << endl;
    }
}

// Helper function to find the largest number of rides
int findLargestNumberOfRides(vector<int> &weekday, vector<int> &weekend) {
    int largestNumberOfRides = weekday.at(0);
    
    for (int i = 0; i < 24; i++) {
        if (largestNumberOfRides < weekday.at(i)) {
            largestNumberOfRides = weekday.at(i);
        }
    }
    
    for (int i = 0; i < 24; i++) {
        if (largestNumberOfRides < weekend.at(i)) {
            largestNumberOfRides = weekend.at(i);
        }
    }
    return largestNumberOfRides;
}

void displayGraph(vector<int> weekday, vector<int> weekend) {
    
    int largest = findLargestNumberOfRides(weekday,weekend);
    int nextNumOfRides;
    const int maxNumOfChar = 50;
    int numOfChar;

    for (int i = 0; i < 24; i++) {
        cout << setw(5) << i << ": ";
        
        nextNumOfRides = weekday.at(i);
        numOfChar = int((double(nextNumOfRides)/largest) * maxNumOfChar);
        
        for (int i = 0; i < numOfChar; i++) {
            cout << "@";
        }
        cout << endl;
        
        nextNumOfRides = weekend.at(i);
        cout << setw(7) << "";
        numOfChar = int((double(nextNumOfRides)/largest) * maxNumOfChar);
        
        for (int i = 0; i < numOfChar; i++) {
            cout << "+";
        }
        cout << endl;
    }
}

void selectTypeOfDisplay(vector<Ride> &rides) {
    
    vector<Ride> weekdayRides = extractRidesByDay(rides, 1);    // Provide vector of rides and day to extract the information from
    vector<Ride> weekendRides = extractRidesByDay(rides, 4);
    
    vector<int> ridesPerHourCounterWeekday = countRidesPerHour(weekdayRides); // Create a counter vector for each hour of the day
    vector<int> ridesPerHourCounterWeekend = countRidesPerHour(weekendRides);
   
    int choice;
    do {
        cout << "Select type of display: " << endl;
        cout << "   1. Counts of rides per hour in the day " << endl;
        cout << "   2. Proportional 50 column graph with @ for weekday and + for weekend" << endl;
        
        cin >> choice;
        cout << "Your selection-->" << endl;
        
        switch (choice) {
            case 1: {
                int largestNumberOfRides = findLargestNumberOfRides(ridesPerHourCounterWeekday,ridesPerHourCounterWeekend);
                cout << "LargestNumberOfRides is: " << largestNumberOfRides << endl;
                displayWeekdayVsWeekendTable(ridesPerHourCounterWeekday,ridesPerHourCounterWeekend);
                break;
          } case 2:
                displayGraph(ridesPerHourCounterWeekday, ridesPerHourCounterWeekend);
                break;
                
            default:
                break;
        }
    } while(choice < 1 || choice > 2);
}

// Extra Credit portion
void findClosestStation() {
    
    vector<Ride> vectorOfRideObjects;
    vector<string> vectorOfRideStrings;
    int const readAllRidesOption = 3;
    readData(vectorOfRideStrings,readAllRidesOption);
    vectorOfRideObjects = createVectorOfRideObj(vectorOfRideStrings);
    vector<Ride> cleanData = extractCleanData(vectorOfRideObjects);
    
    double inputLatitude;
    double inputLongitude;
    
    double minLatitude;
    double minLongitude;
    
    double nextLatitude;
    double nextLongitude;
    
    double minDistance;
    double nextDistance;
    
    string closestStation;
    
    cout << "Input latitude and longitude of the home: ";
    cin >> inputLatitude;
    cin >> inputLongitude;
    
    // Get distance to the first station from the first Ride object
    minLatitude = stod(cleanData.at(0).getLatitudeStart());
    minLongitude = stod(cleanData.at(0).getLongitudeStart());
    minDistance = distance(inputLatitude,inputLongitude,minLatitude,minLongitude);
    closestStation = cleanData.at(0).getStationNameStart();

    for (int i = 1; i < cleanData.size(); i++) {
        
        nextLatitude = stod(cleanData.at(i).getLatitudeStart());      // Every ride has two stations. Thus we have to check both.
        nextLongitude = stod(cleanData.at(i).getLongitudeStart());
        nextDistance = distance(inputLatitude,inputLongitude,nextLatitude,nextLongitude);
        
        if (nextDistance < minDistance) {
            minDistance = nextDistance;
            
            minLatitude = stod(cleanData.at(i).getLatitudeStart());
            minLongitude = stod(cleanData.at(i).getLongitudeStart());
            closestStation = cleanData.at(i).getStationNameStart();
        }
        
        nextLatitude = stod(cleanData.at(i).getLatitudeEnd());
        nextLongitude = stod(cleanData.at(i).getLongitudeEnd());
        nextDistance = distance(inputLatitude,inputLongitude,nextLatitude,nextLongitude);
        
        if (nextDistance < minDistance) {
            minDistance = nextDistance;
            
            minLatitude = stod(cleanData.at(i).getLatitudeEnd());
            minLongitude = stod(cleanData.at(i).getLongitudeEnd());
            closestStation = cleanData.at(i).getStationNameEnd();
        }
    }
    
    cout << "You entered: " << round(inputLatitude * 10)/10 << " for latitude and " << round(inputLongitude * 10)/10 << " for longitude" << endl;
    cout << "Closest Divvy station is: " << closestStation << " at ";
    printf("%.8f", minLatitude);
    cout << ", ";
    printf("%.8f", minLongitude);
    cout << ", ";
    cout << round(minDistance * 10)/10 << " miles away" << endl;
}

int main(int argc, const char * argv[]) {
    
    vector<Ride> rides;
    bool dataWasRead = false;
    int choice;
    
    cout << "Analyze Divvy bike ride information using September trip data." << endl;
    cout << "First select option 1 to read and clean the data." << endl;
    
    do {
        displayMenu();
        
        cin >> choice;
        //cout << "Your choice --> " << choice << endl;
        cout << "Your choice --> " << endl;
        
        switch (choice) {
            case 1:
                rides = selectDataFile();
                dataWasRead = true;
                break;
            
            case 2:
                if (!dataWasRead) {
                    cout << "   First read in data by selecting menu option 1" << endl;
                    continue;
                }
                displayOverallTripInfo(rides);
                break;
                
            case 3: {
                if (!dataWasRead) {
                    cout << "   First read in data by selecting menu option 1" << endl;
                    continue;
                }
                displayPercentCasualVsMember(rides);
                break;
            }
            case 4: {
           
                if (!dataWasRead) {
                    cout << "   First read in data by selecting menu option 1" << endl;
                    continue;
                }
                selectTypeOfDisplay(rides);
                break;
            }
            case 5: {
            
                findClosestStation();

                break;
            }
            default:
                break;
        }
        
    } while (choice != 6);
    return 0;
}
