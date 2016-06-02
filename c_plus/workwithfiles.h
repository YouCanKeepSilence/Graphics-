#ifndef WORKWITHFILES_H
#define WORKWITHFILES_H
/*!

  \file
  \brief Загловочный файл содержащий классы работы с файлами

  class FormatFactory является абстрактным и используется только для наследования.
  */
#include "mainwindow.h"
#include "mydialogcurve.h"
class graph;

/*!
 * \brief The FormatFactory class
 *
 * Абстрактный класс от которого производится наследование форматов
 */
class FormatFactory
{

public:
    virtual ~FormatFactory(){}

    /*!
     * \brief Функция чтения первой прямой из файла
     *
     * Чисто виртуальная функция, уникальная для каждого класса наследника\n
     * см Txt::ReadOneFrom() и Doc::ReadOneFrom()
     * \param flag удачно ли было проведено чтение 1 - да 0 -нет
     * \param file ссылка на файл
     * \param FF промежуточный вектор с прямыми
     */
    virtual void ReadOneFrom(bool &flag, QFile &file,graph &FF)=0;
    /*!
     * \brief Функция дописывания одной прямой в конец
     *
     * Чисто виртуальная функция, уникальная для каждого класса наследника\n
     * см Txt::AppendTo() и Doc::AppendTo()
     * \param flag показатель записи 1 - записано 0 -нет
     * \param file ссылка на файл
     * \param FF ссылка на нужную прямую
     */
    virtual void AppendTo(bool &flag, QFile &file,graph &FF)=0;
    /*!
     * \brief Функция чтения всех прямых из файла
     *
     * Чисто виртуальная функция, уникальная для каждого класса наследника\n
     * см Txt::ReadFrom() и Doc::ReadFrom()
     * \param flag удачно ли было проведено чтение 1 - да 0 -нет
     * \param file ссылка на файл
     * \param FF промежуточный вектор с прямыми
     */
    virtual void ReadFrom(bool &flag, QFile &file,QVector <graph> &FF)=0;
    /*!
     * \brief Функция сохранения всех прямых
     *
     * Чисто виртуальная функция , уникальная для каждого класса наследника\n
     * см. Txt::SaveTo() и Doc::SaveTo()\n
     * \param flag определяет удачна ли была запись 1 - да 0 - нет
     * \param file ссылка на файл
     * \param FF все прямые для записи
     */
    virtual void SaveTo(bool &flag, QFile &file,QVector <graph> &FF)=0;

};
/*!
 * \brief Класс для работы с .txt форматом
 */

class Txt : public FormatFactory
{
    /*!
     * \brief Читает одну прямую из .txt формата
     *
     * \warning Прямые должны быть оформлены соответственно.\n
     * смотрите Txt::SaveTo();
     * \param flag удачно ли было проведено чтение 1 - да 0 -нет
     * \param file ссылка на файл
     * \param FF промежуточный вектор с прямыми
     */
    void ReadOneFrom(bool &flag, QFile &file,graph &FF);
    /*!
     * \brief Функция сохранения одной прямой в конец файла .txt
     *
     * \param flag показатель  1 - записано 0 -нет
     * \param file ссылка на файл
     * \param FF ссылка на нужную прямую
     */
    void AppendTo(bool &flag, QFile &file,graph &FF);
    /*!
     * \brief Читает все прямые из .txt формата
     *
     * \warning Прямые должны быть оформлены соответственно.\n
     * смотрите Txt::SaveTo();
     * \param flag удачно ли было проведено чтение 1 - да 0 -нет
     * \param file ссылка на файл
     * \param FF промежуточный вектор с прямыми
     */
    void ReadFrom(bool &flag, QFile &file,QVector <graph> &FF);
    /*!
     * \brief Функция сохранения в формат .txt
     *
     * \warning  установлен определнный порядок расположения данных,необходимый для чтения данных
     *  , а именно : \n
     * Имя прямой\n
     * Красный цвет\n
     * Зелеый цвет\n
     * Синий цвет\n
     * Толщина\n
     * Координата по x\n
     * Координата по y\n
     * \param flag определяет удачна ли была запись 1 - да 0 - нет
     * \param file ссылка на файл
     * \param FF все прямые для записи
     */
    void SaveTo(bool &flag, QFile &file,QVector <graph> &FF);
};
/*!
 * \brief Класс для работы с .doc форматом
 */
class Doc : public FormatFactory
{
    /*!
     * \brief Читает одну прямую из .doc формата
     *
     * \warning Прямые должны быть оформлены соответственно.\n
     * смотрите Doc::SaveTo();
     * \param flag удачно ли было проведено чтение 1 - да 0 -нет
     * \param file ссылка на файл
     * \param FF промежуточный вектор с прямыми
     */
    void ReadOneFrom(bool &flag, QFile &file,graph &FF);
    /*!
     * \brief Функция сохранения одной прямой в конец файла .doc
     *
     * \param flag показатель записи 1 - записано 0 -нет
     * \param file ссылка на файл
     * \param FF ссылка на нужную прямую
     */
    void AppendTo(bool &flag, QFile &file,graph &FF);
    /*!
     * \brief Читает все прямые из .doc формата
     *
     * \warning Прямые должны быть оформлены соответственно.\n
     * смотрите Doc::SaveTo();
     * \param flag удачно ли было проведено чтение 1 - да 0 -нет
     * \param file ссылка на файл
     * \param FF промежуточный вектор с прямыми
     */
    void ReadFrom(bool &flag, QFile &file,QVector <graph> &FF);
    /*!
     * \brief Функция сохранения в формат .doc
     *
     * \warning Важен определенный формат расположения , а именно : \n
     * Имя прямой 'TAB' Красный цвет 'TAB' Зеленый цвет 'TAB' Синий цвет 'TAB' Толщина\n
     * Координата x 'TAB' Координата y
     * \param flag определяет удачна ли была запись 1 - да 0 - нет
     * \param file ссылка на файл
     * \param FF все прямые для записи
     */
    void SaveTo(bool &flag, QFile &file,QVector <graph> &FF);
};

#endif // WORKWITHFILES_H
