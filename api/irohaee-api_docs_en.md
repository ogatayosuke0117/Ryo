# IrohaEE function definition document

## Table of contents

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

### Appendix
1. [Error code](#%e3%82%a8%e3%83%a9%e3%83%bc%e3%82%b3%e3%83%bc%e3%83%89)
1. [Cause code](#%e5%8e%9f%e5%9b%a0%e3%82%b3%e3%83%bc%e3%83%89)


# Setting
## setIroha

Configure connection information to Iroha 

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| host | ○ | Iroha Torii address | IPv4, IPv6, domain name, etc. |
| port | ○ | Torii port number | Positive number |
| timeout | | Connection Timeout Time (seconds) | Positive number |

### Return value
None

### Content
Set the connection information to Iroha. 
If this function is not called, it is connected to 127.0.0.1:50051.  

### Limitations
<br>

## setAccount
Set account information to operate and refer to Iroha

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID | <account_name>@<domain_id> |
| private_key | ○ | Private key corresponding to the public key configured for the account | ed25519 private key |

### Return value
None

### Content
Configure an account that issues transactions and queries on iroha

### Limitations
<br>

<br>

# Command
## addAssetQuantity
Add Quantities to an Asset

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| asset_id | ○ | Asset ID | <asset_name>#<domain_id> |
| amount | ○ | Quantity to add | Positive number |

- Asset ID must be created in advance
- Asmount allows decimal notation according to precision when created

### Return value
| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:----|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse #getTxHash () | 
| status | transaction states | one of the "COMMITTED" or "MST _ PENDING" | ToriiResponse# getStatus (). toString () |

### Exception
When command execution error happen, IrohaEETransactionException is transmitted.

The return value is taken from IrohaEETransactionException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | IrohaEETransactionException #getResponse(). getTxHash() |
| status | Transaction status | one of the "REJECTED" or "STATELESS_VALIDATION_FAILED" | IrohaEETransactionException #getResponse(). getTxStatus(). toString() | 
| error_code | Error Code | error codes of stateful validation     error code is compliant with the IrohaAPI specification | IrohaEETransactionException #getStatefullErrorCode() |

### Content
Add the amount of assets owned by the account that issued the transaction.

### Authority
The transaction issuer must have the can _ add _ asset _ qty or can _ add _ domain _ asset _ qty privilege. However, the can _ add _ domain _ asset _ qty privilege can only be executed on assets in the domain to which the transaction issuer belongs.  

### Limitations
<br>

## addPeer
Add peers to the network

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| address | ○ | Resolvable addresses in the network | IPv6 4, IPv6 6, domain name, etc. |
| peer_key | ○ | Peer public key | ed25519 public key |

- Public keys are used in consensus building algorithms
- Cannot use the same public key as another peer

### Return value
| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:---|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse #getTxHash () | 
| status | transaction states | one of the "COMMITTED" or "MST _ PENDING" | ToriiResponse #getTxStatus (). toString () |


### Exception
When command execution error happen, IrohaEETransactionException is transmitted.

The return value is taken from IrohaEETransactionException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | IrohaEETransactionException #getResponse(). getTxHash() |
| status | Transaction status | one of the "REJECTED" or "STATELESS_VALIDATION_FAILED" | IrohaEETransactionException #getResponse(). getTxStatus(). toString() | 
| error_code | Error Code | error codes of stateful validation     error code is compliant with the IrohaAPI specification | IrohaEETransactionException #getStatefullErrorCode() |

### Content
Write the fact that a peer has been added to the peer network in the ledger.

### Authority
The issuer of the transaction must have the can _ add _ peer privilege.

### Limitations
<br>

## addSignatory
Add a signature

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID to which the signature is added | <account_name>@<domain_id> |
| public_key | ○ | Public key to add to the account | ed25519 public key |

- Account ID must be created in advance

### Return value
| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:---|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse #getTxHash () | 
| status | transaction states | one of the "COMMITTED" or "MST _ PENDING" | ToriiResponse #getTxStatus (). toString () |

### Exception
A command execution error IrohaEETransactionException is transmitted.

The return value is taken from IrohaEETransactionException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | IrohaEETransactionException #getResponse(). getTxHash() |
| status | Transaction status | one of the "REJECTED" or "STATELESS_VALIDATION_FAILED" | IrohaEETransactionException #getResponse(). getTxStatus(). toString() | 
| error_code | Error Code | error codes of stateful validation     error code is compliant with the IrohaAPI specification | IrohaEETransactionException #getStatefullErrorCode() |

### Content
Add a signature to the specified account.

### Authority
The issuer of the transaction must have the can _ add _ signatory privilege.


The can _ add _ signatory privilege is required if the issuer of the transaction adds its own signature. If the issuer of the transaction adds a signature to another account, the can_add_my_signatory privilege must be delegated from that account.  

### Limitations
<br>

## appendRole
Add a role to an account

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID to which the role is added | <account_name>@<domain_id> |
| role_name | ○ | Role name already defined in the system | [a-z_0-9{1,32}] |

- Account ID and Roles must be created in advance

### Return value
| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:---|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse #getTxHash () | 
| status | transaction states | one of the "COMMITTED" or "MST _ PENDING" | ToriiResponse #getTxStatus (). toString () |


### Exception
At command execution error, IrohaEETransactionException is transmitted.

The return value is taken from IrohaEETransactionException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | IrohaEETransactionException #getResponse(). getTxHash() |
| status | Transaction status | one of the "REJECTED" or "STATELESS_VALIDATION_FAILED" | IrohaEETransactionException #getResponse(). getTxStatus(). toString() | 
| error_code | Error Code | error codes of stateful validation     error code is compliant with the IrohaAPI specification | IrohaEETransactionException #getStatefullErrorCode() |

### Content
Add a role to the specified account.

### Authority
The issuer of the transaction must have the can _ append _ role privilege.

### Limitations
<br>

## createAccount
Create a new account

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_name | ○ | Account Name | [a-z_0-9{1,32}] |
| domain_id | ○ | Domain ID | RFC1035, RFC1123 |
| public_key | ○ | Public key to add to the account | ed25519 public key |

- Domain ID must be created in advance
- Account name must be unique within the domain

### Return value
| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:---|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse #getTxHash() | 
| status | transaction states | one of the "COMMITTED" or "MST_PENDING" | ToriiResponse #getTxStatus(). toString() |


### Exception
At command execution error IrohaEETransactionException is transmitted.

The return value is taken from IrohaEETransactionException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | IrohaEETransactionException #getResponse(). getTxHash() |
| status | Transaction status | one of the "REJECTED" or "STATELESS_VALIDATION_FAILED" | IrohaEETransactionException #getResponse(). getTxStatus(). toString() | 
| error_code | Error Code | error codes of stateful validation     error code is compliant with the IrohaAPI specification | IrohaEETransactionException #getStatefullErrorCode() |

### Content
Create a new account in the specified domain.

### Authority
The issuer of the transaction must have the can _ create _ account privilege.

### Limitations
<br>

## createAsset
Publishing assets

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| asset_name | ○ | Asset Name | [a-z_0-9{1,32}] |
| domain_id | ○ | Domain ID | RFC1035, RFC1123 |
| precision | ○ | Number of digits after comma / dot | 0<=precision<=255 |

- Domain ID must be created in advance
- Asset names must be unique within the domain

### Return value
| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:---|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse #getTxHash() | 
| status | transaction states | one of the "COMMITTED" or "MST _ PENDING" | ToriiResponse #getTxStatus(). toString() |


### Exception
At command execution error, IrohaEETransactionException is transmitted.

The return value is taken from IrohaEETransactionException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | IrohaEETransactionException #getResponse(). getTxHash() |
| status | Transaction status | one of the "REJECTED" or "STATELESS _ VALIDATION _ FAILED" | IrohaEETransactionException #getResponse(). getTxStatus(). toString() | 
| error_code | Error Codes | Stateful validation error codes Error codes are compliant with the IrohaAPI specification | IrohaEETransactionException #getStatefullErrorCode() |

### Content
Create a new asset in the specified domain.

### Authority
The issuer of the transaction must have the can _ create _ asset privilege.

### Limitations
<br>

## createDomain
Create a domain

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| domain_id | ○ | Domain ID | RFC1035, RFC1123 |
| default_role | ○ | Role name already defined in the system | [a-z_0-9{1,32}] |

- Roles must be created in advance
- Domain ID must be unique on the system

### Return value
| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:---|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse #getTxHash() | 
| status | transaction states | one of the "COMMITTED" or "MST_PENDING" | ToriiResponse #getTxStatus(). toString() |

### Exception
At command execution error, IrohaEETransactionException is transmitted.

The return value is taken from IrohaEETransactionException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | IrohaEETransactionException #getResponse(). getTxHash() |
| status | Transaction status | one of the "REJECTED" or "STATELESS_VALIDATION_FAILED" | IrohaEETransactionException #getResponse(). getTxStatus(). toString() | 
| error_code | Error Code | error codes of stateful validation     error code is compliant with the IrohaAPI specification | IrohaEETransactionException #getStatefullErrorCode() |

### Content
Create a new domain in the Iroha network.

### Authority
The issuer of the transaction must have the can _ create _ domain privilege.

### Limitations
<br>

## createRole
Create a role

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| role_name | ○ | Role Name | [a-z_0-9{1,32}] |
| permissions | ○ | Array of authority | ex: [can_receive, can_transfer] |

- Permissions must have one or more permissions
- See [here](https://iroha.readthedocs.io/en/latest/develop/api/permissions.html#list-of-permissions) for configurable permissions

### Return value
| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:---|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse #getTxHash() | 
| status | transaction states | one of the "COMMITTED" or "MST_PENDING" | ToriiResponse #getTxStatus(). toString() |

### Exception
At command execution error, IrohaEETransactionException is transmitted.

The return value is taken from IrohaEETransactionException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | IrohaEETransactionException #getResponse(). getTxHash() |
| status | Transaction status | one of the "REJECTED" or "STATELESS_VALIDATION_FAILED" | IrohaEETransactionException #getResponse(). getTxStatus(). toString() | 
| error_code | Error Code | error codes of stateful validation     error code is compliant with the IrohaAPI specification | IrohaEETransactionException #getStatefullErrorCode() |

### Content
Create a new role on the system.

### Authority
The issuer of the transaction must have the can _ create _ role privilege.

### Limitations
<br>

## detachRole
Detach Roles

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | The account ID to which the role is detached | <account_name>@<domain_id> |
| role_name | ○ | Role name to detach | [a-z_0-9{1,32}] |

- Account ID must have role to detach

### Return value
| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:---|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse #getTxHash() | 
| status | transaction states | one of the "COMMITTED" or "MST _ PENDING" | ToriiResponse #getTxStatus(). toString() |

### Exception
At command execution error, IrohaEETransactionException is transmitted.

The return value is taken from IrohaEETransactionException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | IrohaEETransactionException #getResponse(). getTxHash() |
| status | Transaction status | one of the "REJECTED" or "STATELESS_VALIDATION_FAILED" | IrohaEETransactionException #getResponse(). getTxStatus(). toString() | 
| error_code | Error Code | error codes of stateful validation     error code is compliant with the IrohaAPI specification | IrohaEETransactionException #getStatefullErrorCode() |

### Content
Detach the role from the specified account.

### Authority
The issuer of the transaction must have the can _ detach _ role privilege.

### Limitations
<br>

## grantPermission
Delegate authority

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID to delegate authority to | <account_name>@<domain_id> |
| permission | ○ | Authority to delegate | Permissions that are grantable (see below) |

- Account ID must be created in advance
- The configurable grantable privileges are below (refer to [here](https://iroha.readthedocs.io/en/latest/develop/api/permissions.html#list-of-permissions))
   - can_add_my_signatory
   - can_remove_my_signatory
   - can_set_my_account_detail
   - can_set_my_quorum
   - can_transfer_my_assets

### Return value
| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:---|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse #getTxHash() | 
| status | transaction states | one of the "COMMITTED" or "MST_PENDING" | ToriiResponse #getTxStatus(). toString() |

### Exception
At command execution error, IrohaEETransactionException is transmitted.

The return value is taken from IrohaEETransactionException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | IrohaEETransactionException #getResponse(). getTxHash() |
| status | Transaction status | one of the "REJECTED" or "STATELESS_VALIDATION_FAILED" | IrohaEETransactionException #getResponse(). getTxStatus(). toString() | 
| error_code | Error Code | error codes of stateful validation     error code is compliant with the IrohaAPI specification | IrohaEETransactionException #getStatefullErrorCode() |

### Content
Delegate specified privileges to the account specified by the transaction issuer.

### Authority
The issuer of the transaction must have the authority to delegate.

| Privileges required by the transaction issuer | Authority to delegate |
|:----|:----|
| can_grant_can_add_my_signatory | can_add_my_signatory |
| can_grant_can_remove_my_signatory | can_remove_my_signatory |
| can_grant_can_set_my_account_detail | can_set_my_account_detail |
| can_grant_can_set_my_quorum | can_set_my_quorum |
| can_grant_can_transfer_my_assets | can_transfer_my_assets |

### Limitations
<br>

## removePeer
Remove peers from the Iroha network

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| public_key | ○ | Public key of the peer to remove | ed25519 public key |

- A peer with the specified public key must exist on the Iroha network
- A peer other than the one with the specified public key must exist on the Iroha network

### Return value
| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:---|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse #getTxHash() | 
| status | transaction states | one of the "COMMITTED" or "MST_PENDING" | ToriiResponse #getTxStatus(). toString() |

### Exception
At command execution error, IrohaEETransactionException is transmitted.

The return value is taken from IrohaEETransactionException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | IrohaEETransactionException #getResponse(). getTxHash() |
| status | Transaction status | one of the "REJECTED" or "STATELESS_VALIDATION_FAILED" | IrohaEETransactionException #getResponse(). getTxStatus(). toString() | 
| error_code | Error Code | error codes of stateful validation     error code is compliant with the IrohaAPI specification | IrohaEETransactionException #getStatefullErrorCode() |

### Content
Write the fact that the peer was removed to the peer network in the ledger.

### Authority
The issuer of the transaction must have the can _ remove _ peer privilege.

### Limitations
<br>

## removeSignatory
Remove a signature

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID | <account_name>@<domain_id> |
| public_key | ○ | Public key to delete from the account | ed25519 public key |

- Account ID must be created in advance
- The number of public keys associated with the account, excluding the public key to be deleted, must be greater than or equal to quorum

### Return value
| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:---|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse #getTxHash() | 
| status | transaction states | one of the "COMMITTED" or "MST_PENDING" | ToriiResponse #getTxStatus(). toString() |


### Exception
At command execution error, IrohaEETransactionException is transmitted.

The return value is taken from IrohaEETransactionException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | IrohaEETransactionException #getResponse(). getTxHash() |
| status | Transaction status | one of the "REJECTED" or "STATELESS_VALIDATION_FAILED" | IrohaEETransactionException #getResponse(). getTxStatus(). toString() | 
| error_code | Error Code | error codes of stateful validation     error code is compliant with the IrohaAPI specification | IrohaEETransactionException #getStatefullErrorCode() |

### Content
Remove a signature from the specified account.

### Authority
The can_remove_signatory privilege is required if the issuer of the transaction wants to remove its own signature. If a transaction issuer removes a signature from another account, the can_remove_my_signatory privilege must be delegated from that account.  

### Limitations
<br>

## revokePermission
Revoke authority

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID to revoke authority | <account_name>@<domain_id> |
| permission | ○ | Power to revoke | Permissions that are grantable (see below) |

- The privileges you want to revoke must be granted in advance to the account you specify
- The configurable grantable privileges are below (refer to [here](https://iroha.readthedocs.io/en/latest/develop/api/permissions.html#list-of-permissions))
   - can_add_my_signatory
   - can_remove_my_signatory
   - can_set_my_account_detail
   - can_set_my_quorum
   - can_transfer_my_assets

### Return value
| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:---|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse #getTxHash() | 
| status | transaction states | one of the "COMMITTED" or "MST_PENDING" | ToriiResponse #getTxStatus(). toString() |


### Exception
At command execution error, IrohaEETransactionException is transmitted.

The return value is taken from IrohaEETransactionException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | IrohaEETransactionException #getResponse(). getTxHash() |
| status | Transaction status | one of the "REJECTED" or "STATELESS _ VALIDATION _ FAILED" | IrohaEETransactionException #getResponse(). getTxStatus(). toString() | 
| error_code | Error Codes | Stateful validation error codes Error codes are compliant with the IrohaAPI specification | IrohaEETransactionException #getStatefullErrorCode() |

### Content
Revoke the authority delegated by the transaction issuer to the specified account.

### Authority
The issuer of the transaction must have the authority to revoke.

| Privileges required by the transaction issuer | Power to revoke |
|:----|:----|
| can_grant_can_add_my_signatory | can_add_my_signatory |
| can_grant_can_remove_my_signatory | can_remove_my_signatory |
| can_grant_can_set_my_account_detail | can_set_my_account_detail |
| can_grant_can_set_my_quorum | can_set_my_quorum |
| can_grant_can_transfer_my_assets | can_transfer_my_assets |

### Limitations
<br>

## setAccountDetail
Set Account Details

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID to set details | <account_name>@<domain_id> |
| key | ○ | Keys to be set | [A-Za-z0-9_{1,64}] |
| value | ○ | Value corresponding to the key | Character string of 4096 bytes or less |

- Account ID must be created in advance

### Return value
| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:---|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse #getTxHash() | 
| status | transaction states | one of the "COMMITTED" or "MST_PENDING" | ToriiResponse #getTxStatus(). toString() |

### Exception
At command execution error, IrohaEETransactionException is transmitted.

The return value is taken from IrohaEETransactionException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | IrohaEETransactionException #getResponse(). getTxHash() |
| status | Transaction status | one of the "REJECTED" or "STATELESS_VALIDATION_FAILED" | IrohaEETransactionException #getResponse(). getTxStatus(). toString() | 
| error_code | Error Code | error codes of stateful validation     error code is compliant with the IrohaAPI specification | IrohaEETransactionException #getStatefullErrorCode() |

### Content
Sets the key value information associated with the specified account. If the account already has a key, overwrite the value.  

### Authority
If the issuer of the transaction wants to set details for another account, it must either have the can _ set _ detail privilege or have delegated the can _ set _ my _ account _ detail privilege from that account. (No permissions are required to set details for the transaction issuer's own account)  

### Limitations
<br>

## setAccountQuorum
Set the quorum for an account

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID to set the quorum | <account_name>@<domain_id> |
| quorum | ○ | Quorum | Integer 0 <quorum <= number of public keys associated with the account <= 128<br> |

- The account ID must be created in advance.

### Return value
| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:---|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse #getTxHash() | 
| status | transaction states | one of the "COMMITTED" or "MST _ PENDING" | ToriiResponse #getTxStatus(). toString() |

### Exception
At command execution error, IrohaEETransactionException is transmitted.

The return value is taken from IrohaEETransactionException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | IrohaEETransactionException #getResponse(). getTxHash() |
| status | Transaction status | one of the "REJECTED" or "STATELESS_VALIDATION_FAILED" | IrohaEETransactionException #getResponse(). getTxStatus(). toString() | 
| error_code | Error Code | error codes of stateful validation     error code is compliant with the IrohaAPI specification | IrohaEETransactionException #getStatefullErrorCode() |

### Content
Sets the quorum count for the account for the specified account.

### Authority
The can _ set _ quorum privilege is required if the transaction issuer wants to set its own quorum count. If the transaction issuer sets the quorum count for another account, the can_set_my_quorum privilege must be delegated from that account.  

### Limitations
<br>

## subtractAssetQuantity
Reduce the quantity of assets

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| asset_id | ○ | Asset ID | <asset_name>#<domain_id> |
| amount | ○ | The quantity to subtract | Positive number |

- Asset ID must be created in advance
- Asmount allows decimal notation according to precision when created

### Return value
| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:---|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse #getTxHash() | 
| status | transaction states | one of the "COMMITTED" or "MST_PENDING" | ToriiResponse #getTxStatus(). toString() |

### Exception
At command execution error, IrohaEETransactionException is transmitted.

The return value is taken from IrohaEETransactionException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | IrohaEETransactionException #getResponse(). getTxHash() |
| status | Transaction status | one of the "REJECTED" or "STATELESS_VALIDATION_FAILED" | IrohaEETransactionException #getResponse(). getTxStatus(). toString() | 
| error_code | Error Code | error codes of stateful validation     error code is compliant with the IrohaAPI specification | IrohaEETransactionException #getStatefullErrorCode() |

### Content
Decrements the amount of assets owned by the account that issued the transaction.

### Authority
The transaction issuer must have the can_subtract_asset_qty or can_subtract_domain_asset_qty privilege. However, the can_subtract_domain_asset_qty privilege can only be executed on assets in the domain to which the transaction issuer belongs.  

### Limitations
<br>

## transferAsset
Transfer the assets

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| src_account_id | ○ | Source Account ID | <account_name>@<domain_id> |
| dest_account_id | ○ | Transferee Account ID | <account_name>@<domain_id> |
| asset_id | ○ | Asset ID | <asset_name>#<domain_id> |
| description | ○ | Message attached to the transfer operation | Character string of 64 bytes or less |
| amount | ○ | Quantity to be transferred | Positive number |

- Source and destination accounts must exist
- The asset must exist in the account from which it was transferred
- Sufficient assets to transfer to the source account, not 0
- Quantities can be expressed as decimal points according to precision at creation

### Return value
| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:---|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse #getTxHash() | 
| status | transaction states | one of the "COMMITTED" or "MST_PENDING" | ToriiResponse #getTxStatus(). toString() |

### Exception
At command execution error, IrohaEETransactionException is transmitted.

The return value is taken from IrohaEETransactionException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | IrohaEETransactionException #getResponse(). getTxHash() |
| status | Transaction status | one of the "REJECTED" or "STATELESS_VALIDATION_FAILED" | IrohaEETransactionException #getResponse(). getTxStatus(). toString() | 
| error_code | Error Code | error codes of stateful validation     error code is compliant with the IrohaAPI specification | IrohaEETransactionException #getStatefullErrorCode() |

### Content
Transfer assets from one account to another.

### Authority
The issuer of the transaction must have the can_transfer privilege. 
The relocation account must have the can_receive privilege. 
If you want the source account to have an account other than the issuer of the transaction, the can_transfer_my_assets privilege must be delegated to it.    

### Limitations
<br>

## compareAndSetAccountDetail
Replace the contents of account details

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID to set details | <account_name>@<domain_id> |
| key | ○ | Keys to be set | [A-Za-z0-9_{1,64}] |
| value | ○ | New value corresponding to the key | Character string of 4096 bytes or less |
| old_value | | Current value corresponding to the key | Character string of 4096 bytes or less |

- Account ID must be created in advance

### Return value
| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:---|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse #getTxHash() | 
| status | transaction states | one of the "COMMITTED" or "MST_PENDING" | ToriiResponse #getTxStatus(). toString() |

### Exception
At command execution error, IrohaEETransactionException is transmitted.

The return value is taken from IrohaEETransactionException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | IrohaEETransactionException #getResponse(). getTxHash() |
| status | Transaction status | one of the "REJECTED" or "STATELESS_VALIDATION_FAILED" | IrohaEETransactionException #getResponse(). getTxStatus(). toString() | 
| error_code | Error Code | error codes of stateful validation     error code is compliant with the IrohaAPI specification | IrohaEETransactionException #getStatefullErrorCode() |

### Content
Update the key value information with the new value only if the current value corresponding to the key is the specified value. If the specified key does not exist in the account, the new value is set to the key value information.  

### Authority
The issuer of the transaction must have the can_get_my_acc_detail, can_get_all_acc_detail, or can_get_domain_acc_detail permissions to set details for his account.

If the issuer of the transaction wants to set details for another account, it must either have the can_set_detail privilege or have delegated the can_set_my_account_detail privilege from that account. Can_get_all_acc_detail or can_get_domain_acc_detail. However, the can_get_domain_acc_detail privilege can only be run against accounts in the domain to which the transaction issuer belongs.

| Target Account | Necessary authority |
|:----|:----|
| Transaction issuer itself | 1. can_get_my_acc_detail / can_get_all_acc_detail / can_get_domain_acc_detail |
| Accounts in the same domain | 1. can_set_detail / (granted) can_set_my_account_detail<br>2. can_get_all_acc_detail / can_get_domain_acc_detail<br> |
| Accounts in another domain | 1. can_set_detail / (granted) can_set_my_account_detail<br>2. can_get_all_acc_detail<br> |

### Limitations
<br>


# Query

## getAccount
Get account status

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | 0 | ID of the account whose status you want to query | <account_name>@<domain_id> |

### Return value
| Return Value Name | Content | Format | Retrieval Method (Java) |
|:----|:----|:----|:----|
| account_id | Account ID | <account_name>@<domain_id> | AccountResponse# getAccount().getAccountId() |
| domain_id | Domain ID | RFC1035, RFC1123 | AccountResponse# getAccount().getDomainId() |
| quorum | Number of signers required to make the transaction valid | Integer between 1 and 128 | AccountResponse# getAccount().getQuorum() |
| json_data | Key value information associated with the account | JSON | AccountResponse# getAccount().getJsonData() |
| account_roles | Array of role names existing on the system | Array of strings | AccountResponse# getAccountRolesList() |

### Exception
A query execution error IrohaEEQueryException is sent.

The return value is taken from IrohaEEQueryException.

| Return Value Name | Content | Format | Retrieval Methods (Java) |
|:-|:----|:----|:----| 
| Reason | Cause code | [Cause code](#Causecode) is based on IrohaAPI specification | IrohaEEQueryException #getErrorResponse(). getReasonValue() | error  message | error message | IrohaEEQueryException #getErrorResponse(). getMessage() | error _ code | error code of stateful validation | error code of stateful validation<br>error code is based on IrohaAPI specification | IrohaEEQueryException#getStatefullErrorCode()

### Content
Gets the status of the specified account.

### Authority
The query issuer must have the can _ get _ my _ account or can _ get _ domain _ account or can _ get _ all _ account permissions. The can _ get _ my _ account and can _ get _ domain _ account privileges allow you to get the status of only the query issuer's own account and the can _ get _ domain _ account privileges allow you to get the status of an account that belongs to the same domain as the query issuer.

### Limitations
<br>

## getBlock
Get block

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| height | ○ | Block height to get | Integer between 1 and 2 ^ 64 |

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| block | Retrieved Blocks | Block structure |

### Exception
A query execution error IrohaEEQueryException is sent.

The return value is taken from IrohaEEQueryException.

Return Value Name Content Format Retrieval Methods (Java) : - : ---- -- : ---- -- reason Cause Code is IrohaAPI compliant IrohaEEQueryException #getErrorResponse (). getReasonValue () message error message error message IrohaEEQueryException #getErrorResponse (). getMessage () error _ code Stateful validation error code Error Code is IrohaAPI compliant IrohaEEQueryException #getStatefullErrorCode ()[](#Causecode)<br>

### Content
Gets the specified block.

### Authority
The query issuer must have the can _ get _ blocks privilege.

### Limitations
<br>

## getSignatories
Get a signature tied to an account

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | ID of the account requesting the signature | <account_name>@<domain_id> |

### Return value
| Return Value Name | Content | Format | Retrieval Method (Java) |
|:----|:----|:----|:----|
| keys | Arrangement of public keys | Sequence of ed 25519 | SignatoriesResponse#getKeysList() |

### Exception
A query execution error IrohaEEQueryException is sent.

The return value is taken from IrohaEEQueryException.

Return Value Name Content Format Retrieval Methods (Java) : - : ---- -- : ---- -- reason Cause Code is IrohaAPI compliant IrohaEEQueryException #getErrorResponse (). getReasonValue () message error message error message IrohaEEQueryException #getErrorResponse (). getMessage () error _ code Stateful validation error code Error Code is IrohaAPI compliant IrohaEEQueryException #getStatefullErrorCode ()[](#Causecode)<br>

### Content
Gets the signature associated with the specified account.

### Authority
The query issuer must have can _ get _ my _ signatories or can _ get _ domain _ signatories or can _ get _ all _ signatories permissions. The can _ get _ my _ signatories and can _ get _ domain _ signatories permissions allow you to get the signature of only the query issuer's own account and the can _ get _ domain _ water permissions allow you to get the signature of an account that belongs to the same domain as the query issuer.

### Limitations
<br>

## getTransactions
Get a transaction

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| tx_hashes | 0 | Array of hashes for the transactions to retrieve | 32 byte long hash array |

### Return value
| Return Value Name | Content | Format | Retrieval Method (Java) |
|:----|:----|:----|:----|
| transactions | Array of committed transactions | Array of transactions | TransactionsResponse#getTransactionsList() |

### Exception
A query execution error IrohaEEQueryException is sent.

The return value is taken from IrohaEEQueryException.

Return Value Name Content Format Retrieval Methods (Java) : - : ---- -- : ---- -- reason Cause Code is IrohaAPI compliant IrohaEEQueryException #getErrorResponse (). getReasonValue () message error message error message IrohaEEQueryException #getErrorResponse (). getMessage () error _ code Stateful validation error code Error Code is IrohaAPI compliant IrohaEEQueryException #getStatefullErrorCode ()[](#Causecode)<br>

### Content
Get the specified transaction.

### Authority
The query issuer must have the can _ get _ my _ txs or can _ get _ all _ txs privilege. With the can _ get _ my _ txs privilege, only transactions issued by the query issuer itself can be retrieved.

### Limitations
<br>

## getPendingTransactions
Get pending transactions

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| page_size | ○ | Maximum amount of transactions returned with return values | Positive integer |
| first_tx_hash | | Transaction hash at the top of the page | 32 byte long hash |

### Return value
| Return Value Name | Content | Format | Retrieval Method (Java) |
|:----|:----|:----|:----|
| transactions | Array of pending transactions | Array of transactions | PendingTransactionsPageResponse# getTransactionsList() |
| all_transactions_size | Number of transactions stored on the system | Integer | PendingTransactionsPageResponse# getAllTransactionsSize() |
| first_tx_hash | Transaction hash at the beginning of the next batch | 32 byte long hash | PendingTransactionsPageResponse# getNextBatchInfo().getFirstTxHash() |
| batch_size | Minimum page size required to retrieve the next batch | Positive integer | PendingTransactionsPageResponse# getNextBatchInfo().getBatchSize() |

### Exception
A query execution error IrohaEEQueryException is sent.

The return value is taken from IrohaEEQueryException.

Return Value Name Content Format Retrieval Methods (Java) : - : ---- -- : ---- -- reason Cause Code is IrohaAPI compliant IrohaEEQueryException #getErrorResponse (). getReasonValue () message error message error message IrohaEEQueryException #getErrorResponse (). getMessage () error _ code Stateful validation error code Error Code is IrohaAPI compliant IrohaEEQueryException #getStatefullErrorCode ()[](#Causecode)<br>

### Content
Get a list of pending multisignature transactions or batches of transactions issued by the query issuer itself.

### Authority
None

### Limitations
<br>

## getAccountTransactions
Capture transactions for each account

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID requesting transaction information | <account_name>@<domain_id> |
| page_size | ○ | Maximum amount of transactions returned with return values | Positive integer |
| first_tx_hash | | Transaction hash at the top of the page | 32 byte long hash |

### Return value
| Return Value Name | Content | Format | Retrieval Method (Java) |
|:----|:----|:----|:----|
| transactions | Array of transactions issued by the specified account | Array of transactions | TransactionsPageResponse# getTransactionsList() |
| all_transactions_size | Number of transactions stored on the system | Integer | TransactionsPageResponse# getAllTransactionsSize() |
| first_tx_hash | Transaction hash at the top of the next page | 32 byte long hash | TransactionsPageResponse# getNextTxHash() |

- First _ tx _ hash is empty if the last transaction for the specified account is contained in the returned array

### Exception
A query execution error IrohaEEQueryException is sent.

The return value is taken from IrohaEEQueryException.

Return Value Name Content Format Retrieval Methods (Java) : - : ---- -- : ---- -- reason Cause Code is IrohaAPI compliant IrohaEEQueryException #getErrorResponse (). getReasonValue () message error message error message IrohaEEQueryException #getErrorResponse (). getMessage () error _ code Stateful validation error code Error Code is IrohaAPI compliant IrohaEEQueryException #getStatefullErrorCode ()[](#Causecode)<br>

### Content
Gets a list of transactions issued by the specified account. If the first _ tx _ hash argument is unspecified, the first transaction is returned.  

### Authority
The query issuer must have the can _ get _ my _ acc _ txs or can _ get _ domain _ acc _ txs or can _ get _ all _ acc _ txs privilege. The can _ get _ my _ acc _ txs privilege allows transactions to be retrieved only from the query issuer's own account ; the can _ get _ domain _ acc _ txs privilege allows transactions to be retrieved from an account that belongs to the same domain as the query issuer.

### Limitations
<br>

## getAccountAssetTransactions
Capture transactions related to assets per account

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID requesting transaction information | <account_name>@<domain_id> |
| asset_id | ○ | Asset ID to filter transactions | <asset_name>#<domain_id> |
| page_size | ○ | Maximum amount of transactions returned with return values | Positive integer |
| first_tx_hash | | Transaction hash at the top of the page | 32 byte long hash |

### Return value
| Return Value Name | Content | Format | Retrieval Method (Java) |
|:----|:----|:----|:----|
| transactions | Array of transactions associated with the specified account and asset | Array of transactions | TransactionsPageResponse# getTransactionsList() |
| all_transactions_size | Number of transactions stored on the system | Integer | TransactionsPageResponse# getAllTransactionsSize() |
| first_tx_hash | Transaction hash at the top of the next page | 32 byte long hash | TransactionsPageResponse# getNextTxHash() |

- First _ tx _ hash is empty if the last transaction for the specified account is contained in the returned array

### Exception
A query execution error IrohaEEQueryException is sent.

The return value is taken from IrohaEEQueryException.

Return Value Name Content Format Retrieval Methods (Java) : - : ---- -- : ---- -- reason Cause Code is IrohaAPI compliant IrohaEEQueryException #getErrorResponse (). getReasonValue () message error message error message IrohaEEQueryException #getErrorResponse (). getMessage () error _ code Stateful validation error code Error Code is IrohaAPI compliant IrohaEEQueryException #getStatefullErrorCode ()[](#Causecode)<br>

### Content
Gets a list of transactions issued by the specified account that pertain to the specified asset. If the first _ tx _ hash argument is unspecified, the first transaction is returned.  

### Authority
The query issuer must have the can _ get _ my _ acc _ ast _ txs or can _ get _ domain _ acc _ ast _ txs or can _ get _ all _ acc _ ast _ txs privilege. The can _ get _ my _ acc _ ast _ txs privilege allows transactions to be retrieved only from the query issuer's own account ; the can _ get _ domain _ acc _ ast _ txs privilege allows transactions to be retrieved from an account that belongs to the same domain as the query issuer.

### Limitations
<br>

## getAccountAssets
Get the status of all assets in an account

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID to get asset state from | <account_name>@<domain_id> |
| page_size | ○ | Maximum amount of asset information returned with return values | Positive integer less than 4294967296 |
| first_asset_id | | Asset ID at the top of the page | <asset_name>#<domain_id> |

### Return value
| Return Value Name | | Content | Format | Retrieval Method (Java) |
|:----|:----|:----|:----|:----|
| account_assets | | Asset information associated with the account | Array of objects with the following structure | AccountAssetResponse# getAccountAssetsList() |
| | asset_id | Asset ID | <asset_name>#<domain_id> | AccountAsset# getAssetId() |
| | account_id | Accounts with asset balances | <account_name>@<domain_id> | AccountAsset# getAccountId() |
| | balance | Asset Balance | 0 or more | AccountAsset# getBalance() |
| total_number | | Total number of assets the account has | Positive integer less than 4294967296 | AccountAssetResponse# getTotalNumber() |
| next_asset_id | | Asset ID at the top of the next page | <asset_name>#<domain_id> | AccountAssetResponse# getNextAssetId() |

- If the last asset for the specified account is contained within the returned account _ assets array, the next _ asset _ id is empty

### Exception
A query execution error IrohaEEQueryException is sent.

The return value is taken from IrohaEEQueryException.

Return Value Name Content Format Retrieval Methods (Java) : - : ---- -- : ---- -- reason Cause Code is IrohaAPI compliant IrohaEEQueryException #getErrorResponse (). getReasonValue () message error message error message IrohaEEQueryException #getErrorResponse (). getMessage () error _ code Stateful validation error code Error Code is IrohaAPI compliant IrohaEEQueryException #getStatefullErrorCode ()[](#Causecode)<br>

### Content
Retrieve the balance information for all assets in the specified account. If the first _ asset _ id argument is unspecified, the first page is returned.  

### Authority
The query issuer must have the can _ get _ my _ acc _ ast or can _ get _ domain _ acc _ ast or can _ get _ all _ acc _ ast permissions. The can _ get _ my _ acc _ ast and can _ get _ domain _ acc _ ast permissions retrieve the asset state of only the query issuer's own account and the same domain as the query issuer, respectively.

### Limitations
<br>

## getAccountDetail
Get account details

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| page_size | 0 | Maximum amount of asset information returned with return values | Positive integer less than 4294967296 |
| first_record_id_writer | 0 | The account ID of the person who filled out the detail information at the top of the page | <account_name>@<domain_id> |
| first_record_id_key | 0 | Detail keys at the top of the page | String |
| account_id | | Account ID to get account details | <account_name>@<domain_id> |
| key | | Detail Key | String |
| writer | | Detailed Information Entry Account ID | <account_name>@<domain_id> |

* If account _ id is not specified, the query creator's account is treated as specified

### Return value
| Return Value Name | | Content | Format | Retrieval Method (Java) |
|:----|:----|:----|:----|:----|
| detail | | JSON with account details | JSON | AccountDetailResponse# getDetail() |
| total_number | | The total number of records that match the query without the page limit | Positive integer less than 4294967296 | AccountDetailResponse# getTotalNumber() |
| next_record_id | | First record information on the next page | Objects with the following structure | AccountDetailResponse# getNextRecordId() |
| | writer | Account ID of the person who filled out the detailed information at the top of the next page | <account_name>@<domain_id> | AccountDetailRecordId# getWriter() |
| | key | Keys for detailed information at the top of the next page | String | AccountDetailRecordId# getKey() |

### Exception
A query execution error IrohaEEQueryException is sent.

The return value is taken from IrohaEEQueryException.

Return Value Name Content Format Retrieval Methods (Java) : - : ---- -- : ---- -- reason Cause Code is IrohaAPI compliant IrohaEEQueryException #getErrorResponse (). getReasonValue () message error message error message IrohaEEQueryException #getErrorResponse (). getMessage () error _ code Stateful validation error code Error Code is IrohaAPI compliant IrohaEEQueryException #getStatefullErrorCode ()[](#Causecode)<br>

### Content
Get detailed information for the specified account.

### Authority
The query issuer must have the can _ get _ my _ acc _ detail or can _ get _ domain _ acc _ detail or can _ get _ all _ acc _ detail permissions. The can _ get _ my _ acc _ detail privilege allows you to retrieve details only for the query issuer's own account ; the can _ get _ domain _ acc _ detail privilege allows you to retrieve details for an account that belongs to the same domain as the query issuer.

### Limitations
<br>

## getAssetInfo
Get asset information

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| asset_id | ○ | Asset ID from which to retrieve information | <asset_name>#<domain_id> |

### Return value
| Return Value Name | Content | Format | Retrieval Method (Java) |
|:----|:----|:----|:----|
| asset_id | Asset ID | <asset_name>#<domain_id> | AssetResponse#getAsset().getAssetId() |
| domain_id | Domain associated with the asset | RFC1035, RFC1123 | AssetResponse#getAsset().getDomainId() |
| precision | Number of decimal places for asset quantity | 0<=precision<=255 | AssetResponse#getAsset().getPrecision() |

### Exception
A query execution error IrohaEEQueryException is sent.

The return value is taken from IrohaEEQueryException.

Return Value Name Content Format Retrieval Methods (Java) : - : ---- -- : ---- -- reason Cause Code is IrohaAPI compliant IrohaEEQueryException #getErrorResponse (). getReasonValue () message error message error message IrohaEEQueryException #getErrorResponse (). getMessage () error _ code Stateful validation error code Error Code is IrohaAPI compliant IrohaEEQueryException #getStatefullErrorCode ()[](#Causecode)<br>

### Content
Get the specified asset information.

### Authority
The query issuer must have the can _ read _ assets privilege.

### Limitations
<br>

## getRoles
Get a list of roles

### Argument
None

### Return value
| Return Value Name | Content | Format | Retrieval Method (Java) |
|:----|:----|:----|:----|
| roles | Role name array | Array of strings | RolesResponse#getRolesList() |

### Exception
A query execution error IrohaEEQueryException is sent.

The return value is taken from IrohaEEQueryException.

Return Value Name Content Format Retrieval Methods (Java) : - : ---- -- : ---- -- reason Cause Code is IrohaAPI compliant IrohaEEQueryException #getErrorResponse (). getReasonValue () message error message error message IrohaEEQueryException #getErrorResponse (). getMessage () error _ code Stateful validation error code Error Code is IrohaAPI compliant IrohaEEQueryException #getStatefullErrorCode ()[](#Causecode)<br>

### Content
Get a list of the roles that exist on the system.

### Authority
The query issuer must have the can _ get _ roles privilege.

### Limitations
<br>

## getRolePermissions
Get the permissions list for a role

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| role_id | ○ | The name of the role from which to obtain permission information | [a-z_0-9{1,32}] |

### Return value
| Return Value Name | Content | Format | Retrieval Method (Java) |
|:----|:----|:----|:----|
| permissions | Array of authority | ex: can_receive, can_transfer[] | RolePermissionsResponse#getPermissionsList() |

### Exception
A query execution error IrohaEEQueryException is sent.

The return value is taken from IrohaEEQueryException.

Return Value Name Content Format Retrieval Methods (Java) : - : ---- -- : ---- -- reason Cause Code is IrohaAPI compliant IrohaEEQueryException #getErrorResponse (). getReasonValue () message error message error message IrohaEEQueryException #getErrorResponse (). getMessage () error _ code Stateful validation error code Error Code is IrohaAPI compliant IrohaEEQueryException #getStatefullErrorCode ()[](#Causecode)<br>

### Content
Gets the list of permissions set for the specified role.

### Authority
The query issuer must have the can _ get _ roles privilege.

### Limitations
<br>

## getPeers
Get a list of peers

### Argument
None

### Return value
An array with the following objects

| Return Value Name | | Content | Format | Retrieval Method (Java) |
|:----|:----|:----|:----|:----|
| peers | Array of peers | Array of objects with the following structure | PeersResponse#getPeersList() |
| | address | Peer address | IPv6 4, IPv6 6, domain name, etc. | Peer#getAddress() |
| | peer_key | Peer public key | Ed 25519 public key | Peer#getPeerKey() |

### Exception
A query execution error IrohaEEQueryException is sent.

The return value is taken from IrohaEEQueryException.

Return Value Name Content Format Retrieval Methods (Java) : - : ---- -- : ---- -- reason Cause Code is IrohaAPI compliant IrohaEEQueryException #getErrorResponse (). getReasonValue () message error message error message IrohaEEQueryException #getErrorResponse (). getMessage () error _ code Stateful validation error code Error Code is IrohaAPI compliant IrohaEEQueryException #getStatefullErrorCode ()[](#Causecode)<br>

### Content
Obtain a list of the peers registered on the Iroha network.

### Authority
The query issuer must have the can _ get _ peers privilege.

### Limitations
<br>

# Batch
## sendBatch
Submit a batch in ORDERED mode

### Argument
None

### Return value
Returns an array of tuples with

| Return Value Name | Content | Format | Retrieval Method (Java) |
|:----|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse#getTxHash() |
| status | Transaction State | "COMMITTED", "REJECTED", "STATELESS _ VALIDATION _ FAILED", or "MST _ PENDING" | ToriiResponse# getTxStatus().toString() |

### Exception
If there are even 1 errors in the transaction in the batch, IrohaEEBatchTransactionException is sent.

Batch transaction results held within an exception are held for each transaction, including successful transactions.

Return Value Name Content Format Retrieval Methods (Java) : - : ---- : ---- -- tx _ hash Transaction hash 32 byte long hash IrohaEEBatchTransactionException #getResponses () n. getTxHash () status Transaction status "COMMITTED", "REJECTED", "STATELESS _ VALIDATION _ FAILED", or "MST _ PENDING" IrohaEEBatchTransactionException #getResponses () n. getTxStatus (). toString ()[][]

### Content
After setting the issued batch command to ORDERED mode, sign each transaction and send it to Iroha.

### Authority
Each command requires its own authority to execute.

### Limitations
If the stateful validation is rejected, the error code is not output, and the cause of the error cannot be determined.<br>

## sendAtomic
Send batch in atomic mode

### Argument
None

### Return value
Returns an array of tuples with

| Return Value Name | Content | Format | Retrieval Method (Java) |
|:----|:----|:----|:----|
| tx_hash | Transaction hash | 32 byte long hash | ToriiResponse# getTxHash() |
| status | Transaction State | "COMMITTED", "REJECTED", "STATELESS _ VALIDATION _ FAILED", or "MST _ PENDING" | ToriiResponse# getTxStatus().toString() |

### Exception
If there is an error in the transaction in the batch, IrohaEEBatchTransactionException is sent. Batch transaction results held within the exception are held for each transaction, but since they are atomic, the status is all REJECTED.  

Return Value Name Content Format Retrieval Methods (Java) : - : ---- : ---- -- tx _ hash Transaction Hash 32 byte long IrohaEEBatchTransactionException #getResponses () n. getTxHash () status Transaction Status "REJECTED" IrohaEEBatchTransactionException #getResponses () n. getTxStatus (). toString ()[][]

### Content
After setting the issued batch command to atomic mode, sign each transaction and send it to Iroha.

### Authority
Each command requires its own authority to execute.

### Limitations
If stateful validation is rejected, no error code is output. Therefore, if an error occurs in one of the transactions and the entire batch is rejected, you cannot determine the transaction that caused the error and the cause of the error.  <br>

## addAssetQuantityForBatch
Issue batch commands to add quantities to assets

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| asset_id | ○ | Asset ID | <asset_name>#<domain_id> |
| amount | ○ | Quantity to add | Positive number |

- Asset ID must be created in advance
- Asmount allows decimal notation according to precision when created

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| self | Own object reference holding the batch command | IrohaEE |

### Content
Issue a batch command to add the amount of assets held by the account that issued the transaction.

### Authority
The transaction issuer must have the can _ add _ asset _ qty or can _ add _ domain _ asset _ qty privilege. However, the can _ add _ domain _ asset _ qty privilege can only be executed on assets in the domain to which the transaction issuer belongs.  

### Limitations
<br>

## addPeerForBatch
Issue a batch command to add peers to the network

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| address | ○ | Resolvable addresses in the network | IPv6 4, IPv6 6, domain name, etc. |
| peer_key | ○ | Peer public key | Ed 25519 public key |

- Public keys are used in consensus building algorithms
- Cannot use the same public key as another peer

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| self | Own object reference holding the batch command | IrohaEE |

### Content
Issue a batch command to write the fact that a peer has been added to the ledger for the peer network.

### Authority
The issuer of the transaction must have the can _ add _ peer privilege.

### Limitations
<br>

## addSignatoryForBatch
Issue a batch command to add a signature

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID to which the signature is added | <account_name>@<domain_id> |
| public_key | ○ | Public key to add to the account | Ed 25519 public key |

- Account ID must be created in advance

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| self | Own object reference holding the batch command | IrohaEE |

### Content
Issue a batch command to add a signature to the specified account.

### Authority
The issuer of the transaction must have the can _ add _ signatory privilege.


The can _ add _ signatory privilege is required if the issuer of the transaction adds its own signature. If the issuer of the transaction adds a signature to another account, the can _ add _ my _ signatory privilege must be delegated from that account.  

### Limitations
<br>

## appendRoleForBatch
Issue a batch command to add a role to an account

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID to which the role is added | <account_name>@<domain_id> |
| role_name | ○ | Role name already defined in the system | [a-z_0-9{1,32}] |

- Account IDs and Roles must be created in advance

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| self | Own object reference holding the batch command | IrohaEE |

### Content
Issue a batch command to add roles to the specified account.

### Authority
The issuer of the transaction must have the can _ append _ role privilege.

### Limitations
<br>

## createAccountForBatch
Issue a batch command to create a new account

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_name | ○ | Account Name | [a-z_0-9{1,32}] |
| domain_id | ○ | Domain ID | RFC1035, RFC1123 |
| public_key | ○ | Public key to add to the account | Ed 25519 public key |

- Domain ID must be created in advance
- Account name must be unique within the domain

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| self | Own object reference holding the batch command | IrohaEE |

### Content
Issue a batch command to create a new account in the specified domain.

### Authority
The issuer of the transaction must have the can _ create _ account privilege.

### Limitations
<br>

## createAssetForBatch
Issue batch commands to issue assets

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| asset_name | ○ | Asset Name | [a-z_0-9{1,32}] |
| domain_id | ○ | Domain ID | RFC1035, RFC1123 |
| precision | ○ | Number of digits after comma / dot | 0<=precision<=255 |

- Domain ID must be created in advance
- Asset names must be unique within the domain

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| self | Own object reference holding the batch command | IrohaEE |

### Content
Issue batch commands to create new assets in the specified domain.

### Authority
The issuer of the transaction must have the can _ create _ asset privilege.

### Limitations
<br>

## createDomainForBatch
Issue a batch command to create a domain

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| domain_id | ○ | Domain ID | RFC1035, RFC1123 |
| default_role | ○ | Role name already defined in the system | [a-z_0-9{1,32}] |

- Roles must be created in advance
- Domain ID must be unique on the system

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| self | Own object reference holding the batch command | IrohaEE |

### Content
Issue a batch command to create a new domain in the Iroha network.

### Authority
The issuer of the transaction must have the can _ create _ domain privilege.

### Limitations
<br>

## createRoleForBatch
Issue a batch command to create a role

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| role_name | ○ | Role Name | [a-z_0-9{1,32}] |
| permissions | ○ | Array of authority | ex: can_receive, can_transfer[] |

- Permissions must have one or more permissions
- See here for configurable permissions[](https://iroha.readthedocs.io/en/latest/develop/api/permissions.html#list-of-permissions)

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| self | Own object reference holding the batch command | IrohaEE |

### Content
Issue a batch command to create a new role on the system.

### Authority
The issuer of the transaction must have the can _ create _ role privilege.

### Limitations
<br>

## detachRoleForBatch
Issue a batch command to detach roles

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | The account ID to which the role is detached | <account_name>@<domain_id> |
| role_name | ○ | Role name to detach | [a-z_0-9{1,32}] |

- Account ID must have role to detach

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| self | Own object reference holding the batch command | IrohaEE |

### Content
Issue a batch command to detach the role from the specified account.

### Authority
The issuer of the transaction must have the can _ detach _ role privilege.

### Limitations
<br>

## grantPermissionForBatch
Issue a batch command to delegate authority

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID to delegate authority to | <account_name>@<domain_id> |
| permission | ○ | Authority to delegate | Permissions that are grantable (see below) |

- Account ID must be created in advance
- The configurable grantable privileges are :[](https://iroha.readthedocs.io/en/latest/develop/api/permissions.html#list-of-permissions)
   - can_add_my_signatory
   - can_remove_my_signatory
   - can_set_my_account_detail
   - can_set_my_quorum
   - can_transfer_my_assets

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| self | Own object reference holding the batch command | IrohaEE |

### Content
The issuer of the transaction issues a batch command to delegate the specified authority to the specified account.

### Authority
The issuer of the transaction must have the authority to delegate.

| Privileges required by the transaction issuer | Authority to delegate |
|:----|:----|
| can_grant_can_add_my_signatory | can_add_my_signatory |
| can_grant_can_remove_my_signatory | can_remove_my_signatory |
| can_grant_can_set_my_account_detail | can_set_my_account_detail |
| can_grant_can_set_my_quorum | can_set_my_quorum |
| can_grant_can_transfer_my_assets | can_transfer_my_assets |

### Limitations
<br>

## removePeerForBatch
Issue a batch command to remove a peer from the Iroha network

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| public_key | 0 | Public key of the peer to remove | Ed 25519 public key |

- A peer with the specified public key must exist on the Iroha network
- A peer other than the one with the specified public key must exist on the Iroha network

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| self | Own object reference holding the batch command | IrohaEE |

### Content
Issue a batch command to write the fact that the peer has been removed to the peer network.

### Authority
The issuer of the transaction must have the can _ remove _ peer privilege.

### Limitations
<br>

## removeSignatoryForBatch
Issue a batch command to remove signatures

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID | <account_name>@<domain_id> |
| public_key | ○ | Public key to delete from the account | Ed 25519 public key |

- Account ID must be created in advance
- The number of public keys associated with the account, excluding the public key to be deleted, must be greater than or equal to quorum

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| self | Own object reference holding the batch command | IrohaEE |

### Content
Issue a batch command to remove signatures from the specified account.

### Authority
The can _ remove _ signatory privilege is required if the issuer of the transaction wants to remove its own signature. If a transaction issuer removes a signature from another account, the can _ remove _ my _ signatory privilege must be delegated from that account.  

### Limitations
<br>

## revokePermissionForBatch
Issue a batch command to revoke privileges

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID to revoke authority | <account_name>@<domain_id> |
| permission | ○ | Power to revoke | Permissions that are grantable (see below) |

- The privileges you want to revoke must be granted in advance to the account you specify
- The configurable grantable privileges are :[](https://iroha.readthedocs.io/en/latest/develop/api/permissions.html#list-of-permissions)
   - can_add_my_signatory
   - can_remove_my_signatory
   - can_set_my_account_detail
   - can_set_my_quorum
   - can_transfer_my_assets

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| self | Own object reference holding the batch command | IrohaEE |

### Content
Issue a batch command that revokes the authority delegated by the transaction issuer to the specified account.

### Authority
The issuer of the transaction must have the authority to revoke.

| Privileges required by the transaction issuer | Power to revoke |
|:----|:----|
| can_grant_can_add_my_signatory | can_add_my_signatory |
| can_grant_can_remove_my_signatory | can_remove_my_signatory |
| can_grant_can_set_my_account_detail | can_set_my_account_detail |
| can_grant_can_set_my_quorum | can_set_my_quorum |
| can_grant_can_transfer_my_assets | can_transfer_my_assets |

### Limitations
<br>

## setAccountDetailForBatch
Issue batch commands to set account details

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID to set details | <account_name>@<domain_id> |
| key | ○ | Keys to be set | [A-Za-z0-9_{1,64}] |
| value | ○ | Value corresponding to the key | Character string of 4096 bytes or less |

- Account ID must be created in advance

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| self | Own object reference holding the batch command | IrohaEE |

### Content
Issue a batch command to set key value information associated with the specified account. If the account already has a key, overwrite the value.  

### Authority
If the issuer of the transaction wants to set details for another account, it must either have the can _ set _ detail privilege or have delegated the can _ set _ my _ account _ detail privilege from that account. (No permissions are required to set details for the transaction issuer's own account)  

### Limitations
<br>

## setAccountQuorumForBatch
Issue a batch command to set the quorum for an account

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID to set the quorum | <account_name>@<domain_id> |
| quorum | ○ | Quorum | Integer 0 <quorum <= number of public keys associated with the account <= 128<br> |

- The account ID must be created in advance.

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| self | Own object reference holding the batch command | IrohaEE |


### Content
Issue a batch command to set the quorum count for the account for the specified account.

### Authority
The can _ set _ quorum privilege is required if the transaction issuer wants to set its own quorum count. If the transaction issuer sets the quorum count for another account, the can _ set _ my _ quorum privilege must be delegated from that account.  

### Limitations
<br>

## subtractAssetQuantityForBatch
Issue batch commands to reduce the quantity of assets

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| asset_id | ○ | Asset ID | <asset_name>#<domain_id> |
| amount | ○ | The quantity to subtract | Positive number |

- Asset ID must be created in advance
- Asmount allows decimal notation according to precision when created

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| self | Own object reference holding the batch command | IrohaEE |

### Content
Issue a batch command that decrements the amount of assets owned by the account that issued the transaction.

### Authority
The transaction issuer must have the can _ subtract _ asset _ qty or can _ subtract _ domain _ asset _ qty privilege. However, the can _ subtract _ domain _ asset _ qty privilege can only be executed on assets in the domain to which the transaction issuer belongs.  

### Limitations
<br>

## transferAssetForBatch
Issue a batch command to transfer assets

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| src_account_id | ○ | Source Account ID | <account_name>@<domain_id> |
| dest_account_id | ○ | Transferee Account ID | <account_name>@<domain_id> |
| asset_id | ○ | Asset ID | <asset_name>#<domain_id> |
| description | ○ | Message attached to the transfer operation | Character string of 64 bytes or less |
| amount | ○ | Quantity to be transferred | Positive number |

- Source and destination accounts must exist
- The asset must exist in the account from which it was transferred
- Sufficient assets to transfer to the source account, not 0
- Quantities can be expressed as decimal points according to precision at creation

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| self | Own object reference holding the batch command | IrohaEE |

### Content
Issue batch commands to transfer assets from one account to another.

### Authority
The issuer of the transaction must have the can _ transfer privilege. The relocation account must have the can _ receive privilege. If you want the source account to have an account other than the issuer of the transaction, the can _ transfer _ my _ assets privilege must be delegated to it.    

### Limitations
<br>

## compareAndSetAccountDetailForBatch
Issue a batch command to replace the contents of the account details

### Argument
| Argument name | Required | Content | Format |
|:----|:----:|:----|:----|
| account_id | ○ | Account ID to set details | <account_name>@<domain_id> |
| key | ○ | Keys to be set | [A-Za-z0-9_{1,64}] |
| value | ○ | New value corresponding to the key | Character string of 4096 bytes or less |
| old_value | | Current value corresponding to the key | Character string of 4096 bytes or less |

- Account ID must be created in advance

### Return value
| Return Value Name | Content | Format |
|:----|:----|:----|
| self | Own object reference holding the batch command | IrohaEE |

### Content
Issue a batch command to update the key value information with the new value only if the current value corresponding to the key is the specified value. If the specified key does not exist in the account, the new value is set to the key value information.  

### Authority
The issuer of the transaction must have the can _ get _ my _ acc _ detail, can _ get _ all _ acc _ detail, or can _ get _ domain _ acc _ detail permissions to set details for his account.

If the issuer of the transaction wants to set details for another account, it must either have the can _ set _ detail privilege or have delegated the can _ set _ my _ account _ detail privilege from that account. Can _ get _ all _ acc _ detail or can _ get _ domain _ acc _ detail. However, the can _ get _ domain _ acc _ detail privilege can only be run against accounts in the domain to which the transaction issuer belongs.

| Target Account | Necessary authority |
|:----|:----|
| Transaction issuer itself | 1. can_get_my_acc_detail / can_get_all_acc_detail / can_get_domain_acc_detail |
| Accounts in the same domain | 1. can_set_detail / (granted) can_set_my_account_detail 2. can_get_all_acc_detail / can_get_domain_acc_detail<br> |
| Accounts in another domain | 1. can_set_detail / (granted) can_set_my_account_detail 2. can_get_all_acc_detail<br> |

### Limitations
<br>

# Appendix

## Error code

See Possible Stateful Validation Errors for each API.

[Iroha API reference](https://iroha.readthedocs.io/en/latest/develop/api.html)

## Cause code

When an error occurs during query execution, the cause code is as follows.

| Cause code | Cause | Description |
|:----|:----|:----|
| 0 | STATELESS_INVALID | When STATELESS _ INVALID Occurs |
| 1 | STATEFUL_INVALID | When STATEFUL _ INVALID Occurs |
| 2 | NO_ACCOUNT | A nonexistent account is specified |
| 3 | NO_ACCOUNT_ASSETS | A nonexistent account asset was specified. |
| 4 | NO_ACCOUNT_DETAIL | A missing account detail is specified |
| 5 | NO_SIGNATORIES | If a nonexistent signature is specified |
| 6 | NOT_SUPPORTED | Unknown request sent |
| 7 | NO_ASSET | A nonexistent asset is specified. |
| 8 | NO_ROLES | A role that does not exist is specified. |
