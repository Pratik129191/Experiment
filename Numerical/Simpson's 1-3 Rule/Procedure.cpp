#include<iostream>
#include<string>
#include<cstdlib>
//#include<corecrt_math_defines.h>
#include<cmath>
#define _USE_MATH_DEFINES
#define WHITE "\033[0;37m"
#define RED_BACKGROUND "\033[41m"
#define YELLLOW_BACKGROUND "\033[43m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"
#define SIN '0'
#define COS '1'
#define TAN '2'
#define COSEC '3'
#define SEC '4'
#define COT '5'
using namespace std;

typedef struct coefficients_and_exponents
{
	double coef;
	double expo;
}values;

typedef struct coefficients_and_exponents_of_trigonometry
{
	double coef;
	double expo;
	double x_coef;
	char fnctn;
}trigo_values;

//function declaration part for polynomial functions ----
string take_input_equation();
int count_terms(string eqtn);
bool is_any_x_in_term(string test);
bool is_any_trigonometric_function(string eqtn);
string get_signs(string eqtn);
values* get_eqtn_in_numerical_poly(string* splt_eqtn, int length);
string* rearrange_input_equation(string* splt_eqtn, int length);
string* split_input_equation(string eqtn);
double calculate_functional_value(values* terms, string signs, double x, int length);
double solution_polynomial(values* terms, string signs, int length, double upper_range, double lower_range, double n_intervals, double h_spacing);

//function declaration part for polynomial functions ----
double convert_range_to_double(string str);
double convert_degree_to_radian(double degree);
string get_trigonometric_function(string term);
string insert_characters(int pos, string main, string input);
string* rearrange_input_equation_trigo(string* splt_eqtn, int length);
trigo_values* get_equation_in_numerical(string* splt_eqtn, int length);
double calculate_functional_value(trigo_values* terms, int length, string signs, double x_val);
double solution(trigo_values* terms, int length, string signs, double upper_range, double lower_range, double n_intervals, double h_spacing);

int main()
{
	string eqtn = take_input_equation();
	double upper_range = 0;
	double lower_range = 0;
	int length = count_terms(eqtn);
	string signs = get_signs(eqtn);
	string* splt_eqtn = split_input_equation(eqtn);
	
	if (is_any_trigonometric_function(eqtn) == true)
	{
		string up, low;
		cout << "Enter The Upper Range:\t";
		getline(cin, up);
		cout << "Enter The Lower Range:\t";
		getline(cin, low);
		if (up.find("pi") < up.length())
		{
			upper_range = convert_range_to_double(up);
		}
		else
		{
			upper_range = convert_degree_to_radian(stod(up));

		}
		if (low.find("pi") < low.length())
		{
			lower_range = convert_range_to_double(low);
		}
		else
		{
			lower_range = convert_degree_to_radian(stod(low));
		}

		double n_intervals;
		cout << "Enter The Number of Intervals:\t";
		cin >> n_intervals;
		double h_spacing = ((upper_range - lower_range) / n_intervals);

		splt_eqtn = rearrange_input_equation_trigo(splt_eqtn, length);
		trigo_values* terms = get_equation_in_numerical(splt_eqtn, length);
		double final_value = solution(terms, length, signs, upper_range, lower_range, n_intervals, h_spacing);
		cout << endl << YELLOW << "The Result of the Integration is:  " << final_value << endl << RESET;
	}
	else
	{
		cout << "Enter The Upper Range:\t";
		cin >> upper_range;
		cout << "Enter The Lower Range:\t";
		cin >> lower_range;
		double n_intervals;
		cout << "Enter The Number of Intervals (n) :\t";
		cin >> n_intervals;
		double h_spacing = ((upper_range - lower_range) / n_intervals);
		splt_eqtn = rearrange_input_equation(splt_eqtn, length);
		values* terms = get_eqtn_in_numerical_poly(splt_eqtn, length);
		double final_value = solution_polynomial(terms, signs, length, upper_range, lower_range, n_intervals, h_spacing);
		cout << endl << YELLOW << "The Result of the Integration is:  " << final_value << endl << RESET;
	}
}

