// Polynomial_Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <utility>
int abs(int a) {
    if (a < 0) {
        return -a;
    }
    else {
        return a;
    }
}
void printPair(std::pair<int, int > a) {
    if (a.second == 1) {
        std::cout << a.first;
    }
    else {
        std::cout << a.first << '/' << a.second;
    }
}
//PRINTING FUNCTIONS
void printPolynom(std::vector<std::pair<int, int>>& pol) {
    for (int i = 0;i < pol.size(); i++) {
        if (pol[i].first == 0) {
            continue;
        }
        
        if (pol[i].first * pol[i].second > 0 && i != 0) {
            std::cout << " + ";
        }
        if (pol[i].first * pol[i].second < 0) {
            std::cout << " - ";
        }
     
        if (abs(pol[i].second) == 1) {
            if (abs(pol[i].first) != 1) {

                std::cout << abs(pol[i].first);
            }
            else if (i == pol.size() - 1) {
                std::cout << 1;
            }
            else {

            }
            
        }
        else {
        std::cout<<abs(pol[i].first) << '/' << abs(pol[i].second);
    }
        int exp = pol.size() - 1 - i;
        if (exp > 1) {
            std::cout << "x^" << exp;
        }
        if (exp == 1) {
            std::cout << "x";
        }
    }
    
    bool flagi = true;
    for (int i = 0;i < pol.size();i++) {
        if (pol[i].first != 0) {
            flagi = false;
        }
    }
    if (flagi) {
        std::cout << 0;
    }
 
}
//PRINTING THE POLYNOM IN A NEW (x+a) Format
void printNewPolynom(std::vector<std::pair<int, int>>& pol, std::pair<int, int> a) {
    std::cout << "P(x + ";
    printPair(a);
    std::cout << ") = ";
    for (int i = 0;i < pol.size(); i++) {
        if (pol[i].first == 0) {
            continue;
        }

        if (pol[i].first * pol[i].second > 0 && i != 0) {
            std::cout << " + ";
        }
        if (pol[i].first * pol[i].second < 0) {
            std::cout << " - ";
        }

        if (abs(pol[i].second) == 1) {
            if (abs(pol[i].first) != 1) {

                std::cout << abs(pol[i].first);
            }
            else if (i == pol.size() - 1) {
                std::cout << 1;
            }
            else {

            }

        }
        else {
            std::cout << abs(pol[i].first) << '/' << abs(pol[i].second);
        }
        int exp = pol.size() - 1 - i;
        if (exp > 1) {
            std::cout << "(x + ";
            printPair(a);
            std::cout<<")^"<< exp;
           
        }
        if (exp == 1) {
            std::cout << "(x + ";
            printPair(a);
            std::cout << ")";
        }
    }

    bool flagi = true;
    for (int i = 0;i < pol.size();i++) {
        if (pol[i].first != 0) {
            flagi = false;
        }
    }
    if (flagi) {
        std::cout << 0;
    }
   
}
//Getting the coefficient from the input
std::pair<int, int> Coefficient(char buffer[]) {
    int i = 0;
    int num = 0;
    int dem = 0;
    bool flag = false;
    bool negative = false;
  
    if (buffer[0] == '-') {
        i++;
        negative = true;
    }
   
    while (buffer[i] != '\0') {
        if ((buffer[i] > '9' || buffer[i] < '0') && buffer[i] != '/') {
            throw std::exception("Invalid input!");
        }
        if (buffer[i] == '/') {
            flag =true;
            i++;
            continue;
        }
        if (flag) {
            dem = dem * 10 + (buffer[i] - '0');
        }
        else {
            num = num * 10 + (buffer[i] - '0');
        }
        i++;
    }
    if (!flag) {
        dem = 1;
    }
    if (negative) {
        num = -num;
    }
    if (dem == 0) {
        throw("Cannot divide by zero!");
    }
    
    std::pair<int, int> result{ num, dem };
    return result;
}
//Creating the polynoms
std::vector<std::pair<int, int>> createPolynom() {
    std::cout << "Enter degree of your polynom>>";
    int deg;
    std::cin >> deg;

    std::vector<std::pair<int, int>> polynom(deg+1);
    for (int i = deg;i >= 0;i--) {
        char buffer[1024];
        std::cout << "Enter a coefficient before x^" << i << ">>";
        if (i == deg) {
            std::cin.ignore();
        }
        std::cin.getline(buffer, 1024);
        polynom[deg-i] = Coefficient(buffer);
       
   
        
    }
    return polynom;
}
std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> createPolynoms() {
    std::cout << "Enter P(x)" << '\n';
    std::vector<std::pair<int, int>> p = createPolynom();
    printPolynom(p);
    std::cout << '\n';
    std::cout << "Enter Q(x)" << '\n';
    std::vector<std::pair<int, int>> q = createPolynom();
    printPolynom(q);
    std::cout << '\n';
    std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> pair(p, q);
    return pair;

}
//Substract and add polynomials functions - 1, 2
std::pair<int, int>& gcd(std::pair<int, int>& other) {
    int a = abs(other.first);
    int b = abs(other.second);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;

    }
    other.first /= a;
    other.second /= a;


    return other;
}
int add(int a, int b) {
    return a + b;
}
int substract(int a, int b) {
    return a - b;
}

