#include <fstream>
#include <string>
#include <iostream>
#include "matrix.h"
using namespace std;
#define N 10


void intro();
void help();
int choice();

int dimension(int);
void setSquarematrixNodal(double[N][N], int);
void setSquarematrixMesh(double[N][N], int);

void setColumnmatrix(double[N][N], int, int, int);
void displayresult(double[N][N], int, int);


void outputFile(double[N][N], double[N][N], double[N][N], int, int, int);
bool restart();




int main()
{
	intro();
	do {

		matrix mat;

		//declare all variable
		//purpose: matA=n*n, matB=n*1, matINV=inverse matA.
		double matA[N][N], matB[N][N], matINV[N][N], matANS[N][N];
		int col = 1;//col=column for n*1 matrix

		int ch = choice();
		if (ch == 3)
			continue;

		int n = dimension(ch);//n=squarematrix or row


		//obtain matA
		if (ch == 1)
			setSquarematrixMesh(matA, n);
		else if (ch == 2)
			setSquarematrixNodal(matA, n);

		//obtain matINV(inverse matrix of matA)
		if (mat.INV(matA, matINV, n))
			;
		else {
			cout << "Sorry, data is unacceptable. Calculation cannot be done using the data given.\n\n";
			continue;
		}

		//obtain matB
		setColumnmatrix(matB, n, col, ch);



		//obtain matANS(final answer)
		mat.multiply(matINV, matB, matANS, n, col);


		//display final answer
		displayresult(matANS, n, ch);

		outputFile(matA, matB, matANS, n, col,ch);

	} while (restart());

	char anykey;
	cout << "\npress any key to exit";
	cin >> anykey;

	return 0;
}




//return nodal=2 or mesh=1 or help=3
int choice()
{
	char key;
	int choice;

	cout << "\tHello!\n\n";
	cout << "\tMENU" << endl;
	cout << "...................." << endl;
	cout << " Mesh Analysis (M)" << endl;
	cout << " Nodal Analysis (N)" << endl;
	cout << " Help (H)\n" << endl;

	do
	{
		cout << "Please enter which analysis you prefer to use (M/N/H) : ";
		cin >> key;
	} while (key != 'm' && key != 'M' && key != 'n' && key != 'N' && key != 'h' && key != 'H');

	if (key == 'm' || key == 'M') {
		cout << "Your choice is Mesh Analysis" << endl;
		cout << "........................................\n";
		cout << "Prerequisites:" << endl;
		cout << "1. lable or assign number to meshes.\n";
		cout << "........................................\n";
		choice = 1;
	}
	else if(key=='n'||key=='N') {
		cout << "Your choice is Nodal Analysis\n";
		cout << "........................................\n";
		cout << "Prerequisites:" << endl;
		cout << "1. select a node as reference node in the circuit.\n";
		cout << "2. lable or assign number to remaining non-reference nodes.\n";
		cout << "........................................\n";
		choice = 2;
	}
	else if (key == 'h' || key == 'H') {
		choice = 3;
		help();
	}
	cout << endl;
	return choice;
}

//dimension of square matrix//input dimension is 1-10 only
int dimension(int choice) {

	int n;

	if (choice == 1) {
		cout << "Enter the number of mesh in the circuit=";
	}
	else if (choice == 2) {
		cout << "Enter the number of non-reference node in the circuit=";
	}

	do {
		cin >> n;
		while (!cin) {
			cout << "wrong input, enter number again=";
			cin.clear();
			cin.ignore(123, '\n');
			cin >> n;
		}

		if (n < 1 || n>10)
			cout << "wrong input, maximum number is 10, enter number again=";
	} while (n < 1 || n>10);
	return n;
}


