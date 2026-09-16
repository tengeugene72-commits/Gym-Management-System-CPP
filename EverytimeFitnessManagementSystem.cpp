#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cctype> 

using namespace std;

// CONSTANT VARIABLES
const double SST_RATE = 0.06;
const double STUDENT_DISCOUNT_RATE = 0.20;
const double PLAN1_FEE = 1140.0;
const double PLAN2_FEE = 2040.0;
const int MAX_MEMBERS_TRACKED = 20;
const int DAYS_IN_WEEK = 7;

// DATA STRUCTURES
struct Member {
    string memberID;
    string password;
    string name;
    string phoneNumber;
    int planCode = 0;
    string status;
    double benchPressPR = 0.0;
    double deadliftPR = 0.0;
    double squatPR = 0.0;
};

struct FitnessClass {
    string classID;
    string className;
    string trainerName;
    string time;
    int maxCapacity;
    int currentBookings;
};

struct BookingRecord {
    string memberID;
    string classID;
};

struct Locker {
    string lockerID;
    double rentalFee;
    bool isAvailable;
};

struct Payment {
    string memberID;
    double subtotal;
    double discountAmount;
    double totalAmount;
    double paymentAmount;
    double change;
};

struct Attendance {
    string memberID;
    bool hasCheckedOut;
};

// FUNCTIONS

// Helper Function
string toUpperCase(string str);

// Module 1: Member Management & Login
bool loginMember(const vector<Member>& members, string& loggedInUserID);
void createMember(vector<Member>& members);
void retrieveMember(const vector<Member>& members);
void updateMember(vector<Member>& members);
void deleteMember(vector<Member>& members, string& currentSessionUser);
int selectMembershipPlan();
int searchMember(const vector<Member>& members, string searchInput);
string checkMembershipStatus(const Member& member);
// Module 2: Booking
void displaySchedule(const vector<FitnessClass>& classes);
void bookClass(vector<Member>& members, vector<FitnessClass>& classes, vector<BookingRecord>& bookings);
void modifyBooking(vector<FitnessClass>& classes, vector<BookingRecord>& bookings);
void viewMyBookings(const vector<FitnessClass>& classes, const vector<BookingRecord>& bookings);
// Module 3: Billing & Locker
double calculateServiceFee(int serviceType);
void processPayment(vector<Member>& members, vector<Payment>& payments);
void rentLocker(vector<Locker>& lockers);
void generateReceipt(const Payment& payment);
// Module 4: Attendance & Analytics
void recordCheckIn(vector<Attendance>& attendanceLog, const vector<Member>& members);
void recordCheckOut(vector<Attendance>& attendanceLog);
int calculateOccupancy(const vector<Attendance>& attendanceLog);
void analyseClassPopularity(const vector<FitnessClass>& classes);
void generateWeeklyAttendanceMatrix(const vector<Member>& members);
// Extra Features
void calculateBMI();
void managePersonalRecords(vector<Member>& members, const string& currentSessionUser);

