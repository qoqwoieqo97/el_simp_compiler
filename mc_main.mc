//Function Design
//[Function_Name] ([Parameters]) [Options] : [DoingThings]
//
//Extern Design
//extern [Type (C/C++)] [Command]
//
//Variable Design
//[Type] [Name] (= [Value])

lib++("iostream")
lib++("SFML/Graphics.h")
extern C++ class Drawer {public: sf::RenderWindow window; void draw(sf::Sprite spr){window.draw(spr);window.display();} void clear(sf::Color color){window.clear(color);} }Display;
extern C++ using namespace std;
print(string thing) void : extern C++ std::cout << thing;
printi (int thing) void : extern C++ std::cout << thing;
printf(string thing) void : extern C++ std::cout << thing << std::endl;
printfi(int thing) void : extern C++ std::cout << thing << std::endl;
endl() void : extern C++ std::cout << std::endl;
string s
getch() void : extern C++ std::cin >> s;
inc(int &num) void : extern C++ num++;
plus(int &num,int in) void : extern C++ num+=in;