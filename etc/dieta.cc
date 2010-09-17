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

#include <iostream>
#include <sstream>
#include "pilal/pilal.h"
#include "simplex/simplex.h"
#include <ctime>
#include <cstdlib>

using namespace pilal;
using namespace optimization;

int main() {


    Simplex dieta("Problema della dieta");
    Matrix tabella_nutrizionale(4,38);
    

    //                                  Cal   Pro  Lip   Glic
    tabella_nutrizionale.set_column(0,  "362   11   1.5   76  "  );  // Pasta
    
    tabella_nutrizionale.set_column(1,  "348    7   0.7   78  "  );  // Riso
    tabella_nutrizionale.set_column(2,  "280    8   0.5   64  "  );  // Pane
    tabella_nutrizionale.set_column(3,  "120    7   0.8   20  "  );  // Fagioli
    tabella_nutrizionale.set_column(4,  " 76    7   0.4   12  "  );  // Piselli
    tabella_nutrizionale.set_column(5,  " 88    4   0.6   18  "  );  // Aglio
    tabella_nutrizionale.set_column(6,  " 10    1   0      2.7"  );  // Carote
    tabella_nutrizionale.set_column(7,  " 30    1   0      7  "  );  // Cipolle
    tabella_nutrizionale.set_column(8,  " 16    2   0.4    2.2"  );  // Lattuga
    tabella_nutrizionale.set_column(9,  " 15    1   0.1    2.6"  );  // Melanzane
    tabella_nutrizionale.set_column(10, " 85    2   1     18  "  );  // Patate
    tabella_nutrizionale.set_column(11, " 19    1   0.2    3.5"  );  // Pomodoro
    tabella_nutrizionale.set_column(12, " 30    3.5 0.5    5  "  );  // Spinaci
    tabella_nutrizionale.set_column(13, " 40    0.5 0     10  "  );  // Succo arancia
    tabella_nutrizionale.set_column(14, " 75    1.2 0.3   18  "  );  // Banane
    tabella_nutrizionale.set_column(15, " 50    0.5 0.2   16  "  );  // Mele
    tabella_nutrizionale.set_column(16, "214   19  13      0  "  );  // Manzo
    tabella_nutrizionale.set_column(17, "100   18   3      0  "  );  // Maiale
    tabella_nutrizionale.set_column(18, " 97   22   1.6    0  "  );  // Pollo
    tabella_nutrizionale.set_column(19, "130   21   5      0.4"  );  // Vitello
    tabella_nutrizionale.set_column(20, "480   20  42      0  "  );  // Prosciutto crudo
    tabella_nutrizionale.set_column(21, "412   21  36      0  "  );  // Prosciutto cotto
    tabella_nutrizionale.set_column(22, " 68   13   1.7    0.6"  );  // Calamari
    tabella_nutrizionale.set_column(23, "127   16   7      0.7"  );  // Cefali
    tabella_nutrizionale.set_column(24, " 65   12   1.9    2  "  );  // Cozze
    tabella_nutrizionale.set_column(25, "168   17  11      0.8"  );  // Sgombro
    tabella_nutrizionale.set_column(26, "140   22   6      0.6"  );  // Tonno
    tabella_nutrizionale.set_column(27, " 47    3.5 1.8    5  "  );  // Latte
    tabella_nutrizionale.set_column(28, "381   35  27      3.5"  );  // Grana
    tabella_nutrizionale.set_column(29, "450   31  37      0  "  );  // Latteria
    tabella_nutrizionale.set_column(30, "243   20  16      4.9"  );  // Mozzarella
    tabella_nutrizionale.set_column(31, "160   13  11      1  "  );  // Uova
    tabella_nutrizionale.set_column(32, "760    1  84      1  "  );  // Burro
    tabella_nutrizionale.set_column(33, "880    0 100      0  "  );  // Olio di oliva
    tabella_nutrizionale.set_column(34, "500    4  30     60  "  );  // Cioccolato fondente
    tabella_nutrizionale.set_column(35, "220    4  14     21  "  );  // Gelato
    tabella_nutrizionale.set_column(36, " 33    0   0      3  "  );  // Birra
    tabella_nutrizionale.set_column(37, " 80    0   0      0.5"  );  // Vino
    
    
    
    Matrix lower_bound_nutrienti(1,4), upper_bound_nutrienti(1,4);
    
    //                                Cal   Pro  Lip   Glic
    lower_bound_nutrienti.set_values("2000  58   70    100");
    upper_bound_nutrienti.set_values("2500  100  100   500");
    
    Matrix c(1,38);
    c.set_values("1.2 2.2 2.5 1.3 1.35 5.2 1.9 1.3 1.5 1.2 0.6 1.5 1.9 1.5 1.5 1.8 12 6 9.8 18 18 15 6 7 13 6 8 0.8 14 11 8 0.8 8 4 7 7 1.5 1.8");
    
    
    for (int i = 0; i < 4; ++i) {
    
        Matrix coefficients(1, 38);
        
        for (int j = 0; j < 38; ++j)
            coefficients(j) = tabella_nutrizionale(i,j);
            
        dieta.add_constraint( Constraint( coefficients, CT_LESS_EQUAL, upper_bound_nutrienti(i) ) );
        dieta.add_constraint( Constraint( coefficients, CT_MORE_EQUAL, lower_bound_nutrienti(i) ) );
        
        
    }
    
    for ( int i = 0; i < 38; ++i ) {
        Matrix eye(1,38,0);
        eye(i) = 1;    
        dieta.add_constraint( Constraint( eye, CT_NON_NEGATIVE, 0));
        dieta.add_constraint( Constraint( eye, CT_LESS_EQUAL, 2));

    }
    
    
    // Set objective function
    dieta.set_objective_function( ObjectiveFunction(OFT_MINIMIZE, c) );
    
    // Solve
    dieta.solve();
    
    
    
    return 0;
}
