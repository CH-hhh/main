#ifndef WORKERMANAGER_H
#define WORKERMANAGER_H

#include <iostream>
#include <vector>
#include <string>

class Worker {
public:
    int id;
    std::string name;
    int deptId;
    Worker(int id, std::string name, int deptId);
    virtual void showInfo() const = 0;
    virtual ~Worker() = default;
};

class Employee : public Worker {
public:
    Employee(int id, std::string name, int deptId);
    void showInfo() const override;
};

class Manager : public Worker {
public:
    Manager(int id, std::string name, int deptId);
    void showInfo() const override;
};

class Boss : public Worker {
public:
    Boss(int id, std::string name, int deptId);
    void showInfo() const override;
};

class WorkerManager {
private:
    std::vector<Worker*> workers;
    void save() const;

public:
    WorkerManager();
    ~WorkerManager();
    void showMenu() const;
    void addWorker();
    void showWorkers() const;
    void deleteWorker();
    void modifyWorker();
    void findWorker() const;
    void sortWorkers();
    void clearWorkers();
};

#endif // WORKERMANAGER_H