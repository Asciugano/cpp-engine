.PHONY: configure build compile test run clean rebuild

BUILD_DIR := build

configure:
	cmake -B $(BUILD_DIR)

build:
	cmake -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)

compile:
	cmake --build $(BUILD_DIR)

test:
	cmake --build $(BUILD_DIR)
	@if [ -n "$(FILTER)" ]; then \
		ctest --test-dir $(BUILD_DIR) -R "$(FILTER)" -j --output-on-failure; \
	else \
		ctest --test-dir $(BUILD_DIR) -j --output-on-failure; \
	fi

run:
	cmake --build $(BUILD_DIR)
	./$(BUILD_DIR)/game/Rally

clean:
	rm -rf $(BUILD_DIR)

rebuild:
	rm -rf $(BUILD_DIR)
	cmake -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)
