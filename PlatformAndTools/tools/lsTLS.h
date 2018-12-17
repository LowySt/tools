#ifndef LS_TLS_H
#define LS_TLS_H

#include "..\win\win32.h"

#ifndef LS_CRT_H
#include "tools\lsCRT.h"
#endif

#ifndef LS_HTTP_H
#include "tools\lsHTTP.h"
#endif

#include "tools\lsRand.h"

#define TLS_RND_BUFF_SIZE 28

struct TLS_Random
{
    //sec since 00:00 Jan 1, 1970, UTC
    u32 unixTime;
    u8  random_bytes[TLS_RND_BUFF_SIZE];
};

struct TLS_ProtocolVersion
{
    u8 major;
    u8 minor;
};


struct TLS_SessionID
{
    //SessionID sessionID<0..32>
    void *data;
    u8   len;
};

struct TLS_Extensions
{
    u16 extensionType; // values 13 - 65535
    
    void *extensionData;
    u32 sizeOfData;
};

enum TLS_ContentType : u8 
{
    TLS_change_cipher_spec = 20,
    TLS_alert = 21,
    TLS_handshake = 22,
    TLS_application_data = 23,
    
    TLS_maxContentType = 255
};

struct TLS_PlainTextHeader
{
    TLS_ContentType type;
    TLS_ProtocolVersion version;
    u16 length;
};

// The following CipherSuite definitions require that the server 
// provide an RSA certificate that can be used for key exchange
#define TLS_NULL_WITH_NULL_NULL         0x0000
#define TLS_RSA_WITH_NULL_MD5           0x0001
#define TLS_RSA_WITH_NULL_SHA           0x0002
#define TLS_RSA_WITH_NULL_SHA256        0x003B
#define TLS_RSA_WITH_RC4_128_MD5        0x0004
#define TLS_RSA_WITH_RC4_128_SHA        0x0005
#define TLS_RSA_WITH_3DES_EDE_CBC_SHA   0x000A
#define TLS_RSA_WITH_AES_128_CBC_SHA    0x002F
#define TLS_RSA_WITH_AES_256_CBC_SHA    0x0035
#define TLS_RSA_WITH_AES_128_CBC_SHA256 0x003C
#define TLS_RSA_WITH_AES_256_CBC_SHA256 0x003D

// The following cipher suite definitions are used for 
// server-authenticated (and optionally client-authenticated) Diffie-Hellman.
#define TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA    0x000D
#define TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA    0x0010
#define TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA   0x0013
#define TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA   0x0016
#define TLS_DH_DSS_WITH_AES_128_CBC_SHA     0x0030
#define TLS_DH_RSA_WITH_AES_128_CBC_SHA     0x0031
#define TLS_DHE_DSS_WITH_AES_128_CBC_SHA    0x0032
#define TLS_DHE_RSA_WITH_AES_128_CBC_SHA    0x0033
#define TLS_DH_DSS_WITH_AES_256_CBC_SHA     0x0036
#define TLS_DH_RSA_WITH_AES_256_CBC_SHA     0x0037
#define TLS_DHE_DSS_WITH_AES_256_CBC_SHA    0x0038
#define TLS_DHE_RSA_WITH_AES_256_CBC_SHA    0x0039
#define TLS_DH_DSS_WITH_AES_128_CBC_SHA256  0x003E
#define TLS_DH_RSA_WITH_AES_128_CBC_SHA256  0x003F
#define TLS_DHE_DSS_WITH_AES_128_CBC_SHA256 0x0040
#define TLS_DHE_RSA_WITH_AES_128_CBC_SHA256 0x0067
#define TLS_DH_DSS_WITH_AES_256_CBC_SHA256  0x0068
#define TLS_DH_RSA_WITH_AES_256_CBC_SHA256  0x0069
#define TLS_DHE_DSS_WITH_AES_256_CBC_SHA256 0x006A
#define TLS_DHE_RSA_WITH_AES_256_CBC_SHA256 0x006B

//The following cipher suites are used for completely anonymous
//Diffie-Hellman communications in which neither party is authenticated
#define TLS_DH_anon_WITH_RC4_128_MD5        0x0018
#define TLS_DH_anon_WITH_3DES_EDE_CBC_SHA   0x001B
#define TLS_DH_anon_WITH_AES_128_CBC_SHA    0x0034
#define TLS_DH_anon_WITH_AES_256_CBC_SHA    0x003A
#define TLS_DH_anon_WITH_AES_128_CBC_SHA256 0x006C
#define TLS_DH_anon_WITH_AES_256_CBC_SHA256 0x006D

struct TLS_ClientHello
{
    TLS_ProtocolVersion clientVersion;
    TLS_Random          random;
    TLS_SessionID       sessionId;
    u16                 *cipherSuites;
    u16                 ciphersLen;
    u8                  *compressionMethods; // values 0 - 255
    u8                  compressionLen;
    
    u16                 extensionLength;
    //Extensions
};

