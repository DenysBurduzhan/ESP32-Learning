idf_component_register(
    SRCS "main.cpp" "GPIO_driver/GPIO.cpp"
    INCLUDE_DIRS "." "GPIO_driver"
    REQUIRES esp_driver_gpio driver esp_timer
)