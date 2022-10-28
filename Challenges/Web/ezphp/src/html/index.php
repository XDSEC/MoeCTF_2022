<?php

highlight_file('source.txt');
echo "<br><br>";

$flag = 'moectf{Wa0g_Yi1g_Chu0}';
$giveme = 'can can need flag!';
$getout = 'No! flag.Try again. Come on!';

if(!isset($_GET['flag']) && !isset($_POST['flag'])){
	exit($giveme);
}

if($_POST['flag'] === 'flag' || $_GET['flag'] === 'flag'){
	exit($getout);
}

foreach ($_POST as $key => $value) {
	$$key = $value;
}


foreach ($_GET as $key => $value) {
	$$key = $$value;
}

echo 'the flag is : ' . $flag;

