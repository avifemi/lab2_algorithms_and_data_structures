#include <iostream>
#include <vector>
#include <functional> //для компаратора
using namespace std;

template <typename T>
bool decreasing(T a, T b) // компаратор для убывания
{
    return a >= b;
}

template <typename T>
bool increasing(T a, T b) // компаратор для возрастания
{
    return a <= b;
}

template <typename T>
class sorting_algorithms // наш абстрактный класс
{
public:
    virtual void sort(std::vector<T>& vec, std::function<bool(const T&, const T&)> comparator) = 0;
    virtual ~sorting_algorithms() = default;
    virtual void print(std::vector<T>& vec) = 0;
};

template <typename T>
class sorting_by_counting : public sorting_algorithms<T> //сортировка подсчетом
{
private:
    std::vector<T> vec;

public:
    void sort(std::vector<T>& vec, std::function<bool(const T&, const T&)> comparator) override
        {
            std::vector<int> count(vec.size(), 0); //шаг C1 

            for(int i = vec.size()-1; i >= 1; i--) //шаг C2
            {
                for(int j = i-1; j >= 0 ; j--) //шаг C3
                {
                    if(comparator(vec[i], vec[j])) //шаг C4
                    {
                        count[j]++;
                    }
                    else
                    {
                        count[i]++;
                    }
                }
            }

            std::vector<T> sort_vec(vec.size());
            for(int i = 0; i < vec.size(); i++)
            {
                sort_vec[count[i]] = vec[i];
            }

            vec = std::move(sort_vec);
        }
    void print(std::vector<T>& vec) override
    {
        std::cout<<"{ ";
        for(int i = 0; i < vec.size(); i++)
        {
            std::cout<< vec[i]<< " ";
        }
        std::cout<<"}";
    }
    sorting_by_counting(const sorting_by_counting& other) : vec(other.vec) {} // конструктор копий
    sorting_by_counting(std::vector<T> vek):vec(vek){}; //конструктор с инициализацией

    sorting_by_counting& operator=(const sorting_by_counting& other) // оператор присваивания
    {
        if (this != &other)
        {
            vec = other.vec;
        }
        return *this;
    }

    sorting_by_counting(sorting_by_counting&& other) noexcept : vec(std::move(other.vec)) {} // конструктор перемещения

    sorting_by_counting& operator=(sorting_by_counting&& other) noexcept // присваивание перемещением
    {
        if (this != &other)
        {
            vec = std::move(other.vec);
        }
        return *this;
    }
};

template <typename T>
class sorting_by_inserts : public sorting_algorithms<T> //сортировка вставками
{
    private:
        std::vector<T> vec;
    public:
        void sort(std::vector<T> &vec, std::function<bool(const T&, const T&)> comparator) override
        {
            for(int j = 1; j<vec.size(); j++) //шаг S1
            {
                int i = j-1; //шаг S2
                T K = vec[j];
                T R = vec[j];
                while(i >= 0 && !comparator(vec[i], K)) //шаг S3
                {
                    vec[i+1] = vec[i]; //шаг S4
                    i = i - 1;
                }
                vec[i+1] = K; //шаг S5
            }
        }
        void print(std::vector<T>& vec) override
        {
            std::cout<<"{ ";
            for(int i = 0; i < vec.size(); i++)
            {
                std::cout<< vec[i]<< " ";
            }
            std::cout<<"}";
        }
        sorting_by_inserts(const sorting_by_inserts& other) : vec(other.vec) {} // конструктор копий
        sorting_by_inserts(std::vector<T> vek):vec(vek){}; //конструктор с инициализацией

        sorting_by_inserts& operator=(const sorting_by_inserts& other) // оператор присваивания
        {
            if (this != &other)
            {
                vec = other.vec;
            }
            return *this;
        }

        sorting_by_inserts(sorting_by_inserts&& other) noexcept : vec(std::move(other.vec)) {} // конструктор перемещения

        sorting_by_inserts& operator=(sorting_by_inserts&& other) noexcept // присваивание перемещением
        {
            if (this != &other)
            {
                vec = std::move(other.vec);
            }
            return *this;
        }
};

