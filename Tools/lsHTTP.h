#ifndef LS_HTTP_H
#define LS_HTTP_H

//#include "..\win\win32.h"

#ifndef LS_CRT_H
#include "tools\lsCRT.h"
#endif

#define LS_HTTP_PORT 80
#define LS_HTTPS_PORT 443

#ifdef LS_PLAT_WINDOWS
typedef SOCKET HTTPSocket;
#elif LS_PLAT_LINUX
typedef int HTTPSocket;
#endif

/* ------------------ */
/* GENERAL CONNECTION */
/* ------------------ */

const char *StatusCode[] = { "100", "101", "200", "201", "202", "203", "204", "205", 
    "206", "300", "301", "302", "303", "304", "305", "307", "400", "401", "402", 
    "403",  "404",  "405",  "406",  "407",  "408",  "409",  "410",  "411",  "412", 
    "413",  "414",  "415",  "416",  "417",  "500",  "501",  "502",  "503",  
    "504", "505"};

enum http_statusCodesEnum
{
    HTTP_SC_CONTINUE = 0,
    HTTP_SC_SWITCHING_PROTO,
    HTTP_SC_OK,
    HTTP_SC_CREATED,
    HTTP_SC_ACCEPTED,
    HTTP_SC_NON_AUTH_INFO,
    HTTP_SC_NO_CONTENT,
    HTTP_SC_RESET_CONTENT,
    HTTP_SC_PARTIAL_CONTENT,
    HTTP_SC_MULTIPLE_CHOICES,
    HTTP_SC_MOVED_PERM,
    HTTP_SC_FOUND,
    HTTP_SC_SEE_OTHER,
    HTTP_SC_NOT_MODIFIED,
    HTTP_SC_USE_PROXY,
    HTTP_SC_TEMP_REDIRECT,
    HTTP_SC_BAD_REQUEST,
    HTTP_SC_UNAUTHORAIZED,
    HTTP_SC_PAYMENT_REQUIRED,
    HTTP_SC_FORBIDDEN,
    HTTP_SC_NOT_FOUND,
    HTTP_SC_METHOD_NOT_ALLOWED,
    HTTP_SC_NOT_ACCEPTABLE,
    HTTP_SC_PROXY_AUTH_REQUIRED,
    HTTP_SC_REQUEST_TIMEOUT,
    HTTP_SC_CONFLICT,
    HTTP_SC_GONE,
    HTTP_SC_LENGTH_REQUIRED,
    HTTP_SC_PRECONDITION_FAILED,
    HTTP_SC_REQ_ENTITY_TOO_LARGE,
    HTTP_SC_REQ_URI_TOO_LARGE,
    HTTP_SC_UNSUPP_MEDIA_TYPE,
    HTTP_SC_REQ_RANGE_NOT_SATISFIABLE,
    HTTP_SC_EXPECTATION_FAILED,
    HTTP_SC_INTERNAL_SERVER_ERROR,
    HTTP_SC_NOT_IMPLEMENTED,
    HTTP_SC_BAD_GATEWAY,
    HTTP_SC_SERVICE_UNAVAILABLE,
    HTTP_SC_GATEWAY_TIMEOUT,
    HTTP_SC_HTTP_VER_NOT_SUPPORTED
};

enum http_socketFlag
{
    HTTP_PASSIVE = 0x1,
    HTTP_CANONNAME = 0x2,
    HTTP_NUMERICHOST = 0x4,
    HTTP_ALL = 0x8,
    HTTP_ADDRCONFIG = 0x10,
    HTTP_V4MAPPED = 0x20,
    HTTP_NON_AUTHORITATIVE = 0x40,
    HTTP_SECURE = 0x80,
    HTTP_RETURN_PREFERRED_NAMES = 0x100,
    HTTP_FQDN = 0x200,
    HTTP_FILESERVER = 0x400,
};

enum http_socketFamily
{
    HTTP_UNSPEC,
    HTTP_UNIX,
    HTTP_INET,
    HTTP_IMPLINK,
    HTTP_PUP,
    HTTP_CHAOS,
    HTTP_NS,
    HTTP_IPX,
    HTTP_ISO,
    HTTP_OSI,
    HTTP_ECMA,
    HTTP_DATAKIT,
    HTTP_CCITT,
    HTTP_SNA,
    HTTP_DECnet,
    HTTP_DLI,
    HTTP_LAT,
    HTTP_HYLINK,
    HTTP_APPLETALK,
    HTTP_NETBIOS,
    HTTP_VOICEVIEW,
    HTTP_FIREFOX,
    HTTP_UNKNOWN1,
    HTTP_BAN,
    HTTP_ATM,
    HTTP_INET6,
    HTTP_CLUSTER,
    HTTP_12844,
    HTTP_IRDA,
    HTTP_NETDES,
    HTTP_TCNPROCESS,
    HTTP_TCNMESSAGE,
    HTTP_ICLFXBM,
    HTTP_BTH,
    HTTP_LINK,
    HTTP_HYPERV,
    HTTP_MAX
};

enum http_socketType
{
    HTTP_STREAM,
    HTTP_DGRAM,
    HTTP_RAW,
    HTTP_RDM,
    HTTP_SEQPACKET
};

