<?php
error_reporting(1);
session_start();
$_SESSION['login'] = '0';
$username = $_POST['username'];
$password = $_POST['password'];
$mysqli = new mysqli("localhost","root", "root", "moectf");
$sql = 'select username,password from users where username="'.$username.'" && password="'.$password.'";';
$result = $mysqli->query($sql);
$data = mysqli_fetch_all($result);
if(count($data) == 0){
    #set response in json
    $response = array(
        'code' => '0',
        'message' => '用户名或密码错误'
    );
    echo json_encode($response);
}else{
    $_SESSION['login'] = '1';
    $response = array(
        'code' => '1',
        'message' => '登录成功',
        'redirect' => 'secrets.php?id=1'
    );
    echo json_encode($response);
}

