#include "tests.hpp"
#include <list>

// --- Class foo from mli
template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose && VERBOSE) std::cout << "~foo::foo()" << std::endl; };
		void m(void) { if (VERBOSE) std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { if (VERBOSE) std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (VERBOSE && (this->_verbose || src._verbose))
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

template <typename T>
std::ostream	&operator<<(std::ostream &o, foo<T> const &bar) {
	o << bar.getValue();
	return o;
}
// --- End of class foo

template <class T1, class T2>
static void print_map(FT::map<T1, T2> m)
{
	typedef typename FT::map<T1, T2> map_type;
	typedef typename map_type::iterator iterator;
	if (!VERBOSE)
		return;
	std::cout << "size: " << m.size() << std::endl;
	std::cout << "max_size: " << m.max_size() << std::endl;

	iterator ite = m.end();
	for (iterator it = m.begin(); it != ite; ++it)
	{
		std::cout << "-- m[" << it->first << "] = " << it->second << std::endl;
	}
}

int test_map_void_constructor()
{
	FT::map<int, int> m;

	ASSERT_EQUAL(m.empty(), true);
	print_map(m);
	return (0);
}

int test_map_copy_constructor()
{
	FT::map<int, int> m;

	m[5] = 1;
	m[6] = 2;
	m[3] = 4;
	FT::map<int, int> m2(m);
	ASSERT_EQUAL(m2.size(), (unsigned long)3);
	ASSERT_EQUAL(m2.empty(), false);
	FT::map<int, int>::iterator it1 = m.begin();
	FT::map<int, int>::iterator ite1 = m.end();
	FT::map<int, int>::iterator it2 = m2.begin();
	FT::map<int, int>::iterator ite2 = m2.end();
	while (it1 != ite1 && it2 != ite2)
	{
		ASSERT_EQUALQ(*it1, *it2);
		++it1;
		++it2;
	}
	print_map(m);
	print_map(m2);
	return (0);
}

int test_map_iterator_constructor()
{
	FT::map<int, int> m;

	m[5] = 1;
	m[6] = 2;
	m[3] = 4;

	FT::map<int, int>::iterator it1 = m.begin();
	FT::map<int, int>::iterator ite1 = m.end();
	FT::map<int, int> m2(it1, ite1);
	ASSERT_EQUAL(m2.size(), (unsigned long)3);
	ASSERT_EQUAL(m2.empty(), false);
	FT::map<int, int>::iterator it2 = m2.begin();
	FT::map<int, int>::iterator ite2 = m2.end();
	while (it1 != ite1 && it2 != ite2)
	{
		ASSERT_EQUALQ(*it1, *it2);
		++it1;
		++it2;
	}
	print_map(m);
	return (0);
}

int test_map_empty()
{
	FT::map<char, int> m;

	FT::pair<const char, int> p1; //('a', 10);
	FT::pair<const char, int> p2('b', 20);

	ASSERT_EQUAL(m.empty(), true);
	m.insert(p1);
	m.insert(p2);
	ASSERT_EQUAL(m.empty(), false);
	print_map(m);
	return (0);
}

int test_map_size()
{
	FT::map<char, int> m;

	FT::pair<const char, int> p1('a', 10);
	FT::pair<const char, int> p2('b', 20);

	ASSERT_EQUAL(m.size(), (unsigned int)0);
	m.insert(p1);
	ASSERT_EQUAL(m.size(), (unsigned int)1);
	m.insert(p2);
	ASSERT_EQUAL(m.size(), (unsigned int)2);
	print_map(m);
	return (0);
}

int test_map_brackets_write()
{
	FT::map<char, int> m;

	m['a'] = 10;
	m['c'] = 30;
	m['b'] = 20;
	int count = 10;

	FT::map<char, int>::iterator it = m.begin();
	FT::map<char, int>::iterator ite = m.end();
	while (it != ite)
	{
		ASSERT_EQUAL(it->second, count);
		count += 10;
		++it;
	}
	ASSERT_EQUAL(m.size(), (unsigned int)3);
	ASSERT_EQUAL((m.begin())->second, 10);
	ASSERT_EQUAL((++m.begin())->second, 20);
	ASSERT_EQUAL((--m.end())->second, 30);
	print_map(m);
	return (0);
}

int test_map_brackets_read()
{
	FT::map<char, int> m;

	m['a'] = 10;
	m['c'] = 30;
	m['b'] = 20;
	ASSERT_EQUAL(m['a'], 10);
	ASSERT_EQUAL(m['b'], 20);
	ASSERT_EQUAL(m['c'], 30);
	print_map(m);
	return (0);
}

int test_map_brackets_overwrite()
{
	FT::map<char, int> m;

	m['a'] = 10;
	m['c'] = 30;
	m['b'] = 20;
	m['a'] = 40;
	m['b'] = 50;
	m['c'] = 60;
	int count = 40;

	FT::map<char, int>::iterator it = m.begin();
	FT::map<char, int>::iterator ite = m.end();
	while (it != ite)
	{
		ASSERT_EQUAL(it->second, count);
		count += 10;
		++it;
	}
	ASSERT_EQUAL(m.size(), (unsigned int)3);
	ASSERT_EQUAL((m.begin())->second, 40);
	ASSERT_EQUAL((++m.begin())->second, 50);
	ASSERT_EQUAL((--m.end())->second, 60);
	print_map(m);
	return (0);
}

int test_map_insert_duplicate()
{
	FT::map<char, int> m;

	FT::pair<const char, int> p1('a', 10);
	FT::pair<const char, int> p2('a', 20);

	ASSERT_EQUAL(m.size(), (unsigned int)0);
	m.insert(p1);
	ASSERT_EQUAL(m.size(), (unsigned int)1);
	m.insert(p1);
	ASSERT_EQUAL(m.size(), (unsigned int)1);
	m.insert(p2);
	ASSERT_EQUAL(m.size(), (unsigned int)1);
	ASSERT_EQUAL(m.begin()->second, 10);
	print_map(m);
	return (0);
}

int test_map_reverse_iterator()
{
	FT::map<char, int> m;

	m['a'] = 10;
	m['c'] = 30;
	m['b'] = 20;
	int count = 30;

	FT::map<char, int>::reverse_iterator rit = m.rbegin();
	FT::map<char, int>::reverse_iterator rite = m.rend();
	while (rit != rite)
	{
		ASSERT_EQUAL(rit->second, count);
		count -= 10;
		++rit;
	}
	ASSERT_EQUAL(m.size(), (unsigned int)3);
	ASSERT_EQUAL((m.rbegin())->second, 30);
	ASSERT_EQUAL((++m.rbegin())->second, 20);
	ASSERT_EQUAL((--m.rend())->second, 10);
	print_map(m);
	return (0);
}

int test_map_find()
{
	FT::map<char, int> m;
	FT::map<char, int>::iterator it;
	char tmp_c;

	m['a'] = 10;
	m['k'] = 20;

	it = m.find('a');
	tmp_c = it->first;
	ASSERT_EQUAL(tmp_c, 'a');
	ASSERT_EQUAL((m.find('k'))->first, 'k');
	ASSERT_EQUALQ((m.find('a')), m.begin());
	ASSERT_EQUALQ((m.find('b')), m.end());
	ASSERT_EQUALQ((m.find('k')), (++m.begin()));
	print_map(m);
	return (0);
}

int test_map_count()
{
	FT::map<char, int> m;

	m['a'] = 10;
	m['k'] = 20;

	ASSERT_EQUALQ((m.count('a')), (unsigned long)1);
	ASSERT_EQUALQ((m.count('b')), (unsigned long)0);
	ASSERT_EQUALQ((m.count('k')), (unsigned long)1);
	m.erase('k');
	ASSERT_EQUALQ((m.count('k')), (unsigned long)0);
	print_map(m);
	return (0);
}

int test_map_erase_by_iterator()
{
	FT::map<char, int> m;
	FT::map<char, int>::iterator it;

	m['a'] = 1;
	m['b'] = 2;
	m['c'] = 3;

	ASSERT_EQUAL(m.size(), (unsigned long)3);
	it = (++m.begin());
	m.erase(it);
	ASSERT_EQUAL(m.size(), (unsigned long)2);
	ASSERT_EQUAL(m.begin()->first, 'a');
	ASSERT_EQUAL((++m.begin())->first, 'c');
	print_map(m);
	return (0);
}

int test_map_erase_by_key()
{
	FT::map<char, int> m;
	FT::map<char, int>::iterator it;

	m['a'] = 1;
	m['b'] = 2;
	m['c'] = 3;

	ASSERT_EQUAL(m.size(), (unsigned long)3);
	it = (++m.begin());
	m.erase('c');
	ASSERT_EQUAL(m.size(), (unsigned long)2);
	ASSERT_EQUAL(m.begin()->first, 'a');
	ASSERT_EQUAL((++m.begin())->first, 'b');
	print_map(m);
	return (0);
}

int test_map_erase_by_range()
{
	FT::map<char, int> m;
	FT::map<char, int>::iterator it;

	m['a'] = 1;
	m['b'] = 2;
	m['c'] = 3;
	m['d'] = 4;
	m['e'] = 5;

	ASSERT_EQUAL(m.size(), (unsigned long)5);
	it = (++m.begin());
	m.erase(++it, m.end());
	ASSERT_EQUAL(m.size(), (unsigned long)2);
	ASSERT_EQUAL(m.begin()->first, 'a');
	ASSERT_EQUAL((++m.begin())->first, 'b');
	print_map(m);
	return (0);
}

int test_map_clear()
{
	FT::map<char, int> m;

	m['a'] = 1;
	m['b'] = 2;
	m['c'] = 3;

	ASSERT_EQUAL(m.size(), (unsigned long)3);
	m.clear();
	ASSERT_EQUAL(m.size(), (unsigned long)0);
	print_map(m);
	return (0);
}

int test_map_swap()
{
	FT::map<char, int> m1;
	FT::map<char, int> m2;

	m1['a'] = 1;
	m1['b'] = 2;
	m1['c'] = 3;
	m2['d'] = 11;
	m2['e'] = 12;
	m2['f'] = 13;
	m2['g'] = 14;

	m1.size();
	ASSERT_EQUAL(m1.size(), (unsigned long)3);
	ASSERT_EQUAL(m2.size(), (unsigned long)4);
	m1.swap(m2);
	ASSERT_EQUAL(m1.size(), (unsigned long)4);
	ASSERT_EQUAL(m2.size(), (unsigned long)3);
	ASSERT_EQUAL(m2.begin()->first, 'a');
	ASSERT_EQUAL(m2.begin()->second, 1);
	ASSERT_EQUAL(m1.begin()->first, 'd');
	ASSERT_EQUAL(m1.begin()->second, 11);
	print_map(m1);
	print_map(m2);
	return (0);
}

int test_map_four_values()
{
	FT::map<char, int> m1;

	m1['a'] = 1;
	m1['b'] = 2;
	m1['c'] = 3;
	m1['d'] = 11;

	m1.size();
	ASSERT_EQUAL(m1.size(), (unsigned long)4);
	print_map(m1);
	return (0);
}

int test_map_four_values_descending()
{
	FT::map<char, int> m1;

	m1['d'] = 5;
	m1['c'] = 4;
	m1['b'] = 3;
	m1['a'] = 2;

	m1.size();
	ASSERT_EQUAL(m1.size(), (unsigned long)4);
	print_map(m1);
	return (0);
}

int test_map_lower_bound()
{
	FT::map<char, int> m1;

	m1['b'] = 1;
	m1['c'] = 2;
	m1['e'] = 4;

	ASSERT_EQUAL(m1.lower_bound('a')->second, 1);
	ASSERT_EQUAL(m1.lower_bound('b')->second, 1);
	ASSERT_EQUAL(m1.lower_bound('c')->second, 2);
	ASSERT_EQUAL(m1.lower_bound('d')->second, 4);
	ASSERT_EQUAL(m1.lower_bound('e')->second, 4);
	ASSERT_EQUALQ(m1.lower_bound('f'), m1.end());
	print_map(m1);
	return (0);
}

int test_map_upper_bound()
{
	FT::map<char, int> m1;

	m1['b'] = 1;
	m1['c'] = 2;
	m1['e'] = 4;

	ASSERT_EQUAL(m1.upper_bound('a')->second, 1);
	ASSERT_EQUAL(m1.upper_bound('b')->second, 2);
	ASSERT_EQUAL(m1.upper_bound('c')->second, 4);
	ASSERT_EQUAL(m1.upper_bound('d')->second, 4);
	ASSERT_EQUALQ(m1.upper_bound('e'), m1.end());
	ASSERT_EQUALQ(m1.upper_bound('f'), m1.end());
	print_map(m1);
	return (0);
}

int test_map_equal_range()
{
	typedef FT::map<char, int>::iterator iterator;
	FT::map<char, int> m1;
	FT::pair<iterator, iterator> p;

	m1['b'] = 1;
	m1['c'] = 2;
	m1['e'] = 4;

	ASSERT_EQUAL(m1.equal_range('a').first->first, 'b');
	ASSERT_EQUAL(m1.equal_range('a').second->first, 'b');
	ASSERT_EQUAL(m1.equal_range('a').first->second, 1);
	ASSERT_EQUAL(m1.equal_range('a').second->second, 1);
	ASSERT_EQUAL(m1.equal_range('b').first->first, 'b');
	ASSERT_EQUAL(m1.equal_range('b').second->first, 'c');
	ASSERT_EQUAL(m1.equal_range('b').first->second, 1);
	ASSERT_EQUAL(m1.equal_range('b').second->second, 2);
	ASSERT_EQUAL(m1.equal_range('c').first->first, 'c');
	ASSERT_EQUAL(m1.equal_range('c').second->first, 'e');
	ASSERT_EQUAL(m1.equal_range('c').first->second, 2);
	ASSERT_EQUAL(m1.equal_range('c').second->second, 4);
	ASSERT_EQUAL(m1.equal_range('d').first->first, 'e');
	ASSERT_EQUAL(m1.equal_range('d').second->first, 'e');
	ASSERT_EQUAL(m1.equal_range('d').first->second, 4);
	ASSERT_EQUAL(m1.equal_range('d').second->second, 4);
	ASSERT_EQUAL(m1.equal_range('e').first->first, 'e');
	ASSERT_EQUAL(m1.equal_range('e').first->second, 4);
	ASSERT_EQUALQ(m1.equal_range('e').second, m1.end());
	ASSERT_EQUALQ(m1.equal_range('f').first, m1.end());
	ASSERT_EQUALQ(m1.equal_range('f').second, m1.end());
	print_map(m1);
	return (0);
}

int test_map_insert_random_order()
{
	FT::map<unsigned long, unsigned long> m;
	unsigned long amt_to_test = 100;

	unsigned long nums[] = {771,169,802,719,238,821,698,190,385,606,572,554,776,463,723,808,806,515,302,851,460,363,49,670,592,390,283,531,240,12,277,350,207,383,789,15,512,68,354,398,987,907,767,243,108,502,134,482,837,667,946,783,715,391,150,712,996,952,324,462,936,820,329,487,845,186,871,275,189,838,722,95,779,214,762,472,725,935,295,51,196,394,418,479,728,435,826,841,882,61,591,852,636,801,994,970,299,835,933,938};

	for (unsigned long i = 0; i < amt_to_test; ++i)
		m[nums[i]] = i;
	print_map(m);
	for (unsigned long i = 0; i < amt_to_test; ++i)
	{
		m.erase(nums[i]);
		print_map(m);
	}
	return (0);
}

int test_map_insert_and_erase_random_order()
{
	FT::map<unsigned long, unsigned long> m;
	unsigned long amt_to_test = 100;

	unsigned long nums[] = {898,476,187,103,795,71,257,580,255,608,867,851,821,643,556,615,881,991,921,589,874,727,456,429,411,838,942,35,982,249,746,667,433,432,158,113,230,614,280,597,540,947,88,987,901,73,12,900,683,333,545,902,7,826,469,833,381,294,957,656,362,638,978,640,605,248,306,706,619,956,977,413,781,971,622,208,105,173,137,646,583,284,572,657,288,840,848,986,787,175,261,780,114,349,327,868,10,182,885,774,461,632,34,470,119,275,654,163,397,58,61,259,997,124,737,91,926,756,427,82,299,748,932,511,388,866,74,89,440,383,709,835,218,235,714,745,761,508,591,62,449,185,167,152,775,749,732,302,49,291,650,514,768,473,386,785,179,287,106,28,490,718,675,39,216,857,31,6,205,320,207,609,587,157,554,686,988,361,803,817,916,899,303,518,339,75,146,153,3,845,853,274,610,189,973,955,653,854,747,618,304,529,909,341,337,770,652,827,492,551,960,405,281,677,475,536,430,398,468,954,81,879,937,194,830,897,627,311,509,326,979,790,282,892,127,367,246,353,499,735,301,786,462,980,575,21,662,766,724,121,392,661,731,154,890,699,273,212,846,396,191,407,694,97,695,613,708,300,939,460,63,439,232,929,406,87,496,894,364,263,46,655,463,444,972,174,889,913,990,102,129,586,408,378,733,120,94,561,645,400,639,253,852,111,743,136,176,448,611,590,755,880,340,651,873,607,239,471,887,934,483,594,211,110,256,698,635,981,360,555,964,348,519,704,229,437,998,719,600,841,494,843,782,217,177,504,331,967,65,384,402,245,562,549,379,459,669,644,516,70,84,268,922,401,422,243,862,203,345,713,414,54,225,352,126,149,170,92,222,924,466,672,631,484,966,151,399,861,221,328,356,912,391,184,822,995,502,914,474,870,794,115,436,227,428,231,538,241,142,723,574,270,293,86,777,55,258,616,829,365,664,143,629,789,801,863,421,742,720,765,537,453,193,823,925,52,548,526,850,329,363,517,450,228,670,588,710,59,712,697,876,535,112,604,906,385,592,159,606,271,140,793,395,148,734,478,30,684,141,8,893,322,882,122,911,4,596,77,628,40,691,566,946,252,568,531,772,47,310,633,334,665,457,116,214,730,716,403,530,647,240,527,130,265,936,905,505,50,726,617,539,776,262,769,335,959,858,626,759,948,585,80,279,636,671,512,702,884,792,832,809,181,532,984,344,696,254,621,108,441,725,784,431,197,952,949,849,192,847,779,791,68,741,272,503,139,692,44,186,438,226,336,994,480,808,918,482,658,435,209,958,368,637,180,446,579,498,992,1,705,267,343,390,56,369,620,83,953,416,393,603,688,927,599,951,546,903,104,944,237,969,195,904,888,818,497,542,728,164,26,721,33,479,190,131,488,598,162,128,522,486,552,630,204,318,27,584,679,377,298,155,123,700,23,266,565,923,523,783,974,276,717,935,389,825,95,144,642,570,687,419,371,250,15,238,680,559,802,350,649,220,739,940,500,357,156,315,961,24,168,805,685,778,425,183,404,834,236,9,219,251,844,933,673,41,752,308,442,289,420,160,109,118,816,45,738,907,689,359,223,29,864,351,309,424,506,493,877,305,125,917,319,582,491,51,454,886,321,67,799,467,296,567,797,804,161,234,976,543,324,999,36,22,264,297,938,819,57,72,78,495,813,612,767,842,477,722,510,865,520,796,201,18,663,188,244,641,412,202,100,507,2,533,48,451,557,380,25,347,375,150,292,171,242,215,172,5,711,915,962,98,13,455,16,481,690,736,965,285,983,487,896,66,920,38,993,625,338,286,452,908,96,472,601,883,707,342,410,758,79,374,458,703,569,872,943,93,581,564,64,107,233,134,928,659,196,521,674,578,464,138,930,409,528,812,931,210,515,423,307,198,330,577,101,815,224,443,525,269,576,762,445,346,660,20,372,989,90,701,373,376,828,560,623,417,693,247,513,323,558,807,260,295,277,99,820,806,132,355,501,875,524,325,855,550,666,85,593,678,69,60,753,740,919,485,76,489,278,571,382,312,963,811,831,165,757,771,316,985,891,465,945,213,810,744,358,950,788,426,1000,11,117,206,317,624,544,764,553,676,996,715,975,839,856,42,836,17,145,415,602,563,43,332,147,595,19,648,447,418,751,37,32,878,283,53,729,541,763,200,354,634,754,837,750,859,814,394,169,178,970,869,773,313,941,682,968,14,760,199,387,800,547,366,681,534,668,135,314,133,370,871,860,798,166,434,895,290,573,824,910};
	unsigned long nums2[] = {8,669,417,225,932,878,732,278,874,653,14,99,207,488,577,603,325,928,337,463,80,738,985,57,739,215,267,472,31,926,875,953,1000,775,524,922,986,514,907,618,54,769,419,323,685,159,450,756,155,59,561,800,187,527,3,838,123,797,75,947,277,906,478,406,431,500,641,398,372,507,558,951,461,433,285,964,935,247,132,581,853,724,4,449,319,251,886,335,513,399,731,733,927,409,146,897,269,848,127,519,762,802,177,868,576,595,718,841,630,790,729,484,317,678,200,374,866,546,793,812,352,944,138,473,913,301,712,363,315,359,987,665,199,586,367,425,609,960,348,700,163,139,95,462,97,191,53,725,844,780,438,120,453,170,705,280,555,365,757,571,549,42,943,408,566,233,495,961,457,105,156,656,401,209,276,602,538,17,446,600,262,13,690,442,29,490,750,709,942,835,291,135,708,668,525,117,931,945,486,383,52,65,714,494,71,281,440,479,976,345,11,826,257,166,655,683,604,995,471,796,579,557,565,161,114,124,259,781,880,891,634,811,25,688,294,109,292,434,717,522,505,234,339,773,635,506,915,420,357,900,217,21,670,141,542,824,266,827,302,601,814,612,836,89,175,334,2,716,707,864,882,784,713,119,799,142,703,174,390,658,962,232,892,646,697,320,504,468,763,908,933,20,787,326,137,607,719,192,605,354,5,6,810,201,806,324,270,696,375,180,760,640,388,220,15,333,465,66,834,726,360,76,197,573,454,7,598,444,307,154,666,261,983,244,178,111,283,572,136,744,673,777,741,28,948,914,483,903,305,260,936,402,78,41,512,37,485,254,803,680,361,889,237,493,984,214,521,228,594,67,62,877,497,994,939,564,411,567,46,938,843,297,186,196,309,686,631,455,194,870,832,946,316,788,480,271,165,876,865,400,937,858,837,64,341,887,975,242,88,10,387,991,902,789,193,47,502,327,158,441,734,679,662,203,620,608,660,541,710,427,145,288,143,185,422,58,255,560,691,958,102,711,771,842,252,859,412,511,861,34,249,110,230,687,651,924,786,671,240,72,809,520,674,528,35,721,68,925,229,23,94,342,121,675,966,825,134,751,79,644,336,749,404,61,40,972,849,698,168,188,617,24,779,312,370,279,530,821,100,467,957,300,611,828,940,179,918,250,428,899,692,107,56,466,407,856,147,554,979,850,198,314,202,614,537,282,526,70,981,971,625,378,795,860,181,830,736,745,816,664,308,451,574,358,753,405,748,854,930,596,366,299,413,636,213,474,148,672,950,265,437,582,973,552,133,344,182,904,693,18,318,30,978,954,584,619,45,578,162,629,460,49,992,350,647,368,847,727,464,580,470,223,677,909,245,195,765,173,243,539,382,766,475,949,969,982,993,888,392,905,157,545,384,364,222,840,663,997,303,22,999,823,306,51,974,559,833,989,768,867,599,410,715,212,873,755,167,613,169,183,221,55,272,115,96,652,274,332,492,103,929,508,219,952,921,380,510,839,393,807,436,654,681,910,236,439,543,610,862,535,9,551,556,805,50,916,499,657,740,293,901,794,284,27,153,39,211,414,956,934,591,532,628,890,149,347,791,622,632,536,184,590,206,491,389,730,418,550,397,63,160,458,69,12,920,758,639,569,489,804,172,226,616,469,74,684,43,706,171,91,638,720,648,517,588,429,322,642,911,73,884,896,128,33,563,338,289,423,592,362,970,426,371,568,818,477,792,346,445,923,313,895,996,487,150,116,912,264,883,879,963,112,659,258,93,118,503,239,695,385,872,965,208,637,218,482,881,822,32,857,817,501,448,723,36,290,801,129,955,509,176,329,248,855,376,570,377,224,998,421,852,268,813,518,650,216,694,728,774,722,343,752,871,587,776,498,643,48,845,340,869,808,356,585,238,104,190,394,205,553,98,60,122,893,106,81,125,435,77,164,676,583,496,759,452,231,746,189,381,988,778,90,355,328,846,747,298,204,379,863,476,626,295,523,959,534,597,767,144,330,761,544,820,785,287,894,246,84,701,235,606,743,548,627,432,649,331,615,311,621,633,623,241,396,699,273,764,919,83,702,980,310,82,26,575,101,1,321,44,424,798,391,386,227,253,286,447,968,92,885,403,296,624,783,661,210,831,152,275,108,917,481,369,819,529,456,459,16,19,415,151,967,373,772,256,131,898,263,990,140,353,126,735,516,86,689,851,782,754,443,531,682,547,416,737,742,593,829,351,589,667,770,941,349,533,430,38,85,540,395,645,815,113,562,87,977,704,130,515,304};

	for (unsigned long i = 0; i < amt_to_test; ++i)
	{
		m[nums[i]] = i;
		print_map(m);
	}
	for (unsigned long i = 0; i < amt_to_test; ++i)
	{
		m.erase(nums2[i]);
		print_map(m);
	}
	return (0);
}

int test_map_int_insert_med_low_high()
{
	FT::map<unsigned long, unsigned long> m;
	m[771] = 1;
	m[169] = 2;
	m[802] = 3;
	
	print_map(m);
	m.erase(771);
	print_map(m);
	m.erase(169);
	print_map(m);
	m.erase(802);
	print_map(m);

	return (0);
}

int test_map_overload()
{
	FT::map<unsigned long, unsigned long> m;

	for (unsigned long i = 500; i > 0; --i)
		m[i] = i;

	print_map(m);
	return (0);
}

int		test_map_mli_copy_construct(void)
{
	typedef int T1;
	typedef int T2;

	typedef FT::pair<const T1, T2> T3;
	std::list<T3> lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(lst_size - i, i));

	FT::map<T1, T2> mp(lst.begin(), lst.end());
	FT::map<T1, T2>::iterator it = mp.begin(), ite = mp.end();

	FT::map<T1, T2> mp_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 5;

	it = mp.begin(); ite = --(--mp.end());
	FT::map<T1, T2> mp_copy(mp);
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 7;

	if (VERBOSE)
		std::cout << "\t-- PART ONE --" << std::endl;
	print_map(mp);
	print_map(mp_range);
	print_map(mp_copy);

	mp = mp_copy;
	mp_copy = mp_range;
	mp_range.clear();

	if (VERBOSE)
		std::cout << "\t-- PART TWO --" << std::endl;
	print_map(mp);
	print_map(mp_range);
	print_map(mp_copy);
	return (0);
}

void	ft_find(int const &k, FT::map<int, std::string> mp)
{
	FT::map<int, std::string>::iterator ret = mp.find(k);
	FT::map<int, std::string>::iterator ite = mp.end();

	if (!VERBOSE)
		return;
	if (ret != ite)
	{
		std::cout << "first: " << ret->first << std::endl;
		std::cout << "second: " << ret->second << std::endl;
	}
	else
		std::cout << "map::find(" << k << ") returned end()" << std::endl;
}

static void	ft_count(int const &k, FT::map<int, std::string> mp)
{
	if (VERBOSE)
		std::cout << "map::count(" << k << ")\treturned [" << mp.count(k) << "]" << std::endl;
}

int		test_map_mli_find_count()
{
	typedef int T1;
	typedef std::string T2;

	FT::map<T1, T2> mp;
	// FT::map<T1, T2>::iterator it = mp.end();
	mp[42] = "fgzgxfn";
	mp[25] = "funny";
	mp[80] = "hey";
	mp[12] = "no";
	mp[27] = "bee";
	mp[90] = "8";
	print_map(mp);

	if (VERBOSE)
		std::cout << "\t-- FIND --" << std::endl;
	ft_find(12, mp);
	ft_find(3, mp);
	ft_find(35, mp);
	ft_find(90, mp);
	ft_find(100, mp);

	if (VERBOSE)
		std::cout << "\t-- COUNT --" << std::endl;
	ft_count(-3, mp);
	ft_count(12, mp);
	ft_count(3, mp);
	ft_count(35, mp);
	ft_count(90, mp);
	ft_count(100, mp);

	mp.find(27)->second = "newly inserted mapped_value";

	print_map(mp);

	FT::map<T1, T2> const c_map(mp.begin(), mp.end());
	if (VERBOSE)
	{
		std::cout << "const map.find(" << 42 << ")->second: [" << c_map.find(42)->second << "]" << std::endl;
		std::cout << "const map.count(" << 80 << "): [" << c_map.count(80) << "]" << std::endl;
	}
	return (0);
}

template <class T>
static void printPair(T it)
{
	if (VERBOSE)
		std::cout << it->first << " : " << it->second << std::endl;
}

int		test_map_mli_ite_arrow(void)
{
	typedef float T1;
	typedef foo<int> T2;
	typedef FT::pair<const T1, T2> T3;
	std::list<T3> lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(2.5 + i, i + 1));

	FT::map<T1, T2> mp(lst.begin(), lst.end());
	FT::map<T1, T2>::iterator it(mp.begin());
	FT::map<T1, T2>::const_iterator ite(mp.begin());
	print_map(mp);

	printPair(++ite);
	printPair(ite++);
	printPair(ite++);
	printPair(++ite);

	it->second.m();
	ite->second.m();

	printPair(++it);
	printPair(it++);
	printPair(it++);
	printPair(++it);

	printPair(--ite);
	printPair(ite--);
	printPair(--ite);
	printPair(ite--);

	(*it).second.m();
	(*ite).second.m();

	printPair(--it);
	printPair(it--);
	printPair(it--);
	printPair(--it);

	return (0);
}

