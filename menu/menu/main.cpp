#include "DIYACMenu.hpp"

int main() {
    DIYACMenu menu;
    while(menu.isOpen()) {
        menu.update();
        menu.render();
        menu.lateUpdate();
    }
}
