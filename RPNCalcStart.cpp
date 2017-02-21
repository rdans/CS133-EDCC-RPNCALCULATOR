#include "RPNCalc.h"
//-------------------------------------------------------------------------------------------
//    Class:		CRPNCalc
//
//    File:             RPNCalc.cpp
//
//    Description:	This file contains the function definitions for CRPNCalc
//
//    Programmer:		
//   
//    Date:             
// 
//    Version:          1.0
//  
//    Environment:	Intel Xeon PC 
//                  	Software:   MS Windows 7 for execution; 
//                  	Compiles under Microsoft Visual C++.Net 2010
// 
//	  class CRPNCalc:
//
//	  Properties:
//				double m_registers[10];
//				stack<string> m_stack;
//				vector<list<string>> m_programs(NUMPROGRAMS);
//				istringstream m_inStrStream;
//	
//
//	  Non-inline Methods:
//	
//				CRPNCalc(bool on)
//				run()
//				print(ostream& ostr)
//				parse()
//				void add() -- 
//				void bin_prep(double& d1, double& d2) -- 
//				void clear() -- 
//				void clearAll() -- 
//				void divide() -- 
//				void exp() -- 
//				void getReg(int reg) -- 
//				void loadProgram() -- 
//				void mod() -- 
//				void multiply() -- 
//				void neg() -- 
//				void parse() -- 
//				void recordProgram() -- 
//				void rotateUp() -- 
//				void rotateDown() -- 
//				void runProgram() -- 
//				void saveToFile() -- 
//				void setReg(int reg) -- 
//				void subtract() -- 
//				void unary_prep(double& d) -- 

//	  related functions:
//				ostream &operator <<(ostream &ostr, const CRPNCalc &calc)
//    				istream &operator >>(istream &istr, CRPNCalc &calc)
//
//    History Log:
//                           
// ----------------------------------------------------------------------------	
namespace PB_CALC
{
	// ----------------------------------------------------------------------------
	//	constructor
	// ----------------------------------------------------------------------------
	CRPNCalc::CRPNCalc(bool on) : m_on(on), m_error(false), m_helpOn(true),
		m_programRunning(false)
	{
		for (int i = 0; i < NUMREGS; i++)
			m_registers[i] = 0.0;
		if (m_on)
			run();
	}

	// ----------------------------------------------------------------------------
	//	starts the calculator running
	// ----------------------------------------------------------------------------
	void CRPNCalc::run()
	{
		if (!m_on)
			EXIT_SUCCESS;
	}

	// ----------------------------------------------------------------------------
	//	prints out calculator screen
	// ----------------------------------------------------------------------------
	void CRPNCalc::print(ostream& ostr)
	{
		double d = 0.0;
		ostr << "[RPN Programmable Calculator] by Paul Bladek" << endl;
		if (m_helpOn)
			cout << helpMenu;
		else
			cout << endl << endl << endl;
		cout << line;
		if (!m_stack.empty())
		{
			d = m_stack.front();
			ostr << d;
		}
		ostr << endl << endl;
		if (m_error)
		{
			ostr << "<<error>>" << endl;
			m_error = false;
		}
	}

	// ----------------------------------------------------------------------------
	//	parses the next command from m_instrStream
	// ----------------------------------------------------------------------------
	void CRPNCalc::parse()
	{

	}

	// ----------------------------------------------------------------------------
	//	if possible, pops top 2 elements from the stack, adds them
	//	  and pushes the result onto the stack
	// ----------------------------------------------------------------------------	
	void CRPNCalc::add()
	{
		double a = m_stack.front();
		m_stack.pop_front();

		double b = m_stack.front();
		m_stack.pop_front();

		binary_prep(a, b);

		m_stack.push_front(a + b);

	}

	// ----------------------------------------------------------------------------
	//	sets the args to the popped values from the stack, if possible
	//	  set error state otherwise
	// ----------------------------------------------------------------------------

	void CRPNCalc::binary_prep(double& d1, double& d2)
	{

	}

	// ----------------------------------------------------------------------------
	//	removes the top element from the stack
	// ----------------------------------------------------------------------------
	void CRPNCalc::clearEntry()
	{
		m_stack.pop_front();
	}

	// ----------------------------------------------------------------------------
	//	empties the stack
	// ----------------------------------------------------------------------------
	void CRPNCalc::clearAll()
	{
		while (!m_stack.empty())
			m_stack.pop_front();
	}

	// ----------------------------------------------------------------------------
	//	if possible, pops top 2 elements from the stack, divides them
	//	  and pushes the result onto the stack
	// ----------------------------------------------------------------------------
	void CRPNCalc::divide()
	{
		double a = m_stack.front();
		m_stack.pop_front();

		double b = m_stack.front();
		m_stack.pop_front();

		m_stack.push_front(a / b);
	}

	// ----------------------------------------------------------------------------
	//	if possible, pops top 2 elements from the stack,
	//	  raises one element to the other power
	//	  and pushes the result onto the stack
	// ----------------------------------------------------------------------------
	void CRPNCalc::exp()
	{
		double a = m_stack.front();
		m_stack.pop_front();

		double b = m_stack.front();
		m_stack.pop_front();

		m_stack.push_front(pow(a, b));
	}

