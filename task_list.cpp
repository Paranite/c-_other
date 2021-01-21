#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <conio.h>

using namespace std;

struct TaskList {
	string TaskName;
	string Subject;
	string Term;
	string Description;

	TaskList *next;
};

class queueLinkList {
private:
	TaskList* first;
	TaskList* last;
	TaskList* curr;
public:
	queueLinkList() {  //konstruktorius
		first = NULL;
		last = NULL;
		curr = NULL;
	}

	void enqueue(TaskList* task, int poz) { //prideti elementa

		TaskList* temp;
		
		if (poz > getTaskCount() + 1 || poz < 1) {
			cout << "Blogai nurodyta pozicija" << endl;
		}
		else if (isTaskInList(task->TaskName)) {
			cout << "Tokia uzduotis jau yra sarase" << endl;
		}
		else if (poz == 1) {
			if (first == NULL) {
				task->next = NULL;
				first = last = curr = task;
			}
			else {
				temp = first;
				first = task;
				first->next = temp;
			}	
		}
		else if (poz == getTaskCount() + 1) {
			task->next = NULL;
			last->next = task;
			last = task;
		}
		else {
			TaskList* currentT = first->next;
			TaskList* lastT = first;
			int cpos = 2;
			while (cpos <= poz) {
				if (cpos == poz) {
					lastT->next = task;
					task->next = currentT;
				}
				lastT = currentT;
				currentT = currentT->next;
				cpos++;
			}
		}
	}

