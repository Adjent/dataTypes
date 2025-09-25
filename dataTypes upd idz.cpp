#include <iostream>
#include <limits>
using namespace std;

union UniversalType { //объединение для хранения разных типов, необходимо для преобразования float/double в	
	float f;
	unsigned int u;
	double d;
	unsigned long long ul;
};

template <typename T>//шаблон для безопасного ввода различных типов
void SafeInput(T& var) {
	while (!(cin >> var)) {
		cout << "Некорректный ввод. Попробуйте еще раз: ";
		cin.clear();//сброс ошибки ввода
		cin.ignore(numeric_limits<streamsize>::max(), '\n');//очистка буфера ввода | numeric_limits<streamsize>::max() указывает максимальное кол-во символов, которые следует игнорировать
	}
}

void TypesMemorySize() {
	cout << "Отведенный объем памяти под различные типы данных:\nint: " << sizeof(int) << " байт\nshort int: " << sizeof(short int) << " байт\nlong int: " << sizeof(long int) << " байт\nfloat: " << sizeof(float) << " байт\ndouble: " << sizeof(double) << " байт\nlong double: " << sizeof(long double) << " байт\nchar: " << sizeof(char) << " байт\nbool: " << sizeof(bool) << " байт\n";
	cout << "\n";
}

void IntInMemory(int valueInt) {
	unsigned int mask = 1;
	unsigned short slots = sizeof(valueInt) * 8;
	mask <<= slots - 1;
	cout << "S | 1 byte  | 2 byte   | 3 byte   | 4 byte   |\n";
	cout << "----------------------------------------------\n";
	for (int i = 1; i <= slots; i++) {
		cout << (valueInt & mask ? '1' : '0');
		mask >>= 1;
		if (i % 8 == 0 && i != slots) {
			cout << " | ";
		}
		if (i == 1) {
			cout << " | ";
		}
	}
	cout << "\n\n";
}

void FloatInMemory(float valueFloat) {
	UniversalType generalVar;
	generalVar.f = valueFloat;
	unsigned int mask = 1;
	unsigned short slots = sizeof(valueFloat) * 8;
	mask <<= slots - 1;
	cout << "S | Exponent | Mantissa\n";
	cout << "--------------------------------------\n";
	for (int i = 1; i <= slots; i++) {
		cout << (generalVar.u & mask ? '1' : '0');
		mask >>= 1;
		if (i == 1) {
			cout << " | ";
		}
		if (i == 9) {
			cout << " | ";
		}
	}
	cout << "\n\n";
}

void DoubleInMemory(double valueDouble) {
	UniversalType generalVar;
	unsigned long long mask = 1;
	unsigned short slots = sizeof(valueDouble) * 8;
	generalVar.d = valueDouble;
	mask <<= slots - 1;
	cout << "S | Exponent    | Mantissa\n";
	cout << "----------------------------------------------------------------------\n";
	for (int i = 1; i <= slots; i++) {
		cout << (generalVar.ul & mask ? '1' : '0');
		mask >>= 1;
		if (i == 1) {
			cout << " | ";
		}
		if (i == 12) {
			cout << " | ";
		}
	}
	cout << "\n\n";
}

template <typename T>//шаблон чтобы не дублировать код замены бита для разных типов данных
void ChangeBits(T& value, unsigned short slots) {
	unsigned long long changeMask = 1;
	unsigned short changer, changeNumber;
	cout << "Введите порядковый номер бита который хотите заменить: ";
	do {
		SafeInput(changeNumber);
		if (changeNumber > slots || changeNumber < 1) {
			cout << "Некорректный ввод. Попробуйте еще раз: ";
		}
	} while (changeNumber > slots || changeNumber < 1);
	changeMask <<= (slots - changeNumber);
	cout << "Введите на что хотите заменить бит, на 1 или 0: ";
	do {
		SafeInput(changer);
		if (changer != 0 && changer != 1) {
			cout << "Некорректный ввод. Попробуйте еще раз: ";
		}
	} while (changer != 0 && changer != 1);
	if (changer == 1) {
		value |= changeMask;
	}
	else {
		changeMask = ~changeMask;
		value &= changeMask;
	}
}