string take_input_equation()
{
	cout << endl << GREEN << "\t\t\t<===: Integration By Simpson's 1/3 Rule :===>" << endl << endl;
	cout << RED;
	cout << "           <------- For Giving Input of Polynomial Functions ------->                 " << endl;
	cout << "Example Function:   " << YELLLOW_BACKGROUND << "-x^3 + 5x^-2 - x^2 - x + 17  " << RESET << RED << "                                     " << endl << endl;
	cout << "           <------- For Giving Input of Trigonometric Functions ------->              " << endl;
	cout << "Example Function:   " << YELLLOW_BACKGROUND << "-4sinx + 5cos^(-5)x - tan^(4)5x + cosec6x - 7sec5x + 9cot^(5)-4x  " << RESET << RED << endl;
	cout << "Input type of range in Radians is -->  pi, pi/2, 2pi                                  " << endl;
	cout << "Functions Coefficients is at first of the term, with sign (if negative)               " << endl;
	cout << "Functions Exponent is within the Paranthesis (except 1)                               " << endl;
	cout << "X's coefficient is just after close paranthesis, with sign (if negative)              " << endl << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "+       Don't Mistake to give space before & after of signs between two terms.       +" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << RESET;
	string str; 
	cout << endl << "Enter The Function:\t"<<BLUE;
	getline(cin, str);
	cout << RESET;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == 'X')
		{
			str.replace(i, 1, "x");
		}
	}
	return str;
}

int count_terms(string eqtn)
{
	int count = 0;
	for (int i = 0; i < eqtn.length(); i++)
	{
		if (eqtn[i] == ' ')
		{
			count++;
			i += 2;
		}
	}
	return (count + 1);
}

bool is_any_x_in_term(string test)
{
	bool flag = false;
	for (int i = 0; i < test.length(); i++)
	{
		if (test[i] == 'x')
		{
			return true;
		}
	}
	return flag; 
}

bool is_any_trigonometric_function(string eqtn)
{
	bool flag = false;
	if (eqtn.find("sin") < eqtn.length() || eqtn.find("cos") < eqtn.length() || eqtn.find("tan") < eqtn.length() || eqtn.find("sec") < eqtn.length() || eqtn.find("cosec") < eqtn.length() || eqtn.find("cot") < eqtn.length())
	{
		flag = true;
	}
	return flag;
}

string get_signs(string eqtn)
{
	string signs = "";
	for (int i = 0; i < eqtn.length(); i++)
	{
		if (eqtn[i] == ' ')
		{
			if (eqtn[i + 1] == '+')
			{
				signs.append("+");
			}
			if (eqtn[i + 1] == '-')
			{
				signs.append("-");
			}
			i+=2;
		}
	}
	return signs;
}

values* get_eqtn_in_numerical_poly(string* splt_eqtn, int length)
{
	values* terms = (values*)malloc(25 * sizeof(values));
	if (terms == NULL)
	{
		puts("Malloc Failed.");
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			string temp = "";
			for (int j = 0; j < splt_eqtn[i].find("x"); j++)
			{
				temp += splt_eqtn[i][j];
			}
			//cout << temp << endl;
			terms[i].coef = stod(temp);
			temp = "";

			for (int j = (splt_eqtn[i].find("^") + 1); j < splt_eqtn[i].length(); j++)
			{
				temp += splt_eqtn[i][j];
			}
			//cout << temp << endl;
			terms[i].expo = stod(temp);
			temp = "";
		}
	}
	return terms;
}

string* rearrange_input_equation(string* splt_eqtn, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (is_any_x_in_term(splt_eqtn[i]) == true)
		{
			if (splt_eqtn[i].find("x") == 0)
			{
				splt_eqtn[i].insert(0, 1, '1');
				if (splt_eqtn[i].length() == 1)
				{
					splt_eqtn[i].append("^1");
				}
			}
			if (splt_eqtn[i][splt_eqtn[i].find("x") - 1] == '-')
			{
				int loc = splt_eqtn[i].find("x");
				splt_eqtn[i].insert(loc, 1, '1');
			}
			if (splt_eqtn[i].find("x") == splt_eqtn[i].length() - 1)
			{
				splt_eqtn[i].append("^1");
			}
		}
		if (is_any_x_in_term(splt_eqtn[i]) == false)
		{
			splt_eqtn[i].append("x^0");
		}
	}
	return splt_eqtn;
}

