#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<list>

using namespace std;




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

Calculator::Calculator(const string& calculation) {
	string s = calculation;

	split(s, units);

	current = units.front();
}

void Calculator::next() {
	units.pop_front();
	if (!units.empty()) {
		current = units.front();

	}
	else {
		current = string();
	}
}

int Calculator::exp() {
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

int Calculator::term() {
	int result = factor();
	while (current == "*" || current == "/") {
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

int Calculator::factor() {
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

int Calculator::toInt(const string& s) {
	stringstream ss;
	ss << s;
	int x;
	ss >> x;
	return x;
}


int calculate(string s) {
	Calculator calculator(s);
	return calculator.exp();
}

int main() {
	string calculation;

	
	fstream rfile("computation_in.txt");
	ofstream wfile("computation_out.txt");
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
