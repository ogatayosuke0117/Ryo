# 動作確認
## 実行手順
1. example/docker-compose.yml を使用して iroha を起動する
2. sample.py を実行する

## 動作確認内容
* アカウント作成
    * Irohaアカウント「user」を作成
    * Irohaアカウント「store」を作成し、ロール「store」を付与

* レジ追加
    * 「store」アカウントに署名を追加

* レジ削除
    * 「store」アカウントから署名を削除（-> 削除後、再度署名を追加する）

* チャージ
    * ユーザ が レジA で 1000円分 チャージ
        * 「system」アカウントで通貨を 1000 発行
        * 「system」から「store」に通貨を 1000 送金
        * 「store」から「user」に通貨を 1000 送金

    * ユーザ が レジB で 2000円分 チャージ
        * 「system」アカウントで通貨を 2000 発行
        * 「system」から「store」に通貨を 2000 送金
        * 「store」から「user」に通貨を 2000 送金

* 支払い
    * ユーザ が 店舗 に 500円分 支払いをする

* 決済
    * 店舗 の持つ通貨 100円分 を決済する
        * 「store」アカウントから「admin」に通貨を 100 送金

* 残高照会
    * ユーザ および 店舗 の残高を表示する  
    ⇒ 「user」の残高は 2500 となる  
    ⇒ 「store」の残高は 400 となる 

* 取引履歴閲覧
    * ユーザの取引履歴を表示する
    * 店舗のレジごと取引履歴を表示する
    * 管理者用に全取引履歴を表示する

## サンプルプログラム実行結果
```console
--- [ Create account ] ---
Create account 'user' ... OK
Create account 'store' ... OK
--- [ Add register ] ---
Add signatory to 'store' account ... OK
        Added signatory is '5406fd232088d5447ad6517943d016e44186375fee116f72908a472955a63006'
--- [ Remove register ] ---
Remove signatory from 'store' account ... OK
        Removed signatory is '5406fd232088d5447ad6517943d016e44186375fee116f72908a472955a63006'
Re-add signatory for later operations ... OK
--- [ Charge ] ---
Charge to 'user' by register01 (amount: 1000) ... OK
Charge to 'user' by register02 (amount: 2000) ... OK
--- [ Pay ] ---
Pay 500 to 'store' by 'user' ... OK
--- [ Settlement ] ---
Transfer 100 to 'admin' from 'store' ... OK
Transfer 100 to 'system' from 'admin' ... OK
Subtract 100 from 'system' ... OK
--- [ Get balance ] ---
Get balance : 'user' ... OK
        region_coin#xxx-currency : 2500
Get balance : 'store' ... OK
        region_coin#xxx-currency : 400
--- [ Get trade history ] ---
Get history : 'user'   ... OK
        [IN]  + 1000 : From store@xxx-currency  (2019-10-25 15:01:56)
        [IN]  + 2000 : From store@xxx-currency  (2019-10-25 15:01:57)
        [OUT] -  500 :   To store@xxx-currency  (2019-10-25 15:01:57)
Get history : 'store'   ... OK
        <Register01>
        [IN]  + 1000 : From system@xxx-currency (2019-10-25 15:01:56)
        [OUT] - 1000 :   To user@xxx-currency   (2019-10-25 15:01:56)
        [IN]  +  500 : From user@xxx-currency   (2019-10-25 15:01:57)
        [OUT] -  100 :   To admin@xxx-currency  (2019-10-25 15:01:57)
        <Register02>
        [IN]  + 2000 : From system@xxx-currency (2019-10-25 15:01:57)
        [OUT] - 2000 :   To user@xxx-currency   (2019-10-25 15:01:57)
Get all history ... OK
        From: system@xxx-currency / To: store@xxx-currency  / Amount: 1000 (2019-10-25 15:01:56)
        From: store@xxx-currency  / To: user@xxx-currency   / Amount: 1000 (2019-10-25 15:01:56)
        From: system@xxx-currency / To: store@xxx-currency  / Amount: 2000 (2019-10-25 15:01:57)
        From: store@xxx-currency  / To: user@xxx-currency   / Amount: 2000 (2019-10-25 15:01:57)
        From: user@xxx-currency   / To: store@xxx-currency  / Amount:  500 (2019-10-25 15:01:57)
        From: store@xxx-currency  / To: admin@xxx-currency  / Amount:  100 (2019-10-25 15:01:57)
        From: admin@xxx-currency  / To: system@xxx-currency / Amount:  100 (2019-10-25 15:01:58)
```
＜2019/10/25時点＞  
上記実行結果の最後の処理「Get all history」では、サンプルプログラム内で実行した全取引の履歴をクエリ「getTransactions」を１回のみ実行し、一度に複数のトランザクションを取得する想定であるが、現状では一度に複数のトランザクションを問い合わせても最後の1件しか取得できない。  
このため、暫定対処として「getTransactions」クエリを複数回呼び出すコードとしているが、実運用には適さない。