enum http_socketOpt
{
    HTTP_DEBUG,
    HTTP_ACCEPTCONN,
    HTTP_REUSEADDR,
    HTTP_KEEPALIVE,
    HTTP_DONTROUTE,
    HTTP_BROADCAST,
    HTTP_USELOOPBACK,
    HTTP_LINGER,
    HTTP_OOBINLINE,
    HTTP_DONTLINGER,
    HTTP_EXCLUSIVEADDRUSE,
    HTTP_SNDBUF,
    HTTP_RCVBUF,
    HTTP_SNDLOWAT,
    HTTP_RCVLOWAT,
    HTTP_SNDTIMEO,
    HTTP_RCVTIMEO,
    HTTP_ERROR,
    HTTP_TYPE,
    HTTP_BSP_STATE,
    HTTP_GROUP_ID,
    HTTP_GROUP_PRIORITY,
    HTTP_MAX_MSG_SIZE,
    HTTP_CONDITIONAL_ACCEPT,
    HTTP_PAUSE_ACCEPT,
    HTTP_COMPARTMENT_ID,
    HTTP_RANDOMIZE_PORT,
    HTTP_PORT_SCALABILITY,
    HTTP_REUSE_UNICASTPORT,
    HTTP_REUSE_MULTICASTPORT,
    
    //SO_UPDATE_ACCEPT_CONTEXT,
    //PVD_CONFIG
};

enum http_socketLevel
{
    HTTP_SOCKET,
    HTTP_IPPROTO_TCP,
    HTTP_NSPROTO_IPX
};

struct http_socketHints
{
    http_socketFlag flags;
    http_socketFamily family;
    http_socketType type;
    
    http_socketLevel level;
    http_socketOpt opt;
    
    b32 areOptsBoolean;
    char *optVal;
    u32  optLen;
};

struct HTTPUri
{
    view scheme;
    view authority;
    view path;
    view filename;
};

struct HTTPConnection
{
    HTTPSocket socket;
    struct sockaddr_storage address;
    
    HTTPUri uri;
};

enum http_MethodType
{
    HTTP_GET,
    HTTP_PUT,
    HTTP_POST,
    HTTP_HEAD,
    HTTP_OPTIONS,
    HTTP_DELETE,
    HTTP_TRACE,
    HTTP_CONNECT,
    
    HTTP_METHOD_NOT_ALLOWED
};

enum http_headerEnum
{
    HTTP_GH_CACHE_CONTROL,
    HTTP_GH_CONNECTION,
    HTTP_GH_DATE,
    HTTP_GH_PRAGMA,
    HTTP_GH_TRAILER,
    HTTP_GH_TRANSFER_ENCODING,
    HTTP_GH_UPGRADE,
    HTTP_GH_VIA,
    HTTP_GH_WARNING,
    HTTP_RH_ACCEPT,
    HTTP_RH_ACCEPT_CHARSET,
    HTTP_RH_ACCEPT_ENCODING,
    HTTP_RH_ACCEPT_LANGUAGE,
    HTTP_RH_AUTHORIZATION,
    HTTP_RH_EXPECT,
    HTTP_RH_FROM,
    HTTP_RH_HOST,
    HTTP_RH_IF_MATCH,
    HTTP_RH_IF_MODIFIED_SINCE,
    HTTP_RH_IF_NONE_MATCH,
    HTTP_RH_IF_RANGE,
    HTTP_RH_IF_UNMODIFIED_SINCE,
    HTTP_RH_MAX_FORWARDS,
    HTTP_RH_PROXY_AUTHORIZATION,
    HTTP_RH_RANGE,
    HTTP_RH_REFERER,
    HTTP_RH_TE,
    HTTP_RH_USER_AGENT,
    
    HTTP_HEADER_NOT_RECOGNIZED
};

struct http_headerValues
{
    http_headerEnum name;
    string val[8];
};

struct http_message
{
    http_MethodType   method;
    string            requestURI;
    u16               httpVersion;
    
    http_headerValues hValues[16];
    u32 usedValues;
};


/* ------------------ */
/* GENERAL CONNECTION */
/* ------------------ */

HTTPUri        ls_httpParseUrl(string url);

HTTPSocket     ls_httpConnectByName(string serverNameString, u32 port);
HTTPConnection ls_httpConnectByUrl(string url, u32 port);

string         ls_httpRequest(HTTPConnection info, string message);

string         ls_httpGET(HTTPConnection info, string message);

#if 0
s32            ls_getHeaderLength(char *content);

/*I Made these functions to be used on a server-side program.*/
void           ls_receiveAndProcessMessage(HTTPSocket s);
HTTPConnection ls_openAndBind(string hostname, string port, http_socketHints *hints);
s32            ls_setListenSocket(HTTPSocket listener, u32 maxQueueSize);
HTTPSocket     ls_acceptConnection(HTTPSocket listener, HTTPConnection *info);
#endif

#endif //LS_HTTP_H

#ifdef LS_HTTP_IMPLEMENTATION

