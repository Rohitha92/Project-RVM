/*
 * main.cpp
 *
 *  Created on: Nov 17, 2017
 *      Author: Rohitha
 */

#include "Machine.hpp"
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

int Cust_Bottle_Count=0;
int Cust_Can_Count=0;
double Cust_money_out=0;
double new_money_out;
/***Machine::Machine(){
	Can_Count=0;
	Bottle_Count=0;
	Can_price=0.1;
	Bottle_price=0.2;
	money_out=0;
	PIN = 1234;
}***/

Machine::Machine(){
	ifstream input_file("admin_control.txt");
	string line;

	 while (std::getline(input_file, line))
	    {
	        istringstream ss(line);
	        ss>> Can_Count>> Bottle_Count>> Can_price>>Bottle_price>>money_out>>PIN;
	    }
}

Machine::~Machine(){}

void Machine::getMachineState(){
	cout<< "Total cans collected: "<< Cust_Can_Count<<endl;
	cout<< "Total PET bottles collected: "<< Cust_Bottle_Count<<endl;
	cout<< "Total: "<< Cust_Can_Count+ Cust_Bottle_Count <<endl;
	cout<< "Price per PET bottle: "<<Bottle_price<<endl;
	cout<< "Price per Can: "<< Can_price<<endl;
	Cust_money_out = Bottle_price*Cust_Bottle_Count + Cust_Can_Count*Can_price;
	cout<< "Total price paid to customer: "<<Cust_money_out<<endl;
}

double Machine::new_money(){
	Cust_money_out = Bottle_price*Cust_Bottle_Count + Cust_Can_Count*Can_price;
	new_money_out= money_out+ Cust_money_out;
	return new_money_out;
}
void Machine::admin_getMachineState(){
	cout<< "Total cans collected: "<< Can_Count<<endl;
	cout<< "Total PET bottles collected: "<< Bottle_Count<<endl;
	cout<< "Total: "<< Can_Count+ Cust_Bottle_Count <<endl;
	cout<< "Price per PET bottle: "<<Bottle_price<<endl;
	cout<< "Price per Can: "<< Can_price<<endl;
	double money_paid= new_money();
	cout<< "Total price paid to customer: "<<money_paid<<endl;
}

void Machine::Clear(){
	Can_Count=0;
	Bottle_Count=0;
	Can_price=0.10;
	Bottle_price=0.10;
	money_out=0;
}
int Machine::admin_control(int a){
	int new_pin;
	switch(a){
		case(0):{
			cout<<"enter New PIN"<<endl;
			cin>>new_pin;
			PIN = new_pin;
			cout<<"new PIN confirmed: "<< PIN;
			cout<<endl;
			return 2;
			break;
		}
		case(1):{
			cout<<"Getting Machine Stats..."<<endl;
			Machine::admin_getMachineState();
			return 2;
			//Machine::Restart(2);
			break;
		}
		case(2):{
			cout<<"Clearing Machine Stats to default.."<<endl;
			Machine::Clear();
			cout<< "Cleared"<<endl;
			cout<< "............"<<endl;
			return 2;
			break;
		}
		case(3):{
			cout<<" Changing Price stats..."<<endl;
			cout<<"Enter the price per PET bottle"<<endl;
			cin>> Bottle_price;
			cout<< "Enter price per Can"<<endl;
			cin>> Can_price;
			cout<<" Successfully updated"<<endl;
			cout<< "............"<<endl;
			return 2;
			break;
		}
		case(4):{
			return 0;
			break;
		}

		default:{
			cout<<" Invalid entry in admin control..Back to start.."<<endl;
			return 0;
			break;
		}

	}

}


void Machine::Restart(int case_x){
	Machine::Init(case_x);
}


int entry(){
	int start;
	cout<<"Enter\n Start:1 \n Admin control:2 \n Exit:3"<<endl;
	cin>>start;
	return start;
}

bool Machine::check_entry(int start){
	while(cin.fail()){
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			return true;
		}
	return false;
}

int Machine::Bottle_Process(int b){
	switch(b){
		case(1):{
			cout<< "bottle accepted"<<endl;
			Bottle_Count++;
			Cust_Bottle_Count++;
			return 1;
			break;
		}
		case(2):{
			cout<<"can accepted"<<endl;
			Can_Count++;
			Cust_Can_Count++;
			return 1;
			break;
		}
		case(3):{
			cout<<"cannot accept the item"<<endl;
			return 1;
			break;
		}
		case(4):{
			cout<<"returning to menu"<<endl;
			return 0;
			break;
		}
		default:{
			cout<<"invalid bottle process entry..returning to start"<<endl;
			return 1;
			break;
		}
	}
}

void Machine::Init(int start){
	int item, entered_pin, admin1;
	if(start==0)
		start= entry();
	if(check_entry(start)){
		cout<<"Invalid Entry -> Enter a Number"<<endl;
		start=0;
	}
	do{
		switch(start){
			case(0):{
				start=entry();
				break;
			}
			case(1): {
				cout<<"Place can/bottle in the slot.."<<endl;
				cout<< "Select below: \n Bottle: 1\n Can: 2\n other:3\n return to menu:4\n exit:5"<<endl;
				cin>>item;
				if(check_entry(item)){
					cout<<"Invalid Entry. Enter a Number"<<endl;
					start=1; break;
				}
				else{
					if(item==5){
						start=3;
					}
					else
						start=Machine::Bottle_Process(item);
				}
				break;
			}
			case(2):{
				cout<< "Enter 4digit PIN"<<endl;
				cin>> entered_pin;
				if(check_entry(entered_pin)){
					cout<<"Invalid Entry -> Enter 4 digit Number"<<endl;
					start=2; break;
					}
				else{
					if(entered_pin == PIN){
						cout<<"Welcome Admin....\n Change PIN:0\n Machine status:1\n Clear Machine Stats:2\n Change Price Stats:3\n To Menu:4\n Exit: 5"<<endl;
						cin>>admin1;
						if(check_entry(admin1)){
							cout<<"Invalid Entry -> Must be a Number"<<endl;
							start=2; break;
						}
						if(admin1==5){
								start=3; break;
						}
						else{
							start= Machine::admin_control(admin1);}
					}
					else {
						cout<<"Wrong PIN. Going Back to Start..."<<endl;
						start=0; break;
					}
				}
				break;
			}
			case(3):{
				cout<<"exiting..."<<endl;
				break;
			}
			default:{
				cout<<"Invalid entry"<<endl;
				start=0;
			}
		}
	}while(start!=3);
	double new_money_out= new_money();
	ofstream input_file("admin_control.txt");
	input_file.seekp(0,std::ios::end);
	input_file<<Can_Count<<"\t"<<Bottle_Count<<"\t"<< Can_price<<"\t"<<Bottle_price<<"\t"<<new_money_out<<"\t"<<PIN;

	cout<< "exited the process"<<endl;
	cout<< "Details of this transaction"<<endl;
	cout<< "------------------------------"<<endl;
	Machine::getMachineState();
	cout<< "------------------------------"<<endl;

}

int main(){
	Machine A;
	A.Init(0);
	return 0;

}
