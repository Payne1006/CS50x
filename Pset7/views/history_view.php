<div>
    <div class="intro">
        <h5>
            Transaction history for <?=$username?>'s account.
        </h5>
    </div>
    <table class="table table-striped">
        <thead>
            <tr>
                <th>Transaction</th>
                <th>Date/Time</th>
                <th>Symbol</th>
                <th>Shares</th>
                <th>Price</th>
            </tr>
        </thead>
        <tbody>
            <?php foreach($transactions as $transaction): ?>
            <tr>
                <td><?=$transaction["transaction"]?></td>
                <td><?=$transaction["timestamp"]?></td>
                <td><?=$transaction["symbol"]?></td>
                <td><?=$transaction["shares"]?></td>
                <td><?=$transaction["price"]?></td>
            </tr>
            
            <?php endforeach?>
        </tbody>
    </table>
    <div>
        <a href="../index.php">Return Home</a>
    </div>
</div>
