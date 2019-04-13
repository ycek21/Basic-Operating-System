#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include"pipes.h"
#include"Procesy.h"
#include "Memory.h"
#include "fafms.h"
#include "ConsoleColor.h"

extern class Procesor;
extern PCB_tree drzewko;
//4 registers
int AX;
int BX;
int CX;
int DX;
int CommandCounter;
int PID;

void SaveRegisters(); //Saving registers after executing a command
void ShowRegisters();  //displaying registers
void GetRegisters(); //getting registers from a RUNNING process
std::string GetCommand(); //getting command from RAM memory

void SaveRegisters()  
{

	PCB* pcb = Procesor::getRunning();
	pcb->counter = CommandCounter;
	pcb->registers[0] = AX;
	pcb->registers[1] = BX;
	pcb->registers[2] = CX;
	pcb->registers[3] = DX;
	pcb->PID = PID;
}

void ShowRegisters() //displaying registers
{
	std::cout << yellow << "[ASSEMBLER]" << white << " Process PID: " << PID << std::endl;
	std::cout << yellow << "[ASSEMBLER]" << white << " AX: " << AX << " BX: " << BX << " CX: " << CX << " DX: " << DX << std::endl;
	std::cout << yellow << "[ASSEMBLER]" << white << " CommandCounter: " << CommandCounter << std::endl;
}

void GetRegisters() //getting registers from a RUNNING process
{

	PCB *pcb = Procesor::getRunning();
	AX = pcb->registers[0];
	BX = pcb->registers[1];
	CX = pcb->registers[2];
	DX = pcb->registers[3];
	PID = pcb->PID;
	CommandCounter = pcb->counter;

}

