 <?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "manage_account";
$tbl_users = "users";
 
$mysqli = new mysqli($servername, $username, $password, $dbname);

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

$result = mysqli_query($conn, "SELECT max(id) FROM users");
$row = mysqli_fetch_array($result);

    
    $highest_id = $row[0];
    $new_id = $highest_id + 1;
	
	$password = "123456a*";
	$password_hash = password_hash($password, PASSWORD_DEFAULT);

$sql = "INSERT INTO " . $tbl_users . " (id, username, password)
VALUES (" . $new_id . ", 'tuanxu" .$new_id . "', '" . $password_hash ."')";

if ($conn->query($sql) === TRUE) {
  echo "New record created successfully";
} else {
  echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?> 