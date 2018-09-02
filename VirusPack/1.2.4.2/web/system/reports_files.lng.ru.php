<?php if(!defined('__CP__'))die();
define('LNG_REPORTS', 'Поиск в файлах');

define('LNG_REPORTS_FILESACTION',              'Действие над файлами:');
define('LNG_REPORTS_FILESACTION_REMOVE',       'Удалить');
define('LNG_REPORTS_FILESACTION_CREATEARC',    'Создать архив и скачать');
define('LNG_REPORTS_FILESACTION_REMOVE_EFILE', 'Не удалось удалить файл "%s".');
define('LNG_REPORTS_FILESACTION_REMOVE_EDIR',  'Не удалось удалить папку "%s".');
define('LNG_REPORTS_FILESACTION_Q',            'Вы дейcтвительно хотите совершить это дейтвие?');

//Фильтр.
define('LNG_REPORTS_FILTER_TITLE',   'Поиск');

define('LNG_REPORTS_FILTER_BOTS',    'Боты:');
define('LNG_REPORTS_FILTER_BOTNETS', 'Ботнеты:');
define('LNG_REPORTS_FILTER_MASK',    'Маска файлов:');
define('LNG_REPORTS_FILTER_QUERY',   'Строка поиска:');
define('LNG_REPORTS_FILTER_CS',      'С учетом регистра.');
define('LNG_REPORTS_FILTER_CURDIR',  'Только в текущей папки (включая подпапки).');
define('LNG_REPORTS_FILTER_RESET',   'Сброс формы');
define('LNG_REPORTS_FILTER_SUBMIT',  'Поиск');

define('LNG_REPORTS_RESULT',        'Результат:');
define('LNG_REPORTS_RESULT_BROWSE', 'Обзор:');

define('LNG_REPORTS_RESULT_ERROR',    'ОШИБКА!');
define('LNG_REPORTS_RESULT_ERRORDIR', 'Не удалось открыть папку!');
define('LNG_REPORTS_RESULT_EMPTYDIR', 'Папка пуста.');
define('LNG_REPORTS_RESULT_SEFILE',   'Не удалось открыть файл "%s".');
define('LNG_REPORTS_RESULT_SEDIR',    'Не удалось открыть папку "%s".');

define('LNG_REPORTS_LIST_DIR_TITLE', 'Папка:');
define('LNG_REPORTS_LIST_NAME',      'Имя');
define('LNG_REPORTS_LIST_SIZE',      'Размер (байты)');
define('LNG_REPORTS_LIST_MTIME',     'Время модификации');
define('LNG_REPORTS_LIST_UP',        '&lt;ВВЕРХ&gt;');
define('LNG_REPORTS_LIST_DIR',       '&lt;ПАПКА&gt;');
define('LNG_REPORTS_LIST_TOTAL',     'Всего %s файлов (%s байт) и %s папок.');
?>