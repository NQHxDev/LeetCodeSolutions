# Xác định file nhị phân dựa trên hệ điều hành
ifeq ($(OS),Windows_NT)
   EXE = .dev/create.exe
   CMD = $(EXE)
else
   EXE = .dev/create
   CMD = ./$(EXE)
endif

# Tự động biên dịch tool nếu chưa có
$(EXE): .dev/create.cpp
	g++ -std=c++17 -static .dev/create.cpp -o $(EXE) -lstdc++fs

e: $(EXE)
	$(CMD) Easy $(filter-out $@,$(MAKECMDGOALS))

m: $(EXE)
	$(CMD) Medium $(filter-out $@,$(MAKECMDGOALS))

h: $(EXE)
	$(CMD) Hard $(filter-out $@,$(MAKECMDGOALS))

%:
	@:
