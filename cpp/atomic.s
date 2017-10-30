	.arch armv5te
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"atomic.cc"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,4
	.text
	.align	2
	.type	_ZL17__NSDK_FetchIndexv, %function
_ZL17__NSDK_FetchIndexv:
	.fnstart
.LFB961:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.cfi_def_cfa_offset 8
	add	fp, sp, #4
	.cfi_offset 14, -4
	.cfi_offset 11, -8
	.cfi_def_cfa 11, 4
	ldr	r3, .L5
	ldr	r2, [r3, #0]
	ldr	r3, .L5+4
	cmp	r2, r3
	bls	.L2
	ldr	r0, .L5
	mov	r1, #10
	bl	__sync_sub_and_fetch_4
	mov	r3, r0
	b	.L3
.L2:
	ldr	r0, .L5
	mov	r1, #1
	bl	__sync_add_and_fetch_4
	mov	r3, r0
.L3:
	mov	r0, r3
	ldmfd	sp!, {fp, pc}
.L6:
	.align	2
.L5:
	.word	_ZZL17__NSDK_FetchIndexvE7s_index
	.word	19999990
	.cfi_endproc
.LFE961:
	.cantunwind
	.fnend
	.size	_ZL17__NSDK_FetchIndexv, .-_ZL17__NSDK_FetchIndexv
	.global	g_cc
	.data
	.align	2
	.type	g_cc, %object
	.size	g_cc, 4
g_cc:
	.word	10000
	.text
	.align	2
	.global	_Z14pthread_proc_1Pv
	.type	_Z14pthread_proc_1Pv, %function
_Z14pthread_proc_1Pv:
	.fnstart
.LFB962:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_offset 14, -4
	.cfi_offset 11, -8
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	str	r0, [fp, #-8]
	b	.L8
.L11:
	ldr	r3, .L13
	ldr	r2, [r3, #0]
	ldr	r3, .L13+4
	cmp	r2, r3
	bls	.L9
	ldr	r0, .L13
	mov	r1, #10
	bl	__sync_sub_and_fetch_4
	mov	r3, r0
	b	.L10
.L9:
	ldr	r0, .L13
	mov	r1, #1
	bl	__sync_add_and_fetch_4
	mov	r3, r0
.L10:
	ldr	r0, .L13+8
	mov	r1, r3
	bl	_ZNSolsEj
	mov	r3, r0
	mov	r0, r3
	mov	r1, #10
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c
	mov	r0, #100
	bl	usleep
.L8:
	ldr	r3, .L13+12
	ldr	r3, [r3, #0]
	cmp	r3, #0
	moveq	r2, #0
	movne	r2, #1
	and	r2, r2, #255
	sub	r1, r3, #1
	ldr	r3, .L13+12
	str	r1, [r3, #0]
	cmp	r2, #0
	bne	.L11
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L14:
	.align	2
.L13:
	.word	_ZZL17__NSDK_FetchIndexvE7s_index
	.word	19999990
	.word	_ZSt4cout
	.word	g_cc
	.cfi_endproc
.LFE962:
	.fnend
	.size	_Z14pthread_proc_1Pv, .-_Z14pthread_proc_1Pv
	.align	2
	.global	_Z14pthread_proc_2Pv
	.type	_Z14pthread_proc_2Pv, %function
_Z14pthread_proc_2Pv:
	.fnstart
.LFB963:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_offset 14, -4
	.cfi_offset 11, -8
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	str	r0, [fp, #-8]
	b	.L16
.L19:
	ldr	r3, .L21
	ldr	r2, [r3, #0]
	ldr	r3, .L21+4
	cmp	r2, r3
	bls	.L17
	ldr	r0, .L21
	mov	r1, #10
	bl	__sync_sub_and_fetch_4
	mov	r3, r0
	b	.L18
.L17:
	ldr	r0, .L21
	mov	r1, #1
	bl	__sync_add_and_fetch_4
	mov	r3, r0
.L18:
	ldr	r0, .L21+8
	mov	r1, r3
	bl	_ZNSolsEj
	mov	r3, r0
	mov	r0, r3
	mov	r1, #10
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c
	mov	r0, #100
	bl	usleep
.L16:
	ldr	r3, .L21+12
	ldr	r3, [r3, #0]
	cmp	r3, #0
	moveq	r2, #0
	movne	r2, #1
	and	r2, r2, #255
	sub	r1, r3, #1
	ldr	r3, .L21+12
	str	r1, [r3, #0]
	cmp	r2, #0
	bne	.L19
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L22:
	.align	2
.L21:
	.word	_ZZL17__NSDK_FetchIndexvE7s_index
	.word	19999990
	.word	_ZSt4cout
	.word	g_cc
	.cfi_endproc
.LFE963:
	.fnend
	.size	_Z14pthread_proc_2Pv, .-_Z14pthread_proc_2Pv
	.align	2
	.global	_Z14pthread_proc_3Pv
	.type	_Z14pthread_proc_3Pv, %function
_Z14pthread_proc_3Pv:
	.fnstart
.LFB964:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_offset 14, -4
	.cfi_offset 11, -8
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	str	r0, [fp, #-8]
	b	.L24
.L27:
	ldr	r3, .L29
	ldr	r2, [r3, #0]
	ldr	r3, .L29+4
	cmp	r2, r3
	bls	.L25
	ldr	r0, .L29
	mov	r1, #10
	bl	__sync_sub_and_fetch_4
	mov	r3, r0
	b	.L26
.L25:
	ldr	r0, .L29
	mov	r1, #1
	bl	__sync_add_and_fetch_4
	mov	r3, r0
.L26:
	ldr	r0, .L29+8
	mov	r1, r3
	bl	_ZNSolsEj
	mov	r3, r0
	mov	r0, r3
	mov	r1, #10
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c
	mov	r0, #100
	bl	usleep
.L24:
	ldr	r3, .L29+12
	ldr	r3, [r3, #0]
	cmp	r3, #0
	moveq	r2, #0
	movne	r2, #1
	and	r2, r2, #255
	sub	r1, r3, #1
	ldr	r3, .L29+12
	str	r1, [r3, #0]
	cmp	r2, #0
	bne	.L27
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L30:
	.align	2
.L29:
	.word	_ZZL17__NSDK_FetchIndexvE7s_index
	.word	19999990
	.word	_ZSt4cout
	.word	g_cc
	.cfi_endproc
.LFE964:
	.fnend
	.size	_Z14pthread_proc_3Pv, .-_Z14pthread_proc_3Pv
	.align	2
	.global	_Z14pthread_proc_4Pv
	.type	_Z14pthread_proc_4Pv, %function
_Z14pthread_proc_4Pv:
	.fnstart
.LFB965:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_offset 14, -4
	.cfi_offset 11, -8
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	str	r0, [fp, #-8]
	b	.L32
.L35:
	ldr	r3, .L37
	ldr	r2, [r3, #0]
	ldr	r3, .L37+4
	cmp	r2, r3
	bls	.L33
	ldr	r0, .L37
	mov	r1, #10
	bl	__sync_sub_and_fetch_4
	mov	r3, r0
	b	.L34
.L33:
	ldr	r0, .L37
	mov	r1, #1
	bl	__sync_add_and_fetch_4
	mov	r3, r0
.L34:
	ldr	r0, .L37+8
	mov	r1, r3
	bl	_ZNSolsEj
	mov	r3, r0
	mov	r0, r3
	mov	r1, #10
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c
	mov	r0, #100
	bl	usleep
.L32:
	ldr	r3, .L37+12
	ldr	r3, [r3, #0]
	cmp	r3, #0
	moveq	r2, #0
	movne	r2, #1
	and	r2, r2, #255
	sub	r1, r3, #1
	ldr	r3, .L37+12
	str	r1, [r3, #0]
	cmp	r2, #0
	bne	.L35
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L38:
	.align	2
.L37:
	.word	_ZZL17__NSDK_FetchIndexvE7s_index
	.word	19999990
	.word	_ZSt4cout
	.word	g_cc
	.cfi_endproc
.LFE965:
	.fnend
	.size	_Z14pthread_proc_4Pv, .-_Z14pthread_proc_4Pv
	.align	2
	.global	main
	.type	main, %function
main:
	.fnstart
.LFB966:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	@ args = 0, pretend = 0, frame = 40
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_offset 14, -4
	.cfi_offset 11, -8
	.cfi_def_cfa 11, 4
	.pad #40
	sub	sp, sp, #40
	ldr	r3, .L47
	sub	ip, fp, #28
	ldmia	r3, {r0, r1, r2, r3}
	stmia	ip, {r0, r1, r2, r3}
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L40
.L41:
	ldr	r3, [fp, #-12]
	sub	r2, fp, #44
	mov	r3, r3, asl #2
	add	r2, r2, r3
	ldr	r3, [fp, #-12]
	mov	r3, r3, asl #2
	sub	r1, fp, #4
	add	r3, r1, r3
	ldr	r3, [r3, #-24]
	mov	r0, r2
	mov	r1, #0
	mov	r2, r3
	mov	r3, #0
	bl	pthread_create
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L40:
	ldr	r3, [fp, #-12]
	cmp	r3, #3
	movgt	r3, #0
	movle	r3, #1
	and	r3, r3, #255
	cmp	r3, #0
	bne	.L41
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L42
.L43:
	ldr	r3, [fp, #-8]
	mov	r3, r3, asl #2
	sub	r2, fp, #4
	add	r3, r2, r3
	ldr	r3, [r3, #-40]
	mov	r0, r3
	mov	r1, #0
	bl	pthread_join
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L42:
	ldr	r3, [fp, #-8]
	cmp	r3, #3
	movgt	r3, #0
	movle	r3, #1
	and	r3, r3, #255
	cmp	r3, #0
	bne	.L43
	ldr	r3, .L47+4
	ldr	r2, [r3, #0]
	ldr	r3, .L47+8
	cmp	r2, r3
	bls	.L44
	ldr	r0, .L47+4
	mov	r1, #10
	bl	__sync_sub_and_fetch_4
	mov	r3, r0
	b	.L45
.L44:
	ldr	r0, .L47+4
	mov	r1, #1
	bl	__sync_add_and_fetch_4
	mov	r3, r0
.L45:
	ldr	r0, .L47+12
	mov	r1, r3
	bl	_ZNSolsEj
	mov	r3, r0
	mov	r0, r3
	mov	r1, #10
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L48:
	.align	2
.L47:
	.word	_ZZ4mainE4C.64
	.word	_ZZL17__NSDK_FetchIndexvE7s_index
	.word	19999990
	.word	_ZSt4cout
	.cfi_endproc
.LFE966:
	.fnend
	.size	main, .-main
	.align	2
	.type	_Z41__static_initialization_and_destruction_0ii, %function
_Z41__static_initialization_and_destruction_0ii:
	.fnstart
.LFB969:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_offset 14, -4
	.cfi_offset 11, -8
	.cfi_def_cfa 11, 4
	.pad #8
	sub	sp, sp, #8
	str	r0, [fp, #-8]
	str	r1, [fp, #-12]
	ldr	r3, [fp, #-8]
	cmp	r3, #1
	bne	.L50
	ldr	r2, [fp, #-12]
	ldr	r3, .L53
	cmp	r2, r3
	bne	.L50
	ldr	r0, .L53+4
	bl	_ZNSt8ios_base4InitC1Ev
.L50:
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	bne	.L52
	ldr	r2, [fp, #-12]
	ldr	r3, .L53
	cmp	r2, r3
	bne	.L52
	ldr	r0, .L53+4
	bl	_ZNSt8ios_base4InitD1Ev
.L52:
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L54:
	.align	2
.L53:
	.word	65535
	.word	_ZStL8__ioinit
	.cfi_endproc
.LFE969:
	.fnend
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.align	2
	.type	_GLOBAL__I_g_cc, %function
_GLOBAL__I_g_cc:
	.fnstart
.LFB970:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_offset 14, -4
	.cfi_offset 11, -8
	.cfi_def_cfa 11, 4
	mov	r0, #1
	ldr	r1, .L57
	bl	_Z41__static_initialization_and_destruction_0ii
	ldmfd	sp!, {fp, pc}
.L58:
	.align	2
.L57:
	.word	65535
	.cfi_endproc
.LFE970:
	.fnend
	.size	_GLOBAL__I_g_cc, .-_GLOBAL__I_g_cc
	.section	.init_array,"aw",%init_array
	.align	2
	.word	_GLOBAL__I_g_cc(target1)
	.text
	.align	2
	.type	_GLOBAL__D_g_cc, %function
_GLOBAL__D_g_cc:
	.fnstart
.LFB971:
	.cfi_startproc
	.cfi_personality 0x0,__gxx_personality_v0
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.cfi_def_cfa_offset 8
	.setfp fp, sp, #4
	add	fp, sp, #4
	.cfi_offset 14, -4
	.cfi_offset 11, -8
	.cfi_def_cfa 11, 4
	mov	r0, #0
	ldr	r1, .L61
	bl	_Z41__static_initialization_and_destruction_0ii
	ldmfd	sp!, {fp, pc}
.L62:
	.align	2
.L61:
	.word	65535
	.cfi_endproc
.LFE971:
	.fnend
	.size	_GLOBAL__D_g_cc, .-_GLOBAL__D_g_cc
	.section	.fini_array,"aw",%fini_array
	.align	2
	.word	_GLOBAL__D_g_cc(target1)
	.section	.rodata
	.align	2
	.type	_ZZ4mainE4C.64, %object
	.size	_ZZ4mainE4C.64, 16
_ZZ4mainE4C.64:
	.word	_Z14pthread_proc_1Pv
	.word	_Z14pthread_proc_2Pv
	.word	_Z14pthread_proc_3Pv
	.word	_Z14pthread_proc_4Pv
	.data
	.align	2
	.type	_ZZL17__NSDK_FetchIndexvE7s_index, %object
	.size	_ZZL17__NSDK_FetchIndexvE7s_index, 4
_ZZL17__NSDK_FetchIndexvE7s_index:
	.word	19999980
	.section	.rodata
	.align	2
	.type	_ZZL17__NSDK_FetchIndexvE7s_k_max, %object
	.size	_ZZL17__NSDK_FetchIndexvE7s_k_max, 4
_ZZL17__NSDK_FetchIndexvE7s_k_max:
	.word	19999990
	.weakref	_ZL20__gthrw_pthread_oncePiPFvvE,pthread_once
	.weakref	_ZL27__gthrw_pthread_getspecificj,pthread_getspecific
	.weakref	_ZL27__gthrw_pthread_setspecificjPKv,pthread_setspecific
	.weakref	_ZL22__gthrw_pthread_createPmPK14pthread_attr_tPFPvS3_ES3_,pthread_create
	.weakref	_ZL20__gthrw_pthread_joinmPPv,pthread_join
	.weakref	_ZL21__gthrw_pthread_equalmm,pthread_equal
	.weakref	_ZL20__gthrw_pthread_selfv,pthread_self
	.weakref	_ZL22__gthrw_pthread_detachm,pthread_detach
	.weakref	_ZL22__gthrw_pthread_cancelm,pthread_cancel
	.weakref	_ZL19__gthrw_sched_yieldv,sched_yield
	.weakref	_ZL26__gthrw_pthread_mutex_lockP15pthread_mutex_t,pthread_mutex_lock
	.weakref	_ZL29__gthrw_pthread_mutex_trylockP15pthread_mutex_t,pthread_mutex_trylock
	.weakref	_ZL31__gthrw_pthread_mutex_timedlockP15pthread_mutex_tPK8timespec,pthread_mutex_timedlock
	.weakref	_ZL28__gthrw_pthread_mutex_unlockP15pthread_mutex_t,pthread_mutex_unlock
	.weakref	_ZL26__gthrw_pthread_mutex_initP15pthread_mutex_tPK19pthread_mutexattr_t,pthread_mutex_init
	.weakref	_ZL29__gthrw_pthread_mutex_destroyP15pthread_mutex_t,pthread_mutex_destroy
	.weakref	_ZL30__gthrw_pthread_cond_broadcastP14pthread_cond_t,pthread_cond_broadcast
	.weakref	_ZL27__gthrw_pthread_cond_signalP14pthread_cond_t,pthread_cond_signal
	.weakref	_ZL25__gthrw_pthread_cond_waitP14pthread_cond_tP15pthread_mutex_t,pthread_cond_wait
	.weakref	_ZL30__gthrw_pthread_cond_timedwaitP14pthread_cond_tP15pthread_mutex_tPK8timespec,pthread_cond_timedwait
	.weakref	_ZL28__gthrw_pthread_cond_destroyP14pthread_cond_t,pthread_cond_destroy
	.weakref	_ZL26__gthrw_pthread_key_createPjPFvPvE,pthread_key_create
	.weakref	_ZL26__gthrw_pthread_key_deletej,pthread_key_delete
	.weakref	_ZL30__gthrw_pthread_mutexattr_initP19pthread_mutexattr_t,pthread_mutexattr_init
	.weakref	_ZL33__gthrw_pthread_mutexattr_settypeP19pthread_mutexattr_ti,pthread_mutexattr_settype
	.weakref	_ZL33__gthrw_pthread_mutexattr_destroyP19pthread_mutexattr_t,pthread_mutexattr_destroy
	.ident	"GCC: (Buildroot 2012.02) 4.4.0 20100318 (experimental)"
	.section	.note.GNU-stack,"",%progbits