//first square matrix(Nodal)// input branch is 0-10
void setSquarematrixNodal(double a[N][N], int n) {

	//initialise array to avoid repetition
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			a[i][j] = -999;
	}


	int branch;
	double resistor[N]; //resistor list connected to node

	cout << "\nEnter the following:-"<<endl;
	cout << "........................................\n";
	cout << "Reminder:" << endl;
	cout << "The branch is the portion of the circuit between two nodes which has element in it.\n";
	cout << "........................................\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			//to avoid repetition of input
			if (a[i][j] != -999)
				continue;


			if (i == j) {
				cout << "enter number of branch connected to node " << i + 1 << " = " << endl;
				//input validity
				do {
					cin >> branch;
					while (!cin) {
						cout << "wrong input, enter number again" << endl;
						cin.clear();
						cin.ignore(123, '\n');
						cin >> branch;
					}
					if (branch < 0 || branch>10)
						cout << "wrong input, maximum branch is 10, enter number again" << endl;
				} while (branch < 0 || branch>10);

				for (int k = 0; k < branch; k++) {
					cout << "\tenter sum of resistance in branch " << k + 1 << " = ";
					cin >> resistor[k];
					while (!cin) {
						cout << "wrong input, enter number again" << endl;
						cin.clear();
						cin.ignore(123, '\n');
						cin >> resistor[k];
					}
				}

				double  sumConductance = 0;
				for (int k = 0; k < branch; k++) {
					if (resistor[k] == 0)
						continue;

					sumConductance += 1 / resistor[k];
				}

				a[i][j] = sumConductance;

			}

			else {
				cout << "enter number of branch connecting node " << i + 1 << " and " << j + 1 << " directly = " << endl;
				//input validity
				do {
					cin >> branch;
					while (!cin) {
						cout << "wrong input, enter number again" << endl;
						cin.clear();
						cin.ignore(123, '\n');
						cin >> branch;
					}
					if (branch < 0 || branch>10)
						cout << "wrong input, maximum branch is 10, enter number again"<<endl;
				} while (branch < 0 || branch>10);

				for (int k = 0; k < branch; k++) {
					cout << "\tenter sum of resistance in branch " << k + 1 << " = ";
					cin >> resistor[k];
					while (!cin) {
						cout << "wrong input, enter number again" << endl;
						cin.clear();
						cin.ignore(123, '\n');
						cin >> resistor[k];
					}
				}

				double  sumConductance = 0;
				for (int k = 0; k < branch; k++) {
					if (resistor[k] == 0)
						continue;

					sumConductance += 1 / resistor[k];
				}

				a[i][j] = -sumConductance;
				a[j][i] = -sumConductance;


			}
			cout << endl;
		}
	}
	cout << endl;
}

//first square matrix(Mesh)
void setSquarematrixMesh(double a[N][N], int n) {

	//initialise array to avoid repetition
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			a[i][j] = -999;
	}

	cout << "\nEnter the following:-"<<endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			//to avoid repetition of input
			if (a[i][j] != -999)
				continue;


			if (i == j){
				cout << "enter sum of the resistances in mesh " << i + 1 <<" = ";
				cin >> a[i][j];
				//int input validity test
				while (!cin) {
					cout << "wrong input, enter number again" << endl;
					cin.clear();
					cin.ignore(123, '\n');
					cin >> a[i][j];
				}

			}

			else {
				cout<<"enter sum of the resistances in common with meshes " << i + 1 << " and " << j + 1 << " = ";
				cin >> a[i][j];
				while (!cin) {
					cout << "wrong input, enter number again" << endl;
					cin.clear();
					cin.ignore(123, '\n');
					cin >> a[i][j];
				}
				a[i][j] *= -1;
				a[j][i] = a[i][j];


			}
		}
	}
	cout << endl;
}


//second column matrix
void setColumnmatrix(double b[N][N], int row, int column,int choice) {
	if (choice == 1) {
		cout << "enter the sum taken clockwise of all independent voltage sources in each mesh, \n(with voltage rise treated as positive)" << endl;
	}
	else if (choice == 2) {
		cout << "enter the sum of all independent current sources directly connected to each node, tip: check each branch connected to the node.\n";
		cout << "(with currents entering the node treated as positive)" << endl;
		cout << "(sum = current entering node - current leaving node)" << endl;
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (choice == 1) {
				cout << "\tsum of voltage for mesh " << i + 1 << " = ";
			}
			else if(choice==2){
				cout << "\tsum of current for node " << i + 1 << " = ";
			};

			cin >> b[i][j];
			while (!cin) {
				cout << "wrong input, enter number again" << endl;
				cin.clear();
				cin.ignore(123, '\n');
				cin >> b[i][j];
			}
		}
	}
	cout << endl;
}


//to write output in external file.
void outputFile(double a[N][N], double b[N][N], double c[N][N], int n, int col, int choice)
{
	string fileName;
	string file;
	ofstream outputFile;
	char confirm;

	cout << "Do you want to save the result in external file?(Y-Yes/N-No) : ";
	cin >> confirm;
	if (confirm == 'y' || confirm == 'Y')
	{
		cout << "Enter the preferred file name: ";
		cin >> fileName;
		file = fileName + ".txt";

		outputFile.open(file,ios::app);
		if (!outputFile)
			cout << "File open failure";


		if (outputFile << "This is record of your calculation in matrix form") {
			cout << "The result successfully written in the file.\n";

			if (choice == 1)
				outputFile << " for Mesh Analysis by Inspection\n\n";
			else if (choice == 2)
				outputFile << " for Nodal Analysis by Inspection\n\n";

			outputFile << "First matrix:\n";
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
					outputFile << "  " << a[i][j];
				outputFile << "\n";
			}
			outputFile <<endl<< "Second matrix:\n";
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < col; j++)
					outputFile << "  " << b[i][j];
				outputFile << "\n";
			}
			outputFile <<endl<< "Answer in matrix form:\n";
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < col; j++)
					outputFile << "  " << c[i][j];
				outputFile << "\n";
			}

			outputFile << "\n\n\nThank you ^-^" << endl;

		}
		else {
			cout << "The result CANNOT be written in the file.\n";
		}

		cout << "........................................\n";
		outputFile.close();
	}


}