int main() {
    vector<Member> memberList;
    vector<Payment> paymentList;
    vector<Attendance> attendanceList;
    vector<BookingRecord> bookingList;

    // Dummy Data for member 
    memberList.push_back({ "ETF1111", "password123", "John Doe", "012-3456789", 1, "Active", 60.0, 100.0, 80.0 });
    memberList.push_back({ "ETF2222", "12345678", "Jane Smith", "019-8765432", 2, "Expired", 0.0, 0.0, 0.0 });
    memberList.push_back({ "ETF3333", "gym123456", "Ali Bin Abu", "011-1111222", 1, "Active", 80.0, 120.0, 100.0 });

    // Initialize a full schedule of classes with times included
    vector<FitnessClass> classList = {
        {"C01", "Yoga", "Sarah", "08:00 AM", 10, 3},
        {"C02", "HIIT", "Mike", "09:30 AM", 5, 2},
        {"C03", "Zumba", "Linda", "11:00 AM", 15, 7},
        {"C04", "Spinning", "David", "05:00 PM", 12, 5},
        {"C05", "Pilates", "Emma", "06:00 PM", 8, 8},
        {"C06", "BodyPump", "James", "07:30 PM", 20, 8},
        {"C07", "Muay Thai", "Ali", "08:30 PM", 10, 0}
    };

    // Initialize lockers
    vector<Locker> lockerList = {
        {"L01", 50.0, true}, {"L02", 50.0, true}, {"L03", 50.0, true},
        {"L04", 50.0, true}, {"L05", 50.0, true}, {"L06", 50.0, true},
        {"L07", 75.0, true}, {"L08", 75.0, true}, {"L09", 75.0, true},
        {"L10", 75.0, true}
    };

    int choice;
    string currentSessionUser = ""; // Tracks currently logged-in user

    do {
        cout << "\n============================================\n";
        cout << "   EVERYTIME FITNESS MANAGEMENT SYSTEM\n";
        cout << "============================================\n";
        cout << "1. Member Management & Login\n";
        cout << "2. Class & Trainer Booking\n";
        cout << "3. Billing, Payment & Lockers\n";
        cout << "4. Attendance & Reports\n";
        cout << "5. Extra Features (BMI & PR tracker)\n";
        cout << "6. Exit\n";
        cout << "============================================\n";
        if (currentSessionUser != "") {
            cout << "[Logged in as: " << currentSessionUser << "]\n";
        }
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            if (cin.eof()) {
                cout << "\nInput stream closed. Exiting system.\n";
                break; // exit the do-while loop cleanly instead of looping forever
            }
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number from 1 to 6.\n";
            choice = 0;
            continue;
        }
        else {
            cin.ignore(10000, '\n'); // Clear trailing garbage
        }

        switch (choice) {
        case 1: {
            int sub;
            cout << "\n--- Member & Login Management ---\n";
            if (currentSessionUser == "") {
                cout << "1. Login\n";
            }
            else {
                cout << "1. Login (Switch User)\n";
            }
            cout << "2. Create Account (Register)\n";
            cout << "3. Retrieve Account Details\n";
            cout << "4. Update Account\n";
            cout << "5. Delete Account\n";
            cout << "6. Logout\n";
            cout << "0. Back to Main Menu\n";
            cout << "Choice: ";
            cin >> sub;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a number.\n";
                break;
            }
            else {
                cin.ignore(10000, '\n');
            }

            if (sub == 1) loginMember(memberList, currentSessionUser);
            else if (sub == 2) createMember(memberList);
            else if (sub == 3) retrieveMember(memberList);
            else if (sub == 4) updateMember(memberList);
            else if (sub == 5) deleteMember(memberList, currentSessionUser);
            else if (sub == 6) {
                if (currentSessionUser != "") {
                    cout << "User " << currentSessionUser << " has been logged out successfully.\n";
                    currentSessionUser = "";
                }
                else {
                    cout << "Notice: No user is currently logged in.\n";
                }
            }
            else if (sub == 0) cout << "Returning to Main Menu...\n";
            else cout << "Invalid choice.\n";
            break;
        }
        case 2: {
            int sub;
            cout << "\n--- Class & Trainer Booking ---\n";
            cout << "1. View Schedule\n";
            cout << "2. Book Class\n";
            cout << "3. Cancel/Modify Class\n";
            cout << "4. View My Bookings\n";
            cout << "0. Back to Main Menu\n";
            cout << "Choice: ";
            cin >> sub;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a number.\n";
                break;
            }
            else {
                cin.ignore(10000, '\n');
            }

            if (sub == 1) displaySchedule(classList);
            else if (sub == 2) bookClass(memberList, classList, bookingList);
            else if (sub == 3) modifyBooking(classList, bookingList);
            else if (sub == 4) viewMyBookings(classList, bookingList);
            else if (sub == 0) cout << "Returning to Main Menu...\n";
            else cout << "Invalid choice.\n";
            break;
        }
        case 3: {
            int sub;
            cout << "\n--- Billing, Payment & Lockers ---\n";
            cout << "1. Process Payment (Activates Member)\n";
            cout << "2. Rent Locker\n";
            cout << "0. Back to Main Menu\n";
            cout << "Choice: ";
            cin >> sub;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a number.\n";
                break;
            }
            else {
                cin.ignore(10000, '\n');
            }

            if (sub == 1) processPayment(memberList, paymentList);
            else if (sub == 2) rentLocker(lockerList);
            else if (sub == 0) cout << "Returning to Main Menu...\n";
            else cout << "Invalid choice.\n";
            break;
        }
        case 4: {
            int sub;
            cout << "\n--- Attendance & Reports ---\n";
            cout << "1. Member Check-in\n";
            cout << "2. Member Check-out\n";
            cout << "3. View Occupancy\n";
            cout << "4. Class Analytics\n";
            cout << "5. Weekly Attendance Matrix\n";
            cout << "0. Back to Main Menu\n";
            cout << "Choice: ";
            cin >> sub;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a number.\n";
                break;
            }
            else {
                cin.ignore(10000, '\n');
            }

            if (sub == 1) recordCheckIn(attendanceList, memberList);
            else if (sub == 2) recordCheckOut(attendanceList);
            else if (sub == 3) cout << "Current Occupancy: " << calculateOccupancy(attendanceList) << "\n";
            else if (sub == 4) analyseClassPopularity(classList);
            else if (sub == 5) generateWeeklyAttendanceMatrix(memberList);
            else if (sub == 0) cout << "Returning to Main Menu...\n";
            else cout << "Invalid choice.\n";
            break;
        }
        case 5: {
            int sub;
            cout << "\n--- Extra Features ---\n";
            cout << "1. BMI Calculator\n";
            cout << "2. Personal Record (PR) Tracker\n";
            cout << "0. Back to Main Menu\n";
            cout << "Choice: ";
            cin >> sub;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a number.\n";
                break;
            }
            else {
                cin.ignore(10000, '\n');
            }

            if (sub == 1) calculateBMI();
            else if (sub == 2) managePersonalRecords(memberList, currentSessionUser);
            else if (sub == 0) cout << "Returning to Main Menu...\n";
            else cout << "Invalid choice.\n";
            break;
        }
        case 6:
            cout << "Exiting system. Goodbye!\n";
            break;
        default:
            cout << "Invalid selection! Please enter a number from 1 to 6.\n";
        }
    } while (choice != 6);

    return 0;
}

