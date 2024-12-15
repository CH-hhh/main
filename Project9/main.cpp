#include "WorkerManager.h"

int main() {
    WorkerManager wm;
    int choice;
    do {
        wm.showMenu();
        std::cout << "请输入您的选择：";
        std::cin >> choice;
        switch (choice) {
        case 0:
            std::cout << "退出管理程序\n";
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
            std::cout << "无效选择，请重新输入\n";
            break;
        }
    } while (choice != 0);
    return 0;
}