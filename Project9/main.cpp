#include "WorkerManager.h"

int main() {
    WorkerManager wm;
    int choice;
    do {
        wm.showMenu();
        std::cout << "����������ѡ��";
        std::cin >> choice;
        switch (choice) {
        case 0:
            std::cout << "�˳��������\n";
            break;
        case 1:
            wm.addWorker();
            break;
        case 2:
            wm.showWorkers();
            break;
        case 3:
            wm.deleteWorker();
            break;
        case 4:
            wm.modifyWorker();
            break;
        case 5:
            wm.findWorker();
            break;
        case 6:
            wm.sortWorkers();
            break;
        case 7:
            wm.clearWorkers();
            break;
        default:
            std::cout << "��Чѡ������������\n";
            break;
        }
    } while (choice != 0);
    return 0;
}