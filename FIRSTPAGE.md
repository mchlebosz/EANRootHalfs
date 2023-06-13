# Klasa BisectionInterval

Klasa `BisectionInterval` implementuje metodę bisekcji do znajdowania miejsc zerowych wielomianu przy użyciu arytmetyki przedziałowej.

### Konstruktor

```cpp
BisectionInterval(std::vector<double> leftCoefficients,
				  std::vector<double> rightCoefficients, double aLeft,
				  double bLeft, double aRight, double bRight,
				  double epsilon, long long max_iterations = 10000);
```

Konstruktor inicjalizuje obiekt klasy `BisectionInterval` z danymi współczynnikami, granicami przedziału oraz kryteriami zbieżności.

- `leftCoefficients`: Wektor współczynników dla lewej granicy przedziału wartości współczynników. Każdy element wektora reprezentuje współczynnik kolejnego składnika wielomianu, zaczynając od wyrazu stałego i zwiększając stopień wielomianu.
- `rightCoefficients`: Wektor współczynników dla prawej granicy przedziału wartości współczynników. Każdy element wektora reprezentuje współczynnik kolejnego składnika wielomianu, zaczynając od wyrazu stałego i zwiększając stopień wielomianu.
- `aLeft`: Lewa granica przedziału dla zmiennej lewej w metodzie bisekcji.
- `bLeft`: Lewa granica przedziału dla zmiennej prawej w metodzie bisekcji.
- `aRight`: Prawa granica przedziału dla zmiennej lewej w metodzie bisekcji.
- `bRight`: Prawa granica przedziału dla zmiennej prawej w metodzie bisekcji.
- `epsilon`: Poziom tolerancji dla metody bisekcji. Określa maksymalną dopuszczalną różnicę między górnym i dolnym ograniczeniem przedziału. Jeśli różnica jest mniejsza niż epsilon, algorytm zatrzymuje się i zwraca środek przedziału jako rozwiązanie.
- `max_iterations`: Maksymalna liczba iteracji dozwolonych dla algorytmu bisekcji w celu zbiegnięcia do rozwiązania. Wartość domyślna to 10000.

### Metoda solve

```cpp
interval_arithmetic::Interval<double> solve(short* error_code);
```

Metoda `solve` implementuje metodę bisekcji w celu znalezienia miejsca zerowego funkcji wielomianowej z wykorzystaniem współczynników przedziałowych.

- `error_code`: Wskaźnik na krótką liczbę całkowitą, który zostanie użyty do zwrócenia kodu błędu wskazującego na powodzenie lub niepowodzenie funkcji. Jeśli wskaźnik jest równy `nullptr`, zostanie wyświetlony komunikat o błędzie, a funkcja zwróci wartość NaN.

Zwraca przedział typu `interval_arithmetic::Interval<double>`, który reprezentuje miejsce zerowe funkcji uzyskane za pomocą metody bisekcji. Jeśli wystąpił błąd, wartość zwracana będzie zawierać NaN.

### Metoda solve

Metoda `solve` jest odpowiedzialna za implementację metody bisekcji w celu znalezienia miejsca zerowego funkcji wielomianowej z wykorzystaniem współczynników przedziałowych.

```cpp
interval_arithmetic::Interval<double> solve(short* error_code);
```

Parametry:
- `error_code`: Wskaźnik na zmienną typu `short`, który zostanie użyty do zwrócenia kodu błędu wskazującego na powodzenie lub niepowodzenie funkcji. Jeśli wartość wskaźnika to `nullptr`, zostanie wyświetlony komunikat o błędzie, a funkcja zwróci wartość NaN.

Zwracany typ:
- `interval_arithmetic::Interval<double>`: Przedział, który reprezentuje miejsce zerowe funkcji. Jeśli wystąpił błąd, wartość zwracana będzie zawierać NaN.

Opis:
Metoda `solve` implementuje kroki metody bisekcji w celu znalezienia miejsca zerowego funkcji wielomianowej w określonym przedziale. Algorytm dzieli przedział na pół i sprawdza, w którym połówce znajduje się miejsce zerowe. Następnie kontynuuje podział przedziału zawierającego miejsce zerowe, aż osiągnie pożądaną dokładność.

