#include <iostream>
#include <vector>
#include <math.h>
#include "emils_lib.h"

template<class T> void operator+=(T& a, T& b) { a = a + b; }
template<class T> void operator-=(T& a, T& b) { a = a - b; }
template<class T> bool operator!=(T a, T b) { return !(a == b); }

namespace el {
	std::string getVersion() { return "0.1.9"; }
	namespace Classic {
		template <class T> int getNumberOfElements(T* c) { return sizeof(c) / sizeof(c[0]); }
		template <class T> inline void swap(T& a, T& b) { T t; t = a; a = b; b = t; }
		template<class ARRAYTYPE> bool control(ARRAYTYPE array[], int& counter) { return ++counter < getNumberOfElements(array); }
	}

	namespace StrCalc {
		int glos(std::string str)
		{
			int count = 0; for (int i = 0; str[i] != '\0'; i++) count++;
			return count;
		}
		bool isContains(std::string string, std::string wllSearch)
		{
			for (int i = 0; i < glos(string) - glos(wllSearch) + 1; i++) for (int j = 0; j < glos(wllSearch); j++) {
				if (string[i + j] != wllSearch[j]) break;
				if (j == glos(wllSearch) - 1) return true;
			}
			return false;
		}

		int whereContains(std::string string, std::string wllSearch,int place)
		{
			int result = -1;
			for (int i = 0; i < glos(string) - glos(wllSearch) + 1; i++) for (int j = 0; j < glos(wllSearch); j++) {
				if (string[i + j] != wllSearch[j]) break;
				if (j == glos(wllSearch) - 1) {
					place--;
					if (place == 0) { result = i; break; break; }
				}
			}

			return result;
		}
		int howManyContains(std::string string, char c) { int result = 0; for (int i = 0; i < glos(string); i++) if (string[i] == c) result++; return result; }
		int howManyContains(std::string string, std::string wllSearch) 
		{ for(int i=1;i<glos(string);i++) if (whereContains(string, wllSearch, i) == -1) return i - 1; return 0; }
		int getThats(std::string string, char a, int place)
		{
			int result = -1; if (place == -1) return -1; else if (place > howManyContains(string, a) - 1) return glos(string);
			else for (int i = 0; i < glos(string); i++) if (string[i] == a) if (place == 0) { result = i; break; }
			else place--;
			return result;
		}

		std::string getBetweenThat(std::string string, int p1, int p2) {
			std::string result = "";
			for (int i = p1 + 1; i < p2 && i<glos(string); i++) result += string[i];
			return result;
		}

		std::vector<std::string> split(std::string str, char c)
		{
			std::vector<std::string> result;
			if (howManyContains(str, c) != 0) for (int i = -1; i < howManyContains(str, c); i++) result.push_back(getBetweenThat(str, getThats(str, c, i), getThats(str, c, i + 1)));
			return result;
		}
		/* "patates","uçan, kaçan çocuk" c=',' out='"' */
		std::vector<std::string> splitOut(std::string str, char c, char out)
		{
			bool isOut = true;
			std::vector<std::string> result;
			std::string use = "";
			for (char input : str)
			{
				if (isOut && input == c) { result.push_back(use); use = ""; }
				else if (input == out) { rev(isOut); }
				else use += input;
			}
			if (use != "") result.push_back(use);
			return result;
		}

		std::vector<std::string> splitOut(std::string str, char c, char out, char out2)
		{
			bool isOut = true;
			std::vector<std::string> result;
			std::string use = "";
			for (char input : str)
			{
				if (isOut && input == c) { result.push_back(use); use = ""; }
				else if (input == out) { isOut=false; }
				else if (input == out2) { isOut = true; }
				else use += input;
			}
			if (use != "") result.push_back(use);
			return result;
		}

		std::string subtract(std::string str, std::string wllSubtract, int place)
		{
			int w = whereContains(str, wllSubtract, place); std::string result = "";
			if (w != -1) {
				for (int i = 0; i < w; i++) result += str[i];
				for (int i = w + glos(wllSubtract); i < glos(str); i++) result += str[i];
			}


			return result;
		}

		std::string subtractCharacters(std::string str, char without /*= ' '*/)
		{
			std::string result = "";
			for (int i = 0; i < glos(str); i++) if (str[i] != without) result += str[i];
			return result;
		}