#ifdef LS_PLAT_WINDOWS
void ls_wsaLogError(const char *fName, s64 errorCode)
{
#define WSA_INVALID_EVENT_NON_PTR 0
    string buf;
    switch(errorCode)
    {
        case WSA_IO_PENDING: buf = ls_strInit("WSA: IO PENDING"); break;
        case WSA_IO_INCOMPLETE: buf = ls_strInit("WSA: IO INCOMPLETE"); break;
        case WSA_INVALID_HANDLE: buf = ls_strInit("WSA: INVALID HANDLE"); break;
        case WSA_INVALID_PARAMETER: buf = ls_strInit("WSA: INVALID PARAMETER"); break;
        case WSA_NOT_ENOUGH_MEMORY: buf = ls_strInit("WSA: NOT ENOUGH MEMORY"); break;
        case WSA_OPERATION_ABORTED: buf = ls_strInit("WSA: OPERATION ABORTED"); break;
        case WSA_INVALID_EVENT_NON_PTR: buf = ls_strInit("WSA: INVALID EVENT"); break;
        case WSA_MAXIMUM_WAIT_EVENTS: buf = ls_strInit("WSA: MAX WAIT EVENTS"); break;
        case WSA_WAIT_FAILED: buf = ls_strInit("WSA: WAIT FAILED"); break;
        //case WSA_WAIT_EVENT_0: buf = ls_strInit("WSA: WAIT EVENT 0"); break;
        case WSA_WAIT_IO_COMPLETION: buf = ls_strInit("WSA: WAIT IO COMPLETION"); break;
        case WSA_WAIT_TIMEOUT: buf = ls_strInit("WSA: WAIT TIMEOUT"); break;
        case WSAEINTR: buf = ls_strInit("INTERRUPTED FUN CALL"); break;
        case WSAEBADF: buf = ls_strInit("WSA: FILE HANDLE NOT FOUND"); break;
        case WSAEACCES: buf = ls_strInit("WSA: PERMISSION DENIED"); break;
        case WSAEFAULT: buf = ls_strInit("WSA: BAD ADDRESS"); break;
        case WSAEINVAL: buf = ls_strInit("WSA: INVALID ARG"); break;
        case WSAEMFILE: buf = ls_strInit("WSA: TOO MANY OPEN FILES"); break;
        case WSAEWOULDBLOCK: buf = ls_strInit("WSA: RESOURCE TEMP. UNAVAIL."); break;
        case WSAEINPROGRESS: buf = ls_strInit("WSA: OPER. NOW IN PROGRESS"); break; 
        case WSAEALREADY: buf = ls_strInit("WSA: OPER. ALREADY IN PROGRESS"); break;
        case WSAENOTSOCK: buf = ls_strInit("WSA: SOCKET OPER. ON NON-SOCKET"); break;
        case WSAEDESTADDRREQ: buf = ls_strInit("WSA: DESTINATION ADDR. REQUIRED"); break;
        case WSAEMSGSIZE: buf = ls_strInit("WSA: MESSAGE TOO LONG"); break; 
        case WSAEPROTOTYPE: buf = ls_strInit("WSA: PROTOCOL WRONG TYPE FOR SOCKET"); break;
        case WSAENOPROTOOPT: buf = ls_strInit("WSA: BAD PROTOCOL OPTION"); break;
        case WSAEPROTONOSUPPORT: buf = ls_strInit("WSA: PROTOCOL NOT SUPPORTED"); break;
        case WSAESOCKTNOSUPPORT: buf = ls_strInit("WSA: SOCKET TYPE NOT SUPPORTED"); break; 
        case WSAEOPNOTSUPP: buf = ls_strInit("WSA: OPERATION NOT SUPPORTED"); break;
        case WSAEPFNOSUPPORT: buf = ls_strInit("WSA: PROTOCOL FAMILY NOT SUPPORTED"); break;
        case WSAEAFNOSUPPORT: buf = ls_strInit("WSA: ADDR.FAM. NOT SUPP. BY PROTO.FAM."); break;
        case WSAEADDRINUSE: buf = ls_strInit("WSA: ADDRESS ALREADY IN USE"); break;
        case WSAEADDRNOTAVAIL: buf = ls_strInit("WSA: CANNOT ASSIGN REQUESTED ADDRESS"); break;
        case WSAENETDOWN: buf = ls_strInit("WSA: NETWORK IS DOWN"); break;
        case WSAENETUNREACH: buf = ls_strInit("WSA: NETWORK IS UNREACHABLE"); break;
        case WSAENETRESET: buf = ls_strInit("WSA: NETWORK DROPPED CONN. ON RESET"); break;
        case WSAECONNABORTED: buf = ls_strInit("WSA: SOFTWARE CAUSED CONN. ABORT");  break;
        case WSAECONNRESET: buf = ls_strInit("WSA: CONNECTION RESET BY PEER"); break;
        case WSAENOBUFS: buf = ls_strInit("WSA: NO BUFFER SPACE AVAIL."); break;
        case WSAEISCONN: buf = ls_strInit("WSA: SOCKET IS ALREADY CONN."); break;
        case WSAENOTCONN: buf = ls_strInit("WSA: SOCKET IS NOT CONN."); break;
        case WSAESHUTDOWN: buf = ls_strInit("WSA: CANNOT SEND AFTER SOCKET SHUTDOWN"); break;
        case WSAETOOMANYREFS: buf = ls_strInit("WSA: TOO MANY REFERENCES"); break;
        case WSAETIMEDOUT: buf = ls_strInit("WSA: CONNECTION TIMED OUT"); break;
        case WSAECONNREFUSED: buf = ls_strInit("WSA: CONNECTION REFUSED"); break;
        case WSAELOOP: buf = ls_strInit("WSA: CANNOT TRANSLATE NAME"); break;
        case WSAENAMETOOLONG: buf = ls_strInit("WSA: NAME TOO LONG"); break;
        case WSAEHOSTDOWN: buf = ls_strInit("WSA: HOST IS DOWN"); break;
        case WSAEHOSTUNREACH: buf = ls_strInit("WSA: NO ROUTE TO HOST"); break;
        case WSAENOTEMPTY: buf = ls_strInit("WSA: DIRECTORY NOT EMPTY"); break;
        case WSAEPROCLIM: buf = ls_strInit("WSA: TOO MANY PROCESSES"); break;
        case WSAEUSERS: buf = ls_strInit("WSA: USER QUOTA EXCEEDED"); break;
        case WSAEDQUOT: buf = ls_strInit("WSA: DISK QUOTA EXCEEDED"); break;
        case WSAESTALE: buf = ls_strInit("WSA: STALE FILE HANDLE REF."); break;
        case WSAEREMOTE: buf = ls_strInit("WSA: ITEM IS REMOTE"); break;
        case WSASYSNOTREADY: buf = ls_strInit("WSA: NETWORK SUBSYS. IS UNAVAILABLE"); break;
        case WSAVERNOTSUPPORTED: buf = ls_strInit("WSA: WINSOCK DLL VER. OUT OF RANGE"); break;
        case WSANOTINITIALISED: buf = ls_strInit("WSA: WSAStartup() NOT YET PERFORMED"); break;
        case WSAEDISCON: buf = ls_strInit("WSA: GRACEFUL SHUTDOWN IN PROGRESS");  break;
        case WSAENOMORE: buf = ls_strInit("WSA: NO MORE RESULTS BY WSALookupServiceNext()"); break;
        case WSAECANCELLED: buf = ls_strInit("WSA: CALL HAS BEEN CANCELED"); break;
        case WSAEINVALIDPROCTABLE: buf = ls_strInit("WSA: INVALID PROC. TABLE");  break;
        case WSAEINVALIDPROVIDER: buf = ls_strInit("WSA: SERVICE PROVIDER IS INVALID"); break;
        case WSAEPROVIDERFAILEDINIT: buf = ls_strInit("WSA: SERVICE PROVIDER FAILED TO INIT."); break;
        case WSASYSCALLFAILURE: buf = ls_strInit("WSA: SYSTEM CALL FAILURE");  break;
        case WSASERVICE_NOT_FOUND: buf = ls_strInit("WSA: SERVICE NOT FOUND"); break;
        case WSATYPE_NOT_FOUND: buf = ls_strInit("WSA: CLASS TYPE NOT FOUND"); break;
        case WSA_E_NO_MORE: buf = ls_strInit("WSA: NO MORE RESULTS BY WSALookupServiceNext()"); break;
        case WSA_E_CANCELLED: buf = ls_strInit("WSA: CALL WAS CANCELLED"); break;
        case WSAEREFUSED: buf = ls_strInit("WSA: DATABASE QUERY WAS REFUSED"); break;
        case WSAHOST_NOT_FOUND: buf = ls_strInit("WSA: HOST NOT FOUND"); break;
        case WSATRY_AGAIN: buf = ls_strInit("WSA: NON-AUTHORITATIVE HOST NOT FOUND"); break;
        case WSANO_RECOVERY: buf = ls_strInit("WSA: NON RECOVERABLE ERROR DURING DATABASE LOOKUP"); break;
        case WSANO_DATA: buf = ls_strInit("WSA: VALID NAME, NO DATA RECORD OF REQUESTED TYPE"); break;
    }
    
    ls_printf("%s returned error %d: %s", fName, errorCode, buf);
}
#endif

