#include <ncurses.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
void displayArt(WINDOW * art, int y, int x) {

std::string artwork = R"(
  _______  _                               _____  _                                                ___  
 |__   __|| |                             / ____|| |                                              / _ \ 
    | |   | |__    ___  _ __ ___    ___  | |     | |__    __ _  _ __    __ _   ___  _ __  __   __| | | |
    | |   | '_ \  / _ \| '_ ` _ \  / _ \ | |     | '_ \  / _` || '_ \  / _` | / _ \| '__| \ \ / /| | | |
    | |   | | | ||  __/| | | | | ||  __/ | |____ | | | || (_| || | | || (_| ||  __/| |     \ V / | |_| |
    |_|   |_| |_| \___||_| |_| |_| \___|  \_____||_| |_| \__,_||_| |_| \__, | \___||_|      \_/   \___/ 
                                                                        __/ |                           
                                                                       |___/                            
)";

    int yPos = 0;
    std::stringstream ss(artwork);
    std::string line;
    while (std::getline(ss,line)) {
        mvwprintw(art, y + yPos, x, "%s", line.c_str());
        yPos++;
    }
}

std::string menu_options(WINDOW * win) {

    std::vector<std::string> themes;
    std::ifstream in("/home/mattw/config-switcher/src/themes.txt");
    std::string theme;

    if (in.fail()) {
        std::cerr << "Could not read the themes file\n";
        exit(EXIT_FAILURE);
    }

    while (in >> theme) {
        themes.push_back(theme);
    }

    int choice;
    int highlight = 0;
    for (;;) {

        for (int i = 0, y_pos = 1; i < static_cast<int>(themes.size()); i++, y_pos+=2) {
            if (i == highlight) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, y_pos, 1, "%s", themes[i].c_str());
            wattroff(win, A_REVERSE);
        }
        choice = wgetch(win);

        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight == -1) {
                    highlight = 0;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == static_cast<int>(themes.size())) {
                    highlight = static_cast<int>(themes.size() - 1);
                }
                break; 
            default:
                break;
        }
        if (choice == 10) {
            break;
        }
    }
    std::string selected_theme = themes[highlight];
    return selected_theme;
    // printw("Selected Theme: %s", selected_theme.c_str());
}
int main(int argc, char **argv){

    initscr();
    cbreak();

    int maxY, maxX;
    
    getmaxyx(stdscr, maxY, maxX);
    int menuHeight = maxY / 1.5; 
    int menuWidth = maxX / 3;

    // Creating The windows
    WINDOW * menu = newwin(menuHeight, menuWidth, 1, 1);
    WINDOW * preview = newwin(menuHeight, maxX - menuWidth - 1, 1, menuWidth + 1);
    WINDOW * artwork = newwin(maxY - menuHeight - 1, maxX - 1, menuHeight + 1, 1);

    // Refresh so the windows are recognized
    refresh();

    box(menu, 0, 0);
    box(preview, 0, 0);
    box(artwork,0,0);

    mvwprintw(menu, 0,1, " Config Switcher v0 ");
    mvwprintw(preview, 0, 1, " Preview: WIP ");

    displayArt(artwork, (maxY - menuHeight - 1) / 3, 4); 
    wrefresh(preview);
    wrefresh(artwork);

    keypad(menu, true);
    wmove(menu,1,1);
    wrefresh(menu);
    std::string theme = menu_options(menu);


    endwin();

    std::ofstream out("tmp.txt");
    out << theme; 
    out.close();
    return 0;
}
