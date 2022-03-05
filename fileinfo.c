__int64 __fastcall DriverEntry(PDRIVER_OBJECT DriverObject)
{
  
  PDRIVER_OBJECT driver_object; // rbx
  NTSTATUS start_filtering; // edi
  ULONG ulong_number; // edx
  ULONG v4; // er9
  ULONG v6; // [rsp+20h] [rbp-3E8h]
  BOOLEAN v7; // [rsp+28h] [rbp-3E0h]
  const UNICODE_STRING *v8; // [rsp+30h] [rbp-3D8h]
  const GUID *guid; // [rsp+38h] [rbp-3D0h]
  __int128 some_random_shit; // [rsp+50h] [rbp-3B8h]
  __int64 *ptr; // [rsp+60h] [rbp-3A8h]
  unsigned __int64 physical_memory_size; // [rsp+68h] [rbp-3A0h]
  UNICODE_STRING DestinationString; // [rsp+70h] [rbp-398h]
  int address; // [rsp+80h] [rbp-388h]
  int v15; // [rsp+84h] [rbp-384h]
  int *v16; // [rsp+88h] [rbp-380h]
  char *v17; // [rsp+90h] [rbp-378h]
  __int64 (__fastcall *unload_FI)(_QWORD); // [rsp+98h] [rbp-370h]
  __int64 v19; // [rsp+A0h] [rbp-368h]
  __int64 v20; // [rsp+A8h] [rbp-360h]
  __int64 v21; // [rsp+B0h] [rbp-358h]
  __int64 v22; // [rsp+B8h] [rbp-350h]
  __int64 v23; // [rsp+C0h] [rbp-348h]
  __int64 v24; // [rsp+C8h] [rbp-340h]
  __int128 v25; // [rsp+D0h] [rbp-338h]
  __int128 v26; // [rsp+E0h] [rbp-328h]
  char v27; // [rsp+F0h] [rbp-318h]
  int v28; // [rsp+F4h] [rbp-314h]
  __int64 (__fastcall *v29)(); // [rsp+F8h] [rbp-310h]
  __int64 (__fastcall *v30)(); // [rsp+100h] [rbp-308h]
  __int64 v31; // [rsp+108h] [rbp-300h]
  char v32; // [rsp+110h] [rbp-2F8h]
  int v33; // [rsp+114h] [rbp-2F4h]
  __int64 (__fastcall *v34)(); // [rsp+118h] [rbp-2F0h]
  __int64 (__fastcall *v35)(); // [rsp+120h] [rbp-2E8h]
  __int64 v36; // [rsp+128h] [rbp-2E0h]
  char v37; // [rsp+130h] [rbp-2D8h]
  int v38; // [rsp+134h] [rbp-2D4h]
  __int64 (__fastcall *v39)(); // [rsp+138h] [rbp-2D0h]
  __int64 (__fastcall *v40)(); // [rsp+140h] [rbp-2C8h]
  __int64 v41; // [rsp+148h] [rbp-2C0h]
  char v42; // [rsp+150h] [rbp-2B8h]
  int v43; // [rsp+154h] [rbp-2B4h]
  __int64 (__fastcall *v44)(); // [rsp+158h] [rbp-2B0h]
  __int64 (__fastcall *v45)(); // [rsp+160h] [rbp-2A8h]
  __int64 v46; // [rsp+168h] [rbp-2A0h]
  char v47; // [rsp+170h] [rbp-298h]
  int v48; // [rsp+174h] [rbp-294h]
  __int64 (__fastcall *v49)(); // [rsp+178h] [rbp-290h]
  __int64 (__fastcall *v50)(); // [rsp+180h] [rbp-288h]
  __int64 v51; // [rsp+188h] [rbp-280h]
  char v52; // [rsp+190h] [rbp-278h]
  int v53; // [rsp+194h] [rbp-274h]
  __int64 (__fastcall *v54)(); // [rsp+198h] [rbp-270h]
  __int64 (__fastcall *v55)(); // [rsp+1A0h] [rbp-268h]
  __int64 v56; // [rsp+1A8h] [rbp-260h]
  char v57; // [rsp+1B0h] [rbp-258h]
  int v58; // [rsp+1B4h] [rbp-254h]
  __int64 (__fastcall *v59)(); // [rsp+1B8h] [rbp-250h]
  __int64 (__fastcall *v60)(); // [rsp+1C0h] [rbp-248h]
  __int64 v61; // [rsp+1C8h] [rbp-240h]
  char v62; // [rsp+1D0h] [rbp-238h]
  int v63; // [rsp+1D4h] [rbp-234h]
  __int64 (__fastcall *v64)(); // [rsp+1D8h] [rbp-230h]
  __int64 (__fastcall *v65)(); // [rsp+1E0h] [rbp-228h]
  __int64 v66; // [rsp+1E8h] [rbp-220h]
  char v67; // [rsp+1F0h] [rbp-218h]
  int v68; // [rsp+1F4h] [rbp-214h]
  __int64 (__fastcall *v69)(); // [rsp+1F8h] [rbp-210h]
  __int64 (__fastcall *v70)(); // [rsp+200h] [rbp-208h]
  __int64 v71; // [rsp+208h] [rbp-200h]
  char v72; // [rsp+210h] [rbp-1F8h]
  int v73; // [rsp+214h] [rbp-1F4h]
  __int64 (__fastcall *v74)(); // [rsp+218h] [rbp-1F0h]
  __int64 (__fastcall *v75)(); // [rsp+220h] [rbp-1E8h]
  __int64 v76; // [rsp+228h] [rbp-1E0h]
  char v77; // [rsp+230h] [rbp-1D8h]
  int v78; // [rsp+234h] [rbp-1D4h]
  __int64 (__fastcall *v79)(); // [rsp+238h] [rbp-1D0h]
  __int64 (__fastcall *v80)(); // [rsp+240h] [rbp-1C8h]
  __int64 v81; // [rsp+248h] [rbp-1C0h]
  char v82; // [rsp+250h] [rbp-1B8h]
  int v83; // [rsp+254h] [rbp-1B4h]
  __int64 (__fastcall *v84)(); // [rsp+258h] [rbp-1B0h]
  __int64 (__fastcall *v85)(); // [rsp+260h] [rbp-1A8h]
  __int64 v86; // [rsp+268h] [rbp-1A0h]
  char v87; // [rsp+270h] [rbp-198h]
  int v88; // [rsp+274h] [rbp-194h]
  __int64 (__fastcall *v89)(); // [rsp+278h] [rbp-190h]
  __int64 (__fastcall *v90)(); // [rsp+280h] [rbp-188h]
  __int64 v91; // [rsp+288h] [rbp-180h]
  char v92; // [rsp+290h] [rbp-178h]
  int v93; // [rsp+294h] [rbp-174h]
  __int64 (__fastcall *v94)(); // [rsp+298h] [rbp-170h]
  __int64 (__fastcall *v95)(); // [rsp+2A0h] [rbp-168h]
  __int64 v96; // [rsp+2A8h] [rbp-160h]
  char v97; // [rsp+2B0h] [rbp-158h]
  int v98; // [rsp+2B4h] [rbp-154h]
  __int64 (__fastcall *v99)(); // [rsp+2B8h] [rbp-150h]
  __int64 (__fastcall *v100)(); // [rsp+2C0h] [rbp-148h]
  __int64 v101; // [rsp+2C8h] [rbp-140h]
  char v102; // [rsp+2D0h] [rbp-138h]
  int v103; // [rsp+2D4h] [rbp-134h]
  __int64 (__fastcall *v104)(); // [rsp+2D8h] [rbp-130h]
  __int64 (__fastcall *v105)(); // [rsp+2E0h] [rbp-128h]
  __int64 v106; // [rsp+2E8h] [rbp-120h]
  char v107; // [rsp+2F0h] [rbp-118h]
  int v108; // [rsp+2F4h] [rbp-114h]
  __int64 (__fastcall *v109)(); // [rsp+2F8h] [rbp-110h]
  __int64 (__fastcall *v110)(); // [rsp+300h] [rbp-108h]
  __int64 v111; // [rsp+308h] [rbp-100h]
  char v112; // [rsp+310h] [rbp-F8h]
  __int128 v113; // [rsp+314h] [rbp-F4h]
  __int64 v114; // [rsp+324h] [rbp-E4h]
  int v115; // [rsp+32Ch] [rbp-DCh]
  int v116; // [rsp+330h] [rbp-D8h]
  __int64 (__fastcall *v117)(); // [rsp+338h] [rbp-D0h]
  __int64 v118; // [rsp+340h] [rbp-C8h]
  int v119; // [rsp+348h] [rbp-C0h]
  __int128 v120; // [rsp+350h] [rbp-B8h]
  __int64 v121; // [rsp+360h] [rbp-A8h]
  int v122; // [rsp+368h] [rbp-A0h]
  __int64 (__fastcall *v123)(); // [rsp+370h] [rbp-98h]
  __int64 v124; // [rsp+378h] [rbp-90h]
  int v125; // [rsp+380h] [rbp-88h]
  __int128 v126; // [rsp+388h] [rbp-80h]
  __int64 v127; // [rsp+398h] [rbp-70h]
  __int16 v128; // [rsp+3A0h] [rbp-68h]
  __int128 v129; // [rsp+3A2h] [rbp-66h]
  __int128 v130; // [rsp+3B2h] [rbp-56h]
  __int128 v131; // [rsp+3C2h] [rbp-46h]
  int v132; // [rsp+3D2h] [rbp-36h]
  __int16 v133; // [rsp+3D6h] [rbp-32h]

  ptr = 0i64;
  v27 = 0;
  driver_object = DriverObject;
  v28 = 0;
  v29 = FIPreCreateCallback;
  physical_memory_size = 0i64;
  v30 = FIPostCreateCallback;
  v31 = 0i64;
  v32 = 18;
  v33 = 0;
  v34 = FIPreCleanupCallback;
  v35 = FIPostCleanupCallback;
  v36 = 0i64;
  v37 = 2;
  v38 = 0;
  v39 = FIPreCloseCallback;
  v41 = 0i64;
  v40 = FIPostOperationCommonCallback;
  v42 = 3;
  v43 = 0;
  v46 = 0i64;
  v44 = FIPreReadWriteCallback;
  v45 = FIPostReadWriteCallback;
  v47 = 4;
  v48 = 0;
  v51 = 0i64;
  v49 = FIPreReadWriteCallback;
  v50 = FIPostReadWriteCallback;
  v52 = 6;
  v53 = 0;
  v54 = FIPreSetInformationCallback;
  v55 = FIPostSetInformationCallback;
  v56 = 0i64;
  v57 = 13;
  v58 = 0;
  v59 = FIPreFSControlCallback;
  v60 = FIPostFSControlCallback;
  v61 = 0i64;
  v62 = 9;
  v63 = 0;
  v64 = FIPreFlushBuffersCallback;
  v66 = 0i64;
  v65 = FIPostOperationCommonCallback;
  v67 = 12;
  v68 = 0;
  v69 = FIPreDirectoryControlCallback;
  v71 = 0i64;
  v70 = FIPostOperationCommonCallback;
  v72 = 5;
  v73 = 0;
  v74 = FIPreQueryInformationCallback;
  DestinationString = 0i64;
  v75 = FIPostOperationCommonCallback;
  some_random_shit = 0i64;
  v118 = 80i64;
  v76 = 0i64;
  v77 = 27;
  v78 = 0;
  v79 = FIPrePnpCallback;
  v80 = FIPostPnpCallback;
  v81 = 0i64;
  v82 = -15;
  v83 = 0;
  v84 = FIPreMdlOperationCallback;
  v85 = FIPostOperationCommonCallback;
  v86 = 0i64;
  v87 = -18;
  v88 = 0;
  v89 = FIPreMdlOperationCallback;
  v90 = FIPostOperationCommonCallback;
  v91 = 0i64;
  v92 = 21;
  v93 = 0;
  v94 = FIPreSetSecurityCallback;
  v95 = FIPostOperationCommonCallback;
  v96 = 0i64;
  v97 = 20;
  v98 = 0;
  v99 = FIPreQuerySecurityCallback;
  v100 = FIPostOperationCommonCallback;
  v101 = 0i64;
  v102 = 8;
  v103 = 0;
  v104 = FIPreSetEACallback;
  v105 = FIPostOperationCommonCallback;
  v106 = 0i64;
  v107 = 7;
  v108 = 0;
  v109 = FIPreQueryEACallback;
  v110 = FIPostOperationCommonCallback;
  v111 = 0i64;
  v116 = 8;
  v112 = -128;
  v113 = 0i64;
  v114 = 0i64;
  v115 = 0;
  v117 = FIStreamCleanup;
  v119 = 1935886662;
  v120 = 0i64;
  v121 = 0i64;
  v123 = FIVolumeCleanup;
  v122 = 2;
  v124 = 672i64;
  v125 = 1986218310;
  v127 = 0i64;
  v128 = -1;
  v132 = 0;
  v133 = 0;
  v126 = 0i64;
  address = 0x2030070;
  v129 = 0i64;
  v15 = 4;
  v130 = 0i64;
  v131 = 0i64;
  v16 = &v116;
  v19 = 0i64;
  v17 = &v27;
  v20 = 0i64;
  unload_FI = FIUnload;
  v21 = 0i64;
  v22 = 0i64;
  v23 = 0i64;
  v24 = 0i64;
  v25 = 0i64;
  v26 = 0i64;
  
  memset(&FIGlobals, 0, 0x800ui64);
  
  qword_1C0007450 = 0i64;
  qword_1C00072D8 = (__int64)&qword_1C00072D0;
  qword_1C00072D0 = (__int64)&qword_1C00072D0;
  FIPfOpenAttemptsInitialize(&unk_1C0007458);
  FIPfOpenAttemptsInitialize(&qword_1C0007488);
  qword_1C00074B8 = 0i64;
  qword_1C00074C8 = (__int64)&qword_1C00074C0;
  qword_1C00074C0 = (__int64)&qword_1C00074C0;
  qword_1C00076A0 = 0i64;
  qword_1C00076B0 = (__int64)&qword_1C00076A8;
  qword_1C00076A8 = (__int64)&qword_1C00076A8;
  qword_1C0007588 = 0i64;
  dword_1C0007590 = 0;
  qword_1C0007598 = (__int64)&converted_dword_address;
  dword_1C0007594 = 1024;
  
  if ( &qword_1C00076A0 >= (__int64 *)&converted_dword_address ? 32 : 0 )
    memset64(
      &converted_dword_address,
      (unsigned __int64)&dword_1C0007590 + 1,
      &qword_1C00076A0 >= (__int64 *)&converted_dword_address ? 32 : 0);
  
  qword_1C0007A18 = (__int64)&unk_1C0007A20;
  InitializeSListHead(&SListHead);
  qword_1C0007A90 = 0i64;
  qword_1C00079C8 = 0i64;
  
  driver_object->MajorFunction[0] = (PDRIVER_DISPATCH)&FIControlDispatch;
  driver_object->MajorFunction[18] = (PDRIVER_DISPATCH)&FIControlDispatch;
  driver_object->MajorFunction[2] = (PDRIVER_DISPATCH)&FIControlDispatch;
  driver_object->MajorFunction[14] = (PDRIVER_DISPATCH)&FIControlDispatch;
  driver_object->MajorFunction[23] = (PDRIVER_DISPATCH)&FIControlDispatch;
  start_filtering = FIGetRegistryParameters(&dword_1C0007310);
  
  if ( start_filtering < 0 )
    goto LABEL_22;
  
  start_filtering = FIQueryPhysicalMemorySize(&physical_memory_size);
  if ( start_filtering < 0 )
    goto LABEL_22;
  
  if ( physical_memory_size >= 0x3E800000 )
    FIFileInfoStateChange(1i64);
  
  KeInitializeSemaphore(&Semaphore, Count, Count);
  RtlInitUnicodeString(&DestinationString, L"\\Device\\FileInfo");
  start_filtering = WdmlibIoCreateDeviceSecure(
                      driver_object,
                      ulong_number,
                      &DestinationString,
                      v4,
                      v6,
                      v7,
                      v8,
                      guid,
                      &DeviceObject);
  
  if ( start_filtering < 0 )
    goto LABEL_22;
  
  start_filtering = IoWMIRegistrationControl(DeviceObject, 0x410001u);
  
  if ( start_filtering < 0 )
    goto LABEL_22;
  some_dword |= 4u;
  
  if ( (int)EtwRegister(&FileInfoEventProvider, FIEtwEnableCallback, '\0', &nullcharacter) < 0 )
    nullcharacter = 0i64;
  
  start_filtering = FltRegisterFilter(driver_object, &address, &FIGlobals);
  if ( start_filtering < 0 )
    goto LABEL_22;
  
  FltInitExtraCreateParameterLookasideList(FIGlobals, &unk_1C0007500, '\0', '\x10', 'pcIF');
  some_dword |= 1u;
  
  DWORD1(some_random_shit) = 12;
  _mm_storeu_si128((__m128i *)((char *)&some_random_shit + 8), (__m128i)0i64);
  
  LODWORD(some_random_shit) = 15;
  DWORD2(some_random_shit) = _mm_cvtsi128_si32((__m128i)0i64) | 8;
  
  if ( (int)PfFileInfoNotify(&some_random_shit) < 0 )
    FIPfDisableUntilTickMsSet(&qword_1C00074D8, (unsigned int)dword_1C0007314, &qword_1C0007450);
  
  *((_QWORD *)&some_random_shit + 1) = 8i64;
  ptr = &interface_open;
  interface_open = (__int64)FIPfInterfaceOpen;
  interface_close = (__int64)FIPfInterfaceClose;
  interface_query_file = (__int64)FIPfInterfaceQueryFile;
  interface_query_volume = (__int64)FIPfInterfaceQueryVolume;
  registe_global_block_notify = (__int64)FIPfRegisterGlobalBlockNotify;
  *(_QWORD *)&some_random_shit = 42949672975i64;
  
  if ( (int)PfFileInfoNotify(&some_random_shit) >= 0 )
    some_dword |= 2u;
  
  start_filtering = FltStartFiltering(FIGlobals);
  if ( start_filtering < 0 )
LABEL_22:
    FIUnload(1i64);
  
  else
    start_filtering = 0;
  return (unsigned int)start_filtering;
}
