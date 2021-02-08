#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>

#ifdef MYLIBRARY_EXPORT
#define MYLIBRARY_API /*DLLEXPORT*/
#else
#define MYLIBRARY_API /*DLLIMPORT*/
#endif

#define LOG(x) std::cout<<x<<std::endl;
#define LO(x) std::cout<<x;
#define rev(x) x=!x;
#define STOP while(true);

template<class T> void operator+=(T& a, T& b);
template<class T> void operator-=(T& a, T& b);
template<class T> bool operator!=(T a, T b);

namespace el {
	MYLIBRARY_API std::string getVersion();
	namespace Classic {
		template <class T> MYLIBRARY_API int getNumberOfElements(T* c);
		template <class T> MYLIBRARY_API inline void swap(T& a, T& b);
		template<class ARRAYTYPE> MYLIBRARY_API bool control(ARRAYTYPE array[], int& counter);
	}
	namespace StrCalc {
		MYLIBRARY_API int glos(std::string str);
		MYLIBRARY_API bool isContains(std::string string, std::string wllSearch);
		MYLIBRARY_API int whereContains(std::string string, std::string wllSearch, int place);
		MYLIBRARY_API int howManyContains(std::string string, char c);
		MYLIBRARY_API int howManyContains(std::string string, std::string wllSearch);
		MYLIBRARY_API int getThats(std::string string, char a, int place);
		MYLIBRARY_API std::string getBetweenThat(std::string string, int p1, int p2);
		MYLIBRARY_API std::vector<std::string> split(std::string str, char c);
		MYLIBRARY_API std::vector<std::string> splitOut(std::string str, char c,char out);
		MYLIBRARY_API std::vector<std::string> splitOut(std::string str, char c, char out,char out2);
		MYLIBRARY_API std::string subtract(std::string str, std::string wllSubtract,int place);
		MYLIBRARY_API std::string subtractCharacters(std::string control, char without = ' ');
		MYLIBRARY_API void pFor100(std::string urArray[100]);
		MYLIBRARY_API std::string getN(std::string a, int place, int n);
		MYLIBRARY_API int toInteger(char c);
		MYLIBRARY_API bool isThisInt(std::string str);
		MYLIBRARY_API std::string reverse(std::string str);
		MYLIBRARY_API int toInteger(std::string str);
		MYLIBRARY_API std::string toLower(std::string str);
		MYLIBRARY_API std::string combineVecS(std::vector<std::string> str);
		MYLIBRARY_API std::string add(std::string str, std::string wllAdd, int place);
		MYLIBRARY_API std::string Replace(std::string str, std::string replacing, std::string replaced,int place);
		MYLIBRARY_API bool controlFromThere(std::string str, std::string control, int place);
	}

	template <typename T1, typename T2>struct Variable2 { T1 First; T2 Second; };
	template <typename T1, typename T2> class Map
	{
	private:
		std::vector<Variable2<T1, T2>> m_Map;
	public:
		void push_back(T1 a, T2 b) { m_Map.push_back({ a,b }); }
		bool control(T1 a)
		{
			for (Variable2<T1, T2> control : m_Map) if (control.First == a) return true;
			return false;
		}
		std::vector<Variable2<T1, T2>> getMap() const { return m_Map; }
		int getId(T1 a)
		{
			for (int i = 0; i < m_Map.size();i++) if (m_Map[i].First == a) return i;
			return -1;
		}
		void setId(int a, T2 inf) { if (!a<0) m_Map[a].Second = inf; }
		void setId(int a, T1 inf) { if (!a < 0) m_Map[a].First = inf; }
	};


	class Pattern
	{
	private:
		std::vector<std::string> PatternString; char PatternMarker;
	public:
		Pattern(std::vector<std::string> pattern, char patternMarker);
		Pattern(std::string pattern, char patternMarker);
		static bool PatternController(std::vector<std::string> PatternVector, std::string input);
		std::vector<std::string> getPatternResult(std::string input);
	};

