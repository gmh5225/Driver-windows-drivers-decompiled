__int64 __fastcall FxDriverEntryWorker(__int64 a1, const UNICODE_STRING *a2)
{
  const UNICODE_STRING *argc2; // rsi
  __int64 argc1; // rdi
  __int64 result; // rax
  struct _WDF_BIND_INFO *v5; // rcx
  signed int fx_stub_class; // ebx
  unsigned int mainfunc; // eax
  __int64 idk; // rax

  argc2 = a2;
  argc1 = a1;
  if ( !a1 )
    return DriverEntry(0i64, a2);
  
  *(_DWORD *)&DestinationString.Length = 34078720;
  DestinationString.Buffer = (wchar_t *)&unk_1C00131C0;
  RtlCopyUnicodeString(&DestinationString, a2);
  result = WdfVersionBind(argc1, &DestinationString, &WdfBindInfo, &WdfDriverGlobals);
  
  if ( (int)result >= 0 )
  {
    
    fx_stub_class = FxStubBindClasses(v5);
    if ( fx_stub_class < 0 )
      goto LABEL_8;
    fx_stub_class = FxStubInitTypes();
    if ( fx_stub_class < 0 )
      goto LABEL_8;
    mainfunc = DriverEntry(argc1, argc2);
    fx_stub_class = mainfunc;
    
    if ( (mainfunc & 0x80000000) != 0 )
    {
      DbgPrintEx(0x4Di64, '\0', "DriverEntry failed 0x%x for driver %wZ\n", mainfunc, &DestinationString);
LABEL_8:
      FxStubDriverUnloadCommon();
      return (unsigned int)fx_stub_class;
    }
    
    if ( *(_BYTE *)(WdfDriverGlobals + 48) )
    {
      idk = qword_1C00133C8;
      if ( *(_QWORD *)(argc1 + 104) )
        idk = *(_QWORD *)(argc1 + 104);
      qword_1C00133C8 = idk;
      *(_QWORD *)(argc1 + 104) = FxStubDriverUnload;
    }
    
    result = 0i64;
  }
  return result;
}

NTSTATUS __stdcall FxDriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
  const UNICODE_STRING *registry_path; // rbx
  PDRIVER_OBJECT driver_object; // rdi

  registry_path = RegistryPath;
  driver_object = DriverObject;
  _security_init_cookie();
  return FxDriverEntryWorker((__int64)driver_object, registry_path);
}
