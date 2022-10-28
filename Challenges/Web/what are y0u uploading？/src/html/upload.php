<?php
header("Content-Type: text/html;charset=utf-8");
    if(isset($_POST["submit"]))
    {
    	if($_FILES['file']['type'] !== "image/jpeg" 
            && $_FILES['file']['type'] !== "image/png"
            && $_FILES['file']['type'] !== "image/gif" )
        {
            echo $_FILES['file']['type'];
            exit('文件上传类型错误');
    	}
        $name = $_FILES['file']['name'];
        echo "文件上传成功！filename：".$name;
        echo "<br>";
        if($name === 'f1ag.php'){
            echo "<br>".'moectf{A0_Qua1_D0ne!}';
            exit();
        }
        echo "我不想要这个特洛伊文件，给我一个f1ag.php  我就给你flag!";

        
        
    }
?>