struct TLS_ServerHello
{
    TLS_ProtocolVersion serverVersion;
    TLS_Random          random;
    TLS_SessionID       sessionId;
    u16                 cipherSuite;
    u8                  compressionMethod; // values 0 - 255
    
    u16                 extensionLength;
    //Extensions
};

enum TLS_HandshakeType : u8
{
    TLS_hello_request = 0,
    TLS_client_hello = 1,
    TLS_server_hello = 2,
    TLS_certificate = 11,
    TLS_server_key_exchange = 12,
    TLS_certificate_request = 13,
    TLS_server_hello_done = 14,
    TLS_certificate_verify = 15,
    TLS_client_key_exchange = 16,
    TLS_finished = 20,
    
    TLS_max = 255
};

struct TLS_Handshake
{
    TLS_PlainTextHeader header;
    TLS_HandshakeType msgType;
    u8 length[3];
    
    //The entire message together with the above fields
    u8 *message;
};

extern "C"
{
    void ls_TLSHandshake(connectionInfo *info);
};


#endif

#ifdef LS_TLS_IMPLEMENTATION

TLS_Random TLS_genRandom()
{
    TLS_Random result = {};
    result.unixTime = ls_getUnix32Time();
    ls_fillBufferRand(result.random_bytes, TLS_RND_BUFF_SIZE);
    return result;
}

void ls_TLSmake24BitVal(u8 *buff, u32 val)
{
    u8 *At = (u8 *)&val;
    // @TODO: @INCOMPLETE:
    // What if I'm in an already Big-Endian Platform?
    // Can't call htons on buff, but calling on val always
    // may reproduce incorrect results regardless
    // because I don't know in which endianess I'm performing.
    // Maybe make hanshake.len a u32 val, and htons that,
    // And only send 3 bytes...
    buff[0] = At[2];
    buff[1] = At[1];
    buff[2] = At[0];
}

void ls_TLSmakeClientHelloMessage(TLS_ClientHello *client,
                                  TLS_PlainTextHeader *header, TLS_Handshake *hs)
{
    u32 i = 0;
    
    // Copy PlainTextHeader
    ls_memcpy((void *)&header->type, hs->message + i, sizeof(TLS_ContentType));
    i += sizeof(TLS_ContentType);
    
    ls_memcpy((void *)&header->version, hs->message + i, sizeof(TLS_ProtocolVersion));
    i += sizeof(TLS_ProtocolVersion);
    
    u16 headerLen = htons(header->length);
    
    ls_memcpy((void *)&headerLen, hs->message + i, sizeof(u16));
    i += sizeof(u16);
    
    // Copy Handshake Header
    ls_memcpy((void *)&hs->msgType, hs->message + i, sizeof(TLS_HandshakeType));
    i += sizeof(TLS_HandshakeType);
    
    ls_memcpy((void *)hs->length, hs->message + i, sizeof(hs->length));
    i += sizeof(hs->length);
    
    // Copy protocol version
    ls_memcpy((void *)&client->clientVersion, hs->message + i, sizeof(TLS_ProtocolVersion));
    i += sizeof(TLS_ProtocolVersion);
    
    // Copy random structure
    u32 noUnixTime = htonl(client->random.unixTime);
    ls_memcpy((void *)&noUnixTime, hs->message + i, sizeof(u32)); i += sizeof(u32);
    ls_memcpy((void *)client->random.random_bytes, hs->message + i, TLS_RND_BUFF_SIZE);
    i += TLS_RND_BUFF_SIZE;
    
    // Copy sessionId
    u8 idLen = client->sessionId.len;
    ls_memcpy((void *)&idLen, hs->message + i, sizeof(u8));
    i += sizeof(u8);
    
    if(idLen != 0)
    {
        ls_memcpy((void *)client->sessionId.data, hs->message + i, idLen);
        i += idLen;
    }
    
    // Copy cipherSuites
    u16 noCipherLen = htons(client->ciphersLen);
    ls_memcpy((void *)&noCipherLen, hs->message + i, sizeof(u16));
    i += sizeof(u16);
    
    if(noCipherLen != 0)
    {
        u32 numOfCiphers = client->ciphersLen / sizeof(u16);
        for(u32 idx = 0; idx < numOfCiphers; idx++)
        {
            u16 val = htons(client->cipherSuites[idx]);
            ls_memcpy((void *)&val, hs->message + i, sizeof(u16)); i += sizeof(u16);
        }
    }
    
    // Copy compressionMethods
    
    u8 comprLen = client->compressionLen;
    ls_memcpy((void *)&comprLen, hs->message + i, sizeof(u8));
    i += sizeof(u8);
    
    if(comprLen != 0)
    {
        for(u32 idx = 0; idx < comprLen; idx++)
        {
            ls_memcpy((void *)&client->compressionMethods[idx], hs->message + i, sizeof(u8));
            i += comprLen;
        }
    }
    
    // Copy Extensions
    
    u16 noExtLen = htons(client->extensionLength);
    ls_memcpy((void *)&noExtLen, hs->message + i, sizeof(u16));
    
    if(noExtLen != 0)
    { 
        // Implement Extensions 
    }
}

