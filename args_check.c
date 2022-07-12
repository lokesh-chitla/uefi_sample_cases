EFI_STATUS
EFIAPI
main (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{

    EFI_STATUS      status;
    UINTN           argc;
    CHAR16          **argv;

    status = get_args(&argc, &argv);
    if (EFI_ERROR(status)) {
       Print(L"ERROR: Parsing command line arguments: %d\n", status);
       return status;
    }

    if (argc <= 1){
        Print(L"No args passed.\n");
        return (EFI_UNSUPPORTED);  //need to have at least one parameter
    }
    
    return EFI_SUCCESS;
}