std::pair<int, int> addsubstract(std::pair<int, int> a, std::pair<int, int> b, int (*func)(int, int)) {
    std::pair<int, int> c;
    c.first = func(a.first * b.second ,b.first * a.second);
    c.second = a.second * b.second;
    return gcd(c);
}

std::pair<int, int> bigger(int a, int b) {
    if (a > b) {
        return { a, b };
    }
    else {
        return { b, a };
    }

}
std::vector<std::pair<int, int>> addsubstractPolynoms(std::pair<std::vector<std::pair<int, int>> , std::vector<std::pair<int, int>>> polynoms ,std::pair<int, int> (*func)(std::pair<int, int> a, std::pair<int, int> b, int (*func)(int, int)),int (*func1)(int, int))
{
    int n, m;
    std::pair<int, int> help = bigger(polynoms.first.size(), polynoms.second.size());
    n = help.first;
    m = help.second;
    
    std::vector<std::pair<int, int>> newPolynom(n);
    int k = n - m;
    bool flag = polynoms.first.size() > polynoms.second.size();
    for (int j = 0;j < k;j++) {
        if (flag) {
            newPolynom[j] = polynoms.first[j];
        }
        else {
            newPolynom[j] = polynoms.second[j];
        }
    }
    for (int i = 0;i < m;i++) {
        
        if (flag) {
            newPolynom[i+k] = func(polynoms.first[i + k], polynoms.second[i], func1);
        }
        else { newPolynom[i + k] = func(polynoms.first[i], polynoms.second[i + k], func1); }
    }
    while ((!newPolynom.empty()) && newPolynom[0].first == 0) {
        
            newPolynom.erase(newPolynom.begin());
      
    }
    return newPolynom;
}
//Multiplying polynomial by number - 5
std::vector<std::pair<int, int>> multiplyByNumber(std::pair<int, int> num, std::vector<std::pair<int, int>>& pol) {
    for (int i = 0;i < pol.size(); i++) {
        std::pair<int, int> help = { pol[i].first * num.first, pol[i].second * num.second };
        pol[i] = gcd(help);
    }
    return pol;

}
std::pair<int, int> multiplyPairs(std::pair<int, int> a, std::pair<int, int> b) {
    std::pair<int, int> help;
    help.first = a.first * b.first;
    help.second = a.second * b.second;
    return gcd(help);
}

int pow(int base, int stepen) {
    int b = 1;
    for (int i = 0;i < stepen;i++) {
        b *= base;
    }
    return b;
}

bool checkBit(int num, int k) {
    num = num >> k;
    return num & 1;
}
int countOnes(int num) {
    int count = 0;
    while (num) {
        count += num & 1;
        num = num >> 1;
    }
    return count;
}
void printXcomb(int n, int k) {
    int num = pow(2, n);
    bool first = false;
    for (int i = num-1;i >= 0;i--) {
        
        if (countOnes(i) == k) {
            if (first) {
                std::cout << " + ";
            }
            first = true;
            for (int j = n;j >= 1;j--) {
                if (checkBit(i, j-1)) {
                    std::cout << 'x' << n - j + 1;
                }
            }
            
            
        }
    }
    
}
std::pair<int, int> dividePairs(std::pair<int, int> a, std::pair<int, int> b) {
    return multiplyPairs(a, { b.second, b.first });
}

