#include<iostream>
#include<fstream>
#include<iterator>
#include<algorithm>
#include<vector>
#include<deque>
#include<windows.h>
#include<initializer_list>
using namespace std;

ostream& operator<<(ostream& out, const POINT& p)
{
	out << '(' << p.x << ';' << p.y << ')';
	return out;
}

class polygon {
	unique_ptr<vector<POINT>> points_ptr = make_unique<vector<POINT>>();// new vector<POINT>();

public:
	polygon(int _size = 0) : points_ptr(new vector<POINT>(_size)) {}
	polygon(const initializer_list<POINT>& in_list) : points_ptr(new vector<POINT>(in_list.size()))
	{
		copy(in_list.begin(), in_list.end(), begin());
	}
	//copy ctor
	polygon(const polygon& polygon_object) :points_ptr(new vector<POINT>(polygon_object.points_ptr->size()))
	{
		cout << "copy ctor" << endl;
		copy(polygon_object.cbegin(), polygon_object.cend(), begin());
	}
	//move ctor
	polygon(polygon&& polygon_object)
	{
		cout << "move ctor" << endl;
		points_ptr = move(polygon_object.points_ptr);
		//polygon_object.points_ptr = nullptr;
	}
	~polygon()
	{
		//delete points_ptr;
	}
	polygon& operator=(const polygon& polygon_object)
	{
		cout << "= copy" << endl;
		if (this == &polygon_object)
			return *this;
		//delete points_ptr;
		points_ptr = make_unique<vector<POINT>>(polygon_object.points_ptr->size()); //new vector<POINT>(polygon_object.points_ptr->size());
		copy(polygon_object.cbegin(), polygon_object.cend(), begin());
	}
	//move =
	polygon& operator=(polygon&& polygon_object)
	{
		cout << "= move" << endl;
		if (this == &polygon_object)
			return *this;
		//delete points_ptr;
		points_ptr = move(polygon_object.points_ptr);
		//polygon_object.points_ptr = nullptr;
	}


	// type definition
	using iterator = vector<POINT>::iterator;
	using reverse_iterator = vector<POINT>::reverse_iterator;
	using const_iterator = vector<POINT>::const_iterator;
	using const_reverse_iterator = vector<POINT>::const_reverse_iterator;

	iterator begin()
	{
		return points_ptr->begin();
	}

	iterator end()
	{
		return points_ptr->end();
	}

	const_iterator cbegin() const
	{
		return points_ptr->cbegin();
	}

	const_iterator cend() const
	{
		return points_ptr->cend();
	}
	//typedef vector<POINT>::iterator iterator;
};

polygon generate_zero_polygon(int size)
{
	polygon p(size);
	return p;
}

polygon transform_polygon(polygon&& p)
{
	transform(p.begin(), p.end(), p.begin(), [](const POINT& point) { return POINT{ point.y,point.x }; });
	return p;
}

class A {
	int a = 0;
	weak_ptr<A> pair;

public:
	A(int _a = 0) :a(_a) { cout << "ctor" << endl; }
	~A() { cout << "dtor" << endl; }
	friend ostream& operator<<(ostream& out, const A& obj)
	{
		out << obj.a << '-' << obj.pair.lock()->get_value() << endl;
		return out;
	}

	void set_pair(shared_ptr<A>& sptr)
	{
		pair = sptr;
	}

	int get_value() const
	{
		return a;
	}
};