		void pFor100(std::string urArray[100]) { for (int i = 0; i < 100; i++)if (urArray[i] != "")LO(urArray[i]); }
		std::string getN(std::string a, int place, int n)
		{
			if (!glos(a) < place * n) return getBetweenThat(a, place * n - 1, place * n + n); else return "";
		}
		int toInteger(char c)
		{
			if (c == '0') return 0;
			else if (c == '1') return 1;
			else if (c == '2') return 2;
			else if (c == '3') return 3;
			else if (c == '4') return 4;
			else if (c == '5') return 5;
			else if (c == '6') return 6;
			else if (c == '7') return 7;
			else if (c == '8') return 8;
			else if (c == '9') return 9;
			else return -1;
		}
		bool isThisInt(std::string str) { for (int i = 0; i < glos(str); i++) if (toInteger(str[i]) == -1) return false; return true; }
		std::string reverse(std::string str)
		{
			int length = glos(str); std::string result = "";
			for (int i = 1; i < length + 1; i++) result += str[length - i]; return result;
		}
		int toInteger(std::string str)
		{
			int result = 0; str = reverse(str);
			for (int i = 0; i < glos(str); i++) result += pow(10, i) * toInteger(str[i]); return result;
		}
		std::string toLower(std::string str)
		{
			for (int i = 0; i < glos(str); i++) str[i] = tolower(str[i]); return str;
		}
		std::string combineVecS(std::vector<std::string> str)
		{
			std::string result; for (std::string member : str) result += member + " "; return result;
		}
		std::string add(std::string str, std::string wllAdd, int place)
		{
			std::string result = ""; int wllAddGlos = glos(wllAdd);

			if (place != -1)
			{
				for (int i = 0; i < place && i < glos(str); i++) result += str[i];
				for (int i = 0; i < wllAddGlos; i++) result += wllAdd[i];
				for (int i = place; i < glos(str); i++) result += str[i];
				return result;
			}
			return str;
		}
		std::string Replace(std::string str, std::string replacing, std::string replaced,int place)
		{
			if (whereContains(str, replacing, place) != -1)
			{
				std::string subtracted = subtract(str, replacing, place);
				return el::StrCalc::add(subtracted, replaced, el::StrCalc::whereContains(str, replacing, place));
			}
			else return str;
		}
		bool controlFromThere(std::string str, std::string control, int place)
		{
			if(glos(control)+place>glos(str)) return false;
			for(int counter = 0;counter<glos(control);counter++) if(str[counter+place] != control[counter]) return false; return true;
		}
	}

	bool Pattern::PatternController(std::vector<std::string> PatternVector, std::string input)
	{
		int key = el::StrCalc::whereContains(input, PatternVector[0],0);
		for (int i = 1; i < PatternVector.size(); i++)
		{
			if (key < el::StrCalc::whereContains(input, PatternVector[1],0))
			{
				key = el::StrCalc::whereContains(input, PatternVector[1],0);
				continue;
			}
			else return false;
		}
		return true;
	}

	Pattern::Pattern(std::vector<std::string> pattern, char patternMarker) { 
		PatternString = pattern; PatternMarker = patternMarker;
	}

	Pattern::Pattern(std::string pattern, char patternMarker)
	{
		PatternString = el::StrCalc::split(pattern, patternMarker); PatternMarker = patternMarker;
	}

	std::vector<std::string> Pattern::getPatternResult(std::string input)
	{
		std::vector<std::string> result;
		for (int i = 0; i < PatternString.size() - 1; i++)
		{
			int leftW = el::StrCalc::whereContains(input, PatternString[i],1) + el::StrCalc::glos(PatternString[i]) - 1;
			int rightW = el::StrCalc::whereContains(input, PatternString[i + 1],1);
			result.push_back(el::StrCalc::getBetweenThat(input, leftW, rightW));
		}
		return result;
	}

	namespace Inputs {
		std::vector<std::string> getUntilB(char until)
		{
			std::vector<std::string> result;
			while (true)
			{
				std::string wllCin; std::cin >> wllCin;
				if (wllCin[0] != until) result.push_back(wllCin);
				else break;
			} return result;
		}
	}

	namespace Math {
		int factorial(int a) { for (int i = 1; i < a; i++) a *= i; return a; }
		template <typename T> T absoluteValue(T a) { if (a < 0) a *= -1; return a; }

		inline float hypotenuse(float a, float b) { return sqrt(pow(a, 2) + pow(b, 2)); }
		template <typename T> int getNepos(T a) { return a<0 ? -1 : a > 0 ? 1 : 0; }

		float permutation(float a, float b) { return factorial(a) / factorial(a - b); }
		float combination(float a, float b) { return factorial(a) / (factorial(a - b) * factorial(b)); }
		template <typename T> T getBigger(T a, T b) { return a > b ? a : b; }


	}



	namespace Vectors {
		Vector2 get(float x, float y) { return { x,y }; }
		Vector3 get(float x, float y, float z) { return { x,y,z }; }

		Vector2 toVector2(Vector3 a) { return { a.x,a.y }; }
		Vector3 toVector3(Vector2 a) { return { a.x,a.y,0 }; }