static void	ft_find(int const &k, FT::map<int, std::string> & mp, FT::map<int, std::string>::iterator & it)
{
	FT::map<int, std::string>::iterator ret = mp.find(k);

	if (ret != it)
		printPair(ret);
	else
	{
		if (!VERBOSE)
			return;
		std::cout << "map::find(" << k << ") returned end()" << std::endl;
	}
}

static void	ft_find(int const &k, FT::map<int, std::string> & mp, FT::map<int, std::string>::const_iterator & it)
{
	FT::map<int, std::string>::iterator ret = mp.find(k);

	if (ret != it)
		printPair(ret);
	else
	{
		if (!VERBOSE)
			return;
		std::cout << "map::find(" << k << ") returned end()" << std::endl;
	}
}

int		test_map_mli_find_count2(void)
{
	FT::map<int, std::string> mp;
	FT::map<int, std::string>::iterator it = mp.end();

	mp[42] = "fgzgxfn";
	mp[25] = "funny";
	mp[80] = "hey";
	mp[12] = "no";
	mp[27] = "bee";
	mp[90] = "8";

	print_map(mp);

	std::cout << "\t-- FIND --" << std::endl;
	ft_find(12, mp, it);
	ft_find(3, mp, it);
	ft_find(35, mp, it);
	ft_find(90, mp, it);
	ft_find(100, mp, it);

	std::cout << "\t-- COUNT --" << std::endl;
	ft_count(-3, mp);
	ft_count(12, mp);
	ft_count(3, mp);
	ft_count(35, mp);
	ft_count(90, mp);
	ft_count(100, mp);

	mp.find(27)->second = "newly inserted mapped_value";

	print_map(mp);

	FT::map<int, std::string> const c_map(mp.begin(), mp.end());
	std::cout << "const map.find(" << 42 << ")->second: [" << c_map.find(42)->second << "]" << std::endl;
	std::cout << "const map.count(" << 80 << "): [" << c_map.count(80) << "]" << std::endl;
	return (0);
}
int		test_map_mli_find_count2_const(void)
{
	FT::map<int, std::string> mp;
	FT::map<int, std::string>::const_iterator it = mp.end();

	mp[42] = "fgzgxfn";
	mp[25] = "funny";
	mp[80] = "hey";
	mp[12] = "no";
	mp[27] = "bee";
	mp[90] = "8";

	print_map(mp);

	std::cout << "\t-- FIND --" << std::endl;
	ft_find(12, mp, it);
	ft_find(3, mp, it);
	ft_find(35, mp, it);
	ft_find(90, mp, it);
	ft_find(100, mp, it);

	std::cout << "\t-- COUNT --" << std::endl;
	ft_count(-3, mp);
	ft_count(12, mp);
	ft_count(3, mp);
	ft_count(35, mp);
	ft_count(90, mp);
	ft_count(100, mp);

	mp.find(27)->second = "newly inserted mapped_value";

	print_map(mp);

	FT::map<int, std::string> const c_map(mp.begin(), mp.end());
	std::cout << "const map.find(" << 42 << ")->second: [" << c_map.find(42)->second << "]" << std::endl;
	std::cout << "const map.count(" << 80 << "): [" << c_map.count(80) << "]" << std::endl;
	return (0);
}

