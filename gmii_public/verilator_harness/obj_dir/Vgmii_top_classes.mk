# Verilated -*- Makefile -*-
# DESCRIPTION: Verilator output: Make include file with class lists
#
# This file lists generated Verilated files, for including in higher level makefiles.
# See Vgmii_top.mk for the caller.

### Switches...
# C11 constructs required?  0/1 (from --threads, --trace-threads or use of classes)
VM_C11 = 0
# Coverage output mode?  0/1 (from --coverage)
VM_COVERAGE = 0
# Parallel builds?  0/1 (from --output-split)
VM_PARALLEL_BUILDS = 1
# Threaded output mode?  0/1/N threads (from --threads)
VM_THREADS = 0
# Tracing output mode?  0/1 (from --trace/--trace-fst)
VM_TRACE = 1
# Tracing threaded output mode?  0/1/N threads (from --trace-thread)
VM_TRACE_THREADS = 0
# Separate FST writer thread? 0/1 (from --trace-fst with --trace-thread > 0)
VM_TRACE_FST_WRITER_THREAD = 0

### Object file lists...
# Generated module classes, fast-path, compile with highest optimization
VM_CLASSES_FAST += \
	Vgmii_top \

# Generated module classes, non-fast-path, compile with low/medium optimization
VM_CLASSES_SLOW += \
	Vgmii_top__Slow \
	Vgmii_top__1__Slow \
	Vgmii_top__2__Slow \
	Vgmii_top__3__Slow \
	Vgmii_top__4__Slow \
	Vgmii_top__5__Slow \
	Vgmii_top__6__Slow \
	Vgmii_top__7__Slow \
	Vgmii_top__8__Slow \
	Vgmii_top__9__Slow \
	Vgmii_top__10__Slow \
	Vgmii_top__11__Slow \
	Vgmii_top__12__Slow \
	Vgmii_top__13__Slow \
	Vgmii_top__14__Slow \
	Vgmii_top__15__Slow \
	Vgmii_top__16__Slow \
	Vgmii_top__17__Slow \
	Vgmii_top__18__Slow \
	Vgmii_top__19__Slow \
	Vgmii_top__20__Slow \
	Vgmii_top__21__Slow \
	Vgmii_top__22__Slow \
	Vgmii_top__23__Slow \
	Vgmii_top__24__Slow \
	Vgmii_top__25__Slow \
	Vgmii_top__26__Slow \
	Vgmii_top__27__Slow \

# Generated support classes, fast-path, compile with highest optimization
VM_SUPPORT_FAST += \
	Vgmii_top__Trace \

# Generated support classes, non-fast-path, compile with low/medium optimization
VM_SUPPORT_SLOW += \
	Vgmii_top__Syms \
	Vgmii_top__Trace__Slow \

# Global classes, need linked once per executable, fast-path, compile with highest optimization
VM_GLOBAL_FAST += \
	verilated \
	verilated_vcd_c \

# Global classes, need linked once per executable, non-fast-path, compile with low/medium optimization
VM_GLOBAL_SLOW += \


# Verilated -*- Makefile -*-