		Vector2 operator+(Vector2 a, Vector2 b) { return { a.x + b.x,a.y + b.y }; }
		Vector3 operator+(Vector3 a, Vector3 b) { return { a.x + b.x,a.y + b.y,a.z + b.z }; }
		Vector3 operator+(Vector3 a, Vector2 b) { return a + toVector3(b); }


		Vector2 operator-(Vector2 a, Vector2 b) { return { a.x - b.x,a.y - b.y }; }
		Vector3 operator-(Vector3 a, Vector3 b) { return { a.x - b.x,a.y - b.y,a.z - b.z }; }
		Vector3 operator-(Vector3 a, Vector2 b) { return a - toVector3(b); }

		Vector2 operator*(Vector2 a, Vector2 b) { return { a.x * b.x,a.y * b.y }; }
		Vector3 operator*(Vector3 a, Vector3 b) { return{ a.x * b.x,a.y * b.y,a.z * b.z }; }


		template<class T> void operator+=(T& a, T& b) { a = a + b; }
		template<class T> void operator-=(T& a, T& b) { a = a - b; }


		template <class T> Vector2 operator*(Vector2 a, T b) { return { a.x * b,a.y * b }; }
		template <class T> Vector3 operator*(Vector3 a, T b) { return { a.x * b,a.y * b,a.z * b }; }

		template <class T> Vector2 operator/(Vector2 a, T b) { return { a.x / b,a.y / b }; }
		template <class T> Vector3 operator/(Vector3 a, T b) { return { a.x / b,a.y / b,a.z / b }; }

		template <class T> Vector2 operator+(Vector2 a, T b) { return { a.x + b,a.y + b }; }
		template <class T> Vector3 operator+(Vector3 a, T b) { return { a.x + b,a.y + b,a.z + b }; }

		std::ostream& operator<<(std::ostream& os, Vector3 v) { os << "X:" << v.x << " Y:" << v.y << " Z:" << v.z; return os; }
		std::ostream& operator<<(std::ostream& os, Vector2 v) { os << "X:" << v.x << " Y:" << v.y; return os; }

		Vector3 absoluteValue(Vector3 a) { return { Math::absoluteValue(a.x),Math::absoluteValue(a.y),Math::absoluteValue(a.z) }; }

		Vector1 distance(Vector1 a, Vector1 b) { return Math::absoluteValue(a - b); }
		Vector2 distance(Vector2 a, Vector2 b) { return toVector2(absoluteValue(toVector3(a - b))); }
		Vector3 distance(Vector3 a, Vector3 b) { return absoluteValue(a - b); }

		float vectorTenuse(Vector3 a) { return Math::hypotenuse(Math::hypotenuse(a.x, a.y), a.z); }
		float vectorTenuse(Vector2 a) { return Math::hypotenuse(a.x, a.y); }

		Vector3 getVectorNepos(Vector3 a) { return { (float)Math::getNepos(a.x),(float)Math::getNepos(a.y),(float)Math::getNepos(a.z) }; }
		Vector2 getVectorNepos(Vector2 a) { return { (float)Math::getNepos(a.x), (float)Math::getNepos(a.y) }; }

		Vector1 where(Vector1 v1, Vector1 v2) { return Math::getNepos(v2 - v1); }
		Vector2 where(Vector2 v1, Vector2 v2) { return getVectorNepos(v2 - v1); }
		Vector3 where(Vector3 v1, Vector3 v2) { return getVectorNepos(v2 - v1); }


	}

	namespace Geo {
		Angle2 getAngle(float x, float y, angle angleD) { return { {x,y},angleD }; }
		bool operator==(Angle2 a, Angle2 b) { return a.v.x == b.v.x && a.v.y == b.v.y && a.ang == b.ang; }
		Triangle2 getTriangle(Angle2 a, Angle2 b, Angle2 c) { return { a,b,c }; }

		Angle2 getDiffAngle(Triangle2 t1, Triangle2 t2) {
			Angle2 t1Angle[3] = { t1.a,t1.b,t1.c }; Angle2 t2Angle[3] = { t2.a,t2.b,t2.c };
			Angle2 result = { {0,0}, 0 };
			for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) if (t1Angle[i] != t2Angle[i]) {
				result = t1Angle[i];
				break;
			}
			return result;
		}
		Rectangle2 getRectangle(Angle2 a, Angle2 b, Angle2 c, Angle2 d) { return { a,b,c,d }; }
		Rectangle2 getRectangle(Triangle2 a, Triangle2 b) {
			return { a.a, a.b, a.c, getDiffAngle(b,a) };
		}

		std::ostream& operator<<(std::ostream& os, Angle2 v) { os << "X:" << v.v.x << " Y:" << v.v.y << " ANGLE:" << v.ang << std::endl; return os; }
		std::ostream& operator<<(std::ostream& os, Rectangle2 v) { os << v.a << v.b << v.c << v.d; return os; }


