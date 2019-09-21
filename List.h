#ifndef LIST
#define LIST



class List {
private:

	struct Node {
		int data;
		Node * next;
	};
  

	Node * head = NULL;
	Node * tail = NULL;
public:
	void makeEmpty()
	{
		head = NULL;
	}

	bool IsEmpty()
	{
		if (head == NULL) return true;
		else return false;
	}

	void Add(int data)
	{
		Node * temp = new Node();
		temp->data = data;
		temp->next = NULL;
		if (head == NULL)
		{
			head = temp;
			tail = temp;
			temp = NULL;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
	}
	int Remove(int removeData)
	{
		Node * current = head;
		Node * previous = NULL;
		Node * temp = head;
		while (temp)
		{
			if (temp->data == removeData)
			{
				while (current->data != removeData)
				{
					if (current->next == NULL)
					{
						return 0;
					}
					else
					{
						previous = current;
						current = current->next;
					}
				}

				if (current == head)
				{
					head = head->next;
				}
				else
				{
					previous->next = current->next;
				}
			}
			temp = temp->next;
		}
	}
	void search(int val)
	{
		bool flag = false;
		Node * temp = head;
		while (temp)
		{
			if (temp->data == val)
			{
				flag = true;
				Serial.print(val);Serial.print(" is founded");
			}
			temp = temp->next;
		}
		if (!flag) { Serial.print(val);Serial.println(" is not founded");}
	}
	void print()
	{
		Node * temp = head;
		Serial.println("\nList Is: ");
		if (head == NULL) {Serial.println("Empty"); }
		while (temp != NULL)
		{
			Serial.println(temp->data); Serial.println(" ");
			temp = temp->next;
		}
		Serial.println("");
	}
 int largestElement()
 {
    Node * temp = head;
    int max = 180;
    while (temp != NULL) {
      if (max < temp->data) {max = temp->data;}
      temp = temp->next;
    }
    return max;
  }
    int smallestElement()
  {
    Node * temp = head;
    int min = 0;
    while (temp != NULL) {
      if (min > temp->data){min = temp->data;}
      temp = temp->next;
    }
    return min;
  }
};

#endif
