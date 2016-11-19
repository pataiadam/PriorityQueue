/*#include <iostream>
#include <string>
using namespace std;
*/

/**
 * Comparator: típus, aminek példányai rendezést megvalósító függvényobjektumok
 */
template<class T>
struct comparator {
    /** 
     * Függvényhívás operátor felüldefiniálása, amely rendezést valósít meg. 
     * Visszatérési értéke igaz, ha a < b valamilyen rendezési reláció szerint.
     */
    bool operator()(const T &a, const T &b){
        return a<b;
    };
};

/**
 * Az osztálysablon neve my_priqueue.
 * A sablon paraméterezése:
 *   - T: a sorba helyezhetõ elemek típusa
 *   - Comparator: típus, aminek példányai rendezést megvalósító 
 *                 függvényobjektumok
 */
template<class T=int, class Comparator = comparator<int>>
class my_priqueue {
public:
    /** Belsõ osztály, amely az elõrehaladó iterátort valósítja meg. */
    class iterator      
    {
        public:
            /** default konstruktor */
            iterator() : _p(0) {}
			/** * operátor overloading/dereferencia */                             
            T& operator*() { return *_p; }
            /** prefix ++ */                                   
            iterator& operator++() { ++_p; return *this; }                         
            /** postfix ++ */
            iterator operator++(int) { iterator temp(*this); ++_p; return temp; }
            /** prefix -- */
            iterator& operator--() { --_p; return *this; }                         
            /** postfix -- */
            iterator operator--(int) { iterator temp(*this); --_p; return temp; }                     
            /** nem egyenlő operator */
            bool operator!=(const iterator &it) { return _p != it._p; }
            /** egyenlő operator */
            bool operator==(const iterator &it) { return _p != it._p; }
        private:
            /** private konstruktor */
            iterator(T* p) : _p(p) {}  
            /** az aktualisan mutatott elem */
            T* _p;
        /** friend definició */
		friend class my_priqueue<T,Comparator>; 
    };
    /** Belsõ osztály, amely a hátrafeléhaladó iterátort valósítja meg. */
    class reverse_iterator      
    {
        public:
            /** default konstruktor */
            reverse_iterator() : _p(0) {}
			/** * operátor overloading/dereferencia */                             
            T& operator*() { return *_p; }
            /** prefix ++ */                                   
            reverse_iterator& operator++() { --_p; return *this; }                         
            /** postfix ++ */
            reverse_iterator operator++(int) { reverse_iterator temp(*this); --_p; return temp; }
            /** prefix -- */
            reverse_iterator& operator--() { ++_p; return *this; }                         
            /** postfix -- */
            reverse_iterator operator--(int) { reverse_iterator temp(*this); ++_p; return temp; }
            /** nem egyenlő operator */
            bool operator!=(const reverse_iterator &it) { return _p != it._p; }     
            /** egyenlő operator */
            bool operator==(const reverse_iterator &it) { return _p != it._p; }  
        private:
            /** private konstruktor */
            reverse_iterator(T* p) : _p(p) {}  
            /** az aktualisan mutatott elem */
            T* _p;
        /** friend definició */
		friend class my_priqueue<T,Comparator>; 
    };
    /** A sablonpéldány rendelkezik default konstruktorral. */
    my_priqueue() : _queue(new T[0]), _size(0), _capacity(0) {

	};
    /** A destruktor felszabadítja a memóriaterületet. */
    ~my_priqueue() { 
		delete[] _queue; 
	}
    /** Elem beszúrása a prioritási sorba a rendezésnek megfelelõ helyre. */
    void push(const T &item) {     
        if ( _capacity == _size) {
            int tmpcap = _capacity * 2 + 1;                        
            T *tmpqueue = new T[tmpcap];             
            for (int i = 0; i < _capacity; i++) {
                tmpqueue[i] = _queue[i];
            }
            delete[] _queue;
            _queue = tmpqueue;
            _capacity = tmpcap;
        }
        _queue[_size] = item;
        _size++;
        
        //sort
        for (int j = _size-2; 0<=j; j--)
        {
            if (_comparator(_queue[j+1],_queue[j]))
            {
                T temp;
                temp = _queue[j];
                _queue[j] = _queue[j+1];
                _queue[j+1] = temp;
            }
        }
    }
    /** A prioritási sor legelsõ elemének eltávolítása és visszaadása. */
    T pop() {
        T ret = _queue[0];
        for (int i = 1; i<_size; i++){
            _queue[i-1] = _queue[i];
        }
        _size--;
        return ret;
    };
    /** A prioritási sorban levõ elemek száma. */
    int size() { return _size; };
    /** A prioritási sor elemeinek indexelése (0-tól size()-1 -ig). */
    const T& operator[](int index) const { return _queue[index]; };
    /** Elõrehaladó kétirányú iterátor típus a prisor elemeinek bejárására. */
    class iterator;
    /** Hátrafelé haladó kétirányú iterátor típus a prisor elemeinek bejárására. */
    class reverse_iterator;
    /** Elõrehaladó iterátor a prisor legelsõ elemére. */
    iterator begin() { return iterator(_queue); }
    /** Elõrehaladó iterátor a prisor utolsó utáni elemére. */
    iterator end() { return iterator(_queue + _size); }
    /** Hátrafelé haladó iterátor a prisor utolsó elemére. */
    reverse_iterator rbegin() { return reverse_iterator(_queue + _size - 1); }
    /** Hátrafelé haladó iterátor a prisor elsõ elõtti elemére. */
    reverse_iterator rend() { return reverse_iterator(_queue - 1 ); }
	private: 
		/** elemek tárolása a prioritási sorban */
		T *_queue;
		/** a prioritási sorban lévő elemek száma */ 
		int _size;
		/** _queue adattároló maximális kapacitása */
		int _capacity;
		/** Sablonpéldány a rendezésre */
		Comparator _comparator;

};

// === MEGVALÓSÍTÁS VÉGE ===
//Testing
/*int main() {
    my_priqueue<int> q0;
    q0.push(76);
    q0.push(1);
    q0.push(2);
    q0.push(27);
    q0.push(7);
    my_priqueue<int>::reverse_iterator it0;
    it0 = q0.rbegin();    
    while(*it0 != *q0.rend()){
        cout << *it0 << " " << endl;
        ++it0;
    }
     
    my_priqueue<string, comparator<string>> q1;
    q1.push("bbb");
    q1.push("dddd");
    q1.push("dd");
    q1.push("aa");
    q1.push("ccc");
    my_priqueue<string, comparator<string>>::reverse_iterator it1;
    it1 = q1.rend();
      
     while((--it1) != q1.rbegin()){
        cout << *it1 << " " << endl;
    }
   
    return 0;
}
*/
