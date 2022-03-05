__int64 __fastcall FxDllInitialize(_UNICODE_STRING *RegistryPath)
{
  unsigned int klib_init; // ebx
  void (__fastcall *get_system_routime_address)(_WDF_LDR_GLOBALS *); // rax
  unsigned int Value; // [rsp+20h] [rbp-168h]
  _UNICODE_STRING ValueName; // [rsp+28h] [rbp-160h]
  _UNICODE_STRING SystemRoutineName; // [rsp+38h] [rbp-150h]
  int version_information; // [rsp+50h] [rbp-138h]
  unsigned int Dst; // [rsp+54h] [rbp-134h]
  unsigned int v9; // [rsp+58h] [rbp-130h]

  ValueName.Buffer = L"DbgPrintOn";
  *(_QWORD *)&ValueName.Length = 0x160014i64;
  Value = 0;
  if ( alreadyExecuted )
    return '\0'; 
  
  alreadyExecuted = 1;                          
  TraceLoggingRegister_EtwRegister_2K((const _tlgProvider_t *)RegistryPath);
  memset(&Dst, 0, 0x110ui64);
  version_information = 276;
  
  if ( (int)RtlGetVersion(&version_information) >= 0 && (Dst > 6 || Dst == 6 && v9 >= 2) )
    ExDefaultNonPagedPoolType = 512;
  
  unk_1C000A2C0 = &unk_1C000A2B8;
  unk_1C000A2B8 = &unk_1C000A2B8;
  ExInitializeResourceLite(&Resource);
  if ( WdfLdrDiagnosticsValueByNameAsULONG(&ValueName, &Value) >= 0 && Value )
    WdfLdrDiags.DiagFlags |= 1;
  klib_init = AuxKlibInitialize();
  
  if ( (klib_init & 0x80000000) == 0 )
  {
    *(_QWORD *)&SystemRoutineName.Length = 1835034i64;
    SystemRoutineName.Buffer = L"RtlGetVersion";
    get_system_routime_address = (void (__fastcall *)(_WDF_LDR_GLOBALS *))MmGetSystemRoutineAddress(&SystemRoutineName);
    if ( get_system_routime_address )
    {
      get_system_routime_address(&WdfLdrGlobals);
    }
    else
    {
      *(_DWORD *)&ValueName.Length = 16777472;
      ValueName.Buffer = (wchar_t *)&unk_1C000A144;
      PsGetVersion(&major_version, &minor_version, &build_number, &ValueName);
    }
    if ( WdfLdrDiags.DiagFlags & 1 )
    {
      DbgPrint("WdfLdr: FxDllInitialize - ");
      DbgPrint("OsVersion(%d.%d)\n", major_version, minor_version);
    }
    return '\0';
  }
  if ( WdfLdrDiags.DiagFlags & 1 )
  {
    DbgPrint("WdfLdr: FxDllInitialize - ");
    DbgPrint("ERROR: AuxKlibInitialize failed with Status 0x%x\n", klib_init);
  }
  return klib_init;
}

__int64 __fastcall DriverEntry(_DRIVER_OBJECT *DriverObject, _UNICODE_STRING *RegistryPath)
{
  DriverObject->DriverUnload = WdfLdrUnload;
  return FxDllInitialize((_UNICODE_STRING *)DriverObject);
}
