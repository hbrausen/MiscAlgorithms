#include <vector>
#include <iostream>

using namespace std;

#define fromArray(A) vector<double>(A, A + sizeof(A) / sizeof(A[0]))

template <typename T>
class Simplex {
public:
	enum ConstraintType {LT, GT, EQ};
	class Constraint {
	public:
		Constraint(const vector<T>& coeffs, ConstraintType ct, T b)
			: _coeffs(coeffs), _ct(ct), _b(b) {}
		ConstraintType getType() const { return _ct; }
		vector<T> getAsRow(int numSlack, int slackIndex) const;
	private:
		vector<T> _coeffs;
		ConstraintType _ct;
		T _b;
	};
	Simplex<T>(int nVars) : _nVars(nVars) {}
	void addConstraint(const Constraint& c) { _constraints.push_back(c); }
	void setObjective(const vector<T>& objective) { _objective = objective; }
	bool solve();
	bool phase1();	// Add slack, find basic feasible.
	bool phase2();	// Find optimum
	void printTableau() {
		for (int i = 0; i < _tableau.size(); ++i) {
			for (int j = 0; j < _tableau[i].size(); ++j) {
				cout << _tableau[i][j] << ' ';
			}
			cout << endl;
		}
	}
private:
	int getSlackCount() const;
	vector<Constraint> _constraints;
	vector<T> _objective;
	vector<vector<T> > _tableau;
	int _nVars;
};

template <typename T>
vector<T> Simplex<T>::Constraint::getAsRow(int numSlack, int slackIndex) const
{
	vector<T> row(_coeffs.size() + numSlack + 1);
	for (int i = 0; i < _coeffs.size() + numSlack; ++i) {
		row[i] = (i < _coeffs.size())?(_coeffs[i]):(_ct != EQ && i-_coeffs.size() == slackIndex);
	}
	row[_coeffs.size() + numSlack] = _b;
	return row;
}

template <typename T>
int Simplex<T>::getSlackCount() const
{
	int numSlack = 0;
	for (vector<Constraint>::const_iterator it = _constraints.begin();
		it != _constraints.end(); ++it) {
		numSlack += (it->getType() != EQ);
	}
	return numSlack;
}

template <typename T>
bool Simplex<T>::phase1()
{
	_tableau.clear();
	int numSlack = getSlackCount();
	int numCols = _nVars + numSlack + 3;
	vector<T> tempRow(numCols, static_cast<T>(0));
	vector<T> tempRow2(numCols, static_cast<T>(0));
	tempRow[0] = static_cast<T>(1);
	for (int i = 0; i < _objective.size(); ++i) {
		tempRow[i+1] = -_objective[i];
	}
	_tableau.push_back(tempRow);
	int slack = 0;
	for (vector<Constraint>::const_iterator it = _constraints.begin();
		it != _constraints.end(); ++it) {
		tempRow[0] = 0;
		copy(tempRow.begin(), tempRow.end(), 
		_tableau.push_back(it->getAsRow(numSlack, slack));
		if (it->getType() != EQ) ++slack;
	}
	return true;
}

typedef Simplex<double>::Constraint Constraint;
typedef Simplex<double>::ConstraintType ConstraintType;

int main(int argc, char **argv)
{
	// Solution of example problem.
	const double obj[] = {-2.0, -3.0, -4.0};
	const double c1[] = {3.0, 2.0, 1.0};
	const double b1 = 10;
	const double c2[] = {2.0, 5.0, 3.0};
	const double b2 = 15;
	Simplex<double> S(3);
	S.setObjective(fromArray(obj));
	S.addConstraint(Constraint(fromArray(c1), ConstraintType::EQ, b1));
	S.addConstraint(Constraint(fromArray(c2), ConstraintType::EQ, b2));
	S.phase1();
	S.printTableau();
	//S.solve();
	return 0;
}