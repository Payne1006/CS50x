<?php

    // Configuration
    require("../includes/config.php");
    
    $username = CS50::query("SELECT username FROM users WHERE id = ?", $_SESSION["id"]);
    
    $history = CS50::query("SELECT * FROM history WHERE user_id = ?", $_SESSION["id"]);

    $transactions = [];
    
    foreach($history as $histories)
    {
        $transactions [] = [
            
            "transaction" => $histories["transaction"],
            "timestamp"   => date("d-m-y h:i:s", strtotime($histories["date/time"])),
            "symbol"      => $histories["symbol"],    
            "shares"      => $histories["shares"],
            "price"       => number_format($histories["price"], 2, '.', ','),
            ];
    }
    render("history_view.php", ["title" => "History", "username" => $username[0]["username"], "transactions" => $transactions]);
?>