string* split_input_equation(string eqtn)
{
	string* splt_eqtn = new string[25];
	int x = 0;
	string temp = "";
	for (int i = 0; i < eqtn.length(); i++)
	{
		if (eqtn[i] == ' ')
		{
			splt_eqtn[x] = temp;
			x++;
			temp = "";
			i += 2;
		}
		else
		{
			temp += eqtn[i];
		}
	}
	splt_eqtn[x] = temp;
	return splt_eqtn;
}

double calculate_functional_value(values* terms, string signs, double x, int length)
{
	int k = 0;
	double f_val = (terms[0].coef * pow(x, terms[0].expo));
	for (int i = 1; i < length; i++)
	{
		if (signs[k] == '+')
		{
			k++;
			f_val = f_val + (terms[i].coef * pow(x, terms[i].expo));
		}
		if (signs[k] == '-')
		{
			k++;
			f_val = f_val - (terms[i].coef * pow(x, terms[i].expo));
		}
	}
	return f_val;
}

double solution_polynomial(values* terms, string signs, int length, double upper_range, double lower_range, double n_intervals, double h_spacing)
{
	double even_sum_2 = 0;
	double x[50], y[50];
	int k = 0;
	x[k] = lower_range;
	y[k] = calculate_functional_value(terms, signs, lower_range, length);
	k = 2;
	for (double i = (lower_range + (2 * h_spacing)); i < upper_range; i += (2 * h_spacing))
	{
		double temp = calculate_functional_value(terms, signs, i, length);
		even_sum_2 = even_sum_2 + temp;
		x[k] = i;
		y[k] = temp;
		k += 2;
	}

	double odd_sum_4 = 0;
	k = 1;
	for (double i = (lower_range + (h_spacing)); i < upper_range; i += (2 * h_spacing))
	{
		double temp = calculate_functional_value(terms, signs, i, length);
		odd_sum_4 = odd_sum_4 + temp;
		x[k] = i;
		y[k] = temp;
		k += 2;
	}
	
	k = (int)n_intervals;
	x[k] = upper_range;
	y[k] = calculate_functional_value(terms, signs, upper_range, length);

	double final_value = 0;
	final_value = (h_spacing / 3) * (calculate_functional_value(terms, signs, lower_range, length) + (2 * even_sum_2) + (4 * odd_sum_4) + calculate_functional_value(terms, signs, upper_range, length));

	cout <<endl<< GREEN << "     <---- Calculation Table of x & f(x) ---->" << RESET << endl << endl;
	cout << "     " << WHITE << RED_BACKGROUND<< "   x   " << RESET << "\t               \t     " << WHITE<< RED_BACKGROUND<< "   f(x)   " << RESET << endl;
	for (int i = 0; i <= (int)n_intervals; i++)
	{
		cout << "\t" << x[i] << "\t:==========---> \t" << y[i] << endl;
	}
	return final_value;
}

double convert_range_to_double(string str)
{
	double val = 0;
	if (str == "0")
	{
		val = 0;
	}

	if (str.find("/") < str.length())
	{
		string temp = "";
		for (int i = (int)str.find("/") + 1; i < (int)str.length(); i++)
		{
			temp += str[i];
		}
		val = M_PI / stod(temp);
	}
	else
	{
		string temp = "";
		for (int i = 0; i < str.find("pi"); i++)
		{
			temp += str[i];
		}
		val = stod(temp) * M_PI;
	}
	return val;
}

double convert_degree_to_radian(double degree)
{
	double radian = degree * (M_PI / 180);
	return radian;
}

string get_trigonometric_function(string term)
{
	string temp = "";
	if (term.find("sin") < term.length())
	{
		temp = "0sin";
	}
	else if (term.find("cos") < term.length())
	{
		temp = "1cos";
		if (term.find("cosec") < term.length())
		{
			temp = "3cosec";
		}
	}
	else if (term.find("tan") < term.length())
	{
		temp = "2tan";
	}
	else if (term.find("sec") < term.length())
	{
		temp = "4sec";
	}
	else if (term.find("cot") < term.length())
	{
		temp = "5cot";
	}
	return temp;
}

string insert_characters(int pos, string main, string input)
{
	if (input.length() == 1)
	{
		main.insert(pos, 1, input[0]);
	}
	else
	{
		for (int i = 0; i < input.length(); i++)
		{
			main.insert(pos, 1, input[i]);
			pos++;
		}
	}
	return main;
}

