idf_component_register(
    SRCS "wifi_module.cpp"
    INCLUDE_DIRS "."         # 👈 NECESARIO
    PRIV_REQUIRES arduino
)
