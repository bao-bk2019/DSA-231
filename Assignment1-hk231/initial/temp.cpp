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
	private:
		customer* waitingHead;
		customer* eatingHead;
		SinglyList* listRemove;
		int waitingCount;
		int eatingCount;
	public:	
		imp_res() : waitingHead(nullptr), eatingHead(nullptr), listRemove(new SinglyList()), waitingCount(0), eatingCount(0) {}

		virtual ~imp_res() {
			//Hiện thực hàm hủy (destructor) cho danh sách
			// while (waitingHead) {
			// 	customer* temp = waitingHead;
			// 	waitingHead = waitingHead->next;
			// 	delete temp;
			// 	// Nếu bạn sử dụng danh sách liên kết vòng, bạn không cần xóa node ở đây
			// }
    	}

		void RED(string name, int energy)
		{
			cout << name << " " << energy << endl;
			//các trường hợp không tiếp nhận khách nữa: energy = 0, eatingcount + waitingcount = 2*maxsize, check name trong cac 2 list
			if(energy == 0 || (this->eatingCount+this->waitingCount) >= 2*MAXSIZE|| checkName(name))
				return ;
			
			customer *cus = new customer (name, energy, nullptr, nullptr);
			//check MAXSIZE/2 sau do moi dung chien thuat lap vi tri
			if(this->eatingCount < (MAXSIZE/2)){
				//option 1
				//khi vua mo cua hang thi khach co the ngoi bat ky dau

				//energy lon hon hoac bang se o vi tri cung chieu kdh, khong thi nguoc lai
				if(!this->eatingHead){
					this->eatingHead = cus;
					this->eatingHead->next = this->eatingHead;
					this->eatingHead->prev = this->eatingHead;
				}else{
					if (cus->energy >= this->eatingHead->energy)
					{
						cus->next = eatingHead->next;
						eatingHead->next->prev = cus;
						cus->prev = eatingHead;
						eatingHead->next = cus;
						eatingHead = cus;
					}else{
						customer* last = eatingHead->prev;
						last->next = cus;
						cus->prev = last;
						cus->next = eatingHead;
						eatingHead->prev = cus;
						eatingHead = cus;
					}
					
				}
				this->eatingCount++;
				this->listRemove->add(0, name, energy);

			}else if(this->eatingCount < MAXSIZE){
			
			
			//option 2: Res cang lon cang tot va la vi tri dau tien theo chieu kdh sau do bo tri tuyet doi va chon lai
			//theo thu tu am thi nguoc chieu kdh va nguoc lai
			//RES= |Khach moi - Khach cu|

			//hang cho co so luong bang MAXSIZE va se ko nhan them khi da du hang cho
			int max = findMaxRES(energy);
			while (abs((cus->energy - this->eatingHead->energy)) != max)
			{
				eatingHead = eatingHead->next;
			}
			if ((energy - this->eatingHead->energy) > 0)
			{
				cus->next = eatingHead->next;
				eatingHead->next->prev = cus;
				cus->prev = eatingHead;
				eatingHead->next = cus;
				eatingHead = cus;
			}else{
				customer* last = eatingHead->prev;
				last->next = cus;
				cus->prev = last;
				cus->next = eatingHead;
				eatingHead->prev = cus;
				eatingHead = cus;
			}
			this->eatingCount++;
			this->listRemove->add(0, name, energy);
			} else{
				if(!this->waitingHead){
					this->waitingHead = cus;
					this->waitingHead->next = this->waitingHead;
					this->waitingHead->prev = this->waitingHead;
				}else{
				customer* last = waitingHead->prev;
				last->next = cus;
				cus->prev = last;
				cus->next = waitingHead;
				waitingHead->prev = cus;
				waitingHead = cus;
				}
				this->waitingCount++;
			}
			

		
		}
		void BLUE(int num)
		{
			cout << "blue "<< num << endl;
			//kiem tra neu co khach dang cho se tien hanh thu don khach trong nha hang neu dung qua lau
			//num > khach || num > maxsize se duoi het khach
			
			if(num > this->eatingCount || num > MAXSIZE){
				while (eatingHead) {
				customer* temp = eatingHead;
				eatingHead = eatingHead->next;
				delete temp;
				this->listRemove->removeItem(temp->name);
				this->eatingCount--;
				// Nếu bạn sử dụng danh sách liên kết vòng, bạn không cần xóa node ở đây
        		}
			}
			for (int i = 0; i < num; i++) //xoa n khach
			{	
				customer* delCustomer = findByName(this->listRemove->get(this->listRemove->size()-1));
				if(this->eatingCount == 1){
					this->eatingHead = nullptr;
					deleteCus(delCustomer);
					this->eatingCount--;
				}else{
					if(delCustomer->energy > 0){
						this->eatingHead = delCustomer->next;
					} else this->eatingHead = delCustomer->prev;
					deleteCus(delCustomer);
					this->eatingCount--;
				}
				/* code */
				// customer* temp = eatingHead;
				// if(this->eatingCount == 1){
				// 	this->eatingHead = nullptr;
				// 	this->eatingCount = 0;
				// 	deleteCus(temp);
				// }else{
				// eatingHead = eatingHead->next;
				// deleteCus(temp);
				// this->eatingCount--;
				// }
			}
			if(this->waitingCount == 0) return ;
			for (int i = 0; i < this->waitingCount; i++)
			{
				/* code */
				if(this->eatingCount == MAXSIZE){
					break;
				}
				//enqueue
				customer* getCus = this->waitingHead->prev;
				this->waitingHead->prev = getCus->prev;
				getCus->prev->next = waitingHead;
				this->RED(getCus->name, getCus->energy);
				delete getCus;
				this->waitingCount--;
				
			}
			
			//mac dinh num lon hon 0 va chon khach trong hang cho tien hanh sau khi don dep xong. FIFO

		}
		void PURPLE()
		{
			cout << "purple"<< endl;
			// sap xep lai hang cho theo gia tri tuyet doi energy theo giai thuat Shell Sort

			//lay so lan chuyen doi cua Shell Sort sau do tien hanh Blue voi tham so num = N mod MAXSIZE

		}
		void REVERSAL()
		{
			cout << "reversal" << endl;
			// hoa doi cac vi khach cung tinh chat voi nhau nguoc chieu kdh

		}
		void UNLIMITED_VOID()
		{
			cout << "unlimited_void" << endl;
			// tim theo chieu kdh day con (>=4)
			// ko tim duoc thi ko can lam gi ca
		}
		void DOMAIN_EXPANSION()
		{
			cout << "domain_expansion" << endl;
			// duoi khach dua vao energy va sao do lap day lai neu can
			// in ra danh sach thu tu cac vi khach bi duoi theo thu tu thoi gian

		}
		void LIGHT(int num)
		{
			cout << "light " << num << endl;
			//num = 0 thi in ra cac khach trong hang cho theo thu tu
			//num duong thi in theo chieu kdh voi vi khach vua vao ban num am thi lam nguoc theo kdh
		}
		bool checkName(string name){
			customer* temp = eatingHead;
			for (int i = 0; i < this->eatingCount; i++)
			{
				if (temp->name == name) return true;
			}
			customer* temp2 = waitingHead;
			for (int i = 0; i < this->waitingCount; i++)
			{
				if (temp2->name == name)return true;
				temp2 = temp2->next;
			}
			return false;
		};
		int findMaxRES(int energy){
			//tra ve gia tri maxRES
			int max=0;
			customer* temp = eatingHead;
			for (int i = 0; i < this->eatingCount; i++)
			{
				int res = abs(energy - temp->energy);
				if (res > max) max = res;
			}
			return max;
		}
		
		void deleteCus(customer *Node){
			Node->prev->next = Node->next;
			Node->next->prev = Node->prev;
			this->listRemove->removeItem(Node->name);
			delete Node;
			
		}
		customer* findByName(string name){
			customer* temp = this->eatingHead;
			for (int i = 0; i < this->eatingCount; i++)
			{
				if(temp->name == name) return temp;
				temp = temp->next;
			}
			return nullptr;
		}
		public:
			class SinglyList{
			public:
				customer* head;
				customer* tail;
				int count;
			public:
				SinglyList(): head(nullptr), tail(nullptr), count(0){}
				~SinglyList(){}
				void    add(string name, int energy);
				void    add(int index, string name, int energy);
				int     size();
				bool    empty();
				string       get(int index);
				void    set(int index,string e, int energy);
				int     indexOf(string item);
				bool    contains(string item);
				void    clear();
				string       removeAt(int index);
				bool    removeItem(string item);
			};
			
		
};

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
