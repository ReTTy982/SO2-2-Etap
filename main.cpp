#include <iostream>
#include <thread>
#include <mutex>
#include <ncurses.h>

using namespace std;

const int PHIL_LEN = 8;
mutex forks[PHIL_LEN];
mutex print_guard;
WINDOW* win[PHIL_LEN];
WINDOW* win_left[PHIL_LEN];
WINDOW* win_right[PHIL_LEN];
            

void philosopher(int id) {

 
// dishes = [ 1, 2, 3, 4]
// f1 - 1 dishes[0].lock()
// dishes.pop(0)
// f2 - dishes[0].lock()
//

    int left_fork = id;
    int right_fork = (id + 1) % PHIL_LEN;
    while(true){

        {
            lock_guard<mutex> lock(print_guard);
            werase(win[id]);
            box(win[id], 0, 0);
            wbkgd(win[id], COLOR_PAIR(2));
            mvwprintw(win[id], 1, 1, "Thinkng");
            wrefresh(win[id]);
        }     
        std::this_thread::sleep_for(chrono::seconds(3));

        
        {
            lock_guard<mutex> lock(print_guard);
            werase(win[id]);
            box(win[id], 0, 0);
            mvwprintw(win[id], 1, 1, "Hungry");
            wbkgd(win[id], COLOR_PAIR(1));
            wrefresh(win[id]);
        }

        if (id % 2 == 0 ){
            forks[right_fork].lock();
            {
                lock_guard<mutex> lock(print_guard);
                werase(win[id]);
                box(win_left[id],0,0);
                wbkgd(win_left[id],COLOR_PAIR(1));
                mvwprintw(win_left[id], 1, 1, " ");
                box(win_right[id],0,0);
                wbkgd(win_right[id], COLOR_PAIR(4));
                mvwprintw(win_right[id], 1, 1, "Right");
                wrefresh(win_right[id]);
                wrefresh(win_left[id]);
            }
            std::this_thread::sleep_for(chrono::seconds(2));

            forks[left_fork].lock();
            {
                lock_guard<mutex> lock(print_guard);
                werase(win[id]);
                box(win_left[id],0,0);
                wbkgd(win_left[id],COLOR_PAIR(4));
                mvwprintw(win_left[id], 1, 1, "Left");
                box(win_right[id],0,0);
                wbkgd(win_right[id], COLOR_PAIR(4));
                mvwprintw(win_right[id], 1, 1, "Right");
                wrefresh(win_right[id]);
                wrefresh(win_left[id]);
            }
        }
        else{
            forks[left_fork].lock(); 
            {
                lock_guard<mutex> lock(print_guard);
                werase(win[id]);
                box(win_left[id],0,0);
                wbkgd(win_left[id],COLOR_PAIR(4));
                mvwprintw(win_left[id], 1, 1, "Left");
                box(win_right[id],0,0);
                wbkgd(win_right[id], COLOR_PAIR(1));
                mvwprintw(win_right[id], 1, 1, " ");
                wrefresh(win_right[id]);
                wrefresh(win_left[id]);
            }

            std::this_thread::sleep_for(chrono::seconds(2));

            forks[right_fork].lock();
            {
                lock_guard<mutex> lock(print_guard);
                werase(win[id]);
                box(win_left[id],0,0);
                wbkgd(win_left[id],COLOR_PAIR(4));
                mvwprintw(win_left[id], 1, 1, "Left");
                box(win_right[id],0,0);
                wbkgd(win_right[id], COLOR_PAIR(4));
                mvwprintw(win_right[id], 1, 1, "Right");
                wrefresh(win_right[id]);
                wrefresh(win_left[id]);
            }
        }
        std::this_thread::sleep_for(chrono::seconds(2));
      
        {
            lock_guard<mutex> lock(print_guard);
            werase(win_left[id]);
            werase(win_right[id]);
            werase(win[id]);
            box(win[id], 0, 0);
            mvwprintw(win[id], 1, 1, "Eating");
            wbkgd(win[id], COLOR_PAIR(3));
            wrefresh(win[id]);
        }
        
        this_thread::sleep_for(chrono::seconds(2));

        forks[right_fork].unlock(); 
        forks[left_fork].unlock();  
    }
}

int main(){

initscr();
noecho();
start_color();
init_pair(1, COLOR_WHITE, COLOR_BLUE);
init_pair(2, COLOR_WHITE, COLOR_GREEN);
init_pair(3, COLOR_WHITE, COLOR_RED);
init_pair(4,COLOR_WHITE,COLOR_MAGENTA);
thread philosophers[PHIL_LEN];

// Statystyki
int starty = LINES - 5 -1;
int startx = COLS - 10 - 1;
WINDOW* legend = newwin(5,10,starty,startx);
werase(legend);
box(legend,0,0);

mvwprintw(legend,1,1,"test");
mvwprintw(legend,2,2,"test2");
wrefresh(legend);



for (int i = 0; i < PHIL_LEN; i++) {
    win[i] = newwin(3, 30, i * 3, 0);
    win_left[i] = newwin(3,15,i*3,0);
    win_right[i] = newwin(3,15,i*3,15);
    wrefresh(win[i]);
}



for (int i = 0; i < PHIL_LEN; i++) {
    philosophers[i] = thread(philosopher, i);
}

for (int i = 0; i < PHIL_LEN; i++) {
    philosophers[i].join();
}





int wait;
std::cin>>wait;

endwin();

return 0;
}

