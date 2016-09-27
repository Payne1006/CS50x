<?php
    
    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        //  Username and cash balance to be displayed in form
        $username = CS50::query("SELECT username FROM users WHERE id = ?", $_SESSION["id"]);
        $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        
        render("buy_form.php", ["title" => "Buy","username" =>$username[0]["username"],  "cash" => $cash[0]["cash"]]);
    }
    else if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //  Valid form entry
        if(empty($_POST["symbol"]) || empty($_POST["shares"]))
        {
            apologize("Please enter valid stock and shares");
        }
        
        // Shares is non-negative integer only
        if(!preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("Invalid number of shares");
        }
        
        // Validate stock choice, retrieve current info
        $stock = lookup($_POST["symbol"]);
        if(empty($stock))
        {
            apologize("No such stock!");
        }
        
        //  Verify user has enough cash
        $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $needed_cash = ($stock["price"] * $cash[0]["cash"]);
        if($cash < $needed_cash)
        {
            apologize("Not enough cash, please modify selection!");
        }
        
        // Update user portfolio, databases
        CS50::query("INSERT INTO portfolio (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], strtoupper($_POST["symbol"]), $_POST["shares"]);
        CS50::query("UPDATE users SET cash = cash - ?", ($stock["price"] * $_POST["shares"]));
        
        // Update history
        CS50::query("INSERT INTO history (user_id, transaction, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], "Buy", strtoupper($_POST["symbol"]), $_POST["shares"], $stock["price"]);
        
        redirect("../index.php");
    }
?>  
