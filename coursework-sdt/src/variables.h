#ifndef VARIABLES_H
#define VARIABLES_H


#include <string>

#define LOGIN_SYSTEM_MESSAGE "Войти в систему."
#define REGISTER_MESSAGE "Зарегистрироваться."
#define PASSWORD_INPUT_MESSAGE "Введите пароль: "
#define LOGIN_INPUT_MESSAGE "Введите логин: "
#define DEFAULT_LOGIN "admin"
#define DEFAULT_PASSWORD "admin"
#define ACCOUNTS_FILENAME "accounts.dat"
//#define SALT_TEMPLATE "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
//#define LOGIN_TEMPLATE "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
//#define PASSWORD_TEMPLATE "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"
#define BLOCK_MESSAGE "Ваша учётная запись была заблокирована администратором."
#define LOG_OUT_MESSAGE "Выйти из аккаунта."
#define CLOSE_SYSTEM_MESSAGE "Завершить работу программы."
#define USE_ADMIN_PANEL_MESSAGE "Панель управления учётными записями."
#define USE_COMMON_USER_PANEL_MESSAGE "Панель управления данными."
#define BACK_MESSAGE "Назад."
#define SUCCESSFUL_ACCOUNT_REGISTRATION_MESSAGE "Аккаунт был успешно зарегистрирован. Ожидайте подтверждения от администратора."
#define REQUIREMENTS_FOR_LOGIN "Логин должен состоять из маленьких и больших латинских символов и цифр."
#define REQUIREMENTS_FOR_PASSWORD "Пароль состоять из маленьких и больших латинских символов и цифр."
#define INCORRECT_LOGIN_OR_PASSWORD_MESSAGE "Неверный логин или пароль."
#define SHOW_ALL_USERS "Вывести список всех пользователей."
#define ADD_NEW_USER "Добавить нового пользователя."
#define EDIT_USER "Редактировать пользователя."
#define DELETE_USER "Удалить пользователя."
#define CONFIRM_USERS_REGISTRATION "Подтверждение учётной записи пользователя."
#define BLOCK_USER "Заблокировать пользователя."
#define UNBLOCK_USER "Разблокировать пользователя."
#define INPUT_USER_LOGIN "Введите логин пользователя: "
#define WHAT_CHANGE "Что менять?"
#define LOGIN "Логин."
#define PASSWORD "Пароль."
#define ROLE "Роль."
#define SELECT_ROLE "Выберите роль:"
#define ADMIN "Администратор."
#define COMMON_USER "Обычный пользователь."
#define INPUT_USER_LOGIN_FOR_UNBLOCK "Введите логин пользователя для разблокировки: "
#define INPUT_USER_LOGIN_FOR_APPROVE "Введите логин пользователя для подтверждения: "
#define INPUT_USER_LOGIN_FOR_BLOCK "Введите логин пользователя для блокировки: "
#define INPUT_USER_LOGIN_FOR_ADMIN_ROOT "Введите логин пользователя для выдачи прав администратора: "
#define GIVE_ADMIN_ROOT "Выдать права администратора."
#define WELCOME_MESSAGE "Добро пожаловать в систему расчёта выпускаемой продукции!"
#define NOT_APPROVED_MESSAGE "Данный аккаунт ещё не подтверждён администратором."


const std::string SALT_TEMPLATE = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
const std::string LOGIN_TEMPLATE = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
const std::string PASSWORD_TEMPLATE = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

struct DataProperties {
    std::string employee_name;
    struct BirthDateProperties {
        int day;
        int month;
        int year;
    } child_birth_date;
    std::string child_name;
};

#endif
