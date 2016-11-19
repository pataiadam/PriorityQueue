//#include<iostream>
//using namespace std;

struct comparator {
    /** 
     * Függvényhívás operátor felüldefiniálása, amely rendezést valósít meg. 
     * Visszatérési értéke igaz, ha a < b valamilyen rendezési reláció szerint.
     */
    bool operator()(const int &a, const int &b){
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
template<class T, class Comparator = comparator>
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
        private:
            /** private konstruktor */
            iterator(T* p) : _p(p) {}  
            /** az aktualisan mutatott elem */
            T* _p;
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
        private:
            /** private konstruktor */
            reverse_iterator(T* p) : _p(p) {}  
            /** az aktualisan mutatott elem */
            T* _p;
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
    const T& operator[](int index) const;
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
/*1int main() {
    my_priqueue<int, comparator> q1;
    q1.push(76);
    q1.push(1);
    q1.push(2);
    q1.push(27);
    q1.push(7);
    my_priqueue<int>::reverse_iterator it;
    it = q1.rbegin();    
    while(*it != *q1.rend()){
        cout << *it << " " << endl;
        ++it;
    }
        
    return 0;
}*/
