/*
 * Machine.h
 *
 *  Created on: Nov 17, 2017
 *      Author: Rohitha
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
	/***friend std::istream& operator>>(std::istream& is, Machine& asd){
		std::string line;
		std::getline(is, line);
        std::istringstream iss(line);

		iss>> asd.Can_Count;
		iss>> asd.Bottle_Count;
		iss>> asd.Can_price;
		iss>> asd.Bottle_price;
		iss>> asd.money_out;
		iss >> asd.PIN;
		return is;
	}***/

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