Algorytm metody bisekcji w skrócie:
1. Sprawdź czy wartości funkcji na końcach przedziału mają różne znaki. Jeśli nie, oznacza to brak miejsca zerowego w przedziale, zwróć NaN.
2. Dla każdej iteracji:
   - Podziel przedział na pół i oblicz wartość funkcji w środku przedziału.
   - Sprawdź znak wartości funkcji w środku przedziału.
   - Jeśli wartość funkcji w środku przedziału ma ten sam znak jak wartość na lewym końcu przedziału, przesuń lewą granicę przedziału do środka.
   - W przeciwnym przypadku, przesuń prawą granicę przedziału do środka.
   - Powtarzaj kroki powyżej, aż przedział osiągnie pożądaną dokładność (różnica między górnym i dolnym ograniczeniem przedziału jest mniejsza niż epsilon).

Jeśli wartość wskaźnika `error_code` nie jest równa `nullptr`, metoda solve przypisuje kod błędu do zmiennej wskazywanej przez ten wskaźnik, informując o powodzeniu lub niepowodzeniu funkcji.


```cpp
interval_arithmetic::Interval<double> BisectionInterval::solve(
    short* error_code) {
    // Sprawdzenie, czy error_code jest nullptr
    if (error_code == nullptr) {
        std::cout << "error_code is nullptr" << std::endl;
        return std::numeric_limits<interval_arithmetic::Interval<double>>::quiet_NaN();
    }

    // Sprawdzenie, czy coefficients jest pusty
    if (coefficients.empty()) {
        std::cout << "coefficients are empty" << std::endl;
        *error_code = 1;
        return std::numeric_limits<interval_arithmetic::Interval<double>>::quiet_NaN();
    }

    // Sprawdzenie, czy epsilon jest zerowe
    if (epsilon == 0) {
        std::cout << "epsilon is empty" << std::endl;
        *error_code = 2;
        return std::numeric_limits<interval_arithmetic::Interval<double>>::quiet_NaN();
    }
    
    
    // Sprawdzenie, czy f(a) lub f(b) przechodzi przez zero
    if (f(a).a * f(a).b < 0) {
        *error_code = 0;
        return a;
    }
    if (f(b).a * f(b).b < 0) {
        *error_code = 0;
        return b;
    }

    // Sprawdzenie, czy f(a) i f(b) mają przeciwne znaki
    std::string leftInv;
    std::string rightInv;
    f(a).IEndsToStrings(leftInv, rightInv);
    std::cout << "f(a) = [" << leftInv << " , " << rightInv << "]" << std::endl;
    f(b).IEndsToStrings(leftInv, rightInv);
    std::cout << "f(b) = [" << leftInv << " , " << rightInv << "]" << std::endl;

    if (f(a).a * f(b).a > 0) {
        std::cout << "f(a) and f(b) must have opposite signs" << std::endl;
        *error_code = 4;
        return std::numeric_limits<interval_arithmetic::Interval<double>>::quiet_NaN();
    }
    if (f(a).b * f(b).b > 0) {
        std::cout << "f(a) and f(b) must have opposite signs" << std::endl;
        *error_code = 4;
        return std::numeric_limits<interval_arithmetic::Interval<double>>::quiet_NaN();
    }

    // Metoda bisekcji
    long long iterations = 0;
    interval_arithmetic::Interval<double> inv0 = interval_arithmetic::Interval<double>(0, 0);
    interval_arithmetic::Interval<double> inv2 = interval_arithmetic::Interval<double>(2, 2);

    std::cout << "f(x) = ";
    for (int i = 0; i < this->coefficients.size() - 1; i++) {
        std::cout << "[" << this->coefficients[i].a << " , " << this->coefficients[i].b << "]"
                  << " * x^" << this->coefficients.size() - 1 - i << " + ";
    }
    std::cout << "[" << this->coefficients.back().a << " , " << this->coefficients.back().b << "]" << std::endl;

    interval_arithmetic

::Interval<double> c;
    interval_arithmetic::Interval<double> f_c;

    while (abs(b.a - a.a) > epsilon && abs(b.b - a.b) > epsilon) {
        c = (a + b) / inv2;
        iterations++;

        if (iterations > max_iterations) {
            std::cout << "max_iterations exceeded" << std::endl;
            *error_code = 55;
            return c;
        }

        f_c = f(c);

        if (f_c.a * f_c.b < 0) {
            *error_code = 0;
            return c;
        }

        if (f(a).b * f_c.a < 0) {
            b = c;
        } else {
            a = c;
        }
    }

    *error_code = 0;
    return (a + b) / inv2;
}
```

