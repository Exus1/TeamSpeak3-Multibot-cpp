.PHONY: clean All

All:
	@echo "----------Building project:[ Multibot - Debug 64bit ]----------"
	@cd "Multibot" && "$(MAKE)" -f  "Multibot.mk"
clean:
	@echo "----------Cleaning project:[ Multibot - Debug 64bit ]----------"
	@cd "Multibot" && "$(MAKE)" -f  "Multibot.mk" clean
