#include "WorkerManager.h"
#include <fstream>
#include <algorithm>

using namespace std;

// Worker class implementation
Worker::Worker(int id, std::string name, int deptId) : id(id), name(name), deptId(deptId) {}

// Employee class implementation
Employee::Employee(int id, std::string name, int deptId) : Worker(id, name, deptId) {}
void Employee::showInfo() const {
    cout << "职工编号：" << id << " 姓名：" << name << " 部门编号：" << deptId << " 职位：普通员工\n职责：完成经理交给的任务\n";
}

// Manager class implementation
Manager::Manager(int id, std::string name, int deptId) : Worker(id, name, deptId) {}
void Manager::showInfo() const {
    cout << "职工编号：" << id << " 姓名：" << name << " 部门编号：" << deptId << " 职位：经理\n职责：完成老板交给的任务，并下发任务给员工\n";
}

// Boss class implementation
Boss::Boss(int id, std::string name, int deptId) : Worker(id, name, deptId) {}
void Boss::showInfo() const {
    cout << "职工编号：" << id << " 姓名：" << name << " 部门编号：" << deptId << " 职位：老板\n职责：管理公司所有事务\n";
}

// WorkerManager class implementation
WorkerManager::WorkerManager() {
    ifstream ifs("workers.txt");
    if (!ifs.is_open()) return;
    int id, deptId;
    string name;
    while (ifs >> id >> name >> deptId) {
        switch (deptId) {
        case 1: workers.push_back(new Employee(id, name, deptId)); break;
        case 2: workers.push_back(new Manager(id, name, deptId)); break;
        case 3: workers.push_back(new Boss(id, name, deptId)); break;
        }
    }
}

WorkerManager::~WorkerManager() {
    for (auto worker : workers) delete worker;
}

void WorkerManager::showMenu() const {
    cout << "0.退出管理程序\n1.增加职工信息\n2.显示职工信息\n3.删除离职职工\n4.修改职工信息\n5.查找职工信息\n6.按照编号排序\n7.清空所有文档\n";
}

void WorkerManager::addWorker() {
    int num, id, deptId;
    string name;
    cout << "请输入添加职工数量：";
    cin >> num;
    for (int i = 0; i < num; ++i) {
        cout << "请输入职工编号：";
        cin >> id;
        cout << "请输入职工姓名：";
        cin >> name;
        cout << "请选择职工部门编号（1-普通员工 2-经理 3-老板）：";
        cin >> deptId;
        switch (deptId) {
        case 1: workers.push_back(new Employee(id, name, deptId)); break;
        case 2: workers.push_back(new Manager(id, name, deptId)); break;
        case 3: workers.push_back(new Boss(id, name, deptId)); break;
        default: cout << "无效的部门编号。\n"; break;
        }
    }
    save();
}

void WorkerManager::showWorkers() const {
    for (const auto& worker : workers) worker->showInfo();
}

void WorkerManager::deleteWorker() {
    int id;
    cout << "请输入删除职工的编号：";
    cin >> id;
    auto it = remove_if(workers.begin(), workers.end(), [id](Worker* worker) {
        if (worker->id == id) {
            delete worker;
            return true;
        }
        return false;
        });
    if (it != workers.end()) {
        workers.erase(it, workers.end());
        save();
        cout << "删除成功\n";
    }
    else {
        cout << "未找到编号为" << id << "的职工\n";
    }
}

void WorkerManager::modifyWorker() {
    int id, newId, deptId;
    string name;
    cout << "请输入要修改的职工编号：";
    cin >> id;
    auto it = find_if(workers.begin(), workers.end(), [id](Worker* worker) { return worker->id == id; });
    if (it != workers.end()) {
        cout << "请输入新的编号：";
        cin >> newId;
        cout << "请输入新的姓名：";
        cin >> name;
        cout << "请选择新的部门编号（1-普通员工 2-经理 3-老板）：";
        cin >> deptId;
        delete* it;
        switch (deptId) {
        case 1: *it = new Employee(newId, name, deptId); break;
        case 2: *it = new Manager(newId, name, deptId); break;
        case 3: *it = new Boss(newId, name, deptId); break;
        default: cout << "无效的部门编号。\n"; return;
        }
        save();
        cout << "修改成功\n";
    }
    else {
        cout << "未找到编号为" << id << "的职工\n";
    }
}

void WorkerManager::findWorker() const {
    int choice, id;
    string name;
    cout << "请选择查找方式：1-按编号查找 2-按姓名查找：";
    cin >> choice;
    if (choice == 1) {
        cout << "请输入职工编号：";
        cin >> id;
        auto it = find_if(workers.begin(), workers.end(), [id](Worker* worker) { return worker->id == id; });
        if (it != workers.end()) {
            (*it)->showInfo();
        }
        else {
            cout << "未找到编号为" << id << "的职工\n";
        }
    }
    else if (choice == 2) {
        cout << "请输入职工姓名：";
        cin >> name;
        auto it = find_if(workers.begin(), workers.end(), [&name](Worker* worker) { return worker->name == name; });
        if (it != workers.end()) {
            (*it)->showInfo();
        }
        else {
            cout << "未找到姓名为" << name << "的职工\n";
        }
    }
    else {
        cout << "无效的查找方式。\n";
    }
}

void WorkerManager::sortWorkers() {
    sort(workers.begin(), workers.end(), [](Worker* a, Worker* b) { return a->id < b->id; });
    save();
    cout << "排序完成\n";
}

void WorkerManager::clearWorkers() {
    char confirmation;
    cout << "确定要清空所有记录吗？此操作不可恢复！(y/n): ";
    cin >> confirmation;
    if (confirmation == 'y' || confirmation == 'Y') {
        for (auto worker : workers) delete worker;
        workers.clear();
        save();
        cout << "所有记录已清空\n";
    }
    else {
        cout << "操作已取消\n";
    }
}

void WorkerManager::save() const {
    ofstream ofs("workers.txt", ios::trunc);
    for (const auto& worker : workers) {
        ofs << worker->id << " " << worker->name << " " << worker->deptId << endl;
    }
}