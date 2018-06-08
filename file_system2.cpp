#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <list>
#include <cstring>
#include <vector>

using namespace std;

//typedef struct dir dir;
//typedef struct file file;
class file;

class dir;

class user;

class user {
public:
    string username;
    string password;
    list<file *> opened_files;
} root;

list<user *> userlist{&root};
user *current_user;

class file {
public:
    string name;
    dir *parent;
    int omode;
    user *creater;
    int position;
    string content;
};

class dir {
public:
    string name;
    dir *parent_dir;
    list<file *> files;
    list<dir *> dirs;
};


dir rootdir{
        .name= "",
        .parent_dir= nullptr};


dir *current_dir;

void show_man();

void initialize();

void mkdir(dir *directory);

void dedir(dir *directory);

void ls(dir *directory);

void cd();

void cdp(); // 这两个cd含义不同

void create(dir *directory);

void open(dir *directory);

void close(dir *directory);

void write(dir *directory);

void search(dir *directory, const string &file_name);

void cat(dir *directory);

void myDelete(dir *directory);

void reposition(dir *directory);

void truncate(dir *directory);

void chmod(dir *directory);

void lsfile();

void regusr();

void delusr();

void disusr();

void login();


string get_path(dir directory);

dir *get_dir(const string &absolute_path);

file *get_file(const string &absolute_path);

vector<string> split(const string &str, const string &delim);