int main() {
	UniversalType generalVar;
	int valueInt, minDouble = 1;
	float valueFloat;
	double valueDouble;
	unsigned short menuChoice, changeChoice;
	setlocale(0, "");
	for (;;) {
		cout << "Доступные действия:\n1 - Вывести объем памяти, отведенный под различные типы данных\n2 - Вывести представление целого числа int в памяти\n3 - Вывести представление числа c плавающей точкой float в памяти\n4 - Вывести представление числа c плавающей точкой double в памяти\n5 - Сконструировать и вывести на экран минимальное положительное денормализованное число типа и double\n0 - Выход из программы\n\nВыберите пункт меню: ";
		SafeInput(menuChoice);
		switch (menuChoice) {
		case 1:   //объем памяти под типы
			TypesMemorySize();
			break;
		case 2:   //предствавление int в памяти
			cout << "Введите целое число: ";
			SafeInput(valueInt);
			IntInMemory(valueInt);
			cout << "Хотите заменить бит в числе? (Да - 1 | Нет - 0): ";
			do {
				SafeInput(changeChoice);
				if (changeChoice != 0 && changeChoice != 1) {
					cout << "Некорректный ввод. Попробуйте еще раз: ";
				}
			} while (changeChoice != 0 && changeChoice != 1);
			if (changeChoice == 1) {
				ChangeBits(valueInt, sizeof(valueInt) * 8);
				cout << "\nНовое значение числа и его представление в памяти: " << valueInt << "\n";
				IntInMemory(valueInt);
			}
			cout << "\n";
			break;
		case 3:   //представление float в памяти
			cout << "Введите вещественное число тип float: ";
			SafeInput(valueFloat);
			FloatInMemory(valueFloat);
			cout << "Хотите заменить бит в числе? (Да - 1 | Нет - 0): ";
			do {
				SafeInput(changeChoice);
				if (changeChoice != 0 && changeChoice != 1) {
					cout << "Некорректный ввод. Попробуйте еще раз: ";
				}
			} while (changeChoice != 0 && changeChoice != 1);
			generalVar.f = valueFloat;
			if (changeChoice == 1) {
				ChangeBits(generalVar.u, sizeof(valueFloat) * 8);
				cout << "\nНовое значение числа и его представление в памяти: " << generalVar.f << "\n";
				FloatInMemory(generalVar.f);
			}
			cout << "\n";
			break;
		case 4:   //представление double в памяти
			cout << "Введите вещественное число тип double: ";
			SafeInput(valueDouble);
			DoubleInMemory(valueDouble);
			cout << "Хотите заменить бит в числе? (Да - 1 | Нет - 0): ";
			do {
				SafeInput(changeChoice);
				if (changeChoice != 0 && changeChoice != 1) {
					cout << "Некорректный ввод. Попробуйте еще раз: ";
				}
			} while (changeChoice != 0 && changeChoice != 1);
			generalVar.d = valueDouble;
			if (changeChoice == 1) {
				ChangeBits(generalVar.ul, sizeof(valueDouble) * 8);
				cout << "\nНовое значение числа и его представление в памяти: " << generalVar.d << "\n";
				DoubleInMemory(generalVar.d);
			}
			cout << "\n";
			break;
		case 5:
			generalVar.d = 0;
			generalVar.ul |= minDouble;
			cout << "Минимальное положительное денормализованное число типа double и его представление в памяти: " << generalVar.d << "\n";
			DoubleInMemory(generalVar.d);
			cout << "\n";
			break;
		case 0:   //выход из программы
			return 0;
		default:
			cout << "Данная операция не предусмотрена. Выберите другую. \n\n";
			break;
		}
	}
	return 0;
}