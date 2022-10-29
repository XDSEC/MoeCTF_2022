<html>
<title>Here's a secret. Can you find it?</title>
<?php

if(isset($_GET['file'])){
    $file = $_GET['file'];
    include($file);
}else{
    highlight_file(__FILE__);
}
?>
</html>
