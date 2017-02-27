//
//  main.cpp
//  ME493_HMWK2
//
//  Created by Cruz Kerver on 2/24/17.
//  Copyright © 2017 Autonomy. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>
#include <random>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <limits>

#define CKRAND ((double)rand()/RAND_MAX)

using namespace std;

class domain{
public:
    int xmin;
    int xmax;
    int ymin;
    int ymax;
    int goalx;
    int goaly;
    
    void init_domain(int*,int*);
};

class agent{
public:
    int agentx;
    int agenty;
    int agent_lastx;
    int agent_lasty;
    int agentx_start;
    int agenty_start;
    
    void init_agent(int*,int*);
};

void domain::init_domain(int* width , int* height){
    xmax = *width;
    ymax = *height;
    xmin = 1;
    ymin = 1;
    goalx = rand() % *width + 1;
    goaly = rand() % *height + 1;
};

void agent::init_agent(int* width,int* height){
    agentx_start = rand() % *width + 1;
    agenty_start = rand() % *height + 1;
    agentx = agentx_start;
    agenty = agenty_start;
    agent_lastx = agentx;
    agent_lasty = agenty;
};

void move(string* move_letter , int* pagentx , int* pagenty){
    if(*move_letter == "w"){
        *pagenty = *pagenty + 1;
    }
    else if(*move_letter == "d"){
        *pagentx = *pagentx + 1;
    }
    else if(*move_letter == "s"){
        *pagenty = *pagenty - 1;
    }
    else if(*move_letter == "a"){
        *pagentx = *pagentx - 1;
    }
    else{
        cout << "Not working" << endl;
    }
};

void bump(int* pagentx , int* pagenty, int* plastx , int* plasty , int* pxmax , int* pxmin , int* pymax , int* pymin){
    if((*pagentx > *pxmax) or (*pagentx < *pxmin) or (*pagenty > *pymax) or (*pagenty < *pymin)){
        *pagentx=*plastx;
        *pagenty=*plasty;
    }
    else{
        *pagentx=*pagentx;
        *pagenty=*pagenty;
    }
};

void lawn_mower(int* pagentx , int* pagenty, int* plastx , int* plasty , int* pxmax , int* pxmin , int* pymax , int* pymin , int* pgoalx , int* pgoaly){
    while(*pagentx != *pxmin){
        *pagentx = *pagentx - 1;
        cout << "Agent's position: " << "(" << *pagentx << "," << *pagenty << ")" << endl;
    }
    while(*pagenty != *pymin){
        *pagenty = *pagenty - 1;
        cout << "Agent's position: " << "(" << *pagentx << "," << *pagenty << ")" << endl;
    }
    cout << "Agent's position: " << "(" << *pagentx << "," << *pagenty << ")" << endl;
    for(int j=1; j<(*pymax + 1); j++){
        for(int i=1; i<(*pxmax + 1); i++){
            if(*pagentx != *pgoalx){
                *pagentx = *pagentx + 1;
                cout << "Agent's position: " << "(" << *pagentx << "," << *pagenty << ")" << endl;
            }
        }
        if(*pagenty != *pgoaly){
            *pagenty = *pagenty + 1;
            cout << "Agent's position: " << "(" << *pagentx << "," << *pagenty << ")" << endl;
        }
    }
    cout << "\n" <<"It worked!" << endl;
};

//////////////// The Main Event ////////////////

int main() {
    
    //Initializing size and starting point
    
    srand(time(NULL));
    int width = 0;
    int height = 0;
    cout << "How many squares wide is your grid? ";
    cin >> width;
    cout << "How many squares long is your grid? ";
    cin >> height;
    
    domain grid;
    grid.init_domain(&width , &height);
    cout << grid.xmax << "x" << grid.ymax << " grid" << endl;
    agent Z;
    Z.init_agent(&width , &height);
    while((Z.agentx != grid.goalx) && (Z.agenty != grid.goaly)){
        Z.init_agent(&width , &height);
    };
    
    cout << "Starting position of agent: (" << Z.agentx << "," << Z.agenty << ")" << endl;
    cout << "Goal position: (" << grid.goalx << "," << grid.goaly << ")" << endl;
    for(int i=height; i>0; i--){
        for(int j=1; j<(width+1); j++){
            if(Z.agentx_start == j && Z.agenty_start == i){
                cout << "A ";
            }
            else if(grid.goalx == j && grid.goaly == i){
                cout << "G ";
            }
            else{
                cout << ". ";
            }
        }
        cout << endl;
    }

    // Pointer assignments
    
    int* pagentx;
    int* pagenty;
    int* plastx;
    int* plasty;
    int* pxmax;
    int* pxmin;
    int* pymax;
    int* pymin;
    int* pgoalx;
    int* pgoaly;
    pagentx = &Z.agentx;
    pagenty = &Z.agenty;
    plastx = &Z.agent_lastx;
    plasty = &Z.agent_lasty;;
    pxmax = &grid.xmax;
    pxmin = &grid.xmin;
    pymax = &grid.ymax;
    pymin = &grid.ymin;
    pgoalx =&grid.goalx;
    pgoaly =&grid.goaly;
    
    // User plays the game
    
    string move_letter;
    while ((Z.agentx != grid.goalx) or (Z.agenty != grid.goaly)){
        cout << "w = up , a = left , s = Down , d = right: ";
        cin >> move_letter;
        move(&move_letter , pagentx , pagenty);
        bump(pagentx , pagenty, plastx , plasty , pxmax , pxmin , pymax , pymin);
        cout << "Agent position: (" << Z.agentx << "," << Z.agenty << ")" << endl;
        cout << "Goal position: (" << grid.goalx << "," << grid.goaly << ")" << endl;
        for(int i=height; i>0; i--){
            for(int j=1; j<(width+1); j++){
                if(Z.agentx == j && Z.agenty == i){
                    cout << "A ";
                }
                else if(grid.goalx == j && grid.goaly == i){
                    cout << "G ";
                }
                else{
                    cout << ". ";
                }
            }
            cout << endl;
        }
        Z.agent_lastx=Z.agentx;
        Z.agent_lasty=Z.agenty;
    }
    
    for(int i=height; i>0; i--){
        for(int j=1; j<(width+1); j++){
            cout << "Winner! ";
        }
        cout << endl;
    }
    cout << "\n";
    
    // Agent finds the goal all by himself
    
    cout << "Now watch the agent solve it by himself." << endl;
    Z.init_agent(&width , &height);
    while((Z.agentx != grid.goalx) && (Z.agenty != grid.goaly)){
        Z.init_agent(&width , &height);
    };
    
    cout << "Starting position of agent: (" << Z.agentx << "," << Z.agenty << ")" << endl;
    cout << "Goal position: (" << grid.goalx << "," << grid.goaly << ")" << endl;
    for(int i=height; i>0; i--){
        for(int j=1; j<(width+1); j++){
            if(Z.agentx_start == j && Z.agenty_start == i){
                cout << "A ";
            }
            else if(grid.goalx == j && grid.goaly == i){
                cout << "G ";
            }
            else{
                cout << ". ";
            }
        }
        cout << endl;
    }

    lawn_mower(pagentx , pagenty, plastx , plasty , pxmax , pxmin , pymax , pymin , pgoalx , pgoaly);
    
    return 0;
};
