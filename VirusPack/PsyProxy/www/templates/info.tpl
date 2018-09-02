[ <a href="index.php">back to proxies list</a> ]<p>

<table>
<tr><td align='right'>total bot's:</td><td><b>{$btotal}</b></td></tr>
<tr><td align='right'>total not NAT'ed bot's:</td><td><b>{$notnated}</b></td></tr>
<tr><td align='right'>bot's per hour:</td><td><b>{$bhour}</b></td></tr>
<tr><td align='right'>bot's per day:</td><td><b>{$bday}</b></td></tr>
<tr><td align='right'>bot's for all time:</td><td><b>{$ball}</b></td></tr>
<tr><td colspan=2><b>statistic by builds</b></td></tr>
{section name=i loop=$builds}
<tr><td align='right'>{$builds[i].build_id}:</td><td><b>{$builds[i].cnt}</b></td></tr>
{/section}
{*
    <?
           foreach ($builds as $b)
                    echo "<tr><td align='right'>".htmlspecialchars($b['build']).":</td><td><b>{$b['cnt']}</b></td></tr>";
    ?>
*}
</table>
