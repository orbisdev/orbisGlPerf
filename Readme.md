orbisGlPerf basic GL ES 2.0 perfomance sample for PlayStation 4
======================
 
 What does this do?
===================
 
  This is a basic sample using GL ES 2.0 and orbisGL included with liborbis: 
  
  
  https://github.com/orbisdev/liborbis
  
  Original work is rasperf3d from https://www.bigmessowires.com/2014/10/06/raspberry-pi-3d-performance-demo/
  
  It has been ported to PlayStation 4 using liborbis
  
  
  What do you need to compile it?
==================

 1) You will need ps4sdk fork branch firmware505 and liborbis from my own repository

  https://github.com/psxdev/ps4sdk/tree/firmware505
  
  Follow steps in readme
  ```
  git clone https://github.com/orbisdev/liborbis
  
  ```
  
  
 2) Compile sample
  
  
  ```
  git clone https://github.com/orbisdev/orbisGlPerf
  cd orbisGlPerf
  make
  ```
  copy bin/homebrew.elf to ps4sh/bin folder or where you are executing ps4sh binary

 3) You will need ps4sh because all is loaded from host using the last orbislinkgl.pkg look for it or make your own using code published by flatz or me 
 
 Copy content of folder assets where your homebrew.elf was copied

 4) Before execute homebrew.elf you need ps4sh running on folder where your homebrew.elf was copied. Load orbislinkgl pkg and you will see logs in your ps4sh tool
 
 After you see orbislink splash screen execute connect command on ps4sh
  
 ```
 [PS4][INFO]: debugnet initialized
 [PS4][INFO]: ready to have a lot of fun...
 [PS4][INFO]: [PS4LINK] Server request thread UID: 0x80F4C9C0
 [PS4][DEBUG]: [PS4LINK] Created ps4link_requests_sock: 7
 [PS4][INFO]: [PS4LINK] Server command thread UID: 0x80F4CE40
 [PS4][DEBUG]: [PS4LINK] bind to ps4link_requests_sock done
 [PS4][DEBUG]: [PS4LINK] Command Thread Started.
 [PS4][DEBUG]: [PS4LINK] Ready for connection 1
 [PS4][INFO]: [PS4LINK] Waiting for connection
 
 ps4sh> connect
 log: [HOST][INFO]: [PS4SH] Connecting to fio ps4link ip 192.168.1.17
 log: [HOST][INFO]: [PS4SH] PlayStation is listening at 192.168.1.17
 [PS4][DEBUG]: [PS4LINK] Created ps4link_commands_sock: 8
 [PS4][DEBUG]: [PS4LINK] Command listener waiting for commands...
 [PS4][DEBUG]: [PS4LINK] Client connected from 192.168.1.3 port: 729
 [PS4][INFO]: [PS4LINK] sock ps4link_fileio set 9 connected 1
 [PS4][DEBUG]: [ORBISLINK] Initialized and connected from pc/mac ready to receive commands
 [PS4][INFO]: [PS4LINK] Waiting for connection
 [PS4][DEBUG]: liborbispad sceUserServiceInitialize return 0x       0!
 [PS4][DEBUG]: liborbispad scePadInit return 0
 [PS4][DEBUG]: liborbispad scePadOpen return handle 0x 3220500
 [PS4][DEBUG]: [ORBISLINK] sandbox e5ni6oyUMk
 [PS4][DEBUG]: sceKernelLoadStartModule(libScePigletv2VSH.sprx) return id: 63
 [PS4][DEBUG]: sceKernelLoadStartModule(libSceShaccVSH.sprx) return id: 64
 [PS4][DEBUG]: [ORBISLINK] piglet modules loaded
 [PS4][DEBUG]: [ORBISLINK] module base=0x80000000 size=704512
 [PS4][DEBUG]: [ORBISLINK] patching module
 [PS4][DEBUG]: [ORBISLINK] piglet modules patched
 [PS4][DEBUG]: [orbisAudio] sceAudioOutInit return 0
 [PS4][DEBUG]: [orbisAudio] initialized!
 [PS4][DEBUG]: [orbisAudio] buffers 0 for audio 0 8000ec40 created
 [PS4][DEBUG]: [orbisAudio] buffers 1 for audio 0 80011040 created
 [PS4][DEBUG]: [orbisAudio] buffers for audio channel 0 created
 [PS4][DEBUG]: [orbisAudio] sceAudioOutOpen  1024 samples
 [PS4][DEBUG]: [orbisAudio] sceAudioOutOpen handle  20000007 
 [PS4][DEBUG]: [orbisAudio] audio channel 0 thread UID: 0x80F4D740 created
 [PS4][DEBUG]: orbisAudioChannelThread channel 0
 [PS4][DEBUG]: orbisAudioChannelThread channel samples 0 1024
 [PS4][DEBUG]: orbisAudioChannelThread channel samples 1 1024
 [PS4][DEBUG]: orbisAudioChannelThread buffer 0 8000ec40
 [PS4][DEBUG]: orbisAudioChannelThread buffer 1 80011040
 [PS4][DEBUG]: [orbisAudio] orbisAudioChannelThread 0  1 ready to have a lot of fun...
 [PS4][DEBUG]: [ORBISLINK] orbisAudioInitChannel return 0 
 [PS4][DEBUG]: liborbiskeyboard userID r 0x10000000
 [PS4][DEBUG]: liborbiskeyboard is initialized!
 [PS4][DEBUG]: orbisKeyboardInit 1
 [PS4][DEBUG]: liborbiskeyboard sceImeKeyboardOpen in
 [PS4][DEBUG]: liborbiskeyboard orbisKeyboardConf not null 
 [PS4][DEBUG]: liborbiskeyboard sceImeKeyboardOpen return success 0
 [PS4][DEBUG]: orbisKeyboardOpen 0
 [PS4][DEBUG]: [ORBISLINK]Loading homebrew.elf from host
 [PS4][DEBUG]: [ORBISLINK] orbisExecUserElf called
 [PS4][DEBUG]: [PS4LINK] file open req (host0:homebrew.elf, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 739768)
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 0)
 [PS4][DEBUG]: [ORBISLINK] before orbisSysMmap
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 739768 bytes to read (wanted 739768)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 0  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 1  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 2  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 3  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 4  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 5  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 6  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 7  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 8  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 9  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 10  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 11  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 12  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 13  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 14  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 15  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 16  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 17  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 18  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 19  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 20  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 21  readed 51640
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [ORBISLINK] orbisExecUserElf ready to run elf
 [PS4][DEBUG]: [ORBISLINK] orbisUserRun malloc for argument
 [PS4][DEBUG]: [ORBISLINK] orbisUserRun after malloc for argument
 [PS4][DEBUG]: [ORBISLINK] orbisUserRun after ps4MemoryProtectedCreate
 [PS4][DEBUG]: [ORBISLINK] orbisUserRun after ps4MemoryProtectedGetWritableAddress writable=2000d0000
 [PS4][DEBUG]: [ORBISLINK] orbisUserRun after ps4MemoryProtectedGetExecutableAddress executable=2000d0000
 [PS4][DEBUG]: [ORBISLINK] elfLoaderInstantiate in segments length=6
 [PS4][DEBUG]: [ORBISLINK] elfLoaderInstantiate before elfLoaderInstantiate memcpy 2000d0040 200018040 336
 [PS4][DEBUG]: [ORBISLINK] orbisMemoryCopy before memcpy
 [PS4][DEBUG]: [ORBISLINK] orbisMemoryCopy after memcpy
 [PS4][DEBUG]: [ORBISLINK] elfLoaderInstantiate after elfLoaderInstantiate memcpy
 [PS4][DEBUG]: [ORBISLINK] elfLoaderInstantiate before elfLoaderInstantiate memcpy 2000d0190 200018190 25
 [PS4][DEBUG]: [ORBISLINK] orbisMemoryCopy before memcpy
 [PS4][DEBUG]: [ORBISLINK] orbisMemoryCopy after memcpy
 [PS4][DEBUG]: [ORBISLINK] elfLoaderInstantiate after elfLoaderInstantiate memcpy
 [PS4][DEBUG]: [ORBISLINK] elfLoaderInstantiate before elfLoaderInstantiate memcpy 2000d0000 200018000 503288
 [PS4][DEBUG]: [ORBISLINK] orbisMemoryCopy before memcpy
 [PS4][DEBUG]: [ORBISLINK] orbisMemoryCopy after memcpy
 [PS4][DEBUG]: [ORBISLINK] elfLoaderInstantiate after elfLoaderInstantiate memcpy
 [PS4][DEBUG]: [ORBISLINK] elfLoaderInstantiate before elfLoaderInstantiate memcpy 20034b000 200093000 153040
 [PS4][DEBUG]: [ORBISLINK] orbisMemoryCopy before memcpy
 [PS4][DEBUG]: [ORBISLINK] orbisMemoryCopy after memcpy
 [PS4][DEBUG]: [ORBISLINK] elfLoaderInstantiate after elfLoaderInstantiate memcpy
 [PS4][DEBUG]: [ORBISLINK] elfLoaderInstantiate before elfLoaderInstantiate orbisMemorySet
 [PS4][DEBUG]: [ORBISLINK] orbisMemorySet before memset
 [PS4][DEBUG]: [ORBISLINK] orbisMemorySet after memset
 [PS4][DEBUG]: [ORBISLINK] elfLoaderInstantiate after elfLoaderInstantiate orbisMemorySet
 [PS4][DEBUG]: [ORBISLINK] elfLoaderInstantiate before elfLoaderInstantiate memcpy 20034b018 200093018 256
 [PS4][DEBUG]: [ORBISLINK] orbisMemoryCopy before memcpy
 [PS4][DEBUG]: [ORBISLINK] orbisMemoryCopy after memcpy
 [PS4][DEBUG]: [ORBISLINK] elfLoaderInstantiate after elfLoaderInstantiate memcpy
 [PS4][DEBUG]: [ORBISLINK] elfLoaderLoad  after elfLoaderInstantiate return=0
 [PS4][DEBUG]: [ORBISLINK] elfLoaderLoad after elfLoaderRelocate return=0
 [PS4][DEBUG]: [ORBISLINK] orbisUserRun after elfLoaderLoad return r=0 readable=2000d0000 executable=2000d0000
 [PS4][DEBUG]: [ORBISLINK] orbisUserRun after set argument->main 20010bca0 
 [PS4][DEBUG]: [ORBISLINK] orbisUserRun after elfDestroyAndFree 
 [PS4][DEBUG]: [ORBISLINK] New user elf thread UID: 0x80F4DBC0
 [PS4][DEBUG]: [ORBISLINK] orbisUserMain Configuration pointer 424500, pointer_conf string 424500
 [PS4][INFO]: debugnet already initialized using configuration from ps4link
 [PS4][INFO]: debugnet_initialized=1 SocketFD=6 logLevel=3
 [PS4][INFO]: ready to have a lot of fun...
 [PS4][INFO]: ps4link already initialized using configuration from ps4link
 [PS4][INFO]: ps4link_fileio_active=1
 [PS4][INFO]: ps4link_cmdsio_active=1
 [PS4][INFO]: ps4link_initialized=1
 [PS4][INFO]: ps4link_requests_port=18193
 [PS4][INFO]: ps4link_commands_port=18194
 [PS4][INFO]: ps4link_debug_port=18194
 [PS4][INFO]: ps4link_fileio_sock=9
 [PS4][INFO]: ps4link_requests_sock=7
 [PS4][INFO]: [ORBISGLPERF] let's go
 [PS4][INFO]: ps4link_commands_sock=8
 [PS4][DEBUG]: [ORBISFILE] liborbisFile initialized
 [PS4][DEBUG]: liborbisPad already initialized using configuration external
 [PS4][DEBUG]: orbispad_initialized=1
 [PS4][DEBUG]: ready to have a lot of fun...
 [PS4][DEBUG]: liborbisaudio already initialized using configuration external
 [PS4][DEBUG]: ready to have a lot of fun...
 [PS4][DEBUG]: orbisaudio_initialized=1
 [PS4][DEBUG]: liborbisKeyboard already initialized using configuration external
 [PS4][DEBUG]: orbiskeyboard_initialized=1
 [PS4][DEBUG]: ready to have a lot of fun :P ...
 [PS4][INFO]: [ORBISGL] scePigletSetConfigurationVSH success.
 [PS4][INFO]: [ORBISGL] eglGetDisplay success.
 [PS4][INFO]: [ORBISGL] EGL version major:1, minor:4
 [PS4][INFO]: [ORBISGL] eglBindAPI success.
 [PS4][INFO]: [ORBISGL] eglSwapInterval success.
 [PS4][INFO]: [ORBISGL] eglChooseConfig success.
 [PS4][INFO]: [ORBISGL] eglCreateWindowSurface success.
 [PS4][INFO]: [ORBISGL] eglCreateContext success.
 [PS4][INFO]: [ORBISGL] eglMakeCurrent success.
 [PS4][INFO]: [ORBISGL] GL_VERSION: OpenGL ES 2.0 Piglet
 [PS4][INFO]: [ORBISGL] GL_RENDERER: Piglet
 [PS4][INFO]: [ORBISGL] liborbisGl initialized
 [PS4][DEBUG]: [PS4LINK] file open req (host0:estrayk_-_xmas.mod, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 58494)
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 58494 bytes to read (wanted 58494)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 0  readed 58494
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: In play 0
 [PS4][DEBUG]: In play m_bPlaying 1
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/models/kid.dat, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 113056 bytes to read (wanted 113056)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 0  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 1  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 2  readed 47520
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 34092 bytes to read (wanted 34092)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 0  readed 34092
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/models/trex.dat, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 413280 bytes to read (wanted 413280)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 0  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 1  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 2  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 3  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 4  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 5  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 6  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 7  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 8  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 9  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 10  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 11  readed 52832
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 113640 bytes to read (wanted 113640)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 0  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 1  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 2  readed 48104
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/models/robot.dat, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 2097152 bytes to read (wanted 2097152)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 0  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 1  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 2  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 3  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 4  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 5  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 6  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 7  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 8  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 9  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 10  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 11  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 12  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 13  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 14  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 15  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 16  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 17  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 18  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 19  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 20  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 21  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 22  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 23  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 24  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 25  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 26  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 27  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 28  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 29  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 30  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 31  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 32  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 33  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 34  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 35  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 36  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 37  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 38  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 39  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 40  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 41  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 42  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 43  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 44  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 45  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 46  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 47  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 48  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 49  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 50  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 51  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 52  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 53  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 54  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 55  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 56  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 57  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 58  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 59  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 60  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 61  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 62  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 63  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 333558 bytes to read (wanted 333558)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 0  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 1  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 2  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 3  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 4  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 5  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 6  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 7  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 8  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 9  readed 38646
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/textures/cube.ktx, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 64 bytes to read (wanted 64)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 64
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 96)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 32768 bytes to read (wanted 32768)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 0  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8192 bytes to read (wanted 8192)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8192
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 2048 bytes to read (wanted 2048)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 2048
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 512 bytes to read (wanted 512)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 512
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 128 bytes to read (wanted 128)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 128
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 32 bytes to read (wanted 32)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 32
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8 bytes to read (wanted 8)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8 bytes to read (wanted 8)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8 bytes to read (wanted 8)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/textures/frog.ktx, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 64 bytes to read (wanted 64)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 64
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 96)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 65536 bytes to read (wanted 65536)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 0  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 1  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 16384 bytes to read (wanted 16384)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 16384
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4096 bytes to read (wanted 4096)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4096
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 1024 bytes to read (wanted 1024)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 1024
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 256 bytes to read (wanted 256)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 256
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 64 bytes to read (wanted 64)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 64
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 16 bytes to read (wanted 16)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 16
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8 bytes to read (wanted 8)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8 bytes to read (wanted 8)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8 bytes to read (wanted 8)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/textures/kid.ktx, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 64 bytes to read (wanted 64)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 64
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 96)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 32768 bytes to read (wanted 32768)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 0  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8192 bytes to read (wanted 8192)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8192
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 2048 bytes to read (wanted 2048)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 2048
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 512 bytes to read (wanted 512)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 512
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 128 bytes to read (wanted 128)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 128
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 32 bytes to read (wanted 32)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 32
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8 bytes to read (wanted 8)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8 bytes to read (wanted 8)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8 bytes to read (wanted 8)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/textures/trex.ktx, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 64 bytes to read (wanted 64)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 64
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 96)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 32768 bytes to read (wanted 32768)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 0  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8192 bytes to read (wanted 8192)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8192
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 2048 bytes to read (wanted 2048)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 2048
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 512 bytes to read (wanted 512)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 512
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 128 bytes to read (wanted 128)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 128
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 32 bytes to read (wanted 32)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 32
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8 bytes to read (wanted 8)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8 bytes to read (wanted 8)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8 bytes to read (wanted 8)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/textures/robot.ktx, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 64 bytes to read (wanted 64)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 64
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 96)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 131072 bytes to read (wanted 131072)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 0  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 1  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 2  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 3  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 32768 bytes to read (wanted 32768)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 0  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8192 bytes to read (wanted 8192)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8192
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 2048 bytes to read (wanted 2048)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 2048
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 512 bytes to read (wanted 512)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 512
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 128 bytes to read (wanted 128)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 128
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 32 bytes to read (wanted 32)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 32
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8 bytes to read (wanted 8)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8 bytes to read (wanted 8)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 4 bytes to read (wanted 4)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 4
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 8 bytes to read (wanted 8)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 8
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [ORBISGL] orbisGlLoadShaders host0:orbisGlPerf/shaders/phong.vertexShader host0:orbisGlPerf/shaders/phong.fragmentShader
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/shaders/phong.vertexShader, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 981)
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 981 bytes to read (wanted 981)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 981
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][ERROR]: [ORBISGL] glShaderSource failed: 0x00000502
 [PS4][DEBUG]: [ORBISGL] shader compilation shader_id=50 done
 [PS4][DEBUG]: [ORBISGL] shader compilantion no log
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/shaders/phong.fragmentShader, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 1781)
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 1781 bytes to read (wanted 1781)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 1781
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [ORBISGL] shader compilation shader_id=51 done
 [PS4][DEBUG]: [ORBISGL] shader compilantion no log
 [PS4][INFO]: [ORBISGL] link program_id=52 done
 [PS4][DEBUG]: [ORBISGL] program link no log
 [PS4][DEBUG]: [ORBISGLPERF] program 52 created for host0:orbisGlPerf/shaders/phong.vertexShader host0:orbisGlPerf/shaders/phong.fragmentShader
 [PS4][DEBUG]: [ORBISGL] orbisGlLoadShaders host0:orbisGlPerf/shaders/gouraud.vertexShader host0:orbisGlPerf/shaders/gouraud.fragmentShader
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/shaders/gouraud.vertexShader, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 2398)
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 2398 bytes to read (wanted 2398)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 2398
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [ORBISGL] shader compilation shader_id=53 done
 [PS4][DEBUG]: [ORBISGL] shader compilantion no log
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/shaders/gouraud.fragmentShader, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 246)
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 246 bytes to read (wanted 246)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 246
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [ORBISGL] shader compilation shader_id=54 done
 [PS4][DEBUG]: [ORBISGL] shader compilantion no log
 [PS4][INFO]: [ORBISGL] link program_id=55 done
 [PS4][DEBUG]: [ORBISGL] program link no log
 [PS4][DEBUG]: [ORBISGLPERF] program 55 created for host0:orbisGlPerf/shaders/gouraud.vertexShader host0:orbisGlPerf/shaders/gouraud.fragmentShader
 [PS4][DEBUG]: [ORBISGL] orbisGlLoadShaders host0:orbisGlPerf/shaders/phong.vertexShader host0:orbisGlPerf/shaders/untextured-phong.fragmentShader
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/shaders/phong.vertexShader, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 981)
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 981 bytes to read (wanted 981)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 981
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [ORBISGL] shader compilation shader_id=56 done
 [PS4][DEBUG]: [ORBISGL] shader compilantion no log
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/shaders/untextured-phong.fragmentShader, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 1684)
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 1684 bytes to read (wanted 1684)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 1684
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [ORBISGL] shader compilation shader_id=57 done
 [PS4][DEBUG]: [ORBISGL] shader compilantion no log
 [PS4][INFO]: [ORBISGL] link program_id=58 done
 [PS4][DEBUG]: [ORBISGL] program link no log
 [PS4][DEBUG]: [ORBISGLPERF] program 58 created for host0:orbisGlPerf/shaders/phong.vertexShader host0:orbisGlPerf/shaders/untextured-phong.fragmentShader
 [PS4][DEBUG]: [ORBISGL] orbisGlLoadShaders host0:orbisGlPerf/shaders/gouraud.vertexShader host0:orbisGlPerf/shaders/untextured-gouraud.fragmentShader
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/shaders/gouraud.vertexShader, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 2398)
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 2398 bytes to read (wanted 2398)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 2398
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [ORBISGL] shader compilation shader_id=59 done
 [PS4][DEBUG]: [ORBISGL] shader compilantion no log
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/shaders/untextured-gouraud.fragmentShader, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 148)
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 148 bytes to read (wanted 148)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 148
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [ORBISGL] shader compilation shader_id=60 done
 [PS4][DEBUG]: [ORBISGL] shader compilantion no log
 [PS4][INFO]: [ORBISGL] link program_id=61 done
 [PS4][DEBUG]: [ORBISGL] program link no log
 [PS4][DEBUG]: [ORBISGLPERF] program 61 created for host0:orbisGlPerf/shaders/gouraud.vertexShader host0:orbisGlPerf/shaders/untextured-gouraud.fragmentShader
 [PS4][DEBUG]: [ORBISGL] orbisGlLoadShaders host0:orbisGlPerf/shaders/flat.vertexShader host0:orbisGlPerf/shaders/flat.fragmentShader
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/shaders/flat.vertexShader, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 446)
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 446 bytes to read (wanted 446)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 446
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [ORBISGL] shader compilation shader_id=62 done
 [PS4][DEBUG]: [ORBISGL] shader compilantion no log
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/shaders/flat.fragmentShader, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 137)
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 137 bytes to read (wanted 137)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 137
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [ORBISGL] shader compilation shader_id=63 done
 [PS4][DEBUG]: [ORBISGL] shader compilantion no log
 [PS4][INFO]: [ORBISGL] link program_id=64 done
 [PS4][DEBUG]: [ORBISGL] program link no log
 [PS4][DEBUG]: [ORBISGLPERF] program 64 created for host0:orbisGlPerf/shaders/flat.vertexShader host0:orbisGlPerf/shaders/flat.fragmentShader
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/textures/atari-font.bmp, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 14 bytes to read (wanted 14)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 14
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 1132 bytes to read (wanted 1132)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 1132
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 32768 bytes to read (wanted 32768)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: chunk 0  readed 32768
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [ORBISGL] orbisGlLoadShaders host0:orbisGlPerf/shaders/text.vertexShader host0:orbisGlPerf/shaders/text.fragmentShader
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/shaders/text.vertexShader, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 495)
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 495 bytes to read (wanted 495)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 495
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [ORBISGL] shader compilation shader_id=67 done
 [PS4][DEBUG]: [ORBISGL] shader compilantion no log
 [PS4][DEBUG]: [PS4LINK] file open req (host0:orbisGlPerf/shaders/text.fragmentShader, 0 0)
 [PS4][DEBUG]: [PS4LINK] file open reply received (ret 9)
 [PS4][DEBUG]: [ORBISFILE] slot=0 fd=9
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 183)
 [PS4][DEBUG]: [PS4LINK] file lseek req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_lseek_file: lseek reply received (ret 0)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: Reply said there's 183 bytes to read (wanted 183)
 [PS4][DEBUG]: [PS4LINK] ps4link_read_file: readed 183
 [PS4][DEBUG]: [PS4LINK] ps4link_file: file close req (fd: 9)
 [PS4][DEBUG]: [PS4LINK] ps4link_close_file: close reply received (ret 0)
 [PS4][DEBUG]: [ORBISGL] shader compilation shader_id=68 done
 [PS4][DEBUG]: [ORBISGL] shader compilantion no log
 [PS4][INFO]: [ORBISGL] link program_id=69 done
 [PS4][DEBUG]: [ORBISGL] program link no log
 [PS4][DEBUG]: [ORBISGLPERF] font shader linked 69
 [PS4][DEBUG]: [ORBISGLPERF] fontScreenHalfSizeId 0
 [PS4][DEBUG]: [ORBISGLPERF] fontPositionId 0
 [PS4][DEBUG]: [ORBISGLPERF] fontUVId 1
 [PS4][DEBUG]: [ORBISGLPERF] fontSamplerId 2
 [PS4][INFO]: [ORBISGLPERF] init done 
 [PS4][INFO]: [ORBISGLPERF] tv_sec=1545674846 tv_usec=108285
 [PS4][INFO]: [ORBISGLPERF] tv_sec=1545674846 tv_usec=108299
 log: [PS4][DEBUG]: [ORBISGLPERF] showStats=1
 log: [PS4][DEBUG]: [ORBISGLPERF] shaderType=4
 log: [PS4][DEBUG]: [ORBISGLPERF] shaderType=0
 log: [PS4][DEBUG]: [ORBISGLPERF] shaderType=1
 log: [PS4][DEBUG]: [ORBISGLPERF] modelType=1
 log: [PS4][DEBUG]: [ORBISGLPERF] modelType=2
 log: [PS4][DEBUG]: [ORBISGLPERF] modelType=3
 log: [PS4][DEBUG]: [ORBISGLPERF] backFaceCull=0
 log: [PS4][DEBUG]: [ORBISGLPERF] backFaceCull=1
 log: [PS4][DEBUG]: [ORBISGLPERF] depthTest=1
 log: [PS4][DEBUG]: [ORBISGLPERF] Triangle pressed exit
 log: [PS4][DEBUG]: [orbisAudio] orbisAudioChannelThread 1  exit...
 log: [PS4][DEBUG]: [orbisAudio] closing audio handle
 log: [PS4][DEBUG]: [orbisAudio] free buffers channel
 log: [PS4][DEBUG]: [orbisAudio] finished
 log: [PS4][DEBUG]: [ORBISGL] liborbisGl finished
 log: [PS4][DEBUG]: [ORBISLINK] orbisUserMain return (user): 0
 
 ```
 
 5) ready to have a lot of fun :P 
 
  
 6) I hope that this can help to real developers


  Change log
===========================
 - 24/12/2018 Christmas release
 

  Credits
===========================
  
  - flatz finally brought a lot of fun for christmas !!!!
  - Steve Chamberlin from https://www.bigmessowires.com/about/  rasperf3d was easy to port THANKS!!!!
  - Music from estrayck https://modarchive.org/index.php?request=search&query=estrayk&submit=Find&search_type=filename_or_songtitle
  
  ![alt text](https://raw.github.com/orbisdev/orbisGlPerf/master/capture.png "rex on PlayStation 4 :P")
  
  
 