// Helper function to handle case sensitivity
string toUpperCase(string str) {
    for (int i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

// Module 1 : Member login and register
bool loginMember(const vector<Member>& members, string& loggedInUserID) {
    string inputID, inputPass;
    cout << "\n--- Member Login ---\n";
    cout << "Enter User ID (or '0' to go back): ";
    cin >> inputID;
    cin.ignore(10000, '\n');
    if (inputID == "0") return false;
    inputID = toUpperCase(inputID);

    cout << "Enter Password: ";
    cin >> inputPass;
    cin.ignore(10000, '\n');

    for (size_t i = 0; i < members.size(); i++) {
        if (members[i].memberID == inputID && members[i].password == inputPass) {
            loggedInUserID = inputID;
            cout << "Login successful! Welcome, " << members[i].name << ".\n";
            return true;
        }
    }
    cout << "Error: Invalid User ID or Password.\n";
    return false;
}

void createMember(vector<Member>& members) {
    Member m;
    cout << "\n--- Create New Account ---\n";

    while (true) {
        cout << "Enter new User ID (format ETFxxxx, or '0' to go back): ";
        cin >> m.memberID;
        cin.ignore(10000, '\n');
        if (m.memberID == "0") return;
        m.memberID = toUpperCase(m.memberID);

        bool isValidID = true;
        if (m.memberID.length() != 7 || m.memberID[0] != 'E' || m.memberID[1] != 'T' || m.memberID[2] != 'F') {
            isValidID = false;
        }
        else {
            for (int i = 3; i < 7; i++) {
                if (m.memberID[i] < '0' || m.memberID[i] > '9') {
                    isValidID = false;
                }
            }
        }

        if (isValidID) {
            if (searchMember(members, m.memberID) != -1) {
                cout << "Error: User ID already exists!\n";
            }
            else {
                break;
            }
        }
        else {
            cout << "Invalid format! User ID must start with ETF followed by 4 numbers (e.g., ETF1234).\n";
        }
    }

    while (true) {
        cout << "Create Password (min 8 characters, no spaces): ";
        cin >> m.password;
        cin.ignore(10000, '\n');

        if (m.password.length() >= 8) break;
        else cout << "Error: Password is too short! Must be at least 8 characters long.\n";
    }

    cout << "Enter Name: ";
    while (true) {
        getline(cin, m.name);
        bool hasNumber = false;
        for (int i = 0; i < m.name.length(); i++) {
            if (m.name[i] >= '0' && m.name[i] <= '9') {
                hasNumber = true;
            }
        }
        if (hasNumber == false && m.name.length() > 0) break;
        else cout << "Error: Name cannot be empty or contain numbers. Enter Name again: ";
    }

    while (true) {
        cout << "Enter Phone (format 01x-xxxxxxx): ";
        getline(cin, m.phoneNumber);
        bool isValid = true;
        if (m.phoneNumber.length() != 11 || m.phoneNumber[0] != '0' || m.phoneNumber[1] != '1' || m.phoneNumber[3] != '-') {
            isValid = false;
        }
        else {
            for (int i = 0; i < 11; i++) {
                if (i == 3) continue;
                if (m.phoneNumber[i] < '0' || m.phoneNumber[i] > '9') isValid = false;
            }
        }
        if (isValid) break;
        else cout << "Invalid format! Example: 012-3456789\n";
    }

    m.planCode = selectMembershipPlan();
    m.status = "Expired";
    m.benchPressPR = 0.0;
    m.deadliftPR = 0.0;
    m.squatPR = 0.0;
    members.push_back(m);
    cout << "Account created successfully! Please login to continue.\n";
}

void retrieveMember(const vector<Member>& members) {
    string id;
    cout << "\n--- Retrieve Account Details ---\n";
    cout << "Enter User ID to search (or '0' to go back): ";
    cin >> id;
    cin.ignore(10000, '\n');
    if (id == "0") return;
    id = toUpperCase(id);

    int index = searchMember(members, id);
    if (index != -1) {
        cout << "\n--- Member Profile ---\n";
        cout << "User ID: " << members[index].memberID << "\n";
        cout << "Name: " << members[index].name << "\n";
        cout << "Phone: " << members[index].phoneNumber << "\n";
        cout << "Plan Code: " << members[index].planCode << "\n";
        cout << "Status: " << members[index].status << "\n";
        cout << "----------------------\n";
    }
    else {
        cout << "Member not found.\n";
    }
}

void updateMember(vector<Member>& members) {
    string id, pass;
    cout << "\n--- Update Account ---\n";
    cout << "Enter User ID to update (or '0' to go back): ";
    cin >> id;
    cin.ignore(10000, '\n');
    if (id == "0") return;
    id = toUpperCase(id);

    int index = searchMember(members, id);
    if (index != -1) {
        cout << "Enter Password to verify identity: ";
        cin >> pass;
        cin.ignore(10000, '\n');

        if (members[index].password == pass) {
            int updateChoice;
            cout << "What would you like to update?\n1. Password\n2. Phone Number\nChoice: ";
            cin >> updateChoice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input! Update canceled.\n";
                return;
            }
            else {
                cin.ignore(10000, '\n');
            }

            if (updateChoice == 1) {
                while (true) {
                    cout << "Enter new password (min 8 characters, no spaces): ";
                    cin >> members[index].password;
                    cin.ignore(10000, '\n');

                    if (members[index].password.length() >= 8) break;
                    else cout << "Error: Password is too short! Must be at least 8 characters long.\n";
                }
                cout << "Password updated successfully.\n";
            }
            else if (updateChoice == 2) {
                while (true) {
                    cout << "Enter new phone number (format 01x-xxxxxxx): ";
                    getline(cin, members[index].phoneNumber);
                    bool isValid = true;
                    if (members[index].phoneNumber.length() != 11 || members[index].phoneNumber[0] != '0' || members[index].phoneNumber[1] != '1' || members[index].phoneNumber[3] != '-') {
                        isValid = false;
                    }
                    else {
                        for (int i = 0; i < 11; i++) {
                            if (i == 3) continue;
                            if (members[index].phoneNumber[i] < '0' || members[index].phoneNumber[i] > '9') isValid = false;
                        }
                    }
                    if (isValid) break;
                    else cout << "Invalid format! Example: 012-3456789\n";
                }
                cout << "Phone number updated successfully.\n";
            }
            else {
                cout << "Invalid choice.\n";
            }
        }
        else {
            cout << "Incorrect password! Update denied.\n";
        }
    }
    else {
        cout << "Member not found.\n";
    }
}

void deleteMember(vector<Member>& members, string& currentSessionUser) {
    string id, pass;
    cout << "\n--- Delete Account ---\n";
    cout << "Enter User ID to delete (or '0' to go back): ";
    cin >> id;
    cin.ignore(10000, '\n');
    if (id == "0") return;
    id = toUpperCase(id);

    int index = searchMember(members, id);
    if (index != -1) {
        cout << "WARNING: You are about to delete this account.\n";
        cout << "Enter Password to confirm: ";
        cin >> pass;
        cin.ignore(10000, '\n');

        if (members[index].password == pass) {
            if (members[index].memberID == currentSessionUser) {
                currentSessionUser = ""; // Log them out completely
            }
            members.erase(members.begin() + index);
            cout << "Account completely deleted from the system.\n";
        }
        else {
            cout << "Incorrect password! Deletion canceled.\n";
        }
    }
    else {
        cout << "Member not found.\n";
    }
}

int selectMembershipPlan() {
    string planChoice;
    int plan = 0;

    while (true) {
        cout << "\n--- Everytime Fitness Membership Plans ---\n";
        cout << "1. 6-Month Commitment (RM 1,140 total / RM 190 per month)\n";
        cout << "2. 1-Year Commitment  (RM 2,040 total / RM 170 per month - Best Value!)\n";
        cout << "Select Plan (1 or 2): ";
        cin >> planChoice;
        cin.ignore(10000, '\n');

        if (planChoice == "1") {
            plan = 1;
            break;
        }
        else if (planChoice == "2") {
            plan = 2;
            break;
        }
        else {
            cout << "Invalid selection! Please enter exactly 1 or 2.\n";
        }
    }
    return plan;
}

int searchMember(const vector<Member>& members, string searchInput) {
    for (size_t i = 0; i < members.size(); i++) {
        if (members[i].memberID == searchInput) {
            return (int)i;
        }
    }
    return -1;
}

string checkMembershipStatus(const Member& member) {
    return member.status;
}

// --- Module 2: Booking Management ---
void displaySchedule(const vector<FitnessClass>& classes) {
    cout << left << setw(10) << "ID" << setw(15) << "Class" << setw(15) << "Trainer" << setw(12) << "Time" << "Available Slots\n";
    cout << "------------------------------------------------------------------\n";
    for (const auto& c : classes) {
        cout << left << setw(10) << c.classID
            << setw(15) << c.className
            << setw(15) << c.trainerName
            << setw(12) << c.time
            << (c.maxCapacity - c.currentBookings) << "/" << c.maxCapacity << "\n";
    }
}

void bookClass(vector<Member>& members, vector<FitnessClass>& classes, vector<BookingRecord>& bookings) {
    string mID, cID;

    cout << "\n--- Book a Fitness Class ---\n";
    cout << "Enter Member ID (or type '0' to go back): ";
    cin >> mID;
    cin.ignore(10000, '\n');
    if (mID == "0") return;
    mID = toUpperCase(mID);

    int mIndex = searchMember(members, mID);
    if (mIndex == -1 || checkMembershipStatus(members[mIndex]) != "Active") {
        cout << "Cannot book: Member not found or membership is not Active.\n";
        return;
    }

    cout << "\n--- Available Class Schedule ---\n";
    displaySchedule(classes);

    cout << "\nEnter Class ID to book (or type '0' to go back): ";
    cin >> cID;
    cin.ignore(10000, '\n');
    if (cID == "0") return;
    cID = toUpperCase(cID);

    for (const auto& b : bookings) {
        if (b.memberID == mID && toUpperCase(b.classID) == cID) {
            cout << "Booking failed. You have already booked this class.\n";
            return;
        }
    }

    for (auto& c : classes) {
        if (toUpperCase(c.classID) == cID) {
            if (c.currentBookings < c.maxCapacity) {
                c.currentBookings++;
                bookings.push_back({ mID, c.classID });
                cout << "Successfully booked " << c.className << "!\n";
            }
            else {
                cout << "Sorry, " << c.className << " is full!\n";
            }
            return;
        }
    }
    cout << "Class ID not found. Booking failed.\n";
}

void modifyBooking(vector<FitnessClass>& classes, vector<BookingRecord>& bookings) {
    string mID, cID;
    cout << "\n--- Cancel a Booking ---\n";
    cout << "Enter Member ID (or '0' to go back): ";
    cin >> mID;
    cin.ignore(10000, '\n');
    if (mID == "0") return;
    mID = toUpperCase(mID);

    cout << "Enter Class ID to cancel: ";
    cin >> cID;
    cin.ignore(10000, '\n');
    cID = toUpperCase(cID);

    for (size_t i = 0; i < bookings.size(); i++) {
        if (bookings[i].memberID == mID && toUpperCase(bookings[i].classID) == cID) {
            bookings.erase(bookings.begin() + i);

            for (auto& c : classes) {
                if (toUpperCase(c.classID) == cID) {
                    c.currentBookings--;
                }
            }
            cout << "Booking cancelled successfully. Capacity updated.\n";
            return;
        }
    }
    cout << "Error: No matching booking found for this Member ID and Class ID.\n";
}

void viewMyBookings(const vector<FitnessClass>& classes, const vector<BookingRecord>& bookings) {
    string mID;
    cout << "\n--- View My Bookings ---\n";
    cout << "Enter Member ID (or type '0' to go back): ";
    cin >> mID;
    cin.ignore(10000, '\n');
    if (mID == "0") return;
    mID = toUpperCase(mID);

    bool foundAnyBooking = false;
    cout << "\n--- Your Booked Classes ---\n";
    cout << left << setw(10) << "ID" << setw(15) << "Class" << setw(15) << "Trainer" << setw(12) << "Time" << "\n";
    cout << "--------------------------------------------------------\n";

    for (const auto& b : bookings) {
        if (b.memberID == mID) {
            for (const auto& c : classes) {
                if (c.classID == b.classID) {
                    cout << left << setw(10) << c.classID
                        << setw(15) << c.className
                        << setw(15) << c.trainerName
                        << setw(12) << c.time << "\n";
                    foundAnyBooking = true;
                }
            }
        }
    }

    if (!foundAnyBooking) {
        cout << "You have not booked any fitness classes yet.\n";
    }
}

// --- Module 3: Billing & Payments ---
double calculateServiceFee(int planCode) {
    if (planCode == 1) return PLAN1_FEE;
    else return PLAN2_FEE;
}

void processPayment(vector<Member>& members, vector<Payment>& payments) {
    string id;
    cout << "\n--- Process Membership Payment ---\n";
    cout << "Enter Member ID (or '0' to go back): ";
    cin >> id;
    cin.ignore(10000, '\n');
    if (id == "0") return;
    id = toUpperCase(id);

    int index = searchMember(members, id);

    if (index != -1) {
        if (members[index].status == "Active") {
            cout << "Notice: This member's account is already 'Active'. No payment required at this time.\n";
            return;
        }

        double subtotal = calculateServiceFee(members[index].planCode);
        double discount = 0.0;

        char isStudent;
        cout << "Are you a student? Enter 'Y' for yes, or any other key for no: ";
        cin >> isStudent;
        cin.ignore(10000, '\n');

        if (isStudent == 'Y' || isStudent == 'y') {
            string studentID;
            while (true) {
                cout << "Enter Student ID (format 2xxxxxx) or '0' to cancel promo: ";
                cin >> studentID;
                cin.ignore(10000, '\n');

                if (studentID == "0") break;

                bool isValid = true;
                if (studentID.length() != 7 || studentID[0] != '2') {
                    isValid = false;
                }
                else {
                    for (int i = 1; i < 7; i++) {
                        if (studentID[i] < '0' || studentID[i] > '9') isValid = false;
                    }
                }

                if (isValid) {
                    cout << "Student ID verified! 20% discount applied.\n";
                    discount = subtotal * STUDENT_DISCOUNT_RATE;
                    break;
                }
                else {
                    cout << "Invalid format! Must start with '2' and be exactly 7 numbers.\n";
                }
            }
        }

        double afterDiscount = subtotal - discount;
        double sst = afterDiscount * SST_RATE;
        double total = afterDiscount + sst;

        cout << "\n--- Payment Summary ---\n";
        cout << "Subtotal: RM " << fixed << setprecision(2) << subtotal << "\n";
        if (discount > 0) cout << "Student Promo (20%): -RM " << discount << "\n";
        cout << "SST (6%): RM " << sst << "\n";
        cout << "Total Due: RM " << total << "\n";

        double paymentAmt;
        while (true) {
            cout << "Enter payment amount: RM ";
            cin >> paymentAmt;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter numbers only.\n";
            }
            else if (paymentAmt < total) {
                cin.ignore(10000, '\n');
                cout << "Insufficient amount.\n";
            }
            else {
                cin.ignore(10000, '\n');
                break;
            }
        }

        Payment p = { id, subtotal, discount, total, paymentAmt, paymentAmt - total };
        payments.push_back(p);

        members[index].status = "Active";
        generateReceipt(p);
    }
    else {
        cout << "Member not found.\n";
    }
}

