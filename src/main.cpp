#include <ncurses.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
void displayArt(WINDOW * art, int y, int x) {

std::string artwork = R"(

  _________  _  ______  __   ____  ___   ___  _______    ________  ______
 / ___/ __ \/ |/ / __/ / /  / __ \/ _ | / _ \/ __/ _ \  /_  __/ / / /  _/
/ /__/ /_/ /    / _/  / /__/ /_/ / __ |/ // / _// , _/   / / / /_/ // /  
\___/\____/_/|_/_/   /____/\____/_/ |_/____/___/_/|_|   /_/  \____/___/  

)";

    int yPos = 0;
    std::stringstream ss(artwork);
    std::string line;
    while (std::getline(ss,line)) {
        wattron(art, COLOR_PAIR(1));
        mvwprintw(art, y + yPos, x, "%s", line.c_str());
        wattroff(art,COLOR_PAIR(1));
        yPos++;
    }

}

void print_help() {
	attron(COLOR_PAIR(2));
	mvprintw(LINES - 2, 1, "Use PageUp and PageDown to scoll down or up a page of items");
	mvprintw(LINES - 1, 1, "Arrow Keys to navigate (Ctrl c to Exit)");
	attroff(COLOR_PAIR(2));
}
std::vector<std::string> get_themes(const std::string &path) {
    std::vector<std::string> themes;
    std::ifstream in(path);
    std::string theme;

    if (in.fail()) {
        std::cerr << "Error: Could not locate themes";
        exit(EXIT_FAILURE);
    }

    while (in >> theme) {
        themes.push_back(theme);
    }

    return themes;
}

std::string menu_options(WINDOW * win, const std::vector<std::string> &vec) {

    int choice;
    int highlight = 0;
    for (;;) {

        for (int i = 0, y_pos = 2; i < static_cast<int>(vec.size()); i++, y_pos+=2) {
            if (i == highlight) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, y_pos, 1, "%s", vec[i].c_str());
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
                if (highlight == static_cast<int>(vec.size())) {
                    highlight = static_cast<int>(vec.size() - 1);
                }
                break; 
            default:
                break;
        }
        if (choice == 10) {
            break;
        }
    }

    std::string selected_theme = vec[highlight];
    return selected_theme;
}

int main(int argc, char **argv){

    std::string themePath = argv[1];
    
    initscr();
    cbreak();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    int maxY, maxX;
    
    getmaxyx(stdscr, maxY, maxX);
    int menuHeight = maxY / 1.5; 
    int menuWidth = maxX / 3;

    // Creating The windows
    WINDOW * menu = newwin(menuHeight, menuWidth, 1, 1);
    WINDOW * options = newwin(menuHeight, maxX - menuWidth - 1, 1, menuWidth + 1);
    WINDOW * artwork = newwin(maxY - menuHeight - 3, maxX - 1, menuHeight + 1, 1);

    // Refresh so the windows are recognized
    refresh();

    box(menu, 0, 0);
    box(options, 0, 0);
    box(artwork,0,0);

    wattron(menu, A_BOLD);
    mvwprintw(menu, 0,1, " Select A Theme ");
    wattroff(menu, A_BOLD);

    displayArt(artwork, (((maxY - menuHeight - 1) / 2) /2) - 2, 4); 
    wrefresh(options);
    wrefresh(artwork);

    keypad(menu, true);
    keypad(options, true);
    curs_set(0);
    wrefresh(menu);

    print_help(); refresh();

    std::vector<std::string> themes = get_themes(themePath);
    std::string theme = menu_options(menu, themes);

    wattron(options, A_BOLD);
    mvwprintw(options, 0,1, " Select Your Window Manager ");
    wattroff(options, A_BOLD);

    std::vector<std::string> wms = {"Bspwm", "i3wm"};
    std::string wm = menu_options(options, wms);

    wclear(options); box(options,0,0);
    wattron(options, A_BOLD);
    mvwprintw(options, 0,1, " Select Your Terminal Emulator ");
    wattroff(options, A_BOLD);

    std::vector<std::string> terms = {"Alacritty", "Kitty"};
    std::string term = menu_options(options, terms);



    getch();

    endwin();

    std::ofstream out("tmp.txt");
    out << theme << "\n";
    out << wm << "\n";
    out << term << "\n";
    out.close();
    return 0;
}
