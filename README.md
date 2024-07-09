# hangman

This code is a command line game.

It was created with Visual Studio 17 and it uses cxxopts library from https://github.com/jarro2783/cxxopts
(I duplicate it here)

In order to run this game you should:
1. get the repo to your local folder.
2. open the solution in Visual Studio and compile it, as 32 bit console application
3. The hangman.exe will be created in Debug folder
4. open CMD window at this Debug folder and run the command:
   >hangman.exe -w ..\input\words.txt
   or
   >hangman.exe -w ..\input\words.txt -l 3  (for exaple, to use only 3 words from the file)
5. the instructions how to play are displayed on the screen
   Enjoy.
