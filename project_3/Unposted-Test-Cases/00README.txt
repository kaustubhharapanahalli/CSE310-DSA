At the requests of some students, I am posting the un-posted test cases
of Project 2. These are in the folders u31, u32, ..., u50.

I am also make it available a simple shell script I wrote to helps students
identifying the problems they have.

The syntax for using this shell script is
./xx FOLDER
with FOLDER replaced by the name of the folder for a particular test case.
For example, you can run "./xx u31" the check your program against test case u31.

You need to have your executable PJ2 in the current directory.
Here is the content of the shell script.
========
#!/bin/bash
rm Message.txt Output.txt
rm HEAPofile.txt
cp $1/HEAPifile.txt .
cp $1/Commands .
cp $1/Execution .
chmod +x Execution
./Execution
diff $1/Output.txt Output.txt
diff $1/Message.txt Message.txt
diff $1/HEAPofile.txt HEAPofile.txt
========

When you run "./xx u31", the value of $1 will be "u31".
When you run "./xx u32", the value of $1 will be "u32".
I assume you know the Linux commands rm, cp, chmod, and diff.
If you do not know them, try search "diff in Linux" on Google.