std::string GetCommand() //Saving registers after executing a command
{

	PCB *pcb = Procesor::getRunning();

	std::string command;
	command = getOrder(pcb, CommandCounter);
	CommandCounter += command.size() + 1;
	return command;
}
int signum(int x)
{
	if (x > 0)
	{
		return 1;
	}
	else if (x < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}


void Execute() //executing a command
{
	PCB *pcb = Procesor::getRunning();
	std::string C1, C2;
	int temporary = 0;
	GetRegisters();
	std::string command;
	//command.clear(); 
	command = GetCommand();
	std::cout << yellow << "[ASSEMBLER]" << white << " Command is: " << command << " ";

	
	//checking operation
	if (command == "AD")//addition
	{
		C1 = GetCommand();
		C2 = GetCommand();
		if (C1.length() >= 10 || C2.length() >= 10)
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Number you enter is too big" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();//incrementing time quantum
			return;
		}
		
		//C1=DX
		if (C1 == "DX")
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " You can't use DX" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		if (C2[0]>67)
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Please enter a key" << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		std::cout << C1 << " " << C2 << std::endl;
		if (C2[1] != 'X')
		{
			temporary = stoi(C2);
		}

		//C1==AX
	
		if (C1 == "AX" && temporary != 0)
		{
		   AX + temporary;
						
		}
		else if (C1[0] == 'A' && C2[0] == 'B')
		{
			AX += BX;
		}
		else if (C1 == "AX" && C2 == "CX")
		{
			AX += CX;
		}
		else if (C1 == "AX" && C2 == "AX")
		{
			AX += AX;
		}
		else if (C1 == "AX" && C2 == "DX")
		{

			std::cout << yellow << "[ASSEMBLER]" << white << " Second argument is wrong" << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

		// C1=BX
		if (C1 == "BX" && temporary != 0)
		{
			BX += temporary;
		}
		else if (C1 == "BX" && C2 == "AX")
		{
			BX += AX;
		}
		else if (C1 == "BX" && C2 == "CX")
		{
			BX += CX;
		}
		else if (C1 == "BX" && C2 == "BX")
		{
			BX += BX;
		}
		else if (C1 == "BX" && C2 == "DX")
		{

			std::cout << yellow << "[ASSEMBLER]" << white << " Second argument is wrong" << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

		//C1=CX
		if (C1 == "CX" && temporary != 0)
		{
			CX += temporary;
		}
		else if (C1 == "CX" && C2 == "BX")
		{
			CX += BX;
		}
		else if (C1 == "CX" && C2 == "AX")
		{
			CX += AX;
		}
		else if (C1 == "CX" && C2 == "CX")
		{
			CX += CX;
		}
		else if (C1 == "CX" && C2 == "DX")
		{

			std::cout << yellow << "[ASSEMBLER]" << white << " Second argument is wrong" << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

		ShowRegisters();
		SaveRegisters();
		Procesor::incCOUNT();
	}

	
	if (command == "SB")//subtraction
	{

		C1 = GetCommand();
		C2 = GetCommand();
		if (C1.length() >= 10 || C2.length() >= 10)
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Number you enter is too big" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		if (C1 == "DX")
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " You can't use DX" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		if (C2[0] > 67)
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Please enter a key" << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		std::cout << C1 << " " << C2 << std::endl;
		if (C2 != "AX" && C2 != "BX" && C2 != "CX" && C2 != "DX")
		{
			temporary = stoi(C2);
		}

		//C1==AX

		if (C1 == "AX" && temporary != 0)
		{
			AX -= temporary;
		}
		else if (C1 == "AX" && C2 == "BX")
		{
			AX -= BX;
		}
		else if (C1 == "AX" && C2 == "CX")
		{
			AX -= CX;
		}
		else if (C1 == "AX" && C2 == "AX")
		{
			AX -= AX;
		}
		else if (C1 == "AX" && C2 == "DX")
		{

			std::cout << yellow << "[ASSEMBLER]" << white << " Second argument is wrong" << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

		// C1=BX
		if (C1 == "BX" && temporary != 0)
		{
			BX -= temporary;
		}
		else if (C1 == "BX" && C2 == "AX")
		{
			BX -= AX;
		}
		else if (C1 == "BX" && C2 == "CX")
		{
			BX -= CX;
		}
		else if (C1 == "BX" && C2 == "BX")
		{
			BX -= BX;
		}
		else if (C1 == "BX" && C2 == "DX")
		{

			std::cout << yellow << "[ASSEMBLER]" << white << " Second argument is wrong" << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

		//C1=CX
		if (C1 == "CX" && temporary != 0)
		{
			CX -= temporary;
		}
		else if (C1 == "CX" && C2 == "BX")
		{
			CX -= BX;
		}
		else if (C1 == "CX" && C2 == "AX")
		{
			CX -= AX;
		}
		else if (C1 == "CX" && C2 == "CX")
		{
			CX -= CX;
		}
		else if (C1 == "CX" && C2 == "DX")
		{

			std::cout << yellow << "[ASSEMBLER]" << white << " Second argument is wrong" << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

		ShowRegisters();
		SaveRegisters();
		Procesor::incCOUNT();
	}

	//division
	if (command == "DV")
	{
		C1 = GetCommand();
		C2 = GetCommand();
		
		if (C1.length() >= 10 || C2.length() >= 10)
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " umber you enter is too big" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		if (C2[0] > 67)
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Please enter a key" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		if (stoi(C2) == 0)
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Don't divide by 0 !" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		if (C1 == "DX")
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " You can't use DX" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		
		std::cout << C1 << " " << C2 << std::endl;
		if (C2 != "AX" && C2 != "BX" && C2 != "CX" && C2 != "DX")
		{
			temporary = stoi(C2);
		}

		//C1==A
		if (C1 == "AX" && temporary != 0)
		{
			AX /= temporary;
		}
		else if (C1 == "AX" && C2 == "BX")
		{
			AX /= BX;
		}
		else if (C1 == "AX" && C2 == "CX")
		{
			AX /= CX;
		}
		else if (C1 == "AX" && C2 == "AX")
		{
			AX /= AX;
		}
		else if (C1 == "AX" && C2 == "DX")
		{

			std::cout << yellow << "[ASSEMBLER]" << white << " Second argument is wrong" << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}


		// C1=BX
		if (C1 == "BX" && temporary != 0)
		{
			BX /= temporary;
		}
		else if (C1 == "BX" && C2 == "AX")
		{
			BX /= AX;
		}
		else if (C1 == "BX" && C2 == "CX")
		{
			BX /= CX;
		}
		else if (C1 == "BX" && C2 == "BX")
		{
			BX /= BX;
		}
		else if (C1 == "BX" && C2 == "DX")
		{

			std::cout << yellow << "[ASSEMBLER]" << white << " Second argument is wrong" << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

		//C1=CX
		if (C1 == "CX" && temporary != 0)
		{
			CX /= temporary;
		}
		else if (C1 == "CX" && C2 == "BX")
		{
			CX /= BX;
		}
		else if (C1 == "CX" && C2 == "AX")
		{
			CX /= AX;
		}
		else if (C1 == "CX" && C2 == "CX")
		{
			CX /= CX;
		}
		else if (C1 == "CX" && C2 == "DX")
		{

			std::cout << yellow << "[ASSEMBLER]" << red << " Second argument is wrong" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		ShowRegisters();
		SaveRegisters();
		Procesor::incCOUNT();
	}

	//multiplication
	if (command == "ML")
	{
		C1 = GetCommand();
		C2 = GetCommand();
		if (C1.length() >= 10 || C2.length() >= 10)
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Number you enter is too big" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		if (C1 == "DX")
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " You can't use DX" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		if (C2[0] > 67)
		{
			std::cout << yellow << "[ASSEMBLER]" << red << "Please enter a key" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		std::cout << C1 << " " << C2 << std::endl;
		if (C2 != "AX" && C2 != "BX" && C2 != "CX" && C2 != "DX")
		{
			temporary = stoi(C2);
		}

		//C1==AX
		if (C1 == "AX")
		{
			AX *= temporary;
		}
		else if (C1 == "AX" && C2 == "BX")
		{
			AX *= BX;
		}
		else if (C1 == "AX" && C2 == "CX")
		{
			AX *= CX;
		}
		else if (C1 == "AX" && C2 == "AX")
		{
			AX *= AX;
		}

		else if (C1 == "AX" && C2 == "DX")
		{

			std::cout << yellow << "[ASSEMBLER]" << red << " Second argument is wrong" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

		// C1=BX
		if (C1 == "BX")
		{
			BX *= temporary;
		}
		else if (C1 == "BX" && C2 == "AX")
		{
			BX *= AX;
		}
		else if (C1 == "BX" && C2 == "CX")
		{
			BX *= CX;
		}
		else if (C1 == "BX" && C2 == "BX")
		{
			BX *= BX;
		}
		else if (C1 == "BX" && C2 == "DX")
		{

			std::cout << yellow << "[ASSEMBLER]" << red << " Second argument is wrong" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

		//C1=CX
		if (C1 == "CX")
		{
			CX *= temporary;
		}
		else if (C1 == "CX" && C2 == "BX")
		{
			CX *= BX;
		}
		else if (C1 == "CX" && C2 == "AX")
		{
			CX *= AX;
		}
		else if (C1 == "CX" && C2 == "CX")
		{
			CX *= CX;
		}
		else if (C1 == "CX" && C2 == "DX")
		{

			std::cout << yellow << "[ASSEMBLER]" << red << " Second argument is wrong" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

		ShowRegisters();
		SaveRegisters();
		Procesor::incCOUNT();
	}
	if (command == "CO")
	{
		int x = 0, y = 0;
		C1 = GetCommand();
		C2 = GetCommand();
		std::cout << " " << C1 << " " << C2 << std::endl;
		if (C1 == "DX")
		{
			std::cout <<yellow << "[ASSEMBLER]" << red << " You can't use DX" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		if (C1 == "AX")
		{
			x = AX;

		}
		else if (C1 == "BX")
		{
			x = BX;
		}
		else if (C1 == "CX")
		{
			x = CX;
		}
		else
		{
			x = stoi(C1);
		}

		if (C2 == "AX")
		{
			y = AX;

		}
		else if (C2 == "BX")
		{
			y = BX;
		}
		else if (C2 == "CX")
		{
			y = CX;
		}
		else if (C2 == "DX")
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " You can't use DX" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		else
		{
			y = stoi(C2);
		}

		DX = signum(x - y);
		ShowRegisters();
		SaveRegisters();
		Procesor::incCOUNT();

	}

	//Decrementation of a register
	if (command[0] == 'D'&&command[1] == 'C')
	{
		C1 = GetCommand();
		if (C1 == "DX")
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " You can't use DX" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		
		std::cout << C1 << std::endl;
		if (C1 == "AX")
			AX--;
		if (C1 == "BX")
			BX--;
		if (C1 == "CX")
			CX--;

		ShowRegisters();
		SaveRegisters();
		Procesor::incCOUNT();
	}
	if (command == "IN")//incrementation a register
	{
		C1 = GetCommand();
		if (C1 == "DX")
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " You can't use DX" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		std::cout << C1 << std::endl;
		if (C1 == "AX")
			AX++;
		if (C1 == "BX")
			BX++;
		if (C1 == "CX")
			CX++;
		ShowRegisters();
		SaveRegisters();
		Procesor::incCOUNT();
	}

	//Move to register
	if (command == "MO")
	{

		C1 = GetCommand();
		C2 = GetCommand();
		if (C1.length() >= 9 || C2.length() >= 9)
		{
			std::cout << yellow << "[ASSEMBLER]"<< red << " Number you enter is too big" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		else if (C1 == "DX")
		{
			std::cout << yellow << "[ASSEMBLER]" << red << "You can't use DX " << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		std::cout << C1 << " " << C2 << std::endl;

		if (C2 != "AX" && C2 != "BX" && C2 != "CX" && C2 != "DX")
		{
			temporary = stoi(C2);
		}
		//////////

		if (C1 == "AX" && temporary != 0)
		{
			AX = temporary;
		}
		else if (C1 == "AX" && C2 == "BX")
		{
			AX = BX;
		}
		else if (C1 == "AX" && C2 == "CX")
		{
			AX = CX;
		}
		///////
		if (C1 == "BX" && temporary != 0)
		{
			BX = temporary;
		}
		else if (C1 == "BX" && C2 == "AX")
		{
			BX = CX;
		}
		else if (C1 == "BX" && C2 == "CX")
		{
			BX = CX;
		}

		///////////////////
		if (C1 == "CX" && temporary != 0)
		{
			CX = temporary;
		}
		else if (C1 == "CX" && C2 == "BX")
		{
			CX = BX;
		}
		else if (C1 == "CX" && C2 == "AX")
		{
			CX = AX;
		}

		ShowRegisters();
		SaveRegisters();
		Procesor::incCOUNT();
	}

	////////JUMP
	if (command == "JP")
	{
		C1 = GetCommand();
		if (C1[0]=='-')
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Wrong address" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		if (C1[0] > 64)
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Wrong address" << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		std::cout << C1 << std::endl;
		CommandCounter = stoi(C1);

		ShowRegisters();
		SaveRegisters();
		Procesor::incCOUNT();

	}

	//JUMP ZERO

	if (command == "JZ")//skacze jak jest 0
	{
		C1 = GetCommand();
		std::cout << C1 << std::endl;
		if (C1[0] == '-')
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Wrong address" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		if (C1[0] > 64)
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Wrong address" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		int skok = 0;
		skok = stoi(C1);
		if (DX == 0)
		{

			CommandCounter = skok;
		}
		ShowRegisters();
		SaveRegisters();
		Procesor::incCOUNT();
	}
	if (command == "JN")//JUMP NOT ZERO
	{
		
		C1 = GetCommand();
		std::cout << C1 << std::endl;
		if (C1[0] == '-')
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Wrong address" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		if (C1[0] > 64)
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Wrong address" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		else
		{
			int skok = stoi(C1);
			if (DX != 0)
			{
				CommandCounter = skok;
			}
			ShowRegisters();
			SaveRegisters();
			Procesor::incCOUNT();
		}
	}

	if (command == "OT")//displaying register
	{
		C1 = GetCommand();
		if (C1 == "AX")
		{
			std::cout << AX << std::endl;
		}
		else if (C1 == "BX")
		{
			std::cout << BX << std::endl;
		}
		else if (C1 == "CX")
		{
			std::cout << CX << std::endl;
		}
		else if (C1 == "DX")
		{
			std::cout << DX << std::endl;
		}
		ShowRegisters();
		SaveRegisters();
		Procesor::incCOUNT();
	}

	//DYSK
	if (command == "CF1")//create file 1
	{
		C1 = GetCommand();//folder
		C2 = GetCommand();//file name
		SaveRegisters();
		Procesor::incCOUNT();
		std::cout << C1 << std::endl;
		std::cout << C2 << std::endl;
		if (create(C1, C2))
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " File has been created" << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
	}
	if (command == "CF2")//create file 2
	{
		std::string C3;
		C1 = GetCommand();//folder
		C2 = GetCommand();//file name
		C3 = GetCommand();//parent directory
		SaveRegisters();
		Procesor::incCOUNT();

		std::cout << C1 << std::endl;
		std::cout << C2 << std::endl;
		std::cout << C3 << std::endl;
		if (create(C1, C2, C3))
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " File has been created" << std::endl;
		}
		else
		{

			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "UN1")//unlink 1
	{
		C1 = GetCommand();//file name
		SaveRegisters();
		Procesor::incCOUNT();
		std::cout << C1 << std::endl;
		if (unLink(C1))
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Link has been deleted" << std::endl;
		}
		else
		{

			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect argument" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}


	}
	if (command == "UN2")//unlink 2
	{
		C1 = GetCommand();//file name
		C2 = GetCommand();//parent directory
		SaveRegisters();
		Procesor::incCOUNT();
		std::cout << C1 << std::endl;
		if (unLink(C1, C2))
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Link has been deleted" << std::endl;
		}
		else
		{

			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect argument" << white <<std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}


	}
	if (command == "OP1")//open 1
	{
		C1 = GetCommand();//file name
		C2 = GetCommand();//opening type
		SaveRegisters();
		Procesor::incCOUNT();
		int typ = stoi(C2);
		std::cout << C1 << std::endl;
		if (typ == 1)
		{
			if (open(C1, true))
			{
				std::cout << yellow << "[ASSEMBLER]" << white << " File has been opened" << std::endl;
			}
			else
			{
				std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
				Procesor::REMOVE(pcb);
				deleteFromMemory(pcb->PID);
				drzewko.kill(pcb->PID);
				Procesor::incCOUNT();
				return;
			}
		}
		else
		{
			if (open(C1, false))
			{
				std::cout << yellow << "[ASSEMBLER]" << white << " File has been opened" << std::endl;
			}
			else
			{
				std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
				Procesor::REMOVE(pcb);
				deleteFromMemory(pcb->PID);
				drzewko.kill(pcb->PID);
				Procesor::incCOUNT();
				return;
			}
		}


	}

	if (command == "OP2")//open 2
	{
		std::string C3;
		C1 = GetCommand();//file name
		C2 = GetCommand();//opening type
		C3 = GetCommand();//folder name
		SaveRegisters();
		Procesor::incCOUNT();
		int typ = stoi(C2);
		std::cout << C1 << std::endl;
		if (typ == 1)
		{
			if (open(C1, true, C3))
			{
				std::cout << yellow << "[ASSEMBLER]" << white << " File has been opened" << std::endl;
			}
			else
			{
				std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
				Procesor::REMOVE(pcb);
				deleteFromMemory(pcb->PID);
				drzewko.kill(pcb->PID);
				Procesor::incCOUNT();
				return;
			}
		}
		else
		{
			if (open(C1, false, C3))
			{
				std::cout << yellow << "[ASSEMBLER]" << white << " File has been opened" << std::endl;
			}
			else
			{
				std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
				Procesor::REMOVE(pcb);
				deleteFromMemory(pcb->PID);
				drzewko.kill(pcb->PID);
				Procesor::incCOUNT();
				return;
			}
		}


	}

	if (command == "CL1")//close 1
	{
		C1 = GetCommand();//file name
		SaveRegisters();
		Procesor::incCOUNT();
		if (close(C1))
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " File has been closed" << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "CL2")//close 2
	{
		C1 = GetCommand();//file name
		C2 = GetCommand();//folder name
		SaveRegisters();
		Procesor::incCOUNT();
		if (close(C1, C2))
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " File has been closed" << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "TR1")//truncate 1
	{
		C1 = GetCommand();//file name
		C2 = GetCommand();//destination size
		SaveRegisters();
		Procesor::incCOUNT();
		unsigned short zmienna = stoi(C2);
		if (truncate(C1, zmienna))
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " File size has been changed to :  " << zmienna << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "TR2")//truncate 2
	{
		std::string C3;
		C1 = GetCommand();//file name
		C2 = GetCommand();//destination size
		C3 = GetCommand();//folder name
		SaveRegisters();
		Procesor::incCOUNT();
		unsigned short zmienna = stoi(C2);
		if (truncate(C1, zmienna, C3))
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " File size has been changed to :  " << zmienna << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "RD1")//Read
	{
		C1 = GetCommand();//file name
		C2 = GetCommand();//destination size
		SaveRegisters();
		Procesor::incCOUNT();
		unsigned short zmienna = stoi(C2);
		char* buffer = new char[1];
		short int zmienna2 = read(C1, buffer, zmienna);
		if (zmienna2 != 0)
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Number of bytes: " << zmienna2 << " Read" << std::endl;
			for (int i = 0; i < zmienna2; i++)
			{
				std::cout << buffer[i];
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " It couldn't be read" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "RD2")//Read 2
	{
		std::string C3;
		C1 = GetCommand();//file name
		C2 = GetCommand();//destination size
		C3 = GetCommand();//destination size
		SaveRegisters();
		Procesor::incCOUNT();
		unsigned short zmienna = stoi(C2);
		char* buffer = new char[1];
		short int zmienna2 = read(C1, buffer, zmienna, C3);
		if (zmienna2 != 0)
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Number of bytes: " << zmienna2 << " Read" << std::endl;
			for (int i = 0; i < zmienna2; i++)
			{
				std::cout << buffer[i];
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "RD3")//Read 3
	{
		std::string C3;
		C1 = GetCommand();//file name
		C2 = GetCommand();//destination size
		C3 = GetCommand();//destination size
		SaveRegisters();
		Procesor::incCOUNT();
		unsigned short rd3 = stoi(C3);
		unsigned short zmienna = stoi(C2);
		char* buffer = new char[1];
		short int zmienna2 = read(C1, buffer, zmienna, rd3);
		if (zmienna2 != 0)
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Number of bytes: " << zmienna2 << " Read" << std::endl;
			for (int i = 0; i < zmienna2; i++)
			{
				std::cout << buffer[i];
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "RD4")//Read 3
	{
		std::string C3, C4;
		C1 = GetCommand();//file name
		C2 = GetCommand();//destination size
		C3 = GetCommand();//destination size
		C4 = GetCommand();//destination size
		SaveRegisters();
		Procesor::incCOUNT();
		unsigned short rd3 = stoi(C3);
		unsigned short zmienna = stoi(C2);
		char* buffer = new char[1];
		short int zmienna2 = read(C1, buffer, zmienna, rd3, C4);
		if (zmienna2 != 0)
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Number of bytes: " << zmienna2 << " Read" << std::endl;
			for (int i = 0; i < zmienna2; i++)
			{
				std::cout << buffer[i];
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}

	if (command == "WR1")//Write 1
	{
		C1 = GetCommand();//file name
		C2 = GetCommand();//what we want to save
		SaveRegisters();
		Procesor::incCOUNT();
		std::vector<char> kontener;
		for (int i = 0; i < C2.size(); i++)
		{
			kontener.push_back(C2[i]);
		}
		short int size = write(C1, kontener);
		if (size != 0)
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Number of bytes: " << size << " saved on disc" << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "WR2")//Write 2
	{
		std::string C3;
		C1 = GetCommand();//file name
		C2 = GetCommand();//what we want to save
		C3 = GetCommand();//parent directory
		SaveRegisters();
		Procesor::incCOUNT();
		std::vector<char> kontener;
		for (int i = 0; i < C2.size(); i++)
		{
			kontener.push_back(C2[i]);
		}
		short int size = write(C1, kontener, C3);
		if (size != 0)
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Number of bytes: " << size << " saved on disc" << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "WR3")//Write 3
	{
		std::string C3;

		C1 = GetCommand();//file name
		C2 = GetCommand();//what we want to save
		C3 = GetCommand();//place in file
		SaveRegisters();
		Procesor::incCOUNT();
		std::vector<char> kontener;
		unsigned short place = stoi(C3);
		for (int i = 0; i < C2.size(); i++)
		{
			kontener.push_back(C2[i]);
		}
		short int size = write(C1, kontener, place);
		if (size != 0)
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Number of bytes: " << size << " saved on disc" << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "WR4")//Write 4
	{
		std::string C3, C4;

		C1 = GetCommand();//file name
		C2 = GetCommand();//what we want to save
		C3 = GetCommand();//place in file
		C4 = GetCommand();//parent directory
		SaveRegisters();
		Procesor::incCOUNT();
		std::vector<char> kontener;
		unsigned short place = stoi(C3);
		for (int i = 0; i < C2.size(); i++)
		{
			kontener.push_back(C2[i]);
		}
		short int size = write(C1, kontener, place, C4);
		if (size != 0)
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Number of bytes: " << size << " saved on disc" << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "LS1")//lseek
	{
		std::string C3;
		C1 = GetCommand();//file name
		C2 = GetCommand();//what we want to save
		C3 = GetCommand();//place in file
		SaveRegisters();
		Procesor::incCOUNT();
		short int c2 = stoi(C2);
		unsigned short int c3 = stoi(C3);
		short int pozycja = lseek(C1, c2, c3);
		if (pozycja != -1)
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " The position on pointer has been changed to: " << pozycja << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
		


	}
	if (command == "LS2")//lseek2
	{
		std::string C3, C4;
		C1 = GetCommand();//file name
		C2 = GetCommand();//what we want to save
		C3 = GetCommand();//place in file
		C4 = GetCommand();//parent directory
		SaveRegisters();
		Procesor::incCOUNT();
		short int c2 = stoi(C2);
		unsigned short int c3 = stoi(C3);
		short int pozycja = lseek(C1, c2, c3, C4);
		if (pozycja != -1)
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " The position on pointer has been changed to: " << pozycja << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}

	if (command == "FC1")//folder create
	{
		C1 = GetCommand();//folder name
		C2 = GetCommand();//folder name in which we want to save
		SaveRegisters();
		Procesor::incCOUNT();
		if (fcreate(C1, C2))
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Folder has been created. " << C2 << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "FC2")//folder create2
	{
		std::string C3;
		C1 = GetCommand();//folder create
		C2 = GetCommand();//folder name in which we want to save
		C3 = GetCommand();//parent directory
		SaveRegisters();
		Procesor::incCOUNT();
		if (fcreate(C1, C2, C3))
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Folder has been created. " << C2 << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments" << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "FD1")//delete folder 1
	{
		C1 = GetCommand();
		SaveRegisters();
		Procesor::incCOUNT();
		if (fdelete(C1))
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Folder has been deleted. " << C1 << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments " << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "FD2")//delete folder 2
	{
		C1 = GetCommand();
		C2 = GetCommand();
		SaveRegisters();
		Procesor::incCOUNT();
		if (fdelete(C1, C2))
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Folder has been deleted. " << C1 << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments " << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "FEC1")//creating directory entry 1
	{
		std::string C3;
		C1 = GetCommand();//file name in which we want to work
		C2 = GetCommand();//entry name
		C3 = GetCommand();//file name in which we add
		SaveRegisters();
		Procesor::incCOUNT();
		if (fecreate(C1, C2, fsearch(C3, 0)))
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Directory entry has been created " << C2 << " in folder " << C1 << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments " << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "FEC2")//creating directory entry 2 , file entry create FEC
	{
		std::string C3, C4;
		C1 = GetCommand();//file name in which we want to work
		C2 = GetCommand();//entry name
		C3 = GetCommand();//file name in which we add
		C4 = GetCommand();//parent directory
		SaveRegisters();
		Procesor::incCOUNT();
		if (fecreate(C1, C2, fsearch(C3, 0, C4), C4))
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Directory entry has been created " << C2 << " in folder " << C1 << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER] " << red << " Incorrect arguments " << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "FED1")//file entry delete 1
	{
		C1 = GetCommand();//entry name
		SaveRegisters();
		Procesor::incCOUNT();
		if (fedelete(C1))
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Entry has been deleted " << C1 << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments " << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "FED2")//file entry delete 2
	{
		C1 = GetCommand();//entry name
		C2 = GetCommand();//parent directory
		SaveRegisters();
		Procesor::incCOUNT();
		if (fedelete(C1, C2))
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Entry has been deleted " << C1 << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments " << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "FR1")//file rename
	{

		C1 = GetCommand();//oryginal name
		C2 = GetCommand();//new name
		SaveRegisters();
		Procesor::incCOUNT();
		if (frename(C1, C2))
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Name " << C1 << " has been changed to:  " << C2 << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments " << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}

	}
	if (command == "FR2")//file rename 2
	{

		std::string C3;
		C1 = GetCommand();//oryginal name
		C2 = GetCommand();//new name
		C3 = GetCommand();//parent directory
		SaveRegisters();
		Procesor::incCOUNT();
		if (frename(C1, C2, C3))
		{
			std::cout << yellow << "[ASSEMBLER]" << white << " Name " << C1 << " has been changed to:  " << C2 << std::endl;
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Incorrect arguments " << white << std::endl;
			Procesor::REMOVE(pcb);
			deleteFromMemory(pcb->PID);
			drzewko.kill(pcb->PID);
			Procesor::incCOUNT();
			return;
		}
	}
	if (command == "FCO1")//displaying directory entry 1
	{
		C1 = GetCommand();//oryginal folder name
		SaveRegisters();
		Procesor::incCOUNT();
		std::vector<FEntry> entries = fcontent(C1);
		std::cout << yellow << "[ASSEMBLER]" << white << " " << std::endl;
		for (int i = 0; i < entries.size(); i++)
		{
			std::cout << entries[i];
		}
	}
	if (command == "FCO2")//displaying directory entry 2
	{
		C1 = GetCommand();//oryginal folder name
		C2 = GetCommand();//parent directory
		SaveRegisters();
		Procesor::incCOUNT();
		std::vector<FEntry> entries = fcontent(C1, C2);
		std::cout << yellow << "[ASSEMBLER]" << white << " " << std::endl;
		for (int i = 0; i < entries.size(); i++)
		{
			std::cout << entries[i];
		}
	}
	if (command == "DFC")//display folder contains
	{
		C1 = GetCommand();// folder name
		SaveRegisters();
		Procesor::incCOUNT();
		drawFolderContents(C1);
	}
	if (command == "DB")//display disc block
	{
		C1 = GetCommand();//block disc numbers
		SaveRegisters();
		Procesor::incCOUNT();
		unsigned short int zmienna = stoi(C1);
		drawBlockD(zmienna);

	}
	if (command == "DD")//draw disck
	{
		std::cout << std::endl;
		drawDiscD();
		SaveRegisters();
		Procesor::incCOUNT();

	}
	if (command == "DI")//draw i node
	{
		C1 = GetCommand();//block disc numer
		unsigned short int zmienna = stoi(C1);
		drawInode(zmienna);
		SaveRegisters();
		Procesor::incCOUNT();
	}
	/////processes
	if (command == "CP")//creating process
	{
		C1 = GetCommand();//process name
		std::cout << C1 << std::endl;
		if (drzewko.fork(pcb, C1))
		{
			SaveRegisters();
		}
		else
		{
			PCB* temp = Procesor::getRunning();
			Procesor::REMOVE(temp);
			deleteFromMemory(temp->PID);
			drzewko.kill(temp->PID);
			Procesor::incCOUNT();
			return;
		}
		Procesor::incCOUNT();	
	}

	//PIPeLINES
	if (command == "CPL")// create pipeline
	{
		C1 = GetCommand();
		C2 = GetCommand();
		std::cout << C1 << " "<<C2<<std::endl;
		PCB *temp = drzewko.findpcb(C1);
		PCB *temp2 = drzewko.findpcb(C2);
		Pipeline::createPipe(temp, temp2);
		SaveRegisters();
		Procesor::incCOUNT();
	}
	if (command == "DPL")//delete pipeline
	{
		C1 = GetCommand();
		std::cout << C1 << std::endl;
		PCB *temp = drzewko.findpcb(C1);
		Pipeline::deletePipe(temp);
		SaveRegisters();
		Procesor::incCOUNT();
	}
	if (command == "RPIP")//reading from buffor
	{
		PCB* temp1 = Procesor::getRunning();
		std::string C3;
		C1 = GetCommand();
		C2 = GetCommand();
		C3 = GetCommand();
		std::cout << C1 << " " << C2 <<" "<<C3<< std::endl;
		PCB *temp = drzewko.findpcb(C1);
		PCB *temp2 = drzewko.findpcb(C2);
		unsigned int temp3 = stoi(C3);
		Pipeline::GetPipe(temp->PID, temp2->PID)->read(temp3);
		if (temp1->state != WAITING)
		{
			SaveRegisters();
		}
		Procesor::incCOUNT();
	}

	if (command == "WPIP")//writing to buffor
	{
		PCB* temp1 = Procesor::getRunning();
		std::string C3;
		C1 = GetCommand();
		C2 = GetCommand();
		C3 = GetCommand();
		std::cout << C1 << " " << C2 << " " << C3 << std::endl;
		PCB *temp = drzewko.findpcb(C1);
		PCB *temp2 = drzewko.findpcb(C2);
		Pipeline::GetPipe(temp->PID, temp2->PID)->write(C3);
		if (temp1->state != WAITING)
		{
			SaveRegisters();
		}
		Procesor::incCOUNT();
	}

	// LOCKS
	
	if (command == "LL")//lock lock
	{
		std::cout << std::endl;
		PCB* temp = Procesor::getRunning();
		SaveRegisters();
		lock_l(zamek, temp);
		Procesor::incCOUNT();
	}

	if (command == "LU")//lock unlock
	{
		std::cout << std::endl;
		lock_u(zamek);
		SaveRegisters();
		Procesor::incCOUNT();
	}
	
	//program end
	if (command[0] == 'R'&&command[1] == 'S'&& command[2] == 'T')
	{
		std::cout << std::endl;
		PCB* temp = Procesor::getRunning();
		Procesor::REMOVE(temp);
		deleteFromMemory(temp->PID);
		drzewko.kill(temp->PID);
		Procesor::incCOUNT();
	}

	//killing process
	if (command[0] == 'K'&&command[1] == 'P')
	{
		C1 = GetCommand();
		if (drzewko.findpcb(C1)->PID != Procesor::getRunning()->PID)
		{
			PCB* temp = drzewko.findpcb(C1);
			deleteFromMemory(temp->PID);
			if(temp->state != NEW)
				Procesor::REMOVE(drzewko.findpcb(C1));
			drzewko.kill(temp->PID);
			std::cout << C1 << std::endl;
			std::cout << yellow << "[ASSEMBLER]" << white << " Process has been killed " << C1 << std::endl;
			SaveRegisters();
		
		}
		else
		{
			std::cout << yellow << "[ASSEMBLER]" << red << " Process can't kill himself " << white << std::endl;
			PCB* temp = Procesor::getRunning();
			Procesor::REMOVE(temp);
			deleteFromMemory(temp->PID);
			drzewko.kill(temp->PID);
			Procesor::incCOUNT();
			return;
		}
		Procesor::incCOUNT();
	}
}





