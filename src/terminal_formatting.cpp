#include <sys/ioctl.h>
#include <unistd.h>

int getTerminalWidth() {
    struct winsize w{};

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1 || w.ws_col == 0) {
        return 80;  // Fallback width
    }

    return w.ws_col;
}