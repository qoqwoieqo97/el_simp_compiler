#include <iostream>
#include <vector>

struct Power { int num, pwr; };

std::ostream& operator<<(std::ostream& os, const Power& pw)
{
	os << pw.num<<"^"<<pw.pwr;
	return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Power>& pw)
{
	for (Power a : pw) os << a << ",";
	return os;
}

int getId(std::vector<Power> s,int num)
{
	for (int i = 0; i < s.size(); i++) if (s[i].num == num) return i;
	return -1;
}

std::vector<Power> algorithm(int num){
	std::vector<Power> result;
	int counter=2;
	while (true)
	{
		if (num % counter == 0) { 
			num /= counter; int id = getId(result, counter); 
			if (id == -1)result.push_back({ counter,1 }); 
			else result[id].pwr++; 
		}
		else { counter++; }
		if (num == 1) break;
	}
	return result;
}

class AdvancedNumber {
private:
	std::vector<Power> Powers;
public:
	AdvancedNumber() {}
	AdvancedNumber(int num) { Powers = algorithm(num); }
	AdvancedNumber(std::vector<Power> inputPowers) { Powers = inputPowers; }
	int getNumberi()
	{
		int result = 1;
		for (Power a : Powers) { result *= pow(a.num, a.pwr); }
		return result;
	}
	float getNumberf()
	{
		float result = 1;
		for (Power a : Powers) { result *= pow(a.num, a.pwr); }
		return result;
	}
	std::vector<Power> powers() const { return Powers; }
	AdvancedNumber operator=(const int rhs) { return AdvancedNumber(rhs); }
	AdvancedNumber operator = (const AdvancedNumber a){ return AdvancedNumber(a); }

	AdvancedNumber operator+(AdvancedNumber a)
	{ return AdvancedNumber(a.getNumberi() + getNumberi()); }
	AdvancedNumber operator-(AdvancedNumber a)
	{ return AdvancedNumber(a.getNumberi() - getNumberi()); }
	AdvancedNumber operator*(AdvancedNumber a)
	{
		std::vector<Power> apw = a.powers(); std::vector<Power> bpw = powers();
		for (int i = 0; i < bpw.size(); i++)
		{
			int id = getId(apw, bpw[i].num);
			if (id == -1) apw.push_back({ bpw[i].num,1 });
			else apw[id].pwr += bpw[i].pwr;
		}
		AdvancedNumber result(apw);
		return result;
	}
	AdvancedNumber operator/(AdvancedNumber a)
	{
		std::vector<Power> apw = a.powers(); std::vector<Power> bpw = powers();
		for (int i = 0; i < bpw.size(); i++)
		{
			int id = getId(apw, bpw[i].num);
			if (id == -1) apw.push_back({ bpw[i].num,-1 });
			else apw[id].pwr -= bpw[i].pwr;
		}
		return AdvancedNumber(apw);
	}
};
std::ostream& operator<<(std::ostream& os,AdvancedNumber a)
{ os << a.getNumberi(); return os; }

typedef AdvancedNumber elInt;