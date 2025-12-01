idf_component_register(
    SRCS "main.cpp"
    INCLUDE_DIRS "."
    PRIV_REQUIRES
        arduino
        wifi_manager
        nvs_flash
)
