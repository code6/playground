#include <iostream>

using namespace std;

template<class T>
class Iterator {
    public:
        bool hashNext() {
        }
        T next() {
        }
};

template<class T>
class IteratorWrapper {
    public:
        Iterator<T> it;
        T peek;
        bool hasPeek;
        IteratorWrapper(Iterator<T> it) {
            self.it = it;
            self.hasPeek = false;
            if (self.it.hashNext()) {
                self.hashPeek = true;
                self.peek = it.next();
            }
        }

        bool hashNext() {
            return self.hasPeek;
        }

        T next() {
            if (self.hasPeek) {
                T ret = self.peek;
                if (self.it.hasNext()) {
                    self.hasPeek = true;
                    self.peek = it.next();
                } else {
                    self.hasPeek = false;
                }
                return ret;
            } else {
                throw //
            }
        }
};
