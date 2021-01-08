CREATE TABLE `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `username` varchar(100) NOT NULL,
  `email` varchar(100) NOT NULL,
  `password` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE `chats` (
  `id` int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `username` varchar(100) NOT NULL,
  `message` varchar(255) NOT NULL,
  `encrypted_message` text NOT NULL,
  `response` varchar(255) NOT NULL,
  `encrypted_response` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;