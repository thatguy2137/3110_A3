********A3 3110;	Saatvik Bhayana 	ID: 0000000  ********


*NOTE TO MARKER*.
This assignment was completed while very sick and I wasn't able to do my best work, or comment my code. (Grammatical errors will be present in read me)


*****Running******
To run the program, simply type "make" in the folder with all the files.
To run each the dining program type "./dine.out" followed by 2 arguments (amount of philosophers, amount of times to eat)
To run the holes program type "./holes.out" followed by the input file (test.txt is provided as the file used for testing)

To see the commandline used to complie, look at the makefile in the folder.

Algorithm for P1:
For P1 I used pthread to lock and unlock resources whenever a philosopher was eating. The algorithm goes through all the philosophers and makes them think and eat when it's their turn.
It takes the amount of times to each and amount of philosphers through the command line and then uses that information to run the algorithm the necessary amount of times.

Algorithm for P2:
The program takes in the file through the commandline, then opens the file and saves the contents in 4 seperate arrays (1 reference and 3 for types of fits)
The program then puts it all into a linked list, then begins to do the calculation for each type of fitting algorithm. The algorithms are the ones discussed in class
and I used some of the information from the labs and the slides when deciding my algorithm for each of the fits, as well as found a resource online that helped me figure out how to do the algorithms.
The program counts the amount of times memory is swapped, stops the memory from being reinserted after 3 swaps, and calculates the average amount of holes and other information in the memory simulation

*****KNOWN ISSUES******
Sometimes the philosophers will keeps eating and thinking until they're done their turn (ie, all of philisopher 1's turn, then 2, then 3)
Though this happens only sometimes.

Unsure of values for P2 but am assuimg they're correct

*****Assumptions******
Philosophers can eat and think as many times as needed in a row (as explained in the issues) :P


***NOTE****
-Some of the code for P2 was inspired from code online but the link is lost to me.
-If there are any issues please email me; bhayanas@mail.uoguelph.ca