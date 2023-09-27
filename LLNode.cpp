

class LLNode
{
public:
    int val;
    LLNode* next;
    LLNode(){
        val = 0;
        next = nullptr;
    }; // Constructor: val = 0, next = nullptr
    LLNode(int val, LLNode* next){
        this->val = val;
        this->next = next;
    }; // Constructor with customized data
    LLNode* reverseLinkedList(LLNode* head);
}

LLNode* LLNode::reverseLinkedList(LLNode *head)
{
    LLNode* prev = nullptr;
    LLNode* current = head;
    LLNode* nextNode = nullptr;

    while (current != nullptr) {
        nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }

    return prev;
}
LLNode* addLinkedList(LLNode* l0, LLNode* l1) {
// STUDENT ANSWER
    LLNode* result = nullptr;
    LLNode* current = nullptr;
    int carry = 0;
    while (l0 != nullptr || l1 != nullptr || carry > 0) {
    int sum = carry;

    if (l0 != nullptr) {
        sum += l0->val;
        l0 = l0->next;
    }
    
    if (l1 != nullptr) {
        sum += l1->val;
        l1 = l1->next;
    }
        carry = sum / 10; // Calculate carry for the next iteration
        int digit = sum % 10; // Calculate the current digit

        if (result == nullptr) {
            result = new LLNode(digit, nullptr);
            current = result;
        } else {
            current->next = new LLNode(digit, nullptr);
            current = current->next;
        }
    }

    return result;
}
