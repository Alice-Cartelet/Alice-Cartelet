<?php 
	header('Content-type:text/html; charset=utf-8');
	session_start();
	$_SESSION = array();
	session_destroy();
	setcookie('username', '', time()-99);
	setcookie('code', '', time()-99);
    header("Location: index.php"); 
 
 ?>