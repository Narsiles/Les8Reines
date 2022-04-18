#include <iostream>
#include <vector>

//Permet de ne pas utiliser std :: devant cin et cout
using namespace std;

//fonction permettant de cr�er un tableau et de l'afficher quand il est appel� dans le int main()
void showTab(vector<vector<bool>>& grid) {
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			cout << grid[i][j];//Permet d'afficher chaque ligne du tableau
			cout << " "; //Permet de mettre un espace entre chaque caract�re pour faire un tableau bien carr�
		}
		cout <<endl;//Permet d'aller a la ligne a chaque tour de boucle 
	}
}


//On check les cases comme au puissance 4 pour voir si une reine peut oui ou non �tre acceuilli sur la case
bool checkCase(vector<vector<int>> tempNbQueen, int x, int y)
{
	if (tempNbQueen.size() == 0) {
		return true;
	}
	for (int i = 0; i < tempNbQueen.size(); i++) {
		for (int j = 0; j < tempNbQueen[i].size() - 1; j++) {
			//Je fais un tableau et j'y met mes variables parce que Monsieur Kevin m'a appris a faire des tableaux du coup j'en met partout
			vector<int> Axe = { y - tempNbQueen[i][j + 1], int(x - tempNbQueen[i][j]) };
			if (Axe[0] * (Axe[1] - Axe[0]) * (Axe[1] + Axe[0]) == 0)
			{
				return false;
			}
		}
	}
	return true;
}

//Le BackTrack en iteratif parce que dans notre vie on utilisera que du r�cursif
void IteratifBackTrack(vector<vector<bool>>& grid, int nbQueen) {

	//Je cr�e les variables
	int nbQueenToPlace = nbQueen;
	bool Ok = false;

	//Je cr�er un tableau pour mes variables position horizontale et le verticale car je trouve �a plus propre
	//et que monsieur kevin m'a appris a faire des tableaux
	vector<int> Position = {0,0};
	
	vector<vector<int>> TabNbQueen;
	vector<int> NBY;

	// boucle tant que la taille du tableau est diff�rente du nombre de reine affich�
	while (TabNbQueen.size() != nbQueen){
		for (Position[0]; Position[0] < nbQueen; Position[0]++) {
			if (Ok == false) {
				Position[1] = 0;
			}
			Ok = false;
			for (Position[1]; Position[1] < grid[Position[0]].size(); Position[1]++) {
				if (checkCase(TabNbQueen, Position[0], Position[1]) == true) {
					grid[Position[0]][Position[1]] = true;
					NBY.push_back(Position[0]);
					NBY.push_back(Position[1]);
					TabNbQueen.push_back(NBY);
					NBY.clear();
					Position[1] = 0;
					break;
				}
			}

		}
		if (TabNbQueen.size() < nbQueen) {

			Position[0] = TabNbQueen[TabNbQueen.size() - 1][0];
			Position[1] = TabNbQueen[TabNbQueen.size() - 1][1];
			Ok = true;
			grid[Position[0]][Position[1]] = false;
			Position[1]++;
			TabNbQueen.pop_back();
			if (Position[1] >= grid[Position[0]].size()) {
				Position[1] = 0;
				Position[0] += 1;
			}
		}
	}

}


int main() {
	//Choix du nombre de reine donc aussi de la taille de tableau
	int nbQueen; 

	//Permet d'entrer un nombre de reine 
	cout << "Entre un nombre de reine : " << endl;
	cin >> nbQueen;

	vector<vector<bool>> grid(nbQueen, vector<bool>(nbQueen, false));
	IteratifBackTrack(grid, nbQueen);
	showTab(grid);
}