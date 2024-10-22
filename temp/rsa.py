from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP
from Crypto.Signature import pkcs1_15
from Crypto.Hash import SHA256
from Crypto import Random

# RSA key generation
key = RSA.generate(2048)
private_key = key
public_key = key.publickey()

# Message to encrypt
message = b'This is a secret message.'

# Encrypt the message using RSA public key
cipher = PKCS1_OAEP.new(public_key)
ciphertext = cipher.encrypt(message)

# Decrypt the message using RSA private key
cipher = PKCS1_OAEP.new(private_key)
decrypted_message = cipher.decrypt(ciphertext)

# RSA signature
h = SHA256.new(message)
signature = pkcs1_15.new(private_key).sign(h)

# RSA signature verification
try:
    pkcs1_15.new(public_key).verify(h, signature)
    print("Signature is valid.")
except (ValueError, TypeError):
    print("Signature is invalid.")

print(f"Encrypted: {ciphertext}")
print(f"Decrypted: {decrypted_message}")
