# irohaee-java

## Table of contents
1. [Irohaee - What is java?](#1-irohaee-java-%E3%81%A8%E3%81%AF)
2. Irohaee - java Operating Environment 2.1. java Version 2.2. Availability[](#2-irohaee-java-%E3%81%AE%E5%8B%95%E4%BD%9C%E7%92%B0%E5%A2%83)  [](#21-java%E3%83%90%E3%83%BC%E3%82%B8%E3%83%A7%E3%83%B3)  [](#22-%E6%8F%90%E4%BE%9B%E5%BD%A2%E6%85%8B)
3. Irohaee - java usage overview 3.1. Initialization[](#3-irohaee-java-%E5%88%A9%E7%94%A8%E6%96%B9%E6%B3%95%E3%81%AE%E6%A6%82%E8%A6%81)  [](#33-%E5%88%9D%E6%9C%9F%E5%8C%96)
4. Irohaee - java usage details 4.1. Command 4.2. Query 4.3. Batch 4.4. Exception[](#4-irohaee-java-%E5%88%A9%E7%94%A8%E6%96%B9%E6%B3%95%E3%81%AE%E8%A9%B3%E7%B4%B0)  [](#41-%E3%82%B3%E3%83%9E%E3%83%B3%E3%83%89)  [](#42-%E3%82%AF%E3%82%A8%E3%83%AA)  [](#43-%E3%83%90%E3%83%83%E3%83%81)  [](#44-%E4%BE%8B%E5%A4%96)
5. Appendix 5.1. Transactions[](#5-%E4%BB%98%E9%8C%B2)  [](#51-%E3%83%88%E3%83%A9%E3%83%B3%E3%82%B6%E3%82%AF%E3%82%B7%E3%83%A7%E3%83%B3)

## 1. irohaee - What is java?
Irohaee - java is a high-level wrapper around the open source Iroha - java in a more usable form as Iroha Enterprise Edition, with additional documentation such as function definitions and usage guides.[](https://github.com/hyperledger/iroha-java)****

Irohaee - With java, you can develop without worrying about complex class structures or how to call methods.

## 2. irohaee - java System Requirements
### 2.1. java Version

Java 8 is assumed.

### 2.2 Form of Delivery
Irohaee - java is provided in the form of a JAR file. It is available by taking the irohaee - java JAR file provided in the Git repository and passing it through the Java project classpath.

#### 2.2.1. Git Repositories
Retrieve the JAR file from the following repository :.

```
T.B.D```


## 3. irohaee - Overview of java usage
### 3.1. Initialization
The API calls make use of the jp. co. soramitsu. irohaee. java. IrohaEE class. In the constructor, specify the transaction creator account ID, key pair, Iroha server host, and Iroha server port.[][][][]

* If host and port are not set, host "127.0.0.1" and port 50051 are used as default values.

```java
/ / IrohaEE Instantiation Example 1 IrohaEE irohaee = new IrohaEE (creator _ account, key _ pair, host, port) ; / / IrohaEE Instantiation Example 2 (* host, port not specified) IrohaEE irohaee = new IrohaEE(account_id, private_key)```

If you want to change the setting, call the following methods to override the setting :.

```java
/ / Iroha host, configuring port irohaee. setIroha (host, port) ; / / transaction creator ID, configuring key pair irohaee. setAccount (creator _ account, key _ pair) ;```

## 4. irohaee - java usage details
Irohaee - The API provided by java includes commands for update processing and queries for reference processing.


### 4.1. Commands
Examples of command API calls are :.

> For the API reference for the command (arguments, return values, and exceptions), see the "Command" chapter in the attached "Function Definition Document". The createDomain functions in this chapter correspond to the irohaee. createDomain () calls in the code below.

```java
Try {/ / createDomain (domain generation) API call ToriiResponse res = irohaee. createDomain (.) ;} catch (IrohaEETransactionException e) {/ / exception handling}```

### 4.2. Queries
An example of a query API call is :.

> For the query API reference (arguments, return values, and exceptions), see the "Query" chapter in the attached "Function Definition Document". The getAccount function described in that chapter corresponds to irohaee.

```java
Try {/ getAccount (get account) API call AccountResponse res = irohaee. getAccount (.) ; / / get account id from processing result String accountId = res. getAccount (). getAccountId () ;} catch (IrohaEEQueryException e) {/ / exception handling}```

### 4.3. Batches
Iroha allows you to run multiple transactions as a batch. There are Atomic and Ordered batches in the batch.

> For the batch API reference (arguments, return values, exceptions), see the "Batch" chapter in the attached "Function Definition Document". The createAssetForBatch functions in this chapter correspond to the irohaee. createAssetForBatch () calls in the code below.

#### 4.3.1. Atomic Batch
Atomic batches are recorded in a distributed ledger only if all transactions in the batch have successfully completed the Stateful Validation.

An example of an atomic batch API call is :.

```java
ToriiResponse [] reslist = irohaee. createDomainForBatch (.). createAssetForBatch (.). addAssetQuantityForBatch (.). transferAssetForBatch (.) / / Atomic batch execution. sendAtomic () ;} catch (IrohaEEBatchTransactionException e) {/ / exception handling}```

In the example, createDomain, createAsset, addAssetQuantity, and transferAsset are executed in an atomic batch. If createAsset fails as shown below, all transactions will fail.

![No Atomic batch errors](./images/atomic_batch_success.png "")

![Atomic batch error](./images/atomic_batch_fail.png "")

#### 4.3.2. Ordered Batch
Ordered batches are recorded in a distributed ledger only if the Stateful Validation succeeds. (Even if some transactions fail, the entire batch does not fail.)

An example of an Ordered batch API call is :.

```java
Try {/ / ToriiResponse using the form of a method chain [] reslist = irohaee. createDomainForBatch (.). createAssetForBatch (.). addAssetQuantityForBatch (.). transferAssetForBatch (.) / / Ordered batch execution. sendBatch () ;} catch (IrohaEEBatchTransactionException e) {/ / exception handling}```

The example runs createDomain, createAsset, addAssetQuantity, and transferAsset in an Ordered batch. Even if createAsset fails as shown below, other transactions with no problems will succeed.

![No Ordered Batch Errors No Ordered Batch Errors](./images/ordered_batch_success.png "")

![Ordered Batch Errors Ordered Batch Errors](./images/ordered_batch_fail.png "")

### 4.4. Exceptions
Irohaee - java throws an exception if the transaction fails when calling the API.

The following exceptions correspond to API types :.

| Type | Occurrence exception |
| :------------- | :------------------------------- |
| On command failure | IrohaEETransactionException |
| On query failure | IrohaEEQueryException |
| On batch failure | IrohaEEBatchTransactionException |

#### 4.4.1 Command Failure
IrohaEETransactionException is thrown if the command API fails, and ToriiResponse is returned on success. The state of the transaction is mapped to the return value as follows :.

> See Section 5.1 Transactions for more information about transaction states.[](#5.1-トランザクション)

| Transaction state | Status | Return value |
| :-------------------------- | :--- | :-------------------------------- |
| COMMITTED | Success | ToriiResponse |
| MST_PENDING | Hold | ToriiResponse |
| STATELESS_VALIDATION_FAILED | Failure | IrohaEETransactionException occurs |
| REJECTED | Failure | IrohaEETransactionException occurs |

- The IrohaEETransactionException thrown on failure contains the STATEFUL error code and ToriiResponse object.

- The STATEFUL error code is set when the transaction state is REJECTED and the cause is STATEFUL _ VALIDATION _ FAILED.

- MST _ PENDING is set when the number of signed transactions has not reached the requested number (= the number set by Quorum) in a multisignature transaction

> For the values that can be retrieved from the thrown IrohaEETransactionException, see the exceptions listed in the Command chapter of the Function Definition Document.


#### 4.4.2 Query Failure
IrohaEEQueryException is thrown if the query API fails, and a response object based on the API definition is returned on success.

| Status | Return value |
| :--- | :---------------------------------------- |
| Success | Instances of structure classes based on API definitions |
| Failure | IrohaEEQueryException occurs |

The IrohaEEQueryException thrown on failure includes the STATEFUL error code and the ErrorResponse object.

> See the exceptions listed in the Query chapter of the Function Definition Book for possible values from the thrown IrohaEEQueryException.

#### 4.4.3 Batch Failure
IrohaEEBatchTransactionException is thrown if the batch API fails, and an array of ToriiResponse objects is returned on success.

| Status | Return value |
| :--- | :---------------------------------------- |
| Success | Instances of structure classes based on API definitions |
| Failure | IrohaEEBatchTransactionException occurs |

The IrohaEEBatchTransactionException thrown on failure contains an array of STATEFUL error codes and an array of ToriiResponse objects.

> For the values that can be retrieved from a thrown IrohaEEBatchTransactionException, see the exceptions listed in the Batch chapter of the Function Definition Book.


## 5. Appendix
### 5.1. Transactions
A transaction sent from a client changes state depending on the validation results and signature state.

![Transaction StatusesTransaction Statuses](https://iroha.readthedocs.io/en/latest/_images/tx_status.png "")

#### 5.1.1. Process Overview
1. Client requests are received by Torii.
2. Stateless Validation is performed first, followed by signing and formal validation.
3. A Stateful Validation is performed to verify the execution authority, balance, and so on.
4. Committed blocks are recorded as a block chain.

#### 5.1.2 Transaction State

| Transaction state | Description |
| :--------------------------- | :--------------------------------------------------------- |
| NOT_RECEIVED | The requested peer does not have information about this transaction |
| ENOUGH_SIGNATURES_COLLECTED | Multisignature transactions get enough signatures |
| MST_PENDING | Multisignature transactions require additional signatures |
| MST_EXPIRED | Multisignature transactions disabled and removed |
| STATELESS_VALIDATION_FAILED | Stateless Validation Failed |
| STATELESS_VALIDATION_SUCCESS | Stateless Validation Successful |
| STATEFUL_VALIDATION_FAILED | Stateful validation failed |
| STATEFUL_VALIDATION_SUCCESS | Stateful Validation Successful |
| COMMITTED | Win enough votes and store in block store |
| REJECTED | Transaction denied during stateful validation |


Of these states, the final status of a transaction (sent from a non-malicious node) is either STATELESS _ VALIDATION _ FAILED, COMMITTED, or REJECTED.

Irohaee - java returns either "COMMITTED" or "MST _ PENDING" as the state of the transaction upon successful completion.

If the state of the transaction at the time of the abnormal termination is "STATELESS _ VARIDATION _ FAILED" or "REJECTED", it is considered a transaction failure and throws an exception.

See 4.4 Exceptions for exceptions.[](#4.4-例外)

For more information about transaction state transitions, see the following URL :.
> #### Transaction Statuses
> https://iroha.readthedocs.io/en/latest/before_start/glossary.html#transaction-statuses
> #### Status Streaming In Hyperledger Iroha
> https://medium.com/iroha-contributors/status-streaming-in-hl-iroha-5503487ffcfds

### 5.1.3 Configuring Transactions

Iroha transactions consist of Payload and Signatures.

#### Payload

| Element | Description |
| :----------------------------------- | :---------------------------------------------------------- |
| Command | Iroha API commands |
| Creation time | Creation time (UNIX time in milliseconds) |
| Account ID of the transaction creator | Account name @ domain format |
| Quorum | Number of signatures required (default : 1) |
| Batch meta information (optional) | Batch information (ATOMIC, ORDERED), transaction reduction hash |

#### Signatures

| Element | Description |
| :--- | :----------------------------------- |
| Signature | Transaction Creator / Approver Signature |

#### Transaction definition
```proto
message Transaction { message Payload { message BatchMeta{ enum BatchType{ ATOMIC = 0; ORDERED = 1; } BatchType type = 1; // array of reduced hashes of all txs from the batch repeated string reduced_hashes = 2; } message ReducedPayload{ repeated Command commands = 1; string creator_account_id = 2; uint64 created_time = 3; uint32 quorum = 4; } // transcation fields ReducedPayload reduced_payload = 1; // batch meta fields if tx belong to any batch oneof optional_batch_meta{ BatchMeta batch = 5; } } Payload payload = 1; repeated Signature signatures = 2; }```

### 5.1.4 Multisignature Transactions
Multisignature transactions are transactions that require multiple signatures, and the number of signatures required is specified in quorum.

The following code example adds a signature to a multi-signature transaction.

```java
Try {/ / get transaction pending signature val pendingResponse = irohaee. getPendingTransactions (1, null) ; val tx = pendingResponse. getTransactions (0) ; / / add signature val signedTx = Transaction. parseFrom (tx). sign (multisigKeypair 2). build () ; / / send transaction val signedRes = irohaee. sendTransation (signedTx) ;} catch (IrohaEETransactionException e) {/ exception handling}```
