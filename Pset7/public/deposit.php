<?php

    // Configuration
    require("../includes/config.php");
    
    if($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("deposit_form.php", ["title" => "Deposit"]);
    }
    else if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if(empty($_POST["deposit"]) || (!preg_match("/^\d+$/", $_POST["deposit"])))
        {
            apologize("Please enter a valid amount");
        }
        
        CS50::query("UPDATE users SET cash = cash + ?", $_POST["deposit"]);
        CS50::query("INSERT INTO history (user_id, transaction, symbol, price) VALUES(?, ?, ?, ?)", $_SESSION["id"], "FUND", "", $_POST["deposit"]);
        
        redirect("../index.php");
    }
?>
