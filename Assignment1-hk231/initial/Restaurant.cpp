#include "main.h"
//ID:1927003
class imp_res : public Restaurant
{
	//sử dụng danh sách liên kết vòng nên chỉ dùng 1 con trỏ cho 1 danh sách:
	//với danh sách ăn head là vị khách vừa được thêm vào sau khi so sánh các chỉ sổ
	//với danh sách chờ thì head mặc định lúc nào cũng là front vì phục vụ theo queue FIFO
	//2 biến để đếm số lượng các khách hàng trong các danh sách
	public:
		class SinglyList;
		class DCLL;
	private:
		SinglyList* listWaiting;
		DCLL* listEating;
		SinglyList* listRemove;
	public:	
		imp_res() : listWaiting(new SinglyList()), listEating(new DCLL() ), listRemove(new SinglyList()) {}

		virtual ~imp_res() {
    	}

		void RED(string name, int energy)
		{
			//cout << name << " " << energy << endl;
			//các trường hợp không tiếp nhận khách nữa: energy = 0, eatingcount + waitingcount = 2*maxsize, check name trong cac 2 list
			if(energy == 0 || (this->listEating->count+this->listWaiting->count) >= 2*MAXSIZE|| this->listEating->contains(name) || this->listWaiting->contains(name))
				return ;
			
			//customer *cus = new customer (name, energy, nullptr, nullptr);
			//check MAXSIZE/2 sau do moi dung chien thuat lap vi tri
			if(this->listEating->count < (MAXSIZE/2)){
				//option 1
				//khi vua mo cua hang thi khach co the ngoi bat ky dau

				//energy lon hon hoac bang se o vi tri cung chieu kdh, khong thi nguoc lai
				if(!this->listEating->head){
					this->listEating->add(name, energy);
				}else{
					if (energy >= this->listEating->head->energy)
					{
					
						this->listEating->add(1, name, energy);
						this->listEating->head = this->listEating->head->next;
					}else{
						this->listEating->add(name, energy);
						this->listEating->head = this->listEating->head->prev;
					}
					
				}
				//this->eatingCount++;
				this->listRemove->add( name, energy);//them o cuoi lay ra o dau

			}else if(this->listEating->count < MAXSIZE){
			
			
			//option 2: Res cang lon cang tot va la vi tri dau tien theo chieu kdh sau do bo tri tuyet doi va chon lai
			//theo thu tu am thi nguoc chieu kdh va nguoc lai
			//RES= |Khach moi - Khach cu|

			//hang cho co so luong bang MAXSIZE va se ko nhan them khi da du hang cho
			int max = this->listEating->findMaxRES(energy);
			while (abs((energy - this->listEating->head->energy)) != max)
			{
				this->listEating->head = this->listEating->head->next;
			}
			if ((energy - this->listEating->head->energy) > 0)
			{
				
				this->listEating->add(1, name, energy);
				this->listEating->head = this->listEating->head->next;
			}else{
				
				this->listEating->add(name, energy);
				this->listEating->head = this->listEating->head->prev;
			}
			this->listRemove->add(name, energy);
			} else{
				
				this->listWaiting->add(name, energy);
			}
		}
		void BLUE(int num)
		{
			
			//kiem tra neu co khach dang cho se tien hanh thu don khach trong nha hang neu dung qua lau
			//num > khach || num > maxsize se duoi het khach
			if( num == 0) return ;
			if(num > this->listEating->count || num > MAXSIZE){
				
				for (int i = 0; i < this->listRemove->count; i++)
				{
					string nameDelete = this->listRemove->removeAt(0);
					int X = this->listEating->searchNodeByName(nameDelete)->energy;
					if( X > 0){ 
						this->listEating->head = this->listEating->head->next;
					}else {
						
						this->listEating->head = this->listEating->head->prev;
					}
					
					this->listEating->removeItem(nameDelete);
				}
				
				
        		
			}
			for (int i = 0; i < num; i++) //xoa n khach
			{	
				
				string nameDelete = this->listRemove->removeAt(0);
				this->listEating->head = this->listEating->searchNodeByName(nameDelete);
				if( this->listEating->head->energy > 0){ 
					this->listEating->head = this->listEating->head->next;
				}else {
					
					this->listEating->head = this->listEating->head->prev;
				}
				
				this->listEating->removeItem(nameDelete);
			}
			if(this->listWaiting->count == 0) return ;
			for (int i = 0; i < this->listWaiting->count; i++)
			{
				/* code */
				if(this->listEating->count == MAXSIZE){
					break;
				}
				//enqueue
				string name = this->listWaiting->head->name;
				int energy = this->listWaiting->head->energy;
				this->listWaiting->removeAt(0);
				this->RED(name ,energy );
				
				
			}

		}
		void PURPLE()
		{
			
			// sap xep lai hang cho theo gia tri tuyet doi energy theo giai thuat Shell Sort
			if(this->listWaiting->count == 0) return;
			customer *temp = this->listWaiting->head;
			int max = this->listWaiting->findMaxRES(0);
			for (int i = 0; i < this->listWaiting->count; i++)
			{
				if (abs(temp->energy) == max)
				{
					break;
				}
				temp = temp->next;
				
			}
			int N = 0;
			int n = this->listWaiting->indexOf(temp->name) + 1;
			this->listWaiting->shellSort(n, N);
			this->BLUE(N % MAXSIZE);

			//lay so lan chuyen doi cua Shell Sort sau do tien hanh Blue voi tham so num = N mod MAXSIZE

		}
		void REVERSAL()
		{
			
			string temp = this->listEating->head->name;
			for (int i = 0; i < this->listEating->count; i++)
			{
				
				if(((this->listEating->head->energy < 0) && (this->listEating->head->prev->energy < 0)) ||
				((this->listEating->head->energy > 0) && (this->listEating->head->prev->energy > 0))){
					this->listEating->my_swap(this->listEating, 0, this->listEating->count - 1);
				}
				this->listEating->head = this->listEating->head->prev;
			}
			this->listEating->head = this->listEating->searchNodeByName(temp);
			
		}
		void UNLIMITED_VOID()
		{
			//cout << "unlimited_void" << endl;
			if(this->listEating->count < 5) return;
			// tim theo chieu kdh day con (>=4)
			// ko tim duoc thi ko can lam gi ca
			int	indexSub = 0;
			int lenghtSub = 0;
			int sumMinSub = 2147483647;
			for (int i = 0; i < this->listEating->count - 3 ; i++)
			{	
				for (int j = 4 ; j < this->listEating->count - i + 1; j++)
				{
					customer* temp = this->listEating->getNodeByIndex(i);
					int sumSub = 0;
					int  k = 0 ;
					while (k<j)
					{
						/* code */
						sumSub += temp->energy;
						k++;
						temp = temp->next;
					}
					if(sumSub < sumMinSub){
						sumMinSub = sumSub;
						indexSub = i;
						lenghtSub = j;
					}
					
				}
				
			}
			customer* temp = this->listEating->getNodeByIndex(indexSub);
			DCLL *temp2 = new DCLL(); // tao sublist con
			for (int i = 0; i < lenghtSub; i++)
			{
				temp2->add(temp->name, temp->energy);
				temp = temp->next;
			}
			// dich chuyen head den phan tu co energy nho nhat
			temp2->head = temp2->findMinEnergy();
			//in ket qua theo chieu kim dong ho
			temp2->toStringPositive();

			
		}
		void DOMAIN_EXPANSION()
		{
			
			if((this->listEating->sumPositive() + this->listWaiting->sumPositive()) >= abs(this->listEating->sumNagitive() + this->listWaiting->sumNagitive())){
				
					int i = 0;
					while (i < this->listRemove->count)
					{
						if(this->listRemove->getNodeByIndex(i)->energy < 0){
							string nameDelete = this->listRemove->removeAt(i);	
							this->listEating->searchNodeByName(nameDelete)->print();
							this->listEating->removeItem(nameDelete);
						}else{i++;}
					}
					
					
				
					i = 0;
					while (i < this->listWaiting->count)
					{
						if(this->listWaiting->getNodeByIndex(i)->energy < 0){
							this->listWaiting->getNodeByIndex(i)->print();
							this->listWaiting->removeAt(i);
						}else{i++;}
					}
					

			}else{
				
					int i = 0;
					while (i < this->listRemove->count)
					{
						if(this->listRemove->getNodeByIndex(i)->energy > 0){
							string nameDelete = this->listRemove->removeAt(i);
							this->listEating->searchNodeByName(nameDelete)->print();
							this->listEating->removeItem(nameDelete);
						}else{i++;}
					}
				
					i = 0;
					while (i < this->listWaiting->count)
					{
						if(this->listWaiting->getNodeByIndex(i)->energy > 0){
							this->listWaiting->getNodeByIndex(i)->print();
							this->listWaiting->removeAt(i);
						}else{i++;}
					}
			}

		}
		void LIGHT(int num)
		{
			//num = 0 thi in ra cac khach trong hang cho theo thu tu
			//num duong thi in theo chieu kdh voi vi khach vua vao ban num am thi lam nguoc theo kdh
			if( num == 0) {this->listWaiting->toString();}
			else if(num < 0){this->listEating->toStringNagitive();}
			else this->listEating->toStringPositive();
		}