void ls_setHints(struct addrinfo *h, http_socketHints *hints)
{
    switch(hints->flags)
    {
        case HTTP_PASSIVE: h->ai_flags = AI_PASSIVE; break;
        case HTTP_CANONNAME: h->ai_flags = AI_CANONNAME; break;
        case HTTP_NUMERICHOST: h->ai_flags = AI_NUMERICHOST; break;
        case HTTP_ALL: h->ai_flags = AI_ALL; break;
        case HTTP_ADDRCONFIG: h->ai_flags = AI_ADDRCONFIG; break;
        case HTTP_V4MAPPED: h->ai_flags = AI_V4MAPPED; break;
        case HTTP_NON_AUTHORITATIVE: h->ai_flags = AI_NON_AUTHORITATIVE; break;
        case HTTP_SECURE: h->ai_flags = AI_SECURE; break;
        case HTTP_RETURN_PREFERRED_NAMES: h->ai_flags = AI_RETURN_PREFERRED_NAMES; break;
        case HTTP_FQDN: h->ai_flags = AI_FQDN; break;
        case HTTP_FILESERVER: h->ai_flags = AI_FILESERVER; break;
    }
    
    switch(hints->family)
    {
        case HTTP_UNSPEC: h->ai_family = AF_UNSPEC; break;
        case HTTP_UNIX: h->ai_family = AF_UNIX; break;
        case HTTP_INET: h->ai_family = AF_INET; break;
        case HTTP_IMPLINK: h->ai_family = AF_IMPLINK; break;
        case HTTP_PUP: h->ai_family = AF_PUP; break;
        case HTTP_CHAOS: h->ai_family = AF_CHAOS; break;
        case HTTP_NS: h->ai_family = AF_NS; break;
        case HTTP_IPX: h->ai_family = AF_IPX; break;
        case HTTP_ISO: h->ai_family = AF_ISO; break;
        case HTTP_OSI: h->ai_family = AF_OSI; break;
        case HTTP_ECMA: h->ai_family = AF_ECMA; break;
        case HTTP_DATAKIT: h->ai_family = AF_DATAKIT; break;
        case HTTP_CCITT: h->ai_family = AF_CCITT; break;
        case HTTP_SNA: h->ai_family = AF_SNA; break;
        case HTTP_DECnet: h->ai_family = AF_DECnet; break;
        case HTTP_DLI: h->ai_family = AF_DLI; break;
        case HTTP_LAT: h->ai_family = AF_LAT; break;
        case HTTP_HYLINK: h->ai_family = AF_HYLINK; break;
        case HTTP_APPLETALK: h->ai_family = AF_APPLETALK; break;
        case HTTP_NETBIOS: h->ai_family = AF_NETBIOS; break;
        case HTTP_VOICEVIEW: h->ai_family = AF_VOICEVIEW; break;
        case HTTP_FIREFOX: h->ai_family = AF_FIREFOX; break;
        case HTTP_UNKNOWN1: h->ai_family = AF_UNKNOWN1; break;
        case HTTP_BAN: h->ai_family = AF_BAN; break;
        case HTTP_ATM: h->ai_family = AF_ATM; break;
        case HTTP_INET6: h->ai_family = AF_INET6; break;
        case HTTP_CLUSTER: h->ai_family = AF_CLUSTER; break;
        case HTTP_12844: h->ai_family = AF_12844; break;
        case HTTP_IRDA: h->ai_family = AF_IRDA; break;
        case HTTP_NETDES: h->ai_family = AF_NETDES; break;
        case HTTP_TCNPROCESS: h->ai_family = AF_TCNPROCESS; break;
        case HTTP_TCNMESSAGE: h->ai_family = AF_TCNMESSAGE; break;
        case HTTP_ICLFXBM: h->ai_family = AF_ICLFXBM; break;
        case HTTP_BTH: h->ai_family = AF_BTH; break;
        case HTTP_LINK: h->ai_family = AF_LINK; break;
        case HTTP_HYPERV: h->ai_family = AF_HYPERV; break;
        case HTTP_MAX: h->ai_family = AF_MAX; break;
    }
    
    switch(hints->type)
    {
        case HTTP_STREAM: h->ai_socktype = SOCK_STREAM; break;
        case HTTP_DGRAM: h->ai_socktype = SOCK_DGRAM; break;
        case HTTP_RAW: h->ai_socktype = SOCK_RAW; break;
        case HTTP_RDM: h->ai_socktype = SOCK_RDM; break;
        case HTTP_SEQPACKET: h->ai_socktype = SOCK_SEQPACKET; break;
    }
    
    return;
}

