#include <iostream>

#include <string>

#include <limits>

#include <cmath> // Для abs()

using namespace std;
// Константа для максимального розміру масиву (згідно з прикладом у методичці)
const int MAX_N = 100;
// --- Допоміжні функції (Введення/Виведення) ---
// Функція для введення коректного цілого числа з перевіркою
int input_int(const string & prompt) {
	int value;
	while(true) {
		cout << prompt;
		if(cin >> value) {
			// Перевірка на зайві символи у буфері не обов'язкова для базового вводу, 
			// але бажана для надійності.
			// Тут використовуємо спрощений варіант, як у прикладі, або з очисткою.
			return value;
		} else {
			cout << "Помилка! Будь ласка, введіть коректне ціле число." << endl;
			cin.clear();
			cin.ignore(numeric_limits < streamsize > ::max(), '\n');
		}
	}
}
// Функція для введення розміру масиву ( > 0 і <= MAX_N)
int input_size(const string & prompt) {
	int value;
	while(true) {
		value = input_int(prompt);
		if(value > 0 && value <= MAX_N) {
			return value;
		} else {
			cout << "Помилка! Розмір має бути від 1 до " << MAX_N << "." << endl;
		}
	}
}
// Функція для введення масиву
void input_array(int arr[], int & n) {
	n = input_size("Введіть кількість елементів (N): ");
	cout << "Введіть елементи масиву:" << endl;
	for(int i = 0; i < n; i++) {
		arr[i] = input_int("Елемент " + to_string(i + 1) + ": ");
	}
}
// Функція для виведення масиву
void output_array(const int arr[], int n) {
	cout << "Масив: ";
	for(int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
// --- Завдання 1: Array26 ---
// Дан цілочисельний масив розміру N. Перевірити, чи чергуються в ньому парні і непарні числа.
// Якщо чергуються, то вивести 0, якщо ні, то вивести порядковий номер першого елемента, що порушує закономірність.
// Функція обробки (повертає 0 або номер порушника)
int check_alternating_parity(const int arr[], int n) {
	// Проходимо з другого елемента
	for(int i = 1; i < n; i++) {
		// Перевіряємо парність поточного і попереднього
		// abs() потрібен для коректної роботи з від'ємними числами
		bool prev_even = (abs(arr[i - 1]) % 2 == 0);
		bool curr_even = (abs(arr[i]) % 2 == 0);
		// Якщо парність збігається, це порушення
		if(prev_even == curr_even) {
			return i + 1; // Повертаємо порядковий номер (індекс + 1)
		}
	}
	return 0; // Порушень немає
}
void task_array26() {
	cout << "\n--- Виконання Array26 (Чергування парності) ---" << endl;
	int arr[MAX_N];
	int n;
	input_array(arr, n);
	output_array(arr, n);
	int result = check_alternating_parity(arr, n);
	if(result == 0) {
		cout << "Результат: 0 (Числа чергуються)" << endl;
	} else {
		cout << "Результат: " << result << " (Порушення на елементі №" << result << ")" << endl;
	}
}
// --- Завдання 2: Array102 ---
// Дан масив розміру N і ціле число К (1 <= K <= N).
// Після елемента масиву з порядковим номером К вставити новий елемент з нульовим значенням.
// Функція модифікації масиву
void insert_zero_after_k(int arr[], int & n, int k) {
	if(n >= MAX_N) {
		cout << "Помилка: Масив переповнений, неможливо додати елемент." << endl;
		return;
	}
	// Індекс елемента з порядковим номером K - це (K - 1).
	// Ми вставляємо ПІСЛЯ нього, тобто на позицію індексу K.
	int insert_pos = k;
	// Зсуваємо елементи вправо, починаючи з останнього, щоб звільнити місце
	for(int i = n; i > insert_pos; i--) {
		arr[i] = arr[i - 1];
	}
	// Вставляємо 0
	arr[insert_pos] = 0;
	// Збільшуємо розмір масиву
	n++;
}
void task_array102() {
	cout << "\n--- Виконання Array102 (Вставка 0 після K) ---" << endl;
	int arr[MAX_N];
	int n;
	input_array(arr, n);
	// Введення K з перевіркою
	int k;
	while(true) {
		k = input_int("Введіть K (порядковий номер, 1 <= K <= " + to_string(n) + "): ");
		if(k >= 1 && k <= n) break;
		cout << "Помилка! K має бути в межах масиву." << endl;
	}
	cout << "Початковий ";
	output_array(arr, n);
	insert_zero_after_k(arr, n, k);
	cout << "Змінений ";
	output_array(arr, n);
}
// --- Головне меню ---
int main() {
	// Налаштування кодування консолі (опціонально, залежить від системи)
	// system("chcp 1251 > nul"); // Для Windows
	while(true) {
		cout << "\n================ МЕНЮ ================" << endl;
		cout << "1. Завдання Array26 (Чергування парності)" << endl;
		cout << "2. Завдання Array102 (Вставка 0 після K)" << endl;
		cout << "0. Вихід" << endl;
		cout << "======================================" << endl;
		int choice = input_int("Ваш вибір: ");
		switch(choice) {
			case 1:
				task_array26();
				break;
			case 2:
				task_array102();
				break;
			case 0:
				cout << "Роботу завершено." << endl;
				return 0;
			default:
				cout << "Невірний вибір. Спробуйте ще раз." << endl;
		}
	}
}