void generateReceipt(const Payment& p) {
    cout << "\n==============================\n";
    cout << "       OFFICIAL RECEIPT\n";
    cout << "==============================\n";
    cout << "Member ID: " << p.memberID << "\n";
    cout << "Subtotal:       RM " << fixed << setprecision(2) << p.subtotal << "\n";
    if (p.discountAmount > 0) {
        cout << "Discount Saved: RM " << p.discountAmount << "\n";
    }
    cout << "------------------------------\n";
    cout << "TOTAL PAID:     RM " << p.totalAmount << "\n";
    cout << "CASH RECEIVED:  RM " << p.paymentAmount << "\n";
    cout << "CHANGE:         RM " << p.change << "\n";
    cout << "==============================\n";
}

void rentLocker(vector<Locker>& lockers) {
    string lID;
    cout << "Available Lockers:\n";
    for (const auto& l : lockers) {
        if (l.isAvailable) cout << "- " << l.lockerID << " (RM " << fixed << setprecision(2) << l.rentalFee << ")\n";
    }
    cout << "Enter Locker ID to rent (or '0' to go back): ";
    cin >> lID;
    cin.ignore(10000, '\n');
    if (lID == "0") return;
    lID = toUpperCase(lID);

    for (auto& l : lockers) {
        if (toUpperCase(l.lockerID) == lID && l.isAvailable) {
            double paymentAmt;
            while (true) {
                cout << "Enter payment amount (RM " << fixed << setprecision(2) << l.rentalFee << "): RM ";
                cin >> paymentAmt;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid input. Please enter numbers only.\n";
                }
                else if (paymentAmt < l.rentalFee) {
                    cin.ignore(10000, '\n');
                    cout << "Insufficient amount.\n";
                }
                else {
                    cin.ignore(10000, '\n');
                    break;
                }
            }

            l.isAvailable = false;
            double change = paymentAmt - l.rentalFee;
            cout << "\nLocker " << lID << " successfully rented!\n";

            cout << "\n==============================\n";
            cout << "       LOCKER RECEIPT\n";
            cout << "==============================\n";
            cout << "Locker ID:      " << l.lockerID << "\n";
            cout << "Rental Fee:     RM " << fixed << setprecision(2) << l.rentalFee << "\n";
            cout << "------------------------------\n";
            cout << "CASH RECEIVED:  RM " << fixed << setprecision(2) << paymentAmt << "\n";
            cout << "CHANGE:         RM " << fixed << setprecision(2) << change << "\n";
            cout << "==============================\n";
            return;
        }
    }
    cout << "Locker unavailable or invalid ID.\n";
}