void ls_setSockOpt(http_socketHints *hints, s32 *level, s32 *optName)
{
    switch(hints->level)
    {
        case HTTP_SOCKET: *level = SOL_SOCKET; break;
        case HTTP_IPPROTO_TCP: *level = IPPROTO_TCP; break;
        case HTTP_NSPROTO_IPX: *level = NSPROTO_IPX; break;
    }
    
    switch (hints->opt)
    {
        case HTTP_DEBUG: *optName = SO_DEBUG; break;
        case HTTP_ACCEPTCONN: *optName = SO_ACCEPTCONN; break;
        case HTTP_REUSEADDR: *optName = SO_REUSEADDR; break;
        case HTTP_KEEPALIVE: *optName = SO_KEEPALIVE; break;
        case HTTP_DONTROUTE: *optName = SO_DONTROUTE; break;
        case HTTP_BROADCAST: *optName = SO_BROADCAST; break;
        case HTTP_USELOOPBACK: *optName = SO_USELOOPBACK; break;
        case HTTP_LINGER: *optName = SO_LINGER; break;
        case HTTP_OOBINLINE: *optName = SO_OOBINLINE; break;
        case HTTP_DONTLINGER: *optName = SO_DONTLINGER; break;
        case HTTP_EXCLUSIVEADDRUSE: *optName = SO_EXCLUSIVEADDRUSE; break;
        case HTTP_SNDBUF: *optName = SO_SNDBUF; break;
        case HTTP_RCVBUF: *optName = SO_RCVBUF; break;
        case HTTP_SNDLOWAT: *optName = SO_SNDLOWAT; break;
        case HTTP_RCVLOWAT: *optName = SO_RCVLOWAT; break;
        case HTTP_SNDTIMEO: *optName = SO_SNDTIMEO; break;
        case HTTP_RCVTIMEO: *optName = SO_RCVTIMEO; break;
        case HTTP_ERROR: *optName = SO_ERROR; break;
        case HTTP_TYPE: *optName = SO_TYPE; break;
        case HTTP_BSP_STATE: *optName = SO_BSP_STATE; break;
        case HTTP_GROUP_ID: *optName = SO_GROUP_ID; break;
        case HTTP_GROUP_PRIORITY: *optName = SO_GROUP_PRIORITY; break;
        case HTTP_MAX_MSG_SIZE: *optName = SO_MAX_MSG_SIZE; break;
        case HTTP_CONDITIONAL_ACCEPT: *optName = SO_CONDITIONAL_ACCEPT; break;
        case HTTP_PAUSE_ACCEPT: *optName = SO_PAUSE_ACCEPT; break;
        case HTTP_COMPARTMENT_ID: *optName = SO_COMPARTMENT_ID; break;
        case HTTP_RANDOMIZE_PORT: *optName = SO_RANDOMIZE_PORT; break;
        case HTTP_PORT_SCALABILITY: *optName = SO_PORT_SCALABILITY; break;
        case HTTP_REUSE_UNICASTPORT: *optName = SO_REUSE_UNICASTPORT; break;
        case HTTP_REUSE_MULTICASTPORT: *optName = SO_REUSE_MULTICASTPORT; break;
    }
}



/* ------------------ */
/* GENERAL CONNECTION */
/* ------------------ */

HTTPUri ls_httpParseUrl(string urlString)
{
    HTTPUri url = {};
    
    //TODO: Redo completely using views
    view urlView = ls_viewCreate(urlString);
    
    view scheme = ls_viewNextDelimiter(urlView, ':');
    url.scheme = scheme;
    
    view hasAuthority = ls_viewNextNChars(scheme, 2);
    if(hasAuthority.s == "//")
    {
        //NOTE: Parse userinfo, host and port
        view authority = ls_viewNextDelimiter(hasAuthority, '/');
        view path = ls_viewNextLine(authority);
        
        url.authority = authority;
        url.path = path;
    }
    else
    {
        view path = ls_viewNextLine(scheme);
        url.path = path;
    }
    
    return url;
}

