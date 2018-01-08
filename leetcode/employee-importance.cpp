// https://leetcode.com/problems/employee-importance/

/*
// Employee info
class Employee {
public:
    // It's the unique ID of each node.
    // unique id of this employee
    int id;
    // the importance value of this employee
    int importance;
    // the id of direct subordinates
    vector<int> subordinates;
};
*/
class Solution {
public:
    int getImportance(const vector<Employee*> &employees, int id) {
        auto e = findById(employees, id);
        if (e == nullptr) return 0;
        int ans = e->importance;
        for (int subordinateId : e->subordinates)
            ans += getImportance(employees, subordinateId);
        return ans;
    }
    
    static Employee* findById(const vector<Employee*> &employees, int id) {
        for (Employee* employee : employees)
            if (employee->id == id)
                return employee;
        return nullptr;
    }
};
