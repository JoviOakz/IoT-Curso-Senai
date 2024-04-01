#include <iostream>

using namespace std;

class Binario {
    private:
        unsigned char m_numero;
    
    public:
        Binario(unsigned char numero){
            m_numero = numero;
        }
    
        void print(){
            for(int i = 7; i >= 0; i--){
                cout << ((m_numero >> i) & 1);
            }
            
            cout << endl;
        }
};

int main() {
    Binario b1(10);
    b1.print();

    return 0;
}