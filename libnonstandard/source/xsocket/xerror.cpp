//-----------------------------------------------------------------------------
#include "xsocket.h"
#include "xerror.h"
//-----------------------------------------------------------------------------
_NSTD_BEGIN;
//-----------------------------------------------------------------------------
C_ErrorWSA::C_ErrorWSA() : m_iWSAError(WSAGetLastError()) {}
//-----------------------------------------------------------------------------
C_ErrorWSA::C_ErrorWSA(IN int wsaerror) : m_iWSAError(wsaerror) {}
//-----------------------------------------------------------------------------
C_ErrorWSA::C_ErrorWSA(IN S_XOverlapped &overlapped)
{
	unsigned long ulBytes, ulFlag;

	WSAGetOverlappedResult(overlapped.Socket, reinterpret_cast<OVERLAPPED *>(&overlapped), &ulBytes, FALSE, &ulFlag); // 取得重疊行為錯誤
	m_iWSAError = WSAGetLastError();
}
//-----------------------------------------------------------------------------
C_ErrorWSA::~C_ErrorWSA() {}
//-----------------------------------------------------------------------------
C_ErrorWSA::operator int () const
{
	return m_iWSAError;
}
//-----------------------------------------------------------------------------
C_ErrorWSA::operator estring () const
{
	estring szWSAError;

	switch(m_iWSAError)
	{
	case WSASUCCESS: szWSAError = __T("success"); break;
	case WSA_E_CANCELLED: szWSAError = __T("(WSA_E_CANCELLED) call was canceled"); break;
	case WSA_E_NO_MORE: szWSAError = __T("(WSA_E_NO_MORE) no more results"); break;
#ifdef _WINSOCK2_
	case WSA_INVALID_HANDLE: szWSAError = __T("(WSA_INVALID_HANDLE) specified event object handle is invalid"); break;
	case WSA_INVALID_PARAMETER: szWSAError = __T("(WSA_INVALID_PARAMETER) one or more parameters are invalid"); break;
	case WSA_IO_INCOMPLETE: szWSAError = __T("(WSA_IO_INCOMPLETE) overlapped i/o event object not in signaled state"); break;
	case WSA_IO_PENDING: szWSAError = __T("(WSA_IO_PENDING) overlapped operations will complete later"); break;
	case WSA_NOT_ENOUGH_MEMORY: szWSAError = __T("(WSA_NOT_ENOUGH_MEMORY) insufficient memory available"); break;
	case WSA_OPERATION_ABORTED: szWSAError = __T("(WSA_OPERATION_ABORTED) overlapped operation aborted"); break;
#endif
	case WSA_QOS_ADMISSION_FAILURE: szWSAError = __T("(WSA_QOS_ADMISSION_FAILURE) qos admission error"); break;
	case WSA_QOS_BAD_OBJECT: szWSAError = __T("(WSA_QOS_BAD_OBJECT) qos bad object"); break;
	case WSA_QOS_BAD_STYLE: szWSAError = __T("(WSA_QOS_BAD_STYLE) qos bad style"); break;
	case WSA_QOS_EFILTERCOUNT: szWSAError = __T("(WSA_QOS_EFILTERCOUNT) incorrect qos filter count"); break;
	case WSA_QOS_EFILTERSTYLE: szWSAError = __T("(WSA_QOS_EFILTERSTYLE) invalid qos filter style"); break;
	case WSA_QOS_EFILTERTYPE: szWSAError = __T("(WSA_QOS_EFILTERTYPE) invalid qos filter type"); break;
	case WSA_QOS_EFLOWCOUNT: szWSAError = __T("(WSA_QOS_EFLOWCOUNT) incorrect qos flow count"); break;
	case WSA_QOS_EFLOWDESC: szWSAError = __T("(WSA_QOS_EFLOWDESC) invalid qos flow descriptor"); break;
	case WSA_QOS_EFLOWSPEC: szWSAError = __T("(WSA_QOS_EFLOWSPEC) qos flowspec error"); break;
	case WSA_QOS_EOBJLENGTH: szWSAError = __T("(WSA_QOS_EOBJLENGTH) invalid qos object length"); break;
	case WSA_QOS_EPOLICYOBJ: szWSAError = __T("(WSA_QOS_EPOLICYOBJ) invalid qos policy object"); break;
	case WSA_QOS_EPROVSPECBUF: szWSAError = __T("(WSA_QOS_EPROVSPECBUF) invalid qos provider buffer"); break;
	case WSA_QOS_EPSFILTERSPEC: szWSAError = __T("(WSA_QOS_EPSFILTERSPEC) invalid qos provider-specific filterspec"); break;
	case WSA_QOS_EPSFLOWSPEC: szWSAError = __T("(WSA_QOS_EPSFLOWSPEC) invalid qos provider-specific flowspec"); break;
	case WSA_QOS_ESDMODEOBJ: szWSAError = __T("(WSA_QOS_ESDMODEOBJ) invalid qos shape discard mode object"); break;
	case WSA_QOS_ESERVICETYPE: szWSAError = __T("(WSA_QOS_ESERVICETYPE) qos service type error"); break;
	case WSA_QOS_ESHAPERATEOBJ: szWSAError = __T("(WSA_QOS_ESHAPERATEOBJ) invalid qos shaping rate object"); break;
	case WSA_QOS_EUNKOWNPSOBJ: szWSAError = __T("(WSA_QOS_EUNKOWNPSOBJ) unrecognized qos object"); break;
	case WSA_QOS_GENERIC_ERROR: szWSAError = __T("(WSA_QOS_GENERIC_ERROR) qos generic error"); break;
	case WSA_QOS_NO_RECEIVERS: szWSAError = __T("(WSA_QOS_NO_RECEIVERS) qos no receivers"); break;
	case WSA_QOS_NO_SENDERS: szWSAError = __T("(WSA_QOS_NO_SENDERS) no qos senders"); break;
	case WSA_QOS_POLICY_FAILURE: szWSAError = __T("(WSA_QOS_POLICY_FAILURE) qos policy failure"); break;
	case WSA_QOS_RECEIVERS: szWSAError = __T("(WSA_QOS_RECEIVERS) qos receivers"); break;
	case WSA_QOS_REQUEST_CONFIRMED: szWSAError = __T("(WSA_QOS_REQUEST_CONFIRMED) qos request confirmed"); break;
	case WSA_QOS_RESERVED_PETYPE: szWSAError = __T("(WSA_QOS_RESERVED_PETYPE) reserved policy qos element type"); break;
	case WSA_QOS_SENDERS: szWSAError = __T("(WSA_QOS_SENDERS) qos senders"); break;
	case WSA_QOS_TRAFFIC_CTRL_ERROR: szWSAError = __T("(WSA_QOS_TRAFFIC_CTRL_ERROR) qos traffic control error"); break;
	case WSAEACCES: szWSAError = __T("(WSAEACCES) permission denied"); break;
	case WSAEADDRINUSE: szWSAError = __T("(WSAEADDRINUSE) address already in use"); break;
	case WSAEADDRNOTAVAIL: szWSAError = __T("(WSAEADDRNOTAVAIL) cannot assign requested address"); break;
	case WSAEAFNOSUPPORT: szWSAError = __T("(WSAEAFNOSUPPORT) address family not supported by protocol family"); break;
	case WSAEALREADY: szWSAError = __T("(WSAEALREADY) operation already in progress"); break;
	case WSAEBADF: szWSAError = __T("(WSAEBADF) file handle is not valid"); break;
	case WSAECANCELLED: szWSAError = __T("(WSAECANCELLED) call has been canceled"); break;
	case WSAECONNABORTED: szWSAError = __T("(WSAECONNABORTED) software caused connection abort"); break;
	case WSAECONNREFUSED: szWSAError = __T("(WSAECONNREFUSED) connection refused"); break;
	case WSAECONNRESET: szWSAError = __T("(WSAECONNRESET) connection reset by peer"); break;
	case WSAEDESTADDRREQ: szWSAError = __T("(WSAEDESTADDRREQ) destination address required"); break;
	case WSAEDISCON: szWSAError = __T("(WSAEDISCON) graceful shutdown in progress"); break;
	case WSAEDQUOT: szWSAError = __T("(WSAEDQUOT) disk quota exceeded"); break;
	case WSAEFAULT: szWSAError = __T("(WSAEFAULT) bad address"); break;
	case WSAEHOSTDOWN: szWSAError = __T("(WSAEHOSTDOWN) host is down"); break;
	case WSAEHOSTUNREACH: szWSAError = __T("(WSAEHOSTUNREACH) no route to host"); break;
	case WSAEINPROGRESS: szWSAError = __T("(WSAEINPROGRESS) operation now in progress"); break;
	case WSAEINTR: szWSAError = __T("(WSAEINTR) interrupted function call"); break;
	case WSAEINVAL: szWSAError = __T("(WSAEINVAL) invalid argument"); break;
	case WSAEINVALIDPROCTABLE: szWSAError = __T("(WSAEINVALIDPROCTABLE) procedure call table is invalid"); break;
	case WSAEINVALIDPROVIDER: szWSAError = __T("(WSAEINVALIDPROVIDER) service provider is invalid"); break;
	case WSAEISCONN: szWSAError = __T("(WSAEISCONN) socket is already connected"); break;
	case WSAELOOP: szWSAError = __T("(WSAELOOP) cannot translate name"); break;
	case WSAEMFILE: szWSAError = __T("(WSAEMFILE) too many open files"); break;
	case WSAEMSGSIZE: szWSAError = __T("(WSAEMSGSIZE) message too long"); break;
	case WSAENAMETOOLONG: szWSAError = __T("(WSAENAMETOOLONG) name too long"); break;
	case WSAENETDOWN: szWSAError = __T("(WSAENETDOWN) network is down"); break;
	case WSAENETRESET: szWSAError = __T("(WSAENETRESET) network dropped connection on reset"); break;
	case WSAENETUNREACH: szWSAError = __T("(WSAENETUNREACH) network is unreachable"); break;
	case WSAENOBUFS: szWSAError = __T("(WSAENOBUFS) no buffer space available"); break;
	case WSAENOMORE: szWSAError = __T("(WSAENOMORE) no more results"); break;
	case WSAENOPROTOOPT: szWSAError = __T("(WSAENOPROTOOPT) bad protocol option"); break;
	case WSAENOTCONN: szWSAError = __T("(WSAENOTCONN) socket is not connected"); break;
	case WSAENOTEMPTY: szWSAError = __T("(WSAENOTEMPTY) directory not empty"); break;
	case WSAENOTSOCK: szWSAError = __T("(WSAENOTSOCK) socket operation on nonsocket"); break;
	case WSAEOPNOTSUPP: szWSAError = __T("(WSAEOPNOTSUPP) operation not supported"); break;
	case WSAEPFNOSUPPORT: szWSAError = __T("(WSAEPFNOSUPPORT) protocol family not supported"); break;
	case WSAEPROCLIM: szWSAError = __T("(WSAEPROCLIM) too many processes"); break;
	case WSAEPROTONOSUPPORT: szWSAError = __T("(WSAEPROTONOSUPPORT) protocol not supported"); break;
	case WSAEPROTOTYPE: szWSAError = __T("(WSAEPROTOTYPE) protocol wrong type for socket"); break;
	case WSAEPROVIDERFAILEDINIT: szWSAError = __T("(WSAEPROVIDERFAILEDINIT) service provider failed to initialize"); break;
	case WSAEREFUSED: szWSAError = __T("(WSAEREFUSED) database query was refused"); break;
	case WSAEREMOTE: szWSAError = __T("(WSAEREMOTE) item is remote"); break;
	case WSAESHUTDOWN: szWSAError = __T("(WSAESHUTDOWN) cannot send after socket shutdown"); break;
	case WSAESOCKTNOSUPPORT: szWSAError = __T("(WSAESOCKTNOSUPPORT) socket type not supported"); break;
	case WSAESTALE: szWSAError = __T("(WSAESTALE) stale file handle reference"); break;
	case WSAETIMEDOUT: szWSAError = __T("(WSAETIMEDOUT) connection timed out"); break;
	case WSAETOOMANYREFS: szWSAError = __T("(WSAETOOMANYREFS) too many references"); break;
	case WSAEUSERS: szWSAError = __T("(WSAEUSERS) user quota exceeded"); break;
	case WSAEWOULDBLOCK: szWSAError = __T("(WSAEWOULDBLOCK) resource temporarily unavailable"); break;
	case WSAHOST_NOT_FOUND: szWSAError = __T("(WSAHOST_NOT_FOUND) host not found"); break;
	case WSANO_DATA: szWSAError = __T("(WSANO_DATA) valid name, no data record of requested type"); break;
	case WSANO_RECOVERY: szWSAError = __T("(WSANO_RECOVERY) this is a nonrecoverable error"); break;
	case WSANOTINITIALISED: szWSAError = __T("(WSANOTINITIALISED) successful case wsastartup not yet performed"); break;
	case WSASERVICE_NOT_FOUND: szWSAError = __T("(WSASERVICE_NOT_FOUND) service not found"); break;
	case WSASYSCALLFAILURE: szWSAError = __T("(WSASYSCALLFAILURE) system call failure"); break;
	case WSASYSNOTREADY: szWSAError = __T("(WSASYSNOTREADY) network subsystem is unavailable"); break;
	case WSATRY_AGAIN: szWSAError = __T("(WSATRY_AGAIN) nonauthoritative host not found"); break;
	case WSATYPE_NOT_FOUND: szWSAError = __T("(WSATYPE_NOT_FOUND) class type not found"); break;
	case WSAVERNOTSUPPORTED: szWSAError = __T("(WSAVERNOTSUPPORTED) winsockdll version out of range"); break;
	default: szWSAError = __T("unknow error"); break;
	}//switch

	return szWSAError + __T(" (") + ntox(m_iWSAError) + __T(")");
}
//-----------------------------------------------------------------------------
_NSTD_END;
//-----------------------------------------------------------------------------