template <typename T>
class sorting_by_choice : public sorting_algorithms<T> //сортировка выбором
{
private:
    std::vector<T> vec;

public:
    T search_max(std::vector<T>& vec, int j, std::function<bool(const T&, const T&)> comparator) //поиск мин/макс элемента в зависимости от компаратора
    {
        T max_ = vec[0];
        for(int i = 0; i <= j; i++)
        {
            if(comparator(max_, vec[i]))
            {
                max_ = vec[i];
            }
        }
        return max_;
    }
    void sort(std::vector<T>& vec, std::function<bool(const T&, const T&)> comparator) override
        {
            for(int j = vec.size()-1; j>=1; j--) //шаг S1
            {
                T m = search_max(vec, j, comparator); //шаг S2
                int one = 0;
                for(int i = vec.size()-1; i>=0; i--)
                {
                    if(vec[i] == m && one == 0)
                    {
                        vec[i] = vec[j]; //шаг S3
                        vec[j] = m;
                        one++;
                    }
                }
            }
        }
    void print(std::vector<T>& vec) override
    {
        std::cout<<"{ ";
        for(int i = 0; i < vec.size(); i++)
        {
            std::cout<< vec[i]<< " ";
        }
        std::cout<<"}";
    }
    sorting_by_choice(const sorting_by_choice& other) : vec(other.vec) {} // конструктор копий
    sorting_by_choice(std::vector<T> vek):vec(vek){}; //конструктор с инициализацией

    sorting_by_choice& operator=(const sorting_by_choice& other) // оператор присваивания
    {
        if (this != &other)
        {
            vec = other.vec;
        }
        return *this;
    }

    sorting_by_choice(sorting_by_choice&& other) noexcept : vec(std::move(other.vec)) {} // конструктор перемещения

    sorting_by_choice& operator=(sorting_by_choice&& other) noexcept // присваивание перемещением
    {
        if (this != &other)
        {
            vec = std::move(other.vec);
        }
        return *this;
    }
};

template <typename T>
class sorting_by_the_Shell_method : public sorting_algorithms<T> //сортировка методом Шелла
{
private:
    std::vector<T> vec;

public:
    void sort(std::vector<T>& vec, std::function<bool(const T&, const T&)> comparator) override
    {
        for(int step = vec.size()/2; step > 0; step /= 2) //шаги D1-D2
        {
            for(int j = 1; j<vec.size(); j++)
            {
                int i = j-step; //шаг D3
                T K = vec[j];
                T R = vec[j];
                while(i >= 0 && !comparator(vec[i], K)) //шаг D4
                {
                    vec[i+step] = vec[i]; //шаг D5
                    i = i - step;
                }
                vec[i+step] = K; //шаг D6
            }
        }
    }
    void print(std::vector<T>& vec) override
    {
        std::cout<<"{ ";
        for(int i = 0; i < vec.size(); i++)
        {
            std::cout<< vec[i]<< " ";
        }
        std::cout<<"}";
    }
    sorting_by_the_Shell_method(const sorting_by_the_Shell_method& other) : vec(other.vec) {} // конструктор копий
    sorting_by_the_Shell_method(std::vector<T> vek):vec(vek){}; //конструктор с инициализацией

    sorting_by_the_Shell_method& operator=(const sorting_by_the_Shell_method& other) // оператор присваивания
    {
        if (this != &other)
        {
            vec = other.vec;
        }
        return *this;
    }

    sorting_by_the_Shell_method(sorting_by_the_Shell_method&& other) noexcept : vec(std::move(other.vec)) {} // конструктор перемещения

    sorting_by_the_Shell_method& operator=(sorting_by_the_Shell_method&& other) noexcept // присваивание перемещением
    {
        if (this != &other)
        {
            vec = std::move(other.vec);
        }
        return *this;
    }
};

int main()
{
    vector<int> numbers = {4, 2, 1, 5, 3};
    sorting_by_the_Shell_method<int> sorter(numbers);
    sorter.sort(numbers, decreasing<int>);
    sorter.print(numbers);

    return 0;
}