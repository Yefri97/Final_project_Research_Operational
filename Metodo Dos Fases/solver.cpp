#include <bits/stdc++.h>
using namespace std;

vector<string> vec_objective = {"Minimizar", "Maximizar"};
vector<string> vec_operator = {">=", "<=", "=="};

void print_matrix(vector< vector<double> > matrix) {
	cout << endl;
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix[i].size(); ++j) {
			printf("%5.02f ", matrix[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

int pos_var_bas(vector<double> v) {
	int target = -1;
	bool flag = false;
	for (int i = 0; i < v.size(); ++i) {
		if (v[i] == 0.0) continue;
		if (flag) return -1;
		if (v[i] == 1.0) {
			target = i;
			flag = true;
		}
	}
	return target;
}

vector<double> multiply_row_by_constant(vector<double> a, double c) {
	vector<double> target(a.size());
	for (int i = 0; i < a.size(); ++i) {
		target[i] = a[i] * c;
	}
	return target;
}

vector<double> sum_row(vector<double> a, vector<double> b) {
	vector<double> target(a.size());
	for (int i = 0; i < a.size(); ++i) {
		target[i] = a[i] + b[i];
	}
	return target;
}

pair<int, int> max_pivote(vector< vector<double> > m) {
	int column = 0, row = 0;
	double min_column = 1000000.0;
	for (int i = 0; i < m[0].size() - 1; ++i) {
		if (m[0][i] < min_column) {
			column = i;
			min_column = m[0][i];
		}
	}
	double min = 1000000.0;
	for (int i = 1; i < m.size(); ++i) {
		if (m[i][column] > 0) {
			if (m[i][m[i].size() - 1] / m[i][column] < min) {
				row = i;
				min = m[i][m[i].size() - 1] / m[i][column];
			}
		}
	}
	return make_pair(row, column);
}

pair<int, int> min_pivote(vector< vector<double> > m) {
	int column = 0, row = 0;
	double max = 0.0;
	for (int i = 0; i < m[0].size() - 1; ++i) {
		if (m[0][i] > max) {
			column = i;
			max = m[0][i];
		}
	}
	double min = 1000000.0;
	for (int i = 1; i < m.size(); ++i) {
		if (m[i][column] > 0) {
			if (m[i][m[i].size() - 1] / m[i][column] < min) {
				row = i;
				min = m[i][m[i].size() - 1] / m[i][column];
			}
		}
	}
	return make_pair(row, column);
}

bool verify(vector<double> v, int obj) {
	for (int i = 0; i < v.size() - 1; ++i) {
		if (obj) {
			if (v[i] < -0.1) {
				return true;
			}
		} else {
			if (v[i] > 0.1) {
				return true;
			}
		}
	}
	return false;
}

vector< vector<double> > gauss_jordan(vector< vector<double> > m, int obj) {

	while (verify(m[0], obj)) {

		pair<int, int> pivote = (obj)? max_pivote(m) : min_pivote(m);

		m[pivote.first] = multiply_row_by_constant(m[pivote.first], 1 / m[pivote.first][pivote.second]);

		for (int i = 0; i < m.size(); ++i) {
			if (i != pivote.first) {
				m[i] = sum_row(m[i], multiply_row_by_constant(m[pivote.first], -1 * (m[i][pivote.second])));
			}
		}
	}
	return m;
}

vector<double> fill_row(int current_res, int var, int res, vector<double> cons) {
	vector<double> target(var + 3 * res + 1);
	for (int i = 0; i < var; ++i) {
		target[i] = cons[i];
	}
	if (cons[cons.size() - 2] == 0) {
		target[var + 0 * res + current_res] = -1.0;
		target[var + 2 * res + current_res] = 1.0;
	}
	if (cons[cons.size() - 2] == 1) {
		target[var + 1 * res + current_res] = 1.0;
		//target[var + 2 * res + current_res] = 1.0;
	}
	if (cons[cons.size() - 2] == 2) {
		target[var + 2 * res + current_res] = 1.0;
	}
	target[target.size() - 1] = cons[cons.size() - 1];
	return target;
}

vector< vector<double> > fill_matrix(int var, int res, vector< vector<double> > cons) {
	vector< vector<double> > target(res + 1, vector<double>(var + 3 * res + 1));
	for (int i = 0; i < cons.size(); ++i) {
		target[i + 1] = fill_row(i, var, res, cons[i]);
	}
	return target;
}

int main() {
	int num_var, num_res, objective;
	
	cout << endl << "¿Cuántas variables de decisión tiene el problema?" << endl;
	cin >> num_var; cout << num_var << endl;
	
	cout << "¿Cuántas restricciones?" << endl;
	cin >> num_res; cout << num_res << endl;
	
	cout << "¿Cuál es el objetivo de la función?" << endl;
	cin >> objective; cout << vec_objective[objective] << endl << endl;

	cout << "Función Objetivo:" << endl;
	vector<double> function_target(num_var);
	for (int i = 0; i < function_target.size(); ++i) {
		cin >> function_target[i];
	}
	for (int i = 0; i < function_target.size(); ++i) {
		if (i) printf(" + ");
		printf("(%5.01f)X%d", function_target[i], i + 1);
	}
	cout << endl << endl;

	cout << "Restricciones:" << endl;
	vector< vector<double> > constraints(num_res, vector<double>(num_var + 2));
	for (int i = 0; i < constraints.size(); ++i) {
		for (int j = 0; j < constraints[i].size(); ++j) {
			cin >> constraints[i][j];
		}
	}
	for (int i = 0; i < constraints.size(); ++i) {
		for (int j = 0; j < constraints[i].size() - 2; ++j) {
			if (j) printf(" + ");
			printf("(%5.01f)X%d", constraints[i][j], j + 1);
		}
		printf(" %s (%5.01f)\n", vec_operator[int(constraints[i][constraints[i].size() - 2])].c_str(), constraints[i][constraints[i].size() - 1]);
	}
	for (int i = 0; i < function_target.size(); ++i) {
		if (i) printf(", ");
		printf("X%d", i + 1);
	}
	printf(" >= 0\n");

	// *FASE 1*

	// Creamos la matriz con las variables de exceso, holgura y artificiales
	vector< vector<double> > matrix = fill_matrix(num_var, num_res, constraints);

	// Sumamos las filas para eliminar los -1
	for (int i = 0; i < num_res; ++i) {
		if (matrix[i + 1][num_var + 2 * num_res + i]) {
			matrix[0] = sum_row(matrix[0], matrix[i + 1]);
			matrix[0][num_var + 2 * num_res + i] = 0;
		}
	}
	
	// Minimizamos por Gauss-Jordan
	matrix = gauss_jordan(matrix, 0);

	// Verificamos si tiene solución factible
	if (matrix[0][matrix[0].size() - 1] > 0.01) {
		cout << "No tiene solución factible" << endl;
		return -1;
	}

	// *FASE 2*

	// Eliminamos las variables artificiales de la matrix
	for (int i = 0; i <= num_res; ++i) {
		for (int j = 0; j < num_res; ++j) {
			matrix[i][num_var + 2 * num_res + j] = 0;
		}
	}

	// Remplazamos la funcion objetivo por la original
	for (int i = 0; i < function_target.size(); ++i) {
		matrix[0][i] = -1 * (function_target[i]);
	}

	// Volvemos cero las variables basicas
	for (int i = 0; i < num_var; ++i) {
		vector<double> v(num_res);
		for (int j = 0; j < num_res; ++j) {
			v[j] = matrix[j + 1][i];
		}
		int pos = pos_var_bas(v);
		if (pos != -1) matrix[0] = sum_row(matrix[0], multiply_row_by_constant(matrix[pos + 1], -1 * (matrix[0][i])));
	}

	// Aplicamos Gauss-Jordan
	matrix = gauss_jordan(matrix, objective);

	//print_matrix(matrix);

	vector<double> target(num_var + 1);
	for (int i = 0; i < num_var; ++i) {
		vector<double> v(num_res);
		for (int j = 0; j < num_res; ++j) {
			v[j] = matrix[j + 1][i];
		}
		int pos = pos_var_bas(v);
		if (pos != -1) target[i] = matrix[pos + 1][matrix[0].size() - 1];
	}
	target[target.size() - 1] = matrix[0][matrix[0].size() - 1];

	cout << endl;
	printf("Z = %5.02f\n", target[target.size() - 1]);
	for (int i = 0; i < target.size() - 1; ++i) {
		if (i) printf(", ");
		printf("X%d = %5.02f", i + 1, target[i]);
	}
	cout << endl;

	cout << endl;
	return 0;
}