	namespace Inputs {
		MYLIBRARY_API std::vector<std::string> getUntilB(char until);
	}
	namespace Math {
		MYLIBRARY_API int factorial(int a);
		template <typename T> MYLIBRARY_API T absoluteValue(T a);
		MYLIBRARY_API inline float hypotenuse(float a, float b);
		template <typename T> MYLIBRARY_API int getNepos(T a);
		MYLIBRARY_API float permutation(float a, float b);
		MYLIBRARY_API float combination(float a, float b);
		template <typename T> MYLIBRARY_API T getBigger(T a, T b);
	}
	namespace Vectors {
		typedef float Vector1;
		struct Vector2 { float x, y; };
		struct Vector3 { float x, y, z; };
		MYLIBRARY_API Vector2 get(float x, float y);
		MYLIBRARY_API Vector3 get(float x, float y, float z);
		MYLIBRARY_API Vector2 toVector2(Vector3 a);
		MYLIBRARY_API Vector3 toVector3(Vector2 a);
		MYLIBRARY_API Vector2 operator+(Vector2 a, Vector2 b);
		MYLIBRARY_API Vector3 operator+(Vector3 a, Vector3 b);
		MYLIBRARY_API Vector3 operator+(Vector3 a, Vector2 b);
		MYLIBRARY_API Vector2 operator-(Vector2 a, Vector2 b);
		MYLIBRARY_API Vector3 operator-(Vector3 a, Vector3 b);
		MYLIBRARY_API Vector3 operator-(Vector3 a, Vector2 b);
		MYLIBRARY_API Vector2 operator*(Vector2 a, Vector2 b);
		MYLIBRARY_API Vector3 operator*(Vector3 a, Vector3 b);
		template<class T> MYLIBRARY_API void operator+=(T& a, T& b);
		template<class T> MYLIBRARY_API void operator-=(T& a, T& b);
		template <class T> MYLIBRARY_API Vector2 operator*(Vector2 a, T b);
		template <class T> MYLIBRARY_API Vector3 operator*(Vector3 a, T b);
		template <class T> MYLIBRARY_API Vector2 operator/(Vector2 a, T b);
		template <class T> MYLIBRARY_API Vector3 operator/(Vector3 a, T b);
		template <class T> MYLIBRARY_API Vector2 operator+(Vector2 a, T b);
		template <class T> MYLIBRARY_API Vector3 operator+(Vector3 a, T b);
		MYLIBRARY_API std::ostream& operator<<(std::ostream& os, Vector3 v);
		MYLIBRARY_API std::ostream& operator<<(std::ostream& os, Vector2 v);
		MYLIBRARY_API Vector3 absoluteValue(Vector3 a);
		MYLIBRARY_API Vector1 distance(Vector1 a, Vector1 b);
		MYLIBRARY_API Vector2 distance(Vector2 a, Vector2 b);
		MYLIBRARY_API Vector3 distance(Vector3 a, Vector3 b);
		MYLIBRARY_API float vectorTenuse(Vector3 a);
		MYLIBRARY_API float vectorTenuse(Vector2 a);
		MYLIBRARY_API Vector3 getVectorNepos(Vector3 a);
		MYLIBRARY_API Vector2 getVectorNepos(Vector2 a);
		MYLIBRARY_API Vector1 where(Vector1 v1, Vector1 v2);
		MYLIBRARY_API Vector2 where(Vector2 v1, Vector2 v2);
		MYLIBRARY_API Vector3 where(Vector3 v1, Vector3 v2);
	}
	namespace Geo {
		typedef int angle;
		struct Angle2 { Vectors::Vector2 v; angle ang; };
		MYLIBRARY_API Angle2 getAngle(float x, float y, angle angleD);
		MYLIBRARY_API bool operator==(Angle2 a, Angle2 b);
		struct Triangle2 { Angle2 a, b, c; }; 
		MYLIBRARY_API Triangle2 getTriangle(Angle2 a, Angle2 b, Angle2 c);
		MYLIBRARY_API Angle2 getDiffAngle(Triangle2 t1, Triangle2 t2);
		struct Rectangle2 { Angle2 a, b, c, d; };
		MYLIBRARY_API Rectangle2 getRectangle(Angle2 a, Angle2 b, Angle2 c, Angle2 d);
		MYLIBRARY_API Rectangle2 getRectangle(Triangle2 a, Triangle2 b);
		MYLIBRARY_API std::ostream& operator<<(std::ostream& os, Angle2 v);
		MYLIBRARY_API std::ostream& operator<<(std::ostream& os, Rectangle2 v);
		MYLIBRARY_API float getHypotenus(Triangle2 triangle);
		MYLIBRARY_API bool isTrue(Triangle2 triangle);
		MYLIBRARY_API bool isTrue(Rectangle2 rectangle);
	}

#define JJNumber 0.4
	namespace Physics {
		typedef int electron; typedef int center;
		struct Atom1 { Vectors::Vector1 v; electron charge; center proton, neutron; };
		MYLIBRARY_API Atom1 get(float x, electron charge, center proton, center neutron);

		struct Atom2 { Vectors::Vector2 v; electron charge; center proton, neutron; };
		MYLIBRARY_API Atom2 get(float x, float y, electron charge, center proton, center neutron);

		struct Atom3 { Vectors::Vector3 v; electron charge; center proton, neutron; };
		MYLIBRARY_API Atom3 get(float x, float y, float z, electron charge, center proton, center neutron);


