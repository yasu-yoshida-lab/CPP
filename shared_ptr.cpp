#include <iostream>
#include <memory>

class hoge {
public: 
	std::shared_ptr<hoge>ptr;
};

void shared_ptr_cp_mv()
{
	std::cout << "shared_ptr_cp_mv" << std::endl;
	std::shared_ptr<int> ptr = std::make_shared<int>(10);
	std::shared_ptr<int> ptr2(ptr);
	std::shared_ptr<int> ptr3;
	ptr3 = ptr;

	std::cout << "ptr = " << ptr << std::endl; 
	std::cout << "ptr2 = " << ptr2 << std::endl; 
	std::cout << "ptr3 = " << ptr3 << std::endl; 

	/* ptr の所有権は ptr4 に移動 */
	std::shared_ptr<int> ptr4(std::move(ptr));
	std::cout << "ptr = " << ptr << std::endl; 
	std::cout << "ptr4 = " << ptr4 << std::endl; 

}

void unique_ptr_mv_shared_ptr() 
{
	std::unique_ptr<int> u_ptr(new int(10));
	std::shared_ptr<int> s_ptr(std::move(u_ptr));

	std::cout << "u_ptr = " << u_ptr << std::endl; 
	std::cout << "s_ptr = " << s_ptr << std::endl; 

	std::unique_ptr<int> u_ptr2(new int(10));
	std::shared_ptr<int> s_ptr2 = std::move(u_ptr2);

	std::cout << "u_ptr2 = " << u_ptr2 << std::endl; 
	std::cout << "s_ptr2 = " << s_ptr2 << std::endl; 
}

void circular_ref() 
{
	std::shared_ptr<hoge> p_hoge1 = std::make_shared<hoge>();
	std::shared_ptr<hoge> p_hoge2 = std::make_shared<hoge>();

	/* p_hoge1 のメンバ変数が p_hoge2 を参照 */
	p_hoge1->ptr = p_hoge2;
	/* p_hoge2 のメンバ変数が p_hoge1 を参照 */
	p_hoge2->ptr = p_hoge1;

	std::cout << "p_hoge1 = " << p_hoge1 << std::endl;
	std::cout << "p_hoge1->ptr = " << p_hoge1->ptr << std::endl;
	std::cout << "p_hoge2 = " << p_hoge2 << std::endl;
	std::cout << "p_hoge2->ptr = " << p_hoge2->ptr << std::endl;


} /* shared_ptrのデストラクタは呼ばれるが、確保した2つの hoge が開放されない */

int main()
{
	std::shared_ptr<int> ptr;

	{
		std::shared_ptr<int> ptr2(new int(0));

		ptr = ptr2; 

		*ptr += 10;
		*ptr2 += 10;
	} /* ptr2 のデストラクタが呼ばれる */

	/* ptr はアクセス可能 */
	std::cout << "ptr = " << *ptr << std::endl; 

	std::shared_ptr<int> ptr3(new int(10));
	std::shared_ptr<int> ptr4;
	ptr4.reset(new int(10));

	std::shared_ptr<int> ptr5 = std::make_shared<int>(10);

	typedef std::pair<int, double> int_double_t;
	std::shared_ptr<int_double_t> ptr6 = std::make_shared<int_double_t>(10, 0.4);

	shared_ptr_cp_mv();
	unique_ptr_mv_shared_ptr();

	/* reset で開放 */
	ptr.reset();
	std::cout << "ptr = " << ptr << std::endl; 

	if (ptr) { std::cout << "number of use : " << ptr.use_count() << std::endl; }
	else { std::cout << "Not use" << std::endl; }

	if (ptr3) { std::cout << "number of use : " << ptr.use_count() << std::endl; }
	else { std::cout << "Not use" << std::endl; }

	std::shared_ptr<std::string> s_ptr_string = std::make_shared<std::string>("test");

	std::cout << *s_ptr_string << std::endl;

	size_t str_size = s_ptr_string->size();
	std::cout << "str_size : " << str_size << std::endl;

	std::shared_ptr<int> s_ptr_int = std::make_shared<int>(10);

	int* raw_ptr = s_ptr_int.get();
	std::cout << "raw_ptr = " << raw_ptr << std::endl;

	std::shared_ptr<int> s_ptr_arr(new int[10], std::default_delete<int[]>());

	for (int i = 0; i < 10; ++i) { 
		s_ptr_arr.get()[i] = i; 
	}

	for (int i = 0; i < 10; ++i) { 
		printf("s_ptr_arr.get()[%d] = %d\n", i, s_ptr_arr.get()[i]);
	}

	circular_ref();


	return 0;
}
