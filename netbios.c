NTSTATUS __fastcall DriverEntry(PDRIVER_OBJECT DriverObject, PCUNICODE_STRING SourceString)
{
  PCUNICODE_STRING src_string; // rbx
  PDRIVER_OBJECT driver_object; // rdi
  ULONG device_extension_size; // edx
  NTSTATUS result; // eax
  PDEVICE_OBJECT destination_string_2; // rsi
  CCHAR get_irp_stack_size; // al
  HANDLE handle_params; // rdi
  NTSTATUS zw_query_value_key_func; // ebx
  __int64 linkage_handle; // rcx
  unsigned __int8 i; // bl
  NTSTATUS result_2; // ebx
  PDEVICE_OBJECT DeviceObject; // [rsp+40h] [rbp-C0h]
  HANDLE KeyHandle; // [rsp+48h] [rbp-B8h]
  __int64 some_value; // [rsp+50h] [rbp-B0h]
  TDI_CLIENT_INTERFACE_INFO ClientInterfaceInfo; // [rsp+58h] [rbp-A8h]
  UNICODE_STRING DestinationString; // [rsp+90h] [rbp-70h]
  UNICODE_STRING ValueName; // [rsp+A0h] [rbp-60h]
  UNICODE_STRING destination_string; // [rsp+B0h] [rbp-50h]
  int KeyValueInformation; // [rsp+C0h] [rbp-40h]
  unsigned int v21; // [rsp+C8h] [rbp-38h]

  src_string = SourceString;
  DestinationString = 0i64;
  ClientInterfaceInfo.DelAddressHandlerV2 = 0i64;
  driver_object = DriverObject;
  *(_OWORD *)&ClientInterfaceInfo.MajorTdiVersion = 0i64;
  *(_OWORD *)&ClientInterfaceInfo.PnPPowerHandler = 0i64;
  *(_OWORD *)&ClientInterfaceInfo.UnBindHandler = 0i64;
  destination_string = 0i64;
  NbFspProcess = (__int64)IoGetCurrentProcess();
  RtlInitUnicodeString(&DestinationString, L"\\Device\\Netbios");
  device_extension_size = src_string->Length + 32;
  DeviceObject = 0i64;
  
  result = IoCreateDevice(driver_object, device_extension_size, &DestinationString, 0x21u, 0x100u, 0, &DeviceObject);
  if ( result >= 0 )
  {
    destination_string_2 = DeviceObject;
    DeviceObject->Flags |= 0x10u;
    get_irp_stack_size = GetIrpStackSize(src_string);
    DeviceObject->StackSize = get_irp_stack_size;
    WORD1(destination_string_2[1].DriverObject) = src_string->Length;
    destination_string_2[1].NextDevice = (PDEVICE_OBJECT)((char *)destination_string_2 + 368);
    RtlCopyUnicodeString((PUNICODE_STRING)&destination_string_2[1].DriverObject, src_string);
    driver_object->MajorFunction[0] = (PDRIVER_DISPATCH)NbDispatch;
    driver_object->MajorFunction[2] = (PDRIVER_DISPATCH)NbDispatch;
    driver_object->MajorFunction[18] = (PDRIVER_DISPATCH)NbDispatch;
    driver_object->MajorFunction[14] = (PDRIVER_DISPATCH)NbDispatch;
    driver_object->DriverUnload = (PDRIVER_UNLOAD)NbDriverUnload;
    registry_path.Buffer = (PWSTR)ExAllocatePoolWithTag((POOL_TYPE)512, 2i64 * src_string->Length + 2, 0x6653424Eu);
    
    if ( !registry_path.Buffer )
      return 0xC0000017;
    
    registry_path.MaximumLength = 2 * (src_string->Length + 1);
    RtlCopyUnicodeString(&registry_path, src_string);
    some_value = 0i64;
    KeyHandle = 0i64;
    LODWORD(DeviceObject) = 0;
    max_lana_global = 0;
    ValueName = 0i64;
    
    if ( (int)NbOpenRegistry(&registry_path, &some_value, &KeyHandle) < 0 )
    {
      handle_params = KeyHandle;
      zw_query_value_key_func = 0xC0000001;
    }
    
    else
    {
      RtlInitUnicodeString(&ValueName, L"MaxLana");
      handle_params = KeyHandle;
      zw_query_value_key_func = ZwQueryValueKey(
                                  KeyHandle,
                                  &ValueName,
                                  KeyValueFullInformation,
                                  &KeyValueInformation,
                                  0x100u,
                                  (PULONG)&DeviceObject);
      
      if ( zw_query_value_key_func >= 0 )
      {
        if ( (_DWORD)DeviceObject )
        {
          max_lana_global = *(int *)((char *)&KeyValueInformation + v21);
          linkage_handle = some_value;
          
LABEL_7:
          NbCloseRegistry(linkage_handle, handle_params);
LABEL_8:
          
          if ( zw_query_value_key_func < 0 )
          {
            ExFreePoolWithTag(registry_path.Buffer, 0);
            return zw_query_value_key_func;
          }
          
          lana_enum = 0;
          active_device_list = ExAllocatePoolWithTag((POOL_TYPE)512, 0xFF0ui64, 0x6653424Eu);
          
          if ( active_device_list )
          {
            for ( i = 0; i <= 0xFEu; ++i )
              RtlInitUnicodeString((PUNICODE_STRING)active_device_list + i, 0i64);
            qword_1C0008368 = (__int64)&fcb_list;
            fcb_list = &fcb_list;
            ExInitializeResourceLite(&global_lock);
            qword_1C0008188 = (__int64)&wait_list;
            wait_list = (__int64)&wait_list;
            ExInitializeResourceLite(&stop_lock);
            KeInitializeEvent(&g_keAllHandlesClosed, SynchronizationEvent, 0);
            LOBYTE(destination_string_2[1].Type) = 1;
            num_opens = 0;
            net_bios_state = 2;
            ClientInterfaceInfo.TdiVersion = 2;
            _mm_storeu_si128((__m128i *)&ClientInterfaceInfo.UnBindHandler, (__m128i)0i64);
            *(_DWORD *)&ClientInterfaceInfo.Unused = 0;
            *(&ClientInterfaceInfo.Unused + 2) = 0;
            ClientInterfaceInfo.DelAddressHandlerV2 = 0i64;
            RtlInitUnicodeString(&destination_string, L"Netbios");
            ClientInterfaceInfo.ClientName = &destination_string;
            ClientInterfaceInfo.BindingHandler = (TDI_BINDING_HANDLER)&NbBindHandler;
            ClientInterfaceInfo.PnPPowerHandler = (TDI_PNP_POWER_HANDLER)NbPowerHandler;
            result = TdiRegisterPnPHandlers(&ClientInterfaceInfo, 0x38u, &bind_handle);
            result_2 = result;
            
            if ( result )
            {
              bind_handle = 0i64;
              ExDeleteResourceLite(&stop_lock);
              ExDeleteResourceLite(&global_lock);
              ExFreePoolWithTag(active_device_list, 0);
              ExFreePoolWithTag(registry_path.Buffer, 0);
              result = result_2;
              LOBYTE(destination_string_2[1].Type) = 0;
            }
            
            return result;
          }
          
          ExFreePoolWithTag(registry_path.Buffer, 0);
          return 0xC0000017;
        }
        
        zw_query_value_key_func = 0xC0000001;
      }
      
    }
    
    linkage_handle = some_value;
    if ( !some_value )
      goto LABEL_8;
    
    goto LABEL_7;
  }
  return result;
}
