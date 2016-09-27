<form action="sell.php" method="post">
    <div class="intro">
        <h5>
            Please select a stock to sell:
        </h5>
    </div>
    <div class="select">
    <select name="symbol">
        <option value=" ">&nbsp;</option>
        <?php foreach($symbol as $symbols): ?>
        <option value="<?=$symbols['symbol']?>"><?=strtoupper($symbols["symbol"])?></option>
        <?php endforeach ?>
    </select>
    </div>
    <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Sell 
            </button>
        </div>
</form>
<div>
    or <a href="../index.php">Return Home </a>
</div>
