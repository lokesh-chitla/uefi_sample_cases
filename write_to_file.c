
#include <Uefi.h>

#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DevicePathLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/ShellLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/PrintLib.h>
#include <Protocol/BlockIO.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/SimpleFileSystem.h>
#include <Protocol/DellPrebootProto.h>
#include <Protocol/DellPrebootProto.h>
#include <Protocol/BlockIO.h>
#include <Protocol/DevicePath.h>
#include <Protocol/NvmExpressPassthru.h>
#include <IndustryStandard/Nvme.h>
#include <string.h>

#if 0
typedef UINTN           RETURN_STATUS;
typedef RETURN_STATUS   EFI_STATUS;
typedef struct {
    UINT32  Data1;
    UINT16  Data2;
    UINT16  Data3;
    UINT8   Data4[8];
} GUID;
typedef GUID                      EFI_GUID;
typedef VOID *EFI_HANDLE;
#endif

EFI_STATUS
EFIAPI
UefiMain(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
        EFI_GUID        sfspGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
        EFI_HANDLE      *handles = NULL;
        UINTN           handleCount = 0;
        INT32           index = 0;
        UINTN           FileBuffSize = 0;
        CHAR8           *Buf = "LOGFILE\n";

        EFI_STATUS efiStatus = gBS->LocateHandleBuffer(ByProtocol,
            &sfspGuid,
            NULL,
            &handleCount,
            &handles);
        //Print(L"Line #%d .. Status %r \n", __LINE__, efiStatus);

         for (index = 0; index < (int)handleCount; index++) {

            EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *fs = NULL;
            EFI_FILE_PROTOCOL   *root       = NULL;
            EFI_FILE_PROTOCOL   *logfile    = NULL;

            efiStatus = gBS->HandleProtocol(handles[index], &sfspGuid, (void**)&fs);
            //Print(L"Line #%d .. Status %r \n", __LINE__, efiStatus);

            if (EFI_ERROR(efiStatus)) {
                continue;
            }

            efiStatus = fs->OpenVolume(fs, &root);

            if (EFI_ERROR(efiStatus)) {
                continue;
            }
            // Print(L"Line #%d .. Status %r \n", __LINE__, efiStatus);

            efiStatus = root->Open(
                root,
                &logfile,
                L"test2\\mytest123.txt",    // Can be within fs0 or fs1 ..
                EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE | EFI_FILE_MODE_READ,
                0);

            if (EFI_ERROR(efiStatus)) {
                continue;
            }

            FileBuffSize = 8;
            efiStatus = logfile->Write(logfile, &FileBuffSize, (CHAR16*)Buf);
            Print(L"Line #%d .. Status %r \n", __LINE__, efiStatus);
        
            logfile->Close(logfile);
            break;
        }

    return EFI_SUCCESS;
}
