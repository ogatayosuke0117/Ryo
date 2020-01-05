import hashlib 
import datetime 
import time 
import json 

INITIAL_BITS=0x1e777777
MAX_32BIT=0xffffffff
#expected_time=140*5

class Block(): #データをインプット
	def __init__(self,index,prev_hash,data,timestamp,bits):
		self.index = index
		self.prev_hash = prev_hash
		self.data = data
		self.timestamp = timestamp
		self.bits = bits
		self.nonce = 0
		self.elapsed_time = ""
		self.block_hush = ""

	def __setitem__(self,key,value): #key と　value を設定可能に
		setattr(self,key,value) 

	def to_json(self): #jsonファイルに変更
		return {
		"index" : self.index,
		"prev_hash": self.prev_hash,
		"stored_data": self.data,
		"timestanp" : self.timestamp.strftime("%Y/%m/%d %H:%M:%S"),
		"bits" : hex(self.bits)[2:].rjust(8,"0"),
		"nonce" : hex(self.nonce)[2:].rjust(8,"0"),
		"elapsed_time" : self.elapsed_time,
		"block_hush" : self.block_hush
		}

	def calc_blockhush(self): #hashheaderを作成する
		blockheader = str(self.index) + str(self.prev_hash) + str(self.data) + str(self.timestamp) + str(hex(self.bits)[2:]) + str(self.nonce)
		h = hashlib.sha256(blockheader.encode()).hexdigest()
		self.block_hush = h
		return h 

	def calc_target(self): #ターゲットを作成
		exponent_bytes = (self.bits >> 24) -3 #>>24は0x1eのみにするため #3bit分は、coefficientの分　#>>は、ビット分ずらす
		exponent_bits = exponent_bytes * 8 #バイト→ビット
		coefficient = self.bits & 0xffffff #0xをなくすため
		return coefficient << exponent_bits 

	def chenk_vaild_hash(self):
		return int(self.calc_blockhush(),16) <= self.calc_target()

class Blockchain():
	def __init__(self, initial_bits): #データ容量の確保
		self.chain = []
		self.initial_bits=initial_bits

	def add_block(self,block):
		self.chain.append(block)#新規のブロックを追加する

	def getblockinfo(self,index=-1):
		return print(json.dumps(self.chain[index].to_json(),indent = 2, ensure_ascii = False))#,indent = 2, sort_keys=True,ensure_arcii=False)

	def mining(self,block): #かかった時間を計測 #マイニング #終わったら、ブロックを追加　#情報を出力
		start_time = int(time.time()*1000)
		while True:
			for n in range(MAX_32BIT + 1):
				block.nonce=n
				if block.chenk_vaild_hash():
					end_time = int(time.time() * 1000)
					block.elapsed_time = str((end_time - start_time) / 1000.0) + "秒"
					self.add_block(block)
					self.getblockinfo()
					return
				new_time = datetime.datetime.now()
				if new_time == block.timestamp:
					block.timestamp += datetime.timedelta(seconds=1)
				else:
					block.timestamp=new_time
	def  create_genesis(self):
		 genesis_block = Block(0,"0000000000000000000000000000000000000000000000000000000000000000","ジェネシスブロック",datetime.datetime.now(),self.initial_bits)
		 self.mining(genesis_block)

	def add_newblock(self,i):
		last_block = self.chain[-1]
		new_bits = self.get_retarget_bits()

		if new_bits < 0:
			bits = last_block.bits
		else:
			bits = new_bits

		block = Block(i+1,last_block.block_hush,"ブロック" + str(i+1),datetime.datetime.now(),bits)
		self.mining(block)

	def get_retarget_bits(self):
		if len(self.chain) == 0 or len(self.chain)%5 != 0:
			return -1 #新規に難易度を上げる必要なし
		expected_time=140*5

		if len(self.chain) != 5:
			first_block = self.chain[-(1+5)]

		else:
			first_block = self.chain[0]
		last_block = self.chain[-1]#一番新しいブロック

		first_time = first_block.timestamp.timestamp()
		last_time = last_block.timestamp.timestamp()

		total_time = last_time- first_time

		target = last_block.calc_target()
		delta = total_time / expected_time
		if delta < 0.25: 
			delta = 0.25
		if delta > 4:
			delta = 4
		new_target = int(target * delta) #newtargetの算定方法

		exponent_bytes = (last_block.bits >> 24) -3
		exponent_bits = exponent_bytes * 8 
		temp_bits = new_target >> exponent_bits #ターゲット→ビッツ化（逆さん）
		if temp_bits != temp_bits & 0xffffff: #大きすぎ
			exponent_bytes += 1
			exponent_bits +=8
		elif temp_bits == temp_bits & 0xffff:
			exponent_bytes -= 1
			exponent_bits -=8
		return ((exponent_bytes + 3)<<24)|(new_target >> exponent_bits) #新たなbitsで返す 


if __name__== "__main__":
		bc=Blockchain(INITIAL_BITS)
		print("ジェネシスブロック作成中...")
		bc.create_genesis()
		for i in range(10):
			print(str(i+2) + "番目のブロックを作成中...")
			bc.add_newblock(i)

		
