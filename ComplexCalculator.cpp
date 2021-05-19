#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<list>
#include<cmath>
using namespace std;



// outputs a list of strings
void split(const string& str, list<string>& units) {
	string num;
	int N = str.size();

	for (int i = 0; i < N; ++i) {
		char c = str[i];
		if (isdigit(c)) {
			num += c;
			

		}
		else {
			if (!num.empty()) {
				units.push_back(num);
				num.clear();

			}
			string unit;
			unit += c;
			units.push_back(unit);

		}
	}
	if (!num.empty()) {
		units.push_back(num);
		
		num.clear();
	}
}


class Calculator {
public:
	Calculator(const string& calculation);

	void next();
	int exp();
	int term();
	int factor();
	int toInt(const string& s);

private:
	list<string>units;
	string current;
};

/*
The calculator class takes in a string 
it loops through the character of every string
the exp method send the current character to the term method which then sends it to the factor method
this ensures that BEDMAS is being followed*/
Calculator::Calculator(const string& calculation) {
	string s = calculation;

	split(s, units);

	current = units.front(); 
}

void Calculator::next() { // changes the "current" string to the next character of string
	units.pop_front(); 
	if (!units.empty()) {
		current = units.front();

	}
	else {
		current = string(); 
	}
}

int Calculator::exp() { // if it is a + or - currently, that operation is performed, returns the final result as everything calculated ends up here being added/subtracted as the last step
	int result = term();
	while (current == "+" || current == "-"){
		if (current == "+"){
			next();
				result +=term();

		}
		if (current == "-") {
			next();
			result -= term();
		}
	}

	return result;
}

int Calculator::term() { // checks for * or / or ^ and sends to factor 
	int result = factor();
	while (current == "*" || current == "/" || current == "^") {
		if (current == "^") {
			next();
			result = pow(result, factor());
		}
		if (current == "*") {
			next();
			result *= factor();

		}
		if (current == "/") {
			next();
			result /= factor();
			
			

		}
	}
	return result;
}

int Calculator::factor() { // checks for open brackets and then goes back to exp()
	int result;

	if (current == "(") {
		next();
		result = exp();
		next();
	}
	else {
		result = toInt(current);
		next();
	}
	return result;
}

int Calculator::toInt(const string& s) { // converts string character to int for calculations
	stringstream ss;
	ss << s;
	int x;
	ss >> x;
	return x;
}


int calculate(string s) {
	Calculator calculator(s); // creates an object of class calculator
	return calculator.exp(); // exp method will return the final answer as it calls the other methods from within
}

int main() {
	string calculation;

	
	fstream rfile("computation_in.txt"); // file containing calculation to be performed
	ofstream wfile("computation_out.txt"); // file answer is written to
	if (!rfile) {
		cout << "No file" << endl;

	}
	if (rfile.is_open()) {
		while (getline(rfile, calculation)) {
			cout << calculation << endl;


		}
		rfile.close();
	}

	
	


	
	if (!wfile) {
		cout << "File not created";

	}
	else {
		wfile << calculate(calculation);
		cout << "Answer written to file" << endl;
		wfile.close();

	}
	return 0;

}
