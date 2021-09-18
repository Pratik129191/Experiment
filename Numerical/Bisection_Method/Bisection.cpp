	#include<iostream>
	#include<string>
	#include<cstdlib>
	#include<iomanip>
	#include<cmath>
	// colors for design purpose ----
	#define RED "\u001b[31m"
	#define GREEN "\u001b[32m"
	#define YELLOW "\u001b[33m"
	#define BLUE "\u001b[34m"
	#define WHITE "\u001b[37m"
	#define CYAN "\u001b[36m"
	#define RED_BACKGROUND "\u001b[41m"
	#define WHITE_BACKGROUND "\u001b[47m"
	#define RESET "\u001b[0m"

	using namespace std;

	// function declaration part ----
	string take_input_equation();
	double* initialize_array(double* arr, int length);
	int count_terms(string eqtn);
	string* split_input_equation(string eqtn);
	bool is_any_x_in_term(string str);
	string* re_arrange_splitted_input(string* store, int terms);
	double* get_coefficients(string* store, int terms);
	double* get_exponents(string* store, int terms);
	string get_operators(string eqtn);
	bool is_simultaneously_negative_positive(double* fx_arr, int length);
	double get_functional_value(double trial, double* coef, double* expo, int terms, string op);
	double* get_positive_solution_range(double* coef, double* expo, int terms, string op);
	double* get_negative_solution_range(double* coef, double* expo, int terms, string op);
	double get_value_upto_decimal_place(double x, int decimal_place);
	double get_root_of_equation_in_range(double nr, double pr, double* coef, double* expo, int terms, string op, int decimal_place);

	// design purpose ----
	void show_root_calculation_table(double nr, double pr, double* coef, double* expo, int terms, string op, int decimal_place);

	int main()
	{
		string eqtn = take_input_equation();
		int decimal_place;
		cout << RED << "Answer Should Be Corrected Upto The Decimal Place (Highest 6):\t" << YELLOW;
		cin >> decimal_place;
		cout << RESET << endl;
		string eqtn_copy = eqtn;
		int terms = count_terms(eqtn);
		string* store = split_input_equation(eqtn);
		store = re_arrange_splitted_input(store, terms);
		double* coef = get_coefficients(store, terms);
		double* expo = get_exponents(store, terms);
		string op = get_operators(eqtn);

		/*
		* in solution range
		* 0, 2, 4, 6, ... positions are negative value &
		* 1, 3, 5, 7, ... positions are positive value.
		*/
		double* rangep = get_positive_solution_range(coef, expo, terms, op);
		double* rangen = get_negative_solution_range(coef, expo, terms, op);
		int i = 0;
		while (rangep[i] != NULL)
		{
			cout << "Root is:- " << get_root_of_equation_in_range(rangep[i], rangep[i + 1], coef, expo, terms, op, decimal_place) << " between "<<"( "<<rangep[i]<<" )"<<" and " <<"( "<<rangep[i+1]<<" )"<<endl;
			i += 2;
		}
		i = 0;
		while (rangen[i] != NULL)
		{
			cout<<"Root is:- " << get_root_of_equation_in_range(rangen[i], rangen[i + 1], coef, expo, terms, op, decimal_place) << " between " << "( " << rangen[i] << " )" << " and " << "( " << rangen[i + 1] << " )" << endl;
			i += 2;
		}
		
		again: cout << RED << "Do You Want to See Graphical Output? (Y/N):- " << YELLOW;
		char choose;
		cin >> choose;
		cout << RESET;
		if (choose == 'y' || choose == 'Y')
		{
			i = 0;
			while (rangep[i] != NULL)
			{
				show_root_calculation_table(rangep[i], rangep[i + 1], coef, expo, terms, op, decimal_place);
				i += 2;
			}
			i = 0;
			while (rangen[i] != NULL)
			{
				show_root_calculation_table(rangen[i], rangen[i + 1], coef, expo, terms, op, decimal_place);
				i += 2;
			}
			char c = getchar();
			cout << RED << endl << "Press Enter to Exit:\t" << RESET;
			c = getchar();
		}
		else if (choose == 'n' || choose == 'N')
		{
			exit(0);
		}
		else
		{
			goto again;
		}
	}

	string take_input_equation()
	{
		cout << BLUE << WHITE_BACKGROUND << "\t\t\t<--=== Equation Format for Bisection Method ===-->"<<endl << RESET;
		cout << BLUE << WHITE_BACKGROUND << "\t\t  C1x^n + C2x^n-1 + C3x^n-2 + .... + C(N-2)x^2 + C(N-1)x + CN = 0   " << endl << RESET;
		cout << BLUE << WHITE_BACKGROUND << "\t\t                      Like:    Ax^2 + Bx + C = 0                    " << endl << RESET;
		string str;
		cout <<endl<< RED << "Enter The Equation:\t"<< YELLOW;
		getline(cin, str);
		cout << RESET;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == 'X')
			{
				str.replace(i, 1, "x");
			}
		}
		str.erase(str.find("=") - 1, str.length());
		return str;
	}

	double* initialize_array(double* arr, int length)
	{
		for (int i = 0; i < length; i++)
		{
			arr[i] = NULL;
		}
		return arr;
	}

	int count_terms(string eqtn)
	{
		int count = 0;
		for (int i = 0; i < eqtn.length(); i++)
		{
			if (eqtn[i] == '+' || eqtn[i] == '-')
			{
				count++;
			}
		}
		return (count + 1);
	}

	string* split_input_equation(string eqtn)
	{
		string*  terms=new string[12];
		int x = 0;
		string temp = "";
		for (int i = 0; i < eqtn.length(); i++)
		{
			if (eqtn[i] == '+' || eqtn[i] == '-')
			{
				x++;
				temp = "";
			}
			else if (eqtn[i] == ' ')
			{
				continue;
			}
			else
			{
				temp += eqtn[i];
				terms[x] = temp;
			}
		}
		return terms;
	}

	bool is_any_x_in_term(string str)
	{
		bool flag = false;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == 'x')
			{
				flag = true;
				break;
			}
		}
		return flag;
	}

	string* re_arrange_splitted_input(string* store, int terms)
	{
		for (int i = 0; i < terms; i++)
		{
			if (is_any_x_in_term(store[i]) == true)
			{
				if (store[i][store[i].length() - 1] == 'x')
				{
					store[i].append("^1");
				}
			}
			if (is_any_x_in_term(store[i]) == false)
			{
				store[i].append("x^0");
			}
			if (store[i][0] == 'x')
			{
				store[i].insert(0, "1");
			}
		}
		return store;
	}

	double* get_coefficients(string* store, int terms)
	{
		string* str = new string[12];
		int x = 0;
		for (int i = 0; i < terms; i++)
		{
			string temp = "";
			int loc = store[i].find("x");
			for (int j = 0; j < loc; j++)
			{
				temp += store[i][j];
				str[x] = temp;
			}
			x++;
		}
		
		double* numeric = new double[12];
		for (int i = 0; i < terms; i++)
		{
			numeric[i] = stod(str[i]);
		}
		return numeric;
	}

	double* get_exponents(string* store, int terms)
	{
		string* str = new string[12];
		int x = 0;
		for (int i = 0; i < terms; i++)
		{
			string temp = "";
			int loc = (store[i].find("^") + 1);
			for (int j = loc; j < store[i].length(); j++)
			{
				temp += store[i][j];
				str[x] = temp;
			}
			x++;
		}

		double* numeric = new double[12];
		for (int i = 0; i < terms; i++)
		{
			numeric[i] = stod(str[i]);
		}
		return numeric;
	}

	string get_operators(string eqtn)
	{
		string op;
		for (int i = 0; i < eqtn.length(); i++)
		{
			if (eqtn[i] == '+')
			{
				op.append("+");
			}
			if (eqtn[i] == '-')
			{
				op.append("-");
			}
		}
		return op;
	}

	bool is_simultaneously_negative_positive(double* fx_arr, int length)
	{
		bool flag;
		if (fx_arr[length] > 0 && fx_arr[length - 1] < 0)
		{
			flag = true;
		}
		else if (fx_arr[length] < 0 && fx_arr[length - 1]>0)
		{
			flag = true;
		}
		else
		{
			flag = false;
		}
		return flag;
	}

	double get_functional_value(double trial, double* coef, double* expo, int terms, string op)
	{
		double* store = new double[12];
		store[0] = 0;
		int pos = 0;
		for (int i = 0; i < terms; i++)
		{
			double cal;
			cal = (coef[i] * (pow(trial, expo[i])));
			store[pos] = cal;
			pos++;
		}

		double fx = store[0];
		for (int i = 0; i < (terms - 1); i++)
		{
			if (op[i] == '+')
			{
				fx = fx + store[i + 1];
			}
			if (op[i] == '-')
			{
				fx = fx - store[i + 1];
			}
		}
		return fx;
	}

	double* get_positive_solution_range(double* coef, double* expo, int terms, string op)
	{
		double* x_arr = new double[50];
		double* fx_arr = new double[50];
		double* range = new double[20];
		range = initialize_array(range, 20);
		int n = 0, p = 1;
		int loc = 0;

		for (int x = 0; x < 50; x++)
		{
			x_arr[loc] = x;
			double fx = get_functional_value(x, coef, expo, terms, op);
			fx_arr[loc] = fx;
			loc++;

			if (x >= 1)
			{
				if (is_simultaneously_negative_positive(fx_arr, x) == true)
				{
					if (fx_arr[x] > 0)
					{
						range[n] = x_arr[x-1];
						n += 2;
						range[p] = x_arr[x];
						p += 2;
					}
					else
					{
						range[p] = x_arr[x - 1];
						p += 2;
						range[n] = x_arr[x];
						n += 2;
					}
				}
			}
		}
		return range;
	}

	double* get_negative_solution_range(double* coef, double* expo, int terms, string op)
	{
		double* x_arr = new double[50];
		double* fx_arr = new double[50];
		double* range = new double[20];
		range = initialize_array(range, 20);
		int n = 0, p = 1;
		int loc = 0;
		int lc = -1;

		for (int x = 0; x > -50; x+=-1)
		{
			lc++;
			x_arr[loc] = x;
			double fx = get_functional_value(x, coef, expo, terms, op);
			fx_arr[loc] = fx;
			loc++;

			if (x <= -1)
			{
				if (is_simultaneously_negative_positive(fx_arr, lc) == true)
				{
					if (fx_arr[lc] > 0)
					{
						range[n] = x_arr[lc - 1];
						n += 2;
						range[p] = x_arr[lc];
						p += 2;
					}
					else
					{
						range[p] = x_arr[lc - 1];
						p += 2;
						range[n] = x_arr[lc];
						n += 2;
					}
				}
			}
		}
		return range;
	}

	double get_value_upto_decimal_place(double x,int decimal_place)
	{
		string str;
		str = to_string(x);
		str.erase(str.find(".") + decimal_place + 1, str.length());
		double k=stod(str);
		return k;
	}

	double get_root_of_equation_in_range(double nr, double pr, double* coef, double* expo, int terms, string op, int decimal_place)
	{
		double x2 = 0, fx2 = 0, first = 0, second = 0;
		int lc = 0;
		x2 = (nr + pr) / 2;
		first = get_value_upto_decimal_place(x2, decimal_place);
		fx2 = get_functional_value(x2, coef, expo, terms, op);
		while (first != second)
		{
			lc++;
			if (fx2 > 0)
			{
				pr = x2;
			}
			if (fx2 < 0)
			{
				nr = x2;
			}
			x2 = (nr + pr) / 2;
			if (lc % 2 != 0)
			{
				second = get_value_upto_decimal_place(x2, decimal_place);
			}
			if (lc % 2 == 0)
			{
				first = get_value_upto_decimal_place(x2, decimal_place);
			}
			fx2 = get_functional_value(x2, coef, expo, terms, op);
		}
		return first;
	}

	void show_root_calculation_table(double nr, double pr, double* coef, double* expo, int terms, string op, int decimal_place)
	{
		cout << endl << endl;
		cout << CYAN << "Calculation Table Between " << "( " << nr << " )" << " and " << "( " << pr << " )" << " ===--->" << endl << RESET;
		cout << GREEN << "\t|-------|---------------|---------------|---------------------|-----------------|" << RESET << endl;
		cout << "\t" << GREEN << "|"<< RED_BACKGROUND<<WHITE << " Sl.No "<<RESET << GREEN << "|"<<RESET<< RED_BACKGROUND<<WHITE<<"    X0(-ve)    "<<RESET << GREEN << "|"<<RESET << RED_BACKGROUND<<WHITE << "    X1(+ve)    "<<RESET << GREEN << "|"<<RESET << RED_BACKGROUND<<WHITE << "  X2[ (X0 + X1)/2 ]  "<<RESET << GREEN << "|"<<RESET << RED_BACKGROUND<<WHITE<<"      F(X2)      "<<RESET << GREEN << "|"<<RESET << endl<<RESET;
		cout << GREEN << "\t|-------|---------------|---------------|---------------------|-----------------|" << RESET << endl;
		double x2 = 0, fx2 = 0, first = 0, second = 0;
		int lc = 0, sl = 0;
		if (sl > 9)
		{
			cout << "\t" << GREEN << "|" << "  " << BLUE << sl + 1 << "   " << GREEN << "|"<<RESET;
		}
		else
		{
			cout << "\t" << GREEN << "|" << "   " << BLUE << sl + 1 << "   " << GREEN << "|"<<RESET;
		}
		if (nr < 0)
		{
			if ((int)nr > -10)
			{
				cout << "   " << BLUE << to_string(nr) << "   " << GREEN"|" << RESET;
			}
			if ((int)nr < -9)
			{
				cout << "   " << BLUE << to_string(nr) << "  " << GREEN"|" << RESET;
			}
		}
		if (nr == 0)
		{
			cout << "    " << BLUE << to_string(nr) << "   " << GREEN"|" << RESET;
		}
		if (nr > 0)
		{
			if ((int)nr < 10)
			{
				cout << "    " << BLUE << to_string(nr) << "   " << GREEN"|" << RESET;
			}
			if ((int)nr > 9)
			{
				cout << "    " << BLUE << to_string(nr) << "  " << GREEN"|" << RESET;
			}
		}
		if (pr < 0)
		{
			if ((int)pr > -10)
			{
				cout << "   " << BLUE << to_string(pr) << "   " << GREEN"|" << RESET;
			}
			if ((int)pr < -9)
			{
				cout << "   " << BLUE << to_string(pr) << "  " << GREEN"|" << RESET;
			}
		}
		if (pr == 0)
		{
			cout << "    " << BLUE << to_string(pr) << "   " << GREEN"|" << RESET;
		}
		if (pr > 0)
		{
			if ((int)pr < 10)
			{
				cout << "    " << BLUE << to_string(pr) << "   " << GREEN"|" << RESET;
			}
			if ((int)pr > 9)
			{
				cout << "    " << BLUE << to_string(pr) << "  " << GREEN"|" << RESET;
			}
		}
		x2 = (nr + pr) / 2;
		if (x2 > 0)
		{
			if ((int)x2 > 9)
			{
				cout << "      " << BLUE << to_string(x2) << "      " << GREEN"|" << RESET;
			}
			if ((int)x2 < 10)
			{
				cout << "      " << BLUE << to_string(x2) << "       " << GREEN"|" << RESET;
			}
		}
		if (x2 < 0)
		{
			if ((int)x2 > -10)
			{
				cout << "     " << BLUE << to_string(x2) << "       " << GREEN"|" << RESET;
			}
			if ((int)x2 < -9)
			{
				cout << "     " << BLUE << to_string(x2) << "      " << GREEN"|" << RESET;
			}
		}
		first = get_value_upto_decimal_place(x2, decimal_place);
		fx2 = get_functional_value(x2, coef, expo, terms, op);
		if (fx2 < 0)
		{
			if ((int)fx2 > -10)
			{
				cout << "    " << BLUE << to_string(fx2) << "    " << GREEN << "|" << endl << RESET;
			}
			if ((int)fx2 < -9)
			{
				cout << "    " << BLUE << to_string(fx2) << "   " << GREEN << "|" << endl << RESET;
			}
		}
		if (fx2 > 0)
		{
			if ((int)fx2 < 10)
			{
				cout << "     " <<BLUE<< to_string(fx2) << "    "<<GREEN<<"|" << endl<<RESET;
			}
			if ((int)fx2 > 9)
			{
				cout << "     " << BLUE << to_string(fx2) << "   " << GREEN << "|" << endl << RESET;
			}
		}
		cout << GREEN << "\t|-------|---------------|---------------|---------------------|-----------------|" << RESET << endl;

		while (first != second)
		{
			sl++;
			if (sl > 9)
			{
				cout << "\t" << GREEN << "|" << "  " << BLUE << sl + 1 << "   " << GREEN << "|" << RESET;
			}
			else
			{
				cout << "\t" << GREEN << "|" << "   " << BLUE << sl + 1 << "   " << GREEN << "|" << RESET;
			}
			lc++;
			if (fx2 > 0)
			{
				pr = x2;
			}
			if (fx2 < 0)
			{
				nr = x2;
			}
			if (nr < 0)
			{
				if ((int)nr > -10)
				{
					cout << "   " << BLUE << to_string(nr) << "   " << GREEN"|" << RESET;
				}
				if ((int)nr < -9)
				{
					cout << "   " << BLUE << to_string(nr) << "  " << GREEN"|" << RESET;
				}
			}
			if (nr == 0)
			{
				cout << "    " << BLUE << to_string(nr) << "   " << GREEN"|" << RESET;
			}
			if (nr > 0)
			{
				if ((int)nr < 10)
				{
					cout << "    " << BLUE << to_string(nr) << "   " << GREEN"|" << RESET;
				}
				if ((int)nr > 9)
				{
					cout << "    " << BLUE << to_string(nr) << "  " << GREEN"|" << RESET;
				}
			}
			if (pr < 0)
			{
				if ((int)pr > -10)
				{
					cout << "   " << BLUE << to_string(pr) << "   " << GREEN"|" << RESET;
				}
				if ((int)pr < -9)
				{
					cout << "   " << BLUE << to_string(pr) << "  " << GREEN"|" << RESET;
				}
			}
			if (pr == 0)
			{
				cout << "    " << BLUE << to_string(pr) << "   " << GREEN"|" << RESET;
			}
			if (pr > 0)
			{
				if ((int)pr < 10)
				{
					cout << "    " << BLUE << to_string(pr) << "   " << GREEN"|" << RESET;
				}
				if ((int)pr > 9)
				{
					cout << "    " << BLUE << to_string(pr) << "  " << GREEN"|" << RESET;
				}
			}
			x2 = (nr + pr) / 2;
			if (x2 > 0)
			{
				if ((int)x2 > 9)
				{
					cout << "      " << BLUE << to_string(x2) << "      " << GREEN"|" << RESET;
				}
				if ((int)x2 < 10)
				{
					cout << "      " << BLUE << to_string(x2) << "       " << GREEN"|" << RESET;
				}
			}
			if (x2 < 0)
			{
				if ((int)x2 > -10)
				{
					cout << "     " << BLUE << to_string(x2) << "       " << GREEN"|" << RESET;
				}
				if ((int)x2 < -9)
				{
					cout << "     " << BLUE << to_string(x2) << "      " << GREEN"|" << RESET;
				}
			}
			if (lc % 2 != 0)
			{
				second = get_value_upto_decimal_place(x2, decimal_place);
			}
			if (lc % 2 == 0)
			{
				first = get_value_upto_decimal_place(x2, decimal_place);
			}
			fx2 = get_functional_value(x2, coef, expo, terms, op);
			if (fx2 < 0)
			{
				if ((int)fx2 > -10)
				{
					cout << "    " << BLUE << to_string(fx2) << "    " << GREEN << "|" << endl << RESET;
				}
				if ((int)fx2 < -9)
				{
					cout << "    " << BLUE << to_string(fx2) << "   " << GREEN << "|" << endl << RESET;
				}
			}
			if (fx2 > 0)
			{
				if ((int)fx2 < 10)
				{
					cout << "     " << BLUE << to_string(fx2) << "    " << GREEN << "|" << endl << RESET;
				}
				if ((int)fx2 > 9)
				{
					cout << "     " << BLUE << to_string(fx2) << "   " << GREEN << "|" << endl << RESET;
				}
			}
			cout << GREEN << "\t|-------|---------------|---------------|---------------------|-----------------|" << RESET << endl;
		}
	}
