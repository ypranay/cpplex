/*
This file is part of C++lex, a project by Tommaso Urli.

C++lex is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

C++lex is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with C++lex.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MATRIX_H
#define MATRIX_H

// Inclusions
#include "pilal.h"
#include <utility>	// std::pair
#include <vector>	// std::vector
#include <iostream> // std::string

namespace pilal {

    
    /*
        PermutationFormat
        =================
        Enum type that describes the two types of permutation data
        that the functions can use.
    */
    enum PermutationFormat {   

        PF_MATRIX, 
        PF_VECTOR 
    };
    
    /*
        MatrixType
        ==========
        Enum type that describes the shape of the matrix to optimize
        matrix inversion for special matrices (triangular, permutation
        or general)
    */
    
    enum MatrixType {   
        MT_GENERAL, 
        MT_TRIANGULAR_UPPER, 
        MT_TRIANGULAR_LOWER, 
        MT_PERMUTATION          
    };
  
    class Matrix;
    class AnonymousMatrix;
  
    /*
        Matrix
        ======
        Main class, where the core computations are carried out.
    
    */
    class Matrix {
	    
	    friend class AnonymousMatrix;
	
	public:
		
		// Constructors, copy-constructor, destructor
		Matrix();
		Matrix(char const * values);
		Matrix(int n);
		Matrix(int n, long double v);
		Matrix(int r, int c);
		Matrix(int r, int c, long double v);
		Matrix(Matrix const& m);		
		Matrix(AnonymousMatrix m);
		virtual ~Matrix();
		
		// Accessor class to manage cache invalidation
        class storage_accessor {
            
            public:
            
                storage_accessor(long double& dest, Matrix& parent);
                operator long double const& () const;                           // Reading
                storage_accessor& operator=(storage_accessor& new_value);       // Copying
                storage_accessor& operator=(long double const& new_value);      // Writing
                
            private:
                
                long double& dest;
                Matrix& parent;
        };
		
		// Log and status query functions
		virtual std::pair<int,int> dim() const;
		void log(std::string name) const;
		void logtave(std::string name) const;
		bool is_square() const;
		bool is_identity(long double tol) const;
		double space() const;
		bool more_equal_than (long double value, long double tol) const;
		bool less_equal_than (long double value, long double tol) const;
		AnonymousMatrix operator- (AnonymousMatrix m) const;
		AnonymousMatrix operator+ (AnonymousMatrix m) const;
		
		// Matrix manipulation
		void swap_columns(int r, int w);
		void swap_rows(int r, int w);
		void set_determinant(long double d);
		void set_identity();
        void transpose();
        void resize(int r, int c);
        void empty();
        void set_row(int i, char const* row);
        void set_column(int j, char const* column);
        void set_values(char const* values);
				
		// Misc functions
        long double determinant() const;
		
        // More complex functions
		void get_lupp(Matrix& l, Matrix& u, Matrix& p, PermutationFormat pf) const;
		void get_inverse(Matrix& inverse) const;
		void get_inverse(Matrix& inverse, MatrixType mt) const;
        static void get_inverse_with_column(Matrix const& old_inverse, Matrix const& new_column, 
                                     int column_index, Matrix& new_inverse);
		void solve(Matrix& x, Matrix const& b) const;
		bool rows_linearly_independent();
		bool columns_linearly_independent();
		
		// Operators overloading - virtual
		virtual AnonymousMatrix operator*(AnonymousMatrix m) const;
		virtual AnonymousMatrix operator*(Matrix const& m);
		
		// Operators overloading
		Matrix& operator=(Matrix const& m);
		Matrix& operator=(char const * values);
		Matrix& operator=(AnonymousMatrix m);
		Matrix& operator*=(Matrix const& m);
		Matrix& operator*=(AnonymousMatrix m);
		
		// Access operators
		long double& operator() (int i);
        long double const& operator() (int i) const;
        long double& operator() (int r, int c);
        long double const& operator() (int r, int c) const;
        long double& at(int r, int c);
        long double const& at(int r, int c) const;
        
        // Cast
        operator long double();	

        
	protected:

        // Other complex operations
        AnonymousMatrix gaussian_elimination();

        // Auxiliary operations
        MatrixType get_matrix_type(Matrix const& m) const;
        
		// Status information
		mutable bool lu_up_to_date, determinant_up_to_date, inverse_up_to_date;
		
		// Storage
		class storage {
		    
		    public:
		        
		        // Create & destroy
		        storage(int size);
		        storage(int size, long double value);
		        storage(storage& origin);
		        ~storage();
		        
		        // Access
		        long double & at(int pos);

                // Data		    
		        std::vector< long double> * contents;
		        int counter;
		
		};
		
		storage* values;
		int rows;
		int columns;
		
		// Algebraic properties
		mutable long double det;
		
	};

    /*
        AnonymousMatrix
        ===============
        Class used for temporary matrices.
    
    */
    class AnonymousMatrix : public Matrix {
                
        public:
            // Copy/constructor
            AnonymousMatrix(int r, int c);
            AnonymousMatrix(const AnonymousMatrix& m);
            AnonymousMatrix(const Matrix& m);
            
            // Operators
            AnonymousMatrix operator*(Matrix const& m);
    };
    
    
    /*
        Auxiliary functions
    */	
    
    bool tol_equal(long double n, long double m, long double tol);	
}

#endif

