ifeq ($(OS),Windows_NT)
   EXE = .dev/create.exe
   CMD = $(EXE)
   FLAGS = -std=c++17 -static -lstdc++fs
   ifeq ($(findstring sh,$(SHELL)),sh)
      MKDIR_DEV = mkdir -p .dev
      RM_CPH = find . -type d -name ".cph" -exec rm -rf {} +
      RM_FILES = find . -type f \( -name "*.bin" -o -name "*.exe" \) -exec rm -f {} +
   else
      MKDIR_DEV = if not exist .dev\nul mkdir .dev
      RM_CPH = for /d /r . %%d in (.cph) do @if exist "%%d" rd /s /q "%%d"
      RM_FILES = del /s /q /f *.bin *.exe >nul 2>&1 || exit 0
   endif
else
   EXE = .dev/create
   CMD = ./$(EXE)
   FLAGS = -std=c++17
   MKDIR_DEV = mkdir -p .dev
   RM_CPH = find . -type d -name ".cph" -exec rm -rf {} +
   RM_FILES = find . -type f \( -name "*.bin" -o -name "*.exe" \) -exec rm -f {} +
endif

LAST_SOL = $(shell cat .dev/last_solution.txt 2>/dev/null || type .dev\last_solution.txt 2>nul)

$(EXE): Utils/CreateSolution.cpp
	@$(MKDIR_DEV)
	g++ $(FLAGS) Utils/CreateSolution.cpp -o $(EXE)

e: $(EXE)
	$(CMD) Easy $(filter-out $@,$(MAKECMDGOALS))

m: $(EXE)
	$(CMD) Medium $(filter-out $@,$(MAKECMDGOALS))

h: $(EXE)
	$(CMD) Hard $(filter-out $@,$(MAKECMDGOALS))

c: $(EXE)
	$(CMD) Custom $(filter-out $@,$(MAKECMDGOALS))

git: $(EXE)
	@git add .
	@git commit -m "feat: add solution and design for $(LAST_SOL)"
	@git push origin $(shell git symbolic-ref --short HEAD)
	@$(CMD) clear

clear:
	@$(RM_CPH)
	@$(RM_FILES)
	@echo "Cleaned all .cph folders, .bin and .exe files..."

.PHONY: e m h c git clear $(filter-out e m h c git clear, $(MAKECMDGOALS))

%:
	@:
