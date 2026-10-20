
#include <iostream>
#include <syncstream>
#include <thread>
#include <latch>
#include <chrono>
#include <cstdlib>
using namespace std;

latch done_a(8);
latch done_b(5);
latch done_c(5);
latch done_d(5);
latch done_e(5);
latch done_f(7);
latch done_g(4);
latch done_h(4);
latch done_i(5);
latch done_j(9);

void f(char x, int i)
{
    this_thread::sleep_for(1s);
    osyncstream(cout) << "З набору " << x << " виконано дію " << i << "." << endl;
}


void do_action(char x, int i, latch& done)
{
    f(x, i);
    done.count_down();
}


void wait_a()     { done_a.wait(); }                                 
void wait_b_e()   { done_b.wait(); done_e.wait(); }                   
void wait_c()     { done_c.wait(); }                                  
void wait_g_i_f() { done_g.wait(); done_i.wait(); done_f.wait(); }    
void wait_d_h_j() { done_d.wait(); done_h.wait(); done_j.wait(); }   


void thread1()
{
    do_action('c', 1, done_c);
    do_action('a', 1, done_a);
    do_action('a', 6, done_a);
    do_action('b', 3, done_b);
    do_action('e', 3, done_e);
    wait_a();
    do_action('d', 1, done_d);
    do_action('g', 1, done_g);
    wait_b_e();
    do_action('h', 1, done_h);
    do_action('i', 1, done_i);
    wait_c();
    do_action('f', 1, done_f);
    do_action('f', 6, done_f);
    wait_g_i_f();
    f('n', 1);
    wait_d_h_j();
    f('k', 1);
}

void thread2()
{
    do_action('c', 2, done_c);
    do_action('a', 2, done_a);
    do_action('a', 7, done_a);
    do_action('b', 4, done_b);
    do_action('e', 4, done_e);
    wait_a();
    do_action('d', 2, done_d);
    do_action('g', 2, done_g);
    wait_b_e();
    do_action('h', 2, done_h);
    do_action('i', 2, done_i);
    wait_c();
    do_action('f', 2, done_f);
    do_action('f', 7, done_f);
    wait_g_i_f();
    f('n', 2);
    wait_d_h_j();
    f('k', 2);
}

void thread3()
{
    do_action('c', 3, done_c);
    do_action('a', 3, done_a);
    do_action('a', 8, done_a);
    do_action('b', 5, done_b);
    do_action('e', 5, done_e);
    wait_a();
    do_action('d', 3, done_d);
    do_action('g', 3, done_g);
    wait_b_e();
    do_action('h', 3, done_h);
    do_action('i', 3, done_i);
    wait_c();
    do_action('f', 3, done_f);
    do_action('j', 5, done_j);
    wait_g_i_f();
    f('n', 3);
    wait_d_h_j();
    f('k', 3);
}

void thread4()
{
    do_action('c', 4, done_c);
    do_action('a', 4, done_a);
    do_action('b', 1, done_b);
    do_action('e', 1, done_e);
    wait_c();
    do_action('j', 1, done_j);
    wait_a();
    do_action('d', 4, done_d);
    do_action('g', 4, done_g);
    wait_b_e();
    do_action('h', 4, done_h);
    do_action('i', 4, done_i);
    do_action('f', 4, done_f);
    do_action('j', 6, done_j);
    do_action('j', 8, done_j);
    wait_d_h_j();
    f('k', 4);
}

void thread5()
{
    do_action('c', 5, done_c);
    do_action('a', 5, done_a);
    do_action('b', 2, done_b);
    do_action('e', 2, done_e);
    wait_c();
    do_action('j', 2, done_j);
    wait_a();
    do_action('d', 5, done_d);
    do_action('j', 3, done_j);
    do_action('j', 4, done_j);
    wait_b_e();
    do_action('i', 5, done_i);
    do_action('f', 5, done_f);
    do_action('j', 7, done_j);
    do_action('j', 9, done_j);
}

int main()
{
    system("chcp 65001 > nul");
    auto start = chrono::steady_clock::now();
    osyncstream(cout) << "Обчислення розпочато." << endl;
    {
        jthread t1(thread1);
        jthread t2(thread2);
        jthread t3(thread3);
        jthread t4(thread4);
        jthread t5(thread5);
    }   
    chrono::duration<double> dt = chrono::steady_clock::now() - start;
    osyncstream(cout) << "Обчислення завершено. Тривалість обчислення "
                      << dt.count() << " секунд." << endl;
}
                                                                                                                                                                                                                                                                                                                         