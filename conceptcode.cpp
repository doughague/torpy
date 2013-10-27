//
//  main.cpp
//  ArenaBasic
//
//  Created by Jason Torpy on 9/28/13.
//  Copyright (c) 2013 CyberT Designs. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

/* warrior class could have arrays of attributes,
 eg, war_prowess[]={max,current} to allow easy access and consolidated storage.
 warrior classes could also include the functions necessary for fights
 that would be realistic as their actions are a function of themselves
 only the fight results would be in the fight class
 The "fight" would be just passing of variables back and forth between instances of the warrior class
*/

class warrior {
public:
    string war_name;
    int war_prowess[2];
    int war_agility[2];
    int war_intel[2];
    int war_pers[2];
    int war_health[2];
    int war_disability[6]; // 0=fatigue,1=stun,2=fall,3=disarm, 4=fatigue/rd; 5=health/rd; higher numbers indicate more severe injury
    bool attacking () { // whether or not the fighter is attacking
        int check_atk = rand()%100+1-war_pers;
        float war_dis_total = war_disability[1] + war_disability[2] + war_disability[3]; // type match?
        check_atk = check_atk + pow(.5, war_dis_total); // pow called properly? can't use ^?
        check_atk > 0 ? return true : return false; // why is this incorrect?
        }
    int action () { // the quality of the fighter's attack
        float actionvalue;
        actionvalue = (war_prowess[1] * 3 + war_agility[1] + war_intel[1]) * (100-war_disability[0])/100;
        return actionvalue;
    }
} warrior1, warrior2;

/*
 cout << "Enter warrior name:"
 cin >> war_name;
 etc...
 hardcoding two warriors initially; use form-filler later
 Warrior creation will also be separate; with fight-initialization selecting from available warriors.
*/

// for both, other attributes should be initialized to zero. obviously won't work as listed.
// however the current attributes should be initialized to the max before new fights (until an alternate recovery system is in place.)
warrior1 = {"John",80,50,50,80,50}; // not sure how to assign values to the members of the class.
warrior2 = {"Jack",50,80,80,50,50};

// this initializes each fighter in this fight to the values listed above for each warrior, or 0.
// this will need to change to choose the selected warrior instead of the hardcoded 2 objects

