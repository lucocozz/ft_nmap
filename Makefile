NAME = ft_nmap
BIN = $(NAME)
BUILD_DIR = .build
SERVCES_DEST = /tmp/ft_nmap_services


ifndef DEBUG
	DEBUG = false
endif

OPTIONS = -Ddebug=$(DEBUG)


all: build compile

build: $(BUILD_DIR)
	@mkdir -p $(SERVCES_DEST)
	@cp -r services/* $(SERVCES_DEST)

$(BUILD_DIR):
	@meson setup $(OPTIONS) $(BUILD_DIR)

reconfigure:
	meson setup --reconfigure $(OPTIONS) $(BUILD_DIR)

wipe:
	meson setup --wipe $(BUILD_DIR)

compile:
	meson compile -C $(BUILD_DIR)
	@ln -sf $(BUILD_DIR)/$(BIN) $(BIN)

clean:
	@rm -rf $(BIN)
	@echo "Executable removed ✅"

fclean: clean
	@rm -rf $(BUILD_DIR)
	@rm -rf $(SERVCES_DEST)
	@echo "Build directory cleaned ✅"

re: reconfigure compile

test:
	@if [ ! -d "$(BUILD_DIR)" ]; then \
		echo "Configuring build directory with tests enabled..."; \
		meson setup $(BUILD_DIR) -Dtest=true; \
	else \
		echo "Reconfiguring build directory with tests enabled..."; \
		meson setup --reconfigure $(BUILD_DIR) -Dtest=true; \
	fi
	@echo "Compiling the project..."
	@meson compile -C $(BUILD_DIR)
	@echo "Running tests..."
	@meson test -C $(BUILD_DIR)


help:
	@echo "Usage: make [target]"
	@echo ""
	@echo "Targets:"
	@echo "  all          - build and compile"
	@echo "  build        - build project"
	@echo "  reconfigure  - reconfigure project"
	@echo "  wipe         - wipe build directory"
	@echo "  compile      - compile project"
	@echo "  clean        - remove executable"
	@echo "  fclean       - clean build directory and remove executable"
	@echo "  re           - reconfigure and compile"
	@echo "  help         - print this help message"


.PHONY: all build compile clean fclean re reconfigure wipe help
