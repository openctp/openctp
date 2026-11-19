# ==========================================
# Windows NMake Makefile
# ==========================================

CXX = cl
CXXFLAGS = -D_CRT_SECURE_NO_WARNINGS /EHsc /W3 /O2 /nologo /I. /ICLI /Inlohmann /ITinyXML2

CTP_DIR = CTPAPI_Win32
OPT_DIR = CTPOPT_Win32

COMMON_OBJS = TinyXML2\tinyxml2.obj

ALL_TARGETS = ctpprice.exe ctpoptprice.exe ctporder.exe ctpoptorder.exe

MD_LIB = $(CTP_DIR)\thostmduserapi_se.lib
TD_LIB = $(CTP_DIR)\thosttraderapi_se.lib
OPT_MD_LIB = $(OPT_DIR)\soptthostmduserapi_se.lib
OPT_TD_LIB = $(OPT_DIR)\soptthosttraderapi_se.lib

all: $(ALL_TARGETS)

# ==========================================
# Link
# ==========================================

# ---------- 1. ctpprice ----------
ctpprice.exe: ctpprice.obj $(COMMON_OBJS)
	$(CXX) /Fe$@ $** $(MD_LIB) /link /nologo

# ---------- 2. ctpoptprice ----------
ctpoptprice.exe: ctpoptprice.obj $(COMMON_OBJS)
	$(CXX) /Fe$@ $** $(OPT_MD_LIB) /link /nologo

# ---------- 3. ctporder ----------
ctporder.exe: ctporder.obj $(COMMON_OBJS)
	$(CXX) /Fe$@ $** $(TD_LIB) /link /nologo

# ---------- 4. ctpoptorder ----------
ctpoptorder.exe: ctpoptorder.obj $(COMMON_OBJS)
	$(CXX) /Fe$@ $** $(OPT_TD_LIB) /link /nologo

# ==========================================
# Objs (.cpp -> .obj)
# ==========================================

ctpprice.obj: ctpprice.cpp
	$(CXX) $(CXXFLAGS) /I$(CTP_DIR) /c $** /Fo$@

ctporder.obj: ctporder.cpp
	$(CXX) $(CXXFLAGS) /I$(CTP_DIR) /c $** /Fo$@

ctpoptprice.obj: ctpoptprice.cpp
	$(CXX) $(CXXFLAGS) /I$(OPT_DIR) /c $** /Fo$@

ctpoptorder.obj: ctpoptorder.cpp
	$(CXX) $(CXXFLAGS) /I$(OPT_DIR) /c $** /Fo$@

TinyXML2\tinyxml2.obj: TinyXML2\tinyxml2.cpp
	$(CXX) $(CXXFLAGS) /c $** /Fo$@

clean:
	-del /Q *.obj TinyXML2\*.obj *.exe *.pdb *.ilk 2>nul

.PHONY: all clean
