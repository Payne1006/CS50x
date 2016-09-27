<form action="buy.php" method="post">
    <div class="intro">
        <h5>
        Hello <?=$username?>, your cash balance is $<?=number_format($cash, 2, '.', ',')?>
        </h5>
        <br>
    </div>
    <fieldset>
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="symbol" placeholder="Symbol" type="text">
        </div>
        <div class="form-group">
            <input autocomplete="off" class="form-control" name="shares" placeholder="Shares" type="text">
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Buy Stocks
            </button>
        </div>
    </fieldset>
</form>
<div>
    or <a href="../index.php">Return Home</a>
</div>