int	test_map_empty_end()
{
	FT::map<int, std::string> mp;
	FT::map<int, std::string>::iterator ite1 = mp.end();
	FT::map<int, std::string>::iterator ite2 = mp.end();

	ASSERT_EQUAL( mp.empty(), true );
	ASSERT_EQUALQ( ite1, ite2 );
	mp[0] = "hi";
	ASSERT_EQUAL( mp.empty(), false );
	ASSERT_EQUALQ( ite1, ite2 );
	ite2 = mp.end();
	ASSERT_EQUALQ( ite1, ite2 );
	return (0);
}

template <class T>
static void	cmp(const T &lhs, const T &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

int		test_map_mli_relational_ope(void)
{
	#define T1 char
	#define T2 int	
	typedef FT::map<const int, char>	map_type;

	map_type mp1;
	map_type mp2;

	mp1['a'] = 2; mp1['b'] = 3; mp1['c'] = 4; mp1['d'] = 5;
	mp2['a'] = 2; mp2['b'] = 3; mp2['c'] = 4; mp2['d'] = 5;

	cmp(mp1, mp1); // 0
	cmp(mp1, mp2); // 1

	mp2['e'] = 6; mp2['f'] = 7; mp2['h'] = 8; mp2['h'] = 9;

	cmp(mp1, mp2); // 2
	cmp(mp2, mp1); // 3

	(++(++mp1.begin()))->second = 42;

	cmp(mp1, mp2); // 4
	cmp(mp2, mp1); // 5

	swap(mp1, mp2);

	cmp(mp1, mp2); // 6
	cmp(mp2, mp1); // 7

	return (0);
}

int test_map_const_map()
{
	typedef FT::map<char, int> const map_type;
	map_type	m;
	map_type::const_iterator	it = m.begin();
	map_type::const_iterator	ite = m.end();

	ASSERT_EQUAL(m.empty(), true);

	while (it != ite)
		++it;

	return (0);
}


void add_test_map_suite(FRAMEWORK_NAMESPACE::vector<Test2> *testlist)
{
	ADD_TEST(testlist, test_map_void_constructor);
	ADD_TEST(testlist, test_map_copy_constructor);
	ADD_TEST(testlist, test_map_iterator_constructor);
	ADD_TEST(testlist, test_map_empty);
	ADD_TEST(testlist, test_map_size);
	ADD_TEST(testlist, test_map_brackets_write);
	ADD_TEST(testlist, test_map_brackets_overwrite);
	ADD_TEST(testlist, test_map_brackets_read);
	ADD_TEST(testlist, test_map_insert_duplicate);
	ADD_TEST(testlist, test_map_reverse_iterator);
	ADD_TEST(testlist, test_map_find);
	ADD_TEST(testlist, test_map_count);
	ADD_TEST(testlist, test_map_erase_by_iterator);
	ADD_TEST(testlist, test_map_erase_by_key);
	ADD_TEST(testlist, test_map_erase_by_range);
	ADD_TEST(testlist, test_map_clear);
	ADD_TEST(testlist, test_map_four_values);
	ADD_TEST(testlist, test_map_four_values_descending);
	ADD_TEST(testlist, test_map_swap);
	ADD_TEST(testlist, test_map_lower_bound);
	ADD_TEST(testlist, test_map_upper_bound);
	ADD_TEST(testlist, test_map_equal_range);
	ADD_TEST(testlist, test_map_insert_random_order);
	ADD_TEST(testlist, test_map_insert_and_erase_random_order);
	ADD_TEST(testlist, test_map_int_insert_med_low_high);
	ADD_TEST(testlist, test_map_mli_copy_construct);
	ADD_TEST(testlist, test_map_mli_find_count);
	ADD_TEST(testlist, test_map_mli_ite_arrow);
	ADD_TEST(testlist, test_map_mli_find_count2);
	ADD_TEST(testlist, test_map_empty_end);
	ADD_TEST(testlist, test_map_mli_find_count2_const);
	ADD_TEST(testlist, test_map_const_map);	
}
