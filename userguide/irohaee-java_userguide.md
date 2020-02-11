# irohaee-java

## 目次
1. [irohaee-java とは](#1-irohaee-java-%E3%81%A8%E3%81%AF)  
2. [irohaee-java 動作環境](#2-irohaee-java-%E3%81%AE%E5%8B%95%E4%BD%9C%E7%92%B0%E5%A2%83)  
    2.1. [javaバージョン](#21-java%E3%83%90%E3%83%BC%E3%82%B8%E3%83%A7%E3%83%B3)  
    2.2. [提供形態](#22-%E6%8F%90%E4%BE%9B%E5%BD%A2%E6%85%8B)  
3. [irohaee-java 利用方法の概要](#3-irohaee-java-%E5%88%A9%E7%94%A8%E6%96%B9%E6%B3%95%E3%81%AE%E6%A6%82%E8%A6%81)  
    3.1. [初期化](#33-%E5%88%9D%E6%9C%9F%E5%8C%96)  
4. [irohaee-java 利用方法の詳細](#4-irohaee-java-%E5%88%A9%E7%94%A8%E6%96%B9%E6%B3%95%E3%81%AE%E8%A9%B3%E7%B4%B0)  
    4.1. [コマンド](#41-%E3%82%B3%E3%83%9E%E3%83%B3%E3%83%89)  
    4.2. [クエリ](#42-%E3%82%AF%E3%82%A8%E3%83%AA)  
    4.3. [バッチ](#43-%E3%83%90%E3%83%83%E3%83%81)  
    4.4. [例外](#44-%E4%BE%8B%E5%A4%96)  
5. [付録](#5-%E4%BB%98%E9%8C%B2)  
    5.1. [トランザクション](#51-%E3%83%88%E3%83%A9%E3%83%B3%E3%82%B6%E3%82%AF%E3%82%B7%E3%83%A7%E3%83%B3) 

## 1. irohaee-java とは
irohaee-java は、オープンソースで公開している [iroha-java](https://github.com/hyperledger/iroha-java) を **Iroha Enterprise Edition** としてより利用しやすい形にハイレベルでラップし、関数定義書や利用ガイドなどのドキュメントを追加したものです。

irohaee-java を利用することで、複雑なクラス構造やメソッドの呼び出し方法などを意識することなく開発を行うことができます。

## 2. irohaee-java の動作環境
### 2.1. javaバージョン

Java8 を前提としています。

### 2.2. 提供形態
irohaee-java は JAR ファイルの形態で提供されます。Gitリポジトリで提供される irohaee-java の JAR ファイルを取得し、Javaプロジェクトのクラスパスに通すことで利用可能となります。

#### 2.2.1. Gitリポジトリ
以下のリポジトリから JAR ファイルを取得してください。

 ```
T.B.D
 ```


## 3. irohaee-java 利用方法の概要
### 3.1. 初期化
APIの呼び出しは、jp.co.soramitsu.irohaee.java.IrohaEE クラスを利用します。コンストラクタで、[トランザクションの作成者アカウントID]、[キーペア]、[irohaサーバのホスト]、[irohaサーバのポート]を指定します。

※ ホスト、ポートの設定を行わない場合は、デフォルト値として、ホスト"127.0.0.1"、ポート 50051 が使用されます。

 ```java
// IrohaEEのインスタンス生成例1
IrohaEE irohaee = new IrohaEE(creator_account, key_pair, host, port);

// IrohaEEのインスタンス生成例2（※ホスト、ポートを未指定）
IrohaEE irohaee = new IrohaEE(account_id, private_key)
```

設定値の変更を行う場合は、以下のメソッドを呼び出して設定を上書きします。

 ```java
// iroha ホスト、ポートの設定
irohaee.setIroha(host, port);

// トランザクション作成者ID、キーペアの設定
irohaee.setAccount(creator_account, key_pair);
```

## 4. irohaee-java 利用方法の詳細
irohaee-java が提供する API には、更新系の処理を行うコマンドと、参照系の処理を行うクエリが存在します。


### 4.1. コマンド
コマンドAPIの呼び出し例は以下の通りです。

> コマンドのAPIリファレンス（引数、戻り値、例外）については、別紙「関数定義書」内の「Command」章を参照してください。
> 当該章に記載されている createDomain 関数が、下記コード内で呼び出している irohaee.createDomain() に該当します。

 ```java
try {
    // createDomain(ドメイン生成)APIの呼び出し
    ToriiResponse res = irohaee.createDomain(...);

} catch (IrohaEETransactionException e) {
    // 例外処理
}
```

### 4.2. クエリ
クエリAPIの呼び出し例は以下の通りです。

> クエリのAPIリファレンス（引数、戻り値、例外）については、別紙「関数定義書」内の「Query」章を参照してください。
> 当該章に記載されている getAccount 関数が、下記コード内で呼び出している irohaee.getAccount() に該当します。

 ```java
try {
    // getAccount(アカウント取得)APIの呼び出し
    AccountResponse res = irohaee.getAccount(...);

    // 処理結果からアカウントIDを取得
    String accountId = res.getAccount().getAccountId();

} catch (IrohaEEQueryException e) {
    // 例外処理
}
```

### 4.3. バッチ
iroha では、バッチとして複数のトランザクションを実行することができます。バッチには、 Atomic バッチと Ordered バッチが存在します。

> バッチAPIリファレンス（引数、戻り値、例外）については、別紙「関数定義書」内の「Batch」章を参照してください。
> 当該章に記載されている createAssetForBatch 関数が、下記コード内で呼び出している irohaee.createAssetForBatch() に該当します。

#### 4.3.1. Atomicバッチ
Atomic バッチは、バッチ内のすべてのトランザクションが Stateful Validation に成功した場合のみ、分散台帳に記録されます。

AtomicバッチAPIの呼び出し例は以下の通りです。

 ```java
try {
    // メソッドチェーンの形式を利用する
    ToriiResponse[] reslist = irohaee.createDomainForBatch(...)
        .createAssetForBatch(...)
        .addAssetQuantityForBatch(...)
        .transferAssetForBatch(...)
        // Atomicバッチ実行
        .sendAtomic();

} catch (IrohaEEBatchTransactionException e) {
    // 例外処理
}
```

例では、createDomain、createAsset、addAssetQuantity、transferAssetをAtomicバッチで実行しています。
下図のようにcreateAssetが失敗した場合、各トランザクションはすべて失敗します。

![Atomicバッチでエラーが発生しない場合](./images/atomic_batch_success.png "Atomicバッチ エラーなし")

![Atomicバッチでエラーが発生した場合](./images/atomic_batch_fail.png "Atomicバッチ エラーあり")

#### 4.3.2. Orderedバッチ
Ordered バッチは、Stateful Validation に成功したトランザクションのみが分散台帳に記録されます。（失敗したトランザクションがあったとしても、バッチ全体が失敗するわけではありません）

OrderedバッチのAPIの呼び出し例は以下の取りです。

 ```java
try {
    // メソッドチェーンの形式を利用する
    ToriiResponse[] reslist = irohaee.createDomainForBatch(...)
        .createAssetForBatch(...)
        .addAssetQuantityForBatch(...)
        .transferAssetForBatch(...)
        // Orderedバッチ実行
        .sendBatch();

} catch (IrohaEEBatchTransactionException e) {
    // 例外処理
}
```

例では、createDomain、createAsset、addAssetQuantity、transferAssetをOrderedバッチで実行しています。
下図のようにcreateAssetが失敗した場合でも、問題のない他のトランザクションは成功します。

![Orderedバッチでエラーが発生しない場合](./images/ordered_batch_success.png "Orderedバッチ エラーなし")

![Orderedバッチでエラーが発生した場合](./images/ordered_batch_fail.png "Orderedバッチ エラーあり")

### 4.4. 例外
irohaee-java は、API呼び出し時にトランザクションが失敗した場合、例外をスローします。

APIの種類に対応する例外は以下の通りです。

| 種類           | 発生例外                         |
| :------------- | :------------------------------- |
| コマンド失敗時 | IrohaEETransactionException      |
| クエリ失敗時   | IrohaEEQueryException            |
| バッチ失敗時   | IrohaEEBatchTransactionException |

#### 4.4.1. コマンド失敗時
コマンドAPI失敗時は IrohaEETransactionException がスローされ、成功時は ToriiResponse が返却されます。トランザクションの状態と戻り値の対応は以下の通りです。

>トランザクション状態の詳細については、[5.1 トランザクション](#5.1-トランザクション) 参照ください。

| トランザクション状態        | 状態 | 戻り値                            |
| :-------------------------- | :--- | :-------------------------------- |
| COMMITTED                   | 成功 | ToriiResponse                     |
| MST_PENDING                 | 保留 | ToriiResponse                     |
| STATELESS_VALIDATION_FAILED | 失敗 | IrohaEETransactionExceptionが発生 |
| REJECTED                    | 失敗 | IrohaEETransactionExceptionが発生 |

- 失敗時にスローされる IrohaEETransactionException には、STATEFULエラーコード及び ToriiResponse オブジェクトが含まれます。

- STATEFULエラーコードは、トランザクション状態が「REJECTED」で、原因が「STATEFUL_VALIDATION_FAILED」の場合に設定されます。

- 「MST_PENDING」は、マルチシグネチャのトランザクションで、署名された数が要求された数（=Quorum で設定された数）に達していない場合に設定されます

> スローされた IrohaEETransactionException から取得可能な値については、別紙「関数定義書」内の「Command」章の各コマンドAPIに記載されている「例外」を参照してください。


#### 4.4.2. クエリ失敗時
クエリAPI失敗時は IrohaEEQueryException がスローされ、成功時はAPI定義に基づくレスポンスオブジェクトが返却されます。

| 状態 | 戻り値                                    |
| :--- | :---------------------------------------- |
| 成功 | API定義に基づく構造体クラスのインスタンス |
| 失敗 | IrohaEEQueryExceptionが発生               |

失敗時にスローされる IrohaEEQueryException には、STATEFULエラーコード及び ErrorResponse オブジェクトが含まれます。

> スローされた IrohaEEQueryException から取得可能な値については、別紙「関数定義書」内の「Query」章の各クエリAPIに記載されている「例外」を参照してください。

#### 4.4.3. バッチ失敗時
バッチAPI失敗時は IrohaEEBatchTransactionException がスローされ、成功時は ToriiResponse オブジェクトの配列が返却されます。

| 状態 | 戻り値                                    |
| :--- | :---------------------------------------- |
| 成功 | API定義に基づく構造体クラスのインスタンス |
| 失敗 | IrohaEEBatchTransactionExceptionが発生    |

失敗時にスローされる IrohaEEBatchTransactionException には、STATEFUL エラーコードの配列、及び ToriiResponse オブジェクトの配列が含まれます。

> スローされた IrohaEEBatchTransactionException から取得可能な値については、別紙「関数定義書」内の「Batch」章の各バッチAPIに記載されている「例外」を参照してください。


## 5. 付録
### 5.1. トランザクション
クライアントから送信されたトランザクションは、バリデーション結果や署名の状態に応じて状態が遷移します。

![Transaction Statuses](https://iroha.readthedocs.io/en/latest/_images/tx_status.png "Transaction Statuses")

#### 5.1.1. 処理概要
1. クライアントからのリクエストを Torii で受信します。
2. 最初に Stateless Validation が実行され、署名と形式的な検証が実行されます。
3. Stateful Validation が実行され、実行権限の有無、残高などが検証されます。
4. Commit されたブロックがブロックチェーンとして記録されます。

#### 5.1.2. トランザクションの状態

| トランザクション状態         | 説明                                                       |
| :--------------------------- | :--------------------------------------------------------- |
| NOT_RECEIVED                 | 要求されたピアにこのトランザクションの情報が無い           |
| ENOUGH_SIGNATURES_COLLECTED  | マルチシグネチャのトランザクションで、十分な署名が得られた |
| MST_PENDING                  | マルチシグネチャのトランザクションで、追加の署名が必要     |
| MST_EXPIRED                  | マルチシグネチャのトランザクションが無効になり、削除された |
| STATELESS_VALIDATION_FAILED  | ステートレス検証に失敗                                     |
| STATELESS_VALIDATION_SUCCESS | ステートレス検証に成功                                     |
| STATEFUL_VALIDATION_FAILED   | ステートフル検証に失敗                                     |
| STATEFUL_VALIDATION_SUCCESS  | ステートフル検証に成功                                     |
| COMMITTED                    | 十分な票を獲得し、ブロックストアに格納済み                 |
| REJECTED                     | ステートフル検証中にトランザクションが拒否された           |


上記状態のうち、(悪意のないノードから送信された)トランザクションの最終ステータスは、「STATELESS_VALIDATION_FAILED」「COMMITTED」「REJECTED」の何れかとなります。

irohaee-java では、正常終了時のトランザクションの状態として「COMMITTED」「MST_PENDING」の何れかを返却します。

また、異常終了時のトランザクションの状態が「STATELESS_VARIDATION_FAILED」「REJECTED」の場合、トランザクション失敗とみなして例外をスローします。

例外については、[4.4 例外](#4.4-例外) を参照ください。

トランザクションの状態遷移の詳細については、以下のURLを参照ください。
>#### Transaction Statuses
>https://iroha.readthedocs.io/en/latest/before_start/glossary.html#transaction-statuses
>#### Status Streaming In Hyperledger Iroha
>https://medium.com/iroha-contributors/status-streaming-in-hl-iroha-5503487ffcfds

### 5.1.3 トランザクションの構成

iroha のトランザクションは、Payload と Signatures から構成されています。

#### Payload

| 要素                                 | 説明                                                        |
| :----------------------------------- | :---------------------------------------------------------- |
| コマンド                             | いろはAPI のコマンド                                        |
| 作成時間                             | 作成時間（ミリ秒単位の UNIX時間）                           |
| トランザクション作成者のアカウントID | 「アカウント名@ドメイン」の形式                             |
| クォーラム                           | 必要な署名の数（デフォルト:1）                              |
| バッチメタ情報(オプション)           | バッチ情報（ATOMIC、ORDERED）、トランザクション縮小ハッシュ |

#### Signatures

| 要素 | 説明                                 |
| :--- | :----------------------------------- |
| 署名 | トランザクション作成者／承認者の署名 |

#### トランザクション定義
```proto
message Transaction {
    message Payload {
        message BatchMeta{
            enum BatchType{
                    ATOMIC = 0;
                    ORDERED = 1;
            }
            BatchType type = 1;
            // array of reduced hashes of all txs from the batch
            repeated string reduced_hashes = 2;
        }
    message ReducedPayload{
        repeated Command commands = 1;
        string creator_account_id = 2;
        uint64 created_time = 3;
        uint32 quorum = 4;
    }
    // transcation fields
    ReducedPayload reduced_payload = 1;
    
    // batch meta fields if tx belong to any batch
    oneof optional_batch_meta{
            BatchMeta batch = 5;
        }
    }
    Payload payload = 1;
    repeated Signature signatures = 2;
}
 ```

### 5.1.4 マルチシグネチャトランザクション
マルチシグネチャトランザクションは、複数の署名を必要とするトランザクションのことであり、必要な署名数は、クォーラムで指定します。

マルチシグネチャトランザクションに署名を追加するコード例は以下の通りです。

 ```java
try {
    // 署名待ちで保留中のトランザクションを取得
    val pendingResponse = irohaee.getPendingTransactions(1, null);
    val tx = pendingResponse.getTransactions(0);

    // 署名の追加
    val signedTx = Transaction.parseFrom(tx).sign(multisigKeypair2).build();

    // トランザクションの送信
    val signedRes = irohaee.sendTransation(signedTx);

} catch (IrohaEETransactionException e) {
    // 例外処理
}
```