string* rearrange_input_equation_trigo(string* splt_eqtn, int length)
{
	for (int i = 0; i < length; i++)
	{
		string temp = get_trigonometric_function(splt_eqtn[i]);
		temp.erase(0, 1);
		if (temp == "cosec")
		{
			if (splt_eqtn[i][0] == '-')
			{
				splt_eqtn[i].insert(splt_eqtn[i].find(temp), 1, '1');
			}
			if (splt_eqtn[i].find(temp) == 0)
			{
				splt_eqtn[i] = insert_characters(0, splt_eqtn[i], "1");
			}
			if (splt_eqtn[i][splt_eqtn[i].find(temp) + 5] != '^')
			{
				splt_eqtn[i] = insert_characters((int)(splt_eqtn[i].find(temp) + 5), splt_eqtn[i], "^(1)");
			}
			if (splt_eqtn[i].find("x") == (splt_eqtn[i].find(")") + 1))
			{
				splt_eqtn[i].insert(splt_eqtn[i].find("x"), 1, '1');
			}
		}
		else
		{
			if (splt_eqtn[i][0] == '-')
			{
				splt_eqtn[i].insert(splt_eqtn[i].find(temp), 1, '1');
			}
			if (splt_eqtn[i].find(temp) == 0)
			{
				splt_eqtn[i] = insert_characters(0, splt_eqtn[i], "1");
			}
			if (splt_eqtn[i][splt_eqtn[i].find(temp) + 3] != '^')
			{
				splt_eqtn[i] = insert_characters((int)(splt_eqtn[i].find(temp) + 3), splt_eqtn[i], "^(1)");
			}
			if (splt_eqtn[i].find("x") == (splt_eqtn[i].find(")") + 1))
			{
				splt_eqtn[i].insert(splt_eqtn[i].find("x"), 1, '1');
			}
		}
	}
	return splt_eqtn;
}

trigo_values* get_equation_in_numerical(string* splt_eqtn, int length)
{
	trigo_values* terms = (trigo_values*)malloc(25 * sizeof(trigo_values));
	string temp = "";
	if (terms == NULL)
	{
		puts("Malloc Failed");
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			string func = get_trigonometric_function(splt_eqtn[i]);
			terms[i].fnctn = func[0];
			func.erase(0, 1);

			int loc = (int)splt_eqtn[i].find(func);
			for (int j = 0; j < loc; j++)
			{
				temp += splt_eqtn[i][j];
			}
			terms[i].coef = stod(temp);
			temp = "";

			loc = (int)splt_eqtn[i].find("(");
			for (int j = loc + 1; j < splt_eqtn[i].find(")"); j++)
			{
				temp += splt_eqtn[i][j];
			}
			terms[i].expo = stod(temp);
			temp = "";

			loc = (int)splt_eqtn[i].find(")");
			for (int j = loc + 1; j < splt_eqtn[i].find("x"); j++)
			{
				temp += splt_eqtn[i][j];
			}
			terms[i].x_coef = stod(temp);
			temp = "";
		}
	}
	return terms;
}

