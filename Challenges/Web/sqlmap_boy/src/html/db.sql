CREATE DATABASE IF NOT EXISTS moectf;

USE moectf;

CREATE TABLE IF NOT EXISTS `users` (
    `id` int(10) NOT NULL,
    `username` varchar(20) NOT NULL,
    `password` varchar(20) NOT NULL
) ENGINE=MyISAM  DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `articles` (
    `id` int(10) NOT NULL,
    `title` varchar(20) NOT NULL,
    `content` varchar(20) NOT NULL
) ENGINE=MyISAM  DEFAULT CHARSET=utf8;

CREATE TABLE IF NOT EXISTS `flag` (
    `flAg` varchar(255) NOT NULL
) ENGINE=MyISAM  DEFAULT CHARSET=utf8;

INSERT INTO `users` values(1,'admin','admin'),(2,'root','root'),(3,'hack','admin123');
INSERT INTO `articles` values(1,'我超','黑客！'),(2,'你好强','你好强'),(1032,'最高鸡密！','/var/www/html/1.png');