#include "matrix/matrix.cc"
#include <cmath>
#include <functional>

class Activation {
public:
	static double sigmoid(const double& k) {
		return 1.0 / (1 + exp(-k));
	}

	static double rectifiedLinearUnit(const double& k) {
		return k > 0.0 ? k : 0.0;
	}

	static Matrix sigmoidMatrix(const Matrix& mat) {
		assert(mat.cols == 1);
		Matrix ret(mat.rows, mat.cols);

		for (size_t i = 0; i < mat.rows; i++) {
			for (size_t j = 0; j < mat.cols; j++) {
				ret.set(i, j, sigmoid(mat.at(i, j)));
			}
		}

		return ret;
	}

	static Matrix rectifiedLinearUnitMatrix(const Matrix& mat) {
		assert(mat.cols == 1);
		Matrix ret(mat.rows, mat.cols);

		for (size_t i = 0; i < mat.rows; i++) {
			for (size_t j = 0; j < mat.cols; j++) {
				ret.set(i, j, rectifiedLinearUnit(mat.at(i, j)));
			}
		}

		return ret;
	}
};

class Layer {
private:
	size_t input_size;
	size_t output_size;
	Matrix weights;
	Matrix biases;
	std::function<Matrix(const Matrix&)> activationFunction;
public:

	explicit Layer(size_t input_size, size_t output_size, std::function<Matrix(const Matrix&)> activation) :
			input_size(input_size),
			output_size(output_size),
			activationFunction(activation),
			weights(Matrix(output_size, input_size)),
			biases(Matrix(output_size, 1)) {
		weights.defaultInitialization();
		biases.defaultInitialization();
	}

	Matrix forward(Matrix input) {
		assert(input.rows == input_size);
		assert(input.cols == 1);

		return activationFunction(weights * input + biases);
	}

};

class NeuralNetwork {
private:
	size_t input_size;
};

int main() {
	size_t input_size = 2;
	size_t output_size = 4;

	Layer l(2, 4, &Activation::sigmoidMatrix);

	Matrix input(2, 1);
	input.defaultInitialization();
	input.print();
	separate();

	Matrix output = l.forward(input);
	output.print();

	return 0;
}