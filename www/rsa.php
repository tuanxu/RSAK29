
<?php
//echo "Study " . $_GET['subject'] . " at " . $_GET['web'];
ini_set('max_execution_time', 300); //300 seconds = 5 minutes
$task_from_client = $_GET['task_from_client'];
$m = $_GET['m'];
if($task_from_client == "receivedfromclient"){
	$answer = shell_exec("RSA.exe decrypt $m");
	echo $answer;
}
else
{
	
	$answer = shell_exec("RSA.exe $task_from_client $m");
	echo $answer;
}
?>