Metoda `solve()` wykonuje następujące kroki:

1. Sprawdza, czy `error_code` jest wskaźnikiem `nullptr`. Jeśli tak, wypisuje komunikat o błędzie i zwraca wartość NaN (`Not a Number`) typu `interval_arithmetic::Interval<double>`.
2. Sprawdza, czy wektor `coefficients` jest pusty. Jeśli tak, wypisuje komunikat o pustych współczynnikach, ustawia kod błędu na 1 i zwraca wartość NaN.
3. Sprawdza, czy `epsilon` jest zerem. Jeśli tak, wypisuje komunikat o pustym `epsilon`, ustawia kod błędu na 2 i zwraca wartość NaN.
4. Sprawdza, czy wartości funkcji `f(a)` i `f(b)` mają przeciwne znaki. Jeśli nie mają przeciwne znaki, wypisuje komunikat o konieczności posiadania przeciwnych znaków, ustawia kod błędu na 4 i zwraca wartość NaN.
5. Sprawdza, czy wartości funkcji `f(a)` lub `f(b)` przechodzą przez zero. Jeśli tak, ustawia kod błędu na 0 i zwraca wartość `a` lub `b` jako przybliżone miejsce zerowe funkcji.
6. Inicjalizuje zmienne i wyświetla funkcję `f(x)` na podstawie współczynników.
7. Rozpoczyna metodę bisekcji, która polega na podziale przedziału na pół i aktualizacji przedziału na podstawie znaku wartości funkcji.
8. Iteracyjnie dzieli przedział na połowę, oblicza wartość funkcji `f(c)` w punkcie środkowym i sprawdza, czy przechodzi przez zero.
9. Jeśli funkcja przechodzi przez zero, ustawia kod błędu na 0 i zwraca wartość `c` jako przybliżone miejsce zerowe.
10. Jeśli liczba iteracji przekracza maksymalną liczbę iteracji, wypisuje komunikat o przekroczeniu limitu iteracji, ustawia kod błędu na 55 i zwraca wartość `c`.
11. Po zakończeniu pętli, ustawia kod

 błędu na 0 i zwraca środek przedziału jako przybliżone miejsce zerowe funkcji.


### Metoda f

Metoda `f` jest używana przez metodę `solve` do obliczania wartości funkcji wielomianowej w danym punkcie.

```cpp
interval_arithmetic::Interval<double> f(interval_arithmetic::Interval<double> x);
```

Parametry:
- `x`: Przedział, dla którego obliczana jest wartość funkcji.

Zwracany typ:
- `interval_arithmetic::Interval<double>`: Pr

zedział, który reprezentuje wartość funkcji w danym przedziale.

Opis:
Metoda `f()` przyjmuje przedział `x` jako argument i oblicza wartość funkcji wielomianowej dla tego przedziału. Wykorzystuje ona współczynniki wielomianu oraz operacje arytmetyczne na przedziałach z biblioteki `interval_arithmetic`. Funkcja zwraca przedział, który reprezentuje wartość funkcji w danym przedziale.

Metoda `f()` wykonuje następujące kroki:

```cpp
interval_arithmetic::Interval<double> BisectionInterval::f(
	const interval_arithmetic::Interval<double> x) {
	interval_arithmetic::Interval<double> result =
		interval_arithmetic::Interval<double>(0, 0);
	for (int i = 0; i < coefficients.size(); i++) {
		long power = coefficients.size() - 1 - i;
		interval_arithmetic::Interval<double> coefficient = coefficients[i];

		interval_arithmetic::Interval<double> x_val;
		double x_minabs = std::min(abs(x.a), abs(x.b));
		double x_maxabs = std::max(abs(x.a), abs(x.b));

		if (power % 2) {
			x_val = interval_arithmetic::Interval<double>(
				double(pow(x.a, power)), double(pow(x.b, power)));
		} else {
			if (x.a < 0 && x.b > 0) {
				x_val = interval_arithmetic::Interval<double>(
					0, double(pow(x_maxabs, power)));
			} else {
				x_val = interval_arithmetic::Interval<double>(
					double(pow(x_minabs, power)), double(pow(x_maxabs, power)));
			}
		}
		result = result + (coefficient * x_val);
	}

	return result;
}

```

