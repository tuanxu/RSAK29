<?php include('server.php') ?>
<?php
//echo "Study " . $_GET['subject'] . " at " . $_GET['web'];
ini_set('max_execution_time', 300); //300 seconds = 5 minutes
$task_from_client = $_GET['task_from_client'];
if($task_from_client == "receivedfromclient"){
	$username = $_GET['u'];
	$encrypted_message = $_GET['m'];
	$message = shell_exec("RSA.exe decrypt $encrypted_message");
	$response = "Get " . $message;
	$encrypted_response = shell_exec("RSA.exe encrypt $response");
	InsertChat($username,$message,$encrypted_message,$response,$encrypted_response);
	echo $encrypted_response;
}
else //init
{
	
	$answer = shell_exec("RSA.exe $task_from_client");
	echo $answer;
}
?>