//Viet Formulas - 8
void displayVietFormulas() {
    std::vector<std::pair<int, int>> pol = createPolynom();
    std::cout << "Displayed Viet Formulas for Polynom: ";
    printPolynom(pol);
    std::cout << '\n';
    int deg = pol.size() - 1;
    for (int i = 1; i <= deg; i++) {
        printXcomb(deg, i);
        
        std::cout << " = ";
        if (pow(-1, i) == -1) {
            pol[i].first = -pol[i].first;
        }
        printPair(dividePairs(pol[i], pol[0]));
        std::cout << '\n';
    }
}
//finding the value of the polynom by given number - 6
std::pair<int, int> findValueByNum(std::pair<int, int> num, std::vector<std::pair<int, int>>& polynom) {
   
    std::pair<int, int> final = { 0, 1 };
    int n = polynom.size();
    for (int i = 0;i < n;i++) {
        std::pair<int, int> help = { 1, 1 };
        help = multiplyPairs(help, polynom[i]);
        
        for (int j = 0;j < n- 1-i;j++) {
            help.first *= num.first;
            help.second *= num.second;
        }
       
        final = addsubstract(final, help, add);

    }
    
    return final;
}
//Multiplying polynomials - 3
std::vector<std::pair<int, int>> multiplyPolynoms(std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>>& polynoms) {
    
    int newSize = polynoms.first.size() + polynoms.second.size()-1;
    std::vector<std::pair<int, int>> multipliedPolynom(newSize, {0, 1});
    for (int i = 0;i < polynoms.first.size();i++) {
        for (int j = 0;j < polynoms.second.size();j++) {
            int idx = i + j;
            multipliedPolynom[idx] =  addsubstract(multipliedPolynom[idx], multiplyPairs(polynoms.first[i], polynoms.second[j]),add);
  
        }
    }
  

    return multipliedPolynom;
}
//Dividing polynomials - 4
std::vector<std::pair<int, int>> MultiplyByMonom(std::vector<std::pair<int, int>>& pol, std::pair<int, int> num, int degree) {
    std::vector<std::pair<int, int>> result(degree + pol.size(), { 0, 1 });
    for (int i = 0;i < pol.size();i++) {
        result[i] = multiplyPairs(pol[i], num);
    }
  
    return result;

}
std::pair< std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>> > 
dividePolynoms(std::pair<std::vector<std::pair<int, int>>, 
    std::vector<std::pair<int, int>>>& polynoms)
{
    
    int size1 = polynoms.first.size();
    int size2 = polynoms.second.size();
  
    if (size1 < size2) {
        throw std::runtime_error("The degree of the divisor cannot be greater than the degree of the divided");
   }
    if (size2 == 0) {
        throw std::runtime_error("Cannot divide by zero.");
    }
   
    bool flag = false;
    for (int i = 0;i < polynoms.second.size();i++) {
        if (polynoms.second[i].first != 0) {
            flag = true;
        }
    }
    if (!flag) {
        throw std::runtime_error("Cannot divide by zero!");
    }

    int k = size1 - size2; 
    if (k == 0) k = 1;
    int deg = k;

    std::vector<std::pair<int, int>> vec(k+1, { 0,1 });
  
    while (true) {
       
        size1 = polynoms.first.size();
        size2 = polynoms.second.size();
        if (size1 < size2) {
            break;
        }
       
        if (size1 == 0 || size2 == 0) {
            break;
        }
        k = size1 - size2;
        std::pair<int, int> coef = dividePairs(polynoms.first[0], polynoms.second[0]);
        vec[deg - k] = coef;

        std::vector<std::pair<int, int>> temp = MultiplyByMonom(polynoms.second, coef, k);
        polynoms.first = addsubstractPolynoms({ polynoms.first, temp}, addsubstract, substract);
    }
   
    
    return{ vec, polynoms.first};


}
bool nullCheck(std::vector<std::pair<int, int>>& pol) {
    bool flag = false;
    for (int i = 0;i < pol.size();i++) {
        if (pol[i].first != 0) {
            flag = true;
        }
    }
    return flag;
}
void swap(std::vector<std::pair<int, int>>& A, std::vector<std::pair<int, int>>& B) {
    std::vector<std::pair<int, int>> H = A;
    A = B;
    B = H;
}
//Finding GCD for polynoms - 7
std::vector<std::pair<int, int>> findGCDforPolynoms() {
    std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> polynoms = createPolynoms();
    std::vector<std::pair<int, int>> A = polynoms.first;
    std::vector<std::pair<int, int>> B = polynoms.second;
    
    if (A.size() < B.size()) {
        swap(A, B);
    }
   
    while (nullCheck(B)) {
        polynoms = { A, B};
        std::vector<std::pair<int, int>> temp = dividePolynoms(polynoms).second;
        A = B;
        B = temp;

    }
   

    std::pair<int, int> leading;
    for (int i = 0;i < A.size();i++) {
        if (A[i].first != 0) {
            leading = A[i];
            break;
        }
    }
    for (int i = 0;i < A.size();i++) {
        A[i] = dividePairs(A[i], leading);
    }
    std::cout << "GCD: ";
    printPolynom(A);
    std::cout << '\n';
    return A;

}
//Finding rational roots - 9
std::vector<int> findDelitels(int num) {
    std::vector<int> delitels;
    for (int i = 1;i <= abs(num);i++) {
        if (num % i == 0) {

            delitels.push_back(i);
            delitels.push_back(-i);
        }

    }
    return delitels;
}
std::pair<int, int> normalizeFraction(std::pair<int, int> num) {
   
    if (num.second < 0) {
        num.first = -num.first;
        num.second = -num.second;
    }
    std::pair<int, int> final = { num.first, num.second };
    return gcd(final);

}

