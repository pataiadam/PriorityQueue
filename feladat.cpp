/**
 * Az osztálysablon neve my_priqueue.
 * A sablon paraméterezése:
 *   - T: a sorba helyezhetõ elemek típusa
 *   - Comparator: típus, aminek példányai rendezést megvalósító 
 *                 függvényobjektumok
 */
template<class T, class Comparator>
class my_priqueue {
public:
    /** Belsõ osztály, amely az elõrehaladó iterátort valósítja meg. */
    class iterator;
    /** Belsõ osztály, amely a hátrafeléhaladó iterátort valósítja meg. */
    class reverse_iterator;
    /** A sablonpéldány rendelkezik default konstruktorral. */
    my_priqueue();
    /** Elem beszúrása a prioritási sorba a rendezésnek megfelelõ helyre. */
    void push(const T &item);
    /** A prioritási sor legelsõ elemének eltávolítása és visszaadása. */
    T pop();
    /** A prioritási sorban levõ elemek száma. */
    int size();
    /** A prioritási sor elemeinek indexelése (0-tól size()-1 -ig). */
    const T& operator[](int index) const;
    /** Elõrehaladó kétirányú iterátor típus a prisor elemeinek bejárására. */
    class iterator;
    /** Hátrafelé haladó kétirányú iterátor típus a prisor elemeinek bejárására. */
    class reverse_iterator;
    /** Elõrehaladó iterátor a prisor legelsõ elemére. */
    iterator begin();
    /** Elõrehaladó iterátor a prisor utolsó utáni elemére. */
    iterator end();
    /** Hátrafelé haladó iterátor a prisor utolsó elemére. */
    reverse_iterator rbegin();
    /** Hátrafelé haladó iterátor a prisor elsõ elõtti elemére. */
    reverse_iterator rend();
};

// === MEGVALÓSÍTÁS VÉGE ===

struct comparator {
    /** 
     * Függvényhívás operátor felüldefiniálása, amely rendezést valósít meg. 
     * Visszatérési értéke igaz, ha a < b valamilyen rendezési reláció szerint.
     */
    bool operator()(const int &a, const int &b);
};

int main() {
    my_priqueue<int> q1;
    q1.push(77);
    q1.push(27);
    q1.push(7);
    
    my_priqueue<int, comparator> q2;
    q2.push(31);
    q2.push(1977);

    return 0;
}
