<?php
    
    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // Empty username
        if(empty($_POST["username"]))
        {
            apologize("Invalid username");
        }
        
        // Empty password
        if(empty($_POST["password"]))
        {
            apologize("Invalid password");
        }
        
        // Password and Confirmation do not match
        if($_POST["password"] !== $_POST["confirmation"])
        {
            apologize("Password not confirmed!");
        }
        
        // Register user, test for unique username
        $rows = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
        
        if(count($rows) !== 1)
        {
            apologize("Username not available");
        }
        
        // Login user with newly created ID
        $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
        
        $_SESSION["id"] = $rows[0]["id"];
        
        redirect("../index.php");
    }

?>
