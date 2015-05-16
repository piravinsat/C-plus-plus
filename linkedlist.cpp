#include <iostream>
using namespace std;

struct node_ll {
	int payload;
	node_ll *next; //pointer to next node
};

void head_insert(node_ll **list, int pload);
void tail_insert(node_ll **list, int pload);
void print_ll(node_ll **list);
int head_return(node_ll **list);
int tail_return(node_ll **list);
bool ordered_list(node_ll **list);

int main() {
  node_ll *alist = NULL;	
  cout << "Empty list a to start\n";
  head_insert(&alist, 2);	
  head_insert(&alist, 4);
  head_insert(&alist, 6);
  cout << "List a after head insertion of 2,4,6 is \n";
  print_ll(&alist);
  cout << '\n';

  node_ll *blist = NULL;	
  cout << "Empty list b to start\n";
  tail_insert(&blist, 2);	
  tail_insert(&blist, 4);
  tail_insert(&blist, 6);
  cout << "List b after tail insertion of 2,4,6 is \n";
  print_ll(&blist);
  cout << '\n';

  cout << "The head of the list is... ";		
  cout << head_return(&blist);
  cout << '\n';

  cout << "The tail of the list is... ";	
  cout << tail_return(&blist);
  cout << '\n';

  cout << "Is the list ordered? ";

  if (ordered_list(&blist)) {
	cout << "True";
  }
  else cout << "False";
  cout << '\n';
}

void head_insert(node_ll **list, int pload) {
  node_ll *temp = new node_ll;
  temp->payload = pload;
  temp->next = *list;
  *list = temp;
};

void tail_insert(node_ll **list, int pload) {
  node_ll *temp = new node_ll;
  if (*list == NULL) head_insert(list,pload);
  else {
    //set temp to last node
    for (temp = *list; temp->next; temp = temp->next);
    temp->next = new node_ll;
    temp->next->payload = pload;
    temp->next->next = NULL;
  };
};

void print_ll(node_ll **list) {
	node_ll *temp;
	temp = *list;

	while (temp) {
		cout << temp->payload << '\n';
		temp = temp->next;
	}
};

int head_return(node_ll **list) {
	
	int pload = 0;
	node_ll *temp = *list;
	*list = (*list)->next;

	//Puts the first integer into pload
	pload = temp->payload;
		
	//Deletes it from the list
	delete temp;


	return pload;
};

int tail_return(node_ll **list) {

	int pload = 0;
	node_ll *temp;

	//Puts the last integer into pload
	for (temp=*list; temp -> next; temp = temp->next);
	pload = temp->payload;

	//Deletes it from the list
	delete temp;
	*list = temp;

	return pload;

};

bool ordered_list(node_ll **list) {

	/**node_ll *temp;
	temp = *list;
	while (temp->next) {
		if (temp->payload > temp->next->payload)
			{
			return false;
			}
		else {
			temp = temp->next;
		}
	}		
		return true;	*/

    node_ll *temp = *list;
    while (temp->next) {
        if (temp -> payload < temp->next->payload) {
            temp = temp->next;
        }
        else return false;
    }
    return true;
}
