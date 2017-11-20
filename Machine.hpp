/*
 * Machine.h
 *
 *  Created on: Nov 17, 2017
 *      Author: Rohitha Reddy Matta
 */

#ifndef MACHINE_HPP_
#define MACHINE_HPP_
#include<string>
#include<fstream>
#include<sstream>
using std::string;

class Machine{
private:
	int Can_Count;
	int Bottle_Count;
	double Can_price;
	double Bottle_price;
	double money_out;
	int PIN;
public:
	Machine();
	~Machine();

	void Init(int x);
	void getMachineState();
	void admin_getMachineState();
	int getPrice();
	double new_money();
	int admin_control(int a);
	int Bottle_Process(int b);
	void Restart(int y);
	void Clear();
	bool check_entry(int a);
};



#endif /* MACHINE_HPP_ */
