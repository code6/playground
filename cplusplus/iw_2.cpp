#include <iostream>
#include <vector>
using namespace std;

template<class T>
class Wrapper {
public:
    Wrapper(vector<T> &v,
        typename vector<T>::iterator it)
        :_vec(v),_it(it),_tempIt(it){
            _it = _vec.begin();
    };

    bool hasNext(){
        _tempIt = _it;
        return (++_tempIt)!=_vec.end();
    };

    T next(){return *++_it;};

    T peek(){
        _tempIt = _it;
        return *++_tempIt;
    };

    T operator*() {return *_it;};    

private:
    vector<T> _vec;
    typename vector<T>::iterator _it;  
    typename vector<T>::iterator _tempIt;  
};
int main()
{       
    int a[]={1,2,3,4,5};
    vector<int> v(a, a+5);
    vector<int>::iterator it;
    Wrapper<int> wit(v, it);

    cout<<"current: "<<*wit<<endl;   
    cout<<"hasNext: "<<wit.hasNext()<<endl;   
    cout<<"go next: "<<wit.next()<<endl;
    cout<<"current: "<<*wit<<endl;  
    cout<<"peek next: "<<wit.peek()<<endl; 
    cout<<"current: "<<*wit<<endl;   
    std::cin.get();
    return 0;
}
