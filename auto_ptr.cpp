#include <iostream>
#include <memory>

class hoge { 
private: 
	std::auto_ptr<int> ptr;
public: 
	hoge(int val):ptr(new int(val)) { } 
	int get_value() const { return *ptr; }
};

int main() 
{ 
	hoge Hoge(10); 
	return 0; 
}
