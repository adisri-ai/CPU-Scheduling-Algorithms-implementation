#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    int priority;
    int turnaround;
    int wait;
    int start;
    int end;
};
struct cmp {
    bool operator()(Process& a, Process& b) {
        if (a.remaining != b.remaining)
            return a.remaining > b.remaining;
        return a.arrival > b.arrival;
    }
};
void find(vector<Process>& v) {
    int n = v.size();
    int curr = 0, completed = 0;
    int total_waiting = 0, total_turnaround = 0;
    priority_queue<Process, vector<Process>, cmp> pq;
    vector<Process> order;
    vector<Process>finals;
    vector<int>times;
    for (auto &p : v) {
        p.remaining = p.burst;
        p.start = -1;
    }
    cout << "\n---- Gantt Chart ---" << endl;
    while (completed < n) {
        for (auto &p : v) {
            if (p.arrival == curr) pq.push(p);
        }
        if (pq.empty()) {
            cout << " Idle |";
            curr++;
            continue;
        }
        Process x = pq.top();
        pq.pop();
        if (x.start == -1) x.start = curr;
        if(order.size()==0 || order.back().id != x.id) cout << " P" << x.id << " |";
        x.remaining--;
        curr++;
        if (x.remaining == 0) {
            x.end = curr;
            x.turnaround = x.end - x.arrival;
            x.wait = x.turnaround - x.burst;
            total_waiting += x.wait;
            total_turnaround += x.turnaround;
            completed++;
            finals.push_back(x);
        }
        else pq.push(x);
        if(order.size() && order.back().id == x.id){
           times.back() = curr;
        }
        else{
          order.push_back(x);
          times.push_back(curr);
        }
    }
    cout<<endl;
    curr = 0;
    int temp = 0;
    for(auto& p : order){
      cout<<setw(5)<<times[temp];
      temp++;
    }
    cout << endl << "------------" << endl;
    cout << left
         << setw(10) << "PID"
         << setw(15) << "Arrival"
         << setw(15) << "Burst"
         << setw(15) << "Waiting"
         << setw(15) << "Turnaround" << endl;
    for (auto& p : finals) {
        cout << left
             << setw(10) << p.id
             << setw(15) << p.arrival
             << setw(15) << p.burst
             << setw(15) << p.wait
             << setw(15) << p.turnaround << endl;
    }

    cout << "\nAverage Waiting Time: "
         << (float)total_waiting / n << endl;
    cout << "Average Turnaround Time: "
         << (float)total_turnaround / n << endl;
}
bool func(Process& a, Process& b) {
    if (a.arrival != b.arrival) return a.arrival < b.arrival;
    if (a.burst != b.burst) return a.priority > b.priority;
    return a.id < b.id;
}
int main() {
    cout << "Enter number of process: ";
    int n;
    cin >> n;
    vector<Process> v(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter id , burst , arrival , priority for process " << i + 1 << endl;
        cin >> v[i].id >> v[i].burst >> v[i].arrival >> v[i].priority;
    }
    sort(v.begin(), v.end(), func);
    find(v);
    return 0;
}

