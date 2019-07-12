.PHONY: clean All

All:
	@echo "----------Building project:[ AirHockey - Debug ]----------"
	@"$(MAKE)" -f  "AirHockey.mk"
clean:
	@echo "----------Cleaning project:[ AirHockey - Debug ]----------"
	@"$(MAKE)" -f  "AirHockey.mk" clean
