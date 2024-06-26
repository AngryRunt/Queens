#include <iostream>
#include <iomanip>
using namespace std;

// удобнее всего реализовать доску, как объект, тогда можно реализовать отдельно методы работы с доской.
class chessboard
{
private:
    int **fChessboard = NULL; // указатель на двумерный массив
    const size_t fSize = 8; // размер доски

    bool checkUp(const size_t i, const size_t j); // проверка вверх
    bool checkDown(const size_t i, const size_t j); // проверка вниз
    bool checkLeft(const size_t i, const size_t j); // проверка влеово
    bool checkRight(const size_t i, const size_t j); // проверка вправо
    bool checkUpLeft(const size_t i, const size_t j); // проверка вверх влево
    bool checkUpRight(const size_t i, const size_t j); // проверка вверх вправо
    bool checkDownLeft(const size_t i, const size_t j); // проверка вниз влево
    bool checkDownRight(const size_t i, const size_t j); // проверка вниз вправо

public:
    /// @brief Конструктор, который создаёт доску и заполняет её нулями.
    chessboard();
    /// @brief Деструктор последовательно уничтожает доску, освобождая память.
    ~chessboard();
    /// @brief Метод выводит доску на экран.
    void printChessboard();
    /// @brief Метод устанавливает ферзя на координаты
    /// @param  i горизонталь
    /// @param  j вертикаль
    void putQueen(const size_t, const size_t);
    /// @brief Метод удаляет ферзя с доски по координатам
    /// @param  i горизонталь
    /// @param  j фертикаль
    void removeQueen(const size_t, const size_t);
    /// @brief Метод возвращает размерность доски
    /// @return размерность доски
    size_t getSize();
    /// @brief Проверка валидности позиции.
    /// @param  i горизонталь
    /// @param  j вертикаль
    /// @return валидна ли позиция?
    bool isValidPos(const size_t, const size_t);
};

chessboard::chessboard()
{
    // Выделяем память для строк.
    fChessboard = new int* [fSize];
    // создаём строки и заполняем их нулями.
    for (size_t i = 0; i < fSize; i++)
    {
        fChessboard[i] = new int[fSize];
        for (size_t j = 0; j < fSize; j++)
        {
            fChessboard[i][j] = 0;
        }
    }
}

chessboard::~chessboard()
{
    // обходим все строки.
    for (size_t i = 0; i < fSize; i++)
    {
        // удаляем каждую строку
        delete[] fChessboard[i];
        fChessboard[i] = NULL;
    }
    // удаляем саму доску.
    delete[] fChessboard;
    fChessboard = NULL;
}

void chessboard::printChessboard()
{
    // задаём размер форматера для выравнивания.
    int formater = 3;
    // Выводим на экран строку с буквами.
    // Заполняем левый верхний угол чтобы буквы встали ровно над полями.
    cout << setw(formater) << " ";
    for (size_t i = 0; i < fSize; i++)
    {
        /*
         Таким способом добавляя к увиличивающейся на каждом шаге i
         букву 'a', точнее её код,
         можно получать следующие буквы.
        */
        cout << setw(3) << (char)(i + 'A');
    }
    cout << endl;
    for (size_t i = 0; i < fSize; i++)
    {
        // выводим в левом столбце номер строки.
        cout << setw(formater) << i + 1;
        // выводим значения ячеек
        for (size_t j = 0; j < fSize; j++)
        {
            cout << setw(formater) << fChessboard[i][j];
        }
        cout << endl;
    }
}

void chessboard::putQueen(const size_t i, const size_t j)
{
    // проверяем координаты на адекватность
    if ((i >= 0) && (i < fSize) &&
        (j >= 0 )&& (j < fSize))
    {
        // ставим единицу
        fChessboard[i][j] = 1;
    }
}

void chessboard::removeQueen(const size_t i, const size_t j)
{
    // проверяем координаты на адекватность
    if ((i >= 0) && (i < fSize) &&
        (j >= 0 )&& (j < fSize))
    {
        // ставим 0
        fChessboard[i][j] = 0;
    }
}

size_t chessboard::getSize()
{
    return fSize;
}

bool chessboard::isValidPos(const size_t i, const size_t j)
{
    // проверяем адекватность координат
    if ((i < 0) || (i >= fSize) ||
        (j < 0) || (j >= fSize))
    {
        return false;
    }

    // проверяем все направления
    // только если по всем направлением не будет атаки вернётся истина
    return checkUp(i, j) && checkDown(i, j) &&
           checkLeft(i, j) && checkRight(i, j) &&
           checkUpLeft(i, j) && checkUpRight(i, j) &&
           checkDownLeft(i, j) && checkDownRight(i, j);
}

