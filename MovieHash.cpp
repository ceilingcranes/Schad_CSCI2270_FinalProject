#include "MovieHash.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <stdlib.h>

MovieHash::MovieHash()
{
    //ctor
    for(int x=0;x<5;x++){
        hashTable[x]=NULL;
    }
}

MovieHash::~MovieHash()
{
    //dtor
}

void MovieHash::insertMovie(std::string title, int startTime, int endTime, int index){
    HashElem *tmp=new HashElem;
    HashElem *node=new HashElem;
    node->title=title;
    node->startTime=startTime;
    node->endTime=endTime;
    node->next=NULL;
    node->previous=NULL;
    //tmp->next=NULL;
    //int sum=hashSum(title, s);
    //cout<<"hi"<<endl;
    if(hashTable[index]==NULL){
        hashTable[index]=node;
    }
    else{
        tmp=hashTable[index];
        while(tmp->next!=NULL){
            tmp=tmp->next;
        }
        tmp->next=node;
        node->previous=tmp;
        node->next=NULL;
    }
}

void MovieHash::printTableContents(){
    int i;
    HashElem *tmp=new HashElem;
    for(int x=0; x<5;x++){
        if(hashTable[x]!=NULL){
            tmp=hashTable[x];
            while(tmp!=NULL){
                cout<<tmp->title<<": "<<tmp->startTime<<" to "<<tmp->endTime<<endl;
                tmp=tmp->next;
            }
        }
    }
}

void MovieHash::findMovie(std::string name){
    int i;
    bool found=false;
    HashElem *tmp=new HashElem;
    for(int x=0; x<5;x++){
        if(hashTable[x]!=NULL){
            tmp=hashTable[x];
            while(tmp!=NULL){
                if(tmp->title==name){
                    cout<<name<<": from "<<tmp->startTime<<" to "<<tmp->endTime<<endl;
                    tmp=tmp->next;
                    found=true;
                }
                else{
                    tmp=tmp->next;
                }
            }
        }
    }
    if(found==false){
       cout<<"Movie not found."<<endl;
    }
}

void MovieHash::doubleFeature(std::string input1, std::string input2){
    int i;
    int z=0;
    int j=0;
    bool found1=false;
    bool found2=false;
    HashElem *tmp=new HashElem;
    for(int x=0; x<5;x++){
        if(hashTable[x]!=NULL){
            tmp=hashTable[x];
            while(tmp!=NULL){
                if(tmp->title==input1){
                    //cout<<input1<<": from "<<tmp->startTime<<" to "<<tmp->endTime<<endl;
                    bool SoE=true;
                    addTime(z,tmp->startTime,tmp->endTime,SoE);
                    tmp=tmp->next;
                    z=z+2;
                    if(z==8){
                        z=0;
                    }
                    found1=true;
                }
                else if(tmp->title==input2){
                    bool SoE=false;
                    addTime(j,tmp->startTime,tmp->endTime,SoE);
                    tmp=tmp->next;
                    j=j+2;
                    if(j==8){
                        j=0;
                    }
                    found2=true;
                }
                else{
                    tmp=tmp->next;
                }
            }
        }
    }
    if(found1==false and found2==false){
       cout<<"1 or more movies not found."<<endl;
    }
    else{
        for(int a=0;a<5;a=a+2){
            bool compare=timeCompare(movieOne[a],movieOne[a+1],movieTwo[a],movieTwo[a+1]);
            if(compare==true){
                if(movieTwo[a]<movieOne[a]){
                    cout<<input1<<" from "<<movieTwo[a]<<"-"<<movieTwo[a+1]<<", and "<<input2<<" from "<<movieOne[a]<<"-"<<movieOne[a+1]<<endl;
                }
                else{
                    cout<<input1<<" from "<<movieOne[a]<<"-"<<movieOne[a+1]<<", and "<<input2<<" from "<<movieTwo[a]<<"-"<<movieTwo[a+1]<<endl;
                }
        }
      }
    }

    /*for(int y=0;y<6;y++){
        cout<<movieOne[y]<<endl;
    }
    for(int y=0;y<6;y++){
        cout<<movieTwo[y]<<endl;
    }*/
}

bool MovieHash::timeCompare(int compareOne, int compareTwo, int compareThree, int compareFour){
    if(compareOne>compareThree and compareOne<compareFour){
        return false;
    }
    else if(compareTwo>compareThree and compareTwo<compareFour){
        return false;
    }
    else if(compareThree>compareOne and compareThree<compareTwo){
        return false;
    }
    else if(compareFour>compareOne and compareFour<compareTwo){
        return false;
    }
    else{
        return true;
    }
}

void MovieHash::addTime(int z, int startTime, int endTime, bool SoE){
    if(SoE==true){
        movieTwo[z]=startTime;
        z++;
        movieTwo[z]=endTime;
    }
    else if(SoE==false){
        movieOne[z]=startTime;
        z++;
        movieOne[z]=endTime;
    }
}

