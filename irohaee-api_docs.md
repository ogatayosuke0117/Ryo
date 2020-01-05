# IrohaEE 関数定義書

## 目次

### Setting
1. [setIroha](#setiroha)
1. [setAccount](#setaccount)

### Command
1. [addAssetQuantity](#addassetquantity)
1. [addPeer](#addpeer)
1. [addSignatory](#addsignatory)
1. [appendRole](#appendrole)
1. [createAccount](#createaccount)
1. [createAsset](#createasset)
1. [createDomain](#createdomain)
1. [createRole](#createrole)
1. [detachRole](#detachrole)
1. [grantPermission](#grantpermission)
1. [removePeer](#removepeer)
1. [removeSignatory](#removesignatory)
1. [revokePermission](#revokepermission)
1. [setAccountDetail](#setaccountdetail)
1. [setAccountQuorum](#setaccountquorum)
1. [subtractAssetQuantity](#subtractassetquantity)
1. [transferAsset](#transferasset)
1. [compareAndSetAccountDetail](#compareandsetaccountdetail)

### Query
1. [getAccount](#getaccount)
1. [getBlock](#getblock)
1. [getSignatories](#getsignatories)
1. [getTransactions](#gettransactions)
1. [getPendingTransactions](#getpendingtransactions)
1. [getAccountTransactions](#getaccounttransactions)
1. [getAccountAssetTransactions](#getaccountassettransactions)
1. [getAccountAssets](#getaccountassets)
1. [getAccountDetail](#getaccountdetail)
1. [getAssetInfo](#getassetinfo)
1. [getRoles](#getroles)
1. [getRolePermissions](#getrolepermissions)
1. [getPeers](#getpeers)

### Batch
1. [sendBatch](#sendbatch)
1. [sendAtomic](#sendatomic)
1. [addAssetQuantityForBatch](#addassetquantityforbatch)
1. [addPeerForBatch](#addpeerforbatch)
1. [addSignatoryForBatch](#addsignatoryforbatch)
1. [appendRoleForBatch](#appendroleforbatch)
1. [createAccountForBatch](#createaccountforbatch)
1. [createAssetForBatch](#createassetforbatch)
1. [createDomainForBatch](#createdomainforbatch)
1. [createRoleForBatch](#createroleforbatch)
1. [detachRoleForBatch](#detachroleforbatch)
1. [grantPermissionForBatch](#grantpermissionforbatch)
1. [removePeerForBatch](#removepeerforbatch)
1. [removeSignatoryForBatch](#removesignatoryforbatch)
1. [revokePermissionForBatch](#revokepermissionforbatch)
1. [setAccountDetailForBatch](#setaccountdetailforbatch)
1. [setAccountQuorumForBatch](#setaccountquorumforbatch)
1. [subtractAssetQuantityForBatch](#subtractassetquantityforbatch)
1. [transferAssetForBatch](#transferassetforbatch)
1. [compareAndSetAccountDetailForBatch](#compareandsetaccountdetailforbatch)

### 付録
1. [エラーコード](#%e3%82%a8%e3%83%a9%e3%83%bc%e3%82%b3%e3%83%bc%e3%83%89)
1. [原因コード](#%e5%8e%9f%e5%9b%a0%e3%82%b3%e3%83%bc%e3%83%89)


# Setting
## setIroha
Irohaへの接続情報を設定をする

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| host | ○ | Iroha Torii address | IPv4、IPv6、ドメイン名など |
| port | ○ | Toriiポート番号 | 正数 |
| timeout | | 接続タイムアウト時間(秒) | 正数 |

### 戻り値
なし

### 内容
Irohaへの接続情報を設定をする。  
本関数を呼び出さない場合は 127.0.0.1:50051 に接続される。

### 制限事項
<br>

## setAccount
Irohaの操作・参照を行うアカウント情報を設定をする

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | アカウントID | <account_name>@<domain_id> |
| private_key | ○ | アカウントに設定済みの公開鍵に対応する秘密鍵 | ed25519秘密鍵 |

### 戻り値
なし

### 内容
Irohaにトランザクションおよびクエリを発行するアカウントを設定する。  

### 制限事項
<br>

<br>

# Command
## addAssetQuantity
アセットに数量を追加する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| asset_id | ○ | アセットID | <asset_name>#<domain_id> |
| amount | ○ | 追加する数量 | 正数 |

- アセットIDは、事前に作成されていなければならない
- アマウントは、作成時のprecisionに従った小数点表記が可能

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |

### 例外
コマンド実行エラー時 IrohaEETransactionException を送出する。

戻り値は、IrohaEETransactionException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEETransactionException#  getResponse().getTxHash() |
| status | トランザクションの状態 | "REJECTED","STATELESS_VALIDATION_FAILED" のうちいずれか | IrohaEETransactionException#  getResponse().getTxStatus().toString() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEETransactionException#  getStatefullErrorCode() | 

### 内容
トランザクションを発行したアカウントの所持するアセットをamountで指定した数量追加する。

### 権限
トランザクションの発行者には、can_add_asset_qty権限またはcan_add_domain_asset_qty権限が必要。  
ただし、can_add_domain_asset_qty権限の場合は、トランザクションの発行者が所属するドメイン内のアセットに対してのみ実行可能。

### 制限事項
<br>

## addPeer
ネットワークにピアを追加する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| address | ○ | ネットワーク内の解決可能なアドレス | IPv4、IPv6、ドメイン名など |
| peer_key | ○ | ピアの公開鍵 | ed25519公開鍵 |

- 公開鍵は合意形成アルゴリズムで使用される
- 他のピアと同一の公開鍵は使用できない

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |


### 例外
コマンド実行エラー時IrohaEETransactionExceptionを送出する。

戻り値は、IrohaEETransactionException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEETransactionException#  getResponse().getTxHash() |
| status | トランザクションの状態 | "REJECTED","STATELESS_VALIDATION_FAILED" のうちいずれか | IrohaEETransactionException#  getResponse().getTxStatus().toString() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEETransactionException#  getStatefullErrorCode() | 

### 内容
ピアネットワークに向けてピアが追加された事実を台帳に書き込む。

### 権限
トランザクションの発行者には、can_add_peer権限が必要。

### 制限事項
<br>

## addSignatory
署名を追加する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | 署名を追加するアカウントID | <account_name>@<domain_id> |
| public_key | ○ | アカウントに追加する公開鍵 | ed25519公開鍵 |

- アカウントIDは事前に作成されていなければならない

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |


### 例外
コマンド実行エラー時IrohaEETransactionExceptionを送出する。

戻り値は、IrohaEETransactionException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEETransactionException#  getResponse().getTxHash() |
| status | トランザクションの状態 | "REJECTED","STATELESS_VALIDATION_FAILED" のうちいずれか | IrohaEETransactionException#  getResponse().getTxStatus().toString() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEETransactionException#  getStatefullErrorCode() | 

### 内容
指定したアカウントに署名を追加する。

### 権限
トランザクションの発行者には、can_add_signatory権限が必要。


トランザクションの発行者が自身の署名を追加する場合は、can_add_signatory権限が必要。  
トランザクションの発行者が別アカウントに署名を追加する場合は、そのアカウントからcan_add_my_signatory権限が委譲されていることが必要。

### 制限事項
<br>

## appendRole
アカウントにロールを追加する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | ロールを追加するアカウントID | <account_name>@<domain_id> |
| role_name | ○ | システム内で既に規定されたロール名 | [a-z_0-9]{1,32} |

- アカウントIDおよびロールは事前に作成されていなければならない

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |


### 例外
コマンド実行エラー時IrohaEETransactionExceptionを送出する。

戻り値は、IrohaEETransactionException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEETransactionException#  getResponse().getTxHash() |
| status | トランザクションの状態 | "REJECTED","STATELESS_VALIDATION_FAILED" のうちいずれか | IrohaEETransactionException#  getResponse().getTxStatus().toString() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEETransactionException#  getStatefullErrorCode() | 

### 内容
指定したアカウントにロールを追加する。

### 権限
トランザクションの発行者には、can_append_role権限が必要。

### 制限事項
<br>

## createAccount
アカウントを新規作成する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_name | ○ | アカウント名 | [a-z_0-9]{1,32} |
| domain_id | ○ | ドメインID | RFC1035, RFC1123 |
| public_key | ○ | アカウントに追加する公開鍵 | ed25519公開鍵 |

- ドメインIDは、事前に作成されていなければならない
- アカウント名はドメイン内で一意でなくてはならない

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |


### 例外
コマンド実行エラー時IrohaEETransactionExceptionを送出する。

戻り値は、IrohaEETransactionException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEETransactionException#  getResponse().getTxHash() |
| status | トランザクションの状態 | "REJECTED","STATELESS_VALIDATION_FAILED" のうちいずれか | IrohaEETransactionException#  getResponse().getTxStatus().toString() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEETransactionException#  getStatefullErrorCode() | 

### 内容
指定したドメイン内に新規アカウントを作成する。

### 権限
トランザクションの発行者には、can_create_account権限が必要。

### 制限事項
<br>

## createAsset
アセットを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| asset_name | ○ | アセット名 | [a-z_0-9]{1,32} |
| domain_id | ○ | ドメインID | RFC1035, RFC1123 |
| precision | ○ | コンマ/ドットに後につづく桁数 | 0<=precision<=255 |

- ドメインIDは、事前に作成されていなければならない
- アセット名はドメイン内で一意でなくてはならない

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |


### 例外
コマンド実行エラー時IrohaEETransactionExceptionを送出する。

戻り値は、IrohaEETransactionException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEETransactionException#  getResponse().getTxHash() |
| status | トランザクションの状態 | "REJECTED","STATELESS_VALIDATION_FAILED" のうちいずれか | IrohaEETransactionException#  getResponse().getTxStatus().toString() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEETransactionException#  getStatefullErrorCode() | 

### 内容
指定したドメイン内に新規アセットを作成する。

### 権限
トランザクションの発行者には、can_create_asset権限が必要。

### 制限事項
<br>

## createDomain
ドメインを作成する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| domain_id | ○ | ドメインID | RFC1035, RFC1123 |
| default_role | ○ | システム内で既に規定されたロール名 | [a-z_0-9]{1,32} |

- ロールは事前に作成されていなければならない
- ドメインIDはシステム上で一意でなくてはならない

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |

### 例外
コマンド実行エラー時IrohaEETransactionExceptionを送出する。

戻り値は、IrohaEETransactionException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEETransactionException#  getResponse().getTxHash() |
| status | トランザクションの状態 | "REJECTED","STATELESS_VALIDATION_FAILED" のうちいずれか | IrohaEETransactionException#  getResponse().getTxStatus().toString() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEETransactionException#  getStatefullErrorCode() | 

### 内容
Irohaネットワークに新たなドメインを作成する。

### 権限
トランザクションの発行者には、can_create_domain権限が必要。

### 制限事項
<br>

## createRole
ロールを作成する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| role_name | ○ | ロール名 | [a-z_0-9]{1,32} |
| permissions | ○ | 権限の配列 | ex: [can_receive, can_transfer] |

- permissionsにはひとつ以上の権限が設定されていること
- 設定可能な権限は[こちら](https://iroha.readthedocs.io/en/latest/develop/api/permissions.html#list-of-permissions)を参照

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |


### 例外
コマンド実行エラー時IrohaEETransactionExceptionを送出する。

戻り値は、IrohaEETransactionException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEETransactionException#  getResponse().getTxHash() |
| status | トランザクションの状態 | "REJECTED","STATELESS_VALIDATION_FAILED" のうちいずれか | IrohaEETransactionException#  getResponse().getTxStatus().toString() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEETransactionException#  getStatefullErrorCode() | 

### 内容
システム上に新たなロールを作成する。

### 権限
トランザクションの発行者には、can_create_role権限が必要。

### 制限事項
<br>

## detachRole
ロールを切り離す

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | ロールを切り離すアカウントID | <account_name>@<domain_id> |
| role_name | ○ | 切り離すロール名 | [a-z_0-9]{1,32} |

- アカウントIDは切り離すロールを持っている必要がある

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |

### 例外
コマンド実行エラー時IrohaEETransactionExceptionを送出する。

戻り値は、IrohaEETransactionException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEETransactionException#  getResponse().getTxHash() |
| status | トランザクションの状態 | "REJECTED","STATELESS_VALIDATION_FAILED" のうちいずれか | IrohaEETransactionException#  getResponse().getTxStatus().toString() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEETransactionException#  getStatefullErrorCode() | 

### 内容
指定したアカウントからロールを切り離す。

### 権限
トランザクションの発行者には、can_detach_role権限が必要。

### 制限事項
<br>

## grantPermission
権限を委譲する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | 権限を委譲するアカウントID | <account_name>@<domain_id> |
| permission | ○ | 委譲する権限 | grantableである権限（下記参照） |

- アカウントIDは事前に作成されていなければならない
- 設定可能なgrantable権限は以下の通り（[こちら](https://iroha.readthedocs.io/en/latest/develop/api/permissions.html#list-of-permissions)も参照）
    - can_add_my_signatory
    - can_remove_my_signatory
    - can_set_my_account_detail
    - can_set_my_quorum
    - can_transfer_my_assets

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |


### 例外
コマンド実行エラー時IrohaEETransactionExceptionを送出する。

戻り値は、IrohaEETransactionException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEETransactionException#  getResponse().getTxHash() |
| status | トランザクションの状態 | "REJECTED","STATELESS_VALIDATION_FAILED" のうちいずれか | IrohaEETransactionException#  getResponse().getTxStatus().toString() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEETransactionException#  getStatefullErrorCode() | 

### 内容
トランザクションの発行者が指定したアカウントに対し、指定した権限を委譲する。

### 権限
トランザクションの発行者には、委譲する権限に対応した権限が必要。

| トランザクション発行者に必要な権限 | 委譲する権限 |
|:----|:----|
| can_grant_can_add_my_signatory | can_add_my_signatory |
| can_grant_can_remove_my_signatory | can_remove_my_signatory |
| can_grant_can_set_my_account_detail | can_set_my_account_detail |
| can_grant_can_set_my_quorum | can_set_my_quorum |
| can_grant_can_transfer_my_assets | can_transfer_my_assets |

### 制限事項
<br>

## removePeer
Irohaネットワークからピアを除去する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| public_key | ○ | 除去するピアの公開鍵 | ed25519公開鍵 |

- 指定した公開鍵を持つピアがIrohaネットワーク上に存在している必要がある
- 指定した公開鍵を持つピア以外のピアがIrohaネットワーク上に存在している必要がある

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |

### 例外
コマンド実行エラー時IrohaEETransactionExceptionを送出する。

戻り値は、IrohaEETransactionException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEETransactionException#  getResponse().getTxHash() |
| status | トランザクションの状態 | "REJECTED","STATELESS_VALIDATION_FAILED" のうちいずれか | IrohaEETransactionException#  getResponse().getTxStatus().toString() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEETransactionException#  getStatefullErrorCode() | 

### 内容
ピアネットワークに向けてピアが除去された事実を台帳に書き込む。

### 権限
トランザクションの発行者には、can_remove_peer権限が必要。

### 制限事項
<br>

## removeSignatory
署名を削除する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | アカウントID | <account_name>@<domain_id> |
| public_key | ○ | アカウントから削除する公開鍵 | ed25519公開鍵 |

- アカウントIDは事前に作成されていなければならない
- 削除する公開鍵を除いたアカウントに紐づく公開鍵の数が quorum 以上であることが必要

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |


### 例外
コマンド実行エラー時IrohaEETransactionExceptionを送出する。

戻り値は、IrohaEETransactionException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEETransactionException#  getResponse().getTxHash() |
| status | トランザクションの状態 | "REJECTED","STATELESS_VALIDATION_FAILED" のうちいずれか | IrohaEETransactionException#  getResponse().getTxStatus().toString() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEETransactionException#  getStatefullErrorCode() | 

### 内容
指定したアカウントから署名を削除する。

### 権限
トランザクションの発行者が自身の署名を削除する場合は、can_remove_signatory権限が必要。  
トランザクションの発行者が別アカウントの署名を削除する場合は、そのアカウントからcan_remove_my_signatory権限が委譲されていることが必要。

### 制限事項
<br>

## revokePermission
権限を取り消す

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | 権限を取り消すアカウントID | <account_name>@<domain_id> |
| permission | ○ | 取り消す権限 | grantableである権限（下記参照） |

- 取り消そうとする権限が指定するアカウントに対して事前に付与されている必要がある
- 設定可能なgrantable権限は以下の通り（[こちら](https://iroha.readthedocs.io/en/latest/develop/api/permissions.html#list-of-permissions)も参照）
    - can_add_my_signatory
    - can_remove_my_signatory
    - can_set_my_account_detail
    - can_set_my_quorum
    - can_transfer_my_assets

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |

### 例外
コマンド実行エラー時IrohaEETransactionExceptionを送出する。

戻り値は、IrohaEETransactionException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEETransactionException#  getResponse().getTxHash() |
| status | トランザクションの状態 | "REJECTED","STATELESS_VALIDATION_FAILED" のうちいずれか | IrohaEETransactionException#  getResponse().getTxStatus().toString() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEETransactionException#  getStatefullErrorCode() | 

### 内容
トランザクションの発行者が指定したアカウントに対して委譲していた権限を取り消す。

### 権限
トランザクションの発行者には、取り消す権限に対応した権限が必要。

| トランザクション発行者に必要な権限 | 取り消す権限 |
|:----|:----|
| can_grant_can_add_my_signatory | can_add_my_signatory |
| can_grant_can_remove_my_signatory | can_remove_my_signatory |
| can_grant_can_set_my_account_detail | can_set_my_account_detail |
| can_grant_can_set_my_quorum | can_set_my_quorum |
| can_grant_can_transfer_my_assets | can_transfer_my_assets |

### 制限事項
<br>

## setAccountDetail
アカウントの詳細を設定する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | 詳細を設定するアカウントID | <account_name>@<domain_id> |
| key | ○ | 設定されるキー | [A-Za-z0-9_]{1,64} |
| value | ○ | キーに対応する値 | 4096バイト以下の文字列 |

- アカウントIDは、事前に作成されていなければならない

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |

### 例外
コマンド実行エラー時IrohaEETransactionExceptionを送出する。

戻り値は、IrohaEETransactionException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEETransactionException#  getResponse().getTxHash() |
| status | トランザクションの状態 | "REJECTED","STATELESS_VALIDATION_FAILED" のうちいずれか | IrohaEETransactionException#  getResponse().getTxStatus().toString() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEETransactionException#  getStatefullErrorCode() | 

### 内容
指定したアカウントに紐づくキーバリュー情報を設定する。  
既にアカウントにキーが存在する場合は、値を上書きする。

### 権限 
トランザクションの発行者が別アカウントの詳細を設定する場合は、can_set_detail権限を保持しているか、そのアカウントからcan_set_my_account_detail権限が委譲されていることが必要。  
(トランザクションの発行者自身のアカウントの詳細を設定する場合は権限は不要） 

### 制限事項
<br>

## setAccountQuorum
アカウントのクォーラム数を設定する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | クォーラム数を設定するアカウントID | <account_name>@<domain_id> |
| quorum | ○ | クォーラム数 | 以下の条件を満たす整数 <br> 0 < quorum <= アカウントに紐づいている公開鍵の数 <= 128 |

- アカウントIDは事前に作成されていなければならない。

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |

### 例外
コマンド実行エラー時IrohaEETransactionExceptionを送出する。

戻り値は、IrohaEETransactionException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEETransactionException#  getResponse().getTxHash() |
| status | トランザクションの状態 | "REJECTED","STATELESS_VALIDATION_FAILED" のうちいずれか | IrohaEETransactionException#  getResponse().getTxStatus().toString() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEETransactionException#  getStatefullErrorCode() | 

### 内容
指定したアカウントのアカウントのクォーラム数を設定する。

### 権限
トランザクションの発行者が自身のクォーラム数を設定する場合は、can_set_quorum権限が必要。  
トランザクションの発行者が別アカウントのクォーラム数を設定する場合は、そのアカウントからcan_set_my_quorum権限が委譲されていることが必要。

### 制限事項
<br>

## subtractAssetQuantity
アセットの数量を減らす

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| asset_id | ○ | アセットID | <asset_name>#<domain_id> |
| amount | ○ | 差し引く数量 | 正数 |

- アセットIDは、事前に作成されていなければならない
- アマウントは、作成時のprecisionに従った小数点表記が可能

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |

### 例外
コマンド実行エラー時IrohaEETransactionExceptionを送出する。

戻り値は、IrohaEETransactionException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEETransactionException#  getResponse().getTxHash() |
| status | トランザクションの状態 | "REJECTED","STATELESS_VALIDATION_FAILED" のうちいずれか | IrohaEETransactionException#  getResponse().getTxStatus().toString() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEETransactionException#  getStatefullErrorCode() | 

### 内容
トランザクションを発行したアカウントの所持するアセットをamountで指定した数量減少させる。

### 権限
トランザクションの発行者には、can_subtract_asset_qty権限またはcan_subtract_domain_asset_qty権限が必要。  
ただし、can_subtract_domain_asset_qty権限の場合は、トランザクションの発行者が所属するドメイン内のアセットに対してのみ実行可能。

### 制限事項
<br>

## transferAsset
資産を移転させる

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| src_account_id | ○ | 移転元アカウントID | <account_name>@<domain_id> |
| dest_account_id | ○ | 移転先アカウントID | <account_name>@<domain_id> |
| asset_id | ○ | アセットID | <asset_name>#<domain_id> |
| description | ○ | 移転操作に付加するメッセージ | 64バイト以下の文字列 |
| amount | ○ | 移転する数量 | 正数 |

- 移転元および移転先のアカウントが存在すること
- 移転元のアカウントに当該アセットが存在すること
- 移転元アカウントに転送する資産が十分にあり、0ではないこと
- 数量は、作成時のprecisionに従った小数点表記が可能

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |

### 例外
コマンド実行エラー時IrohaEETransactionExceptionを送出する。

戻り値は、IrohaEETransactionException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEETransactionException#  getResponse().getTxHash() |
| status | トランザクションの状態 | "REJECTED","STATELESS_VALIDATION_FAILED" のうちいずれか | IrohaEETransactionException#  getResponse().getTxStatus().toString() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEETransactionException#  getStatefullErrorCode() | 

### 内容
指定したアカウントから別のアカウントへ資産を移転させる。

### 権限
トランザクションの発行者には、can_transfer権限が必要。  
移転先アカウントには、can_receive権限が必要。  
移転元のアカウントにトランザクションの発行者以外のアカウントを設定する場合は、そのアカウントからcan_transfer_my_assets権限が委譲されていることが必要。

### 制限事項
<br>

## compareAndSetAccountDetail
アカウント詳細の内容を置換する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | 詳細を設定するアカウントID | <account_name>@<domain_id> |
| key | ○ | 設定されるキー | [A-Za-z0-9_]{1,64} |
| value | ○ | キーに対応する新しい値 | 4096バイト以下の文字列 |
| old_value | | キーに対応する現在の値 | 4096バイト以下の文字列 |

- アカウントIDは、事前に作成されていなければならない

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |

### 例外
コマンド実行エラー時IrohaEETransactionExceptionを送出する。

戻り値は、IrohaEETransactionException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEETransactionException#  getResponse().getTxHash() |
| status | トランザクションの状態 | "REJECTED","STATELESS_VALIDATION_FAILED" のうちいずれか | IrohaEETransactionException#  getResponse().getTxStatus().toString() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEETransactionException#  getStatefullErrorCode() | 

### 内容
キーに対応する現在の値が指定した値であった場合のみ、新しい値でキーバリュー情報を更新する。  
アカウントに指定のキーが存在しない場合、新しい値でキーバリュー情報が設定される。

### 権限
トランザクションの発行者が自身のアカウントの詳細を設定する場合は、can_get_my_acc_detail権限/can_get_all_acc_detail権限/can_get_domain_acc_detail権限のいずれかが必要。

トランザクションの発行者が別アカウントの詳細を設定する場合は、can_set_detail権限を保持しているか、そのアカウントからcan_set_my_account_detail権限が委譲されている必要がある。加えてcan_get_all_acc_detail権限/can_get_domain_acc_detail権限のいずれかが必要。ただし、can_get_domain_acc_detail権限の場合は、トランザクションの発行者が所属するドメイン内のアカウントに対してのみ実行可能。

| 対象アカウント | 必要となる権限 |
|:----|:----|
| トランザクション発行者自身 | 1. can_get_my_acc_detail / can_get_all_acc_detail / can_get_domain_acc_detail |
| 同一ドメインのアカウント | 1. can_set_detail / (granted) can_set_my_account_detail <br> 2. can_get_all_acc_detail / can_get_domain_acc_detail |
| 別ドメインのアカウント | 1. can_set_detail / (granted) can_set_my_account_detail <br> 2. can_get_all_acc_detail |

### 制限事項
<br>


# Query

## getAccount
アカウントの状態を取得する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | 状態を問い合わせるアカウントのID | <account_name>@<domain_id> |

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:----|:----|:----|:----|
| account_id | アカウントID | <account_name>@<domain_id> | AccountResponse#  getAccount().getAccountId() |
| domain_id | ドメインID | RFC1035, RFC1123 | AccountResponse#  getAccount().getDomainId() |
| quorum | トランザクションを有効なものにするために必要な署名者数 | 1以上、128以下の整数 | AccountResponse#  getAccount().getQuorum() |
| json_data | アカウントに紐づくキーバリュー情報 | JSON | AccountResponse#  getAccount().getJsonData() |
| account_roles | システム上に存在するロール名の配列 | 文字列の配列 | AccountResponse#  getAccountRolesList() |

### 例外
クエリ実行エラー時 IrohaEEQueryException を送出する。

戻り値は、IrohaEEQueryException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| reason | 原因コード | [原因コード](#原因コード)はIrohaAPIの仕様に準拠する | IrohaEEQueryException#  getErrorResponse().getReasonValue() |
| message | エラーメッセージ | エラーメッセージ | IrohaEEQueryException#  getErrorResponse().getMessage() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEEQueryException#  getStatefullErrorCode() | 

### 内容
指定したアカウントの状態を取得する。

### 権限
クエリの発行者には、can_get_my_account権限、またはcan_get_domain_account権限、またはcan_get_all_account権限が必要。can_get_my_account権限の場合はクエリ発行者自身のアカウントのみ、can_get_domain_account権限の場合はクエリ発行者と同一ドメインに所属するアカウントの状態が取得可能。

### 制限事項
<br>

## getBlock
ブロックを取得する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| height | ○ | 取得するブロックの高さ | 1以上、2^64以下の整数 |

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| block | 取得したブロック | ブロック構造 |

### 例外
クエリ実行エラー時IrohaEEQueryExceptionを送出する。

戻り値は、IrohaEEQueryException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| reason | 原因コード | [原因コード](#原因コード)はIrohaAPIの仕様に準拠する | IrohaEEQueryException#  getErrorResponse().getReasonValue() |
| message | エラーメッセージ | エラーメッセージ | IrohaEEQueryException#  getErrorResponse().getMessage() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEEQueryException#  getStatefullErrorCode() | 

### 内容
指定したブロックを取得する。

### 権限
クエリの発行者には、can_get_blocks権限が必要。

### 制限事項
<br>

## getSignatories
アカウントに紐づく署名を取得する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | 署名を要求するアカウントのID | <account_name>@<domain_id> |

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:----|:----|:----|:----|
| keys | 公開鍵の配列 | ed25519の配列 | SignatoriesResponse#getKeysList() |

### 例外
クエリ実行エラー時IrohaEEQueryExceptionを送出する。

戻り値は、IrohaEEQueryException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| reason | 原因コード | [原因コード](#原因コード)はIrohaAPIの仕様に準拠する | IrohaEEQueryException#  getErrorResponse().getReasonValue() |
| message | エラーメッセージ | エラーメッセージ | IrohaEEQueryException#  getErrorResponse().getMessage() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEEQueryException#  getStatefullErrorCode() | 

### 内容
指定したアカウントに紐づく署名を取得する。

### 権限
クエリの発行者には、can_get_my_signatories権限、またはcan_get_domain_signatories権限、またはcan_get_all_signatories権限が必要。can_get_my_signatories権限の場合はクエリ発行者自身のアカウントのみ、can_get_domain_signatories権限の場合はクエリ発行者と同一ドメインに所属するアカウントの署名が取得可能。

### 制限事項
<br>

## getTransactions
トランザクションを取得する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| tx_hashes | ○ | 取得するトランザクションのハッシュの配列 | 32バイト長のハッシュの配列 |

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:----|:----|:----|:----|
| transactions | コミットされたトランザクションの配列 | トランザクションの配列 | TransactionsResponse#getTransactionsList() |

### 例外
クエリ実行エラー時IrohaEEQueryExceptionを送出する。

戻り値は、IrohaEEQueryException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| reason | 原因コード | [原因コード](#原因コード)はIrohaAPIの仕様に準拠する | IrohaEEQueryException#  getErrorResponse().getReasonValue() |
| message | エラーメッセージ | エラーメッセージ | IrohaEEQueryException#  getErrorResponse().getMessage() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEEQueryException#  getStatefullErrorCode() | 

### 内容
指定したトランザクションを取得する。

### 権限
クエリの発行者には、can_get_my_txs権限、またはcan_get_all_txs権限が必要。can_get_my_txs権限の場合はクエリ発行者自身が発行したトランザクションのみが取得可能。

### 制限事項
<br>

## getPendingTransactions
保留中のトランザクションを取得する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| page_size | ○ | 戻り値で返却されるトランザクションの最大量 | 正整数 |
| first_tx_hash | | ページ先頭のトランザクションハッシュ | 32バイト長のハッシュ |

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:----|:----|:----|:----|
| transactions | 保留中のトランザクションの配列 | トランザクションの配列 | PendingTransactionsPageResponse#  getTransactionsList() |
| all_transactions_size | システム上に格納されたトランザクションの数 | 整数 | PendingTransactionsPageResponse#  getAllTransactionsSize() |
| first_tx_hash | 次のバッチの先頭のトランザクションハッシュ | 32バイト長のハッシュ | PendingTransactionsPageResponse#  getNextBatchInfo().getFirstTxHash() |
| batch_size | 次のバッチを取得するために必要な最小ページサイズ | 正整数 | PendingTransactionsPageResponse#  getNextBatchInfo().getBatchSize() |

### 例外
クエリ実行エラー時IrohaEEQueryExceptionを送出する。

戻り値は、IrohaEEQueryException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| reason | 原因コード | [原因コード](#原因コード)はIrohaAPIの仕様に準拠する | IrohaEEQueryException#  getErrorResponse().getReasonValue() |
| message | エラーメッセージ | エラーメッセージ | IrohaEEQueryException#  getErrorResponse().getMessage() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEEQueryException#  getStatefullErrorCode() | 

### 内容
クエリ発行者自身が発行した保留中のマルチシグネチャトランザクションまたはトランザクションのバッチのリストを取得する。

### 権限
なし

### 制限事項
<br>

## getAccountTransactions
アカウント毎のトランザクションを取得する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | トランザクション情報をリクエストするアカウントID | <account_name>@<domain_id> |
| page_size | ○ | 戻り値で返却されるトランザクションの最大量 | 正整数 |
| first_tx_hash | | ページ先頭のトランザクションハッシュ | 32バイト長のハッシュ |

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:----|:----|:----|:----|
| transactions | 指定したアカウントが発行したトランザクションの配列 | トランザクションの配列 | TransactionsPageResponse#  getTransactionsList() |
| all_transactions_size | システム上に格納されたトランザクションの数 | 整数 | TransactionsPageResponse#  getAllTransactionsSize() |
| first_tx_hash | 次ページの先頭のトランザクションハッシュ | 32バイト長のハッシュ | TransactionsPageResponse#  getNextTxHash() |

- 指定されたアカウントの最後のトランザクションが返却された配列内に含まれている場合、first_tx_hashは空となる

### 例外
クエリ実行エラー時IrohaEEQueryExceptionを送出する。

戻り値は、IrohaEEQueryException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| reason | 原因コード | [原因コード](#原因コード)はIrohaAPIの仕様に準拠する | IrohaEEQueryException#  getErrorResponse().getReasonValue() |
| message | エラーメッセージ | エラーメッセージ | IrohaEEQueryException#  getErrorResponse().getMessage() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEEQueryException#  getStatefullErrorCode() | 

### 内容
指定したアカウントが発行したトランザクションのリストを取得する。  
引数のfirst_tx_hashが未指定の場合、最初のトランザクションが返却される。

### 権限
クエリの発行者には、can_get_my_acc_txs権限、またはcan_get_domain_acc_txs権限、またはcan_get_all_acc_txs権限が必要。can_get_my_acc_txs権限の場合はクエリ発行者自身のアカウントのみ、can_get_domain_acc_txs権限の場合はクエリ発行者と同一ドメインに所属するアカウントのトランザクションが取得可能。

### 制限事項
<br>

## getAccountAssetTransactions
アカウント毎のアセットに関連したトランザクションを取得する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | トランザクション情報をリクエストするアカウントID | <account_name>@<domain_id> |
| asset_id | ○ | トランザクションをフィルタリングするためのアセットID | <asset_name>#<domain_id> |
| page_size | ○ | 戻り値で返却されるトランザクションの最大量 | 正整数 |
| first_tx_hash | | ページ先頭のトランザクションハッシュ | 32バイト長のハッシュ |

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:----|:----|:----|:----|
| transactions | 指定したアカウントおよびアセット関連のトランザクションの配列 | トランザクションの配列 | TransactionsPageResponse#  getTransactionsList() |
| all_transactions_size | システム上に格納されたトランザクションの数 | 整数 | TransactionsPageResponse#  getAllTransactionsSize() |
| first_tx_hash | 次ページの先頭のトランザクションハッシュ | 32バイト長のハッシュ | TransactionsPageResponse#  getNextTxHash() |

- 指定されたアカウントの最後のトランザクションが返却された配列内に含まれている場合、first_tx_hashは空となる

### 例外
クエリ実行エラー時IrohaEEQueryExceptionを送出する。

戻り値は、IrohaEEQueryException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| reason | 原因コード | [原因コード](#原因コード)はIrohaAPIの仕様に準拠する | IrohaEEQueryException#  getErrorResponse().getReasonValue() |
| message | エラーメッセージ | エラーメッセージ | IrohaEEQueryException#  getErrorResponse().getMessage() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEEQueryException#  getStatefullErrorCode() | 

### 内容
指定したアカウントが発行したトランザクションの内、指定したアセットに関連するトランザクションのリストを取得する。  
引数のfirst_tx_hashが未指定の場合、最初のトランザクションが返却される。

### 権限
クエリの発行者には、can_get_my_acc_ast_txs権限、またはcan_get_domain_acc_ast_txs権限、またはcan_get_all_acc_ast_txs権限が必要。can_get_my_acc_ast_txs権限の場合はクエリ発行者自身のアカウントのみ、can_get_domain_acc_ast_txs権限の場合はクエリ発行者と同一ドメインに所属するアカウントのトランザクションが取得可能。

### 制限事項
<br>

## getAccountAssets
アカウント内の全てのアセットの状態を取得する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | アセット状態を取得するアカウントID | <account_name>@<domain_id> |
| page_size | ○ | 戻り値で返却されるアセット情報の最大量 | 4294967296未満の正整数 |
| first_asset_id | | ページ先頭のアセットID | <asset_name>#<domain_id> |

### 戻り値
| 戻り値名 | | 内容 | 形式 | 取得方法(Java) |
|:----|:----|:----|:----|:----|
| account_assets | | アカウントに紐付くアセット情報 | 以下の構造を持つオブジェクトの配列 | AccountAssetResponse#  getAccountAssetsList() |
| | asset_id | アセットID | <asset_name>#<domain_id> | AccountAsset#  getAssetId() |
| | account_id | アセット残高を持つアカウント | <account_name>@<domain_id> | AccountAsset#  getAccountId() |
| | balance | アセットの残高 | 0以上 | AccountAsset#  getBalance() |
| total_number | | アカウントが所持している全アセット数 | 4294967296未満の正整数 | AccountAssetResponse#  getTotalNumber() |
| next_asset_id | | 次ページの先頭のアセットID | <asset_name>#<domain_id> | AccountAssetResponse#  getNextAssetId() |  

- 指定されたアカウントの最後のアセットが返却されたaccount_assets配列内に含まれている場合、next_asset_idは空となる

### 例外
クエリ実行エラー時IrohaEEQueryExceptionを送出する。

戻り値は、IrohaEEQueryException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| reason | 原因コード | [原因コード](#原因コード)はIrohaAPIの仕様に準拠する | IrohaEEQueryException#  getErrorResponse().getReasonValue() |
| message | エラーメッセージ | エラーメッセージ | IrohaEEQueryException#  getErrorResponse().getMessage() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEEQueryException#  getStatefullErrorCode() | 

### 内容
指定したアカウントが持つ全てのアセットの残高情報を取得する。  
引数のfirst_asset_idが未指定の場合、最初のページが返却される。

### 権限
クエリの発行者には、can_get_my_acc_ast権限、またはcan_get_domain_acc_ast権限、またはcan_get_all_acc_ast権限が必要。can_get_my_acc_ast権限の場合はクエリ発行者自身のアカウントのみ、can_get_domain_acc_ast権限の場合はクエリ発行者と同一ドメインに所属するアカウントのアセット状態が取得可能。

### 制限事項
<br>

## getAccountDetail
アカウント詳細を取得する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| page_size | ○ | 戻り値で返却されるアセット情報の最大量 | 4294967296未満の正整数 |
| first_record_id_writer | ○ | ページ先頭の詳細情報記入者のアカウントID | <account_name>@<domain_id> |
| first_record_id_key | ○ | ページ先頭の詳細情報のキー | 文字列 |
| account_id | | アカウント詳細を取得するアカウントID | <account_name>@<domain_id> |
| key | | 詳細情報のキー | 文字列 |
| writer | | 詳細情報記入者のアカウントID | <account_name>@<domain_id> |

* account_idが未指定の場合、クエリ作成者のアカウントを指定したものとして扱う

### 戻り値
| 戻り値名 | | 内容 | 形式 | 取得方法(Java) |
|:----|:----|:----|:----|:----|
| detail | | アカウント詳細を含むJSON | JSON | AccountDetailResponse#  getDetail() |
| total_number | | ページ制限なしでクエリに一致するレコード総数 | 4294967296未満の正整数 | AccountDetailResponse#  getTotalNumber() |
| next_record_id | | 次ページの先頭レコード情報 | 以下の構造を持つオブジェクト | AccountDetailResponse#  getNextRecordId() |
| | writer | 次ページ先頭の詳細情報記入者のアカウントID | <account_name>@<domain_id> | AccountDetailRecordId#  getWriter() |
| | key | 次ページ先頭の詳細情報のキー | 文字列 | AccountDetailRecordId#  getKey() |

### 例外
クエリ実行エラー時IrohaEEQueryExceptionを送出する。

戻り値は、IrohaEEQueryException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| reason | 原因コード | [原因コード](#原因コード)はIrohaAPIの仕様に準拠する | IrohaEEQueryException#  getErrorResponse().getReasonValue() |
| message | エラーメッセージ | エラーメッセージ | IrohaEEQueryException#  getErrorResponse().getMessage() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEEQueryException#  getStatefullErrorCode() | 

### 内容
指定したアカウントの詳細情報を取得する。

### 権限
クエリの発行者には、can_get_my_acc_detail権限、またはcan_get_domain_acc_detail権限、またはcan_get_all_acc_detail権限が必要。can_get_my_acc_detail権限の場合はクエリ発行者自身のアカウントのみ、can_get_domain_acc_detail権限の場合はクエリ発行者と同一ドメインに所属するアカウントの詳細情報が取得可能。

### 制限事項
<br>

## getAssetInfo
アセット情報を取得する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| asset_id | ○ | 情報を取得するアセットID | <asset_name>#<domain_id> |

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:----|:----|:----|:----|
| asset_id | アセットID | <asset_name>#<domain_id> | AssetResponse#getAsset().getAssetId() |
| domain_id | アセットに関連するドメイン | RFC1035, RFC1123 | AssetResponse#getAsset().getDomainId() |
| precision | アセット数量の小数点以下の桁数 | 0<=precision<=255 | AssetResponse#getAsset().getPrecision() |

### 例外
クエリ実行エラー時IrohaEEQueryExceptionを送出する。

戻り値は、IrohaEEQueryException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| reason | 原因コード | [原因コード](#原因コード)はIrohaAPIの仕様に準拠する | IrohaEEQueryException#  getErrorResponse().getReasonValue() |
| message | エラーメッセージ | エラーメッセージ | IrohaEEQueryException#  getErrorResponse().getMessage() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEEQueryException#  getStatefullErrorCode() | 

### 内容
指定したアセット情報を取得する。

### 権限
クエリの発行者には、can_read_assets権限が必要。

### 制限事項
<br>

## getRoles
ロール一覧を取得する

### 引数
なし

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:----|:----|:----|:----|
| roles | ロール名の配列 | 文字列の配列 | RolesResponse#getRolesList() |

### 例外
クエリ実行エラー時IrohaEEQueryExceptionを送出する。

戻り値は、IrohaEEQueryException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| reason | 原因コード | [原因コード](#原因コード)はIrohaAPIの仕様に準拠する | IrohaEEQueryException#  getErrorResponse().getReasonValue() |
| message | エラーメッセージ | エラーメッセージ | IrohaEEQueryException#  getErrorResponse().getMessage() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEEQueryException#  getStatefullErrorCode() | 

### 内容
システム上に存在するロールの一覧を取得する。

### 権限
クエリの発行者には、can_get_roles権限が必要。

### 制限事項
<br>

## getRolePermissions
ロールの権限一覧を取得する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| role_id | ○ | 権限情報を取得するロール名 | [a-z_0-9]{1,32} |

### 戻り値
| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:----|:----|:----|:----|
| permissions | 権限の配列 | ex: [can_receive, can_transfer] | RolePermissionsResponse#getPermissionsList() |

### 例外
クエリ実行エラー時IrohaEEQueryExceptionを送出する。

戻り値は、IrohaEEQueryException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| reason | 原因コード | [原因コード](#原因コード)はIrohaAPIの仕様に準拠する | IrohaEEQueryException#  getErrorResponse().getReasonValue() |
| message | エラーメッセージ | エラーメッセージ | IrohaEEQueryException#  getErrorResponse().getMessage() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEEQueryException#  getStatefullErrorCode() | 

### 内容
指定したロールに設定された権限一覧を取得する。

### 権限
クエリの発行者には、can_get_roles権限が必要。

### 制限事項
<br>

## getPeers
ピア一覧を取得する

### 引数
なし

### 戻り値
以下の内容のオブジェクトを持つ配列

| 戻り値名 | | 内容 | 形式 | 取得方法(Java) |
|:----|:----|:----|:----|:----|
| peers || ピアの配列 | 以下の構造を持つオブジェクトの配列 | PeersResponse#getPeersList() |
| | address | ピアのアドレス | IPv4、IPv6、ドメイン名など | Peer#getAddress() |
| | peer_key | ピアの公開鍵 | ed25519公開鍵 | Peer#getPeerKey() |

### 例外
クエリ実行エラー時IrohaEEQueryExceptionを送出する。

戻り値は、IrohaEEQueryException から取得する。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| reason | 原因コード | [原因コード](#原因コード)はIrohaAPIの仕様に準拠する | IrohaEEQueryException#  getErrorResponse().getReasonValue() |
| message | エラーメッセージ | エラーメッセージ | IrohaEEQueryException#  getErrorResponse().getMessage() |
| error_code | エラーコード | ステートフルバリデーションのエラーコード<br>エラーコードはIrohaAPIの仕様に準拠する |  IrohaEEQueryException#  getStatefullErrorCode() | 

### 内容
Irohaネットワーク上に登録されているピアのリストを取得する。

### 権限
クエリの発行者には、can_get_peers権限が必要。

### 制限事項
<br>

# Batch
## sendBatch
ORDEREDモードでバッチを送信する

### 引数
なし

### 戻り値
以下の内容を持つタプルの配列を返却する

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:----|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#getTxHash() |
| status | トランザクションの状態 | "COMMITTED","REJECTED", "STATELESS_VALIDATION_FAILED", "MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |

### 例外
バッチ内トランザクションに1件でもエラーがある場合、IrohaEEBatchTransactionExceptionを送出する。  

例外内部で保持するバッチトランザクション結果はトランザクション毎に保持され、成功したトランザクションも含む。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEEBatchTransactionException#  getResponses()[n].getTxHash() |
| status | トランザクションの状態 | "COMMITTED","REJECTED", "STATELESS_VALIDATION_FAILED", "MST_PENDING" のうちいずれか | IrohaEEBatchTransactionException#  getResponses()[n].getTxStatus().toString() |

### 内容
発行されたバッチ用コマンドをORDEREDモードに設定後、各トランザクションに署名し、Irohaへ送信する。

### 権限
各コマンドの実行にはそれぞれに対応した権限が必要。

### 制限事項
ステートフルバリデーションの検証においてREJECTEDになった場合のエラーコードは出力されないため、エラー原因の特定はできません。
<br>

## sendAtomic
ATOMICモードでバッチを送信する

### 引数
なし

### 戻り値
以下の内容を持つタプルの配列を返却する

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:----|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | ToriiResponse#  getTxHash() |
| status | トランザクションの状態 | "COMMITTED","REJECTED", "STATELESS_VALIDATION_FAILED", "MST_PENDING"のうちいずれか | ToriiResponse#  getTxStatus().toString() |

### 例外
バッチ内トランザクションにエラーがある場合、IrohaEEBatchTransactionExceptionを送出する。  
例外内部で保持するバッチトランザクション結果はトランザクション毎に保持されるが、ATOMICであるため、ステータスは全てREJECTEDとなる。

| 戻り値名 | 内容 | 形式 | 取得方法(Java) |
|:-|:----|:----|:----|
| tx_hash | トランザクションハッシュ | 32バイト長のハッシュ | IrohaEEBatchTransactionException#  getResponses()[n].getTxHash() |
| status | トランザクションの状態 | "REJECTED" | IrohaEEBatchTransactionException#  getResponses()[n].getTxStatus().toString() |

### 内容
発行されたバッチ用コマンドをATOMICモードに設定後、各トランザクションに署名し、Irohaへ送信する。

### 権限
各コマンドの実行にはそれぞれに対応した権限が必要。

### 制限事項
ステートフルバリデーションの検証においてREJECTEDになった場合のエラーコードは出力されません。  
このため、いずれかのトランザクションでエラーが発生し、バッチ全体がREJECTEDとなった場合に、原因となったトランザクションおよびエラー原因の特定はできません。
<br>

## addAssetQuantityForBatch
アセットに数量を追加するバッチ用コマンドを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| asset_id | ○ | アセットID | <asset_name>#<domain_id> |
| amount | ○ | 追加する数量 | 正数 |

- アセットIDは、事前に作成されていなければならない
- アマウントは、作成時のprecisionに従った小数点表記が可能

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| self | バッチ用コマンドを保持した自身のオブジェクト参照 | IrohaEE |

### 内容
トランザクションを発行したアカウントの所持するアセットをamountで指定した数量追加するバッチ用コマンドを発行する。

### 権限
トランザクションの発行者には、can_add_asset_qty権限またはcan_add_domain_asset_qty権限が必要。  
ただし、can_add_domain_asset_qty権限の場合は、トランザクションの発行者が所属するドメイン内のアセットに対してのみ実行可能。

### 制限事項
<br>

## addPeerForBatch
ネットワークにピアを追加するバッチ用コマンドを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| address | ○ | ネットワーク内の解決可能なアドレス | IPv4、IPv6、ドメイン名など |
| peer_key | ○ | ピアの公開鍵 | ed25519公開鍵 |

- 公開鍵は合意形成アルゴリズムで使用される
- 他のピアと同一の公開鍵は使用できない

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| self | バッチ用コマンドを保持した自身のオブジェクト参照 | IrohaEE |

### 内容
ピアネットワークに向けてピアが追加された事実を台帳に書き込むバッチ用コマンドを発行する。

### 権限
トランザクションの発行者には、can_add_peer権限が必要。

### 制限事項
<br>

## addSignatoryForBatch
署名を追加するバッチ用コマンドを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | 署名を追加するアカウントID | <account_name>@<domain_id> |
| public_key | ○ | アカウントに追加する公開鍵 | ed25519公開鍵 |

- アカウントIDは事前に作成されていなければならない

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| self | バッチ用コマンドを保持した自身のオブジェクト参照 | IrohaEE |

### 内容
指定したアカウントに署名を追加するバッチ用コマンドを発行する。

### 権限
トランザクションの発行者には、can_add_signatory権限が必要。


トランザクションの発行者が自身の署名を追加する場合は、can_add_signatory権限が必要。  
トランザクションの発行者が別アカウントに署名を追加する場合は、そのアカウントからcan_add_my_signatory権限が委譲されていることが必要。

### 制限事項
<br>

## appendRoleForBatch
アカウントにロールを追加するバッチ用コマンドを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | ロールを追加するアカウントID | <account_name>@<domain_id> |
| role_name | ○ | システム内で既に規定されたロール名 | [a-z_0-9]{1,32} |

- アカウントIDおよびロールは事前に作成されていなければならない

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| self | バッチ用コマンドを保持した自身のオブジェクト参照 | IrohaEE |

### 内容
指定したアカウントにロールを追加するバッチ用コマンドを発行する。

### 権限
トランザクションの発行者には、can_append_role権限が必要。

### 制限事項
<br>

## createAccountForBatch
アカウントを新規作成するバッチ用コマンドを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_name | ○ | アカウント名 | [a-z_0-9]{1,32} |
| domain_id | ○ | ドメインID | RFC1035, RFC1123 |
| public_key | ○ | アカウントに追加する公開鍵 | ed25519公開鍵 |

- ドメインIDは、事前に作成されていなければならない
- アカウント名はドメイン内で一意でなくてはならない

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| self | バッチ用コマンドを保持した自身のオブジェクト参照 | IrohaEE |

### 内容
指定したドメイン内に新規アカウントを作成するバッチ用コマンドを発行する。

### 権限
トランザクションの発行者には、can_create_account権限が必要。

### 制限事項
<br>

## createAssetForBatch
アセットを発行するバッチ用コマンドを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| asset_name | ○ | アセット名 | [a-z_0-9]{1,32} |
| domain_id | ○ | ドメインID | RFC1035, RFC1123 |
| precision | ○ | コンマ/ドットに後につづく桁数 | 0<=precision<=255 |

- ドメインIDは、事前に作成されていなければならない
- アセット名はドメイン内で一意でなくてはならない

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| self | バッチ用コマンドを保持した自身のオブジェクト参照 | IrohaEE |

### 内容
指定したドメイン内に新規アセットを作成するバッチ用コマンドを発行する。

### 権限
トランザクションの発行者には、can_create_asset権限が必要。

### 制限事項
<br>

## createDomainForBatch
ドメインを作成するバッチ用コマンドを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| domain_id | ○ | ドメインID | RFC1035, RFC1123 |
| default_role | ○ | システム内で既に規定されたロール名 | [a-z_0-9]{1,32} |

- ロールは事前に作成されていなければならない
- ドメインIDはシステム上で一意でなくてはならない

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| self | バッチ用コマンドを保持した自身のオブジェクト参照 | IrohaEE |

### 内容
Irohaネットワークに新たなドメインを作成するバッチ用コマンドを発行する。

### 権限
トランザクションの発行者には、can_create_domain権限が必要。

### 制限事項
<br>

## createRoleForBatch
ロールを作成するバッチ用コマンドを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| role_name | ○ | ロール名 | [a-z_0-9]{1,32} |
| permissions | ○ | 権限の配列 | ex: [can_receive, can_transfer] |

- permissionsにはひとつ以上の権限が設定されていること
- 設定可能な権限は[こちら](https://iroha.readthedocs.io/en/latest/develop/api/permissions.html#list-of-permissions)を参照

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| self | バッチ用コマンドを保持した自身のオブジェクト参照 | IrohaEE |

### 内容
システム上に新たなロールを作成するバッチ用コマンドを発行する。

### 権限
トランザクションの発行者には、can_create_role権限が必要。

### 制限事項
<br>

## detachRoleForBatch
ロールを切り離すバッチ用コマンドを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | ロールを切り離すアカウントID | <account_name>@<domain_id> |
| role_name | ○ | 切り離すロール名 | [a-z_0-9]{1,32} |

- アカウントIDは切り離すロールを持っている必要がある

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| self | バッチ用コマンドを保持した自身のオブジェクト参照 | IrohaEE |

### 内容
指定したアカウントからロールを切り離すバッチ用コマンドを発行する。

### 権限
トランザクションの発行者には、can_detach_role権限が必要。

### 制限事項
<br>

## grantPermissionForBatch
権限を委譲するバッチ用コマンドを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | 権限を委譲するアカウントID | <account_name>@<domain_id> |
| permission | ○ | 委譲する権限 | grantableである権限（下記参照） |

- アカウントIDは事前に作成されていなければならない
- 設定可能なgrantable権限は以下の通り（[こちら](https://iroha.readthedocs.io/en/latest/develop/api/permissions.html#list-of-permissions)も参照）
    - can_add_my_signatory
    - can_remove_my_signatory
    - can_set_my_account_detail
    - can_set_my_quorum
    - can_transfer_my_assets

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| self | バッチ用コマンドを保持した自身のオブジェクト参照 | IrohaEE |

### 内容
トランザクションの発行者が指定したアカウントに対し、指定した権限を委譲するバッチ用コマンドを発行する。

### 権限
トランザクションの発行者には、委譲する権限に対応した権限が必要。

| トランザクション発行者に必要な権限 | 委譲する権限 |
|:----|:----|
| can_grant_can_add_my_signatory | can_add_my_signatory |
| can_grant_can_remove_my_signatory | can_remove_my_signatory |
| can_grant_can_set_my_account_detail | can_set_my_account_detail |
| can_grant_can_set_my_quorum | can_set_my_quorum |
| can_grant_can_transfer_my_assets | can_transfer_my_assets |

### 制限事項
<br>

## removePeerForBatch
Irohaネットワークからピアを除去するバッチ用コマンドを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| public_key | ○ | 除去するピアの公開鍵 | ed25519公開鍵 |

- 指定した公開鍵を持つピアがIrohaネットワーク上に存在している必要がある
- 指定した公開鍵を持つピア以外のピアがIrohaネットワーク上に存在している必要がある

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| self | バッチ用コマンドを保持した自身のオブジェクト参照 | IrohaEE |

### 内容
ピアネットワークに向けてピアが除去された事実を台帳に書き込むバッチ用コマンドを発行する。

### 権限
トランザクションの発行者には、can_remove_peer権限が必要。

### 制限事項
<br>

## removeSignatoryForBatch
署名を削除するバッチ用コマンドを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | アカウントID | <account_name>@<domain_id> |
| public_key | ○ | アカウントから削除する公開鍵 | ed25519公開鍵 |

- アカウントIDは事前に作成されていなければならない
- 削除する公開鍵を除いたアカウントに紐づく公開鍵の数が quorum 以上であることが必要

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| self | バッチ用コマンドを保持した自身のオブジェクト参照 | IrohaEE |

### 内容
指定したアカウントから署名を削除するバッチ用コマンドを発行する。

### 権限
トランザクションの発行者が自身の署名を削除する場合は、can_remove_signatory権限が必要。  
トランザクションの発行者が別アカウントの署名を削除する場合は、そのアカウントからcan_remove_my_signatory権限が委譲されていることが必要。

### 制限事項
<br>

## revokePermissionForBatch
権限を取り消すバッチ用コマンドを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | 権限を取り消すアカウントID | <account_name>@<domain_id> |
| permission | ○ | 取り消す権限 | grantableである権限（下記参照） |

- 取り消そうとする権限が指定するアカウントに対して事前に付与されている必要がある
- 設定可能なgrantable権限は以下の通り（[こちら](https://iroha.readthedocs.io/en/latest/develop/api/permissions.html#list-of-permissions)も参照）
    - can_add_my_signatory
    - can_remove_my_signatory
    - can_set_my_account_detail
    - can_set_my_quorum
    - can_transfer_my_assets

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| self | バッチ用コマンドを保持した自身のオブジェクト参照 | IrohaEE |

### 内容
トランザクションの発行者が指定したアカウントに対して委譲していた権限を取り消すバッチ用コマンドを発行する。

### 権限
トランザクションの発行者には、取り消す権限に対応した権限が必要。

| トランザクション発行者に必要な権限 | 取り消す権限 |
|:----|:----|
| can_grant_can_add_my_signatory | can_add_my_signatory |
| can_grant_can_remove_my_signatory | can_remove_my_signatory |
| can_grant_can_set_my_account_detail | can_set_my_account_detail |
| can_grant_can_set_my_quorum | can_set_my_quorum |
| can_grant_can_transfer_my_assets | can_transfer_my_assets |

### 制限事項
<br>

## setAccountDetailForBatch
アカウントの詳細を設定するバッチ用コマンドを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | 詳細を設定するアカウントID | <account_name>@<domain_id> |
| key | ○ | 設定されるキー | [A-Za-z0-9_]{1,64} |
| value | ○ | キーに対応する値 | 4096バイト以下の文字列 |

- アカウントIDは、事前に作成されていなければならない

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| self | バッチ用コマンドを保持した自身のオブジェクト参照 | IrohaEE |

### 内容
指定したアカウントに紐づくキーバリュー情報を設定するバッチ用コマンドを発行する。  
既にアカウントにキーが存在する場合は、値を上書きする。

### 権限 
トランザクションの発行者が別アカウントの詳細を設定する場合は、can_set_detail権限を保持しているか、そのアカウントからcan_set_my_account_detail権限が委譲されていることが必要。  
(トランザクションの発行者自身のアカウントの詳細を設定する場合は権限は不要） 

### 制限事項
<br>

## setAccountQuorumForBatch
アカウントのクォーラム数を設定するバッチ用コマンドを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | クォーラム数を設定するアカウントID | <account_name>@<domain_id> |
| quorum | ○ | クォーラム数 | 以下の条件を満たす整数 <br> 0 < quorum <= アカウントに紐づいている公開鍵の数 <= 128 |

- アカウントIDは事前に作成されていなければならない。

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| self | バッチ用コマンドを保持した自身のオブジェクト参照 | IrohaEE |


### 内容
指定したアカウントのアカウントのクォーラム数を設定するバッチ用コマンドを発行する。

### 権限
トランザクションの発行者が自身のクォーラム数を設定する場合は、can_set_quorum権限が必要。  
トランザクションの発行者が別アカウントのクォーラム数を設定する場合は、そのアカウントからcan_set_my_quorum権限が委譲されていることが必要。

### 制限事項
<br>

## subtractAssetQuantityForBatch
アセットの数量を減らすバッチ用コマンドを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| asset_id | ○ | アセットID | <asset_name>#<domain_id> |
| amount | ○ | 差し引く数量 | 正数 |

- アセットIDは、事前に作成されていなければならない
- アマウントは、作成時のprecisionに従った小数点表記が可能

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| self | バッチ用コマンドを保持した自身のオブジェクト参照 | IrohaEE |

### 内容
トランザクションを発行したアカウントの所持するアセットをamountで指定した数量減少させるバッチ用コマンドを発行する。

### 権限
トランザクションの発行者には、can_subtract_asset_qty権限またはcan_subtract_domain_asset_qty権限が必要。  
ただし、can_subtract_domain_asset_qty権限の場合は、トランザクションの発行者が所属するドメイン内のアセットに対してのみ実行可能。

### 制限事項
<br>

## transferAssetForBatch
資産を移転させるバッチ用コマンドを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| src_account_id | ○ | 移転元アカウントID | <account_name>@<domain_id> |
| dest_account_id | ○ | 移転先アカウントID | <account_name>@<domain_id> |
| asset_id | ○ | アセットID | <asset_name>#<domain_id> |
| description | ○ | 移転操作に付加するメッセージ | 64バイト以下の文字列 |
| amount | ○ | 移転する数量 | 正数 |

- 移転元および移転先のアカウントが存在すること
- 移転元のアカウントに当該アセットが存在すること
- 移転元アカウントに転送する資産が十分にあり、0ではないこと
- 数量は、作成時のprecisionに従った小数点表記が可能

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| self | バッチ用コマンドを保持した自身のオブジェクト参照 | IrohaEE |

### 内容
指定したアカウントから別のアカウントへ資産を移転させるバッチ用コマンドを発行する。

### 権限
トランザクションの発行者には、can_transfer権限が必要。  
移転先アカウントには、can_receive権限が必要。  
移転元のアカウントにトランザクションの発行者以外のアカウントを設定する場合は、そのアカウントからcan_transfer_my_assets権限が委譲されていることが必要。

### 制限事項
<br>

## compareAndSetAccountDetailForBatch
アカウント詳細の内容を置換するバッチ用コマンドを発行する

### 引数
| 引数名 | 必須 | 内容 | 形式 |
|:----|:----:|:----|:----|
| account_id | ○ | 詳細を設定するアカウントID | <account_name>@<domain_id> |
| key | ○ | 設定されるキー | [A-Za-z0-9_]{1,64} |
| value | ○ | キーに対応する新しい値 | 4096バイト以下の文字列 |
| old_value | | キーに対応する現在の値 | 4096バイト以下の文字列 |

- アカウントIDは、事前に作成されていなければならない

### 戻り値
| 戻り値名 | 内容 | 形式 |
|:----|:----|:----|
| self | バッチ用コマンドを保持した自身のオブジェクト参照 | IrohaEE |

### 内容
キーに対応する現在の値が指定した値であった場合のみ、新しい値でキーバリュー情報を更新するバッチ用コマンドを発行する。  
アカウントに指定のキーが存在しない場合、新しい値でキーバリュー情報が設定される。

### 権限
トランザクションの発行者が自身のアカウントの詳細を設定する場合は、can_get_my_acc_detail権限/can_get_all_acc_detail権限/can_get_domain_acc_detail権限のいずれかが必要。

トランザクションの発行者が別アカウントの詳細を設定する場合は、can_set_detail権限を保持しているか、そのアカウントからcan_set_my_account_detail権限が委譲されている必要がある。加えてcan_get_all_acc_detail権限/can_get_domain_acc_detail権限のいずれかが必要。ただし、can_get_domain_acc_detail権限の場合は、トランザクションの発行者が所属するドメイン内のアカウントに対してのみ実行可能。

| 対象アカウント | 必要となる権限 |
|:----|:----|
| トランザクション発行者自身 | 1. can_get_my_acc_detail / can_get_all_acc_detail / can_get_domain_acc_detail |
| 同一ドメインのアカウント | 1. can_set_detail / (granted) can_set_my_account_detail <br> 2. can_get_all_acc_detail / can_get_domain_acc_detail |
| 別ドメインのアカウント | 1. can_set_detail / (granted) can_set_my_account_detail <br> 2. can_get_all_acc_detail |

### 制限事項
<br>

# 付録

## エラーコード

各 API の Possible Stateful Validation Errors を参照してください。

[Iroha API reference](https://iroha.readthedocs.io/en/latest/develop/api.html)  

## 原因コード

クエリ実行時にエラーが発生した場合の原因コードは以下の通りです。

| 原因コード | 原因 | 説明 |
|:----|:----|:----|
| 0 | STATELESS_INVALID | STATELESS_INVALID が発生した場合
| 1 | STATEFUL_INVALID | STATEFUL_INVALID が発生した場合
| 2 | NO_ACCOUNT | 存在しないアカウントが指定された場合
| 3 | NO_ACCOUNT_ASSETS | 存在しないアカウントアセットが指定された場合
| 4 | NO_ACCOUNT_DETAIL | 存在しないアカウント詳細が指定された場合
| 5 | NO_SIGNATORIES | 存在しない署名が指定された場合
| 6 | NOT_SUPPORTED | 不明なリクエストが送信された場合
| 7 | NO_ASSET | 存在しないアセットが指定された場合
| 8 | NO_ROLES | 存在しないロールが指定された場合
