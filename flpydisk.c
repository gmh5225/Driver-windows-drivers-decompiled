NTSTATUS __stdcall GsDriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
  PDRIVER_OBJECT driver_object; // rdi

  driver_object = DriverObject;
  _security_init_cookie();
  return DriverEntry(driver_object);
}


__int64 __fastcall DriverEntry(_QWORD *argc1)
{
  struct _KEVENT *allocate_pool; // rax

  argc1[14] = &FloppyCreateClose;
  argc1[16] = &FloppyCreateClose;
  argc1[17] = &FloppyReadWrite;
  argc1[18] = &FloppyReadWrite;
  argc1[28] = &FloppyDeviceControl;
  argc1[41] = FloppyPnp;
  argc1[36] = &FloppyPower;
  argc1[37] = FloppySystemControl;
  argc1[13] = FloppyUnload;
  *(_QWORD *)(argc1[6] + 8i64) = FloppyAddDevice;
  allocate_pool = (struct _KEVENT *)ExAllocatePoolWithTag((POOL_TYPE)512, 0x38ui64, 0x706F6C46u);
  PagingMutex = allocate_pool;
  
  if ( !allocate_pool )
    return 0xC000009Ai64;
  
  allocate_pool->Header.WaitListHead.Flink = 0i64;
  LODWORD(allocate_pool->Header.WaitListHead.Blink) = 0;
  allocate_pool->Header.Lock = 1;
  KeInitializeEvent(allocate_pool + 1, SynchronizationEvent, 0);
  MmPageEntireDriver(DriverEntry);
  DriveMediaLimits = (__int64)&DriveMediaLimits;
  DriveMediaConstants = (__int64)&DriveMediaConstants;
  
  return 0i64;
}
