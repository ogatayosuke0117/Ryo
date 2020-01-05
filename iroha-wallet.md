# Iroha-wallet の動かし方

## 1. irohwa-wallet.js のクローン

```
$ git clone https://github.com/soramitsu/iroha-wallet.js.git
```

2019/04/15 commit id: e61bfcbff44e6d81278baca5113da1f911604e9c を使用した場合です。

## 2. いろはを起動する

```
$ docker-compose -f docker/docker-compose.yaml up
```

## 3. wallet 用の初期設定

```
$ node scripts/setup.js
```

## 4. npm パッケージのインストール

初回は、以下を実行して npm パッケージをインストールしておく。

```
$ yarn install
```

## 5. iroha-wallet の実行

```
$ yarn serve
```

2回目以降は、上記インストールをしないで iroha-wallet を実行する。

## 6. iroha-wallet へのログイン

以下の項目を入力してログインする。

- Username: admin@test
- Private key: (admin@test.priv を参照する)
- Node IP: http://localhost:8081

本来 IP だが、現在のバージョンでは http:// も入力する。ホスト名（または IP アドレス）はブラウザの実行環境によって変更することも可能。
Iroha-wallet-js では Proxy サーバを利用しているため 8081/tcp を使用する。