bool chessboard::checkUp(const size_t i, const size_t j)
{
    // проверяем клетку на наличие ферзя.
    if (fChessboard[i][j])  //если по координатам ij лежит 1, значит там ферзь и на эту линию другого ферзя ставить нельзя
    {
        return false;
    }

// Если это не конец доски
    if (i != 0)
    {
        // Едем дальше
        return checkUp(i - 1, j);
    }

    return true;
}

bool chessboard::checkDown(const size_t i, const size_t j)
{
    if (fChessboard[i][j])
    {
        return false;
    }

    if (i != fSize - 1)
    {
        return checkDown(i + 1, j);
    }

    return true;
}

bool chessboard::checkLeft(const size_t i, const size_t j)
{
    if (fChessboard[i][j])
    {
        return false;
    }

    if (j != 0)
    {
        return checkLeft(i, j - 1);
    }

    return true;
}

bool chessboard::checkRight(const size_t i, const size_t j)
{
    if (fChessboard[i][j])
    {
        return false;
    }

    if (j != fSize - 1)
    {
        return checkRight(i, j + 1);
    }

    return true;
}

bool chessboard::checkUpLeft(const size_t i, const size_t j)
{
    if (fChessboard[i][j])
    {
        return false;
    }

    if ((i != 0) && (j != 0))
    {
        return checkUpLeft(i - 1, j - 1);
    }

    return true;
}

bool chessboard::checkUpRight(const size_t i, const size_t j)
{
    if (fChessboard[i][j])
    {
        return false;
    }

    if ((i != 0) && (j != fSize - 1))
    {
        return checkUpRight(i - 1, j + 1);
    }

    return true;
}

bool chessboard::checkDownLeft(const size_t i, const size_t j)
{
    if (fChessboard[i][j])
    {
        return false;
    }

    if ((i != fSize - 1) && (j != 0))
    {
        return checkDownLeft(i + 1, j - 1);
    }

    return true;
}

bool chessboard::checkDownRight(const size_t i, const size_t j)
{
    if (fChessboard[i][j])
    {
        return false;
    }

    if ((i != fSize - 1) && (j != fSize - 1))
    {
        return checkDownRight(i + 1, j + 1);
    }

    return true;
}

/// @brief Рекурсивная функция поиска решения
/// @param board Указатель на объект доски
/// @param cur_i Строка
/// @param cur_j Столбец
/// @param depth Глубина
/// @return Найдено или нет решение
bool Queens(chessboard *board, const size_t cur_i, const size_t cur_j, const int depth)
{
    // проверяем, достигнута ли глубина
    if (depth == 0)
    {
        // РЕшение найдено
        return true;
    }
// проверяем, валидны ли координаты и нет ли атаки
    if (!board->isValidPos(cur_i, cur_j))
    {
        // координаты не подходят
        return false;
    }

// Ставим фигуру
    board->putQueen(cur_i, cur_j);

// Флаг, означающий, найдено ли решение на последующих уровнях рекурсии
    bool flag = false;

// проверяем, не достигнут ли край доски?
    if ((cur_i) < board->getSize())
    {
        // получаем индекс следующей строки
        size_t next_i = cur_i + 1;
        // бегунок по столбцам
        size_t j = 0;
        // Повторяем действие пока не найдено решение и не  достигнут край доски
        while (!flag && (j < board->getSize()))
        {
            // Получаем флаг от следующих уровней рекурсии
            flag = Queens(board, next_i, j, depth - 1);
            // прирасчиваем счётчик
            j++;
        }
    }
// Если решение найдено передаём флаг дальше назад
    if (flag)
    {
        return flag;
    }
// Иначе удаляем ферзя
    board->removeQueen(cur_i, cur_j);

// передаём флаг назад
    return flag;
}

int main()
{
    chessboard *cb = new chessboard; // создаём доску по указателю
    int j = 0; // бегунок по клеткам перой строки
    // пока не найдено решение и не достигнут конец первой горизоантали
    while ((j < cb->getSize()) && !Queens(cb, 0, j, cb->getSize()))
    {
        // прирасчаем счётчик
        j++;
    }

    // выводим доску
    cb->printChessboard();
    cb->~chessboard();

    // Мы молодцы
    return 0;
}