		float getHypotenus(Triangle2 triangle) {
			return Math::hypotenuse(
				Math::hypotenuse(
					Math::absoluteValue(triangle.a.v.x - triangle.b.v.x),
					Math::absoluteValue(triangle.a.v.y - triangle.b.v.y))
				, Math::hypotenuse(
					Math::absoluteValue(triangle.c.v.x - triangle.b.v.x),
					Math::absoluteValue(triangle.c.v.y - triangle.b.v.y))
			);
		}

		bool isTrue(Triangle2 triangle) { return triangle.a.ang + triangle.b.ang + triangle.c.ang == 180; }
		bool isTrue(Rectangle2 rectangle) { return rectangle.a.ang + rectangle.b.ang + rectangle.c.ang + rectangle.d.ang == 360; }
	}

#define JJNumber 0.4
	namespace Physics {
		typedef int electron; typedef int center;
		Atom1 get(float x, electron charge, center proton, center neutron) { return { {x},charge,proton,neutron }; }
		Atom2 get(float x, float y, electron charge, center proton, center neutron) { return { {x,y},charge,proton,neutron }; }
		Atom3 get(float x, float y, float z, electron charge, center proton, center neutron) { return { {x,y,z},charge,proton,neutron }; }


		float gravForce(float distance, electron e1, electron e2) { return (e1 * e2) / (distance * distance); }
		float electronJumpForce(float distance, electron e1, electron e2, center p1, center p2) { return((e1 * p2) / (e2 * p1 * distance) * JJNumber); }
		float chargeForce(float distance, int c1, int c2) { return (c1 * c2 / distance); }
		Vectors::Vector2 chargeForce(Vectors::Vector2 distance, int c1, int c2) { return { chargeForce(distance.x,c1,c2),chargeForce(distance.y,c1,c2) }; }
		Vectors::Vector2 chargeForce(Vectors::Vector2 v1, Vectors::Vector2 v2, int c1, int c2) {
			return chargeForce(Vectors::getVectorNepos(v2 - v1) * (v2 - v1), c1, c2);
		}


		Vectors::Vector3 getForce(Atom3& a, Atom3& b) {
			Vectors::Vector3 distance = b.v - a.v;
			Vectors::Vector3 ven = Vectors::getVectorNepos(distance);
			return {
				ven.x * gravForce(distance.x,a.charge,b.charge),
				ven.y * gravForce(distance.y,a.charge,b.charge),
				ven.z * gravForce(distance.z,a.charge,b.charge)
			};
		}

		Vectors::Vector2 getForce(Atom2 a, Atom2 b) {
			Vectors::Vector2 distance = b.v - a.v;
			Vectors::Vector2 ven = Vectors::getVectorNepos(distance);
			return {
				ven.x * gravForce(distance.x,a.charge,b.charge),
				ven.y * gravForce(distance.y,a.charge,b.charge)
			};
		}

		Vectors::Vector1 getForce(Atom1 a, Atom1 b) {
			Vectors::Vector1 distance = b.v - a.v;
			Vectors::Vector1 ven = Math::getNepos(distance);
			return ven * gravForce(distance, a.charge, b.charge);
		}

		//detailing atom

		Matter get(Vectors::Vector2 v, int charge) { return { v,charge }; }
		Vectors::Vector2 chargeForce(Matter e1, Matter e2) {
			return el::Physics::chargeForce((e2.v - e1.v) * el::Vectors::getVectorNepos(e2.v - e1.v), e1.charge, e2.charge);
		}
		template<int T, int T2, int T3>
		void writeAtom(DAtom<T, T2, T3> a) {
			std::cout << "Electrons:";
			for (int i = 0; i < a.getNOE(); i++)
				if (i % 5 == 0) std::cout << std::endl << "Charge:" << a.getElectron(i).charge << " Pos:" << a.getElectron(i).v << " ";
				else std::cout << "Charge:" << a.getElectron(i).charge << " Pos:" << a.getElectron(i).v << " ";
			std::cout << std::endl << "Protons:";
			for (int i = 0; i < a.getNOP(); i++)
				if (i % 5 == 0) std::cout << std::endl << "Charge:" << a.getProton(i).charge << " Pos:" << a.getProton(i).v;
				else std::cout << "Charge:" << a.getProton(i).charge << " Pos:" << a.getProton(i).v;
			std::cout << std::endl << "Neutrons:";
			for (int i = 0; i < a.getNON(); i++)
				if (i % 5 == 0) std::cout << std::endl << "Charge:" << a.getNeutron(i).charge << " Pos:" << a.getNeutron(i).v;
				else std::cout << "Charge:" << a.getNeutron(i).charge << " Pos:" << a.getNeutron(i).v;
		}

	}



}
