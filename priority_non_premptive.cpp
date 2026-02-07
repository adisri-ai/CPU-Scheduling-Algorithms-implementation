#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
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
  int end;
};
struct cmp{
  bool operator()(Process& a , Process& b){
    if(a.priority != b.priority){
        return a.priority < b.priority;
    }
    return a.arrival > b.arrival;
  }
};
bool func(Process& a , Process& b){
   if(a.arrival != b.arrival) return a.arrival < b.arrival;
   return a.id < b.id;
}
void find(vector<Process>& v){
  int n = v.size();
  int curr = 0; int idx = 0;
  int total_waiting = 0; int total_turnaround = 0;
  priority_queue<Process , vector<Process> , cmp>pq;
  vector<Process>order;
  cout<<"\n--- Gantt Chart ---"<<endl;
  while(idx<n || !pq.empty()){
     if(pq.empty() && curr < v[idx].arrival){
        cout<<" Idle |";
        curr = v[idx].arrival;
     }
     while(idx < n && v[idx].arrival <=curr){
         pq.push(v[idx]);
         idx++;
     }
     Process p = pq.top();
     pq.pop();
     p.start = curr;
     p.end = curr + p.burst;
     p.turnaround = p.end - p.arrival;
     p.wait = p.turnaround - p.burst;
     total_waiting += p.wait;
     total_turnaround += p.turnaround;
     curr = p.end;
     order.push_back(p);
     cout<<" P"<<p.id<<" |";
  }
  cout<<endl;
  curr = 0;
  for(auto &p :  order){
     if(curr < p.arrival) curr = p.arrival;
     curr+= p.burst;
     cout<<setw(5)<<curr;
  }
  cout<<"\n-----------\n"<<endl;
  cout<<left
      <<setw(10)<<"PID"
      <<setw(15)<<"Arrival"
      <<setw(15)<<"Burst"
      <<setw(15)<<"Waiting"
      <<setw(15)<<"Turnaround"<<endl;
   for(auto &p : order){
     cout<<left
         <<setw(10)<<p.id
         <<setw(15)<<p.arrival
         <<setw(15)<<p.burst
         <<setw(15)<<p.wait
         <<setw(15)<<p.turnaround<<endl;
   }
   cout<<"\nAverage Waiting Time: "<<(float) total_waiting/n <<endl;
   cout<<"\nAverage Turnaround Time: "<<(float) total_turnaround/n <<endl;
}
int main(){
   int n;
   cout<<"Enter the number of process: ";
   cin>>n;
   vector<Process>v(n);
   for(int i=0 ; i<n ; ++i){
      cout<<"Enter id , burst , arrival, priority for process"<<i+1<<endl;
      cin>>v[i].id>>v[i].burst>>v[i].arrival>>v[i].priority;
   }
   sort(v.begin() , v.end() , func);
   find(v);
   return 0;
}