void ls_TLSHandshake(connectionInfo *info)
{
    const u32 buffSize = 512;
    s32 thisReadSize = 0, totalBytesRead;
    u8 readBuffer[buffSize];
    u8 *tmpResult = 0;
    
    TLS_ClientHello *client = (TLS_ClientHello *)ls_alloc(sizeof(TLS_ClientHello));
    client->clientVersion = {3, 3};
    client->random = TLS_genRandom();
    client->sessionId.len = 0;
    
    client->cipherSuites = (u16 *)ls_alloc(sizeof(u16) * 1);
    client->cipherSuites[0] = TLS_RSA_WITH_NULL_MD5;
    client->ciphersLen = sizeof(u16);
    
    client->compressionMethods = (u8 *)ls_alloc(sizeof(u8) * 1);
    client->compressionMethods[0] = 0;
    client->compressionLen = sizeof(u8);
    
    client->extensionLength = 0;
    
    TLS_Handshake handshake = {};
    handshake.msgType = TLS_client_hello;
    
    u32 s1 = sizeof(TLS_ProtocolVersion);
    u32 s2 = sizeof(TLS_Random);
    u32 s3 = sizeof(client->sessionId.len);
    u32 s4 = client->sessionId.len;
    u32 s5 = sizeof(client->ciphersLen);
    u32 s6 = client->ciphersLen;
    u32 s7 = sizeof(client->compressionLen);
    u32 s8 = client->compressionLen;
    u32 s9 = client->extensionLength;
    
    u32 msgBodyLen = sizeof(TLS_ProtocolVersion) +
        sizeof(TLS_Random) + sizeof(client->sessionId.len) + 
        client->sessionId.len + sizeof(client->ciphersLen) + 
        client->ciphersLen + sizeof(client->compressionLen) +
        client->compressionLen + client->extensionLength;
    
    u32 s10 = msgBodyLen;
    u32 s11 = sizeof(TLS_HandshakeType);
    u32 s12 = sizeof(handshake.length);
    
    u32 msgLenNoHeader = msgBodyLen + sizeof(TLS_HandshakeType) +
        sizeof(handshake.length);
    
    TLS_PlainTextHeader header = {};
    header.type = TLS_handshake;
    header.version = {3, 3};
    header.length = msgLenNoHeader;
    
    u32 msgLen = msgLenNoHeader + sizeof(TLS_PlainTextHeader);
    
    handshake.message = (u8 *)ls_alloc(sizeof(u8) * msgLen);
    ls_TLSmake24BitVal(handshake.length, msgBodyLen);
    
    ls_TLSmakeClientHelloMessage(client, &header, &handshake);
#if 0
    u32 idx = msgLen;
    u32 i = 0;
    u32 difference;
    string buffer = 256;
    string *t = 0;
    while(true)
    {
        u64 v = ((u64 *)handshake.message)[i++];
        t = ls_itohs(v);
        buffer += *t;
        t->free();
        
        idx -= 8;
        buffer += '\n';
        if(idx < 8) { difference = 8 - idx; break; }
    }
    
    i *= 8;
    while(difference--)
    {
        u8 v = ((u8 *)handshake.message)[i++];
        t = ls_itohs(v);
        buffer += *t;
        t->free();
        buffer += '\n';
    }
#endif
    ls_writeFile("C:\\Users\\loren\\Desktop\\test.bin", handshake.message, msgLen, 0);
    
    // Send Client Hello //
    s32 bytesSent = send(info->conn, (const char *)handshake.message, msgLen, 0);
    
    if(bytesSent < msgLen)
    {
        ls_printf("Not sent Enough!\n\n");
        int breakHere = 0;
    }
    if(bytesSent == SOCKET_ERROR)
    {
        s32 errorCode = WSAGetLastError();
        ls_printf("recv returned error code: %d", errorCode);
    }
    
    // Recieve Server Hello
    
    totalBytesRead = 0;
    while(1)
    {
        ls_zeroMem(readBuffer, buffSize);
        thisReadSize = recv(info->conn, (char *)readBuffer, buffSize, 0);
        
        if(thisReadSize == SOCKET_ERROR)
        {
            s32 errorCode = WSAGetLastError();
            ls_printf("recv returned error code: %d", errorCode);
            if(tmpResult) { ls_free(tmpResult); }
        }
        
        if(thisReadSize <= 0) { break; }
        
        tmpResult = (u8 *)ls_realloc(tmpResult, 
                                     totalBytesRead, thisReadSize+totalBytesRead);
        
        ls_memcpy(readBuffer, tmpResult+totalBytesRead, thisReadSize);
        totalBytesRead += thisReadSize;
    }
}

#endif