This project is catb which is just a dumb project which prints out file contents in bianary
 (and has a flag to output a file in integer form). 
The name comes from the cat command with b for bianary. 
To use (for linux) first git clone this repo, then use your favorite c compiler (for example gcc) 
and compile it with the name catb (with gcc the command would be: gcc -o catb main.c). 
Now copy or move the bianary into the /usr/local/bin folder and it should work! 
Im not sure how to make this work for windows and mac. 
Currently the project doesn't have much extensibility. 
You may need to give setup.sh execute permissions if you want to run it to automatically set up
for you.
