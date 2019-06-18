#ifndef POLYFIT_H
#define POLYFIT_H

#include <vector>
#include <string>
#include "matrix.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Class for polynomial fitting of measured data </summary>
///
/// <remarks>	Paolo Infante, 18/06/2019. </remarks>
///
/// <typeparam name="T">		Type of the data. Double, Float, Integer are recommended. </typeparam>
/// <typeparam name="Order">	Order of the polynomial </typeparam>
////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
class PolyFit
{
public:
        // Custom exception
        class FitException : public std::exception {
        public:
                FitException(std::string msg) : msg(msg) {}
                const char* what() const noexcept override { return msg.c_str();  }
        private:
                std::string msg;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>	Fit goodness statistical parameters </summary>
        ///
        /// <remarks>	Paolo, 18/06/2019. </remarks>
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        template<typename E>
        struct Parameters {
                double RSquared;
                std::vector<E> residuals;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>	Constructor. </summary>
        ///
        /// <remarks>	Paolo, 18/06/2019. </remarks>
        ///
        /// <exception cref="FitException">	Thrown when a Fit error condition occurs. </exception>
        ///
        /// <typeparam name="T">		Type of the data. Double, Float, Integer are recommended. </typeparam>
        /// <typeparam name="Order">	Order of the polynomial </typeparam>
        /// <param name="X">	A std::vector&lt;T&gt; to process. </param>
        /// <param name="Y">	A std::vector&lt;T&gt; to process. </param>
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        PolyFit<T>(const std::vector<T>& X, const std::vector<T>& Y, int order) : X(X), Y(Y), order(order) {
                if (X.size() < 2 || Y.size() < 2)
                        throw new FitException("X and Y vectors must contain at least 2 elements");
                if (X.size() != Y.size())
                        throw new FitException("X and Y vectors must be of same size");
                doFit();
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>	Gets the coefficients. </summary>
        ///
        /// <remarks>	Paolo, 18/06/2019. </remarks>
        ///
        /// <returns>	The coefficients of the resulting fitted polynomial. Index of the vector
        /// 			corresponds to the order of the variable
        /// </returns>
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        const std::vector<double> getCoefficients() const { return coefficients;  }

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        /// <summary>	Gets the statistical parameters. </summary>
        ///
        /// <remarks>	Paolo, 18/06/2019. </remarks>
        ///
        /// <returns>	The parameters. </returns>
        ////////////////////////////////////////////////////////////////////////////////////////////////////

        const Parameters<T> getParameters() const { return params; }


        const T estimate(T x) const {
                T out = 0.;
                for (int i = 0; i < coefficients.size(); i++)
                        out += pow(x, i) * coefficients.at(i);
                return out;
        }
private:
        int order;
        std::vector<T> X, Y;
        std::vector<double> coefficients;
        Parameters<T> params;

        double getMean(std::vector<T> values) {
                double t = 0.;
                for (T v : values)
                        t += v;
                return t / values.size();
        }

        void doFit() {
                coefficients.resize(order + 1);
                SquareMatrix<double> A(order+1);
                std::vector<double> B;
                B.resize(order + 1);

                for (int i = 0; i < X.size(); i++) {
                        for (int m = 0; m <= order; m++) {
                                // Build A matrix
                                for (int n = 0; n <= order; n++) {
                                        T x = X.at(i);
                                        A.add(m, n, pow(x, m) * pow(x, n));
                                }
                                // Build B column vector
                                B.at(m) += pow(X.at(i), m) * Y.at(i);
                        }
                }
                double Adet = A.determinant();
                // Build replaced matrices and fill coefficients vector with the result given by Cramer method
                // Which is Ci = det(Ai)/det(A)
                for (int i = 0; i <= order; i++) {
                        SquareMatrix<double> Ai(A);
                        Ai.replaceColumn(i, B);
                        double Aidet = Ai.determinant();
                        coefficients.at(i) = Aidet / Adet;
                }

                double yMean = getMean(Y);
                double ESS = 0.;
                double TSS = 0.;
                for (int i = 0; i < Y.size(); i++) {
                        T yEstim = estimate(X.at(i)); // iastim cchiù ca ato
                        ESS += pow(yEstim - yMean, 2);
                        TSS += pow(Y.at(i) - yMean, 2);
                        params.residuals.emplace_back(yEstim - Y.at(i));
                }

                params.RSquared = ESS / TSS;

        }
};



#endif // POLYFIT_H