double calculate_functional_value(trigo_values* terms, int length, string signs, double x_val)
{
	double f_val = 0, temp = 0;
	int x = 0;
	switch (terms[0].fnctn)
	{
	case SIN:
		temp = sin(terms[0].x_coef * x_val);
		temp = pow(temp, terms[0].expo);
		f_val = (temp * terms[0].coef);
		break;
	case COS:
		temp = cos(terms[0].x_coef * x_val);
		temp = pow(temp, terms[0].expo);
		f_val = (temp * terms[0].coef);
		break;
	case TAN:
		temp = tan(terms[0].x_coef * x_val);
		temp = pow(temp, terms[0].expo);
		f_val = (temp * terms[0].coef);
		break;
	case COSEC:
		temp = (1 / (sin(terms[0].x_coef * x_val)));
		temp = pow(temp, terms[0].expo);
		f_val = (temp * terms[0].coef);
		break;
	case SEC:
		temp = (1 / (cos(terms[0].x_coef * x_val)));
		temp = pow(temp, terms[0].expo);
		f_val = (temp * terms[0].coef);
		break;
	case COT:
		temp = (1 / (tan(terms[0].x_coef * x_val)));
		temp = pow(temp, terms[0].expo);
		f_val = (temp * terms[0].coef);
		break;
	}

	x = 0;
	for (int i = 1; i < length; i++)
	{
		switch (terms[i].fnctn)
		{
		case SIN:
			temp = sin(terms[i].x_coef * x_val);
			temp = pow(temp, terms[i].expo);
			if (signs[x] == '+')
			{
				f_val = f_val + (temp * terms[i].coef);
			}
			else if (signs[x] == '-')
			{
				f_val = f_val - (temp * terms[i].coef);
			}
			break;
		case COS:
			temp = cos(terms[i].x_coef * x_val);
			temp = pow(temp, terms[i].expo);
			if (signs[x] == '+')
			{
				f_val = f_val + (temp * terms[i].coef);
			}
			else if (signs[x] == '-')
			{
				f_val = f_val - (temp * terms[i].coef);
			}
			break;
		case TAN:
			temp = tan(terms[i].x_coef * x_val);
			temp = pow(temp, terms[i].expo);
			if (signs[x] == '+')
			{
				f_val = f_val + (temp * terms[i].coef);
			}
			else if (signs[x] == '-')
			{
				f_val = f_val - (temp * terms[i].coef);
			}
			break;
		case COSEC:
			temp = (1 / (sin(terms[i].x_coef * x_val)));
			temp = pow(temp, terms[i].expo);
			if (signs[x] == '+')
			{
				f_val = f_val + (temp * terms[i].coef);
			}
			else if (signs[x] == '-')
			{
				f_val = f_val - (temp * terms[i].coef);
			}
			break;
		case SEC:
			temp = (1 / (cos(terms[i].x_coef * x_val)));
			temp = pow(temp, terms[i].expo);
			if (signs[x] == '+')
			{
				f_val = f_val + (temp * terms[i].coef);
			}
			else if (signs[x] == '-')
			{
				f_val = f_val - (temp * terms[i].coef);
			}
			break;
		case COT:
			temp = (1 / (tan(terms[i].x_coef * x_val)));
			temp = pow(temp, terms[i].expo);
			if (signs[x] == '+')
			{
				f_val = f_val + (temp * terms[i].coef);
			}
			else if (signs[x] == '-')
			{
				f_val = f_val - (temp * terms[i].coef);
			}
			break;
		}
		x++;
	}
	return f_val;
}

double solution(trigo_values* terms, int length, string signs, double upper_range, double lower_range, double n_intervals, double h_spacing)
{
	double even_sum_2 = 0;
	double x[50], y[50];
	int k = 0;
	x[k] = lower_range;
	y[k] = calculate_functional_value(terms, length, signs, lower_range);
	k = 2;
	for (double i = (lower_range + (2 * h_spacing)); i < upper_range; i += (2 * h_spacing))
	{
		double temp = calculate_functional_value(terms, length, signs, i);
		even_sum_2 = even_sum_2 + temp;
		x[k] = i;
		y[k] = temp;
		k += 2;
	}

	double odd_sum_4 = 0;
	k = 1;
	for (double i = (lower_range + (h_spacing)); i < upper_range; i += (2 * h_spacing))
	{
		double temp = calculate_functional_value(terms, length, signs, i);
		odd_sum_4 = odd_sum_4 + temp;
		x[k] = i;
		y[k] = temp;
		k += 2;
	}

	k = (int)n_intervals;
	x[k] = upper_range;
	y[k] = calculate_functional_value(terms, length, signs, upper_range);

	double final_value = 0;
	final_value = (h_spacing / 3) * (calculate_functional_value(terms, length, signs, lower_range) + (2 * even_sum_2) + (4 * odd_sum_4) + calculate_functional_value(terms, length, signs, upper_range));

	cout << endl << GREEN << "     <---- Calculation Table of x & f(x) ---->" << RESET << endl << endl;
	cout << "     " << WHITE << RED_BACKGROUND << "   x   " << RESET << "\t               \t     " << WHITE << RED_BACKGROUND << "   f(x)   " << RESET << endl;
	for (int i = 0; i <= (int)n_intervals; i++)
	{
		cout << "\t" << x[i] << "\t\t\t" << y[i] << endl;
	}
	return final_value;
}