// @TODO: Do I want to record the host name and save it 
//in the http_connInfo struct?
HTTPSocket ls_httpConnectByName(string serverNameString, u32 port)
{
    ADDRINFOA *addrInfo = NULL;
    u32 addr;
    //sockaddr_in *server;
    HTTPSocket conn;
    
    char serverName[256] = {};
    char portString[8]  = {};
    
    ls_strToCStr_t(serverNameString, serverName, 256);
    ls_itoa_t(port, portString, 8);
    
    conn = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    if(conn == INVALID_SOCKET)
    { LogMsgF(FALSE, "When creating socket got error: %d\n", WSAGetLastError()); return NULL; }
    
    if(inet_addr(serverName) == INADDR_NONE)
    { 
        s32 success = getaddrinfo(serverName, portString, NULL, &addrInfo);
        LogMsgF(success == 0, "When getting address info got error: %d", WSAGetLastError());
    }
    else
    {
        char hostName[512] = {};
        char serviceName[512] = {};
        addr = inet_addr(serverName);
        
        sockaddr_in server = {};
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = addr;
        server.sin_port = htons(port);
        
        s32 success = getnameinfo((const sockaddr *)&server, sizeof(server), 
                                  hostName, sizeof(hostName), serviceName, sizeof(serviceName), NULL);
        LogMsgF(success == 0, "When getting name info got error: %d", WSAGetLastError());
        
        success = getaddrinfo(hostName, portString, NULL, &addrInfo);
        LogMsgF(success == 0, "When getting address info got error: %d", WSAGetLastError());
    }
    
    if(addrInfo->ai_addr == NULL)
    { 
        closesocket(conn); 
        LogMsg(FALSE, "Could not find address info.\n");
        return 0;
    }
    /*
    switch(addrInfo->ai_addr.sa_family)
    {
    case AF_INET:
    {
    server = (sockaddr_in *)&addrInfo->ai_addr;
    }
    break;
    case AF_INET6:
    {
    //server = (sockaddr_in6 *) addrInfo->ai_addr;
    }
    break;
    default:
    ls_printf("Error: when casting sockaddr to sockaddr_in found unhandled sa_family.\n");
    break;
    }
    */
    //ls_memcpy(addrInfo->ai_addr, &server, sizeof(sockaddr_in));
    
    s32 success = connect(conn, addrInfo->ai_addr, sizeof(*(addrInfo->ai_addr)));
    
    if(success != 0)
    {
        LogMsgF(FALSE, "When connecting to server got error: %d\n", WSAGetLastError());
        return NULL;
    }
    
    freeaddrinfo(addrInfo);
    
    return conn;
}

HTTPConnection ls_httpConnectByUrl(string urlString, u32 port)
{
    HTTPConnection connection = {};
    
    connection.uri    = ls_httpParseUrl(urlString);
    connection.socket = ls_httpConnectByName(connection.uri.authority.s, port);
    
    return connection;
}

string ls_httpRequest(HTTPConnection info, string message)
{
    return ls_httpGET(info, message);
}

string ls_httpGET(HTTPConnection info, string message)
{
    /*
    ///////////// send GET request /////////////
    ls_sprintf(tmpBuffer, "GET %s HTTP/1.0", info->filepath.data);
    string message = tmpBuffer;
    message += "\r\n";
    ls_sprintf(tmpBuffer, "Host: %s", info->serverName.data);
    message += tmpBuffer;
    message += "\r\n\r\n";
    */
    
    /*@NOTE: HTTP/1.1 length of the answer might be specified by a 
    * Content-Length  header, by Transfer-Encoding: chunked or by end-of-file. 
    * And since HTTP/1.1 allows by default multiple requests over a single 
    * connection (keep-alive) the simple approach of reading until the end might 
    * cause your connection to stall because the server does not close the 
    * connection and instead waits for a new request.
    *
    * If you would issue instead a HTTP/1.0 request you would not have to 
    * deal with all these problems, i.e. no chunked mode and no keep-alive 
    * by default. Then you could simply read until you get no more data.
    */
    
    //string message = ls_strConstant("GET /wiki/Database_Mostri HTTP/1.1");
    
    s32 bytesSent = send(info.socket, message.data, message.len, 0);
    
    LogMsg(bytesSent >= message.len, "The message was not fully sent.\n");
    
    if(bytesSent == SOCKET_ERROR)
    {
        LogMsgF(FALSE, "send() returned error code: %d", WSAGetLastError());
        return {};
    }
    
    
    ls_printf("Buffer being sent:\n%s\n\n", message);
    
    const int bufSize = 512;
    char readBuffer[bufSize], tmpBuffer[bufSize];
    
    s64 thisReadSize = recv(info.socket, readBuffer, bufSize, 0);
    
    ls_printf("Response:\n%cs\n", readBuffer);
    return {};
#if 0
    ///////////// step 3 - get received bytes ////////////////
    // Receive until the peer closes the connection
    
    s64 totalBytesRead = 0;
    char *tmpResult = 0;
    while(1)
    {
        ls_zeroMem(readBuffer, bufSize);
        s64 thisReadSize = recv(info.socket, readBuffer, bufSize, 0);
        
        if(thisReadSize == SOCKET_ERROR)
        {
            s32 errorCode = WSAGetLastError();
            ls_printf("recv returned error code: %d", errorCode);
            if(tmpResult) { ls_free(tmpResult); }
            return {};
        }
        
        if(thisReadSize <= 0) { break; }
        
        tmpResult = (char*)ls_realloc(tmpResult, 
                                      totalBytesRead, thisReadSize+totalBytesRead);
        
        ls_memcpy(readBuffer, tmpResult+totalBytesRead, thisReadSize);
        totalBytesRead += thisReadSize;
    }
    
    string result = { tmpResult, (u32)totalBytesRead, (u32)totalBytesRead };
    return result;
#endif
    
#if 0
    s64 headerLen = ls_getHeaderLength(tmpResult);
    
    if(headerLen == -1) 
    { ls_free(tmpResult); ls_printf("Error, recieved bogus data after the GET.\n"); return (char *)""; }
    
    u64 contenLen = totalBytesRead - headerLen;
    
    char *result = (char *)ls_alloc(sizeof(char) *(contenLen + 1));
    
    ls_memcpy(tmpResult+headerLen, result, contenLen);
    result[contenLen] = 0;
    
    char *myTmp = (char *)ls_alloc(sizeof(char) * (headerLen + 1));
    
    //NOTETODO: Check 0 termination
    ls_memcpy((void*)tmpResult, (void*)myTmp, headerLen);
    myTmp[headerLen] = 0;
    
    ls_free(tmpResult);
    *headerOut = myTmp;
    
    *bytesReturnedOut = contenLen;
    
    string returnVal = { result, contentLen+1, contentLen+1 };
    
    return returnVal;
#endif
}

