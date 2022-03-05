__int64 __fastcall DriverEntry(__int64 a1, UNICODE_STRING *a2)
{
  
  UNICODE_STRING *argc2; // rsi
  __int64 argc1; // r14
  int load_signature_data_var; // edi
  bool equality_between_unicode; // al
  NTSTATUS create_callback; // ebx
  const WCHAR *notification_callback_str; // rdx
  __int64 some_char; // rdx
  __int64 (__fastcall *set_routine_address)(__int64 (__fastcall *)(), _QWORD); // r14
  __int64 some_value; // rdx
  NTSTATUS load_signatures; // eax
  __int64 some_attribute; // rdx
  int load_signature_data; // eax
  __int64 device; // rdx
  __int64 signature; // [rsp+30h] [rbp-79h]
  UNICODE_STRING SystemRoutineName; // [rsp+38h] [rbp-71h]
  UNICODE_STRING DestinationString; // [rsp+48h] [rbp-61h]
  UNICODE_STRING String2; // [rsp+58h] [rbp-51h]
  UNICODE_STRING String1; // [rsp+68h] [rbp-41h]
  OBJECT_ATTRIBUTES ObjectAttributes; // [rsp+78h] [rbp-31h]
  OBJECT_ATTRIBUTES object_attributes; // [rsp+A8h] [rbp-1h]
  unsigned int data; // [rsp+120h] [rbp+77h]
  HANDLE KeyHandle; // [rsp+128h] [rbp+7Fh]

  argc2 = a2;
  signature = 0i64;
  argc1 = a1;
  data = 0;
  load_signature_data_var = 2;
  if ( InitSafeBootMode )
    return 0xC000035Fi64;
  *(_QWORD *)&WPP_MAIN_CB.Type = 0i64;
  WPP_MAIN_CB.DriverObject = (_DRIVER_OBJECT *)&WPP_ThisDir_CTLGUID_MpBoot;
  WPP_MAIN_CB.Timer = (PIO_TIMER)1;
  WPP_MAIN_CB.NextDevice = 0i64;
  WPP_MAIN_CB.CurrentIrp = 0i64;
  WppLoadTracingSupport();
  WPP_MAIN_CB.CurrentIrp = 0i64;
  WppInitKm();
  KeyHandle = 0i64;
  RtlInitUnicodeString(&DestinationString, L"ElamInfo");
  ObjectAttributes.RootDirectory = 0i64;
  ObjectAttributes.Attributes = 576;
  ObjectAttributes.Length = 48;
  ObjectAttributes.ObjectName = argc2;
  _mm_storeu_si128((__m128i *)&ObjectAttributes.SecurityDescriptor, (__m128i)0i64);
  
  if ( ZwOpenKey(&KeyHandle, 0x20006u, &ObjectAttributes) >= 0 )
    ZwDeleteValueKey(KeyHandle, &DestinationString);
  
  if ( KeyHandle )
    ZwClose(KeyHandle);
  
  memset(&MpEbGlobals, 0, 0xB0ui64);
  dword_1C0004080 = 0x28EB01;
  qword_1C0004098 = (__int64)&qword_1C0004090;
  qword_1C0004090 = (__int64)&qword_1C0004090;
  InitializeSListHead(&SListHead);
  
  if ( (int)MpEbGetFinalPathComponent(argc2, &String2) >= 0 )
  {
    RtlInitUnicodeString(&String1, L"WdBoot");
    equality_between_unicode = RtlEqualUnicodeString(&String1, &String2, 1u) != 0;
  }
  
  else
  {
    equality_between_unicode = 0;
  }
  
  unicode_is_equal = equality_between_unicode;
  test_mode_enabled = MpEbIsTestModeEnabled();
  MpEbGlobals.Buffer = (PWSTR)ExAllocatePoolWithTag(PagedPool, argc2->Length, 0x74734245u);
  
  if ( !MpEbGlobals.Buffer )
  {
    create_callback = 0xC000009A;
    if ( WPP_GLOBAL_Control != (PDEVICE_OBJECT)&WPP_GLOBAL_Control && HIDWORD(WPP_GLOBAL_Control->Timer) & 1 )
      WPP_SF_qL(WPP_GLOBAL_Control->AttachedDevice, '\n', &WPP_trace_guids, __readgsqword(0x188u), 0xC000009A);
    
    goto LABEL_70;
  }
  
  MpEbGlobals.Length = argc2->Length;
  MpEbGlobals.MaximumLength = argc2->Length;
  RtlCopyUnicodeString(&MpEbGlobals, argc2);
  notification_callback_str = L"\\Callback\\WdEbNotificationCallback";
  
  if ( !unicode_is_equal )
    notification_callback_str = L"\\Callback\\MpEbNotificationCallback";
  
  RtlInitUnicodeString(&SystemRoutineName, notification_callback_str);
  object_attributes.Length = 48;
  object_attributes.ObjectName = &SystemRoutineName;
  object_attributes.RootDirectory = 0i64;
  object_attributes.Attributes = 592;
  _mm_storeu_si128((__m128i *)&object_attributes.SecurityDescriptor, (__m128i)0i64);
  create_callback = ExCreateCallback((PCALLBACK_OBJECT *)&Object, &object_attributes, 1u, 1u);
  
  if ( create_callback < 0 )
  {
    if ( WPP_GLOBAL_Control != (PDEVICE_OBJECT)&WPP_GLOBAL_Control && HIDWORD(WPP_GLOBAL_Control->Timer) & 1 )
    {
      some_char = '\v';
LABEL_21:
      _mm_lfence();
      WPP_SF_qL(WPP_GLOBAL_Control->AttachedDevice, some_char, &WPP_trace_guids, __readgsqword(0x188u), create_callback);
      goto LABEL_69;
    }
    goto LABEL_69;
  }
  
  create_callback = MpEbInitModuleInformation();
  if ( create_callback >= 0 )
  {
    *(_QWORD *)(argc1 + 104) = MpEbUnload;
    RtlInitUnicodeString(&SystemRoutineName, L"IoRegisterBootDriverCallback");
    set_routine_address = (__int64 (__fastcall *)(__int64 (__fastcall *)(), _QWORD))MmGetSystemRoutineAddress(&SystemRoutineName);
    
    if ( !set_routine_address )
    {
      create_callback = -1073741637;
      if ( WPP_GLOBAL_Control == (PDEVICE_OBJECT)&WPP_GLOBAL_Control || !(HIDWORD(WPP_GLOBAL_Control->Timer) & 1) )
        goto LABEL_70;
      some_value = 13i64;
      goto LABEL_30;
    }
    
    RtlInitUnicodeString(&SystemRoutineName, L"IoUnregisterBootDriverCallback");
    qword_1C0004078 = (__int64)MmGetSystemRoutineAddress(&SystemRoutineName);
    
    if ( !qword_1C0004078 )
    {
      create_callback = -1073741637;
      if ( WPP_GLOBAL_Control == (PDEVICE_OBJECT)&WPP_GLOBAL_Control || !(HIDWORD(WPP_GLOBAL_Control->Timer) & 1) )
        goto LABEL_70;
      some_value = 14i64;
LABEL_30:
      WPP_SF_qL(WPP_GLOBAL_Control->AttachedDevice, some_value, &WPP_trace_guids, __readgsqword(0x188u), -1073741637);
      goto LABEL_70;
    }
    
    load_signatures = MpEbLoadSignatures(argc2, &signature, &data);
    create_callback = load_signatures;
    
    if ( load_signatures < 0 )
    {
      if ( load_signatures != 0xC0000034 )
      {
        if ( WPP_GLOBAL_Control != (PDEVICE_OBJECT)&WPP_GLOBAL_Control && HIDWORD(WPP_GLOBAL_Control->Timer) & 1 )
        {
          some_attribute = 15i64;
LABEL_40:
          _mm_lfence();
          WPP_SF_qL(
            WPP_GLOBAL_Control->AttachedDevice,
            some_attribute,
            &WPP_trace_guids,
            __readgsqword(392u),
            create_callback);
          goto LABEL_67;
        }
        goto LABEL_67;
      }
      create_callback = 0;
    }
    
    load_signature_data = EbLoadSignatureData(signature, data);
    load_signature_data_var = load_signature_data;
    
    if ( load_signature_data )
    {
      if ( load_signature_data == 1 )
      {
        create_callback = 0xC000A000;
        if ( WPP_GLOBAL_Control != (PDEVICE_OBJECT)&WPP_GLOBAL_Control && HIDWORD(WPP_GLOBAL_Control->Timer) & 1 )
          WPP_SF_qL(WPP_GLOBAL_Control->AttachedDevice, 16i64, &WPP_trace_guids, __readgsqword(392u), -1073700864);
        goto LABEL_67;
      }
      if ( load_signature_data == 2 )
      {
        create_callback = 0xC000009A;
        if ( WPP_GLOBAL_Control != (PDEVICE_OBJECT)&WPP_GLOBAL_Control && HIDWORD(WPP_GLOBAL_Control->Timer) & 1 )
          WPP_SF_qL(WPP_GLOBAL_Control->AttachedDevice, 0x11i64, &WPP_trace_guids, __readgsqword(392u), 0xC000009A);
        goto LABEL_67;
      }
      create_callback = 0xC0000001;
      if ( WPP_GLOBAL_Control == (PDEVICE_OBJECT)&WPP_GLOBAL_Control || !(HIDWORD(WPP_GLOBAL_Control->Timer) & 1) )
        goto LABEL_67;
      device = 0x12i64;
    }
    
    else
    {
      dword_1C0004084 = dword_1C0004128;
      dword_1C0004088 = dword_1C0004138;
      if ( dword_1C0004020 < (unsigned int)dword_1C0004024 )
      {
        create_callback = CmRegisterCallback(MpEbRegistryCallback, 0ui64, &Cookie);
        if ( create_callback < 0 )
        {
          if ( WPP_GLOBAL_Control != (PDEVICE_OBJECT)&WPP_GLOBAL_Control && HIDWORD(WPP_GLOBAL_Control->Timer) & 1 )
          {
            some_attribute = (unsigned int)(load_signature_data_var + 19);
            goto LABEL_40;
          }
          
LABEL_67:
          if ( signature )
            ExFreePoolWithTag((PVOID)(signature - 12), 0x67734245u);
          goto LABEL_69;
        }
      }
      set_routine_address_action = set_routine_address(MpEbBootDriverCallback, 0i64);
      if ( set_routine_address_action )
      {
        MpEbEnumerateModules();
        goto LABEL_67;
      }
      
      create_callback = 0xC0000001;
      if ( WPP_GLOBAL_Control == (PDEVICE_OBJECT)&WPP_GLOBAL_Control || !(HIDWORD(WPP_GLOBAL_Control->Timer) & 1) )
        goto LABEL_67;
      device = 0x14i64;
      
    }
    WPP_SF_qL(WPP_GLOBAL_Control->AttachedDevice, device, &WPP_trace_guids, __readgsqword(392u), 0xC0000001);
    goto LABEL_67;
  }
  
  if ( WPP_GLOBAL_Control != (PDEVICE_OBJECT)&WPP_GLOBAL_Control && HIDWORD(WPP_GLOBAL_Control->Timer) & 1 )
  {
    some_char = 0xCi64;
    goto LABEL_21;
  }
LABEL_69:
  
  if ( create_callback < 0 )
  {
LABEL_70:
    if ( Cookie.QuadPart )
      CmUnRegisterCallback(Cookie);
    if ( Object )
      ObfDereferenceObject(Object);
    if ( !load_signature_data_var )
    EbCleanupSignatureData();
    MpEbClearRegistryList();
    MpEbClearModuleInformation();
    if ( MpEbGlobals.Buffer )
      ExFreePoolWithTag(MpEbGlobals.Buffer, 0x74734245u);
    WppCleanupKm();
  }
  
  return (unsigned int)create_callback;
}
