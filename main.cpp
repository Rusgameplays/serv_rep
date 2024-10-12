#include <iostream>
#include "tchar.h"
#include "Windows.h"

using namespace std;

WCHAR serviceName[] = L"SolodkovService";
void WINAPI ServiceMain(DWORD argc, wchar_t** argv);

SERVICE_STATUS serviceStatus;
SERVICE_STATUS_HANDLE serviceStatusHandle;

int InstallService(wstring sn, wstring sp)
{
    SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
    if (!hSCManager)
    {
        return -1;
    }
    SC_HANDLE hService = CreateServiceW(
        hSCManager,
        sn.c_str(),
        sn.c_str(),
        SERVICE_ALL_ACCESS,
        SERVICE_WIN32_OWN_PROCESS,
        SERVICE_DEMAND_START,
        SERVICE_ERROR_NORMAL,
        sp.c_str(),
        NULL, NULL, NULL, NULL, NULL);
    if (!hService)
    {
        CloseServiceHandle(hSCManager);
        return -1;
    }
    CloseServiceHandle(hService);
    CloseServiceHandle(hSCManager);
    return 0;
}
int main(int argc, char** argv)
{
}
int wmain(int argc, wchar_t** argv)
{
    if (argc > 1)
    {
        if (wstring(argv[1]) == L"--install")
        {
            InstallService(serviceName, argv[0]);
            return 0;
        }
    }

    SERVICE_TABLE_ENTRYW ServiceTable[2] =
    {
        { serviceName, ServiceMain },
        { NULL, NULL }
    };

    if (!StartServiceCtrlDispatcherW(ServiceTable))
    {
        cerr << "StartServiceCtrlDispatcherW failed: " << GetLastError() << endl;
    }
    return 0;
}