	// ----------------------------------------------------------------------------
	//	pushes the given register's value onto the stack
	// ----------------------------------------------------------------------------
	void CRPNCalc::getReg(int reg)
	{
		m_stack.push_back(m_registers[reg]);
	}

	// ----------------------------------------------------------------------------
	//	retrieves the filename from the user and loads it into m_program
	// ----------------------------------------------------------------------------
	void CRPNCalc::loadProgram()
	{
		string line;
		cout << "Enter the name of the file : ";
		getline(cin, line);

		ifstream myfile(line + ".prog");
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				m_program.push_front(line);
			}
			myfile.close();
		}
		else
			cout << "File cannot be Opened";
	}

	// ----------------------------------------------------------------------------
	//	if possible, pops top 2 elements from the stack, mods them
	//	  and pushes the result onto the stack
	// ----------------------------------------------------------------------------
	void CRPNCalc::mod()
	{
		double a = m_stack.front();
		m_stack.pop_front();

		double b = m_stack.front();
		m_stack.pop_front();

		m_stack.push_front(fmod(a, b));
	}

	// ----------------------------------------------------------------------------
	//	if possible, pops top 2 elements from the stack, multiplies them
	//	  and pushes the result onto the stack
	// ----------------------------------------------------------------------------
	void CRPNCalc::multiply()
	{
		double a = m_stack.front();
		m_stack.pop_front();

		double b = m_stack.front();
		m_stack.pop_front();

		m_stack.push_front(a * b);
	}

	// ----------------------------------------------------------------------------
	//	resets the top element of the stack to it's negative
	// ----------------------------------------------------------------------------
	void CRPNCalc::neg()
	{
		double elem = m_stack.front();
		m_stack.pop_front();

		m_stack.push_front(elem * -1);
	}

	// ----------------------------------------------------------------------------
	//	sets the arg to the popped value from the stack, if possible
	//	  sets error state otherwise
	// ----------------------------------------------------------------------------
	void CRPNCalc::unary_prep(double& d)
	{

	}

	// ----------------------------------------------------------------------------
	//	takes command-line input and loads it into m_program 
	// ----------------------------------------------------------------------------
	void CRPNCalc::recordProgram()
	{
		char c;
		int i = 0;

		

		while (c != 'p')
		{
			cout << i << "> ";
			cin.get(c);
			cout << endl;

			string s(1,c);

			m_program.push_front(s);

			i++;
		}

	}

	// ----------------------------------------------------------------------------
	//	removes the bottom of the stack and adds it to the top
	// ----------------------------------------------------------------------------
	void CRPNCalc::rotateDown()
	{
		double temp = m_stack.back();
		m_stack.pop_back();
		m_stack.push_front(temp);
	}

	// ----------------------------------------------------------------------------
	//	removes the top of the stack and adds it to the bottom
	// ----------------------------------------------------------------------------
	void CRPNCalc::rotateUp()
	{
		double temp = m_stack.front();
		m_stack.pop_front();
		m_stack.push_front(temp);
	}

	// ----------------------------------------------------------------------------
	//	runs the program in m_program 
	// ----------------------------------------------------------------------------
	void CRPNCalc::runProgram()
	{

	}

	// ----------------------------------------------------------------------------
	//	asks the user for a filename and saves m_program to that file
	// ----------------------------------------------------------------------------
	void CRPNCalc::saveToFile()
	{
		string fileName = " ";
		cout << "Enter the name of the file : ";
		getline(cin, fileName);

		ofstream myfile;
		myfile.open(fileName+".prog");

		for (int i = 0; i < m_program.size(); i++)
			myfile << m_program.front();
	}

	// ----------------------------------------------------------------------------
	//	gets the value from the top of the stack
	//	  and places it into the given register
	// ----------------------------------------------------------------------------
	void CRPNCalc::setReg(int reg)
	{
		m_registers[reg] = m_stack.front();
		m_stack.pop_front();
	}

	// ----------------------------------------------------------------------------
	//	if possible, pops top 2 elements from the stack, subtracts them
	//	  and pushes the result onto the stack
	// ----------------------------------------------------------------------------
	void CRPNCalc::subtract()
	{
		double a = m_stack.front();
		m_stack.pop_front();

		double b = m_stack.front();
		m_stack.pop_front();

		m_stack.push_front(b - a);
	}

	// ----------------------------------------------------------------------------
	//	inputs a line from the given stream
	// ----------------------------------------------------------------------------
	void CRPNCalc::input(istream &istr)
	{

	}

	// ----------------------------------------------------------------------------
	//	ostream's << defined for CRPNCalc
	// ----------------------------------------------------------------------------
	ostream &operator <<(ostream &ostr, CRPNCalc &calc)
	{
		calc.print(ostr);
		return ostr;
	}


	// ----------------------------------------------------------------------------
	//	istream's >> defined for CRPNCalc
	// ----------------------------------------------------------------------------
	istream &operator >>(istream &istr, CRPNCalc &calc)
	{
		calc.input(istr);
		return istr;
	}
} // end namespace PB_CALC
