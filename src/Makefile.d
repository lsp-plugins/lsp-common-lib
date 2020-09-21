$(LSP_COMMON_LIB_BIN)/main/stdio.o: main/stdio.cpp \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/stdlib/stdio.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/version.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/types.h
$(LSP_COMMON_LIB_BIN)/main/status.o: main/status.cpp \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/status.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/version.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/types.h
$(LSP_COMMON_LIB_BIN)/main/debug.o: main/debug.cpp \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/debug.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/version.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/types.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/stdlib/stdio.h
$(LSP_COMMON_LIB_BIN)/main/bits.o: main/bits.cpp \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/bits.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/version.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/types.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/arch/x86/bits.h
$(LSP_COMMON_LIB_BIN)/test/utest/version.o: test/utest/version.cpp \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/types.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/version.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/stdlib/string.h
$(LSP_COMMON_LIB_BIN)/test/utest/mword.o: test/utest/mword.cpp \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/types.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/version.h
$(LSP_COMMON_LIB_BIN)/test/utest/endian.o: test/utest/endian.cpp \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/endian.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/version.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/types.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/arch/x86/endian.h
$(LSP_COMMON_LIB_BIN)/test/utest/bits.o: test/utest/bits.cpp \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/bits.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/version.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/types.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/arch/x86/bits.h
$(LSP_COMMON_LIB_BIN)/test/utest/atomic.o: test/utest/atomic.cpp \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/atomic.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/version.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/types.h \
 $(LSP_COMMON_LIB_INC)/lsp-plug.in/common/arch/x86/atomic.h
$(LSP_COMMON_LIB_BIN)/test/main.o: test/main.cpp