		MYLIBRARY_API float gravForce(float distance, electron e1, electron e2);
		MYLIBRARY_API float electronJumpForce(float distance, electron e1, electron e2, center p1, center p2);
		MYLIBRARY_API float chargeForce(float distance, int c1, int c2);
		MYLIBRARY_API Vectors::Vector2 chargeForce(Vectors::Vector2 distance, int c1, int c2);
		MYLIBRARY_API Vectors::Vector2 chargeForce(Vectors::Vector2 v1, Vectors::Vector2 v2, int c1, int c2);
		MYLIBRARY_API Vectors::Vector3 getForce(Atom3& a, Atom3& b);
		MYLIBRARY_API Vectors::Vector2 getForce(Atom2 a, Atom2 b);
		MYLIBRARY_API Vectors::Vector1 getForce(Atom1 a, Atom1 b);

		//detailing atom

		struct Matter { Vectors::Vector2 v; int charge; }; Matter get(Vectors::Vector2 v, int charge);
		MYLIBRARY_API Vectors::Vector2 chargeForce(Matter e1, Matter e2);

		template<int NumberOfElectrons, int NumberOfNeutrons, int NumberOfProtons>class DAtom {
		private:
			Matter Electrons[NumberOfElectrons], Neutrons[NumberOfNeutrons], Protons[NumberOfProtons];
		public:
			DAtom() {
				for (int i = 0; i < NumberOfElectrons; i++) { Electrons[i].v = { 0.0,0.0 }; Electrons[i].charge = -1; }
				for (int i = 0; i < NumberOfNeutrons; i++) { Neutrons[i].v = { 0.0,0.0 }; Neutrons[i].charge = 0; }
				for (int i = 0; i < NumberOfProtons; i++) { Protons[i].v = { 0.0,0.0 }; Protons[i].charge = +1; }
			}

			void setElectronPos(int which, Vectors::Vector2 p) { Electrons[which].v = p; }
			void setNeutronPos(int which, Vectors::Vector2 p) { Neutrons[which].v = p; }
			void setProtonPos(int which, Vectors::Vector2 p) { Protons[which].v = p; }

			Matter getProton(int which) { return Protons[which]; }
			Matter getElectron(int which) { return Electrons[which]; }
			Matter getNeutron(int which) { return Neutrons[which]; }
			int getNOE() { return NumberOfElectrons; }
			int getNOP() { return NumberOfProtons; }
			int getNON() { return NumberOfNeutrons; }

			void calculate() {
				Vectors::Vector2 electronsForce[NumberOfElectrons];
				Vectors::Vector2 protonsForce[NumberOfProtons];
				Vectors::Vector2 neutronsForce[NumberOfNeutrons];

				for (int i = 0; i < NumberOfElectrons; i++) {
					for (int j = 0; j < NumberOfProtons; j++) electronsForce[i] += chargeForce(Electrons[i], Protons[j]);
					for (int j = 0; j < NumberOfElectrons; j++) if (i != j) electronsForce[i] += chargeForce(Electrons[i], Electrons[j]);
					for (int j = 0; j < NumberOfNeutrons; j++) electronsForce[i] += chargeForce(Electrons[i], Neutrons[j]);
				}for (int i = 0; i < NumberOfProtons; i++) {
					for (int j = 0; j < NumberOfProtons; j++) if (i != j) protonsForce[i] += chargeForce(Protons[i], Protons[j]);
					for (int j = 0; j < NumberOfElectrons; j++) protonsForce[i] += chargeForce(Protons[i], Electrons[j]);
					for (int j = 0; j < NumberOfNeutrons; j++) protonsForce[i] += chargeForce(Protons[i], Neutrons[j]);
				}for (int i = 0; i < NumberOfNeutrons; i++) {
					for (int j = 0; j < NumberOfProtons; j++) neutronsForce[i] += chargeForce(Neutrons[i], Protons[j]);
					for (int j = 0; j < NumberOfElectrons; j++) neutronsForce[i] += chargeForce(Neutrons[i], Electrons[j]);
					for (int j = 0; j < NumberOfNeutrons; j++) if (i != j) neutronsForce[i] += chargeForce(Neutrons[i], Neutrons[j]);
				}
				for (int i = 0; i < NumberOfElectrons; i++) Electrons[i].v += electronsForce[i];
				for (int i = 0; i < NumberOfProtons; i++)Protons[i].v += protonsForce[i];
				for (int i = 0; i < NumberOfNeutrons; i++)Neutrons[i].v += neutronsForce[i];
			}
		};

		template<int T, int T2, int T3> MYLIBRARY_API void writeAtom(DAtom<T, T2, T3> a);
	}
}
