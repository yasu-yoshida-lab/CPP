#include <iostream>
#include <memory>

class hoge { 
private: 
	std::unique_ptr<int> ptr; 
public: 
	hoge(int val):ptr(new int(val)) { }
	int get_value() const { return *ptr; }
};

void free_int_ptr(int *ptr)
{
}

struct deleter_ptr { 
	void operator()(int *ptr)
	{ 
		free_int_ptr(ptr);
	}
};

int main() 
{ 
	hoge Hoge(10); 

	/* 
	 * unique_ptr はコピー禁止なのでコピーコストラクタはエラー
	 */
	// hoge Hoge2(Hoge);

	/* ムーブはOK */
	hoge Hoge2(std::move(Hoge));

	std::unique_ptr<int> ptr(new int(10));

	std::unique_ptr<int> ptr2;
	ptr2.reset(new int(10));

	std::unique_ptr<int> ptr3 = std::make_unique<int>(10); 

	std::unique_ptr<int> ptr4(std::move(ptr));

	std::unique_ptr<int> ptr5; 
	ptr5 = std::move(ptr2);

	/* デストラクタはスコープ外、reset() で行われる */
	ptr5.reset();

	/* operator bool() で所有の判定 */
	if (ptr4) { std::cout << "Owned memory" << std::endl; }
	else { std::cout << "Not Owned memory" << std::endl; }

	if (ptr5) { std::cout << "Owned memory" << std::endl; }
	else { std::cout << "Not Owned memory" << std::endl; }

	/* 通常のポインタが欲しいときは get() を利用 */
	int *raw_ptr; 
	std::unique_ptr<int> ptr6(new int(10));
	raw_ptr = ptr6.get();

	/* unique_ptr<T[]> で配列も扱える */
	std::unique_ptr<int[]> ptr_arr(new int[10]); 
	for (size_t i = 0; i < 10; ++i) { ptr_arr[i] = i; } 
	for (size_t i = 0; i < 10; ++i) { std::cout << ptr_arr[i] << std::endl; } 

	/* テンプレート第2引数で deleter を指定 */
	std::unique_ptr<int, deleter_ptr> pt7;


	return 0; 
}
