// Author: Jacob Christiansen
// Class: CSCI 2270
// Course Instructor: Rhonda Hoenigman
// Recitation: 105
//
// Assignment 3

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct city{
	string cityName;
	string message;
	city *next;

	city(){
	// default constructor
	}
	city(string initName, city *initNext, string initMessage){
		cityName = initName;
		next = initNext;
		message = initMessage;
	}
};

// city *addCity(city *head, city *previous, string cityName){
// 	city *cNode = head; //current node
// 	if(cNode->next == NULL){
// 		city *nwNode = new city(cityName, NULL, "");
// 		return nwNode;
// 	}else if(previous == NULL){
// 		city *nwNode = new city(cityName, cNode, "");
// 		return nwNode;
// 	}

// 	while(cNode->next != NULL){ //pass through LL until tail is found
// 		if(previous->cityName.compare(cNode->cityName) == 0){
// 			city *nxNode = cNode->next;
// 			city *nwNode = new city(cityName, nxNode, "");
// 			cNode->next = nwNode;
// 		}
// 		cNode = cNode->next;
// 	}

// 	if(cNode->cityName.compare(previous->cityName) == 0){
// 		city *nwNode = new city(cityName, NULL, "");
// 		cNode->next = nwNode;
// 	}
// 	return head;
// }
city *addCity(city *head, city *prev, string newName){
    city *n = new city(newName, NULL, "");
    if(head == NULL){
        return n;
    }
    if(prev == NULL){
        n->next = head;
        return n;
    }
    if(prev->next == NULL){
        prev->next = n;
        return head;
    }else{
        city *next = prev->next;
        prev->next = n;
        n->next = next;
        return head;
    }
}
/*Add	a	new	city	to	the	linked	list	between	the	city	*previous	and	the	city	that	
follows	it	in	the	network.	The	name	of	the	new	city	is	in	the	argument	cityName.	
Return	the	head	of	the	linked	list.	
*/

city *buildNetwork(){
	string origPath[] = {"Los Angeles", "Phoenix", "Denver", "Dallas", "St. Louis", "Chicago", "Atlanta", "Washington, D.C.", "New York", "Boston"};
//array of the city names ^
	city *rnHead = new city(origPath[0], NULL, "");
	city *lCity = rnHead; //last city and return head
	for(int i=1; i<10; i++){
	    city* cCity = new city(origPath[i], NULL, "");
		lCity->next = cCity;
		lCity = cCity;
	}
	return rnHead;
}
/*Create	a	linked	list	from	the	list	of	cities	provided	above	and	return	the	head	of	
the	list.
*/



void transmitMsg(city *head){
	ifstream fr;
	fr.open("messageIn.txt");
	city *fCity = head; //first city is the head of the LL

	if(head == NULL){
		cout << "Empty list" << endl;
	}else if(fr.is_open()){
		string line = "";
		while(getline(fr, line)){
			stringstream ss(line);
			string word = "";
			while(getline(ss, word, ' ')){
				city *cCity = fCity; //current city and first city
				cCity->message = word;
				while(cCity->next != NULL){
					cout << cCity->cityName << " received " << cCity->message << endl;
					city *pCity = cCity; //previous city and current city
					cCity = pCity->next; 
					cCity->message = pCity->message;
					pCity->message = "";
				}
				cout << cCity->cityName << " received " << cCity->message << endl;
			}
		}
	}
	fr.close();
}
/*Open	the	file	messageLn.txt	and	transmit	the	message	between	all	cities	in	the	
network	word	by	word.	A	word	needs	to	be	received	at	the	end	of	the	network	
before	sending	the	next	word.	Only	one	city	can	hold	the	message	at	a	time;	as	soon	
as	it	is	passed	to	the	next	city,	it	needs	to	be	deleted	from	the	sender	city.	
*/
void printPath(city	*head){
	city *cCity = head;
	cout << "===CURRENT PATH===" << endl;
	while(cCity->next != NULL){
		cout << cCity->cityName << " -> ";
		cCity = cCity->next;
	}
	cout << cCity->cityName << " -> " << " NULL" << endl;
	cout << "==================" << endl;
}
/*Go	through	each	city	in	the	network	starting	at	the	head	and	print	the	name	of	the	
city.*/


int main(){
	city *head;
  	int choice = 0;

  	while(choice != 5){
	    cout << "======Main Menu======\n1. Build Network\n2. Print Network Path\n3. Transmit Message Coast-To-Coast\n4. Add City\n5. Quit" << endl;
	    cin >> choice;
    	switch (choice){
		    case 1:
		    	head = buildNetwork();
		      	break;
		    case 2:
		      	printPath(head);
		      	break;
		    case 3:
		     	if(head == NULL){
		     		cout << "Empty list" << endl;
		     	}else{
		     		transmitMsg(head);
		     	}
		     	break;
		    case 4:
		     	cout << "Enter a City name:" << endl;
		     	string newCityName;
		     	cin >>  newCityName;
		     	cout << "Enter a previous City name:" << endl;
		     	string prevName;
		     	cin >>  prevName;
		    	city *curr = head;
				while(curr){
					if(curr -> cityName == prevName){
			  			addCity(head,curr,newCityName);
			  			break;
			 		}
					curr = curr -> next;
		      	}
		    	addCity(head,NULL,newCityName);
		      	break;
			}
		}
	cout << "Goodbye!" << endl;
}