/* ------------------ */
/* SERVER? CONNECTION */
/* ------------------ */

#if 0
s32 ls_setListenSocket(HTTPSocket listener, u32 maxQueueSize)
{
    s32 errorCode = listen(listener, maxQueueSize);
    if(errorCode == SOCKET_ERROR)
    { ls_wsaLogError("listen", WSAGetLastError()); return -1;}
    
    return 0;
}

HTTPSocket ls_acceptConnection(HTTPSocket listener, HTTPConnection *info)
{
    HTTPSocket Result;
    s32 addrSize = sizeof(info->address);
    Result = accept(listener, ((struct sockaddr *)&(info->address)), &addrSize);
    
    return Result;
}

void ls_parseMsgHeaders(string *words, u32 numWords,  http_message *msg)
{
    http_headerValues *v = &msg->hValues[msg->usedValues++];
    
    if(words[0] == "Host:")
    { v->name = HTTP_RH_HOST; }
    else if(words[0] == "Connection:")
    { v->name = HTTP_GH_CONNECTION; }
    else if(words[0] == "Date:")
    { v->name = HTTP_GH_DATE; }
    else if(words[0] == "Upgrade:")
    { v->name = HTTP_GH_UPGRADE; }
    else if(words[0] == "Cache-Control:")
    { v->name = HTTP_GH_CACHE_CONTROL; }
    else if(words[0] == "User-Agent:")
    { v->name = HTTP_RH_USER_AGENT; }
    else if(words[0] == "Accept:")
    { v->name = HTTP_RH_ACCEPT; }
    else if(words[0] == "Accept-Charset:")
    { v->name = HTTP_RH_ACCEPT_CHARSET; }
    else if(words[0] == "Accept-Encoding:")
    { v->name = HTTP_RH_ACCEPT_ENCODING; }
    else if(words[0] == "Accept-Language:")
    { v->name = HTTP_RH_ACCEPT_LANGUAGE; }
    else if(words[0] == "Transfer-Encoding:")
    { v->name = HTTP_GH_TRANSFER_ENCODING; }
    else if(words[0] == "Authorization:")
    { v->name = HTTP_RH_AUTHORIZATION; }
    else if(words[0] == "Expect:")
    { v->name = HTTP_RH_EXPECT; }
    else if(words[0] == "From:")
    { v->name = HTTP_RH_FROM; }
    else if(words[0] == "If-Match:")
    { v->name = HTTP_RH_IF_MATCH; }
    else if(words[0] == "If-Modified-Since:")
    { v->name = HTTP_RH_IF_MODIFIED_SINCE; }
    else if(words[0] == "If-None-Match:")
    { v->name = HTTP_RH_IF_NONE_MATCH; }
    else if(words[0] == "If-Range:")
    { v->name = HTTP_RH_IF_RANGE; }
    else if(words[0] == "If-Unmodified-Since:")
    { v->name = HTTP_RH_IF_UNMODIFIED_SINCE; }
    else if(words[0] == "Max-Forwards:")
    { v->name = HTTP_RH_MAX_FORWARDS; }
    else if(words[0] == "Proxy-Authorization:")
    { v->name = HTTP_RH_PROXY_AUTHORIZATION; }
    else if(words[0] == "Range:")
    { v->name = HTTP_RH_RANGE; }
    else if(words[0] == "Referer:")
    { v->name = HTTP_RH_REFERER; }
    else if(words[0] == "TE:")
    { v->name = HTTP_RH_TE; }
    else if(words[0] == "Pragma:")
    { v->name = HTTP_GH_PRAGMA; }
    else if(words[0] == "Trailer:")
    { v->name = HTTP_GH_TRAILER; }
    else if(words[0] == "Via:")
    { v->name = HTTP_GH_VIA; }
    else if(words[0] == "Warning:")
    { v->name = HTTP_GH_WARNING; }
    else
    { v->name = HTTP_HEADER_NOT_RECOGNIZED; }
    
    for(u32 i = 0; i < (numWords-1); i++)
    { v->val[i] = words[i+1]; }
}

void ls_sendResponse(HTTPSocket sock, http_message *Request)
{
    string msgBuffer = ls_strAlloc(512);
    string Space = ls_strInit(" ");
    string CRLF  = ls_strInit("\r\n");
    
    // Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF
    if(Request->httpVersion == 0x20) { ls_strAppend(&msgBuffer, "HTTP/2"); }
    else if(Request->httpVersion == 0x11) { ls_strAppend(&msgBuffer, "HTTP/1.1"); }
    else if(Request->httpVersion == 0x10) { ls_strAppend(&msgBuffer, "HTTP/1.0"); }
    
    ls_strAppend(&msgBuffer, Space);
    
    // @TODO: Send Status Code Conditionally instead of hard-coded
    ls_strAppend(&msgBuffer, (char *)StatusCode[HTTP_SC_OK]);
    ls_strAppend(&msgBuffer, Space);
    
    // Send Useless Reason Phrase
    
    ls_strAppend(&msgBuffer, "DontWannaCodeReasonPhrases");
    ls_strAppend(&msgBuffer, CRLF);
    
    //Testing General Header Keep-Alive
    ls_strAppend(&msgBuffer, "Keep-Alive: timeout=5, max=1000");
    ls_strAppend(&msgBuffer, CRLF);
    
    // Entity Header
    ls_strAppend(&msgBuffer, "Content-Type: text/html");
    ls_strAppend(&msgBuffer, CRLF);
    ls_strAppend(&msgBuffer, CRLF);
    
    char *data;
    //u64 dataSize = ls_readFile("C:\\Users\\loren\\Desktop\\test.bmp", &data, 0);
    
    //TODO What the fuck am I supposed to do here?
    
#if 0
    
    u64 dataSize = ls_readFile("..\\code\\testPage.html", &data, 0);
    
    char *allData = (char *)ls_alloc(sizeof(char)*(dataSize + msgBuffer.len));
    
    ls_memcpy(msgBuffer.data, allData, msgBuffer.len);
    ls_memcpy(data, allData + msgBuffer.len, dataSize);
    
    
    s32 bytesSent = send(sock, allData, dataSize + msgBuffer.len, NULL);
    if(bytesSent == SOCKET_ERROR)
    { ls_wsaLogError("send", WSAGetLastError()); }
    
    //TODO: If bytesSent < msgBuffer.len do something.
#endif
    return;
}

