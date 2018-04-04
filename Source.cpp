#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include<sstream>

using namespace std;

string toString(double d)
{
	ostringstream out;
	out << d;
	return out.str();
}
double summa(double a, double b)
{
	double rezult = a + b;
	return rezult;
}
double mini(double a, double b)
{
	double rezult = a - b;
	return rezult;
}
double proizv(double a, double b)
{
	double rezult = a * b;
	return rezult;
}
double sep(double a, double b)
{
	double rezult = a / b;
	return rezult;
}


double rezult(vector<string>& a)
{
	double arg1 = 0;
	double arg2 = 0;
	bool err = false;
	bool d = false; // ���������� ����������� �� ��������
	int N = a.size();
	for (int i = 0; i < N;i++)
	{
		if (a[i] == "(")
		{
			cout << "Open bracket!\n";
			err = true;
		}
		if (a[i] == "-")
		{
			if (i - 2 >= 0)
			{
				arg1 = atof(a[i - 2].c_str());
				arg2 = atof(a[i - 1].c_str());
				a[i - 2] = toString(mini(arg1, arg2));
				d = true;
			}
			else
			{
				cout << "Something wrong!\n";
				err = true;
			}
				
			

		}
		if (a[i] == "+")
		{
			if (i - 2 >= 0)
			{
				arg1 = atof(a[i - 2].c_str());
				arg2 = atof(a[i - 1].c_str());
				a[i - 2] = toString(summa(arg1, arg2));
				d = true;
			}
			else
			{
				cout << "Something wrong!\n";
				err = true;
			}
			
		}
		if (a[i] == "*")
		{
			if (i - 2 >= 0)
			{
				arg1 = atof(a[i - 2].c_str());
				arg2 = atof(a[i - 1].c_str());
				a[i - 2] = toString(proizv(arg1, arg2));
				d = true;
			}
			else
			{
				cout << "Something wrong!\n";
				err = true;
			}
		}
		if (a[i] == "/")
		{
			if (i - 2 >= 0)
			{
				arg1 = atof(a[i - 2].c_str());
				arg2 = atof(a[i - 1].c_str());
				if (arg2 == 0)
				{
					cout << "Error! Division by zero!";
					err = true;
					break;
				}
				a[i - 2] = toString(sep(arg1, arg2));
				d = true;
			}
			else
			{
				cout << "Something wrong!\n";
				err = true;
			}

		}
		if (d == true /*&& (N - 1 != 2)*/)
		{
			for (int j = i - 1;j < N - 2;j++)
			{
				a[j] = a[j + 2];
			}
			a.pop_back();
			a.pop_back();
			d = false;
			i = 0;
			N = a.size();
		}
	}

	if (a.size() > 1 && err !=true)
	{
		cout << "Someting wrong!";
		err = true;
	}
	if (err == true )
	{
		return 0;
	}
	return atof(a[0].c_str());
}

int main()
{
	string str;
	getline(cin, str);

	vector <char> operations;
	vector <string> output;
	int i = 0;
	int j = 0;
	vector<int> j1;;
	string chislo;
	string lastOperation;
	int len = str.length();
	bool minus = false;

	// ������
	while (len > i)
	{

		if (i == 0 && str[0] == '-')
			minus = true;

		if (isdigit(str[i]))
		{
			if (minus == true)
				j = i - 1;
			else
				j = i;

			for (i = i + 1; i <= len;i++)
			{
				if (!isdigit(str[i]))
				{
					if (str[i] == '.')
					{
						continue;
					}
					else
					{
						i = i - 1;
						break;
					}
				}
			}

			chislo = str.substr(j, i - j + 1);
			output.push_back(chislo);
			minus = false;
		}
		else
		{
			if ( str[i] == '*')
				operations.push_back(str[i]);

			if (str[i] == '-' && minus == false)
			{
				if (!(operations.size() == 0))
				{
					lastOperation = operations[operations.size() - 1];
					if (lastOperation == "-" )
					{
						output.push_back(lastOperation);
						operations[operations.size() - 1] = str[i];
					}
					else
						operations.push_back(str[i]);
				}
				else
					operations.push_back(str[i]);
			}
				

			if (str[i] == '+')
			{
				if (!(operations.size() == 0))
				{
					lastOperation = operations[operations.size() - 1];
					if (lastOperation == "*"|| lastOperation == "/")
					{
						output.push_back(lastOperation);
						operations[operations.size() - 1] = str[i];
					}
					else
						operations.push_back(str[i]);
				}
				else
					operations.push_back(str[i]);

			}

			if (str[i] == '/')
			{
				if (!(operations.size() == 0))
				{
					lastOperation = operations[operations.size() - 1];
					if (lastOperation == "*")
					{
						output.push_back(lastOperation);
						operations[operations.size() - 1] = str[i];
					}
					else
						operations.push_back(str[i]);
				}
				else
					operations.push_back(str[i]);

			}

			if (str[i] == '(')
			{
				if (str[i + 1] == '-')
					minus = true;
				j1.push_back(operations.size());
				operations.push_back(str[i]);
			}
			if (str[i] == ')')
			{

				for (int k = operations.size() - 1;k > j1[j1.size()-1];k--)
				{
					lastOperation = operations[operations.size() - 1];
					output.push_back(lastOperation);
					operations.pop_back();
				}
				operations.pop_back();
				j1.pop_back();
			}
		}
		i++;
	}


	for (i = operations.size() - 1;i >= 0; i--)
	{
		lastOperation = operations[operations.size() - 1];
		output.push_back(lastOperation);
		operations.pop_back();
	}
	int N = output.size();
	
	cout << "\n";
	if (N != 0)
		cout << round(rezult(output) * 1000) / 1000;
	else
		cout << "Error!";
	system("pause");
	return 0;
}

