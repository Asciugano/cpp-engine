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
	ctest --test-dir $(BUILD_DIR) --output-on-failure -j

run:
	cmake --build $(BUILD_DIR)
	./$(BUILD_DIR)/game/Rally

clean:
	rm -rf $(BUILD_DIR)

rebuild:
	rm -rf $(BUILD_DIR)
	cmake -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR)
