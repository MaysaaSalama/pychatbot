 <?php

// Program: chatScriptClient.php
// Copyright (c) 2012 R. Wade Schuette
// Function -- a working skeleton of a client to the ChatScript Server
// NOTES:   Be sure to put in your correct host, port, username, and bot name below !

//     Be sure to to change the file suffix to php instead of txt

// Credits:  This program is derived from a sample client script by Alejandro Gervasio
//   posted here:  www dot devshed dot com/c/a/PHP/An-Introduction-to-Sockets-in-PHP/ 

// The legalese is shamelessly copied from Bruce Wilcox's chatscript file header.

// Caveats:   This worked for me, but has no real error handling  
//            There's no way to deal with a gambit PUSHED by the server.



// LEGAL STUFF:
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, or sell
// copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//*********************************************************************************/
// Revisions
// Nov 3,2012 -- tested this and it seems to work correctly for me(rws)





//  =============  user values ====
$host = "5.31.6.5";  //  <<<<<<<<<<<<<<<<< YOUR CHATSCRIPT SERVER IP ADDRESS GOES HERE 
$port = 1024;     // <<<<<<< your portnumber if different from 1024
$bot  = "";  // <<<<<<< desired botname, or "" for default bot
$null = "\x00";
$botprefix = "Rose: ";
$userprefix = "You: ";
//=========================
// Note - the top part (PHP) is skipped on the first display of this form, but fires on each loop after that.

if($_POST['send']){
    // open client connection to TCP server
    //  echo "<p> Here goes </p>";
   $userip = ($_SERVER['X_FORWARDED_FOR']) ? $_SERVER['X_FORWARDED_FOR'] : $_SERVER['REMOTE_ADDR']; // get actual ip address of user as his id

    $msg=$_POST['message'];
    $message = $userip.$null.$bot.$null.$msg.$null;
    echo '<h2>'.$userprefix.$msg.'</h2>';
  
    // fifth parameter in fsockopen is timeout in seconds
    if(!$fp=fsockopen($host,$port,$errstr,$errno,300))
    {
        trigger_error('Error opening socket',E_USER_ERROR);
    }
    
    fputs($fp,$message); // write message to socket server
    while (!feof($fp))
	{
        $ret.= fgets($fp, 128);
      }
      

    // $ret=fgets($fp,$port); // get server response
    
    fclose($fp); // close socket connection
    
   //  echo "Chatbot $bot replied to $user:";
    echo '<h2>'.$botprefix.$ret.'</h2>';
}
?>
<!DOCTYPE HTML>
<html>
  <head>
    <title>
      CHATSCRIPT SERVER
    </title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  </head>
  <body onload="document.getElementById('message').focus()">
    <form action="<?php echo $_SERVER['PHP_SELF'] ?>" method="post">
    <p>
      Enter your message below:
    </p>
    <table>
      <tr>
        <td>Name:</td>
        <td><input type="text" name="user" size="20" value="<?php echo $user ?>" /></td>
      </tr>
      <tr>
        <td>Message:</td>
        <td><input type="text" name="message" id="message" size="70" /></td>
      </tr>
      <tr>
        <td colspan="2"><input type="submit" name="send" value="Send Value" /></td>
      </tr>
    </table>
    </form>
<?php echo $output ?>
  </body>
</html>
