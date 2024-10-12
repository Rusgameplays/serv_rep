//
// Created by solod on 11.10.2024.
//

#include "Windows.h"

extern WCHAR serviceName[];
extern SERVICE_STATUS serviceStatus;
extern SERVICE_STATUS_HANDLE serviceStatusHandle;

DWORD WINAPI ControlHandler(DWORD dwControl, DWORD dmEventType, LPVOID lpEventData)
{
    DWORD result = ERROR_CALL_NOT_IMPLEMENTED;
    switch (dwControl)
    {
        case SERVICE_CONTROL_STOP:
            serviceStatus.dwCurrentState = SERVICE_STOPPED;
            result = NO_ERROR;
            break;
        case SERVICE_CONTROL_SHUTDOWN:
            serviceStatus.dwCurrentState = SERVICE_STOPPED;
            result = NO_ERROR;
            break;
        case SERVICE_CONTROL_INTERROGATE:
            break;
    }
    SetServiceStatus(serviceStatusHandle, &serviceStatus);
    return result;
}

void WINAPI ServiceMain(DWORD argc, wchar_t** argv)
{
    serviceStatusHandle = RegisterServiceCtrlHandlerExW(serviceName, LPHANDLER_FUNCTION_EX(ControlHandler),NULL);
    if (serviceStatusHandle == (SERVICE_STATUS_HANDLE)0)
    {
        return;
    }

    serviceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    serviceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    serviceStatus.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(serviceStatusHandle, &serviceStatus);
}