void ls_receiveAndProcessMessage(HTTPSocket sock)
{
    u8 buff[1024] = {};
    int bytesRecieved = recv(sock, (char *)buff, sizeof(buff), NULL);
    
    http_message Msg = {};
    
    //Because I'm recieving from a Client, it's gonna be a request message
    /* Request-Line
    *  (GeneralHeader & RequestHeader &  EntityHeader)
    *
    *  MessageBody
    */
    
    u32 numOfLines = 0;
    string strBuff = { (char *)buff, sizeof(buff), sizeof(buff) }; //TODO:NOTE Is this good?
    string *lines = ls_strBreakByLine(strBuff, &numOfLines);
    
    string **words = (string **)ls_alloc(sizeof(string *)*numOfLines);
    u32 *numOfWords = (u32 *)ls_alloc(sizeof(u32)*numOfLines);
    for(u32 i = 0; i < numOfLines; i++)
    { words[i] = ls_strBreakBySpace(lines[i], numOfWords + i); }
    
    //Process Request Line
    u32 ReqLineIdx = 0;
    if(words[ReqLineIdx][0] == "GET")
    { Msg.method = HTTP_GET; }
    else if(words[ReqLineIdx][0] == "PUT")
    { Msg.method = HTTP_PUT; }
    else if(words[ReqLineIdx][0] == "POST")
    { Msg.method = HTTP_POST; }
    else if(words[ReqLineIdx][0] == "HEAD")
    { Msg.method = HTTP_HEAD; }
    else if(words[ReqLineIdx][0] == "OPTIONS")
    { Msg.method = HTTP_OPTIONS; }
    else if(words[ReqLineIdx][0] == "DELETE")
    { Msg.method = HTTP_DELETE; }
    else if(words[ReqLineIdx][0] == "TRACE")
    { Msg.method = HTTP_TRACE; }
    else if(words[ReqLineIdx][0] == "CONNECT")
    { Msg.method = HTTP_CONNECT; }
    else
    { Msg.method = HTTP_METHOD_NOT_ALLOWED; }
    
    Msg.requestURI = words[ReqLineIdx][1];
    
    if(words[ReqLineIdx][2] == "HTTP/1.1")
    { Msg.httpVersion = 0x11; }
    else if(words[ReqLineIdx][2] == "HTTP/1.0")
    { Msg.httpVersion = 0x10; }
    
    //Process ALL Headers (genearal,  request, entity)
    
    for(u32 i = 1; i < numOfLines; i++)
    { ls_parseMsgHeaders(words[i], numOfWords[i], &Msg); }
    
    ls_sendResponse(sock, &Msg);
}

HTTPConnection ls_openAndBind(string hostname, string port, http_socketHints *hints)
{
    HTTPConnection Result = {}; 
#ifdef LS_PLAT_WINDOWS
    
    struct addrinfo addressInfo = {};
    struct addrinfo *p;
    struct addrinfo *servInfo;
    
    ls_setHints(&addressInfo, hints);
    
    s32 errorCode;
    errorCode = getaddrinfo(hostname.data, port.data, &addressInfo, &servInfo);
    if(errorCode != 0)
    { ls_wsaLogError("getaddrinfo", errorCode); return Result; }
    
    SOCKET resultSock;
    
    s32 sockLevel = 0;
    s32 optName = 0;
    ls_setSockOpt(hints, &sockLevel, &optName);
    
    for(p = servInfo; p != NULL; p = p->ai_next)
    {
        resultSock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if(resultSock == INVALID_SOCKET)
        { ls_wsaLogError("socket", WSAGetLastError()); continue; }
        
        if(hints->areOptsBoolean == TRUE)
        {
            const char val[sizeof(int)] = {};
            errorCode = setsockopt(resultSock, sockLevel, optName, val, sizeof(int));
        }
        else
        { errorCode = setsockopt(resultSock, sockLevel, optName, (const char *)hints->optVal, hints->optLen); }
        
        if(errorCode == SOCKET_ERROR)
        { ls_wsaLogError("setsockopt", WSAGetLastError()); return Result; }
        
        errorCode = bind(resultSock, p->ai_addr, p->ai_addrlen);
        if(errorCode == SOCKET_ERROR)
        {
            closesocket(resultSock);
            ls_wsaLogError("bind", WSAGetLastError());
            continue;
        }
        break;
    }
    
    freeaddrinfo(servInfo);
    
    if(p == NULL) { ls_printf("server: failed to bind\n"); return Result; }
    
    Result.socket = resultSock;
    return Result;
    
#endif
    
}


s32 ls_getHeaderLength(char *content)
{
    //TODO: I don't understand this code.
#if 0
    const char *srchStr1 = "\r\n\r\n", *srchStr2 = "\n\r\n\r";
    u32 srchStrLen = 4;
    
    char *findPos;
    s32 offset = -1;
    
    findPos = ls_strstr(content, srchStr1);
    if (findPos != NULL)
    {
        offset = findPos - content;
        offset += srchStrLen;
    }
    
    else
    {
        findPos = ls_strstr(content, srchStr2);
        if (findPos != NULL)
        {
            offset = findPos - content;
            offset += srchStrLen;
        }
    }
    return offset;
#endif
    return 0;
}

#endif //#if 0

#endif