int main()
{
	//unique_ptr<polygon> uptr=make_unique<polygon>(initializer_list<POINT>{ POINT{100, 200 }, POINT{200,300 }, POINT{300,400 }, POINT{400,500} });
	//for each (const POINT& item in pol)
	//{

	 //}
	//for (const POINT& item : *uptr)
	//cout << item << " ";

	vector<shared_ptr<A>> v;
	v.push_back(make_shared<A>(10));
	v.push_back(make_shared<A>(20));
	v[0]->set_pair(v[1]);
	v[1]->set_pair(v[0]);
	cout << v[0].use_count();
	//A* ptr = new A(10);
	//A* ptr1 = ptr;
	//A* ptr2;
	//ptr2 = ptr1;
	//cout << *ptr;
	//cout << *ptr1;
	//cout << *ptr2;

	 //auto_ptr<A> aptr1(new A(100));
	//cout << *aptr1;
	//auto_ptr<A> aptr2(aptr1);
	//cout << *aptr2;
	//auto_ptr<A> aptr3;
	//aptr3 = aptr2;
	//cout << *aptr2;

	 //unique_ptr<A> uptr1(new A(100));
	//cout << *uptr1;
	//unique_ptr<A> uptr2(move(uptr1));
	////cout << *uptr1;
	//cout << *uptr2;
	//unique_ptr<A> uptr3;
	//uptr3 = move(uptr2);
	////cout << *uptr2;
	//cout << *uptr3;
	//cout << uptr3->get_value() << endl;

	//shared_ptr<A> sptr1(new A(100));//xAB25
	//cout << *sptr1;
	//cout << sptr1.use_count() << endl;
	//shared_ptr<A> sptr2(sptr1);
	//cout << sptr1.use_count() << endl;
	//cout << sptr2.use_count() << endl;
	//cout << *sptr1;
	//cout << *sptr2;
	//shared_ptr<A> sptr3;
	//sptr3 = sptr2;

	 //shared_ptr<A> sptr4 = make_shared<A>(200);

	 //cout << *sptr2;
	//cout << *sptr3;
	//cout << sptr1.use_count() << endl;

	//delete ptr;
	//int n = 10;
	//int& lvr = n;
	//int* ptr = &n;

	//lvr++;
	//cout << n << endl;

	 //int&& rvr = n + 10;
	////int&& rvr1 = n;
	//rvr += 10;
	//cout << rvr << endl;
	////int array[]={0,1,2,3,25}
	//polygon p(10);

	 //polygon p1{ POINT{10,50}, POINT{100 }, POINT{} };
	//copy(p1.cbegin(), p1.cend(), ostream_iterator<POINT, char>(cout," "));
	//cout << endl;
	//polygon p2(move(p1));
	//copy(p2.cbegin(), p2.cend(), ostream_iterator<POINT, char>(cout, " "));
	////copy(p1.cbegin(), p1.cend(), ostream_iterator<POINT, char>(cout, " "));
	//cout << endl;
	//polygon p3;
	//p3 = p2;
	////ofstream fout("D:\\database\\polygon.txt");
	////if (!fout.is_open())
	//// cerr << "error" << endl;
	//copy(p3.begin(), p3.end(), ostream_iterator<POINT, char>(cout, " "));
	//cout << endl;
	////copy(p3.begin(), p3.end(), ostream_iterator<POINT, char>(fout, " "));
	////fout.close();
	//polygon p4(polygon{ POINT{50,20},POINT{70,100} });
	//copy(p4.begin(), p4.end(), ostream_iterator<POINT, char>(cout, " "));
	//cout << endl;
	//polygon p5;
	////p5 = move(p4);

	 //polygon p6;
	///*p6 = polygon{ POINT{}, POINT{10,20 } };

	 //p6 = generate_zero_polygon(100);*/

	 //p6 = transform_polygon(polygon{ {500,550},{100,200 } });
	//
	//deque<int> v;


	 //int tmp;
	//for (int& item : v)
	//{
	// cin >> item;
	//}
	//while (cin >> tmp)
	//{
	// v.push_back(tmp);
	//}
	/*istream_iterator<int, char> in_it(cin);
	istream_iterator<int, char> end_it;
	front_insert_iterator<deque<int>> ins_it(v);
	copy(in_it, end_it, ins_it);*/
	//copy(istream_iterator<int, char>(cin), istream_iterator<int, char>(), back_insert_iterator<deque<int>>(v));


	 //for_each(v.begin(), v.end(), [](const int& item) {cout << item << ' '; });
	return 0;
}