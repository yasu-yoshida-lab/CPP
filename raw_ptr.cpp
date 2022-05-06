#include <iostream>
using namespace std; 

class hoge { 
private: 
	int *ptr;
public: 
	hoge(int val) { 
		if (val > 0) { ptr = new int(val); } 
	}
	~hoge() { delete ptr; }
}

int main() 
{ 
	int *ptr = new int(10);

	for (int i = 0; i < 10; ++i) { 
		*ptr += i; 
	}

	cout << "ptr = " << *ptr << endl; 

	delete ptr; 

	/* hoge クラスのコンストラクタは呼ばれない */ 
	// hoge H(-1);

	return 0; 
}

/* hoge クラスのコストラクタが呼ばれていないが main 終了時にデストラクタが呼ばれる */
