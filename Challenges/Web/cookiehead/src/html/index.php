<?php
$flag = "flag{this_is_a_fake_flag}";
error_reporting(0);
if(!isset($_COOKIE['login'])){
    setcookie('login','0');
    $_COOKIE['login'] = '0';
}

function getClientIP(){       
     if (array_key_exists('HTTP_X_FORWARDED_FOR', $_SERVER)){
            return  $_SERVER["HTTP_X_FORWARDED_FOR"];  
     }else if (array_key_exists('REMOTE_ADDR', $_SERVER)) { 
            return $_SERVER["REMOTE_ADDR"]; 
     }else if (array_key_exists('HTTP_CLIENT_IP', $_SERVER)) {
            return $_SERVER["HTTP_CLIENT_IP"]; 
     } 

     return '';
}

if($ip != '127.0.0.1'){
    die('<h1>仅限本地访问</h1>');
}


if($_COOKIE['login'] != '1'){
    die('<h1>请先登录</h1>');
}


if($_SERVER['HTTP_REFERER'] != 'http://127.0.0.1/index.php'){
    die('<h1>You are not from http://127.0.0.1/index.php !</h1>');
}


echo $flag;
