<?php 
error_reporting(0);
session_start();
if(array_key_exists('login',$_SESSION)){
    if($_SESSION['login'] != '1'){
        die('我超嗨阔！');
    }
}else{
    die('我超嗨阔！');
}
$id = $_GET['id'];
$mysqli = new mysqli("localhost","root", "root", "moectf");
$sql = "select * from articles where id = '$id';";
$result = $mysqli->query($sql);
$data = mysqli_fetch_all($result);
$title = $data[0][1];
$content = $data[0][2];
function base64EncodeImage ($image_file) {
  $base64_image = '';
  $image_info = getimagesize($image_file);
  $image_data = fread(fopen($image_file, 'r'), filesize($image_file));
  $base64_image = 'data:' . $image_info['mime'] . ';base64,' . chunk_split(base64_encode($image_data));
  return $base64_image;
}
if($id != '1032'){
    echo "<h1>$title</h1>";
    echo "<p>$content</p>";
}else{
    echo "<h1>$title</h1>";
    echo "<img src='".base64EncodeImage($content)."'/>";

}
?>
