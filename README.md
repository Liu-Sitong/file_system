# Simulate a file system in C++

The functions of the file system are as follows:

0) pwd (current work directory) 
1) mkdir(p) (path) directory_name 
2) dedir(p) (path) directory_name 
3) search file_name 
4) create(p) (path) file_name omode
5) cat(p) (path) file_name
6) delete(p) (path) file_name
7) write(p) (path) file_name buff wmode
8) reposition(p) (path) file_name pos
9) truncate(p) (path) file_name cnt
10) ls(p) (path)
11) open(p) (path) file_name
12) close(p) (path) file_name
13) regusr user_name password
14) delusr user_name [root only]
15) disusr
16) login user_name
17) lsfile
18) chmod(p) (path) file_name mode
19) exit



When a command can not be executed successfully for some reasons, the errors would be reported; some commands would also report when it is successfully executed:

directory already exists

directory does not exist

file already exists

file does not exist

write ok 

reposition ok

reposition failed

file already open

file does not open

permission denied

register ok

user already exists

user does not exist

login ok

password wrong

permission denied

file does not found