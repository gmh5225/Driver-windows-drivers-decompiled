__int64 __fastcall DriverEntry(_DEVICE_OBJECT *a1)
{
  unsigned int some_address; // ebx
  unsigned int some_value; // eax
  _DWORD *module_entries; // rdx
  _DEVICE_OBJECT *argc1; // rbp
  __int64 (__fastcall **start_wpp_module)(); // rdi
  unsigned int other_value; // esi
  void (*modules_exist)(void); // rax

  some_address = 0;
  some_value = 0;
  module_entries = &UxModuleEntries;
  argc1 = a1;
  do
  {
    if ( *module_entries != some_value )
    {
      some_address = 0xC0000183;
      goto LABEL_13;
    }
    ++some_value;
    module_entries += 12;
  }
  
  while ( some_value < 52 );
  UxDriverLoadState = 0;
  start_wpp_module = wpp_start_module;
  other_value = 0;
  UxDriverObject = a1;
  
  while ( 1 )
  {
    if ( *start_wpp_module )
    {
      some_address = ((__int64 (__fastcall *)(_DEVICE_OBJECT *, _DWORD *))*start_wpp_module)(a1, module_entries);
      if ( (some_address & 0x80000000) != 0 )
        break;
    }
    
    ++UxModulesInitialized;
    ++other_value;
    start_wpp_module += 6;
    
    if ( other_value >= 52 )
    {
      UxDriverLoadState = 1;
      argc1->Queue.Wcb.DeviceRoutine = (PDRIVER_CONTROL)UxDriverUnload;
      return some_address;
    }
    
  }
  
LABEL_13:
  while ( UxModulesInitialized )
  {
    modules_exist = (void (*)(void))*((_QWORD *)&UxModuleEntries + 6 * (unsigned int)--UxModulesInitialized + 2);
    if ( modules_exist )
      modules_exist();
  }
  KeFlushueuedDpcs();
  
  return some_address;
}
