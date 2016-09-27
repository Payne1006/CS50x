<?php

    // configuration
    require("../includes/config.php"); 
    
    /*// Validate user credentials
    if($_SERVER["REQUEST_METHOD"] == "GET")
    {
        redirect("login.php");
    }
    
    // Known user, assemble portfolio via database access
    else if($_SERVER["REQUEST_METHOD"] == "POST")
    {*/
        // Select all stock symbols that the user owns
        $rows = CS50::query("SELECT symbol,shares FROM portfolio WHERE user_id = ?", $_SESSION["id"]);
    
        // Access username
        $username = CS50::query("SELECT username FROM users where id = ?", $_SESSION["id"]);
        
        // Create associative array
        $positions = [];
    
        // Assign values to associative array
        foreach($rows as $row)
        {
            $stock = lookup($row["symbol"]);
            if($stock !== false)
            {
                $positions [] = [
                
                "name"   => $stock["name"],
                "price"  => $stock["price"],
                "symbol" => $stock["symbol"],
                "shares" => $row["shares"],
                ];
            }
        }
    
    // Get cash balance
    $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);

    // render portfolio
    render("portfolio.php", ["username" => $username[0]["username"], "title" => "Portfolio", "positions" => $positions, "cash" => $cash[0]["cash"]]);
    
?>
