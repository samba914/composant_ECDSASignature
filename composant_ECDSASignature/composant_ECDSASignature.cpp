#include <openssl/ec.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/sha.h>
#include <openssl/err.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <pybind11/pybind11.h>

char version[] = "1.0";

const char *getVersion()
{
    return version;
}

class ECDSASignature
{
private:
    EC_KEY *key;

public:
    ECDSASignature()
    {
        // Create a new EC key
        key = EC_KEY_new_by_curve_name(NID_secp256k1);
    }

    ~ECDSASignature()
    {
        // Clean up
        EC_KEY_free(key);
    }

    void Initialize(const std::string &privateKeyHex)
    {
        BIGNUM *prv = BN_new();
        if (!BN_hex2bn(&prv, privateKeyHex.c_str()))
        {
            throw std::runtime_error("Failed to parse private key.");
        }

        if (!EC_KEY_set_private_key(key, prv))
        {
            throw std::runtime_error("Failed to set private key.");
        }

       
        BN_free(prv);
    }

    std::string Sign(const std::string &message)
    {
        if (message.empty())
        {
            throw std::runtime_error("Message cannot be empty.");
        }

        // Hash the message (SHA256)
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, message.c_str(), message.size());
        SHA256_Final(hash, &sha256);

        // Sign the hash
        ECDSA_SIG *signature = ECDSA_do_sign(hash, sizeof(hash), key);
        if (signature == nullptr)
        {
            // Handle error
            ERR_print_errors_fp(stderr);
            exit(-1);
        }

        // Get the signature in hexadecimal
        const BIGNUM *r, *s;
        ECDSA_SIG_get0(signature, &r, &s);
        char *r_hex = BN_bn2hex(r);
        char *s_hex = BN_bn2hex(s);

        std::string signatureHex = std::string(r_hex) + std::string(s_hex);

        // Clean up
        ECDSA_SIG_free(signature);
        OPENSSL_free(r_hex);
        OPENSSL_free(s_hex);

        return signatureHex;
    }
};

namespace py = pybind11;

PYBIND11_MODULE(composant_ECDSASignature, module)
{
    module.doc() = "composant_ECDSASignature 1.0";
    module.def("getVersion", &getVersion, "a function returning the version");

    py::class_<ECDSASignature>(module, "ECDSASignature", py::dynamic_attr())
        .def(py::init<>())
        .def("Initialize", &ECDSASignature::Initialize)
        .def("Sign", &ECDSASignature::Sign);
}
