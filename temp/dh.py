# Simple Diffie-Hellman Key Exchange example with small values

# Publicly known values
p = 23  # Prime modulus
g = 5   # Generator

# Private keys (chosen randomly by each party)
private_key_alice = 6  # Alice's private key
private_key_bob = 15   # Bob's private key

# Alice computes her public key
public_key_alice = (g ** private_key_alice) % p

# Bob computes his public key
public_key_bob = (g ** private_key_bob) % p

# Alice computes the shared secret using Bob's public key
shared_key_alice = (public_key_bob ** private_key_alice) % p

# Bob computes the shared secret using Alice's public key
shared_key_bob = (public_key_alice ** private_key_bob) % p

# Both shared keys should be the same
print(f"Alice's Public Key: {public_key_alice}")
print(f"Bob's Public Key: {public_key_bob}")
print(f"Shared Key (Alice's computation): {shared_key_alice}")
print(f"Shared Key (Bob's computation): {shared_key_bob}")

# Verifying both shared keys are the same
if shared_key_alice == shared_key_bob:
    print("Both shared keys are equal. Key exchange successful!")
else:
    print("Shared keys are not equal. Key exchange failed.")
