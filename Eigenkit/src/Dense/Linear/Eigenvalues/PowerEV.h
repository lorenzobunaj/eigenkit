namespace ek
{
    template <typename T>
    bool conv(Matrix<T> p, Matrix<T> s, size_t k)
    {
        for (size_t i=0; i<p.rows()-1; i++) {
            if (std::abs(p(i,0)-s(i,0)) > 1/std::pow(10,k)) {
                return 0;
            }
        }

        return 1;
    }

    template <typename T>
    T Rayleigh(Matrix<T> A, Matrix<T> x)
    {
        Vector<T> op1;
        Vector<T> op2;

        op1 = A*x;
        op2 = x;

        return (op1.dot(op2))/(op2.dot(op2));
    }

    template <typename T>
    T PowerEV(Matrix<T> A, size_t k, size_t n)
    {
        std::vector<T> vn;
        vn.resize(2);

        Matrix<T> x(A.cols(),1);
        for (size_t i = 0; i<x.rows(); i++) {
            x(i,0) = 1;
        }

        Matrix<T> p;
        Matrix<T> s;
        size_t i=0;
        do {
            p = x;
            s = A*x;

            s = s/s(s.rows()-1,0);
            x = s;

            i++;
        } while (!conv(p,s,k) && i<n);

        return Rayleigh(A,x);
    }
}
