#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
template <int...NS>
struct XOR;
template <int N1, int...NS>
struct XOR<N1, NS...> {
	const static int XOR_ = (N1^XOR<NS...>::XOR_);
};
template <>
struct XOR<> {
	const static int XOR_ = 0;
};



template <int XOR, int index, int...NS>
struct play;

template <int XOR, int index, int N1, int ...NS>
struct play<XOR, index, N1, NS...> {
	const static int how = ((N1 ^ XOR) <= N1) * (N1 - (N1 ^ XOR)) + ((N1 ^ XOR) > N1) * play<XOR, index + 1, NS...>::how;
	const static int whence = (how == (N1 - (N1 ^ XOR))) * index + (how != (N1 - (N1 ^ XOR))) * play<XOR, index + 1, NS...>::whence;
	
};
template <int XOR, int index> 
struct play<XOR, index> {
	const static int how = 0;
	const static int whence = 0;
};



template <int... NS>
class NIM {
public:
	const static int xor_ = XOR<NS...>::XOR_;
	const static int who = (xor_ != 0) + (xor_ == 0) * 2;
	const static int how = (who == 1) * play <xor_, 1, NS...>::how;
	const static int whence = (who == 1) * play <xor_, 1, NS...>::whence;
};

int main() {
	constexpr int who = NIM<1, 2, 3, 7>::who;
	constexpr int whence = NIM<1, 2, 3, 7>::whence;
	constexpr int how = NIM<1, 2, 3, 7>::how;
	std::cout << who << ' ' << whence << ' ' << how << '\n';
}
