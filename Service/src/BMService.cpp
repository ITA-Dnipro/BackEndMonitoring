#include "Pch.h"

#include "BMService.h"

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Wtsapi32.lib")

// We need this to test the service
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

void RunServer()
{
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        WSACleanup();
        return;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }
    
    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        closesocket(ListenSocket);
        WSACleanup();
        return;
    }

    // No longer need server socket
    closesocket(ListenSocket);

    // Receive until the peer shuts down the connection
    do {
        
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {

        // Echo the buffer back to the sender
            iSendResult = send( ClientSocket, recvbuf, iResult, 0 );
            if (iSendResult == SOCKET_ERROR) {
                closesocket(ClientSocket);
                WSACleanup();
                return;
            }
        }
        else  {
            closesocket(ClientSocket);
            WSACleanup();
            return;
        }

    } while (iResult > 0);

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        closesocket(ClientSocket);
        WSACleanup();
        return;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();
}

BMService* BMService::m_service = nullptr;

BMService::BMService(
    const CString& name,
    const CString& display_name,
    DWORD start_type,
    DWORD err_ctrl_type,
    DWORD accepted_cmds,
    const CString& depends,
    const CString& account,
    const CString& password)
  : m_name(name),
    m_display_name(display_name),
    m_start_type(start_type),
    m_error_ctrl_type(err_ctrl_type),
    m_depends(depends),
    m_account(account),
    m_password(password),
    m_status_handle(nullptr) 
{
    m_status.dwControlsAccepted = accepted_cmds;
    m_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    m_status.dwCurrentState = SERVICE_START_PENDING;
    m_status.dwWin32ExitCode = NO_ERROR;
    m_status.dwServiceSpecificExitCode = 0;
    m_status.dwCheckPoint = 0;
    m_status.dwWaitHint = 0;
}

void BMService::SetStatus(DWORD dwState, DWORD dwErrCode, DWORD dwWait)
{
    m_status.dwCurrentState = dwState;
    m_status.dwWin32ExitCode = dwErrCode;
    m_status.dwWaitHint = dwWait;

    ::SetServiceStatus(m_status_handle, &m_status);
}

DWORD WINAPI BMService::ServiceCtrlHandler(
    DWORD ctrlCode, DWORD evtType,
    void* evtData, void* /*context*/) 
{
    if (ctrlCode == SERVICE_CONTROL_STOP)
    {
        m_service->Stop();
    }

    return 0;
}

void WINAPI BMService::SvcMain(DWORD argc, TCHAR* argv[]) 
{
    assert(m_service);

    m_service->m_status_handle = ::RegisterServiceCtrlHandlerEx(
        m_service->GetName(),
        ServiceCtrlHandler, NULL);

    if (!m_service->m_status_handle)
    {
        return;
    }

    m_service->Start(argc, argv);
}

bool BMService::Run()
{
    m_service = this;

    TCHAR* name = const_cast<CString&>(m_name).GetBuffer();

    SERVICE_TABLE_ENTRY table_entry[] =
    {
        { name, SvcMain },
        { nullptr, nullptr }
    };

    return ::StartServiceCtrlDispatcher(table_entry) == TRUE;
}

const CString& BMService::GetName() const { return m_name; }
const CString& BMService::GetDisplayName() const { return m_display_name; }
const DWORD BMService::GetStartType() const { return m_start_type; }
const DWORD BMService::GetErrorControlType() const { return m_error_ctrl_type; }
const CString& BMService::GetDependencies() const { return m_depends; }
const CString& BMService::GetAccount() const { return m_account; }
const CString& BMService::GetPassword() const { return m_password; }

void BMService::OnStart(DWORD /*argc*/, TCHAR** /*argv*/)
{
    m_main_thread = std::thread(RunServer);
}

void BMService::OnStop() 
{
    m_main_thread.join();
}

void BMService::Start(DWORD argc, TCHAR* argv[])
{
    SetStatus(SERVICE_START_PENDING);
    OnStart(argc, argv);
    SetStatus(SERVICE_RUNNING);
}

void BMService::Stop() 
{
    SetStatus(SERVICE_STOP_PENDING);
    OnStop();
    SetStatus(SERVICE_STOPPED);
}
