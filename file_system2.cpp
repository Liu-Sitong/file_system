#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <list>
#include <cstring>

using namespace std;

typedef struct dir {
    string name;
    dir *parent{};
    list *files{};
    list *dirs{};
} dir;

dir rootdir{
        .name= "",
        .parent= nullptr};


dir current_dir;

void show_man();

void initialize();

string get_path();


int main() {
    initialize();

    while (true) {
        cout << "root$" << current_path;
        string opt;
        cin >> opt;
        if (opt == "man") {
            show_man();
        } else if (opt == "pwd") {
            cout << current_dir.name;
        } else if (opt == "mkdir") {

        } else if (opt == "exit") {
            return 0;
        }
    }
}

void show_man() {
    cout << "Manual:" << endl;
    cout << "0) pwd (current work directory)" << endl;
    cout << "1) mkdir(p) (path) directory_name" << endl;
    cout << "2) dedir(p) (path) directory_name" << endl;
    cout << "3) search file_name" << endl;
    cout << "4) create(p) (path) file_name omode" << endl;
    cout << "5) cat(p) (path) file_name" << endl;
    cout << "6) delete(p) (path) file_name" << endl;
    cout << "7) write(p) (path) file_name buff wmode" << endl;
    cout << "8) reposition(p) (path) file_name pos" << endl;
    cout << "9) truncate(p) (path) file_name cnt" << endl;
    cout << "10) ls(p) (path)" << endl;
    cout << "11) open(p) (path) file_name" << endl;
    cout << "12) close(p) (path) file_name" << endl;
    cout << "13) regusr user_name password" << endl;
    cout << "14) delusr user_name [root only]" << endl;
    cout << "15) disusr" << endl;
    cout << "16) login user_name" << endl;
    cout << "17) lsfile" << endl;
    cout << "18) chmod(p) (path) file_name mode" << endl;
    cout << "19) exit" << endl;
}

void initialize() {
    current_dir = rootdir;
}

string get_path() {
    string current_path = current_dir.name;
    dir *temp_dir = &current_dir;
    //memcpy(&temp_dir, &current_dir, sizeof(temp_dir));
    while (temp_dir->parent != nullptr) {
        temp_dir = temp_dir->parent;
    }
    current_dir.parent;
}