void printRoots(std::vector<std::pair<std::pair<int, int>, int>>& roots) {
    for (int i = 0;i < roots.size();i++) {
        std::cout << "x = ";
        printPair(roots[i].first);
        std::cout << " -> " << roots[i].second <<" - fold root"<< '\n';
    }
}
void factorPolynom() {
    std::vector<std::pair<int, int>> pol = createPolynom();
    printPolynom(pol);
    std::cout << '\n';
    std::vector<std::pair<std::pair<int, int>, int>> roots;
    int countNulls = 0;
    while (true) 
    {
        std::pair<int, int> value = findValueByNum({ 0, 1 }, pol);
        if (value.first != 0) {
            break;
        }
        std::vector<std::pair<int, int>> vec1 = { {1, 1}, {0, 1} };
        std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> polynoms = { pol, vec1 };
        pol = dividePolynoms(polynoms).first;
        countNulls++;
        
    }

    if (countNulls > 0) {
        
        roots.push_back({ {0, 1}, countNulls });
        if (countNulls > 1) {
            std::cout << "x^" << countNulls;
        }
        else {
            std::cout << "x";
        }
    }

    int n1 = pol[0].second;
    int m1 = pol[pol.size() - 1].second;
    multiplyByNumber({ n1 * m1, 1 }, pol);

    int n = pol[0].first;
    int m = pol[pol.size() - 1].first;
    bool isFractorable = false;
    std::vector<int> delitelsN = findDelitels(n);

    std::vector<int> delitelsM = findDelitels(m);
    bool flag = false;
    for (int i = 0;i < delitelsM.size();i++) {
        for (int j = 0;j < delitelsN.size();j++) {
            std::pair<int, int> help = normalizeFraction({ delitelsM[i], delitelsN[j] });
            int count = 0;
            while (true) {
                std::pair<int, int> value = findValueByNum(help, pol);
                if (!(value.first == 0 && value.second == 1)) {
                    break;
                }
                
                isFractorable = true;
                count++;
                std::vector<std::pair<int, int>> vec = { {1, 1}, {-help.first, help.second} };
                std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> polynoms = { pol, vec };

                pol = dividePolynoms(polynoms).first;
                int idx = pol.size() - 1;
                if (pol.size() == 1 && pol[idx].first == 1) {
                    flag = true;
                    break;
                }

            }
            if (count > 0)
            {
                bool isthere = false;
                for (int i = 0;i < roots.size();i++) {
                    if (abs(help.first) == abs(roots[i].first.first) &&
                        abs(help.second) == abs(roots[i].first.second) &&
                        (help.first * help.second * roots[i].first.first * roots[i].first.second > 0))
                    {
                        isthere = true;
                        roots[i].second += count;
                    }
                }
                if (!isthere) { roots.push_back({ { help.first, help.second }, count }); }
            }
        }
    }
        for (int i = 0;i < roots.size();i++) {
            std::pair<int, int> help = roots[i].first;
            if (roots[i].first.first == 0) {
                continue;
            }
            int count = roots[i].second;
            std::cout << "(x ";
            if (help.first * help.second < 0) {
                std::cout << "+ ";
            }
            else {
                std::cout << "- ";
            }
            std::cout << abs(help.first);
            if (abs(help.second) != 1) { std::cout << '/' << abs(help.second); }
            std::cout << ')';
            if (count > 1) {
                std::cout << "^" << count;
            }
        }
        while (!pol.empty() && pol[0].first == 0) {
            pol.erase(pol.begin());
        }
        if(!(pol.size() == 1 && pol[0].first == 1 && pol[0].second == 1))
       
        {
            std::cout << "(";
            printPolynom(pol);
            std::cout << ")";
        }
        
        std::cout << " = 0"<< '\n';
        if (roots.empty()) {
            std::cout << "This polynom cannot be factored."<<'\n';
        }
        std::cout << "RATIONAL ROOTS" << '\n';
        printRoots(roots);
}
//Polynom from P(x) transformed into P(x+a) - 10
std::vector<std::pair<int, int>> powerPol(std::vector<std::pair<int, int>>& vec, int deg) {
    std::vector<std::pair<int, int>> pol = vec;
    if (deg == 0) {
        return { {1, 1} };
    }
    for (int i = 0;i < deg-1;i++) {
        std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> p = { pol, vec };
        pol = multiplyPolynoms(p);
    }

    
    return pol;
}
void newBasePol() {
    std::vector<std::pair<int, int>> pol = createPolynom();
    printPolynom(pol);
    std::cout << '\n';
    std::cout << "Enter a: "<<'\n';
    char buffer[1024];
    std::cin.getline(buffer, 1024);
    std::pair<int, int> num = Coefficient(buffer);
    
    int deg = pol.size() - 1;
    std::vector<std::pair<int, int>> vec(2);
    vec[0] = { 1, 1 };
    vec[1] = { num.first, num.second };

    std::vector<std::pair<int, int>> final_coeffs(deg+1, {0,1});
    std::vector<std::pair<int, int>> pol_helper;

    int degcurr = pol.size() - 1;
    while (true) {
        if (degcurr < 0) {
            break;
        }

        pol_helper = powerPol(vec, degcurr);
        pol_helper = multiplyByNumber(pol[0], pol_helper);
        final_coeffs[deg - degcurr] = pol[0];
        std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> p = { pol, pol_helper };
        
        pol = addsubstractPolynoms(p, addsubstract, substract);
        degcurr = pol.size() - 1;
    }
    printNewPolynom(final_coeffs, num);
    std::cout << '\n';


}
//Bonus function for factoring a polynom using the Undefined Coefficients method
void factorUndefinedCoeff() {
    std::vector<std::pair<int, int>> pol = createPolynom();
    int A, B, C, D, E, F;
    int a = pol[0].first;
    int b = pol[1].first;
    int c = pol[2].first;
    int d = pol[3].first;
    int e = pol[4].first;

    for (int i = 1;i <= a;i++) {
        if (a % i == 0) {
            A = i;
            D = a / i;
            for (int y = 1;y <= abs(e);y++) {
                if (e % y == 0) {
                    C = y;
                    F = e / y;
                    for (int j = -abs(b);j <= abs(b);j++) {
                        for (int j1 = -abs(b);j1 <= abs(b);j1++) {

                            if (A * j + D * j1 == b) {
                                B = j1;
                                E = j;
                                if (A * F + B * E + C * D == c 
                                    && C * E + B * F == d &&
                                    A*D == a && C*F == e &&
                                    A*E + D*B == b) {
                                    std::vector<std::pair<int, int>> vec1 = { {A, 1}, {B, 1}, {C, 1} };
                                    std::vector<std::pair<int, int>> vec2 = { {D, 1}, {E, 1}, {F, 1} };
                                    std::cout << "(";
                                    printPolynom(vec1);
                                    std::cout << ")";
                                    std::cout << "(";
                                    printPolynom(vec2);
                                    std::cout << ")";
                                    std::cout << '\n';
                                    return;
                                }
                        
                            }
                        }
                    }
                }

                
            }
        }
    }
    std::cout << "It is not factorable!" << '\n';
   
}
int main()
{
    std::cout << "Welcome to Polynomial Calculator - mini project intended to work with polynomials with rational coefficients." << '\n';
    std::cout << "Choose one of the following functionalities:" << '\n';
    std::cout << "1/ Add polynomials" << '\n';
    std::cout << "2/ Substract polynomials" << '\n';
    std::cout << "3/ Multiply polynomials" << '\n';
    std::cout << "4/ Divide polynoms" << '\n';
    std::cout << "5/ Multiply polynomial by rational number" << '\n';
    std::cout << "6/ Find value at a polynomial by a given number" << '\n';
    std::cout << "7/ Find GCD for two polynomials" << '\n';
    std::cout << "8/ Display Vieta's formulas for a given polynomial" << '\n';
    std::cout << "9/ Factor polynomial and finding its roots" << '\n';
    std::cout << "10/ P(x) transformed in P(x+a)"<<'\n';
    std::cout << "11/ Factor polynom from 4th degree without rational roots" << '\n';
    std::cout << "Enter your option here>> ";

    int n;
    std::cin >> n;
   

    std::vector<std::pair<int, int>> newPolynom;

    if (n == 1) {
        std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> polynoms = createPolynoms();
        newPolynom = addsubstractPolynoms(polynoms, addsubstract, add);
        std::cout << "P(x) + Q(x) = ";
        printPolynom(newPolynom);
    }
    else if (n == 2) {

        std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> polynoms = createPolynoms();
        newPolynom = addsubstractPolynoms(polynoms, addsubstract, substract);
        std::cout << "P(x) - Q(x) = ";
        printPolynom(newPolynom);
    }
    else if (n == 3) {
        std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> polynoms = createPolynoms();
        std::vector<std::pair<int, int>> multipliedPolynom = multiplyPolynoms(polynoms);
        std::cout << "P(x).Q(x) = ";
        printPolynom(multipliedPolynom);
        std::cout << '\n';
    }
    else if (n == 4) {
        std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> polynoms = createPolynoms();
        std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, int>>> newpolynoms = dividePolynoms(polynoms);
        std::cout << "Remainder: ";
        printPolynom(newpolynoms.first);
        std::cout << '\n';
        std::cout << "Quotient: ";
        printPolynom(newpolynoms.second);
    }
    else if (n == 5) {
        std::vector<std::pair<int, int>> pol = createPolynom();
        std::cout << "Enter your rational number: " << '\n';
        char buffer[1024];
        std::cin.getline(buffer, 1024);
        std::pair<int, int> num = Coefficient(buffer);
        multiplyByNumber(num, pol);
        printPolynom(pol);
    }
    else if (n == 6) {
        std::vector<std::pair<int, int>> pol = createPolynom();
        std::cout << "Enter your number: " << '\n';
        char buffer[1024];
        std::cin.getline(buffer, 1024);
        std::pair<int, int> num = Coefficient(buffer);
        std::pair<int, int> final = findValueByNum(num, pol);
        std::cout << "Final result: ";

        std::cout << final.first;
        if (final.second != 1) {
            std::cout << '/' << final.second;
        }
        std::cout<< '\n';
       
    }
    else if (n == 7) {
        findGCDforPolynoms();
    }
    else if (n == 8) {
        displayVietFormulas();
    }
    else if (n == 9) {
        factorPolynom();
    }
    else if (n == 10) {
        newBasePol();
    }
    else if (n == 11) {

        factorUndefinedCoeff();
    }
    else{
        return 0;
    }
    
}