int main() {
    initialize();

    while (true) {
        cout << current_user->username << "$" << get_path(*current_dir) << "/%:";
        string opt;
        cin >> opt;
        if (opt == "man") {
            show_man();
        } else if (opt == "pwd") {
            cout << get_path(*current_dir) << "/" << endl;
        } else if (opt == "mkdir") {
            mkdir(current_dir);
        } else if (opt == "mkdirp") {
            string path;
            cin >> path;
            dir *d = get_dir(path);
            if (nullptr != d) {
                mkdir(d);
            }
        } else if (opt == "dedir") {
            dedir(current_dir);
        } else if (opt == "dedirp") {
            string path;
            cin >> path;
            dir *d = get_dir(path);
            if (nullptr != d) {
                dedir(d);
            }
        } else if (opt == "ls") {
            ls(current_dir);
        } else if (opt == "lsp") {
            string path;
            cin >> path;
            dir *d = get_dir(path);
            if (nullptr != d) {
                ls(d);
            }
        } else if (opt == "cd") {
            cd();
        } else if (opt == "cdp") {
            cdp();
        } else if (opt == "create") {
            create(current_dir);
        } else if (opt == "createp") {
            string path;
            cin >> path;
            dir *d = get_dir(path);
            if (nullptr != d) {
                create(d);
            }
        } else if (opt == "search") {
            string file_name;
            cin >> file_name;
            search(&rootdir, file_name);
        } else if (opt == "open") {
            open(current_dir);
        } else if (opt == "openp") {
            string path;
            cin >> path;
            dir *d = get_dir(path);
            if (nullptr != d) {
                open(d);
            }
        } else if (opt == "close") {
            close(current_dir);
        } else if (opt == "closep") {
            string path;
            cin >> path;
            dir *d = get_dir(path);
            if (nullptr != d) {
                close(d);
            }
        } else if (opt == "reposition") {
            reposition(current_dir);
        } else if (opt == "repositionp") {
            string path;
            cin >> path;
            dir *d = get_dir(path);
            if (nullptr != d) {
                open(d);
            }
        } else if (opt == "truncate") {
            truncate(current_dir);
        } else if (opt == "truncatep") {
            string path;
            cin >> path;
            dir *d = get_dir(path);
            if (nullptr != d) {
                truncate(d);
            }
        } else if (opt == "chmod") {
            chmod(current_dir);
        } else if (opt == "chmodp") {
            string path;
            cin >> path;
            dir *d = get_dir(path);
            if (nullptr != d) {
                chmod(d);
            }
        } else if (opt == "cat") {
            cat(current_dir);
        } else if (opt == "catp") {
            string path;
            cin >> path;
            dir *d = get_dir(path);
            if (nullptr != d) {
                cat(d);
            }
        } else if (opt == "write") {
            write(current_dir);
        } else if (opt == "writep") {
            string path;
            cin >> path;
            dir *d = get_dir(path);
            if (nullptr != d) {
                write(d);
            }
        } else if (opt == "delete") {
            myDelete(current_dir);
        } else if (opt == "deletep") {
            string path;
            cin >> path;
            dir *d = get_dir(path);
            if (nullptr != d) {
                myDelete(d);
            }
        } else if (opt == "lsfile") {
            lsfile();
        } else if (opt == "regusr") {
            regusr();
        } else if (opt == "delusr") {
            delusr();
        } else if (opt == "disusr") {
            disusr();
        } else if (opt == "login") {
            login();
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
    current_dir = &rootdir;
    root.username = "root";
    root.password = "111";
    current_user = &root;
}

string get_path(dir directory) {
    string current_path = directory.name;
    dir temp_dir = directory;
    //memcpy(&temp_dir, &current_dir, sizeof(temp_dir));
    while (temp_dir.parent_dir != nullptr) {
        temp_dir = *temp_dir.parent_dir;
        current_path = temp_dir.name.append("/").append(current_path);
    }
    return current_path;
}

void mkdir(dir *directory) {
    string directory_name;
    cin >> directory_name;
    for (dir *d:directory->dirs) { // 检查是否存在
        if (d->name == directory_name) {
            cout << "directory already exists" << endl;
            return;
        }
    }

    dir *new_dir = new dir;
    new_dir->name = directory_name;
    new_dir->parent_dir = directory;
    directory->dirs.push_back(new_dir);
}

void dedir(dir *directory) {
    string directory_name;
    cin >> directory_name;
    for (dir *d: directory->dirs) {
        if (d->name == directory_name) {
            directory->dirs.remove(d);
            return;
        }
    }
}

void ls(dir *directory) {
    for (dir *d: directory->dirs) {
        cout << d->name << endl;
    }
    for (file *f: directory->files) {
        cout << f->name << endl;
    }
}


void cd() {
    string dir_name;
    cin >> dir_name;
    for (dir *d: current_dir->dirs) {
        if (d->name == dir_name) {
            current_dir = d;
            return;
        }
    }
    cout << "directory does not exist" << endl;
    return;
}

void cdp() {
    string path;
    cin >> path;
    dir *d;
    d = get_dir(path);
    if (nullptr != d) {
        current_dir = d;
    }
}

void create(dir *directory) {
    string file_name;
    int omode;
    cin >> file_name;
    cin >> omode;

    for (file *f:directory->files) { // 检查是否存在
        if (f->name == file_name) {
            cout << "file already exists" << endl;
            return;
        }
    }

    file *newfile = new file;
    newfile->name = file_name;
    newfile->omode = omode;
    newfile->parent = directory;
    newfile->creater = current_user;
    directory->files.push_back(newfile);
}

void open(dir *directory) {
    string file_name;
    cin >> file_name;
    for (file *f: directory->files) {
        if (f->name == file_name) {
            for (file *openf: current_user->opened_files) {
                if (f == openf) {
                    cout << "file already open" << endl;
                    return;
                }
            }
            current_user->opened_files.push_back(f);
            return;
        }
    }
    cout << "file does not exist" << endl;
}

void close(dir *directory) {
    string file_name;
    cin >> file_name;
    for (file *f : current_user->opened_files) {
        if (f->name == file_name) {
            current_user->opened_files.remove(f);
            return;
        }
    }
    cout << "file does not open" << endl;
}

void write(dir *directory) {
    string file_name, buff;
    int wmode;
    file *thisfile;
    string tail;
    cin >> file_name;
    cin >> buff;
    cin >> wmode;
    for (file *f: directory->files) {
        if (f->name == file_name) {
            for (file *openf: current_user->opened_files) {
                if (f == openf) {
                    if (f->omode == 2 || f->omode == 3 || f->omode == 6 || f->omode == 7) {
                        switch (wmode) {
                            case 0:
                                f->content.append(buff);
                                f->position = f->content.length();
                                break;
                            case 1:
                                if (f->content.length() > buff.length() + f->position) {
                                    tail = f->content.substr(f->position + buff.length(),
                                                             f->content.length());
                                }
                                f->content = f->content.substr(0, f->position).append(buff).append(tail);
                                f->position = f->content.length();
                                break;
                            case 2:
                                f->content = f->content.insert(f->position, buff);
                                f->position = f->content.length();
                                break;
                            default:
                                cout << "permission denied" << endl;
                                break;
                        }
                        return;
                    }
                    cout << "permission denied" << endl;
                    return;
                }
            }
            cout << "file does not open" << endl;
            return;
        }
    }
    cout << "file does not exist" << endl;
}

void search(dir *directory, const string &file_name) {
    for (file *f: directory->files) {
        if (f->name == file_name) {
            cout << get_path(*directory) << "/" << file_name << endl;
        }
    }
    for (dir *d: directory->dirs) {
        search(d, file_name);
    }
}

void cat(dir *directory) {
    string file_name;
    cin >> file_name;
    for (file *f: directory->files) {
        if (f->name == file_name) {
            for (file *openf: current_user->opened_files) {
                if (f == openf) {
                    if (f->omode == 4 || f->omode == 5 || f->omode == 6 || f->omode == 7) {
                        cout << f->content << endl;
                        return;
                    }
                    cout << "permission denied" << endl;
                }
            }
            cout << "file does not open" << endl;
        }
    }
    cout << "file does not exist" << endl;
}


void myDelete(dir *directory) {
    string file_name;
    cin >> file_name;
    for (file *f: current_user->opened_files) { // 如果已经打开就关了
        if (f->name == file_name) {
            directory->files.remove(f);
            break;
        }
    }
    for (file *f: directory->files) {
        if (f->name == file_name) {
            directory->files.remove(f);
            return;
        }
    }

    cout << "file does not exist" << endl;
}

void reposition(dir *directory) {
    string file_name;
    int pos;
    cin >> file_name;
    cin >> pos;
    for (file *f: directory->files) {
        if (f->name == file_name) {
            if (pos > f->content.length()) {
                cout << "reposition failed" << endl;
                return;
            }
            cout << "reposition ok" << endl;
            f->position = pos;
            return;
        }
    }
    cout << "file does not exist" << endl;
}

void truncate(dir *directory) {
    string file_name;
    int cnt;
    cin >> file_name;
    cin >> cnt;
    // 属于哪类操作？ 不属于
    for (file *f: directory->files) {
        if (f->name == file_name) {
            f->content = f->content.substr(0, cnt);
            return;
        }
    }
}

void chmod(dir *directory) {
    string file_name;
    int mode;
    cin >> file_name;
    cin >> mode;
    for (file *f: directory->files) {
        if (f->name == file_name) {
            f->omode = mode;
            return;
        }
    }
    cout << "file does not exist" << endl;
}

void lsfile() {
    for (user *u: userlist) {
        for (file *f: u->opened_files) {
            string path = get_path(*f->parent).empty() ?"/":get_path(*f->parent);
            cout << path << " " << f->name << " " << f->creater->username << " " << u->username << " "
                 << f->omode << endl;
        }
    }
}

void regusr() {
    string username, password;
    cin >> username;
    cin >> password;
    for (user *u: userlist) {
        if (u->username == username) {
            cout << "user already exists" << endl;
            return;
        }
    }
    user *u = new user;
    u->username = username;
    u->password = password;
    userlist.push_back(u);
    cout << "register ok" << endl;
}

void delusr() {
    string username;
    cin >> username;
    if (current_user != &root || username == "root") {
        cout << "permission denied" << endl;
        return;
    }
    for (user *u: userlist) {
        if (u->username == username) {
            userlist.remove(u);
            return;
        }
    }
    cout << "user does not exist" << endl;
}

void disusr() {
    if (current_user != &root) {
        cout << "permission denied" << endl;
        return;
    }
    for (user *u: userlist) {
        cout << u->username << endl;
    }
}

void login() {
    string username;
    cin >> username;
    for (user *u: userlist) {
        if (u->username == username) {
            cout << "password:";
            string password;
            cin >> password;
            if (password == u->password) {
                current_user = u;
                cout << "Login ok" << endl;
                return;
            }
            cout << "password wrong" << endl;
        }
    }
    cout << "user does not exist" << endl;
}

file *get_file(const string &absolute_path) {
    vector<string> paths = split(absolute_path, "/");
    dir *thisdir = &rootdir;
    for (int i = 0; i < paths.size() - 1; i++) {
        for (dir *d: thisdir->dirs) {
            if (d->name == paths[i]) {
                thisdir = d;
                continue;
            }
        }
        cout << "file does not exist" << endl;
        return nullptr;
    }
    for (file *f: thisdir->files) {
        if (f->name == paths[-1]) {
            return f;
        }
    }
    cout << "file does not exist" << endl;
}

dir *get_dir(const string &absolute_path) {
    vector<string> paths = split(absolute_path, "/");
    dir *thisdir = &rootdir;
    for (int i = 0; i < paths.size(); i++) {
        if (thisdir->dirs.empty()){ // 先排除空dir
            cout << "directory does not exist" << endl;
            return nullptr;
        }
        for (dir *d: thisdir->dirs) {

            if (d->name == paths[i]) {
                thisdir = d;
                continue;
            }
            cout << "directory does not exist" << endl;
            return nullptr;
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