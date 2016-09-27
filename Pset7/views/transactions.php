<div>
    <div class="intro">
        <h5>
        Hello <?=$username?>, your cash balance is $<?=number_format($cash, 2, '.', ',')?>
        </h5>
    </div>
    <table class="table table-striped">
        <thead>
            <tr>
                <th>Symbol</th>
                <th>Name</th>
                <th>Shares</th>
                <th>Price</th>
            </tr>
        </thead>
        <tbody>
            <?php foreach($positions as $position): ?>
            <tr>
                <td><?=$position["symbol"]?></td>
                <td><?=$position["name"]?></td>
                <td><?=$position["shares"]?></td>
                <td><?=$position["price"]?></td>
            </tr>
            <?php endforeach ?>
        </tbody>
    </table>
    <div>
        <p>Running low on funds? <a href="/deposit.php">Deposit more here.</a></p>
    </div>
</div>
