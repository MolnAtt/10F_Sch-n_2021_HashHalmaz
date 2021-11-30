// 10F_Schőn_2021_HashHalmaz.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Halmaz // most nem generikus típusokkal foglalkozunk! 
{
public:

	vector<vector<int>>* hasitotabla; // ez nem A hasítótábla, hanem a leendőbeli hasíótábla CÍME!!

	// hasitofuggveny bejövő paraméter kell legyen
	// tábla mérete is kell!

	int meret;
	int (*hasitofuggveny)(int); // a hasitofuggveny deklarációja C#-ban Func<string, int> hasitofuggveny

	Halmaz(int m, int (*fuggvenyneve)(int)) // két bemenet, a méret és a hasítófüggvény, amit a user megad
	{
		this->meret = m;
		this->hasitofuggveny = fuggvenyneve;
		// vector<int> v(5, 7); // 5 hosszú vektor csupa 7-esekkel feltöltve
		this->hasitotabla = new vector<vector<int>>(m, vector<int>()); // m hosszú tömb, mindegyik cellájában van egy üres Elemvektor.
		 // a new nem egy vektorbanavektort ad vissza, hanem egy vektorbanavektor CÍMÉT!

	}

	void Add(int ertek)
	{
		vector<int> hely = helye(ertek);
		int i = hely[0];
		int j = hely[1];
		// megnézzük, hogy olyat akar-e hozzáadni a felhasználó, ami már esetleg benne van-e. Ha igen, nem csinálunk semmit, ha nincs még benne, akkor hozzáadjuk.
		if (j == hasitotabla->at(i).size()) // a torlódó lista méreténél kisebb a "j" a helyből
			hasitotabla->at(i).push_back(ertek);
	}

	void diagnosztika()
	{
		cerr << "-------------- meret: " << meret << "-----------------\n";
		for (int i = 0; i < meret; i++)
		{
			cerr << "[" << i << "]: " << to_string(hasitotabla->at(i)) << endl;
		}
		cerr << "--------------------------------------\n";
	}

	bool contains(int ertek)
	{
		vector<int> hely = helye(ertek);
		int i = hely[0];
		int j = hely[1];
		return j < hasitotabla->at(i).size();
	}

private:

	string to_string(vector<int>& vektor)
	{
		string s = "";
		for (int& elem : vektor)
			s += std::to_string(elem)+ "  ";
		return s;
	}

	vector<int> helye(int ertek)
	{
		int i = hasitofuggveny(ertek);
		int j = 0;
		int torlodo_lista_merete = hasitotabla->at(i).size();
		while (j < torlodo_lista_merete && hasitotabla->at(i)[j] != ertek) // addig növelgeti j-t, míg meg nem találja vagy a végére nem ér
			j++;

		return vector<int>{i, j}; // i a sorszam, ez biztos van, j pedig vagy az elem, ha volt benne, vagy a lista mérete, ha nem volt benne
	}




};

int hash_utolso(string telefonszam)
{
	return telefonszam[telefonszam.size() - 1] - 48;
}


int main()
{
    std::cout << "Hello World!\n";

	Halmaz halmaz(10, [](int ez) {return ez % 10; });

	halmaz.Add(5);
	halmaz.diagnosztika();
	halmaz.Add(10);
	halmaz.diagnosztika();
	halmaz.Add(13);
	halmaz.diagnosztika();
	halmaz.Add(43);
	halmaz.diagnosztika();

	cout << halmaz.contains(33) << endl;
	cout << halmaz.contains(43) << endl;
	cout << halmaz.contains(5) << endl;

}