	bool isTaskInList(string name) {
		TaskList* temp = first;
		while (temp != NULL) {
			if (temp->TaskName == name) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	void dequeue(int poz) { //istrinti elementa is pradzios
		TaskList* temp;

		if (poz > getTaskCount() || poz < 1) {
			cout << "Blogai nurodyta pozicija" << endl;
		}
		else if (first == NULL) {
			cout << "Sarasas tuscias - nera ka trinti" << endl;
		}
		else if (poz == 1) {
			temp = first;
			first = first->next;
			if (first->next == NULL) {
				last = curr = first;
			}
			delete(temp);
		}
		else {
			int cpos = 2;
			TaskList* currentT = first->next;
			TaskList* lastT = first;
			while (cpos <= poz) {
				if (cpos == poz) {
					lastT->next = currentT->next;
					delete(currentT);
				}
				lastT = currentT;
				currentT = currentT->next;
				cpos++;
			}

		}
	}

	bool clear() {
		if (first == NULL)
			return true;
			// Store previous front and move front one node ahead

		TaskList* currentT = first;
		TaskList* nextT;
		while (currentT != NULL) {
			nextT = currentT->next;
			delete(currentT);
			currentT = nextT;
		}
		return true;
	}

	bool isEmpty() {
		if (first == NULL)
			return true;
		else
			return false;
	}

	int getTaskCount() {
		TaskList* temp = first;
		int count = 0;
		while (temp != NULL) {
			temp = temp->next;
			count++;
		}
		return count;
	}

	void display() {
		TaskList* temp = first;

		while (temp != NULL) {
			cout << temp->TaskName << "\t" << temp->Subject << "\t" << temp->Term << "\t" << temp->Description << "\t"<<endl;
			temp = temp->next;
		}
	}

	void changeTaskInfo(string taskName, string subject, string term, string description) {
		TaskList* temp = first;
		while (temp != NULL) {
			if (temp->TaskName == taskName) {
				temp->TaskName = taskName;
				temp->Subject = subject;
				temp->Term = term;
				temp->Description = description;
				return;
			}
			temp = first->next;
		}
	}

	void findTasksBySubject(string subject) {
		TaskList* temp = first;
		while (temp != NULL) {
			if (temp->Subject == subject) {
				cout << temp->TaskName << "\t" << temp->Subject << "\t" << temp->Term << "\t" << temp->Description << "\t"<<endl;
			}
			temp = temp->next;
		}

	}
	
	void findTasksByTerm(string term) {
		TaskList* temp = first;
		while (temp != NULL) {
			if (temp->Term == term) {
				cout << temp->TaskName << "\t" << temp->Subject << "\t" << temp->Term << "\t" << temp->Description << "\t" << endl;
			}
			temp = temp->next;
		}
	}

	TaskList* getFirst() {
		return first;
	}

};

void readFromFile(queueLinkList &q) {
	int uzd_sk;
	ifstream df;
	df.open("Uzduociu_Tvarkykle.txt");
	if (df.fail()) {
		cerr << "Ivyko klaida nuskaitant faila" << endl;
	}
	else if (df.peek() == EOF) {
		cout << "Uzduociu nera" << endl;
	}
	else {
		df >> uzd_sk;
		for (int i = 1; i <= uzd_sk; i++) {
			TaskList* temp = new TaskList;
			df >> temp->TaskName >> temp->Subject >> temp->Term >> temp->Description;
			q.enqueue(temp, i);
		}
	}
	df.close();
}

void writeToFile(queueLinkList q) {
	ofstream df;
	df.open("Uzduociu_Tvarkykle.txt");
	TaskList* temp = q.getFirst();
	if (temp == NULL) {
		cout << "Uzduociu sarasas tuscias" << endl;
	}
	else {
		df << q.getTaskCount()<<endl;
		while (temp != NULL) {
			df << temp->TaskName << endl;
			df << temp->Subject << endl;
			df << temp->Term << endl;
			df << temp->Description << endl;
			temp = temp->next;
		}
	}
	df.close();
}


/*
void Wait4response() {
	bool goBack = false;
	unsigned int choice;
	while (!goBack) {
		cout << "" << endl;
		cout << "\nJei norite grizti i meniu, spauskite bet kuri klavisa\n";
		choice = _getch();
		goBack = true;

	}
}
*/


TaskList* askTaskInfo(queueLinkList q){
	TaskList* temp = new TaskList;

	cout << "Iveskite uzduoties pavadinima" << endl;
	cin >> temp->TaskName;
	while (q.isTaskInList(temp->TaskName)) {
		cout << "Toks uzduoties pavadinimas jau yra. Iveskite kita pavadinima" << endl;
		cin >> temp->TaskName;
	}
	cout << "Iveskite dalyka" << endl;
	cin >> temp->Subject;
	cout << "Iveskite termina" << endl;
	cin >> temp->Term;
	cout << "Iveskite uzduoties aprasyma" << endl;
	cin >> temp->Description;

	return temp;
}

int main() {
	char selection;
	queueLinkList q;
	string filename = "Task_List.csv";


	PRADZIA:
	do {
		system("cls");
		cout << "  Uzduociu tvarkykle\n";
		cout << "  ========================================================================\n";

		cout << "  1. Nuskaityti uzduotis is dokumento ir irasyti i uzduociu sarasa \n";
		cout << "  2. Irasyti nauja uzduoti i sarasa\n";
		cout << "  3. Surasti uzduoti pagal termina\n";
		cout << "  4. Surasti uzduoti pagal dalyka\n";
		cout << "  5. Pakeisti uzduoties informacija\n";
		cout << "  6. Atspausdinti uzduotis i ekrana\n";
		cout << "  7.Istrinti uzduoti\n";

		cout << "\n";
		cout << "  x.  Iseiti\n";
		cout << "  ========================================================================\n";
		cout << "  Iveskite pasirinkima: ";

		cin >> selection;
		cout << endl;

		//system("cls");
		switch (selection) {
			case '1':
			{
				//loadProcess(filename, q);
				//Wait4response();
				readFromFile(q);
				system("pause");
				break;
			}

			case '2':
			{
				char insertionSelection;
				TaskList* temp;
				cout << "  1. Irasyti nauja uzduoti i saraso pradzia\n";
				cout << "  2. Irasyti nauja uzduoti i saraso pabaiga\n";
				cout << "  3. Irasyti nauja uzduoti i norima pozicija\n";
				cout << "  4. Grizti atgal\n";
				cin >> insertionSelection;
				switch (insertionSelection) {
				case '1':
				{
					temp = askTaskInfo(q);
					q.enqueue(temp, 1);
					break;
				}
				case '2':
				{
					temp = askTaskInfo(q);
					q.enqueue(temp, q.getTaskCount() + 1);
					break;
				}
				case '3':
				{
					int uzdPoz;
					cout << "Iveskite kur norite iterpti uzduoti" << endl;
					cin >> uzdPoz;
					temp = askTaskInfo(q);
					q.enqueue(temp, uzdPoz);
					break;
				}
				case '4':
				{
					goto PRADZIA;
					break;
				}
				}
				cout << "Uzduotis sukurta" << endl;
				system("pause");
				break;
			}

			case '3':
			{
				string term;
				cout << "Iveskite termina, pagal kuri norite rasti uzduotis" << endl;
				cin >> term;
				q.findTasksByTerm(term);
				system("pause");
				break;
			}
			case '4':
			{
				string dal;
				cout << "Iveskite dalyka, pagal kuri norite rasti uzduotis" << endl;
				cin >> dal;
				q.findTasksBySubject(dal);
				system("pause");
				break;
			}
			case '5':
			{
				string upav;
				cout << "Ivesktite uzduoties, kuria norite pakeisti, pavadinima" << endl;
				cin >> upav;
				if (!q.isTaskInList(upav)) {
					cout << "Tokios uzduoties nera" << endl;
					system("pause");
				}
				else {
					string npav, ndal, nterm, napr;
					cout << "Iveskite nauja uzduoties pavadinima" << endl;
					cin >> npav;
					while (q.isTaskInList(npav) && upav != npav) {
						cout << "Tokia uzduotis jau yra. Parinkite kita pavadinima" << endl;
						cin >> npav;
					}
					cout << "Iveskite dalyka" << endl;
					cin >> ndal;
					cout << "Iveskite termina" << endl;
					cin >> nterm;
					cout << "Iveskite uzduoties aprasyma" << endl;
					cin >> napr;
					q.changeTaskInfo(npav, ndal, nterm, napr);
					cout << "Uzduotis pakeista" << endl;
					system("pause");
				}

				break;
			}
			case '6':
			{
				q.display();
				system("pause");
				break;
			}
			case '7':
			{
				int poz;
				cout << "Iveskite uzduoties, kuria norite istrinti, pozicija" << endl;
				cin >> poz;
				q.dequeue(poz);
				cout << "Uzduotis istrinta" << endl;
				system("pause");
				break;
			}
			case 'x':
			{
				break;
			}
			default: cout << selection << "is not a valid menu item.\n";

			cout << endl;
		}

	} while (selection != 'x');

	return 0;


	//q.displayFirst();
	//cout<<"\n--------------------------------------------------\n";

	//q.displayLast();
	//cout<<"\n--------------------------------------------------\n";

	//q.display();

	return 0;
}