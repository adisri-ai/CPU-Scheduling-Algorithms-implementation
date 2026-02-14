#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
using namespace std;

struct Process{
    int id;
    int arrival;
    int burst;
    int priority;
    int turnaround;
    int wait;
    int start;
    int remaining;
    int end;
};
bool func(const Process& a , const Process& b){
    if(a.arrival != b.arrival) return a.arrival < b.arrival;
    return a.id < b.id;
}
void find(vector<Process>& v){
    int n = v.size();
    int curr = 0, idx = 0, completed = 0;
    int total_waiting = 0, total_turnaround = 0;
    int quantum = 2;
    for(auto& p : v){
        p.start = -1;
        p.remaining = p.burst;
    }
    deque<int> dq;
    vector<Process> order;
    vector<Process> finals;
    queue<int> q;
    cout << "\n--- Gantt Chart ---\n";
    while(completed < n){
        if(dq.empty() && idx < n && curr < v[idx].arrival){
            cout << " Idle |";
            curr = v[idx].arrival;
        }

        while(idx < n && v[idx].arrival <= curr){
            dq.push_back(idx++);
        }
        if(dq.empty()) continue;
        int i = dq.front();
        dq.pop_front();
        if(v[i].start == -1) v[i].start = curr;
        int k = min(v[i].remaining, quantum);
        v[i].remaining -= k;
        cout << " P" << v[i].id << " |";
        order.push_back(v[i]);
        q.push(k);
        curr += k;
        while(idx < n && v[idx].arrival <= curr){
            dq.push_back(idx++);
        }
        if(v[i].remaining == 0){
            v[i].end = curr;
            v[i].turnaround = v[i].end - v[i].arrival;
            v[i].wait = v[i].turnaround - v[i].burst;
            total_waiting += v[i].wait;
            total_turnaround += v[i].turnaround;
            finals.push_back(v[i]);
            completed++;
        } else {
            dq.push_back(i);
        }
    }
    cout << endl;
    curr = 0;
    for(auto &p : order){
        if(curr < p.arrival) curr = p.arrival;
        int k = q.front();
        q.pop();
        cout << setw(5) << curr;
        curr += k;
    }
    cout << "\n-----------\n\n";
    cout << left
         << setw(10) << "PID"
         << setw(15) << "Arrival"
         << setw(15) << "Burst"
         << setw(15) << "Waiting"
         << setw(15) << "Turnaround" << endl;
    for(auto &p : finals){
        cout << left
             << setw(10) << p.id
             << setw(15) << p.arrival
             << setw(15) << p.burst
             << setw(15) << p.wait
             << setw(15) << p.turnaround << endl;
    }
    cout << "\nAverage Waiting Time: " << (float)total_waiting / n << endl;
    cout << "Average Turnaround Time: " << (float)total_turnaround / n << endl;
}

int main(){
    int n;
    cout << "Enter the number of process: ";
    cin >> n;
    vector<Process> v(n);
    for(int i = 0; i < n; ++i){
        cout << "Enter id , burst , arrival, priority for process " << i + 1 << endl;
        cin >> v[i].id >> v[i].burst >> v[i].arrival >> v[i].priority;
    }
    sort(v.begin(), v.end(), func);
    find(v);
    return 0;
}