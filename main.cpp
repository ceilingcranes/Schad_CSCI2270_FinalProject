//Tyler Schad
//TA: Shirly
//April 27th, 2016

/*
This is meant to be used by a customer going to a movie theater. The .txt file I have created has different movies listed
that is then parsed, creating a hash table of movies and their showtimes. A user can then choose to see what movies are playing,
when they are playing, and sort by showtimes, titles, and much more.

Another exciting feature is the "double feature" option, where a user can insert the titles of two movies they want to see in the
same day, and the program automatically calculates all screening options between those two movies which do not conflict. Finally,
I have randomized options, where the program will pick a movie and showtime at random, or even go so far as to pick a series
of films randomly that do not have any time conflicts.

Overall I'm very happy with my program, and hopefully it's easy to use and useful!
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include "MovieHash.h"

using namespace std;

int main(int argc, char* argv[])
{
    string line; //to stringstream
    int cat=0; //to organize times and days
    //int indexFinder=0; //to add movies to each index
    string temp; //for getline
    string title; //first category for parsing
    int startTime; //second category, when a movie begins
    int endTime; //third category, when a movie ends
    int startTime2;
    int endTime2;
    int startTime3;
    int endTime3;
    int index=0;
    bool noQuit=true;
    int inputInt;
    string menuPick;
    MovieHash h;
    string inputString1;
    string inputString2;

    ifstream inFile;
    inFile.open("movies.txt");
    if(inFile.good()){
        while (getline(inFile, line)){
            stringstream ss(line);
                while(getline(ss,temp,',')){
                    if(index!=5){
                    if(cat==0){
                        title=temp; //parses out only the first on each like to create a hash table
                        //cout<<hashTable[indexFinder].title<<endl;
                        //indexFinder++;
                        cat++;
                    }
                    else if(cat==1){ //adds starting times
                        startTime=atoi(temp.c_str());
                        cat++;
                    }
                    else if(cat==2){ //adds ending times
                        endTime=atoi(temp.c_str());
                        h.insertMovie(title,startTime,endTime,index);
                        cat++;
                    }
                    else if(cat==3){ //adds starting time for 2nd node in hash table
                        startTime2=atoi(temp.c_str());
                        cat++;
                    }
                    else if(cat==4){ //adds ending time for 2nd node in hash table while keeping title name
                        endTime2=atoi(temp.c_str());
                        h.insertMovie(title,startTime2,endTime2,index);
                        cat++;
                    }
                    else if(cat==5){ //adds starting time for 3rd node in hash table
                        startTime3=atoi(temp.c_str());
                        cat++;
                    }
                    else if(cat==6){ //adds ending time for 3rd node in hash table while keeping title name
                        endTime3=atoi(temp.c_str());
                        h.insertMovie(title,startTime3,endTime3,index);
                        cat=0;
                        index++;
                    }
                    }
                } //parse by commas
            } //while getline
            //the hash table is now built!
        while(noQuit==true){
            cout<<"======Main Menu======"<<endl;
            cout<<"1. Print all movies and showtimes"<<endl;
            cout<<"2. Search for a movie's showtimes"<<endl;
            cout<<"3. Find a double feature"<<endl;
            cout<<"4. Check which movies begin at a certain time"<<endl;
            cout<<"5. Pick random movie (with random time)"<<endl;
            cout<<"6. Pick random double feature"<<endl;
            cout<<"7. Quit"<<endl;
            getline(cin,menuPick);
            if(menuPick=="1"){ //Prints the hash table
                h.printTableContents();
            }
            else if(menuPick=="2"){ //Let's you find a certain movie's showtimes (which you must enter the movie)
                cout<<"Enter a movie title:"<<endl;
                getline(cin,inputString1);
                h.findMovie(inputString1);
            }
            else if(menuPick=="3"){ //Enter two movies, it calculates all possible ways to see both in a day without time conflict
                cout<<"Enter first movie title:"<<endl;
                getline(cin,inputString1);
                cout<<"Enter second movie title:"<<endl;
                getline(cin,inputString2);

                //**** check for valid strings here *** -m
                //Also: Causes problems with getting the times when you enter the same movie. -m
                h.doubleFeature(inputString1,inputString2);
            }

            // ** Maybe make it possible to get input it non-military time/ different formats -m

            else if(menuPick=="4"){ //See what movies begin at a certain time, so you can find the most convenient movie showing for you!
                cout<<"Enter the current time (in military time):"<<endl;
                getline(cin,inputString1);
                int inputInt=atoi(inputString1.c_str());
                h.atThisTime(inputInt);
                //string time=h.convertToStandardTime(inputInt);
                //cout << "Time: " << time << endl;
            }
            else if(menuPick=="5"){ //Pick a random movie, with a random screening time
                h.randomMovie();
            }

            //**Can have a movie that starts at the same time one ends, probably (minor thing) -m

            else if(menuPick=="6"){ //Just like above, but makes sure that the movies don't conflict and creates a back-to-back experience
                h.randomDouble();
            }



            else if(menuPick=="7"){ //Quit
                cout<<"Goodbye!"<<endl;
                noQuit=false;
            }
        }//while noQuit is true
    } //if InFile is good

    return 0;
}
