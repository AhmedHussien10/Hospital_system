#include <iostream>
using namespace std;

const int MAX_SPECIALIZATION = 20;
const int MAX_QUEUE = 5;

struct patient {
    string name;
    int status;
    int spec;
};

patient patients[MAX_SPECIALIZATION + 1][MAX_QUEUE];
int queue_length[MAX_SPECIALIZATION + 1] = {0};

void shift_right(int spec) {
    int len = queue_length[spec];

    for (int i = len - 1; i >= 0; --i) {
        patients[spec][i + 1] = patients[spec][i];
    }
    queue_length[spec]++;
}

void shift_left(int spec) {
    int len = queue_length[spec];

    for (int i = 0; i < len - 1; ++i) {
        patients[spec][i] = patients[spec][i + 1];
    }
    queue_length[spec]--;
}

bool add_patient() {
    patient p;
    cout << "Enter specialization, name, status (0 or 1): ";
    cin >> p.spec >> p.name >> p.status;

    int pos = queue_length[p.spec];

    if (pos >= MAX_QUEUE) {
        cout << "Sorry, we can't add more patients for this specialization." << endl;
        return false;
    }

    if (p.status == 0) {
        patients[p.spec][pos] = p;
        queue_length[p.spec]++;
    } else {
        shift_right(p.spec);
        patients[p.spec][0] = p;
    }

    return true;
}

void print_patients() {
    for (int spec = 1; spec <= MAX_SPECIALIZATION; ++spec) {
        int len = queue_length[spec];
        if (len > 0) {
            cout << "Specialization " << spec << " (" << len << " patients):" << endl;
            for (int i = 0; i < len; ++i) {
                cout << "Name: " << patients[spec][i].name << ", Status: " << patients[spec][i].status << endl;
            }
            cout << endl;
        }
    }
}

bool get_next_patient() {
    int spec;
    cout << "Enter specialization to get next patient: ";
    cin >> spec;

    if (queue_length[spec] == 0) {
        cout << "No patients at the moment. Have rest, Dr." << endl;
        return false;
    }

    patient gp = patients[spec][0];
    cout << gp.name << ", please go with the Dr." << endl;
    shift_left(spec);
    return true;
}

int menu() {
    int choice = -1;

    while (choice == -1) {
        cout << "\nEnter your choice:\n";
        cout << "1) Add new patient\n";
        cout << "2) Print all patients\n";
        cout << "3) Get next patient\n";
        cout << "4) Exit\n";

        cin >> choice;

        if (!(1 <= choice && choice <= 4)) {
            cout << "Invalid choice. Try again\n";
            choice = -1; // loop keeps working
        }
    }
    return choice;
}

void hospital_system() {
    while (true) {
        int choice = menu();

        switch (choice) {
            case 1:
                add_patient();
                break;
            case 2:
                print_patients();
                break;
            case 3:
                get_next_patient();
                break;
            case 4:
                cout << "Exiting program." << endl;
                return;
        }
    }
}

int main() {
    hospital_system();
    return 0;
}