// --- Module 4: Attendance Tracking ---
void recordCheckIn(vector<Attendance>& attendanceLog, const vector<Member>& members) {
    string id;
    cout << "Enter Member ID to Check-In (or '0' to go back): ";
    cin >> id;
    cin.ignore(10000, '\n');
    if (id == "0") return;
    id = toUpperCase(id);

    int index = searchMember(members, id);
    if (index == -1 || checkMembershipStatus(members[index]) != "Active") {
        cout << "Check-in failed. Member inactive or not found.\n";
        return;
    }

    for (const auto& a : attendanceLog) {
        if (a.memberID == id && !a.hasCheckedOut) {
            cout << "Check-in failed. This member is already checked in.\n";
            return;
        }
    }

    attendanceLog.push_back({ id, false });
    cout << "Check-in successful! Welcome to Everytime Fitness.\n";
}

void recordCheckOut(vector<Attendance>& attendanceLog) {
    string id;
    cout << "Enter Member ID to Check-Out (or '0' to go back): ";
    cin >> id;
    cin.ignore(10000, '\n');
    if (id == "0") return;
    id = toUpperCase(id);

    bool found = false;
    for (auto& a : attendanceLog) {
        if (a.memberID == id && !a.hasCheckedOut) {
            a.hasCheckedOut = true;
            cout << "Check-out successful! See you next time.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No active check-in found for this ID.\n";
    }
}

int calculateOccupancy(const vector<Attendance>& attendanceLog) {
    int count = 0;
    for (const auto& a : attendanceLog) {
        if (!a.hasCheckedOut) count++;
    }
    return count;
}

void analyseClassPopularity(const vector<FitnessClass>& classes) {
    cout << "\n--- Class Popularity Analytics ---\n";
    for (const auto& c : classes) {
        cout << c.className << " has " << c.currentBookings << " participant(s).\n";
    }
}

void generateWeeklyAttendanceMatrix(const vector<Member>& members) {
    int attendanceGrid[MAX_MEMBERS_TRACKED][DAYS_IN_WEEK] = { 0 };
    string dayLabels[DAYS_IN_WEEK] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

    int numTracked = min((int)members.size(), MAX_MEMBERS_TRACKED);

    cout << "\n--- Weekly Attendance Tracker ---\n";
    cout << "Enter check-in status for each member (1 = Present, 0 = Absent)\n";

    for (int m = 0; m < numTracked; m++) {
        cout << "\nMember: " << members[m].name << " (" << members[m].memberID << ")\n";
        for (int d = 0; d < DAYS_IN_WEEK; d++) {
            int status;
            cout << dayLabels[d] << ": ";
            cin >> status;
            if (cin.fail() || (status != 0 && status != 1)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input, defaulting to 0 (Absent).\n";
                status = 0;
            }
            else {
                cin.ignore(10000, '\n');
            }
            attendanceGrid[m][d] = status;
        }
    }

    cout << "\n--- Attendance Summary Grid ---\n";
    cout << left << setw(15) << "Member";
    for (int d = 0; d < DAYS_IN_WEEK; d++) cout << setw(6) << dayLabels[d];
    cout << "Total\n";
    cout << "---------------------------------------------------------\n";

    int dailyTotals[DAYS_IN_WEEK] = { 0 };

    for (int m = 0; m < numTracked; m++) {
        cout << left << setw(15) << members[m].name;
        int memberTotal = 0;
        for (int d = 0; d < DAYS_IN_WEEK; d++) {
            cout << setw(6) << attendanceGrid[m][d];
            memberTotal += attendanceGrid[m][d];
            dailyTotals[d] += attendanceGrid[m][d];
        }
        cout << memberTotal << " day(s)\n";
    }

    cout << "---------------------------------------------------------\n";
    cout << left << setw(15) << "Daily Total";
    for (int d = 0; d < DAYS_IN_WEEK; d++) cout << setw(6) << dailyTotals[d];
    cout << "\n";

    int busiestDay = 0;
    for (int d = 1; d < DAYS_IN_WEEK; d++) {
        if (dailyTotals[d] > dailyTotals[busiestDay]) busiestDay = d;
    }
    cout << "\nBusiest day this week: " << dayLabels[busiestDay]
        << " (" << dailyTotals[busiestDay] << " check-ins)\n";
}

// --- Extra Features (Bonus Marks) ---
void calculateBMI() {
    double weight, height;
    cout << "\n--- BMI Calculator ---\n";

    while (true) {
        cout << "Enter weight (kg, or 0 to go back): ";
        cin >> weight;
        if (cin.fail() || weight < 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a valid number.\n";
        }
        else if (weight == 0) {
            return; // 0 to go back
        }
        else {
            cin.ignore(10000, '\n');
            break;
        }
    }

    while (true) {
        cout << "Enter height (m, or 0 to go back): ";
        cin >> height;
        if (cin.fail() || height < 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a valid number.\n";
        }
        else if (height == 0) {
            return; // 0 to go back
        }
        else {
            cin.ignore(10000, '\n');
            break;
        }
    }

    double bmi = weight / (height * height);
    cout << "Your BMI is: " << fixed << setprecision(1) << bmi << "\n";
}

void managePersonalRecords(vector<Member>& members, const string& currentSessionUser) {
    int index = -1;
    cout << "\n--- Personal Record (PR) Tracker ---\n";

    // 1. If user is already logged in at the main menu, auto-authenticate them
    if (currentSessionUser != "") {
        index = searchMember(members, currentSessionUser);
        if (index != -1) {
            cout << "Authenticated via active session as: " << members[index].name << " (" << currentSessionUser << ")\n";
        }
    }

    // 2. If not logged in, ask for login credentials
    if (index == -1) {
        string mID, pass;
        cout << "Enter Member ID (or '0' to go back): ";
        cin >> mID;
        cin.ignore(10000, '\n');
        if (mID == "0") return;
        mID = toUpperCase(mID);

        int foundIndex = searchMember(members, mID);
        if (foundIndex != -1) {
            cout << "Enter Password to access PRs: ";
            cin >> pass;
            cin.ignore(10000, '\n');

            if (members[foundIndex].password == pass) {
                index = foundIndex;
            }
            else {
                cout << "Incorrect password. Access denied.\n";
                return;
            }
        }
        else {
            cout << "Member not found.\n";
            return;
        }
    }

    // 3. PR Management Menu
    int choice;
    do {
        cout << "\n--- " << members[index].name << "'s PRs ---\n";
        cout << "1. Bench Press: " << members[index].benchPressPR << " kg\n";
        cout << "2. Deadlift:    " << members[index].deadliftPR << " kg\n";
        cout << "3. Squat:       " << members[index].squatPR << " kg\n";
        cout << "4. Return to Main Menu\n";
        cout << "Which PR would you like to update? (1-4): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        else {
            cin.ignore(10000, '\n');
        }

        if (choice >= 1 && choice <= 3) {
            double newPR;

            while (true) {
                cout << "Enter your new heaviest weight (in kg): ";
                cin >> newPR;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Error: Numbers only! Please try again.\n";
                }
                else if (newPR <= 0) {
                    cin.ignore(10000, '\n');
                    cout << "Error: Weight must be greater than 0 kg.\n";
                }
                else {
                    cin.ignore(10000, '\n');
                    break;
                }
            }

            if (choice == 1) members[index].benchPressPR = newPR;
            else if (choice == 2) members[index].deadliftPR = newPR;
            else if (choice == 3) members[index].squatPR = newPR;

            cout << "PR updated successfully! Keep pushing those limits!\n";
        }
        else if (choice != 4) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 4);
}