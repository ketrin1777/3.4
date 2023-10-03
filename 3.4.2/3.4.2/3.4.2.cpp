// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


class Address
{
public:
    Address(std::string& city, std::string& street, int& num_home, int& num_apart)
    {
        city_ = city;
        street_ = street;
        num_home_ = num_home;
        num_apart_ = num_apart;
    }
    
    std::string get_output_address() { return city_ + ", " + street_ + ", " + std::to_string(num_home_) + ", " + std::to_string(num_apart_); }
    std::string get_city() { return city_; }


private:
    std::string city_, street_;
    int num_home_, num_apart_;
};

void sort(Address** addresses, int size) {
    // Сортировка массива пузырьком
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            char a = addresses[j]->get_city()[0];
            char b = addresses[j + 1]->get_city()[0];
            if (a > b) {
                // меняем элементы местами
                Address* temp = addresses[j];
                addresses[j] = addresses[j + 1];
                addresses[j + 1] = temp;
            }
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    std::fstream fin;
    fin.open("in.txt");

    if (!fin.is_open()) {
        std::cout << "File 'in.txt' not open!\n" << std::endl;
        return 0;
    }
    else {
        // получаем размер массива класса адресов
        int size_arr;
        fin >> size_arr;

        if (size_arr > 0)
        {
            Address** address = new Address * [size_arr];
            for (size_t i = 0; i < size_arr; i++)
            {
                std::string city, street;
                int num_home, num_apart;

                fin >> city;
                fin >> street;
                fin >> num_home;
                fin >> num_apart;

                // std::cout << city << ' ' << street << ' ' << num_home << ' ' << num_apart << std::endl;
                address[i] = new Address(city, street, num_home, num_apart);

            }
            sort(address, size_arr); // Сортируем масссив

            std::ofstream file_write("out.txt");

            file_write << size_arr << std::endl;

            for (size_t i = 0; i < size_arr; i++)
            {
                file_write << address[i]->get_output_address() << std::endl;
            }

            fin.close();

            for (size_t i = 0; i < size_arr; i++)
            {
                delete address[i];
            }
            delete[] address;
        }
    }
   // system("pause");
    return 0;
}