		public:
			class SinglyList{
			public:
				customer* head;
				customer* tail;
				int count;
			public:
				SinglyList(): head(nullptr), tail(nullptr), count(0){}
				~SinglyList(){
					this->clear();
				}
				void    add(string name, int energy);
				void    add(int index, string name, int energy);
				int     size();
				bool    empty();
				string  get(int index);
				customer* getNodeByIndex(int index);
				void    shellSort(int n, int& swap);
				void    inssort2(SinglyList* listHead, int n, int incr, int& swap);
				bool    prior(int a, int b);
				void    my_swap(SinglyList* listHead, int i, int j);			
				void    set(int index,string e, int energy);
				int     indexOf(string item);
				bool    contains(string item);
				void    clear();
				string  removeAt(int index);
				bool    removeItem(string item);
				int		findMaxRES(int energy);
				int 	sumNagitive();
				int 	sumPositive();
				void    toString(){
						customer* temp = this->head;
						for (int i = 0; i < this->count; i++)
						{
							temp->print();
							temp = temp->next;
						}
    			}
			};
			class DCLL
			{
			public:
				/* data */
				customer* head;
				int count;
			public:
				DCLL(): head(nullptr), count(0){}
				~DCLL(){
					this->clear();
				}
				void    add(string name, int energy);
				void    add(int index, string name, int energy);
				int     size();
				bool    empty();
				string	get(int index);
				int     getEnergy(int index);
				void    set(int index,string e, int energy);
				int     indexOf(string item);
				bool    contains(string item);
				customer*   searchNodeByName(string item);
				customer* getNodeByIndex(int index);
				void    clear();
				string  removeAt(int index);
				bool    removeItem(string item);
				int 	findMaxRES(int energy);
				//void    shellSort();
				//void    setNodeValueAtIndex(int index, int value);
				void    my_swap(DCLL* listHead, int i, int j);
				void    toStringPositive();
				void    toStringNagitive();
				int 	sumNagitive();
				int 	sumPositive();
				Restaurant::customer*	findMinEnergy();
			};			
};
//Implement singly linked list
Restaurant::customer* imp_res::SinglyList::getNodeByIndex(int index){
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
void imp_res::SinglyList::shellSort(int n, int& swap) {
    for (int i=n/2; i>1; i/=2){      // For each increment
        for (int j=0; j<i; j++){       // Sort each sublist
            SinglyList* temp = new SinglyList();
            temp->head = this->getNodeByIndex(j);
            temp->count = n;
            inssort2(temp, n-j, i, swap);
        }
    }
  inssort2(this, n, 1, swap);     
}
void imp_res::SinglyList::inssort2(SinglyList* listHead, int n, int incr, int& swap) {
    for (int i = incr; i < n; i += incr){
        for (int j = i; (j >= incr) && (prior(abs(listHead->getNodeByIndex(j)->energy), abs(listHead->getNodeByIndex(j-incr)->energy))); j -= incr){
            my_swap(listHead, j, j - incr);
            swap++;
        }
    }
}
void imp_res::SinglyList::my_swap(SinglyList* listHead, int i, int j){
	int temp1 = listHead->getNodeByIndex(i)->energy;
	string temp2 = listHead->getNodeByIndex(i)->name;
	listHead->getNodeByIndex(i)->energy = listHead->getNodeByIndex(j)->energy;
	listHead->getNodeByIndex(i)->name = listHead->getNodeByIndex(j)->name;
	listHead->getNodeByIndex(j)->energy = temp1;
	listHead->getNodeByIndex(j)->name = temp2;
}
bool imp_res::SinglyList::prior(int a, int b){
	return a > b;
}

void imp_res::SinglyList::add(string name, int energy)
{
	if(this->count == 0){
        customer* newNode = new customer(name, energy, nullptr, nullptr);
        this->head = this->tail = newNode;
    }else{
        customer* newNode = new customer(name, energy, nullptr, nullptr);
        this->tail->next = newNode;
        this->tail = newNode;
    }
    this->count++;
}

void imp_res::SinglyList::add(int index, string name, int energy)
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
    prev->next = tmp;
    count ++;
}

