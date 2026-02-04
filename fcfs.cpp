#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;

struct Process{
    int id;
    int arrival;
    int burst;
    int priority;
    int turnaround;
    int wait;
    int start;
    int end;
};

void find(vector<Process>& v){
    int n = v.size();
    int curr = 0;
    int total_waiting = 0;
    int total_turnaround = 0;

    cout << "\n---- Gantt Chart ---" << endl;
    for(int i = 0; i < n; ++i){
        if(curr < v[i].arrival){
            cout << " Idle |";
            curr = v[i].arrival;
        }
        v[i].start = curr;
        v[i].end = curr + v[i].burst;
        v[i].turnaround = v[i].end - v[i].arrival;
        v[i].wait = v[i].turnaround - v[i].burst;

        total_waiting += v[i].wait;
        total_turnaround += v[i].turnaround;

        curr = v[i].end;
        cout << " P" << v[i].id << " |";
    }
    cout << endl;

    curr = 0;
    for(int i = 0; i < n; ++i){
        if(curr < v[i].arrival){
            curr = v[i].arrival;
        }
        curr += v[i].burst;
        cout << setw(5) << curr;
    }
    cout << "\n------------\n" << endl;
    cout << left
         << setw(10) << "PID"
         << setw(15) << "Arrival"
         << setw(15) << "Burst"
         << setw(15) << "Waiting"
         << setw(15) << "Turnaround" << endl;

    for(int i = 0; i < n; ++i){
        cout << left
             << setw(10) << v[i].id
             << setw(15) << v[i].arrival
             << setw(15) << v[i].burst
             << setw(15) << v[i].wait
             << setw(15) << v[i].turnaround << endl;
    }

    float avg_waiting = (float) total_waiting / n;
    float avg_turnaround = (float) total_turnaround / n;

    cout << "\nAverage Waiting Time: " << avg_waiting << endl;
    cout << "Average Turnaround Time: " << avg_turnaround << endl;
}

bool func(Process& a, Process& b){
    if(a.arrival != b.arrival) return a.arrival < b.arrival;
    return a.id < b.id;
}

int main(){
    cout << "Enter number of process: ";
    int n;
    cin >> n;

    vector<Process> v(n);
    for(int i = 0; i < n; ++i){
        cout << "Enter id , burst , arrival , priority for process " << i + 1 << endl;
        cin >> v[i].id >> v[i].burst >> v[i].arrival >> v[i].priority;
    }

    sort(v.begin(), v.end(), func);
    find(v);

    return 0;
}
