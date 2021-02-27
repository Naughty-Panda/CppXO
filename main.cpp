//////////////////////////////////////////////////
//				C++ XO
//		Naughty Panda @ 2021
//////////////////////////////////////////////////

#include <iostream>
#include <memory>

struct TFrame {
	int data[120 * 40]{};

	TFrame() { std::cout << "Created!\n"; }
	~TFrame() { std::cout << "Deleted...\n"; }
};

void Test(TFrame* f) {};
void Test(std::unique_ptr<TFrame>& f) {};
std::unique_ptr<TFrame> Init() { return std::make_unique<TFrame>(); };

int main() {

	std::unique_ptr<int[]> arr = std::make_unique<int[]>(10);
	std::unique_ptr<TFrame> frame = std::make_unique<TFrame>();

	std::weak_ptr<TFrame> wFrame;
	std::cout << "Before func...\n";
	Test(frame);
	std::cout << "After func...\n";
	std::unique_ptr<TFrame> frame2 = Init();
	return 0;
}