//for printing result nodal analysis or mesh analysis using cout
void displayresult(double matrix[N][N], int row , int choice) {
	cout << "........................................\n";
	cout << "\tANSWER" << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			if (choice == 1) {
				cout << "Mesh current for mesh " << i + 1 << " in the clockwise direction = " << matrix[i][j] ;
			}
			else if(choice==2) {
				cout << "Voltage at node " << i + 1 << " = " << matrix[i][j] ;
			}
		}
		cout << "\n";
	}
	cout << "........................................\n" << endl;
}

//restart option
bool restart() {
	char key;
	cout << "Do you want to restart? (Y-Yes/N-No) : ";
	cin>>key;
	if (key == 'Y' || key == 'y') {
		cout << "........................................................................................................................\n\n";
		return true;
	}
	else {
		cout << "---( The end. Thank you ^-^ ) ---";
		return false;
	}
 }

void intro() {
	cout << "Introduction:\n";
	cout << "This is a software to calculate voltage(using nodal analysis) or current(using mesh analysis) of a a linear resistive circuit.\n";
	cout << "To use this software, make sure:-\n";
	cout << "........................................\n";
	cout << "Rule: Input whole number or decimal only. Do NOT input fraction.\n";
	cout << "........................................\n";
	cout << "For Nodal Analysis:\n";
	cout << "1. all sources in a circuit are independent current sources.\n";
	cout << "2. maximum number of non-reference node is 10.\n";
	cout << "........................................\n";
	cout << "For Mesh Analysis:\n";
	cout << "1. all sources in a circuit are independent voltage sources.\n";
	cout << "2. maximum number of mesh is 10.\n";
	cout << "........................................................................................................................\n\n";

}

void help() {
	cout << "........................................................................................................................\n";
	cout << "\nHELP\n";
	cout << "........................................\n";
	cout << "Keep in mind that this is valid for circuits with only independent sources and linear resistors.\n";
	cout << "# If you want to find the value of current from a linear resistive circuit with only independent voltage sources, choose mesh analysis.\n";
	cout << "# if you want to find the value of voltage from a linear resistive circuit with only independent current sources, choose nodal analysis.\n";
	cout << "........................................\n";
	cout << "Definition:\n";
	cout << "1. Node : A node is the point of connection between two or more branches.\nIf there is no element between two or more connected adjacent nodes, these nodes can be recombined as a single node.\n";
	cout << "2. Reference node: The reference node,commonly called the ground, is a node assumed to have zero potential( 0 Volt )\n";
	cout << "3. Mesh : Mesh is a loop that does not consists of any other loop inside it.\n";
	cout << "4. Loop: A loop is any closed path in a circuit.\n";
	cout << "5. Element : eg: resistor, voltage source, current source, etc.\nThe elements connected to an electric circuit is generally two terminal element.\n";
	cout << "6. Branch : A branch is the portion of the circuit between two nodes which can deliver or absorb energy.\nA branch represents a single element such as a voltage source or a resistor.\n";
	cout << "7. Linear resistor : A Linear resistor is one whose resistance does not vary with the flow of current through it.\n";
	cout << "8. Linear resistive circuit : A circuit that have linear resistor.\n";
	cout << "9. Conductance : Reciprocal of resistance\n";
	cout << "........................................\n";
	cout << "Summary:\n";
	cout << "Any of the circuit elements, when connected to the circuit, it is definitely connected between two nodes of the circuit.\n";
	cout << "When an element exists between two nodes, the   path from one node to another through this element is called branch of the circuit.\n";
	cout << "........................................\n";
	cout << "How data saved in external file:\n";
	cout << "1. When the preferred name of file is \"abc\", the data is saved in \"abc.txt\" file.\n";
	cout << "2. Data is saved in this format.\n\n";
	cout << "(k=row ; j=column)\n";
	cout << "For Nodal Analysis:\n";
	cout << "First matrix: G\nSecond matrix: i\nAnswer matrix: v\n";
	cout << "G(kk) = Sum of the conductances connected to node k\n";
	cout << "G(kj) = G(jk) = Negative of the sum of the conductances directly connecting nodes k and j, k != j\n";
	cout << "v(k) = Unknown voltage at node k\n";
	cout << "i(k) = Sum of all independent current sources directly connected to node k, with currents entering the node treated as positive\n";
	cout << "\n";
	cout << "For Mesh Analysis:\n";
	cout << "First matrix: R\nSecond matrix: v\nAnswer matrix: i\n";
	cout << "R(kk) = Sum of the resistances in mesh k\n";
	cout << "R(kj) = R(jk) = Negative of the sum of the resistances in common with meshes k and j, k!=j\n";
	cout << "i(k) = Unknown mesh current for mesh k in the clockwise direction\n";
	cout << "v(k) = Sum taken clockwise of all independent voltage sources in mesh k, with voltage rise treated as positive\n";
	cout << "........................................................................................................................\n";

}











