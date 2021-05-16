# lervisnh-shell

## 1. Introduction
---
This project is to realize the shell function. First of all, shell has its own syntax and usage, and needs to implement functions similar to syntax parsing. For different commands, the shell needs to complete different functions, so different functions need to be called inside the shell. For example, the PWD command displays the directory where the current shell is running, while the LS command displays the names of all files and folders in the current directory.
In the shell with ";" It is a control module divider to distinguish different commands. In each command, one or several spaces are used to divide the different parameters in the command. For example, the MV command for moving files needs to be explicit < src > and < dst > Parameter to < src > For the original document, and < dst > Is the location of the movement; However, the RM command requires only one parameter < filename >。 For shell, the input command is unknown, so dynamic memory management is used to store different commands.



## 2. Usages
---
Command | #Args | Example | Description
--- | --- | --- | ---
ls | 0 | ls | Unix ls command. Will show the names of files and folders of the current directory.
pwd | 0 | pwd | Unix pwd command. Will show the current directory.
mkdir | 1 | mkdir < name > | Unix mkdir command. Will create a directory with the filename specified by: < name >.
cd | 1 | cd directory | Unix cd command. Will change directory based on the destination specified in the argument.
cp | 2 | cp < src > < dst > | Only for copying files. Copy one file from the path specified by < src > to the location specified by < dst >. < src > can be any form below: “File”, “dir/file” < dst >can also be any form below: “file”,”dir/file”, “dir”
mv | 2 | mv < src> < dst > | Only for copying files. Copy one file from the path specified by < src > to the location specified by < dst >. < src > can be any form below: “File”, “dir/file” < dst >can also be any form below: “file”,”dir/file”, “dir”
rm | 1 | rm < filename > | Only for removing files (not a directory). Will remove the specified file from any directory.
cat | 1 | cat < filename> | Displays a file’s content on the console.