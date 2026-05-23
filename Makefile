ifeq ($(OS),Windows_NT)
   EXE = .dev/create.exe
   CMD = $(EXE)
   FLAGS = -std=c++17 -static -lstdc++fs
   MKDIR_DEV = if not exist .dev mkdir .dev
else
   EXE = .dev/create
   CMD = ./$(EXE)
   FLAGS = -std=c++17
   MKDIR_DEV = mkdir -p .dev
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

git: $(EXE)
	@git add .
	@git commit -m "feat: add solution and design for $(LAST_SOL)"
	@git push origin $(shell git symbolic-ref --short HEAD)
	@$(CMD) clear

.PHONY: e m h git $(filter-out e m h git, $(MAKECMDGOALS))

%:
	@:
