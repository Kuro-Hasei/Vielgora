#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

#include "Tampilan/menu.h"
#include "Tampilan/Tampilan.h"
#include "Tampilan/Procedure.h"

int main() {
    fullscreen();
    disableScrollBar();
    system("color 72");
    setConsoleFont(10,25,L"Cascadia Code Bold");
    apk();
}
