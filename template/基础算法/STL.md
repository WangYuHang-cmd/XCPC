	/*STL笔记部分*/
	/*
	vector动态数组{
	    size()
	    empty()
	    claer()...
	    //系统位某一程序申请空间的所需时间与空间大小无关，与次数有关,因此需要倍增vector
	    vector<int> a(10,3); //定义长度位10的vector每个数初始化为3
	    遍历方式：
	        vector<int>::iterator it;//迭代器遍历
	        for(auto x:a) ... //C++11特性
	    支持比较运算，按字典序比较大小
	}
	
	pair{
	    可以存储一个二元组pair<int,int>
	    p.first,p.second分别取第一个第二的元素
	    支持比较运算，按照字典序，以first为第一关键字，second为第二关键字
	    p=make_pair(a,b) //pair的构造
	    p={a,b} //c++11
	}
	
	string字符串{
	    c_str() //返回string对应的字符数组的头指针
	    如果使用printf("%s",p.c_str());
	}
	
	queue 队列
	priority_queue(优先队列/堆){
	    //默认是大根堆
	    改成小根堆：
	        1.插入负数
	        2.priority_queue<int,vector<int>,greater<int>> heap;
	    push(); 插入
	    top();
	    pop();
	}
	stack 栈
	deque(双端队列,效率低)
	set,multiset{
	    //set里面不能有重复元素，multiset里面可以有重复元素
	    set/multiset:
	        insert()
	        find() //不存在返回end迭代器
	        count返回某个数的个数
	        erase()
	            (1)erase(x),删除所有这个数
	            (2)erase(it)，删除此迭代器
	        lower_bound(x)返回大于等于x的最小的数
	        upper_bound(x)返回大于x的最小的数
	}
	
	map,multimap 基于平衡二叉树(红黑树)实现，动态维护有序序列{
	    insert();   插入的是pair
	    erase();    输入的参数是pair或者迭代器
	    [] 映射，O(logn)
	}
	
	(哈希表){
	unordered_set
	unordered_map
	unordered_multiset
	unordered_multima
	    //增删改查是O(1);
	    //不支持upper_bound和lower_bound
	}
	bitset(位存储，状态压缩){
	    bool a[1024]=1024B,bitset<1024>=128B
	    count() 返回有多少个1
	    any()  判断是否至少有一个1
	    none()  是否全为0
	    set()  把多有位置变成1
	    set(k,v) 把第k位变成v
	    flip()  等价于~
	    flip(k) 等价于把第k位取反
	}
	*/

　 Deque成员函数



| 函数                                                         | 描述                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| c.assign(beg,end) c.assign(n,elem)                           | 将[beg; end)区间中的数据赋值给c。 将n个elem的拷贝赋值给c。   |
| c.at(idx)                                                    | 传回索引idx所指的数据，如果idx越界，抛出out_of_range。       |
| c.back()                                                     | 传回最后一个数据，不检查这个数据是否存在。                   |
| c.begin()                                                    | 传回迭代器重的可一个数据。                                   |
| c.clear()                                                    | 移除容器中所有数据。                                         |
| deque<Elem> c deque<Elem> c1(c2) Deque<Elem> c(n) Deque<Elem> c(n, elem) Deque<Elem> c(beg,end) c.~deque<Elem>() | 创建一个空的deque。 复制一个deque。 创建一个deque，含有n个数据，数据均已缺省构造产生。 创建一个含有n个elem拷贝的deque。 创建一个以[beg;end)区间的deque。 销毁所有数据，释放内存。 |
| c.empty()                                                    | 判断容器是否为空。                                           |
| c.end()                                                      | 指向迭代器中的最后一个数据地址。                             |
| c.erase(pos) c.erase(beg,end)                                | 删除pos位置的数据，传回下一个数据的位置。 删除[beg,end)区间的数据，传回下一个数据的位置。 |
| c.front()                                                    | 传回地一个数据。                                             |
| get_allocator                                                | 使用构造函数返回一个拷贝。                                   |
| c.insert(pos,elem) c.insert(pos,n,elem) c.insert(pos,beg,end) | 在pos位置插入一个elem拷贝，传回新数据位置。 在pos位置插入>n个elem数据。无返回值。 在pos位置插入在[beg,end)区间的数据。无返回值。 |
| c.max_size()                                                 | 返回容器中最大数据的数量。                                   |
| c.pop_back()                                                 | 删除最后一个数据。                                           |
| c.pop_front()                                                | 删除头部数据。                                               |
| c.push_back(elem)                                            | 在尾部加入一个数据。                                         |
| c.push_front(elem)                                           | 在头部插入一个数据。                                         |
| c.rbegin()                                                   | 传回一个逆向队列的第一个数据。                               |
| c.rend()                                                     | 传回一个逆向队列的最后一个数据的下一个位置。                 |
| c.resize(num)                                                | 重新指定队列的长度。                                         |
| c.size()                                                     | 返回容器中实际数据的个数。                                   |
| C1.swap(c2) Swap(c1,c2)                                      | 将c1和c2元素互换。 同上操作。                                |

