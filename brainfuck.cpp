#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>
#ifdef _WIN32
#include <conio.h>
#endif
int main(int argc, char const *argv[])
{
	std::ifstream fin(argv[1], std::ios_base::in);
	if (argc < 2)
	{
		std::cout << "you haven't passed any arguments to me!\n";
		exit(1);
	}
	if (!fin)
	{
		std::cout << "Oh boy! i couldn't find the brainfuck source file\nmake sure you have the source file";
		exit(1);
	}
	std::ofstream fout("a.out.c", std::ios_base::out);
	char ch;
	fout << "#include <stdio.h>\n#include <stdlib.h>\nint main(int argc, char** argv[]) {" << \
			"\n\tchar* ptr=(char*)malloc(sizeof(char)*1000000);\n" << \
			"\tlong long int i;\n" << \
			"\tfor (i = 0; i < 1000000; ++i) { \n" << \
			"\t\t*(ptr+i)=0;\n\t}" << std::endl ;
	std::stack<bool> tabs;
	while(fin.get(ch))
	{
		switch(ch)
		{
			case '>':
				for (int i = 0; i < tabs.size() + 1; ++i)
					fout << "\t";
				fout << "++ptr;\n";
				break;
			case '<':
				for (int i = 0; i < tabs.size() + 1; ++i)
					fout << "\t";
				fout << "--ptr;\n";
				break;
			case '+':
				for (int i = 0; i < tabs.size() + 1; ++i)
					fout << "\t";
				fout << "++*ptr;\n";
				break;
			case '-':
				for (int i = 0; i < tabs.size() + 1; ++i)
					fout << "\t";
				fout << "--*ptr;\n";
				break;
			case '[':
				for (int i = 0; i < tabs.size() + 1; ++i)
					fout << "\t";
				fout << "while (*ptr) {\n";
				tabs.push(true);
				break;
			case ']':
				tabs.pop();
				for (int i = 0; i < tabs.size() + 1; ++i)
					fout << "\t";
				fout << "}\n";
				break;
			case '.':
				for (int i = 0; i < tabs.size() + 1; ++i)
					fout << "\t";
				fout << "putchar(*ptr);\n";
				break;
			case ',':
				for (int i = 0; i < tabs.size() + 1; ++i)
					fout << "\t";
				fout << "*ptr=getchar();\n";
				break;
			default:
				break;
		}
	}
	fout << "return 0;\n}";
	fout.close();
	#ifdef __linux__
		std::cout << "compilation started ... \n";
		std::cout << "\tcompiling " << argv[1] << " ... \n";
		system("gcc a.out.c -o a.out");
		std::cout << "compilation completed ... \n";
	#elif _WIN32
		std::cout << "Oh boy, it's disgusting that windows doesn't have gcc\n";
		std::cout << "i couldn't compile the c file, please take the pain of doing it yourself\n";
		std::cout << "Adiaux!\n" << std::endl;
		getch();// i really hate this
	#else
		std::cout << "actually i couldn't determine your system,\n so i'm only delivering the c file only\n" <<\
		"please take the pain of compiling it yourself\n";
		std::cout << "if you are on linux or on windows and yet this insane error occured.\n "<< \
		"please kick this fool (Srinivas Devaki) at mr.eightnoteight [at] gmail [dot] com\n" << \
		"AND raise an issue at \033[33mhttps://github.com/eightnoteight/brainfuck/issues/new\033[0m";
	#endif
	return 0;
}