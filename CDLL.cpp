
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
using namespace std;
int MAXSIZE;
class DLL
{
public:
    class customer;
public:
    /* data */
    customer* head;
    int count;
public:
    DLL(): head(nullptr), count(0){}
    ~DLL(){
        this->clear();
    }
    void    add(string name, int energy);
    void    add(int index, string name, int energy);
    int     size();
    bool    empty();
    string	get(int index);
    customer* getNodeByIndex(int index);
    int     getEnergy(int index);
    void    set(int index,string e, int energy);
    int     indexOf(string item);
    bool    contains(string item);
    void    clear();
    string  removeAt(int index);
    bool    removeItem(string item);
    void    shellSort(int n, int& swap);
    void    inssort2(DLL* listHead, int n, int incr, int& swap);
    bool    prior(int a, int b) {
                return a < b; // Sort in ascending order
            }
    void    my_swap(DLL* listHead, int i, int j) {
                int temp = listHead->getNodeByIndex(i)->energy;
                listHead->getNodeByIndex(i)->energy = listHead->getNodeByIndex(j)->energy;
                listHead->getNodeByIndex(j)->energy = temp;
            }
    void    toString(){
        customer* temp = head;
        for (int i = 0; i < count; i++)
        {
            cout<< temp->energy << " ";
            temp = temp->next;
        }
        cout<< endl;
    }
public:
    class customer{
        public:	
            string name;
            int energy;
            customer* prev;
            customer* next;
        public:
            customer(){}
            customer(string na, int e, customer* p, customer *ne): name(na), energy(e), prev(p), next(ne){}
            ~customer(){}
            void print() {
                cout << name << "-" << energy << endl;
            }
    };
};

void DLL::add(string name, int energy)
{
    if(this->count == 0){
        customer* newNode = new customer(name, energy, nullptr, nullptr);
        newNode->next = newNode;
        newNode->prev = newNode;
        this->head  = newNode;
    }else{
        customer* newNode = new customer(name, energy, nullptr, nullptr);
        //them vao cuoi
		newNode->next = this->head;
		newNode->prev = this->head->prev;
		this->head->prev->next = newNode;
		this->head->prev = newNode;
    }
    this->count++;
}
void DLL::add(int index, string name, int energy)
{
	/* Insert an element into the list at given index. */ 
    if(index < 0 || index > this->count)
        throw std::out_of_range(" invalid index");
    if(count == 0 || index == count){
        return add(name, energy);
    }
    if(index == 0){
        customer* newNode = new customer(name, energy, nullptr, nullptr);
        newNode->next = this->head;
		newNode->prev = this->head->prev;
		this->head->prev->next = newNode;
		this->head->prev = newNode;
        this->head = newNode;
        count++;
        return ;
    }
    customer* tmp = new customer(name, energy, nullptr, nullptr);
    customer* prev = this->head;
    for(int i=0 ; i < index-1 ; i++ ){
        prev = prev->next;
    }
    tmp->next = prev->next;
    tmp->prev = prev;
    prev->next = tmp;
    tmp->next->prev = tmp;
    count ++;
}
int DLL::size()
{
    return this->count;
}

bool DLL::empty()
{
	if (this->count == 0)
		{
			return true;
		}
		
	return false;
}
string DLL::get(int index)
{
    if (index < 0 || index > (this->count -1))
    {
        throw std::out_of_range(" invalid index");
    }
    customer* temp = this->head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    
    return temp->name;
}
int DLL::getEnergy(int index)
{
    if (index < 0 || index > (this->count -1))
    {
        throw std::out_of_range(" invalid index");
    }
    customer* temp = this->head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    
    return temp->energy;
}
void DLL::set(int index, string e, int energy)
{
	if (index < 0 || index > (this->count -1))
    {
        throw std::out_of_range(" invalid index");
    }
    customer* temp = this->head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    temp->name = e;
	temp->energy = energy;
    return ;
}
int DLL::indexOf(string item)
{
    customer* temp = this->head;
    for (int i = 0; i < this->count; i++)
    {   if (temp->name == item)
        {
            return i;
        }
    
        temp = temp->next;
    }
    return -1;
}
bool DLL::contains(string item)
{
    customer* temp = this->head;
    for (int i = 0; i < this->count; i++)
    {   if (temp->name == item)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}
void DLL::clear()
{
    customer* current = head;
    while (current != nullptr) {
        customer* temp = current;
        current = current->next;
        delete temp;
        if (current == head) {
            break; // Tránh lặp vô hạn trong trường hợp danh sách liên kết đôi vòng
        }
    }
    head = nullptr; // Đặt con trỏ head về nullptr để tránh giải phóng lặp
    
    
}
string DLL::removeAt(int index)
{
    if (index < 0 || index >= this->count)
        throw std::out_of_range("out of range");
    if ( count == 1) {
        customer* tmp = this->head;
        this->head =  nullptr;
        string value = tmp->name;
        delete tmp;
        count--;
        return value;
    }
    if (index == 0){
        customer* tmp = head;
        string value = tmp->name;
        this->head->prev->next = this->head->next;
        this->head->next->prev = this->head->prev;
        head = head->next;
        delete tmp;
        count--;
        return value;
    }
    customer* prev = head;
    for(int i=0 ; i < index-1 ; i++ ){
        prev = prev->next;
    }
    customer* tmp = prev->next;
    string value = tmp->name;
    prev->next = tmp->next;
    tmp->next->prev = prev;
    delete tmp;
    count--;
    return value;
}
bool DLL::removeItem(string item)
{
    int x = indexOf(item);
    if(x != -1){
        removeAt(x);
        return true;
    }

    return false;
}
DLL::customer* DLL::getNodeByIndex(int index){
if (index < 0 || index > (this->count -1))
    {
        throw std::out_of_range(" invalid index");
    }
    customer* temp = this->head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    
    return temp;
}
void DLL::shellSort(int n, int& swap) {
    for (int i=n/2; i>1; i/=2){      // For each increment
        for (int j=0; j<i; j++){       // Sort each sublist
            DLL* temp = new DLL();
            temp->head = this->getNodeByIndex(j);
            temp->count = n;
            inssort2(temp, n-j, i, swap);
        }
    }
  inssort2(this, n, 1, swap);     
}
void DLL::inssort2(DLL* listHead, int n, int incr, int& swap) {
    for (int i = incr; i < n; i += incr){
        for (int j = i; (j >= incr) && (prior(abs(listHead->getNodeByIndex(j)->energy), abs(listHead->getNodeByIndex(j-incr)->energy))); j -= incr){
            my_swap(listHead, j, j - incr);
            swap++;
        }
    }
}



// Thiết lập giá trị của node tại vị trí index

int main(){
    DLL list;
    for(int index = 0; index < 10; index++){
        list.add(0, "jkk",index);
    }

    list.toString();
    list.add("cc", 17);
    list.toString();
    list.removeAt(4);
    list.toString();
    int N =0;
    list.shellSort(10, N);
    list.toString();
    cout<< N ;
}