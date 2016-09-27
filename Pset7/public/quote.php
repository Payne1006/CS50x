<?php
    
    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }
    
    // user reaches page via POST (as by submitting a form via POST)
    else if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // Ensure stock was entered
        if(empty($_POST["symbol"]))
        {
            apologize("Oops!, no stock was entered!");
        }
        
        // Validate requested stock symbol, return symbol, name, price
        $stock = lookup($_POST["symbol"]);
        
        if($stock != true)
        {
            apologize("Invalid stock symbol!");
        }
        
        render("quote_display.php", ["title" =>"Quote", "symbol" => $stock["symbol"], "name" => $stock["name"], "price" => $stock["price"]]);
    } 
?>
