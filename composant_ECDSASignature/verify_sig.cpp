#include <openssl/ec.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/sha.h>
#include <openssl/err.h>
#include <string>
#include <iostream>
#include <vector>

std::vector<unsigned char> HexToBytes(const std::string& hex) {
    std::vector<unsigned char> bytes;
    for (unsigned int i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        unsigned char byte = (unsigned char) strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(byte);
    }
    return bytes;
}

class ECDSAVerify
{
private:
    EC_KEY *key;

public:
    ECDSAVerify()
    {
        key = EC_KEY_new_by_curve_name(NID_secp256k1);
    }

    ~ECDSAVerify()
    {
        EC_KEY_free(key);
    }

    void Initialize(const std::string &publicKeyHex)
    {
        std::vector<unsigned char> publicKeyBytes = HexToBytes(publicKeyHex);
        EC_POINT *pub_key = EC_POINT_new(EC_KEY_get0_group(key));
        if (EC_POINT_oct2point(EC_KEY_get0_group(key), pub_key, &publicKeyBytes[0], publicKeyBytes.size(), NULL) != 1)
        {
            throw std::runtime_error("Failed to parse public key.");
        }

        if (EC_KEY_set_public_key(key, pub_key) != 1)
        {
            throw std::runtime_error("Failed to set public key.");
        }

        EC_POINT_free(pub_key);
    }

    bool Verify(const std::string &message, const std::string &signatureHex)
    {
        size_t r_len = 64;
        size_t s_len = 64;
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, message.c_str(), message.size());
        SHA256_Final(hash, &sha256);

        BIGNUM *r = BN_new();
        BIGNUM *s = BN_new();
        BN_hex2bn(&r, signatureHex.substr(0, r_len).c_str());
        BN_hex2bn(&s, signatureHex.substr(r_len, s_len).c_str());

        ECDSA_SIG *signature = ECDSA_SIG_new();
        ECDSA_SIG_set0(signature, r, s);

        int verifyStatus = ECDSA_do_verify(hash, sizeof(hash), signature, key);

        ECDSA_SIG_free(signature);

        return verifyStatus == 1;
    }
};

int main()
{
    ECDSAVerify ecdsaVerify;
    std::string publicKeyHex = "04F2CE1E40BEFBEBAF4045F1A6D126B7B949E7D5ADEA33F84A09A904093456F4FD504B1F70755BE4CEF27625B1E6B893E05FFEB361F2971FDA1D6BE5E730A74303";
    std::string message = "Hello, World!";
    std::string signature    = "371ADD1C2C324A1278F2412D034005A146D2FA370C6B3C985B133D5C4D97A062EA7FDB202C01DAF04043099544354763290572416B8E22B6B8FF7ED101F6A3C7";

    ecdsaVerify.Initialize(publicKeyHex);

    if (ecdsaVerify.Verify(message, signature)) 
    {
        std::cout << "Signature is valid." << std::endl;
    } 
    else 
    {
        std::cout << "Signature is invalid." << std::endl;
    }

    return 0;
}