1. Inicjalizuje zmienną `result` jako pusty przedział o wartościach [0, 0]. Będzie to wynik funkcji `f(x)`.
2. Przechodzi przez wszystkie współczynniki `coefficients` funkcji, gdzie `i` jest indeksem aktualnego współczynnika.
3. Oblicza wykładnik `power` dla aktualnego współczynnika na podstawie jego pozycji w wektorze `coefficients`.
4. Pobiera aktualny współczynnik do zmiennej `coefficient`.
5. Oblicza przedział wartości `x_val` na podstawie argumentu `x` i wykładnika `power`.
6. Jeśli `power` jest nieparzysty, oblicza przedział `x_val` na podstawie potęgi argumentu `x` (x.a^power, x.b^power).
7. Jeśli `power` jest parzysty, sprawdza warunek:
   - Jeśli `x` obejmuje 0 (x.a < 0 i x.b > 0), oblicza przedział `x_val` od 0 do potęgi maksymalnej wartości bezwzględnej `x` (0, x_maxabs^power).
   - W przeciwnym przypadku oblicza przedział `x_val` od potęgi minimalnej wartości bezwzględnej `x` do potęgi maksymalnej wartości bezwzględnej `x` (x_minabs^power, x_maxabs^power).
8. Dodaje wynik mnożenia aktualnego współczynnika `coefficient` przez przedział `x_val` do zmiennej `result`.
9. Po przejściu przez wszystkie współczynniki, zwraca zmienną `result` jako wynik funkcji `f(x)`.


Wartości `x_minabs` i `x_maxabs` są obliczane na podstawie wartości bezwzględnej argumentu `x` w celu uwzględnienia różnych przypadków przy podnoszeniu przedziału do potęgi. Istnieją dwa główne powody, dla których stosuje się takie wartości bezwzględne:

1. **Bezpieczeństwo przedziałowe**: Stosowanie wartości bezwzględnej pozwala uniknąć niejednoznaczności w wyniku podnoszenia przedziału do potęgi, gdy przedział zawiera wartości ujemne. Bez wartości bezwzględnej, różne kombinacje wartości z przedziału mogłyby prowadzić do różnych wyników, co naruszałoby zasady bezpieczeństwa przedziałowego. Obliczanie `x_minabs` i `x_maxabs` umożliwia wybranie odpowiedniego zakresu dla podniesienia przedziału do potęgi, uwzględniając zarówno wartości dodatnie, jak i ujemne w przedziale.

2. **Zachowanie monotoniczności**: Przy podnoszeniu przedziału do potęgi, wartości bezwzględne są używane w celu zachowania monotoniczności funkcji. W przypadku parzystego wykładnika, wartości ujemne z przedziału `x` powinny być zamienione na wartość bezwzględną przed podniesieniem do potęgi, aby uniknąć utraty monotoniczności. Dzięki temu funkcja `f` zachowuje odpowiednią kolejność wartości i właściwości matematyczne, co jest istotne w algorytmie bisekcji i innych metodach rozwiązywania równań.

# Przykłady

## Przykład 1 - Przedziały Punktowe

### Dane wejściowe
```cpp
std::vector<double> coefficients = {1.0, -2.0, 1.0}; // x^2 - 2x + 1
double aLeft = 0.0;
double bLeft = 1.0;
double aRight = 0.0;
double bRight = 1.0; //a = 0, b = 1
double epsilon = 0.001;
long long max_iterations = 100;

BisectionInterval solver(coefficients, coefficients, aLeft, bLeft, aRight, bRight, epsilon, max_iterations);
```

### Wywołanie
```cpp
short error_code;
interval_arithmetic::Interval<double> root = solver.solve(&error_code);
```