int ftr_main ()
{
ft_startoffight:
    if (!warrior1.attacking && !warrior2.attacking) { // neither attacking scenario; reduce fatigue, minimum 0.
        warrior1.disability[0]>=3 ? warrior1.disability[0]-=3 : warrior1.disability[0]=0;
        warrior2.disability[0]>=3 ? warrior2.disability[0]-=3 : warrior2.disability[0]=0;
        goto ft_nextround;
    }
    if (warrior1.attacking || warrior2.attacking) { // either attacking scenario
        // assigns a winner/loser in the immediate attack session
        new void hit_success; // not sure how to declare this variable; intended to point to a warrior class object
        warrior1.action>warrior2.action ? hit_success == warrior1 : hit_success = warrior2; // prefers 1 in tie.
        hit_success == warrior1 ? hit_fail == warrior2 : hit_fail == warrior1;
        new int ft_res=abs(warrior1.action-warrior2.action); // fight resolution, severity of hit, confirm abs library is available
        warrior1.attacking && warrior2.attacking ? ft_res+=25; // increase severity if both are attacking.
        switch (ft_res) {
            case <50: //
                warrior1.attacking && warrior2.attacking ? cout<< "weapons clash.\n";
                cout << hit_success.war_name << " dodges.\n";
                goto ft_nextround;
            case <75:
                if (!hit_success.attacking) {
                    hit_fail.disability[0]+=10; // a dodge creating a fatiguing miss
                    cout << hit_success.war_name << " dodges deftly, while " << hit_fail.war_name << " flails wildly.\n";
                    else {
                        hit_fail.disability[4]+=3;
                        cout << hit_fail.war_name << " suffers a glancing blow.\n";
                    }
                }
                goto ft_nextround;
            case <100:
                if (!hit_success.attacking) {
                    hit_fail.disability[0]+=10; // fatiguing miss just like <75
                    cout << hit_success.war_name << " dodges deftly, while " << hit_fail.war_name << " flails wildly.\n";
                    else {
                        hit_fail.disability[4]+=5;
                        hit_fail.disability[5]+=5;
                        cout << hit_success.war_name << " scores a solid hit.\n";
                    }
                }
                goto ft_nextround;
            case >=100:
                if (!hit_success.attacking) {
                    hit_fail.disability[0]+=10; // dodge with riposte
                    hit_fail.disability[4]+=3;
                    cout << hit_success.war_name << " dodges deftly, scoring a hit in response.\n";
                    else {
                        hit_fail.disability[4]+=20;
                        hit_fail.disability[5]+=20;
                        cout << hit_fail.war_name << " suffers a grievous wound.\n";
                        rand()%100+1 > hit_fail.war_intel[1] ? hit_fail.war_disability[1]++; // stun check
                        rand()%100+1 > hit_fail.war_agility[1] ? hit_fail.war_disability[2]++; // fall check
                        rand()%100+1 > hit_fail.war_agility[1] ? hit_fail.war_disability[3]++; // disarm check
                        war_disability[1]==1 ? cout<<hit_fail.war_name<<" is stunned. ";
                        war_disability[2]==1 ? cout<<hit_fail.war_name<<" falls to the ground. ";
                        war_disability[3]==1 ? cout<<hit_fail.war_name<<" loses hold of his weapon. ";
                    }
                }
                goto ft_nextround;
        }
    }
ft_nextround:
    new int warrior1status; new int warrior2status;
    warrior1.war_health[1]>0&&warrior1.war_disability[0]>0 ? warrior1status==1 : warrior1status==0;
    warrior2.war_health[1]>0&&warrior2.war_disability[0]>0 ? warrior2status==1 : warrior2status==0;
    if warrior1status <1 || warrior2status <1 {
        warrior1status==1&&warrior2status==0 ? cout<<warrior1.war_name<<" wins!";
        warrior2status==1&&warrior1status==0 ? cout<<warrior2.war_name<<" wins!";
        goto ft_endoffight;
    }
    // if warriors are alive, fight continues with fighters affected by their fatigue.
    warrior1.war_prowess[1]=warrior1.war_prowess[1]*(100-warrior1.war_disability[0])/100;
    warrior1.war_agility[1]=warrior1.war_ability[1]*(100-warrior1.war_disability[0])/100;
    warrior1.war_intel[1]=warrior1.war_intel[1]*(100-warrior1.war_disability[0])/100;
    warrior1.war_pers[1]=warrior1.war_pers[1]*(100-warrior1.war_disability[0])/100;
    warrior2.war_prowess[1]=warrior2.war_prowess[1]*(100-warrior2.war_disability[0])/100;
    warrior2.war_agility[1]=warrior2.war_ability[1]*(100-warrior2.war_disability[0])/100;
    warrior2.war_intel[1]=warrior2.war_intel[1]*(100-warrior2.war_disability[0])/100;
    warrior2.war_pers[1]=warrior2.war_pers[1]*(100-warrior2.war_disability[0])/100;
    // apply effects of low health or high fatigue
    warrior1.health[1]<warrior1.health[1]*.25 ? warrior1.disability[1]++;
    warrior1.health[1]<warrior1.health[1]*.1 ? warrior1.disability[2]++;
    warrior1.disability[1]==1; cout<<warrior1.war_name<<" is stunned from wounds.";
    warrior1.disability[2]==1; cout<<warrior1.war_name<<" stumbles to the ground from wounds.";
    // recover from disabilities, could be easier if I could loop warrior1/2
    if warrior1.disability[1]>0 {
            int stat_check=rand()%100+1)-50;
            warrior1.war_intel[1]>stat_check ? warrior1.disability[1]--;
            warrior1.disability[1]==0 ? cout<<warrior1.war_name<<" clears his head.";
        }
    if warrior1.disability[2]>0 {
        int stat_check=rand()%100+1)-50;
        warrior1.war_agility[1]>stat_check ? warrior1.disability[2]--;
        warrior1.disability[2]==0 ? cout<<warrior1.war_name<<" rises to his feet.";
    }
    if warrior1.disability[3]>0 {
        int stat_check=rand()%100+1)-50;
        warrior1.war_agility[1]>stat_check ? warrior1.disability[3]--;
        warrior1.disability[3]==0 ? cout<<warrior1.war_name<<" recovers his weapon.";
    }
    if warrior2.disability[1]>0 {
        int stat_check=rand()%100+1)-50;
        warrior2.war_intel[1]>stat_check ? warrior2.disability[1]--;
        warrior2.disability[1]==0 ? cout<<warrior2.war_name<<" clears his head.";
    }
    if warrior2.disability[2]>0 {
        int stat_check=rand()%100+1)-50;
        warrior2.war_agility[1]>stat_check ? warrior2.disability[2]--;
        warrior2.disability[2]==0 ? cout<<warrior2.war_name<<" rises to his feet.";
    }
    if warrior2.disability[3]>0 {
        int stat_check=rand()%100+1)-50;
        warrior2.war_agility[1]>stat_check ? warrior2.disability[3]--;
        warrior2.disability[3]==0 ? cout<<warrior2.war_name<<" recovers his weapon.";
    }
goto ft_startoffight;
    
    
ft_endoffight:
    cout<<"\n The crowd roars.";
};



int main(int argc, const char * argv[])
{
    // running fighter main is the only function so far.
    ftr_damage();
    // standard hello world below.
    int p_input;
    string uname;
    cin >> p_input;
    cout<< "Hello, World!\n" << p_input << ": prowess a new line.\n";
    cout<< "input name here: ";
    cin >> uname;
    cout<<"Name: " << uname << "\n";
    return 0;
}