void MovieHash::randomMovie(){
    int randomFilm = rand() % 5 + 0;
    int randomTime = rand() % 3 + 1;
    if(randomTime==1){
        cout<<"See "<<hashTable[randomFilm]->title<<" at "<<hashTable[randomFilm]->startTime<<endl;
    }
    else if(randomTime==2){
        cout<<"See "<<hashTable[randomFilm]->title<<" at "<<hashTable[randomFilm]->next->startTime<<endl;
    }
    else if(randomTime==3){
        cout<<"See "<<hashTable[randomFilm]->title<<" at "<<hashTable[randomFilm]->next->next->startTime<<endl;
    }
}

void MovieHash::randomDouble(){
    int random2=rand() % 5 + 0;
    int random1=rand() % 5 + 0;
    while(random1==random2){
        random1=rand() % 5 + 0;
    }
    randomDoubleFeature(hashTable[random1]->title,hashTable[random2]->title);
}

void MovieHash::randomDoubleFeature(std::string input1, std::string input2){
    int i;
    int z=0;
    int j=0;
    bool firstPick=false;
    bool found1=false;
    bool found2=false;
    HashElem *tmp=new HashElem;
    for(int x=0; x<5;x++){
        if(hashTable[x]!=NULL){
            tmp=hashTable[x];
            while(tmp!=NULL){
                if(tmp->title==input1){
                    bool SoE=true;
                    addTime(z,tmp->startTime,tmp->endTime,SoE);
                    tmp=tmp->next;
                    z=z+2;
                    if(z==8){
                        z=0;
                    }
                    found1=true;
                }
                else if(tmp->title==input2){
                    bool SoE=false;
                    addTime(j,tmp->startTime,tmp->endTime,SoE);
                    tmp=tmp->next;
                    j=j+2;
                    if(j==8){
                        j=0;
                    }
                    found2=true;
                }
                else{
                    tmp=tmp->next;
                }
            }
        }
    }
        for(int a=0;a<5;a=a+2){
            bool compare=timeCompare(movieOne[a],movieOne[a+1],movieTwo[a],movieTwo[a+1]);
            if(compare==true){
                if(firstPick==false){
                    if(movieTwo[a]<movieOne[a]){
                        cout<<input1<<" from "<<movieTwo[a]<<"-"<<movieTwo[a+1]<<", and "<<input2<<" from "<<movieOne[a]<<"-"<<movieOne[a+1]<<endl;
                        firstPick=true;
                    }
                    else{
                        cout<<input1<<" from "<<movieOne[a]<<"-"<<movieOne[a+1]<<", and "<<input2<<" from "<<movieTwo[a]<<"-"<<movieTwo[a+1]<<endl;
                        firstPick=true;
                    }
                }
        }
      }
}

/*void MovieHash::soonestScreening(int time){
    int i;
    int diffStorage1;
    string movieStorage1;
    int timeStorage1;
    int diffStorage2;
    string movieStorage2;
    int timeStorage2;
    int diffStorage3;
    string movieStorage3;
    int timeStorage3;

    HashElem *tmp=new HashElem;
    tmp=hashTable[0];
    diffStorage2=tmp->startTime-time;
    timeStorage2=tmp->startTime;
    movieStorage2=tmp->title;
    //cout<<diffStorage2<<" "<<timeStorage2<<" "<<movieStorage2<<endl;
    if(diffStorage2>2400){
            diffStorage2=time+(2400-tmp->startTime);
    }
    for(int x=0; x<5;x++){
        if(hashTable[x]!=NULL){
            while(tmp!=NULL){
                diffStorage1=tmp->startTime+time;
                if(diffStorage1>2400){
                    //diffStorage1=tmp->startTime-(2400-time);
                    diffStorage1=time+(2400-tmp->startTime);
                }
                movieStorage1=tmp->title;
                timeStorage1=tmp->startTime;
                if(diffStorage1==diffStorage2){
                    diffStorage3=diffStorage2;
                    movieStorage3=movieStorage2;
                    timeStorage3=timeStorage2;
                    diffStorage2=diffStorage1;
                    movieStorage2=movieStorage1;
                    timeStorage2=timeStorage1;
                }
                if(diffStorage1<diffStorage2){
                    diffStorage2=diffStorage1;
                    movieStorage2=movieStorage1;
                    timeStorage2=timeStorage1;
                }
                //cout<<tmp->title<<" is showing at "<<tmp->startTime<<", in "<<diffStorage1<<" minute(s)."<<endl;
                tmp=tmp->next;
            }
        }
    }
    if(diffStorage2==diffStorage3){
        if(movieStorage3==movieStorage2){
            cout<<movieStorage2<<" is showing at "<<timeStorage2<<"."<<endl;
        }
        else{
            cout<<movieStorage2<<" is showing at "<<timeStorage2<<"."<<endl;
            cout<<movieStorage3<<" is showing at "<<timeStorage3<<"."<<endl;
        }
    }
    else{
        cout<<movieStorage2<<" is showing at "<<timeStorage2<<"."<<endl;
    }
}*/

void MovieHash::atThisTime(int time){
    int i;
    HashElem *tmp=new HashElem;
    for(int x=0; x<5;x++){
        if(hashTable[x]!=NULL){
            tmp=hashTable[x];
            while(tmp!=NULL){
                if(tmp->startTime==time){
                    cout<<tmp->title<<": from "<<tmp->startTime<<" to "<<tmp->endTime<<endl;
                }
                tmp=tmp->next;
            }
        }
    }
}