### Wynik
```cpp
root = [9.9951171875E-1 , 9.9951171875E-1]
```
Wynik mieści się w marginesie błędu `epsilon` i jest poprawny.

## Przykład 2 - Przedziały
### Dane wejściowe
```cpp
std::vector<double> coefficientLeft = {0.999, -2.001, -1.001}; 
std::vector<double> coefficientRight = {1.001, -1.999, -0.999}; // x^2 - 2x - 1
double aLeft = 0.0;
double bLeft = 5.0;
double aRight = 0.0;
double bRight = 5.0; //a = 0, b = 1
double epsilon = 0.001;
long long max_iterations = 100;

BisectionInterval solver(coefficientLeft, coefficientRight, aLeft, bLeft, aRight, bRight, epsilon, max_iterations);
```

### Wywołanie
```cpp
short error_code;
interval_arithmetic::Interval<double> root = solver.solve(&error_code);
```

### Wynik
```cpp
 root = [2.412109375000000E+00 , 2.412109375000000E+00]
```
Wynik mieści się w marginesie błędu `epsilon` i jest poprawny.

## Przykład 3 - Przedziały (dane wejściowe powrawnym wynikiem)
### Dane wejściowe
```cpp
std::vector<double> coefficientLeft = {0.9, -2.1, 0.9}; 
std::vector<double> coefficientRight = {1.1, -1.9, 1.1}; // x^2 - 2x + 1
double aLeft = 0.0;
double bLeft = 1.0;
double aRight = 0.0;
double bRight = 1.0; //a = 0, b = 1
double epsilon = 0.001;
long long max_iterations = 100;

BisectionInterval solver(coefficientLeft, coefficientRight, aLeft, bLeft, aRight, bRight, epsilon, max_iterations);
```

### Wywołanie
```cpp
short error_code;
interval_arithmetic::Interval<double> root = solver.solve(&error_code);
```

### Wynik
```cpp
 root = [1.0E+0 , 1.0E+0]
```
Wynikiem jest prawy przedział początkowy b, ponieważ iloczyn dolenj i górnej granicy f(b) jest ujemny.
W związku z tym b znajduje się w przedziale wynikowym.
Wynik mieści się w marginesie błędu `epsilon` i jest poprawny.

## Przykład 4 - Przedziały (złe dane wejściowe)
### Dane wejściowe
```cpp
std::vector<double> coefficientLeft = {0.9, -2.1, 0.9};
std::vector<double> coefficientRight = {1.1, -1.9, 1.1}; // x^2 - 2x + 1
double aLeft = -2.0;
double bLeft = 0.0;
double aRight = -2.0;
double bRight = 0.0; //a = -2, b = 0
double epsilon = 0.001;
long long max_iterations = 100;

BisectionInterval solver(coefficientLeft, coefficientRight, aLeft, bLeft, aRight, bRight, epsilon, max_iterations);
```

### Wywołanie
```cpp
short error_code;
interval_arithmetic::Interval<double> root = solver.solve(&error_code);
```

### Wynik
Pierwiastek nie zostaje odnaleziony ponieważ f(a) i f(b) mają ten sam znak.\

## Przykład 5 - Przedziały (za duża ilość iteracji)
### Dane wejściowe
```cpp
std::vector<double> coefficientLeft = {0.9999, -2.0001, -1.0001};
std::vector<double> coefficientRight = {1.0001, -1.9999, -0.9999}; // x^2 - 2x - 1
double aLeft = 0.0;
double bLeft = 300.0;
double aRight = 0.0;
double bRight = 300.0; //a = 0, b = 300
double epsilon = 0.0000001;
long long max_iterations = 10;

BisectionInterval solver(coefficientLeft, coefficientRight, aLeft, bLeft, aRight, bRight, epsilon, max_iterations);
```

### Wywołanie
```cpp
short error_code;
interval_arithmetic::Interval<double> root = solver.solve(&error_code);
```

### Wynik
Pierwiastek nie zostaje odnaleziony ponieważ przekroczono maksymalną ilość iteracji.
Wyświetlona zostaje ostatnia znaleziona wartość:
```cpp
root = [2.490234375E0,2.490234375E0]
```

