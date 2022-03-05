__int64 __fastcall DriverEntry(__int64 arg1, const UNICODE_STRING *arg2)
{
  const UNICODE_STRING *argc2; // rdi
  __int64 argc1; // r14
  char some_shit_idk; // r15
  char registered_filter; // si
  char initialization; // bp
  __int64 v7; // rcx
  int drive_parameters; // ebx
  __int64 v9; // r8
  USHORT value; // bx
  ULONG v11; // er9
  __int64 result; // rax
  int version; // [rsp+40h] [rbp-158h]
  unsigned int Dst; // [rsp+44h] [rbp-154h]
  unsigned int v15; // [rsp+48h] [rbp-150h]

  argc2 = arg2;
  argc1 = arg1;
  some_shit_idk = 0;
  registered_filter = 0;
  initialization = 0;
  memset(&Dst, 0, '\x01\x10');
  version = '\x01\x14';
  
  if ( (int)RtlGetVersion(&version) >= 0 && (Dst > 6 || Dst == 6 && v15 >= 2) )
  {
    ExDefaultNonPagedPoolType = 512;
    ExDefaultMdlProtection = '@\0\0\0';
  }
  
  McGenEventRegister_EtwRegister();
  drive_parameters = FCReadDriverParameters(argc2);
  
  if ( drive_parameters < 0 )
    goto LABEL_16;
  value = argc2->Length + 2;
  gRegistryPath.Buffer = (PWSTR)ExAllocatePoolWithTag((POOL_TYPE)512, value, 'niCF');
  
  if ( !gRegistryPath.Buffer )
  {
    drive_parameters = '�\0\0�';
LABEL_16:
    
    if ( Microsoft_Windows_FileCryptEnableBits & 1 )
      McTemplateK0d_EtwWriteTransfer(v7, &DriverEntryFailure, v9, (unsigned int)drive_parameters);
    
    if ( some_shit_idk )
    {
      ExDeleteNPagedLookasideList(&gPre2PostIoContextList);
      ExDeleteNPagedLookasideList(&gPre2PostCreateContextList);
      ExDeleteNPagedLookasideList(&gShadowBufferList);
    }
    
    if ( gRegistryPath.Buffer )
      ExFreePoolWithTag(gRegistryPath.Buffer, 0x6E694346u);
    
    if ( initialization )
      StSecDeinitialize();
    
    if ( registered_filter )
      FltUnregisterFilter(gFilterHandle);
    
    return (unsigned int)drive_parameters;
  }
  gRegistryPath.MaximumLength = value;
  RtlCopyUnicodeString(&gRegistryPath, argc2);
  
  v11 = ExDefaultNonPagedPoolType;
  gRegistryPath.Buffer[(unsigned __int64)argc2->Length >> 1] = 0;
  ExInitializeNPagedLookasideList(&gPre2PostIoContextList, 0i64, 0i64, v11, 0x20ui64, 0x70704346u, 0);
  
  ExInitializeNPagedLookasideList(
    &gPre2PostCreateContextList,
    (PALLOCATE_FUNCTION)'\0',
    (PFREE_FUNCTION)'\0',
    ExDefaultNonPagedPoolType,
    '\x10',
    'ppCF',
    0);
  
  some_shit_idk = 1;
  
  ExInitializeNPagedLookasideList(
    &gShadowBufferList,
    (PALLOCATE_FUNCTION)'\0',
    (PFREE_FUNCTION)'\0',
    ExDefaultNonPagedPoolType,
    '\x01\0\0',
    'bsCF',
    0);
  
  if ( (unsigned __int8)FsRtlIsMobileOS() )
    callback_mobile = &CallbacksMobile;
  
  drive_parameters = FltRegisterFilter(argc1, &FilterRegistration, &gFilterHandle);
  if ( drive_parameters < 0 )
    goto LABEL_16;
  
  registered_filter = 1;
  drive_parameters = StSecInitialize();
  
  if ( drive_parameters < 0 )
    goto LABEL_16;
  
  initialization = 1;
  result = FltStartFiltering(gFilterHandle);
  drive_parameters = result;
  
  if ( (int)result < 0 )
    goto LABEL_16;
  return result;
}
