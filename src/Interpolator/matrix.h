#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A square matrix class. </summary>
///
/// <remarks>	Paolo, 18/06/2019. </remarks>
///
/// <typeparam name="D">	Dimension of the square matrix </typeparam>
/// <typeparam name="T">	Type of the elements inside the matrix </typeparam>
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T = double>
class SquareMatrix
{
public:
    SquareMatrix<T>(SquareMatrix<T>& copy) : matrix(copy.matrix), size(copy.size) {}
    SquareMatrix<T>(SquareMatrix<T>&& move) : size(move.size), matrix(std::move(move.matrix)) {}
    SquareMatrix<T>(int dimension) {
        // Init to 0 matrix
        matrix.resize(dimension * dimension, 0);
        size = dimension;
    }
    SquareMatrix<T>(int dimension, bool identity) {
        matrix.resize(dimension * dimension, 0);
        if(identity) {
            // Init to identity matrix
            for (int i = 0; i < dimension; i++)
                matrix.at(i * dimension + i) = 1;
        }
        size = dimension;
    }
    SquareMatrix<T>(int dimension, T* values) {
        matrix.resize(dimension * dimension, 0);
        for (int r = 0; r < dimension; r++)
            for (int c = 0; c < dimension; c++)
                matrix.at(r * dimension + c) = values[r][c];
        size = dimension;
    }
    SquareMatrix<T>(int dimension, std::vector<std::vector<T>> values) {
        matrix.resize(dimension * dimension, 0);
        for (int r = 0; r < dimension; r++)
            for (int c = 0; c < dimension; c++)
                matrix.at(r * dimension + c) = values.at(r).at(c);
        size = dimension;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Gets the determinant of the matrix. </summary>
    ///
    /// <remarks>	Paolo, 18/06/2019. </remarks>
    ///
    /// <returns>	A double containing the determinant of the matrix. </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    double determinant() {
        if (size == 2) {
            return (at(0, 0) * at(1, 1)) - (at(0, 1) * at(1, 0));
        }
        else if (size > 2){
            double det = 0.;
            for (int i = 0; i < size; i++) {
                SquareMatrix<T> reducedMat(size-1);
                for (int r = 1; r < size; r++) {
                    int colDel = 0;
                    for (int c = 0; c < size; c++) {
                        if (c == i)
                            colDel = -1;
                        else
                            reducedMat.set(r - 1, c + colDel, at(r, c));
                    }
                }
                double reddet = reducedMat.determinant();
                int sign = pow(-1, i);
                T curval = at(0, i);
                det += sign*curval*reddet;
            }
            return det;
        }
        else {
            return at(0, 0);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Gets the size of the matrix. </summary>
    ///
    /// <remarks>	Paolo, 18/06/2019. </remarks>
    ///
    /// <returns>	The size. </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const int getSize() const { return size; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Get the element at row r and column c. </summary>
    ///
    /// <remarks>	Paolo, 18/06/2019. </remarks>
    ///
    /// <param name="r">	Row. </param>
    /// <param name="c">	Column. </param>
    ///
    /// <returns>	The element of the matrix. </returns>
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const T at(int r, int c) const {
        return matrix.at(r * size + c);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Sets an element of the matrix. </summary>
    ///
    /// <remarks>	Paolo, 18/06/2019. </remarks>
    ///
    /// <param name="r">  	Row. </param>
    /// <param name="c">  	Column. </param>
    /// <param name="val">	The value. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    void set(int r, int c, T val) {
        matrix.at(r * size + c) = val;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Adds a value to an element of the matrix. </summary>
    ///
    /// <remarks>	Paolo, 18/06/2019. </remarks>
    ///
    /// <param name="r">  	Row. </param>
    /// <param name="c">  	Column. </param>
    /// <param name="val">	The value to add. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    void add(int r, int c, T val) {
        matrix.at(r * size + c) += val;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// <summary>	Replaces a column of the matrix with a column vector. </summary>
    ///
    /// <remarks>	Paolo, 18/06/2019. </remarks>
    ///
    /// <param name="c">		   	Column to replace. </param>
    /// <param name="columnVector">	The column vector. </param>
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    void replaceColumn(int c, const std::vector<T>& columnVector) {
        for (int r = 0; r < size; r++) {
            set(r, c, columnVector.at(r));
        }
    }
private:
    int size = 0;
    std::vector<T> matrix;
};
/*
template<typename T>
class SquareMatrix<1, T>
{
public:
    SquareMatrix<1, T>() {
        size = 1;
    }
    SquareMatrix<1, T>(bool identity) {
        matrix.at(0) = 1;
        size = 1;
    }
    SquareMatrix<1, T>(T* values) {
        matrix.at(0) = values[0][0];
        size = 1;
    }
    SquareMatrix<1, T>(std::vector<std::vector<T>> values) {
        matrix.at(0) = values.at(0).at(0);
        size = 1;
    }
    double determinant() {
        return matrix.at(0);
    }

    const int getSize() const { return size; }
    const T at(int r, int c) const {
        return matrix.at(0);
    }
    void set(int r, int c, T val) {
        matrix.at(0) = val;
    }
private:
    int size = 1;
    std::vector<T> matrix;
};*/

#endif // MATRIX_H
