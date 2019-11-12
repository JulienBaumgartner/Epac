#include <iostream>
#include <functional>
#include "ClassA.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "Triangle.h"
#include <cassert>
#include <stdio.h>

int main(int argc, char* argv[])
{
	auto power_lambda = [](int val, int mul) {
		int v = val;
		for (int i = 1; i < mul; ++i) {
			v *= val;
		}
		return v;
	};

	int result = power_lambda(2, 3);

	std::cout << result << "\n";

	{
		ClassA a;
		auto p = std::make_unique<ClassA>();
		std::cout << "bonjour\n";
	}
	{
		std::unique_ptr<Polygon> p1 = std::make_unique<Rectangle>(4, 5);
		std::unique_ptr<Polygon> p2 = std::make_unique<Triangle>(4, 5);

		int val1 = p1->area();
		int val2 = p2->area();

		assert(val1 != val2);
	}


	std::unique_ptr<FILE, std::function<void(FILE*)>> p(
		fopen("aaa.txt", "w"),
		[](FILE* ptr) {
		fclose(ptr);
	});



	system("pause");

	return 0;
}