<?php include('server.php') ?>
<!DOCTYPE html>
<html lang="en-US">
<head>
	<meta charset="UTF-8">
  <title>RSA Message</title>
  <link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
	<script src="BigInteger.min.js"></script>
	<script src="HandleMessage.js"></script>

  <div class="header">
  	<h2>RSA Message</h2>
  </div>
	
  <form>
	<?php include ('errors.php');

	if (isset($_SESSION['username'])) 
		echo "<script> glb_username ='" . $_SESSION['username'] . "'</script>";
	else 
		echo "<script> glb_username ='NotLogin'</script>";
	?>
	<!-- INIT RSA -->
	<div class="input-group">
  	  <button type="button" class="btn" onclick="InitRSA()">Init RSA</button>
  	</div>
	<div> <label id="lblInitRSA_Response"></label></div>

  
	<!-- GET PUBLIC KEY -->
	<div class="input-group">
  	  <button type="button" class="btn" onclick="GetPublicKey()">Get public key</button>
  	</div>
	<div>PublicKey:  <label id="lblGetPublicKey_Response"></label></div>
	<div>PublicKey_N:  <label id="lblGetPublicKey_N_Response"></label></div>
	<div>PublicKey_E:  <label id="lblGetPublicKey_E_Response"></label></div>
	
	<!-- GET PRIVATE KEY -->
	<div class="input-group">
  	  <button type="button" class="btn" onclick="GetPrivateKey()">Get Private key</button>
  	</div>
	<div>PrivateKey:  <label id="lblGetPrivateKey_Response"></label></div>
	<div>PrivateKey_N:  <label id="lblGetPrivateKey_N_Response"></label></div>
	<div>PrivateKey_E:  <label id="lblGetPrivateKey_E_Response"></label></div>
	<div>PrivateKey_D:  <label id="lblGetPrivateKey_D_Response"></label></div>
	
  	<div class="input-group">
  	  <label>Message need to send:</label>
  	  <input type="text"  id="txtMessage">
  	</div>
	
  	<div class="input-group">
  	  <button type="button" class="btn" onclick="EncryptMessageAndSend()">Encrypt Message And Send</button>
  	  <label>Encrypted message:</label>
  	  <label id="lblEncryptedMessage">.</label>
  	  <label>Response message from server:</label>
  	  <label id="lblResponseMessage">.</label>
  	  <label>Response message decrypted from server:</label>
  	  <label id="lblResponseMessageDecrypted">.</label>
  	</div>	
	
  	<p>
  		Go to users page? <a href="login.php">Sign in</a>
  	</p>
  </form>
</body>
</html>