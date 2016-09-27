<?php
    
    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // Determine which stocks the user owns
        $rows = CS50::query("SELECT symbol FROM portfolio WHERE user_id = ?", $_SESSION["id"]);
        
        if($rows != true)
        {
            apologize("Sorry, no stock to sell!");
        }
        
        $symbol = [];
        
        foreach($rows as $row)
        {
            $symbol[] = ["symbol" => $row["symbol"]];
        }
        
        // render sell form
        render("sell_form.php", ["title" => "Sell", "symbol" => $symbol]);
    }

    else if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // Retrieve current price and other stock info
        if(empty($_POST["symbol"]))
        {
            apologize("No stock symbol provided, invalid sale.");
        }
        
        // Retrieve correct number of shares from user's account
        $rows = CS50::query("SELECT shares FROM portfolio WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);

        // Update cash balance
        $current_stock = lookup($_POST["symbol"]);
        CS50::query("UPDATE users SET cash = cash + ? WHERE id =?", ($current_stock["price"] * $rows[0]["shares"]), $_SESSION["id"]);
        
        // Remove sold shared from user account
        CS50::query("DELETE FROM portfolio WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        // Update History
        CS50::query("INSERT INTO history (user_id, transaction, symbol, shares, price) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], "Sell", strtoupper($_POST["symbol"]), $rows[0]["shares"], $current_stock["price"]);

        
        redirect("../index.php");
    }
?>
