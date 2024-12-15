#include "WorkerManager.h"
#include <fstream>
#include <algorithm>

using namespace std;

// Worker class implementation
Worker::Worker(int id, std::string name, int deptId) : id(id), name(name), deptId(deptId) {}

// Employee class implementation
Employee::Employee(int id, std::string name, int deptId) : Worker(id, name, deptId) {}
void Employee::showInfo() const {
    cout << "ְ����ţ�" << id << " ������" << name << " ���ű�ţ�" << deptId << " ְλ����ͨԱ��\nְ����ɾ�����������\n";
}

// Manager class implementation
Manager::Manager(int id, std::string name, int deptId) : Worker(id, name, deptId) {}
void Manager::showInfo() const {
    cout << "ְ����ţ�" << id << " ������" << name << " ���ű�ţ�" << deptId << " ְλ������\nְ������ϰ彻�������񣬲��·������Ա��\n";
}

// Boss class implementation
Boss::Boss(int id, std::string name, int deptId) : Worker(id, name, deptId) {}
void Boss::showInfo() const {
    cout << "ְ����ţ�" << id << " ������" << name << " ���ű�ţ�" << deptId << " ְλ���ϰ�\nְ�𣺹���˾��������\n";
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
    cout << "0.�˳��������\n1.����ְ����Ϣ\n2.��ʾְ����Ϣ\n3.ɾ����ְְ��\n4.�޸�ְ����Ϣ\n5.����ְ����Ϣ\n6.���ձ������\n7.��������ĵ�\n";
}

void WorkerManager::addWorker() {
    int num, id, deptId;
    string name;
    cout << "���������ְ��������";
    cin >> num;
    for (int i = 0; i < num; ++i) {
        cout << "������ְ����ţ�";
        cin >> id;
        cout << "������ְ��������";
        cin >> name;
        cout << "��ѡ��ְ�����ű�ţ�1-��ͨԱ�� 2-���� 3-�ϰ壩��";
        cin >> deptId;
        switch (deptId) {
        case 1: workers.push_back(new Employee(id, name, deptId)); break;
        case 2: workers.push_back(new Manager(id, name, deptId)); break;
        case 3: workers.push_back(new Boss(id, name, deptId)); break;
        default: cout << "��Ч�Ĳ��ű�š�\n"; break;
        }
    }
    save();
}

void WorkerManager::showWorkers() const {
    for (const auto& worker : workers) worker->showInfo();
}

void WorkerManager::deleteWorker() {
    int id;
    cout << "������ɾ��ְ���ı�ţ�";
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
        cout << "ɾ���ɹ�\n";
    }
    else {
        cout << "δ�ҵ����Ϊ" << id << "��ְ��\n";
    }
}

void WorkerManager::modifyWorker() {
    int id, newId, deptId;
    string name;
    cout << "������Ҫ�޸ĵ�ְ����ţ�";
    cin >> id;
    auto it = find_if(workers.begin(), workers.end(), [id](Worker* worker) { return worker->id == id; });
    if (it != workers.end()) {
        cout << "�������µı�ţ�";
        cin >> newId;
        cout << "�������µ�������";
        cin >> name;
        cout << "��ѡ���µĲ��ű�ţ�1-��ͨԱ�� 2-���� 3-�ϰ壩��";
        cin >> deptId;
        delete* it;
        switch (deptId) {
        case 1: *it = new Employee(newId, name, deptId); break;
        case 2: *it = new Manager(newId, name, deptId); break;
        case 3: *it = new Boss(newId, name, deptId); break;
        default: cout << "��Ч�Ĳ��ű�š�\n"; return;
        }
        save();
        cout << "�޸ĳɹ�\n";
    }
    else {
        cout << "δ�ҵ����Ϊ" << id << "��ְ��\n";
    }
}

void WorkerManager::findWorker() const {
    int choice, id;
    string name;
    cout << "��ѡ����ҷ�ʽ��1-����Ų��� 2-���������ң�";
    cin >> choice;
    if (choice == 1) {
        cout << "������ְ����ţ�";
        cin >> id;
        auto it = find_if(workers.begin(), workers.end(), [id](Worker* worker) { return worker->id == id; });
        if (it != workers.end()) {
            (*it)->showInfo();
        }
        else {
            cout << "δ�ҵ����Ϊ" << id << "��ְ��\n";
        }
    }
    else if (choice == 2) {
        cout << "������ְ��������";
        cin >> name;
        auto it = find_if(workers.begin(), workers.end(), [&name](Worker* worker) { return worker->name == name; });
        if (it != workers.end()) {
            (*it)->showInfo();
        }
        else {
            cout << "δ�ҵ�����Ϊ" << name << "��ְ��\n";
        }
    }
    else {
        cout << "��Ч�Ĳ��ҷ�ʽ��\n";
    }
}

void WorkerManager::sortWorkers() {
    sort(workers.begin(), workers.end(), [](Worker* a, Worker* b) { return a->id < b->id; });
    save();
    cout << "�������\n";
}

void WorkerManager::clearWorkers() {
    char confirmation;
    cout << "ȷ��Ҫ������м�¼�𣿴˲������ɻָ���(y/n): ";
    cin >> confirmation;
    if (confirmation == 'y' || confirmation == 'Y') {
        for (auto worker : workers) delete worker;
        workers.clear();
        save();
        cout << "���м�¼�����\n";
    }
    else {
        cout << "������ȡ��\n";
    }
}

void WorkerManager::save() const {
    ofstream ofs("workers.txt", ios::trunc);
    for (const auto& worker : workers) {
        ofs << worker->id << " " << worker->name << " " << worker->deptId << endl;
    }
}