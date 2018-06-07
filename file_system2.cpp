#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <list>
#include <cstring>
#include <vector>

using namespace std;

typedef struct dir dir;
typedef struct file file;
struct file {
    string name;
    dir *parent;
    int omode;
    bool opened = false;
};
struct dir {
    string name;
    dir* parent_dir;
    list<file*> files;
    list<dir*> dirs;
};

struct user {
    string name;
} current_user, root;

dir rootdir{
        .name= "",
        .parent_dir= nullptr};


dir current_dir;

void show_man();

void initialize();

void mkdir();

void mkdirp();

void dedir();

void dedirp();

void ls();
void lsp();

string get_path(dir directory);

dir* get_dir(const string &absolute_path);

file* get_file(const string &absolute_path);

vector<string> split(const string &str, const string &delim);


int main() {
    initialize();

    while (true) {
        cout << current_user.name <<"$" << get_path(current_dir) << "/%:";
        string opt;
        cin >> opt;
        if (opt == "man") {
            show_man();
        } else if (opt == "pwd") {
            cout << get_path(current_dir);
        } else if (opt == "mkdir") {
            mkdir();
        } else if (opt == "mkdirp") {
            mkdirp();
        } else if (opt == "dedir") {
            dedir();
        }else if (opt == "dedirp") {
            dedirp();
        }else if (opt == "ls") {
            ls();
        }else if (opt == "lsp") {
            lsp();
        }else if (opt == "exit") {
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
    root.name = "root";
    current_user = root;
}

string get_path(dir directory) {
    string current_path = directory.name;
    dir *temp_dir = &directory;
    //memcpy(&temp_dir, &current_dir, sizeof(temp_dir));
    while (temp_dir->parent_dir != nullptr) {
        temp_dir = temp_dir->parent_dir;
        current_path = temp_dir->name.append("/").append(current_path);
    }
    return current_path;
}

void mkdir() {
    string directory_name;
    cin >> directory_name;
    dir new_dir;
    new_dir.name = directory_name;
    new_dir.parent_dir = &current_dir;
    current_dir.dirs.push_back(&new_dir);
}

void mkdirp() {
    string directory_name, path;
    cin >> path;
    cin >> directory_name;
    dir new_dir;
    new_dir.name = directory_name;
    dir* parent_dir = get_dir(path);
    new_dir.parent_dir = parent_dir;
    current_dir.dirs.push_back(&new_dir);
}

void dedir(){
    string directory_name;
    cin >> directory_name;
    for (dir* d: current_dir.dirs){
        if (d->name == directory_name){
            current_dir.dirs.remove(d);
            return;
        }
    }
}

void dedirp(){
    string directory_name, path;
    cin >> path;
    cin >> directory_name;
    dir* thisdir = get_dir(path);
    for (dir* d: thisdir->dirs){
        if (d->name == directory_name){
            thisdir->dirs.remove(d);
            return;
        }
    }
}

void ls(){
    for (dir* d: current_dir.dirs){
        cout << d->name << " ";
    }
    for (file* f: current_dir.files){
        cout << f->name << " ";
    }
    cout << endl;
}
void lsp(){
    string path;
    cin >> path;
    dir* thisdir = get_dir(path);
    for (dir* d: thisdir->dirs){
        cout << d->name << " ";
    }
    for (file* f: thisdir->files){
        cout << f->name << " ";
    }
    cout << endl;
}

file* get_file(const string &absolute_path) {
    vector<string> paths = split(absolute_path, "/");
    dir* thisdir = &rootdir;
    for (int i = 0; i < paths.size() - 1; i++) {
        for (dir* d: thisdir->dirs) {
            if (d->name == paths[i]) {
                thisdir = d;
                continue;
            }
        }
    }
    for (file* f: thisdir->files) {
        if (f->name == paths[-1]) {
            return f;
        }
    }
}

dir* get_dir(const string &absolute_path) {
    vector<string> paths = split(absolute_path, "/");
    dir* thisdir = &rootdir;
    for (int i = 0; i < paths.size(); i++) {
        for (dir* d: thisdir->dirs) {
            if (d->name == paths[i]) {
                thisdir = d;
                continue;
            }
        }
    }
    return thisdir;
}

vector<string> split(const string &str, const string &delim) {
    vector<string> res;
    if ("" == str) return res;
    //先将要切割的字符串从string类型转换为char*类型
    char *strs = new char[str.length() + 1]; //不要忘了
    strcpy(strs, str.c_str());

    char *d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());

    char *p = strtok(strs, d);
    while (p) {
        string s = p; //分割得到的字符串转换为string类型
        res.push_back(s); //存入结果数组
        p = strtok(NULL, d);
    }

    return res;
}