int imp_res::SinglyList::size()
{
    return this->count;
}

bool imp_res::SinglyList::empty()
{
	if (this->count == 0)
		{
			return true;
		}
		
	return false;
}

string imp_res::SinglyList::get(int index)
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

void imp_res::SinglyList::set(int index, string e, int energy)
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

int imp_res::SinglyList::indexOf(string item)
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

bool imp_res::SinglyList::contains(string item)
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

void imp_res::SinglyList::clear()
{
	customer  *iter = this->head, *temp;
    while(iter != nullptr){
        temp = iter;
        iter = iter->next;
        delete temp;
        count--;
    }
    this->tail = nullptr;
    this->head = nullptr;
    return ;
}

string imp_res::SinglyList::removeAt(int index)
{
    if (index < 0 || index >= this->count)
        throw std::out_of_range("out of range");
    if ( count == 1) {
        customer* tmp = this->head;
        this->head =  this->tail = NULL;
        string value = tmp->name;
        delete tmp;
        count--;
        return value;
    }
    if (index == 0){
        customer* tmp = head;
        string value = tmp->name;
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
    if( index == count-1) this->tail = prev;
    delete tmp;
    count--;
    return value;
}

bool imp_res::SinglyList::removeItem(string item)
{
    int x = indexOf(item);
    if(x != -1){
        removeAt(x);
        return true;
    }

    return false;
}
int imp_res::SinglyList::findMaxRES(int energy){
//tra ve gia tri maxRES
	int max=0;
	customer* temp = head;
	for (int i = 0; i < this->count; i++)
	{
		int res = abs(energy - temp->energy);
		if (res > max) max = res;
		temp = temp->next;
	}
	return max;
}
int	imp_res::SinglyList::sumPositive(){
		customer* temp = this->head;
		int sum = 0;
		for (int i = 0; i < this->count; i++)
		{
			if(temp->energy > 0) sum += temp->energy;
			temp = temp->next;
		}
		return sum;
}
int    imp_res::SinglyList::sumNagitive(){
		customer* temp = this->head;
		int sum = 0;
		for (int i = 0; i < this->count; i++)
		{
			if(temp->energy < 0) sum += temp->energy;
			temp = temp->next;
		}
		return sum;
}

//Implement circular doubly linked list
void imp_res::DCLL::add(string name, int energy)
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
void imp_res::DCLL::add(int index, string name, int energy)
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
int imp_res::DCLL::size()
{
    return this->count;
}

bool imp_res::DCLL::empty()
{
	if (this->count == 0)
		{
			return true;
		}
		
	return false;
}
string imp_res::DCLL::get(int index)
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
int imp_res::DCLL::getEnergy(int index)
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
void imp_res::DCLL::set(int index, string e, int energy)
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
int imp_res::DCLL::indexOf(string item)
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
bool imp_res::DCLL::contains(string item)
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
Restaurant::customer* imp_res::DCLL::searchNodeByName(string item)
{
    customer* temp = this->head;
    for (int i = 0; i < this->count; i++)
    {   if (temp->name == item)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}
void imp_res::DCLL::clear()
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
string imp_res::DCLL::removeAt(int index)
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
bool imp_res::DCLL::removeItem(string item)
{
    int x = indexOf(item);
    if(x != -1){
        removeAt(x);
        return true;
    }

    return false;
}

int imp_res::DCLL::findMaxRES(int energy){
	//tra ve gia tri maxRES
	int max=0;
	customer* temp = head;
	for (int i = 0; i < this->count; i++)
	{
		int res = abs(energy - temp->energy);
		if (res > max) max = res;
		temp = temp->next;
	}
	return max;
}
void imp_res::DCLL::my_swap(DCLL* listHead, int i, int j){
	int temp1 = listHead->getNodeByIndex(i)->energy;
	string temp2 = listHead->getNodeByIndex(i)->name;
	listHead->getNodeByIndex(i)->energy = listHead->getNodeByIndex(j)->energy;
	listHead->getNodeByIndex(i)->name = listHead->getNodeByIndex(j)->name;
	listHead->getNodeByIndex(j)->energy = temp1;
	listHead->getNodeByIndex(j)->name = temp2;
};
Restaurant::customer* imp_res::DCLL::getNodeByIndex(int index){
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
void	imp_res::DCLL::toStringPositive(){
		customer* temp = this->head;
		for (int i = 0; i < this->count; i++)
		{
			temp->print();
			temp = temp->next;
		}
}
void    imp_res::DCLL::toStringNagitive(){
		customer* temp = this->head;
		for (int i = 0; i < this->count; i++)
		{
			temp->print();
			temp = temp->prev;
		}
}
int	imp_res::DCLL::sumPositive(){
		customer* temp = this->head;
		int sum = 0;
		for (int i = 0; i < this->count; i++)
		{
			if(temp->energy > 0) sum += temp->energy;
			temp = temp->next;
		}
		return sum;
}
int    imp_res::DCLL::sumNagitive(){
		customer* temp = this->head;
		int sum = 0;
		for (int i = 0; i < this->count; i++)
		{
			if(temp->energy < 0) sum += temp->energy;
			temp = temp->next;
		}
		return sum;
}
Restaurant::customer*	imp_res::DCLL::findMinEnergy(){
	int min = 2147483647;
	customer* temp = this->head;
	customer* temp2;
	for (int i = 0; i < this->count; i++)
	{
		if(temp->energy < min) 
		{
			min = temp->energy;
			temp2 = temp ;
			}
		temp = temp->next;
	}
	return temp2;
};