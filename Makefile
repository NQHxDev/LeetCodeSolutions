# Xác định file nhị phân và cờ biên dịch dựa trên hệ điều hành
ifeq ($(OS),Windows_NT)
   EXE = .dev/create.exe
   CMD = $(EXE)
   FLAGS = -std=c++17 -static -lstdc++fs
else
   EXE = .dev/create
   CMD = ./$(EXE)
   FLAGS = -std=c++17
endif

# Tự động biên dịch tool nếu chưa có
$(EXE): .dev/create.cpp
	g++ $(FLAGS) .dev/create.cpp -o $(EXE)

e: $(EXE)
	$(CMD) Easy $(filter-out $@,$(MAKECMDGOALS))

m: $(EXE)
	$(CMD) Medium $(filter-out $@,$(MAKECMDGOALS))

h: $(EXE)
	$(CMD) Hard $(filter-out $@,$(MAKECMDGOALS))

%:
	@:
