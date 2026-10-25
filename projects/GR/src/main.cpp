#include <fxcg/keyboard.h>
 
int main() {
    int key;

    while (1) {
        GetKey(&key);
        
        

        if (key == KEY_CTRL_EXE) {
            break;
        }
    }
 
    return 0;
}
